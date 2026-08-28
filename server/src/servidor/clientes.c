#include "servidor/clientes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaDoble *clientesNoAutenticados);
void recibirSolicitudesEnListaDoble (t_listaDoble *listaDoble, t_cola *solicitudes);
void recibirSolicitudesEnTablaHash (t_tablaHash *tablaHash, t_cola *solicitudes);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void aceptarNuevosClientes (t_socket sockServidor, t_listaDoble *clientesNoAutenticados)
{
    t_cliente nuevoCliente;
    
    nuevoCliente.sock = socket_aceptarNuevoCliente (sockServidor);
    if (nuevoCliente.sock != SOCKET_INVALIDO)
        procesarNuevoCliente (&nuevoCliente, clientesNoAutenticados);
}

void recibirSolicitudes (t_contextoServidor *contextoServidor)
{
    recibirSolicitudesEnListaDoble (&(contextoServidor->clientesNoAutenticados), &(contextoServidor->solicitudes));
    recibirSolicitudesEnTablaHash (&(contextoServidor->clientes), &(contextoServidor->solicitudes));
}

t_resultadoEnvio enviarRespuestaACliente (t_contextoServidor *contextoServidor, t_respuestaCliente *respuestaCliente)
{
    t_resultadoEnvio resultadoEnvio;

    resultadoEnvio = socket_enviarTodo (respuestaCliente->clienteAResponder->sock, respuestaCliente->datosAEnviar, respuestaCliente->tamDatosAEnviar);
    if (resultadoEnvio == ENVIO_BUFFER_LLENO)
        insertarAlInicioListaSimple (&(contextoServidor->respuestasPendientes), respuestaCliente->datosAEnviar, respuestaCliente->tamDatosAEnviar);

    return resultadoEnvio;
}

t_resultadoEnvio intentarEnviarRespuestaPendienteACliente (t_respuestaCliente *respuestaPendienteACliente)
{
    return (socket_enviarTodo (respuestaPendienteACliente->clienteAResponder->sock, respuestaPendienteACliente->datosAEnviar, respuestaPendienteACliente->tamDatosAEnviar));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaDoble *clientesNoAutenticados)
{
    printf ("Nuevo cliente conectado.\n\n");
    socket_establecerModoNoBloqueante (&(nuevoCliente->sock));
    nuevoCliente->id = ID_INVALIDO; // Le asigna una ID invalida hasta que se autentifique.

    insertarAlInicioListaDoble (clientesNoAutenticados, nuevoCliente, sizeof (t_cliente));
}


static void desconectarCliente (t_listaDoble *listaDoble, int idCliente)
{
    printf ("Cliente ID: %d desconectado.\n\n", idCliente);
    eliminarNodoConAccionListaDoble (listaDoble, NULL, 0, liberarCliente); // Elimina el cliente desconectado de la lista simple.
}

void recibirSolicitudesEnListaDoble (t_listaDoble *listaDoble, t_cola *solicitudes)
{
    t_cliente *cliente;
    t_solicitudCliente solicitudCliente;
    t_resultadoRecepcion resultadoRecepcion;

    while (*listaDoble != NULL) // Mientras haya clientes en la lista doble.
    {
        cliente = (t_cliente*)((*listaDoble)->dato);
        resultadoRecepcion = socket_recibirTodo (cliente->sock, solicitudCliente.solicitud);
        if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
        {
            solicitudCliente.clienteAProcesar = *listaDoble;
            insertarACola (solicitudes, &solicitudCliente, sizeof (t_solicitudCliente));
        }
        
        if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
            desconectarCliente (listaDoble, cliente->id);
        else
            listaDoble = &((*listaDoble)->sig);
    }
}

void recibirSolicitudesEnTablaHash (t_tablaHash *tablaHash, t_cola *solicitudes)
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i++) // Por cada bucket de la tabla hash.
        recibirSolicitudesEnListaDoble (&(tablaHash->buckets[i]), solicitudes); // Recibir solicitudes en su lista doble.
}
