#include "main.h"

int main()
{
    /*
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
    SOCKET sock = INVALID_SOCKET;


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
    char letra = '\0';
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    char bufferSolicitud [MAX_BUFFER_SOLICITUD];
    bool flag = 1;

    strcpy (bufferSolicitud, "1|nacho|nacho");

    while (letra != '1')
    {
        if (flag)
        {
            send (sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
            flag = 0;
        }

        if (recibirSolicitud (sock, bufferRespuesta) == RECIBIO_RESPUESTA)
            puts (bufferRespuesta);


        if (kbhit ())
            letra = getch ();
        Sleep (10);
    }

    ///LIBERAR RECURSOS
    if (sock != INVALID_SOCKET)
    {
        closesocket (sock);
        printf ("entro");
    }
    else
        printf ("no entro");
    WSACleanup ();

    */

    int x, *p = &x;

    MACRO (p);
    printf ("\n%p", p);

    return 0;
}

bool recibirSolicitud (SOCKET sock, char *bufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos - 1;
        *bufferRespuesta = '\0';
        return RECIBIO_RESPUESTA;
    }

    return NO_RECIBIO_RESPUESTA;
}

void enviarYRecibirSolicitud (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta)
{
    int bytesRecibidos;

    send (sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    bufferRespuesta += bytesRecibidos - 1;
    *bufferRespuesta = '\0';
}
























