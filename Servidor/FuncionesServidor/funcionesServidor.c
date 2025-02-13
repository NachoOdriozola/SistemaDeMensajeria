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
            bufferSolicitud += bytesRecibidos - 1;
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

void procesarInicioSesion (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud)
{
    char *bufferRespuesta;
    char *nombre, *contrasenia;

    sqlite3_stmt *sentencia;
    char *consulta;
    int resultadoConsulta;

    s_cliente *cliente;
    int id;


    consulta = malloc (MAX_BUFFER_CONSULTA);
    if (!consulta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    nombre = malloc (MAX_BUFFER_NOMBRE);
    if (!nombre)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    contrasenia = malloc (MAX_BUFFER_CONTRASENIA);
    if (!contrasenia)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }


    sscanf (bufferSolicitud, "%[^|]|%s", nombre, contrasenia);
    cliente = servidor->clienteAProcesar->dato;


    strcpy (consulta, "SELECT id FROM usuarios WHERE nombre = ? AND contrasenia = ?;");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contrasenia, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW)
    {
        id = sqlite3_column_int (sentencia, 0);
        sprintf (bufferRespuesta, "%c|%d", SOLICITUD_ACEPTADA, id);
    }
    else
        sprintf (bufferRespuesta, "%c|%d", SOLICITUD_RECHAZADA, 0);
    sqlite3_finalize (sentencia);

    send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);


    free (bufferRespuesta);
    free (consulta);
    free (nombre);
    free (contrasenia);
}

void procesarRegistro (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud)
{
    char *bufferRespuesta;
    char *nombre, *contrasenia;

    sqlite3_stmt *sentencia;
    char *consulta;
    int resultadoConsulta;

    s_cliente *cliente;
    int id;


    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    consulta = malloc (MAX_BUFFER_CONSULTA);
    if (!consulta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    nombre = malloc (MAX_BUFFER_NOMBRE);
    if (!nombre)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    contrasenia = malloc (MAX_BUFFER_CONTRASENIA);
    if (!contrasenia)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }


    sscanf (bufferSolicitud, "%[^|]|%s", nombre, contrasenia);
    cliente = servidor->clienteAProcesar->dato;


    strcpy (consulta, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) //Encontro un usuario con el mismo nombre
    {
        sprintf (bufferRespuesta, "%c|%d", SOLICITUD_RECHAZADA, 0);
        send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        return;
    }
    sqlite3_finalize (sentencia);


    strcpy (consulta, "INSERT INTO usuarios (nombre, contrasenia) VALUES (?, ?);");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
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


    strcpy (consulta, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    id = sqlite3_column_int (sentencia, 0);
    sqlite3_finalize (sentencia);
    sprintf (bufferRespuesta, "%c|%d", SOLICITUD_ACEPTADA, id);

    send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);


    free (bufferRespuesta);
    free (consulta);
    free (nombre);
    free (contrasenia);
}

void procesarSolicitudAmistad (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud)
{
    char *bufferRespuesta;

    sqlite3_stmt *sentencia;
    char *consulta;
    int resultadoConsulta;

    s_cliente *cliente;
    int idEmisor, idReceptor;
    char *nombreEmisor, *nombreReceptor;


    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    consulta = malloc (MAX_BUFFER_CONSULTA);
    if (!consulta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    nombreEmisor = malloc (MAX_BUFFER_NOMBRE);
    if (!nombreEmisor)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    nombreReceptor = malloc (MAX_BUFFER_NOMBRE);
    if (!nombreReceptor)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }


    sprintf (bufferRespuesta, "%c", SOLICITUD_RECHAZADA);
    sscanf (bufferSolicitud, "%d|%[^|]|%s", &idEmisor, nombreEmisor, nombreReceptor);
    cliente = servidor->clienteAProcesar->dato;


    strcpy (consulta, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return;
    }
    sqlite3_bind_text (sentencia, 1, nombreReceptor, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) //Encontro el nombre del usuario receptor
        idReceptor = sqlite3_column_int (sentencia, 0);
    else //No encontro el nombre del usuario receptor
    {
        send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        sqlite3_finalize (sentencia);
        return;
    }
    sqlite3_finalize (sentencia);

    if (idEmisor == idReceptor) //Es la misma persona
    {
        send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        return;
    }


    strcpy (consulta, "INSERT INTO solicitudes_amistad (id_emisor, nombre_emisor, id_receptor) VALUES (?, ?, ?)");
    if (sqlite3_prepare_v2 (db, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return;
    }
    sqlite3_bind_int (sentencia, 1, idEmisor);
    sqlite3_bind_text (sentencia, 2, nombreEmisor, -1, SQLITE_STATIC);
    sqlite3_bind_int (sentencia, 3, idReceptor);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta != SQLITE_DONE)
    {
        perror ("ERROR - Insertar solicitud de amistad en la base de datos.\n");
        sqlite3_finalize (sentencia);
        send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        return;
    }
    sqlite3_finalize (sentencia);

    sprintf (bufferRespuesta, "%c", SOLICITUD_ACEPTADA);
    send (cliente->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);


    free (bufferRespuesta);
    free (consulta);
    free (nombreEmisor);
    free (nombreReceptor);
}

void liberarCliente (void *cliente)
{
    s_cliente *x = (s_cliente*)cliente;

    closesocket (x->sock);
}









































