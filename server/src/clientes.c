#include "../include/clientes.h"



void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaSimple *listaSimpleClientesNoAutenticados)
{
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    printf ("Nuevo cliente conectado.\n\n");
    ioctlsocket (nuevoCliente->sock, FIONBIO, &modoSocket);
    nuevoCliente->id = ID_INVALIDO; // Le asigna una ID invalida hasta que se autentifique.

    insertarAlInicioListaSimple (listaSimpleClientesNoAutenticados, nuevoCliente, sizeof (t_cliente)); // Insertar el cliente en la lista simple de clientes no autenticados.
}

bool recibirSolicitudEnListaSimple (t_listaSimple *listaSimple, t_nodo ***nodoDelCliente, char *bufferSolicitud)
{
    t_cliente *cliente;
    int bytesRecibidos;

    while (*listaSimple != NULL) // Mientras haya clientes en la lista simple.
    {
        cliente = (*listaSimple)->dato;
        bytesRecibidos = recv (cliente->sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
        if (bytesRecibidos > 0) // Si se recibio una solicitud.
        {
            // Asegura el caracter nulo al final de la solicitud.
            bufferSolicitud += bytesRecibidos;
            *bufferSolicitud = '\0';

            *nodoDelCliente = listaSimple; // Guarda la direccion del cliente que envio la solicitud.
            return RECIBIO_SOLICITUD;
        }

        if ((bytesRecibidos == 0) || ((bytesRecibidos == SOCKET_ERROR) && (WSAGetLastError() == WSAECONNRESET))) // Si el cliente perdio la conexion.
        {
            printf ("Cliente ID: %d desconectado.\n\n", cliente->id);
            eliminarNodoConAccionListaSimple (listaSimple, NULL, 0, liberarCliente); // Elimina el cliente desconectado de la lista simple.
        }
        else
            listaSimple = &((*listaSimple)->sig);
    }

    return NO_RECIBIO_SOLICITUD;
}

bool recibirSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodo ***nodoDelCliente, char *bufferSolicitud)
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i++) // Por cada bucket de la tabla hash.
    {
        if (recibirSolicitudEnListaSimple (&(tablaHash->buckets[i]), nodoDelCliente, bufferSolicitud) == RECIBIO_SOLICITUD) // Si se recibio una solicitud en su lista simple.
            return RECIBIO_SOLICITUD;
    }

    return NO_RECIBIO_SOLICITUD;
}
