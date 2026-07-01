#include "../include/servidor.h"


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

    if (inicializarBaseDatos (&(contextoServidor->baseDeDatos), &(contextoServidor->sentenciasSqlite)) == ERROR_INICIALIZACION)
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

    configurarBaseDeDatos (contextoServidor->baseDeDatos);


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

    liberarBaseDeDatos (contextoServidor->baseDeDatos, &(contextoServidor->sentenciasSqlite));

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

