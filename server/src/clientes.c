#include "../include/clientes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaDoble *clientesNoAutenticados);
static bool recibiSolicitudEnListaDoble (t_listaDoble *listaDoble, t_nodoListaDoble **clienteAProcesar, char *solicitud);
static bool recibiSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodoListaDoble **clienteAProcesar, char *solicitud);


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

bool recibiSolicitud (t_tablaHash *clientes, t_listaDoble *clientesNoAutenticados, t_nodoListaDoble **clienteAProcesar, char *solicitud)
{
    return ((recibiSolicitudEnListaDoble (clientesNoAutenticados, clienteAProcesar, solicitud)) || (recibiSolicitudEnTablaHash (clientes, clienteAProcesar, solicitud)));
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
* Retorna la solicitud que envio el cliente a traves del argumento solicitud.
* Retorna la cantidad de bytes recibidos que envio el cliente a traves del argumento bytesRecibidos.
*/
static bool clienteEnvioSolicitud (t_cliente *cliente, char *solicitud, int *bytesRecibidos)
{
    *bytesRecibidos = socket_recibir (cliente->sock, solicitud);
    if (*bytesRecibidos > 0) // Si se recibio una solicitud.
    {
        // Asegura el caracter nulo al final de la solicitud.
        solicitud += *bytesRecibidos;
        *solicitud = '\0';
        return true;
    }
    return false;
}

static void desconectarCliente (t_listaDoble *listaDoble, int idCliente)
{
    printf ("Cliente ID: %d desconectado.\n\n", idCliente);
    eliminarNodoConAccionListaDoble (listaDoble, NULL, 0, liberarCliente); // Elimina el cliente desconectado de la lista simple.
}

/*
* Guarda la direccion del nodo del cliente a procesar a traves del argumento clienteAProcesar.
* Retorna la solicitud que envio el cliente a traves del argumento solicitud.
*/
static bool recibiSolicitudEnListaDoble (t_listaDoble *listaDoble, t_nodoListaDoble **clienteAProcesar, char *solicitud)
{
    t_cliente *cliente;
    int bytesRecibidos;

    while (*listaDoble != NULL) // Mientras haya clientes en la lista doble.
    {
        cliente = (t_cliente*)((*listaDoble)->dato);

        if (clienteEnvioSolicitud (cliente, solicitud, &bytesRecibidos))
        {
            *clienteAProcesar = *listaDoble; // Guarda la direccion del nodo del cliente que envio la solicitud.
            return RECIBI_SOLICITUD;
        }

        if (socket_perdioConexion (cliente->sock, bytesRecibidos))
            desconectarCliente (listaDoble, cliente->id);
        else
            listaDoble = &((*listaDoble)->sig);
    }

    return NO_RECIBI_SOLICITUD;
}

/*
* Guarda la direccion del nodo del cliente a procesar a traves del argumento clienteAProcesar.
* Retorna la solicitud que envio el cliente a traves del argumento solicitud.
*/
static bool recibiSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodoListaDoble **clienteAProcesar, char *solicitud)
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i++) // Por cada bucket de la tabla hash.
    {
        if (recibiSolicitudEnListaDoble (&(tablaHash->buckets[i]), clienteAProcesar, solicitud)) // Si recibio una solicitud en su lista simple.
            return RECIBI_SOLICITUD;
    }

    return NO_RECIBI_SOLICITUD;
}
