#include "../../include/sockets.h"


static bool estadoWinsock = false; // Estado de Winsock API


t_codigoRetorno socket_inicializarServidor (t_socket *sock)
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

    *sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sock == SOCKET_INVALIDO)
    {
        printf ("\nERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

t_codigoRetorno socket_configurarServidor (t_socket *sock)
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

    socket_establecerModoNoBloqueante (sock);

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

void socket_establecerModoNoBloqueante (t_socket *sock)
{
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    ioctlsocket (*sock, FIONBIO, &modoSocket);
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
    return ((bytesRecibidos == 0) || // Si el cliente cerro la conexion de forma ordenada.
                ((bytesRecibidos == ERROR_SOCKET) && (WSAGetLastError() == WSAECONNRESET))); // O si cerro la conexion de forma abrupta.
}

void socket_cerrar (t_socket *sock)
{
    if (*sock != SOCKET_INVALIDO)
        closesocket (*sock);
}

void socket_finalizar ()
{
    if (estadoWinsock)
    {
        WSACleanup ();
        estadoWinsock = false;
    }
}
