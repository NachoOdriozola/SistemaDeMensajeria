#include "../include/servidor.h"


t_codigoRetorno inicializarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-INICIALIZANDO LOS RECURSOS DEL SERVIDOR-\t");

    int resultado;


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoServidor->sock = INVALID_SOCKET;
    contextoServidor->baseDeDatos = NULL;

    // --------------- CREAR TABLA HASH DE CLIENTES ---------------

    crearTablaHash (&(contextoServidor->clientes), CANT_BUCKETS_TABLA_HASH);

    // --------------- CREAR LISTA DOBLE DE CLIENTES NO AUTENTICADOS ---------------

    crearListaDoble (&(contextoServidor->clientesNoAutenticados));

    // --------------- INICIALIZAR SOCKET ---------------

    if (socket_inicializarServidor (&(contextoServidor->sock)))
        return ERROR_INICIALIZACION;

    // --------------- INICIALIZAR BASE DE DATOS ---------------

    if (inicializarBaseDatos (&(contextoServidor->baseDeDatos), &(contextoServidor->sentenciasSqlite)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // --------------- INICIALIZAR SODIUM ---------------

    if (sodium_init () < 0)
    {
        perror ("\nERROR - Inicializar sodium.\n");
        return ERROR_INICIALIZACION;
    }

    
    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

t_codigoRetorno configurarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-CONFIGURANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- CONFIGURAR MANEJADOR DE CONSOLA ---------------

    if (!SetConsoleCtrlHandler (manejadorConsola, TRUE))
    {
        printf ("\nERROR - Configurar el manejador de cierre de la consola.\n");
        return ERROR_CONFIGURACION;
    }

    // --------------- CONFIGURAR SOCKET ---------------

    if (socket_configurarServidor (&(contextoServidor->sock)) == ERROR_CONFIGURACION)
        return ERROR_CONFIGURACION;

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
    
    // --------------- CERRAR SOCKET ---------------

    socket_cerrar (&(contextoServidor->sock));
    socket_finalizar ();


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

