#include "servidor/servidor.h"


CodigoRetorno servidor_inicializar (ContextoServidor *contextoServidor)
{
    printf ("-INICIALIZANDO LOS RECURSOS DEL SERVIDOR-\t");

    int resultado;


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoServidor->sock = INVALID_SOCKET;
    contextoServidor->bd = NULL;

    // --------------- CREAR TABLA HASH DE CLIENTES ---------------

    tabla_hash_crear (&(contextoServidor->clientes), CANT_BUCKETS_TABLA_HASH);

    // --------------- CREAR LISTA DOBLE DE CLIENTES NO AUTENTICADOS ---------------

    lista_doble_crear (&(contextoServidor->clientesNoAutenticados));

    // --------------- CREAR COLA DE SOLICITUDES ---------------

    cola_crear (&(contextoServidor->solicitudes));

    // --------------- CREAR LISTA SIMPLE DE RESPUESTAS PENDIENTES ---------------

    lista_simple_crear (&(contextoServidor->respuestasPendientes));

    // --------------- INICIALIZAR SOCKET ---------------

    if (socket_inicializar ())
        return ERROR_INICIALIZACION;

    if (socket_crear (&(contextoServidor->sock)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // --------------- INICIALIZAR BASE DE DATOS ---------------

    if (bd_inicializar (&(contextoServidor->bd), &(contextoServidor->sentenciasSqlite)) == ERROR_INICIALIZACION)
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

CodigoRetorno servidor_configurar (ContextoServidor *contextoServidor)
{
    printf ("-CONFIGURANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- CONFIGURAR MANEJADOR DE CONSOLA ---------------

    if (!SetConsoleCtrlHandler (manejador_consola, TRUE))
    {
        printf ("\nERROR - Configurar el manejador de cierre de la consola.\n");
        return ERROR_CONFIGURACION;
    }

    // --------------- CONFIGURAR SOCKET ---------------

    if (socket_conectar_servidor (&(contextoServidor->sock)) == ERROR_CONFIGURACION)
        return ERROR_CONFIGURACION;
        
    socket_establecer_modo_no_bloqueante (&(contextoServidor->sock));
    socket_establecer_keep_alive (&(contextoServidor->sock));

    // --------------- CONFIGURAR BASE DE DATOS ---------------

    bd_configurar (contextoServidor->bd);


    printf ("-CONFIGURACION EXITOSA-\n");
    printf ("\nCtrl+C -> Apagar servidor\n\n");

    return EXITO;
}

void servidor_liberar (ContextoServidor *contextoServidor)
{
    printf ("-LIBERANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- LIBERAR COLA DE SOLICITUDES ---------------

    cola_vaciar (&(contextoServidor->solicitudes));

    // --------------- LIBERAR LISTA SIMPLE DE RESPUESTAS PENDIENTES ---------------

    lista_simple_vaciar (&(contextoServidor->respuestasPendientes));

    // --------------- LIBERAR LISTA DOBLE DE CLIENTES NO AUTENTICADOS ---------------

    lista_doble_vaciar_con_accion (&(contextoServidor->clientesNoAutenticados), liberar_cliente);

    // --------------- LIBERAR TABLA HASH ---------------

    tabla_hash_eliminar_con_accion (&(contextoServidor->clientes), liberar_cliente);

    // --------------- CERRAR BASE DE DATOS ---------------

    bd_liberar (contextoServidor->bd, &(contextoServidor->sentenciasSqlite));
    
    // --------------- CERRAR SOCKET ---------------

    socket_cerrar (&(contextoServidor->sock));
    socket_finalizar ();


    printf ("-LIBERACION EXITOSA-\n");
    system ("pause");
}


BOOL servidorActivo = TRUE;

BOOL WINAPI manejador_consola (DWORD tipoEvento)
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

