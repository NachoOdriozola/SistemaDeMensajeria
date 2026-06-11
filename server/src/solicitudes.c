#include "../include/solicitudes.h"



int manejarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreUsuario [MAX_NOMBRE_USUARIO], contraseniaUsuario [MAX_CONTRASENIA_USUARIO];
    int idCliente;

    t_cliente *cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = (t_cliente*)((*(clienteAProcesar))->dato);
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^|]|%[^\n]", nombreUsuario, contraseniaUsuario); // Extraer nombre y contrasenia de la solicitud recibida.

    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ? AND contrasenia = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contraseniaUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos con tal nombre y contrasenia.
    {
        idCliente = sqlite3_column_int (sentencia, 0); // Recupera su ID
        if (buscarClaveUnicaEnTablaHash (&(contextoServidor->tablaHashClientes), &idCliente, funcionHash, NULL, 0, cmpIdCliente)) // Si el cliente ya esta conectado
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_OPERACION_INVALIDA, ID_INVALIDO);
        else
        {
            cliente->id = idCliente;
            vincularNodoATablaHash (&(contextoServidor->tablaHashClientes), &(cliente->id), funcionHash, desvincularNodoDeListaSimple (clienteAProcesar)); // Mover cliente de la lista simple de clientes no autenticados a la tabla hash.
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, cliente->id);
        }
    }
    else
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO);
    sqlite3_finalize (sentencia);

    send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);

    return EXITO;
}

int manejarSolicitudRegistro (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreUsuario [MAX_NOMBRE_USUARIO], contraseniaUsuario [MAX_CONTRASENIA_USUARIO], correoElectronico [MAX_CORREO_USUARIO];

    t_cliente *cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = (t_cliente*)((*(clienteAProcesar))->dato);
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^|]|%[^|]|%[^\n]", nombreUsuario, contraseniaUsuario, correoElectronico); // Extraer nombre y contrasenia de la solicitud recibida.

    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ? or correoElectronico = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos ya registrado con el mismo nombre o correo electronico.
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
        return EXITO;
    }


    strcpy (consultaSQLITE, "INSERT INTO usuarios (nombre, contrasenia, correoElectronico) VALUES (?, ?, ?);");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contraseniaUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 3, correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);


    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    cliente->id = sqlite3_column_int (sentencia, 0); // Recupera su ID y la guarda en el cliente correspondiente.
    sqlite3_finalize (sentencia);

    vincularNodoATablaHash (&(contextoServidor->tablaHashClientes), &(cliente->id), funcionHash, desvincularNodoDeListaSimple (clienteAProcesar)); // Mover cliente de la lista simple de clientes no autenticados a la tabla hash.
    snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, cliente->id);
    send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);

    return EXITO;
}

int manejarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    int idEmisor, idReceptor;
    char texto [MAX_BUFFER_MENSAJE];

    t_cliente cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;


    // --------------- LOGICA ---------------

    cliente = *((t_cliente*)((*(clienteAProcesar))->dato));
    sscanf (&(buffersComunicacion->solicitud[2]), "%d|%d|%[^\n]", &idEmisor, &idReceptor, texto);

    if ((idEmisor == idReceptor) || (idReceptor == ID_INVALIDO))
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_ERROR_OPERACION_INVALIDA);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
        return ERROR_OPERACION;
    }

    strcpy (consultaSQLITE, "INSERT INTO mensajes (idEmisor, idReceptor, texto) VALUES (?, ?, ?);");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_ERROR_SERVIDOR);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_int (sentencia, 1, idEmisor);
    sqlite3_bind_int (sentencia, 2, idReceptor);
    sqlite3_bind_text (sentencia, 3, texto, -1, SQLITE_STATIC);

    sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);

    snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_EXITO);
    send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n", buffersComunicacion->respuesta);

    if (buscarClaveUnicaEnTablaHash (&(contextoServidor->tablaHashClientes), &idReceptor, funcionHash, &cliente, sizeof (t_cliente), cmpIdCliente))
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d|%s", RESPUESTA_MENSAJE, idEmisor, texto);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n", buffersComunicacion->respuesta);
    }
    printf ("\n");

    return EXITO;
}

int manejarSolicitudSeleccionContacto (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreReceptor [MAX_NOMBRE_USUARIO];
    int idReceptor;

    t_cliente cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = *((t_cliente*)((*(clienteAProcesar))->dato));
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^\n]", nombreReceptor);

    strcpy (consultaSQLITE, "SELECT id FROM usuarios where nombre = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreReceptor, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos con tal nombre.
    {
        idReceptor = sqlite3_column_int (sentencia, 0);

        if (idReceptor != cliente.id)
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, idReceptor);
        else // Si el receptor es el emisor
        {
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_OPERACION_INVALIDA, ID_INVALIDO);
            send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
            printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
            return ERROR_OPERACION;
        }
    }
    else
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_USUARIO_NO_ENCONTRADO, ID_INVALIDO);
    sqlite3_finalize (sentencia);

    send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);


    return EXITO;
}
