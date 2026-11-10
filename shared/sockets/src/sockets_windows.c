#include "sockets.h"


static bool estadoWinsock = false; // Estado de Winsock API

CodigoRetorno socket_inicializar ()
{
    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        logs_escribir (LOG_ERROR, "sockets", "Inicializacion: Winsock.");
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
        logs_escribir (LOG_ERROR, "sockets", "Creacion: %d", WSAGetLastError ());
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
        logs_escribir (LOG_ERROR, "sockets", "Bind socket del servidor: %d", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    if (listen (*sock, SOMAXCONN) == ERROR_SOCKET)
    {
        logs_escribir (LOG_ERROR, "sockets", "Listen socket del servidor: %d", WSAGetLastError ());
        return ERROR_INICIALIZACION;
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
        logs_escribir (LOG_ERROR, "sockets", "Conexion con el servidor: %d", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

bool socket_es_valido (Socket sock)
{
    return (sock != SOCKET_INVALIDO);
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
    {
        logs_escribir (LOG_ERROR, "sockets", "Establecimiento de keep alive: %d", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

Socket socket_aceptar_nuevo_cliente (Socket socketServidor)
{
    Socket sockCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente = sizeof (dirNuevoCliente);

    sockCliente = accept (socketServidor, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);

    return sockCliente;
}

ResultadoEnvio socket_enviar (Socket sock, const char *buffer, size_t tam)
{
    int bytesEnviados, resultado;

    if (tam <= 0)
    {
        logs_escribir (LOG_ERROR, "sockets", "Envio de datos: tamanio de buffer invalido.");
        return ENVIO_NO_REALIZADO;
    }

    bytesEnviados = send (sock, buffer, (int)tam, 0);

    if (bytesEnviados >= 0)
        return ENVIO_EXITO;

    resultado = WSAGetLastError ();
    logs_escribir (LOG_ERROR, "sockets", "Envio de datos: %d", resultado);
    if (resultado == WSAEWOULDBLOCK)
        return ENVIO_BLOQUEADO;
    return ENVIO_ERROR_CONEXION;
}

ResultadoRecepcion socket_recibir (Socket sock, char *returnBuffer, size_t tamBuffer)
{
    Header header;
    int bytesRecibidos, resultado;

    if (sizeof (Header) > tamBuffer)
    {
        logs_escribir (LOG_ERROR, "sockets", "Recepcion de datos: tamanio de buffer invalido.");
        return RECEPCION_NO_REALIZADA;
    }

    bytesRecibidos = recv (sock, (char*)(&header), sizeof (Header), 0);
    if (bytesRecibidos == 0)
    {
        logs_escribir (LOG_INFO, "sockets", "Recepcion de datos: cliente cerro ordenadamente la conexion.");
        return RECEPCION_CERRADA_ORDENADA;
    }
    else if (bytesRecibidos < 0)
    {
        resultado = WSAGetLastError ();
        if (resultado != WSAEWOULDBLOCK)
        {
            logs_escribir (LOG_AVISO, "sockets", "Recepcion de datos: %d", resultado);
            return RECEPCION_ERROR_CONEXION;
        }
        return RECEPCION_NO_RECIBIO_DATOS;
    }

    if (header.longitud + sizeof (Header) > tamBuffer)
    {
        logs_escribir (LOG_INFO, "sockets", "Recepcion de datos: Paquete supera el tamanio del buffer.");
        return RECEPCION_ERROR_CONEXION;
    }

    memcpy (returnBuffer, &header, sizeof (Header));

    bytesRecibidos = recv (sock, returnBuffer + sizeof (Header), header.longitud, 0);
    if (bytesRecibidos <= 0)
    {
        logs_escribir (LOG_INFO, "sockets", "Recepcion de datos: Paquete de datos incompleto.");
        return RECEPCION_ERROR_CONEXION;
    }

    return RECEPCION_RECIBIO_DATOS;
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
