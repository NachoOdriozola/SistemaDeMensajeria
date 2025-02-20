#include "main.h"

int main()
{
    ///INICIALIZAR WINSOCK  API
    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR SOCKET
    SOCKET sock;
    struct sockaddr_in dirCliente;
    u_long modoSocket = 0; //Socket modo bloqueante

    sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        printf ("ERROR - Crear el socket: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    dirCliente.sin_family = AF_INET;
    dirCliente.sin_port = htons (PUERTO);
    dirCliente.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (sock, (struct sockaddr*)&(dirCliente), sizeof (dirCliente)) == SOCKET_ERROR)
    {
        printf ("ERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    ioctlsocket (sock, FIONBIO, &modoSocket);
    printf ("CONECTADO CON EL SERVIDOR.\n");




    ///VARIABLES PROGRAMA


    ///LIBERAR RECURSOS
    closesocket (sock);
    WSACleanup ();


    return 0;
}

void enviarYRecibirSolicitud (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta)
{
    int bytesRecibidos;

    send (sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    bufferRespuesta += bytesRecibidos - 1;
    *bufferRespuesta = '\0';
}


























