#include "main.h"

int main()
{
    int resultado;
    WSADATA wsaData;
    struct sockaddr_in direccionServidor;
    SOCKET sock;
    SOCKET cliente1, cliente2;
    u_long modo = 1; //no bloqueante
    struct sockaddr_in direccionCliente1, direccionCliente2;
    int tamCliente;
    char buffer [MAX_BUFFER];
    int bytesRecibidos;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("Error al inicializar Winsock: %d.\n", resultado);
        return 1;
    }
    sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        printf ("Error al crear el socket: %d.\n", WSAGetLastError ());
        WSACleanup ();
        return 1;
    }
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons (PUERTO);
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    if (bind (sock, (struct sockaddr*)&direccionServidor, sizeof (direccionServidor)) == SOCKET_ERROR)
    {
        printf ("Error en el bind: %d.\n", WSAGetLastError ());
        closesocket (sock);
        WSACleanup ();
        return 1;
    }
    if (listen (sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf ("Error en el listen: %d.\n", WSAGetLastError ());
        closesocket (sock);
        WSACleanup ();
        return 1;
    }

    tamCliente = sizeof (direccionCliente1);
    cliente1 = accept (sock, (struct sockaddr*)&direccionCliente1, &tamCliente);
    if (cliente1 == INVALID_SOCKET)
    {
        printf ("Error en aceptar al primer cliente: %d.\n", WSAGetLastError ());
        closesocket (sock);
        WSACleanup ();
        return 1;
    }
    ioctlsocket (cliente1, FIONBIO, &modo);
    printf ("Cliente 1 conectado.\n");
    tamCliente = sizeof (direccionCliente2);
    cliente2 = accept (sock, (struct sockaddr*)&direccionCliente2, &tamCliente);
    if (cliente2 == INVALID_SOCKET)
    {
        printf ("Error en aceptar al primer cliente: %d.\n", WSAGetLastError ());
        closesocket (sock);
        WSACleanup ();
        return 1;
    }
    ioctlsocket (cliente2, FIONBIO, &modo);
    printf ("Cliente 2 conectado.\n");

    while (1)
    {
        bytesRecibidos = recv (cliente1, buffer, sizeof (buffer), 0);
        if (bytesRecibidos > 0)
        {
            buffer [bytesRecibidos] = '\0';
            send (cliente2, buffer, strlen (buffer), 0);
        }
        bytesRecibidos = recv (cliente2, buffer, sizeof (buffer), 0);
        if (bytesRecibidos > 0)
        {
            buffer [bytesRecibidos] = '\0';
            send (cliente1, buffer, strlen (buffer), 0);
        }
    }

    closesocket (cliente1);
    closesocket (cliente2);
    closesocket (sock);
    WSACleanup ();

    return 0;
}



















































