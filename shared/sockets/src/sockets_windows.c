#include "sockets.h"


static bool estadoWinsock = false; // Estado de Winsock API


CodigoRetorno socket_inicializar ()
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

CodigoRetorno socket_crear (Socket *sock)
{
    *sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sock == SOCKET_INVALIDO)
    {
        printf ("\nERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

CodigoRetorno socket_conectar_servidor (Socket *sock)
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

CodigoRetorno socket_conectar_cliente (Socket *sock)
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

void socket_establecer_modo_bloqueante (Socket *sock)
{
    u_long modoSocket = 0;
    ioctlsocket (*sock, FIONBIO, &modoSocket);
}

void socket_establecer_modo_no_bloqueante (Socket *sock)
{
    u_long modoSocket = 1;
    ioctlsocket (*sock, FIONBIO, &modoSocket);
}

void socket_establecer_timeout (Socket *sock, DWORD tiempo)
{
    setsockopt (*sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tiempo), sizeof (tiempo));
}

CodigoRetorno socket_establecer_keep_alive (Socket *sock)
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

Socket socket_aceptar_nuevo_cliente (Socket sockServidor)
{
    Socket sockCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente = sizeof (dirNuevoCliente);

    sockCliente = accept (sockServidor, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);

    return sockCliente;
}

ResultadoEnvio socket_enviar_todo (Socket sock, const char *buffer, size_t tamBuffer)
{
    int bytesEnviadosTotales = 0, bytesEnviadosParciales;

    do
    {
        bytesEnviadosParciales = send (sock, buffer + bytesEnviadosTotales, tamBuffer - bytesEnviadosTotales, 0);
        if (bytesEnviadosParciales == ERROR_SOCKET)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
                return ENVIO_BUFFER_LLENO;
            else
                return ENVIO_ERROR_CONEXION;
        }
        bytesEnviadosTotales += bytesEnviadosParciales;
    } while (bytesEnviadosTotales < tamBuffer);

    return ENVIO_COMPLETO;
}

ResultadoRecepcion socket_recibir_todo (Socket sock, char *returnBuffer)
{
    Header header;
    int bytesRecibidosTotales = 0, bytesRecibidosParciales;

    do
    {
        bytesRecibidosParciales = recv (sock, (char*)(&header), sizeof (Header), 0);
    
        if (socket_no_recibio_datos (sock, bytesRecibidosParciales))
            return RECEPCION_NO_RECIBIO_DATOS;
    
        if (socket_perdio_conexion (sock, bytesRecibidosParciales))
            return RECEPCION_ERROR_CONEXION;

        bytesRecibidosTotales += bytesRecibidosParciales;
    } while (bytesRecibidosTotales < sizeof (Header));

    memcpy (returnBuffer, &header, sizeof (Header));
    returnBuffer += bytesRecibidosTotales;
    
    bytesRecibidosTotales = 0;
    do
    {
        bytesRecibidosParciales = recv (sock, returnBuffer, header.bytesTransmitidos - sizeof (Header), 0);
    
        if (socket_perdio_conexion (sock, bytesRecibidosParciales))
            return RECEPCION_ERROR_CONEXION;

        bytesRecibidosTotales += bytesRecibidosParciales;
    } while (bytesRecibidosTotales < header.bytesTransmitidos - sizeof (Header));

    returnBuffer += bytesRecibidosTotales;
    *returnBuffer = '\0';

    return RECEPCION_RECIBIO_DATOS;
}

bool socket_no_recibio_datos (Socket sock, int bytesRecibidos)
{
    return ((bytesRecibidos == ERROR_SOCKET) && 
                ((WSAGetLastError() == WSAEWOULDBLOCK) || (WSAGetLastError() == WSAENOTSOCK)));
}

bool socket_perdio_conexion (Socket sock, int bytesRecibidos)
{
    if (bytesRecibidos == 0) // Si el cliente cerro la conexion de forma ordenada.
        return true;

    if ((bytesRecibidos == ERROR_SOCKET) && (WSAGetLastError () != WSAEWOULDBLOCK)) // Si el cliente cerro la conexion de forma abrupta. Verifica que no sea por el socket no bloqueante.
        return true;

    return false;
}

void socket_cerrar (Socket *sock)
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
