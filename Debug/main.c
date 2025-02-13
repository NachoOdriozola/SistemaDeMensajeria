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

    char nombre [MAX_NOMBRE_USUARIO], contrasenia [MAX_CONTRASENIA_USUARIO];
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];
    unsigned i;
    int bytesRecibidos;


    for (i = 0; i < 5; i ++)
    {
        printf ("ingrese nombre: ");
        gets (nombre);
        printf ("ingrese contrasenia: ");
        gets (contrasenia);

        sprintf (bufferSolicitud, "%c|%s|%s", INDICE_INICIO_SESION, nombre, contrasenia);
        printf ("Enviado: %s\n", bufferSolicitud);
        send (sock, bufferSolicitud, sizeof (bufferSolicitud), 0);
        bytesRecibidos = recv (sock, bufferRespuesta, sizeof (bufferRespuesta), 0);
        if (bytesRecibidos > 0)
        {
            bufferRespuesta [bytesRecibidos - 1] = '\0';
            printf ("Recibido: .%s.\n", bufferRespuesta);
        }
        else
            printf ("nada.\n");
    }


    ///LIBERAR RECURSOS
    closesocket (sock);
    WSACleanup ();


    return 0;
}





























