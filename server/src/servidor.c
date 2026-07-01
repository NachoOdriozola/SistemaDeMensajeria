#include "../include/servidor.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static t_codigoRetorno inicializarBaseDatos(sqlite3 **db);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


t_codigoRetorno inicializarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-INICIALIZANDO LOS RECURSOS DEL SERVIDOR-\t");

    int resultado;


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoServidor->estadoWinsock = false;
    contextoServidor->sock = INVALID_SOCKET;
    contextoServidor->baseDeDatos = NULL;


    // --------------- CREAR TABLA HASH DE CLIENTES ---------------

    crearTablaHash (&(contextoServidor->clientes), CANT_BUCKETS_TABLA_HASH);


    // --------------- CREAR LISTA DOBLE DE CLIENTES NO AUTENTICADOS ---------------

    crearListaDoble (&(contextoServidor->clientesNoAutenticados));


    // --------------- INICIALIZAR WINSOCK API ---------------

    WSADATA wsaData;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("\nERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }
    contextoServidor->estadoWinsock = true;


    // --------------- INICIALIZAR SOCKET DEL SERVIDOR ---------------

    contextoServidor->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (contextoServidor->sock == INVALID_SOCKET)
    {
        printf ("\nERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR BASE DE DATOS ---------------

    if (inicializarBaseDatos (&(contextoServidor->baseDeDatos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

t_codigoRetorno configurarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-CONFIGURANDO LOS RECURSOS DEL SERVIDOR-\t");


    if (!SetConsoleCtrlHandler (manejadorConsola, TRUE))
    {
        printf ("\nERROR - Configurar el manejador de cierre de la consola.\n");
        return ERROR_CONFIGURACION;
    }

    // --------------- CONFIGURAR SOCKET DEL SERVIDOR ---------------

    struct sockaddr_in dirServidor;
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirServidor.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones de cualquier direccion IP.
    if (bind (contextoServidor->sock, (struct sockaddr*)(&dirServidor), sizeof (dirServidor)) == SOCKET_ERROR)
    {
        printf ("\nERROR - Enlazar socket al servidor: %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }
    if (listen (contextoServidor->sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf ("\nERROR - Escuchar socket del servidor %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }
    ioctlsocket (contextoServidor->sock, FIONBIO, &modoSocket);

    // --------------- CONFIGURAR BASE DE DATOS ---------------

    sqlite3_exec (contextoServidor->baseDeDatos, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);


    printf ("-CONFIGURACION EXITOSA-\n");
    printf ("Ctrl+C -> Apagar servidor\n");

    return EXITO;
}

void liberarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-LIBERANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- LIBERAR LISTA DOBLE DE CLIENTES NO AUTENTICADOS ---------------

    vaciarListaDobleConAccion (&(contextoServidor->clientesNoAutenticados), liberarCliente);


    // --------------- LIBERAR TABLA HASH ---------------

    eliminarTablaHashConAccion (&(contextoServidor->clientes), liberarCliente);


    // --------------- CERRAR BASE DE DATOS ---------------

    if (contextoServidor->baseDeDatos != NULL)
        sqlite3_close (contextoServidor->baseDeDatos);


    // --------------- LIBERAR SOCKET DEL SERVIDOR ---------------

    if (contextoServidor->sock != INVALID_SOCKET)
        closesocket (contextoServidor->sock);


    // --------------- LIBERAR WINSOCK API ---------------

    if (contextoServidor->estadoWinsock == true)
        WSACleanup ();


    printf ("-LIBERACION EXITOSA-\n");

    system ("pause");
}


BOOL servidorActivo = TRUE;

BOOL WINAPI manejadorConsola(DWORD tipoEvento)
{
    switch (tipoEvento)
    {
        case CTRL_CLOSE_EVENT:
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            servidorActivo = FALSE;
            return TRUE;

        default:
            break;
    }
    return FALSE;
}

/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static t_respuestaInicializacionDB existeTablaUsuarios (sqlite3 *db)
{
    sqlite3_stmt *sentencia;
    int resultado;

    if (sqlite3_prepare_v2 (db, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return ERROR_PREPARACION_CONSULTA;
    }

    resultado = sqlite3_step (sentencia);
    sqlite3_finalize(sentencia);

    if (resultado == SQLITE_ROW)
        return TABLA_EXISTE;
    return TABLA_NO_EXISTE;
}

static t_codigoRetorno crearEsquema (sqlite3 *db)
{
    FILE *archEsquema;
    long tamArchEsquema;
    char *consulta;

    archEsquema = fopen("../../../server/database/schema.sql", "rb");
    if (!archEsquema)
    {
        perror ("\nERROR - Abrir archivo schema.sql.\n");
        return ERROR_INICIALIZACION;
    }

    fseek (archEsquema, 0, SEEK_END);
    tamArchEsquema = ftell (archEsquema);
    rewind (archEsquema);

    consulta = malloc (tamArchEsquema + 1); // +1 para el '\0'.
    if (!consulta)
    {
        perror ("\nERROR - Sin memoria.\n");
        fclose(archEsquema);
        return ERROR_SIN_MEMORIA;
    }

    fread (consulta, 1, tamArchEsquema, archEsquema);
    consulta[tamArchEsquema] = '\0';

    if (sqlite3_exec (db, consulta, 0, 0, NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Ejecutar schema.sql.\n");
        fclose(archEsquema);
        free (consulta);
        return ERROR_OPERACION;
    }

    fclose(archEsquema);
    free (consulta);

    return EXITO;
}

/*
 * Intentar abrir la base de datos "database.db".
 * Verificar si existen las tablas del disenio.
 * En caso de que existan, la base de datos existe y conserva sus datos.
 * En caso contrario, intenta abrir el archivo "schema.sql" que contiene las consultas SQLite de creacion de tablas, segun el disenio, para ejecutarlas.
 * No cierra la base de datos en caso de fallas.
 * Retorna EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al preparar consultas, abrir archivos y asignar memoria.
 */
static t_codigoRetorno inicializarBaseDatos(sqlite3 **db)
{
    if (sqlite3_open ("../../../server/database/database.db", db) != SQLITE_OK)
    {
        printf("\nERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*db));
        return ERROR_INICIALIZACION;
    }
    
    switch (existeTablaUsuarios (*db))
    {
        case TABLA_EXISTE:
            return EXITO;

        case TABLA_NO_EXISTE:
            if (crearEsquema(*db) != EXITO)
                return ERROR_INICIALIZACION;
            return EXITO;

        default:
            return ERROR_INICIALIZACION;
    }
}
