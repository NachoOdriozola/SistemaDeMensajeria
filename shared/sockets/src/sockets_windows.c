#include "../include/sockets.h"


static bool estadoWinsock = false; // Estado de Winsock API


t_codigoRetorno socket_inicializar ()
{
    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("\nERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }
    estadoWinsock = true;

    return EXITO;
}

t_codigoRetorno socket_crear (t_socket *sock)
{
    *sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sock == SOCKET_INVALIDO)
    {
        printf ("\nERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

t_codigoRetorno socket_conectarServidor (t_socket *sock)
{
    struct sockaddr_in dirServidor;

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirServidor.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones de cualquier direccion IP.

    if (bind (*sock, (struct sockaddr*)(&dirServidor), sizeof (dirServidor)) == ERROR_SOCKET)
    {
        printf ("\nERROR - Enlazar socket al servidor: %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }

    if (listen (*sock, SOMAXCONN) == ERROR_SOCKET)
    {
        printf ("\nERROR - Escuchar socket del servidor %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }

    return EXITO;
}

t_codigoRetorno socket_conectarCliente (t_socket *sock)
{
    struct sockaddr_in dirCliente;

    dirCliente.sin_family = AF_INET;
    dirCliente.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirCliente.sin_addr.s_addr = inet_addr ("127.0.0.1"); // Conectarse a IP.

    if (connect (*sock, (struct sockaddr*)(&dirCliente), sizeof (dirCliente)) == ERROR_SOCKET)
    {
        printf ("\nERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }

    return EXITO;
}

void socket_establecerModoBloqueante (t_socket *sock)
{
    u_long modoSocket = 0;
    ioctlsocket (*sock, FIONBIO, &modoSocket);
}

void socket_establecerModoNoBloqueante (t_socket *sock)
{
    u_long modoSocket = 1;
    ioctlsocket (*sock, FIONBIO, &modoSocket);
}

void socket_establecerTimeout (t_socket *sock, DWORD tiempo)
{
    setsockopt (*sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tiempo), sizeof (tiempo));
}

t_codigoRetorno socket_establecerKeepAlive (t_socket *sock)
{
    BOOL activar = true;
    DWORD bytesRetornados;
    struct tcp_keepalive keepAlive;

    setsockopt (*sock, SOL_SOCKET, SO_KEEPALIVE, (char*)(&activar), sizeof (activar));

    keepAlive.onoff = 1;                // Habilitar KeepAlive
    keepAlive.keepalivetime = 60000;    // 60 segundos de inactividad
    keepAlive.keepaliveinterval = 5000; // 5 segundos entre sondas

    if (WSAIoctl (*sock, SIO_KEEPALIVE_VALS, &keepAlive, sizeof(keepAlive), NULL, 0, &bytesRetornados, NULL, NULL) == ERROR_SOCKET)
        return ERROR_INICIALIZACION;

    return EXITO;
}

t_socket socket_aceptarNuevoCliente (t_socket sockServidor)
{
    t_socket sockCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente = sizeof (dirNuevoCliente);

    sockCliente = accept (sockServidor, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);

    return sockCliente;
}

int socket_enviar (t_socket sock, const char *buffer)
{
    return (send (sock, buffer, strlen (buffer), 0));
}

int socket_recibir (t_socket sock, char *returnBuffer)
{
    return (recv (sock, returnBuffer, MAX_BUFFER_SOLICITUD, 0));
}

bool socket_perdioConexion (t_socket sock, int bytesRecibidos)
{
    if (bytesRecibidos == 0) // Si el cliente cerro la conexion de forma ordenada.
        return true;

    if ((bytesRecibidos == ERROR_SOCKET) && (WSAGetLastError () != WSAEWOULDBLOCK)) // Si el cliente cerro la conexion de forma abrupta. Verifica que no sea por el socket no bloqueante.
        return true;

    return false;
}

void socket_cerrar (t_socket *sock)
{
    if (*sock != SOCKET_INVALIDO)
    {
        closesocket (*sock);
        *sock = SOCKET_INVALIDO;
    }
}

void socket_finalizar ()
{
    if (estadoWinsock)
    {
        WSACleanup ();
        estadoWinsock = false;
    }
}
