#include "../include/servidor.h"



int inicializarBaseDatos(sqlite3 **bd)
{
    int resultado;
    char *error = NULL;
    char *consultaSQLITE, *pTemp;
    long tamConsulta;
    sqlite3_stmt *sentencia;
    FILE *arch;


    resultado = sqlite3_open ("../../../server/database/database.db", bd);
    if (resultado != SQLITE_OK)
    {
        printf("\nERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*bd));
        return ERROR_INICIALIZACION;
    }

    consultaSQLITE = malloc (MAX_BUFFER_CONSULTA_SQLITE);
    if (!consultaSQLITE)
    {
        perror ("\nERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    // Verificar si existe la tabla usuarios
    strcpy (consultaSQLITE, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';");
    if (sqlite3_prepare_v2(*bd, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (*bd));
        free(consultaSQLITE);
        return ERROR_INICIALIZACION;
    }

    resultado = (sqlite3_step (sentencia) == SQLITE_ROW);
    sqlite3_finalize(sentencia);

    // Si no existe, ejecutar schema.sql
    if (!resultado)
    {
        arch = fopen("../../../server/database/schema.sql", "rb");
        if (!arch)
        {
            perror ("\nERROR - Abrir archivo schema.sql.\n");
            free(consultaSQLITE);
            return ERROR_INICIALIZACION;
        }

        fseek (arch, 0, SEEK_END);
        tamConsulta = ftell (arch);
        rewind (arch);

        if (tamConsulta >= MAX_BUFFER_CONSULTA_SQLITE)
        {
            pTemp = realloc (consultaSQLITE, tamConsulta + 1);
            if (!pTemp)
            {
                perror ("\nERROR - Sin memoria.\n");
                free(consultaSQLITE);
                fclose(arch);
                return ERROR_SIN_MEMORIA;
            }
            consultaSQLITE = pTemp;
        }

        fread (consultaSQLITE, 1, tamConsulta, arch);
        consultaSQLITE[tamConsulta] = '\0';

        resultado = sqlite3_exec (*bd, consultaSQLITE, 0, 0, &error);
        if (resultado != SQLITE_OK)
        {
            printf ("\nERROR - Ejecutar schema.sql: %s\n", error);
            sqlite3_free (error);
            free(consultaSQLITE);
            fclose(arch);
            return ERROR_OPERACION;
        }

        fclose(arch);
    }

    free(consultaSQLITE);

    return EXITO;
}

int inicializarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-INICIALIZANDO LOS RECURSOS DEL SERVIDOR-\t");

    int resultado;


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoServidor->estadoWinsock = false;
    contextoServidor->sock = INVALID_SOCKET;
    contextoServidor->baseDeDatos = NULL;


    // --------------- CREAR TABLA HASH DE CLIENTES ---------------

    crearTablaHash (&(contextoServidor->tablaHashClientes), CANT_BUCKETS_TABLA_HASH);


    // --------------- CREAR LISTA SIMPLE DE CLIENTES NO AUTENTICADOS ---------------

    crearListaSimple (&(contextoServidor->listaSimpleClientesNoAutenticados));


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

    if (inicializarBaseDatos (&(contextoServidor->baseDeDatos)) != EXITO)
        return ERROR_INICIALIZACION;


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

int configurarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-CONFIGURANDO LOS RECURSOS DEL SERVIDOR-\t");


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


    printf ("-CONFIGURACION EXITOSA-\n");
    return EXITO;
}

void liberarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-LIBERANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- LIBERAR LISTA SIMPLE DE CLIENTES NO AUTENTICADOS ---------------

    vaciarListaSimpleConAccion (&(contextoServidor->listaSimpleClientesNoAutenticados), liberarCliente);


    // --------------- LIBERAR TABLA HASH ---------------

    eliminarTablaHashConAccion (&(contextoServidor->tablaHashClientes), liberarCliente);


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
}

