#include "../include/clientes.h"


/*
* Retorna la solicitud que envio el cliente a traves del argumento solicitud.
* Retorna la cantidad de bytes recibidos que envio el cliente a traves del argumento bytesRecibidos.
*/
static bool clienteEnvioSolicitud (t_cliente *cliente, char *solicitud, int *bytesRecibidos)
{
    *bytesRecibidos = recv (cliente->sock, solicitud, MAX_BUFFER_SOLICITUD, 0);
    if (*bytesRecibidos > 0) // Si se recibio una solicitud.
    {
        // Asegura el caracter nulo al final de la solicitud.
        solicitud += *bytesRecibidos;
        *solicitud = '\0';
        return 1;
    }
    return 0;
}

static bool clientePerdioConexion (int bytesRecibidos)
{
    return ((bytesRecibidos == 0) || // Si el cliente cerro la conexion de forma ordenada.
                ((bytesRecibidos == SOCKET_ERROR) && (WSAGetLastError() == WSAECONNRESET))); // O si cerro la conexion de forma abrupta.
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

        if (clientePerdioConexion (bytesRecibidos))
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


static void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaDoble *clientesNoAutenticados)
{
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    printf ("Nuevo cliente conectado.\n\n");
    ioctlsocket (nuevoCliente->sock, FIONBIO, &modoSocket);
    nuevoCliente->id = ID_INVALIDO; // Le asigna una ID invalida hasta que se autentifique.

    insertarAlInicioListaDoble (clientesNoAutenticados, nuevoCliente, sizeof (t_cliente));
}



void aceptarNuevosClientes (SOCKET sock, t_listaDoble *clientesNoAutenticados)
{
    t_cliente nuevoCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente = sizeof (dirNuevoCliente);

    nuevoCliente.sock = accept (sock, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);
    if (nuevoCliente.sock != INVALID_SOCKET)
        procesarNuevoCliente (&nuevoCliente, clientesNoAutenticados);
}

bool recibiSolicitud (t_tablaHash *clientes, t_listaDoble *clientesNoAutenticados, t_nodoListaDoble **clienteAProcesar, char *solicitud)
{
    return ((recibiSolicitudEnListaDoble (clientesNoAutenticados, clienteAProcesar, solicitud)) || (recibiSolicitudEnTablaHash (clientes, clienteAProcesar, solicitud)));
}