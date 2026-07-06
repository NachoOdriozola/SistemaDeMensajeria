#include "../include/clientes.h"


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


/*
* Retorna la solicitud que envio el cliente a traves del parametro returnSolicitud.
* Retorna la cantidad de bytes recibidos que envio el cliente a traves del argumento returnBytesRecibidos.
*/
static bool clienteEnvioSolicitud (t_cliente *cliente, char *returnSolicitud, int *returnBytesRecibidos)
{
    *returnBytesRecibidos = socket_recibir (cliente->sock, returnSolicitud);
    if (*returnBytesRecibidos > 0) // Si se recibio una solicitud.
    {
        // Asegura el caracter nulo al final de la solicitud.
        returnSolicitud += *returnBytesRecibidos;
        *returnSolicitud = '\0';
        return true;
    }
    return false;
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
    int bytesRecibidos;

    while (*listaDoble != NULL) // Mientras haya clientes en la lista doble.
    {
        cliente = (t_cliente*)((*listaDoble)->dato);
        if (clienteEnvioSolicitud (cliente, solicitudCliente.solicitud, &bytesRecibidos))
        {
            solicitudCliente.clienteAProcesar = *listaDoble;
            insertarACola (solicitudes, &solicitudCliente, sizeof (t_solicitudCliente));
        }

        if (socket_perdioConexion (cliente->sock, bytesRecibidos))
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
