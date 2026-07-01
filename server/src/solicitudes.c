#include "../include/solicitudes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud);
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud);
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud);
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void procesarSolicitud (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud)
{
    t_tipoSolicitud tipoSolicitud = *solicitud;
    const char *solicitudSinTipoSolicitud = &(solicitud[2]);

    printf ("Solicitud recibida: %s\n", solicitud);

    switch (tipoSolicitud)
    {
        case SOLICITUD_AUTENTICACION:
            procesarSolicitudAutenticacion (contextoServidor, clienteAProcesar, solicitudSinTipoSolicitud);
            break;

        case SOLICITUD_REGISTRO:
            procesarSolicitudRegistro (contextoServidor, clienteAProcesar, solicitudSinTipoSolicitud);
            break;

        case SOLICITUD_ENVIO_MENSAJE:
            procesarSolicitudEnvioMensaje (contextoServidor, clienteAProcesar, solicitudSinTipoSolicitud);
            break;

        case SOLICITUD_SELECCION_CHAT:
            procesarSolicitudSeleccionChat (contextoServidor, clienteAProcesar, solicitudSinTipoSolicitud);
            break;

        default:
            break;
    }
}


/* ============================================================================================================================================
   FUNCIONES LOGICAS COMUNES
   ============================================================================================================================================ */


static void conectarUsuario (t_tablaHash *clientes, t_listaDoble *clientesNoAutenticados, t_nodoListaDoble *clienteAProcesar, int idUsuario)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    
    cliente->id = idUsuario;
    
    // Mover el cliente de la lista simple de clientes no autenticados a la tabla hash de clientes autenticados.
    desvincularNodoDeListaDoble (clientesNoAutenticados, clienteAProcesar);
    vincularNodoATablaHash (clientes, &(cliente->id), funcionHash, clienteAProcesar);
}


/* ============================================================================================================================================
   FUNCIONES AUTENTICACION
   ============================================================================================================================================ */


static void extraerDatosSolicitudAutenticacion (const char *solicitud, t_datosAutenticacionUsuario *datosAutenticacionUsuario)
{
    sscanf (solicitud, "%[^|]|%[^\n]", datosAutenticacionUsuario->nombreUsuario, datosAutenticacionUsuario->contrasenia);
}

static bool sonDatosAutenticacionUsuarioInvalidos (const t_datosAutenticacionUsuario *datosAutenticacionUsuario)
{
    if (strlen (datosAutenticacionUsuario->nombreUsuario) < 3)
        return 1;
    
    if (strlen (datosAutenticacionUsuario->contrasenia) < 8)
        return 1;

    return 0;
}

/*
* Si se encontro un usuario con tales datos de autenticacion, retorna en idUsuario su id correspondiente.
* Sino, retorna en idUsuario un id invalido.
*/
static t_estadoSolicitud usuarioExiste (sqlite3 *db, const t_datosAutenticacionUsuario *datosAutenticacionUsuario, int *idUsuario)
{
    t_estadoSolicitud estadoSolicitud;
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios WHERE nombre = ? AND contrasenia = ?;", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_text (sentencia, 1, datosAutenticacionUsuario->nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, datosAutenticacionUsuario->contrasenia, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (ENCONTRO_UN_USUARIO (resultadoConsulta))
    {
        *idUsuario = sqlite3_column_int (sentencia, 0);
        estadoSolicitud = SOLICITUD_EXITO;
    }
    else
    {
        *idUsuario = ID_INVALIDO;
        estadoSolicitud =  SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
    }

    sqlite3_finalize (sentencia);
    return estadoSolicitud;
}

static bool usuarioEstaConectado (t_tablaHash *clientes, int *idUsuario)
{
    return buscarClaveUnicaEnTablaHash (clientes, idUsuario, funcionHash, NULL, 0, cmpIdCliente);
}

static t_estadoSolicitud autenticarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosAutenticacionUsuario *datosAutenticacionUsuario)
{
    int idUsuario;
    t_estadoSolicitud estadoSolicitud;

    if (sonDatosAutenticacionUsuarioInvalidos (datosAutenticacionUsuario))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;

    estadoSolicitud = usuarioExiste (contextoServidor->baseDeDatos, datosAutenticacionUsuario, &idUsuario);
    if (estadoSolicitud == SOLICITUD_EXITO)
    {
        if (usuarioEstaConectado (&(contextoServidor->clientes), &idUsuario))
            return SOLICITUD_ERROR_OPERACION_INVALIDA;
        else
            conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, idUsuario);
    }
        
    return estadoSolicitud;
}

