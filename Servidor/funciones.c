#include "funciones.h"

int inicializar (s_servidor *servidor)
{
    printf ("INICIALIZANDO SERVIDOR.\n");


    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &(servidor->wsaData));
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION_SERVIDOR;
    }

    servidor->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servidor->sock == INVALID_SOCKET)
    {
        printf ("ERROR - Inicializar socket servidor: %d.\n", WSAGetLastError ());
        WSACleanup ();
        return ERROR_INICIALIZACION_SERVIDOR;
    }

    return OK;
}

int setup (s_servidor *servidor)
{
    printf ("SETUP SERVIDOR.\n");


    u_long modoSocket = 1; //modo no bloqueante

    servidor->direccionServidor.sin_family = AF_INET;
    servidor->direccionServidor.sin_port = htons (PUERTO); //Escucha en este puerto
    servidor->direccionServidor.sin_addr.s_addr = INADDR_ANY; //Acepta cualquier direccion IP
    if (bind (servidor->sock, (struct sockaddr*)(&(servidor->direccionServidor)), sizeof (servidor->direccionServidor)) == SOCKET_ERROR)
    {
        printf ("ERROR - Bind socket a servidor: %d.\n", WSAGetLastError ());
        closesocket (servidor->sock);
        WSACleanup ();
        return ERROR_INICIALIZACION_SERVIDOR;
    }

    if (listen (servidor->sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf ("ERROR - Listen socket de servidor %d.\n", WSAGetLastError ());
        closesocket (servidor->sock);
        WSACleanup ();
        return ERROR_INICIALIZACION_SERVIDOR;
    }
    ioctlsocket (servidor->sock, FIONBIO, &modoSocket);

    return OK;
}

int aceptarCliente (s_servidor *servidor, s_lista *listaClientes)
{
    s_cliente nuevoCliente;
    u_long modoSocket = 1; //modo no bloqueante
    int tamCliente;

    tamCliente = sizeof (nuevoCliente.direccionCliente);
    nuevoCliente.sock = accept (servidor->sock, (struct sockaddr*)(&(nuevoCliente.direccionCliente)), &tamCliente);
    if (nuevoCliente.sock == INVALID_SOCKET)
        return ERROR_ACEPTAR_CLIENTE;
    printf ("Cliente aceptado.\n");
    ioctlsocket (nuevoCliente.sock, FIONBIO, &modoSocket);

    insertarAlInicioLista (listaClientes, &nuevoCliente, sizeof (s_cliente));

    return OK;
}

int recibirMensajes (s_lista *listaClientes, char *buffer)
{
    s_cliente *cliente;
    int bytesRecibidos;

    while (*listaClientes != NULL)
    {
        cliente = (*listaClientes)->dato;
        bytesRecibidos = recv (cliente->sock, buffer, MAX_BUFFER, 0);
        if (bytesRecibidos > 0)
        {
            buffer += bytesRecibidos;
            *buffer = '\0';
            return MENSAJE_RECIBIDO;
        }
        else if ((bytesRecibidos == 0) || ((bytesRecibidos == SOCKET_ERROR) && (WSAGetLastError() == WSAECONNRESET)))
        {
            eliminarNodoConAccion (listaClientes, NULL, 0, liberarCliente);
            printf ("Cliente desconectado.\n");
        }
        if (*listaClientes != NULL)
            listaClientes = &((*listaClientes)->sig);
    }
    return NO_RECIBIO_MENSAJE;
}

void enviarMensajes (s_lista *listaClientes, char *buffer)
{
    s_cliente *cliente;
    int resultado, error;

    while (*listaClientes != NULL)
    {
        cliente = (*listaClientes)->dato;
        resultado = send (cliente->sock, buffer, strlen (buffer), 0);
        if (resultado == SOCKET_ERROR)
        {
            error = WSAGetLastError ();
            if ((error == WSAECONNRESET) || (error == WSAENOTCONN))
            {
                eliminarNodoConAccion (listaClientes, NULL, 0, liberarCliente);
                printf ("Cliente desconectado.\n");
            }
        }
        if (*listaClientes != NULL)
            listaClientes = &((*listaClientes)->sig);
    }
}

void liberarCliente (void *cliente)
{
    s_cliente *x = (s_cliente*)cliente;
    closesocket (x->sock);
}

void liberar (s_servidor *servidor, s_lista *listaClientes)
{
    vaciarListaConAccion (listaClientes, liberarCliente);
    closesocket (servidor->sock);
    WSACleanup ();
}










































