#include "funcionesServidor.h"


///FUNCIONES LOGICAS


int aceptarCliente (s_servidor *servidor)
{
    s_cliente nuevoCliente;
    struct sockaddr_in dirCliente;
    u_long modoSocket = 1; //Modo no bloqueante
    int tamCliente;

    tamCliente = sizeof (dirCliente);
    nuevoCliente.sock = accept (servidor->sockServidor, (struct sockaddr*)(&dirCliente), &tamCliente);
    if (nuevoCliente.sock == INVALID_SOCKET)
        return NO_ACEPTO_CLIENTE;
    printf ("Cliente aceptado.\n");
    ioctlsocket (nuevoCliente.sock, FIONBIO, &modoSocket);

    nuevoCliente.id = -1;
    *nuevoCliente.nombre = '\0';

    insertarAlInicioLista (&(servidor->listaClientes), &nuevoCliente, sizeof (s_cliente));

    return OK;
}

int recibirSolicitud (s_servidor *servidor, char *bufferSolicitud, char *solicitud)
{
    s_cliente *cliente;
    s_lista *pl = &(servidor->listaClientes);
    int bytesRecibidos;
    char *auxBufferSolicitud = bufferSolicitud;

    while (*pl != NULL)
    {
        cliente = (*pl)->dato;
        bytesRecibidos = recv (cliente->sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
        if (bytesRecibidos > 0)
        {
            bufferSolicitud += bytesRecibidos;
            *bufferSolicitud = '\0';
            bufferSolicitud = auxBufferSolicitud;

            *solicitud = *auxBufferSolicitud;

            auxBufferSolicitud += 2;
            strcpy (bufferSolicitud, auxBufferSolicitud);

            servidor->clienteAProcesar = *pl;

            return SOLICITUD_RECIBIDA;
        }
        else if ((bytesRecibidos == 0) || ((bytesRecibidos == SOCKET_ERROR) && (WSAGetLastError() == WSAECONNRESET)))
        {
            eliminarNodoConAccion (pl, NULL, 0, liberarCliente);
            printf ("Cliente desconectado.\n");
        }
        if (*pl != NULL)
            pl = &((*pl)->sig);
    }

    return SOLICITUD_NO_RECIBIDA;
}

void procesarInicioSesion (s_servidor *servidor, sqlite3 **db, char *bufferSolicitud)
{
    s_cliente *cliente;
    char *nombre = bufferSolicitud, *contrasenia;
    int id;
    sqlite3_stmt *sentencia;
    char consulta [MAX_BUFFER_CONSULTA] = "SELECT id FROM usuarios WHERE nombre = ? AND contrasenia = ?;";
    int resultadoConsulta;
    char respuestaSolicitud [MAX_BUFFER_RESPUESTA];

    contrasenia = strchr (bufferSolicitud, '|');
    *contrasenia = '\0';
    contrasenia ++;

    cliente = servidor->clienteAProcesar->dato;

    if (sqlite3_prepare_v2 (*db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (*db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contrasenia, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);

    if (resultadoConsulta == SQLITE_ROW)
    {
        id = sqlite3_column_int (sentencia, 0);
        sprintf (respuestaSolicitud, "%d|%d", SOLICITUD_ACEPTADA, id);
    }
    else
        sprintf (respuestaSolicitud, "%d|%d", SOLICITUD_RECHAZADA, 0);

    sqlite3_finalize (sentencia);

    send (cliente->sock, respuestaSolicitud, sizeof (respuestaSolicitud), 0);
}

void procesarRegistro (s_servidor *servidor, sqlite3 **db, char *bufferSolicitud)
{
    s_cliente *cliente;
    char *nombre = bufferSolicitud, *contrasenia;
    sqlite3_stmt *sentencia;
    char consultaSelect [MAX_BUFFER_CONSULTA] = "SELECT id FROM usuarios WHERE nombre = ?;";
    char consultaInsert [MAX_BUFFER_CONSULTA] = "INSERT INTO usuarios (nombre, contrasenia) VALUES (?, ?);";
    int resultadoConsulta;
    char resultadoSolicitud = SOLICITUD_RECHAZADA;

    contrasenia = strchr (bufferSolicitud, '|');
    *contrasenia = '\0';
    contrasenia ++;

    cliente = servidor->clienteAProcesar->dato;

    if (sqlite3_prepare_v2 (*db, consultaSelect, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (*db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);

    if (resultadoConsulta == SQLITE_ROW) //Encontro un usuario con el mismo nombre
    {
        send (cliente->sock, &resultadoSolicitud, sizeof (resultadoSolicitud), 0);
        return;
    }
    resultadoSolicitud = SOLICITUD_ACEPTADA;


    if (sqlite3_prepare_v2 (*db, consultaInsert, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (*db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contrasenia, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta != SQLITE_DONE)
    {
        perror ("ERROR - Insertar usuario a la base de datos.\n");
        sqlite3_finalize (sentencia);
        return;
    }

    sqlite3_finalize (sentencia);

    send (cliente->sock, &resultadoSolicitud, sizeof (resultadoSolicitud), 0);
}

/*
void enviarMensajes (s_servidor *servidor, char *buffer)
{
    s_cliente *cliente;
    int resultado, error;

    while (*listaClientes != NULL)
    {
        cliente = (*listaClientes)->dato;
        if (cliente->envioMensaje == ENVIO_MENSAJE)
            cliente->envioMensaje = NO_ENVIO_MENSAJE;
        else
        {
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
        }
        if (*listaClientes != NULL)
            listaClientes = &((*listaClientes)->sig);
    }
}
*/

void liberarCliente (void *cliente)
{
    s_cliente *x = (s_cliente*)cliente;

    closesocket (x->sock);
}









