static void enviarRespuestaAutenticacion (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", estadoSolicitud, cliente->id);
    send (cliente->sock, respuesta, strlen (respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * nombre de usuario|contrasenia
 * 
 * Consultar en la base de datos si las credenciales del usuario existen y son validas.
 * Verificar que el usuario no se encuentre conectado.
 * Si el usuario no se encuentra conectado, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Genera una cadena para responder al cliente compuesta de la siguiente manera:
 * estado de la solicitud|ID del usuario
 * 
 * Posibles respuestas:
 * SOLICITUD_EXITO|ID del usuario
 * SOLICITUD_ERROR_SERVIDOR|ID invalido
 * SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido
 * SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido
 */
static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud)
{
    t_datosAutenticacionUsuario datosAutenticacionUsuario;
    t_estadoSolicitud estadoSolicitud;

    extraerDatosSolicitudAutenticacion (solicitud, &datosAutenticacionUsuario);
    estadoSolicitud = autenticarCliente (contextoServidor, clienteAProcesar, &datosAutenticacionUsuario);
    enviarRespuestaAutenticacion (clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES REGISTRO
   ============================================================================================================================================ */


static void extraerDatosSolicitudRegistro (const char *solicitud, t_datosRegistroUsuario *datosRegistroUsuario)
{
    sscanf (solicitud, "%[^|]|%[^|]|%[^\n]", datosRegistroUsuario->nombreUsuario, datosRegistroUsuario->contrasenia, datosRegistroUsuario->correoElectronico);
}

static bool esCorreoElectronicoInvalido (const char *correoElectronico)
{
    char *ptr = strchr (correoElectronico, '@'); // Se posiciona en el @

    if ((ptr == NULL) ||                                // Si no tiene @
        (ptr == correoElectronico) ||            // O empieza con @
        (strchr (ptr, '.') == NULL) ||               // O no tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL))         // O tiene 2 arrobas
        return 1;

    return 0;
}

static bool sonDatosRegistroUsuarioInvalidos (const t_datosRegistroUsuario *datosRegistroUsuario)
{
    int largoNombreUsuario = strlen (datosRegistroUsuario->nombreUsuario);
    int largoContrasenia = strlen (datosRegistroUsuario->contrasenia);

    if (strlen (datosRegistroUsuario->nombreUsuario) < 3)
        return 1;
    
    if (strlen (datosRegistroUsuario->contrasenia) < 8)
        return 1;

    if (esCorreoElectronicoInvalido (datosRegistroUsuario->correoElectronico))
        return 1;

    return 0;
}

static t_estadoSolicitud usuarioYaRegistrado (sqlite3 *db, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios WHERE nombre = ? or correoElectronico = ?;", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_text (sentencia, 1, datosRegistroUsuario->nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, datosRegistroUsuario->correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);
    if (ENCONTRO_UN_USUARIO (resultadoConsulta))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
    return SOLICITUD_EXITO;
}

static t_estadoSolicitud registrarUsuario (sqlite3 *db, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "INSERT INTO usuarios (nombre, contrasenia, correoElectronico) VALUES (?, ?, ?);", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_text (sentencia, 1, datosRegistroUsuario->nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, datosRegistroUsuario->contrasenia, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 3, datosRegistroUsuario->correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);
    return SOLICITUD_EXITO;
}

static t_estadoSolicitud recuperarIdUsuarioRegistrado (sqlite3 *db, const t_datosRegistroUsuario *datosRegistroUsuario, int *idUsuario)
{
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios WHERE nombre = ?;", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_text (sentencia, 1, datosRegistroUsuario->nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    *idUsuario = sqlite3_column_int (sentencia, 0);
    sqlite3_finalize (sentencia);
    return SOLICITUD_EXITO;
}

static t_estadoSolicitud registrarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    int idUsuario;
    t_estadoSolicitud estadoSolicitud;

    if (sonDatosRegistroUsuarioInvalidos (datosRegistroUsuario))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    estadoSolicitud = usuarioYaRegistrado (contextoServidor->baseDeDatos, datosRegistroUsuario);
    if (estadoSolicitud == SOLICITUD_ERROR_CREDENCIALES_INVALIDAS || estadoSolicitud == SOLICITUD_ERROR_SERVIDOR)
        return estadoSolicitud;

    estadoSolicitud = registrarUsuario (contextoServidor->baseDeDatos, datosRegistroUsuario);
    if (estadoSolicitud != SOLICITUD_EXITO)
        return estadoSolicitud;

    estadoSolicitud = recuperarIdUsuarioRegistrado (contextoServidor->baseDeDatos, datosRegistroUsuario, &idUsuario);
    if (estadoSolicitud != SOLICITUD_EXITO)
        return estadoSolicitud;

    conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, idUsuario);

    return SOLICITUD_EXITO;
}

static void enviarRespuestaRegistro (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", estadoSolicitud, cliente->id);
    send (cliente->sock, respuesta, strlen (respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * nombre de usuario|contrasenia|correo electronico
 * 
 * Verificar en la base de datos si ya existe un usuario registrado con el mismo nombre de usuario o correo electronico.
 * Si el usuario se puede registrar, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Genera una cadena para responder al cliente compuesta de la siguiente manera:
 * estado de la solicitud|ID del usuario
 * 
 * Posibles respuestas:
 * SOLICITUD_EXITO|ID del usuario
 * SOLICITUD_ERROR_SERVIDOR|ID invalido
 * SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido
 */
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud)
{
    t_datosRegistroUsuario datosRegistroUsuario;
    t_estadoSolicitud estadoSolicitud;

    extraerDatosSolicitudRegistro (solicitud, &datosRegistroUsuario);
    estadoSolicitud = registrarCliente (contextoServidor, clienteAProcesar, &datosRegistroUsuario);
    enviarRespuestaRegistro (clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES ENVIO MENSAJES
   ============================================================================================================================================ */


static void extrarDatosSolicitudEnvioMensaje (const char *solicitud, t_datosEnvioMensaje *datosEnvioMensaje)
{
    sscanf (solicitud, "%d|%d|%[^\n]", &(datosEnvioMensaje->idEmisor), &(datosEnvioMensaje->idReceptor), datosEnvioMensaje->texto);
}

static bool sonEmisorOReceptorInvalidos (const t_datosEnvioMensaje *datosEnvioMensaje)
{
    return ((datosEnvioMensaje->idEmisor == ID_INVALIDO) || (datosEnvioMensaje->idReceptor == ID_INVALIDO));
}

static bool elEmisorEsElReceptor (const t_datosEnvioMensaje *datosEnvioMensaje)
{
    return (datosEnvioMensaje->idEmisor == datosEnvioMensaje->idReceptor);
}

static bool sonDatosEnvioMensajeInvalidos (const t_datosEnvioMensaje *datosEnvioMensaje)
{
    return ((datosEnvioMensaje->texto == NULL) || (sonEmisorOReceptorInvalidos (datosEnvioMensaje)) || (elEmisorEsElReceptor (datosEnvioMensaje)));
}

static t_estadoSolicitud almacenarMensaje (sqlite3 *db, t_datosEnvioMensaje *datosEnvioMensaje)
{
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "INSERT INTO mensajes (idEmisor, idReceptor, texto) VALUES (?, ?, ?);", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_int (sentencia, 1, datosEnvioMensaje->idEmisor);
    sqlite3_bind_int (sentencia, 2, datosEnvioMensaje->idReceptor);
    sqlite3_bind_text (sentencia, 3, datosEnvioMensaje->texto, -1, SQLITE_STATIC);

    sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);

    return SOLICITUD_EXITO;
}

/*
* Retornar el dato del cliente a traves del argumento cliente si el receptor se encuentra conectado.
*/
static bool receptorEstaConectado (t_tablaHash *clientes, int *idReceptor, t_cliente *cliente)
{
    return buscarClaveUnicaEnTablaHash (clientes, idReceptor, funcionHash, cliente, sizeof (t_cliente), cmpIdCliente);
}

static void enviarMensajeAlReceptor (t_cliente *cliente, t_datosEnvioMensaje *datosEnvioMensaje)
{
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d|%s", RESPUESTA_RECEPCION_MENSAJE, datosEnvioMensaje->idEmisor, datosEnvioMensaje->texto);
    send (cliente->sock, respuesta, strlen (respuesta), 0);
    printf ("Respuesta enviada: %s\n", respuesta);
}

static t_estadoSolicitud enviarMensaje (t_contextoServidor *contextoServidor, t_datosEnvioMensaje *datosEnvioMensaje)
{
    t_cliente clienteReceptor;
    t_estadoSolicitud estadoSolicitud = SOLICITUD_EXITO;

    if (sonDatosEnvioMensajeInvalidos (datosEnvioMensaje))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    estadoSolicitud = almacenarMensaje (contextoServidor->baseDeDatos, datosEnvioMensaje);
    if (estadoSolicitud == SOLICITUD_EXITO)
        if (receptorEstaConectado (&(contextoServidor->clientes), &(datosEnvioMensaje->idReceptor), &clienteReceptor))
            enviarMensajeAlReceptor (&clienteReceptor, datosEnvioMensaje);

    return estadoSolicitud;
}

static void enviarRespuestaEnvioMensaje (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c", estadoSolicitud);
    send (cliente->sock, respuesta, strlen (respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * id del emisor|id del receptor|texto del mensaje
 * 
 * Antes de enviar el mensaje, verifica que el ID del emisor o del receptor sean validos y que no sean los mismos.
 * El mensaje es almacenado en la base de datos antes de ser reenviado al receptor.
 * Si el receptor se encuentra conectado, le reenvia el mensaje con una cadena compuesta de la siguiente manera:
 * tipo respuesta mensaje|id del emisor|texto del mensaje
 * 
 * Genera una cadena para responder al cliente compuesta de la siguiente manera:
 * estado de la solicitud
 * 
 * Posibles respuestas:
 * SOLICITUD_EXITO
 * SOLICITUD_ERROR_OPERACION_INVALIDA
 * SOLICITUD_ERROR_SERVIDOR
 */
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud)
{
    t_datosEnvioMensaje datosEnvioMensaje;
    t_estadoSolicitud estadoSolicitud;

    extrarDatosSolicitudEnvioMensaje (solicitud, &datosEnvioMensaje);
    estadoSolicitud = enviarMensaje (contextoServidor, &datosEnvioMensaje);
    enviarRespuestaEnvioMensaje (clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES SELECCION CHAT
   ============================================================================================================================================ */


static void extraerDatosSolicitudSeleccionChat (const char *solicitud, t_datosSeleccionChat *datosSeleccionChat)
{
    sscanf (solicitud, "%[^\n]", datosSeleccionChat->nombreReceptor);
}

static bool sonDatosSeleccionChatInvalidos (const t_datosSeleccionChat *datosSeleccionChat)
{
    return (strlen (datosSeleccionChat->nombreReceptor) < 3);
}

/*
* Si se encontro un usuario con tal nombre de usuario, retorna en idUsuarioDelChatSeleccionado su id correspondiente.
* Sino, retorna en idUsuarioDelChatSeleccionado un id invalido.
*/
static t_estadoSolicitud usuarioSeleccionadoExiste (sqlite3 *db, t_datosSeleccionChat *datosSeleccionChat, int *idUsuarioDelChatSeleccionado)
{
    t_estadoSolicitud estadoSolicitud;
    sqlite3_stmt *sentencia;
    int resultadoConsulta;

    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios where nombre = ?;", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return SOLICITUD_ERROR_SERVIDOR;
    }
    sqlite3_bind_text (sentencia, 1, datosSeleccionChat->nombreReceptor, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (ENCONTRO_UN_USUARIO (resultadoConsulta))
    {
        *idUsuarioDelChatSeleccionado = sqlite3_column_int (sentencia, 0);
        estadoSolicitud = SOLICITUD_EXITO;
    }
    else
    {
        *idUsuarioDelChatSeleccionado = ID_INVALIDO;
        estadoSolicitud = SOLICITUD_ERROR_OPERACION_INVALIDA;
    }
    
    sqlite3_finalize (sentencia);
    return estadoSolicitud;
}

static bool usuarioSeleccionoSuPropioChat (int idCliente, int idUsuarioDelChatSeleccionado)
{
    return (idCliente == idUsuarioDelChatSeleccionado);
}

static t_estadoSolicitud seleccionarChat (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, t_datosSeleccionChat *datosSeleccionChat, int *idUsuarioDelChatSeleccionado)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    t_estadoSolicitud estadoSolicitud;

    if (sonDatosSeleccionChatInvalidos (datosSeleccionChat))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    estadoSolicitud = usuarioSeleccionadoExiste (contextoServidor->baseDeDatos, datosSeleccionChat, idUsuarioDelChatSeleccionado);
    if (estadoSolicitud == SOLICITUD_EXITO)
        if (usuarioSeleccionoSuPropioChat (cliente->id, *idUsuarioDelChatSeleccionado))
            return SOLICITUD_ERROR_OPERACION_INVALIDA;

    return estadoSolicitud;
}

static void enviarRespuestaSeleccionChat (const t_nodoListaDoble *clienteAProcesar, t_respuestaSeleccionChat *respuestaSeleccionChat)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", respuestaSeleccionChat->estadoSolicitud, respuestaSeleccionChat->idUsuarioDelChatSeleccionado);
    send (cliente->sock, respuesta, strlen (respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * nombre del usuario del chat seleccionado
 *
 * Verificar que el usuario seleccionado existe.
 * Verificar que el usuario no haya seleccionado su propio chat.
 *
 * Genera una cadena para responder al cliente compuesta de la siguiente manera:
 * estado de la solicitud|ID del usuario del chat seleccionado
 * 
 * Posibles respuestas:
 * SOLICITUD_EXITO|ID del usuario del chat seleccionado
 * SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido
 * SOLICITUD_ERROR_SERVIDOR|ID invalido
 */
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud)
{  
    t_datosSeleccionChat datosSeleccionChat;
    t_respuestaSeleccionChat respuestaSeleccionChat;

    extraerDatosSolicitudSeleccionChat (solicitud, &datosSeleccionChat);
    respuestaSeleccionChat.estadoSolicitud = seleccionarChat (contextoServidor, clienteAProcesar, &datosSeleccionChat, &(respuestaSeleccionChat.idUsuarioDelChatSeleccionado));
    enviarRespuestaSeleccionChat (clienteAProcesar, &respuestaSeleccionChat);
}

