#include "servidor.h"


CodigoRetorno servidor_inicializar (Servidor *servidor)
{
    if (
        (logs_inicializar ("logs/logs.txt") != EXITO) ||
        (signals_instalar_handler() != EXITO) ||
        (bd_inicializar (&(servidor->bd)) != BD_EXITO) ||
        (registro_clientes_inicializar (&(servidor->registroClientes)) != EXITO) ||
        (servicios_inicializar (&(servidor->servicios), &(servidor->bd), &(servidor->registroClientes)) != EXITO) ||
        (comunicacion_inicializar (&(servidor->comunicacion), &(servidor->registroClientes)) != EXITO)
        )
        {
            bd_liberar (&(servidor->bd));
            registro_clientes_vaciar (&(servidor->registroClientes));
            servicios_liberar (&(servidor->servicios));
            comunicacion_liberar (&(servidor->comunicacion));
            logs_escribir (LOG_ERROR, "servidor", "Inicializacion fallida.");
            return ERROR_INICIALIZACION;
        }
    
    logs_escribir (LOG_INFO, "servidor", "Inicializacion exitosa.");
    return EXITO;
}

void servidor_ejecutar (Servidor *servidor)
{
    while (!signals_apagado_solicitado())
    {
        Solicitud solicitud;

        comunicacion_aceptar_nuevo_cliente (&(servidor->comunicacion));
        comunicacion_recibir_solicitudes (&(servidor->comunicacion));
        while (comunicacion_siguiente_solicitud (&(servidor->comunicacion), &solicitud))
        {
            Respuesta respuesta;

            servicios_procesar (&(servidor->servicios), &solicitud);
            while (servicios_siguiente_respuesta (&(servidor->servicios), &respuesta))
                comunicacion_enviar_respuesta (&(servidor->comunicacion), &respuesta);
        }
        registro_clientes_eliminar_desconectados (&(servidor->registroClientes));

        signals_sleep (200);
    }
    logs_escribir (LOG_INFO, "servidor", "Apagado solicitado.");
}

void servidor_liberar (Servidor *servidor)
{
    comunicacion_liberar (&(servidor->comunicacion));
    servicios_liberar (&(servidor->servicios));
    registro_clientes_vaciar (&(servidor->registroClientes));
    bd_liberar (&(servidor->bd));
    
    logs_escribir (LOG_INFO, "servidor", "Liberacion exitosa.");
    logs_liberar ();
}
