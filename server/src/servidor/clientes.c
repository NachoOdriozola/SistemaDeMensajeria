#include "servidor/clientes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_nuevo_cliente (Cliente *nuevoCliente, ListaDoble *clientesNoAutenticados);
void recibir_solicitudes_lista_doble (ListaDoble *listaDoble, Cola *solicitudes);
void recibir_solicitudes_tabla_hash (TablaHash *tablaHash, Cola *solicitudes);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void aceptar_nuevos_clientes (Socket sockServidor, ListaDoble *clientesNoAutenticados)
{
    Cliente nuevoCliente;
    
    nuevoCliente.sock = socket_aceptar_nuevo_cliente (sockServidor);
    if (nuevoCliente.sock != SOCKET_INVALIDO)
        procesar_nuevo_cliente (&nuevoCliente, clientesNoAutenticados);
}

void recibir_solicitudes (ContextoServidor *contextoServidor)
{
    recibir_solicitudes_lista_doble (&(contextoServidor->clientesNoAutenticados), &(contextoServidor->solicitudes));
    recibir_solicitudes_tabla_hash (&(contextoServidor->clientes), &(contextoServidor->solicitudes));
}

ResultadoEnvio enviar_respuesta_cliente (ContextoServidor *contextoServidor, RespuestaCliente *respuestaCliente)
{
    ResultadoEnvio resultadoEnvio;

    resultadoEnvio = socket_enviar_todo (respuestaCliente->clienteAResponder->sock, respuestaCliente->datosAEnviar, respuestaCliente->tamDatosAEnviar);
    if (resultadoEnvio == ENVIO_BUFFER_LLENO)
        lista_simple_insertar_al_inicio (&(contextoServidor->respuestasPendientes), respuestaCliente->datosAEnviar, respuestaCliente->tamDatosAEnviar);

    return resultadoEnvio;
}

ResultadoEnvio intentar_enviar_respuesta_pendiente_cliente (RespuestaCliente *respuestaPendienteCliente)
{
    return (socket_enviar_todo (respuestaPendienteCliente->clienteAResponder->sock, respuestaPendienteCliente->datosAEnviar, respuestaPendienteCliente->tamDatosAEnviar));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_nuevo_cliente (Cliente *nuevoCliente, ListaDoble *clientesNoAutenticados)
{
    printf ("Nuevo cliente conectado.\n\n");
    socket_establecer_modo_no_bloqueante (&(nuevoCliente->sock));
    nuevoCliente->id = ID_INVALIDO; // Le asigna una ID invalida hasta que se autentifique.

    lista_doble_insertar_al_inicio (clientesNoAutenticados, nuevoCliente, sizeof (Cliente));
}


static void desconectar_cliente (ListaDoble *listaDoble, int idCliente)
{
    printf ("Cliente ID: %d desconectado.\n\n", idCliente);
    lista_doble_eliminar_nodo_con_accion (listaDoble, NULL, 0, liberar_cliente); // Elimina el cliente desconectado de la lista simple.
}

void recibir_solicitudes_lista_doble (ListaDoble *listaDoble, Cola *solicitudes)
{
    Cliente *cliente;
    SolicitudCliente solicitudCliente;
    ResultadoRecepcion resultadoRecepcion;

    while (*listaDoble != NULL) // Mientras haya clientes en la lista doble.
    {
        cliente = (Cliente*)((*listaDoble)->dato);
        resultadoRecepcion = socket_recibir_todo (cliente->sock, solicitudCliente.solicitud);
        if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
        {
            solicitudCliente.clienteAProcesar = *listaDoble;
            cola_insertar (solicitudes, &solicitudCliente, sizeof (SolicitudCliente));
        }
        
        if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
            desconectar_cliente (listaDoble, cliente->id);
        else
            listaDoble = &((*listaDoble)->sig);
    }
}

void recibir_solicitudes_tabla_hash (TablaHash *tablaHash, Cola *solicitudes)
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i++) // Por cada bucket de la tabla hash.
        recibir_solicitudes_lista_doble (&(tablaHash->buckets[i]), solicitudes); // Recibir solicitudes en su lista doble.
}
