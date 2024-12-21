#include "main.h"

int main()
{
    int resultado;
    char buffer [MAX_BUFFER] = "\0";
    int bytesRecibidos;
    u_long modo = 1; //no bloqueante
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;

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
    ioctlsocket (sock, FIONBIO, &modo);

    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons (PUERTO);
    direccionServidor.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (sock, (struct sockaddr*)(&direccionServidor), sizeof (direccionServidor)) != SOCKET_ERROR)
    {
        printf ("Error al conectarse con el servidor: %d.\n", WSAGetLastError ());
        closesocket (sock);
        WSACleanup ();
        return 1;
    }
    printf ("Conectado al servidor.\n");
    printf ("Escriba 'x' para cerrar.\n");
    while (strcmp (buffer, "x\n") != 0)
    {
        if (_kbhit ())
        {
            fgets (buffer, sizeof (buffer), stdin);
            send (sock, buffer, strlen (buffer), 0);
        }
        bytesRecibidos = recv (sock, buffer, sizeof (buffer) - 1, 0);
        if (bytesRecibidos > 0)
        {
            buffer [bytesRecibidos] = '\0';
            if (strcmp (buffer, "x\n") == 0)
                *buffer = '\0';
            else
                printf ("Mensaje recibido: %s", buffer);
        }
        Sleep (10);
    }

    closesocket (sock);
    WSACleanup ();

    system ("pause");

    return 0;
}













