#include "../include/solicitudes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void procesarSolicitudes (t_contextoServidor *contextoServidor)
{
    t_solicitudCliente solicitudCliente;
    t_tipoSolicitud tipoSolicitud;

    while (noEsColaVacia (&(contextoServidor->solicitudes)))
    {
        desacolar (&(contextoServidor->solicitudes), &solicitudCliente, sizeof (t_solicitudCliente));
        printf ("Solicitud recibida: %s\n", solicitudCliente.solicitud);

        tipoSolicitud = *(solicitudCliente.solicitud);
        switch (tipoSolicitud)
        {
            case SOLICITUD_AUTENTICACION:
                procesarSolicitudAutenticacion (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_REGISTRO:
                procesarSolicitudRegistro (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_ENVIO_MENSAJE:
                procesarSolicitudEnvioMensaje (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_SELECCION_CHAT:
                procesarSolicitudSeleccionChat (contextoServidor, &solicitudCliente);
                break;
    
            default:
                break;
        }
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

static bool sonTodosEspacios (const char *mensaje)
{
    if (*mensaje == '\0')
        return false;

    while (*mensaje == ' ')
        mensaje ++;

    if (*mensaje == '\0')
        return true;
    return false;
}


/* ============================================================================================================================================
   FUNCIONES AUTENTICACION
   ============================================================================================================================================ */


static void extraerDatosSolicitudAutenticacion (const char *solicitud, t_datosAutenticacionUsuario *returnDatosAutenticacionUsuario)
{
    char tipoSolicitud;
    sscanf (solicitud, "%c|%[^|]|%[^\n]", &tipoSolicitud, returnDatosAutenticacionUsuario->nombreUsuario, returnDatosAutenticacionUsuario->contrasenia);
}

static bool sonDatosAutenticacionUsuarioInvalidos (const t_datosAutenticacionUsuario *datosAutenticacionUsuario)
{
    if ((strlen (datosAutenticacionUsuario->nombreUsuario) < 3) || (sonTodosEspacios (datosAutenticacionUsuario->nombreUsuario)))
        return 1;
    
    if ((strlen (datosAutenticacionUsuario->contrasenia) < 8) || (sonTodosEspacios (datosAutenticacionUsuario->contrasenia)))
        return 1;

    return 0;
}

static bool usuarioNoExiste (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, const t_datosAutenticacionUsuario *datosAutenticacionUsuario, int *returnIdUsuario, char *returnContrasenia)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosAutenticacionUsuario->nombreUsuario);

    return (!buscarUsuarioPorNombre_recuperarIdYContrasenia (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, &datosBuscarUsuarioPorNombre, returnIdUsuario, returnContrasenia));
}

static bool contraseniaNoCoincide (const t_datosAutenticacionUsuario *datosAutenticacionUsuario, const char *hashContrasenia)
{
    return (crypto_pwhash_str_verify (hashContrasenia, datosAutenticacionUsuario->contrasenia, strlen (datosAutenticacionUsuario->contrasenia)));
}

static bool usuarioEstaConectado (t_tablaHash *clientes, int *idUsuario)
{
    return buscarClaveUnicaEnTablaHash (clientes, idUsuario, funcionHash, NULL, 0, cmpIdCliente);
}

static t_estadoSolicitud autenticarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosAutenticacionUsuario *datosAutenticacionUsuario)
{
    int idUsuario;
    char hashContrasenia [MAX_CONTRASENIA];

    if (sonDatosAutenticacionUsuarioInvalidos (datosAutenticacionUsuario))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;

    if (usuarioNoExiste (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarIdYContrasenia, datosAutenticacionUsuario, &idUsuario, hashContrasenia))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
    
    if (contraseniaNoCoincide (datosAutenticacionUsuario, hashContrasenia))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;

    if (usuarioEstaConectado (&(contextoServidor->clientes), &idUsuario))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;
            
    conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, idUsuario);

    return SOLICITUD_EXITO;
}

static void enviarRespuestaAutenticacion (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", estadoSolicitud, cliente->id);
    socket_enviar (cliente->sock, respuesta);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * SOLICITUD_AUTENTICACION|nombre de usuario|contrasenia
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
 * SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido
 * SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido
 */
static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosAutenticacionUsuario datosAutenticacionUsuario;
    t_estadoSolicitud estadoSolicitud;

    extraerDatosSolicitudAutenticacion (solicitudCliente->solicitud, &datosAutenticacionUsuario);
    estadoSolicitud = autenticarCliente (contextoServidor, solicitudCliente->clienteAProcesar, &datosAutenticacionUsuario);
    enviarRespuestaAutenticacion (solicitudCliente->clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES REGISTRO
   ============================================================================================================================================ */


static void extraerDatosSolicitudRegistro (const char *solicitud, t_datosRegistroUsuario *returnDatosRegistroUsuario)
{
    char tipoSolicitud;
    sscanf (solicitud, "%c|%[^|]|%[^|]|%[^\n]", &tipoSolicitud, returnDatosRegistroUsuario->nombreUsuario, returnDatosRegistroUsuario->contrasenia, returnDatosRegistroUsuario->correoElectronico);
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

    if ((strlen (datosRegistroUsuario->nombreUsuario) < 3) || sonTodosEspacios (datosRegistroUsuario->nombreUsuario))
        return 1;
    
    if ((strlen (datosRegistroUsuario->contrasenia) < 8) || sonTodosEspacios (datosRegistroUsuario->contrasenia))
        return 1;

    if (esCorreoElectronicoInvalido (datosRegistroUsuario->correoElectronico))
        return 1;

    return 0;
}

static nombreYaExistente (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosRegistroUsuario->nombreUsuario);

    return (buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, NULL));
}

static correoYaExistente (sqlite3_stmt *sentenciaBuscarUsuarioPorCorreo, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    t_datosBuscarUsuarioPorCorreo datosBuscarUsuarioPorCorreo;

    strcpy (datosBuscarUsuarioPorCorreo.correoElectronico, datosRegistroUsuario->correoElectronico);

    return (buscarUsuarioPorCorreo (sentenciaBuscarUsuarioPorCorreo, &datosBuscarUsuarioPorCorreo));
}

static t_codigoRetorno hashearContrasenia (t_datosRegistroUsuario *datosRegistroUsuario)
{
    char contraseniaHasheada [crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str (contraseniaHasheada, datosRegistroUsuario->contrasenia, strlen (datosRegistroUsuario->contrasenia), 3, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0)
        return ERROR_INICIALIZACION;

    strcpy (datosRegistroUsuario->contrasenia, contraseniaHasheada);
    
    return EXITO;
}

static void registrarUsuario (sqlite3_stmt *sentenciaInsertarUsuario, const t_datosRegistroUsuario *datosRegistroUsuario)
{
    t_datosInsertarUsuario datosInsertarUsuario;

    strcpy (datosInsertarUsuario.nombreUsuario, datosRegistroUsuario->nombreUsuario);
    strcpy (datosInsertarUsuario.contrasenia, datosRegistroUsuario->contrasenia);
    strcpy (datosInsertarUsuario.correoElectronico, datosRegistroUsuario->correoElectronico);

    insertarUsuario (sentenciaInsertarUsuario, &datosInsertarUsuario);
}

static void recuperarIdUsuarioRecienRegistrado (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosRegistroUsuario *datosRegistroUsuario, int *returnIdUsuario)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosRegistroUsuario->nombreUsuario);

    buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, returnIdUsuario);
}

static t_estadoSolicitud registrarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, t_datosRegistroUsuario *datosRegistroUsuario)
{
    int idUsuario;

    if (sonDatosRegistroUsuarioInvalidos (datosRegistroUsuario))
        return SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;

    if (nombreYaExistente (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosRegistroUsuario))
        return SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE;

    if (correoYaExistente (contextoServidor->sentenciasSqlite.buscarUsuarioPorCorreo, datosRegistroUsuario))
        return SOLICITUD_ERROR_CORREO_YA_EXISTENTE;

    if (hashearContrasenia (datosRegistroUsuario) == ERROR_INICIALIZACION)
        return SOLICITUD_ERROR_SERVIDOR;

    registrarUsuario (contextoServidor->sentenciasSqlite.insertarUsuario, datosRegistroUsuario);
    recuperarIdUsuarioRecienRegistrado (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosRegistroUsuario, &idUsuario);
    conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, idUsuario);

    return SOLICITUD_EXITO;
}

static void enviarRespuestaRegistro (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", estadoSolicitud, cliente->id);
    socket_enviar (cliente->sock, respuesta);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * SOLICITUD_REGISTRO|nombre de usuario|contrasenia|correo electronico
 * 
 * Verificar en la base de datos si ya existe un usuario registrado con el mismo nombre de usuario o correo electronico.
 * Si el usuario se puede registrar, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Genera una cadena para responder al cliente compuesta de la siguiente manera:
 * estado de la solicitud|ID del usuario
 * 
 * Posibles respuestas:
 * SOLICITUD_EXITO|ID del usuario
 * SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido
 * SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE|ID invalido
 * SOLICITUD_ERROR_CORREO_YA_EXISTENTE|ID invalido
 */
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosRegistroUsuario datosRegistroUsuario;
    t_estadoSolicitud estadoSolicitud;

    extraerDatosSolicitudRegistro (solicitudCliente->solicitud, &datosRegistroUsuario);
    estadoSolicitud = registrarCliente (contextoServidor, solicitudCliente->clienteAProcesar, &datosRegistroUsuario);
    enviarRespuestaRegistro (solicitudCliente->clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES ENVIO MENSAJES
   ============================================================================================================================================ */


static void extrarDatosSolicitudEnvioMensaje (const char *solicitud, t_datosEnvioMensaje *returnDatosEnvioMensaje)
{
    char tipoSolicitud;
    sscanf (solicitud, "%c|%d|%d|%[^\n]", &tipoSolicitud, &(returnDatosEnvioMensaje->idEmisor), &(returnDatosEnvioMensaje->idReceptor), returnDatosEnvioMensaje->texto);
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
    return ((*(datosEnvioMensaje->texto) == '\0') || 
                (sonTodosEspacios (datosEnvioMensaje->texto)) ||
                (sonEmisorOReceptorInvalidos (datosEnvioMensaje)) || 
                (elEmisorEsElReceptor (datosEnvioMensaje)));
}

static void almacenarMensaje (sqlite3_stmt *sentenciaInsertarMensaje, const t_datosEnvioMensaje *datosEnvioMensaje)
{
    t_datosInsertarMensaje datosInsertarMensaje;

    datosInsertarMensaje.idEmisor = datosEnvioMensaje->idEmisor;
    datosInsertarMensaje.idReceptor = datosEnvioMensaje->idReceptor;
    strcpy (datosInsertarMensaje.texto, datosEnvioMensaje->texto);

    insertarMensaje (sentenciaInsertarMensaje, &datosInsertarMensaje);
}

static bool receptorEstaConectado (t_tablaHash *clientes, const int *idReceptor, t_cliente *returnCliente)
{
    return buscarClaveUnicaEnTablaHash (clientes, idReceptor, funcionHash, returnCliente, sizeof (t_cliente), cmpIdCliente);
}

static void enviarMensajeAlReceptor (t_cliente *cliente, const t_datosEnvioMensaje *datosEnvioMensaje)
{
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d|%s", RESPUESTA_RECEPCION_MENSAJE, datosEnvioMensaje->idEmisor, datosEnvioMensaje->texto);
    socket_enviar (cliente->sock, respuesta);
    printf ("Respuesta enviada: %s\n", respuesta);
}

static t_estadoSolicitud enviarMensaje (t_contextoServidor *contextoServidor, const t_datosEnvioMensaje *datosEnvioMensaje)
{
    t_cliente clienteReceptor;

    if (sonDatosEnvioMensajeInvalidos (datosEnvioMensaje))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    almacenarMensaje (contextoServidor->sentenciasSqlite.insertarMensaje, datosEnvioMensaje);
    if (receptorEstaConectado (&(contextoServidor->clientes), &(datosEnvioMensaje->idReceptor), &clienteReceptor))
        enviarMensajeAlReceptor (&clienteReceptor, datosEnvioMensaje);

    return SOLICITUD_EXITO;
}

static void enviarRespuestaEnvioMensaje (const t_nodoListaDoble *clienteAProcesar, t_estadoSolicitud estadoSolicitud)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c", estadoSolicitud);
    socket_enviar (cliente->sock, respuesta);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * SOLICITUD_ENVIO_MENSAJE|id del emisor|id del receptor|texto del mensaje
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
 */
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosEnvioMensaje datosEnvioMensaje;
    t_estadoSolicitud estadoSolicitud;

    extrarDatosSolicitudEnvioMensaje (solicitudCliente->solicitud, &datosEnvioMensaje);
    estadoSolicitud = enviarMensaje (contextoServidor, &datosEnvioMensaje);
    enviarRespuestaEnvioMensaje (solicitudCliente->clienteAProcesar, estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES SELECCION CHAT
   ============================================================================================================================================ */


static void extraerDatosSolicitudSeleccionChat (const char *solicitud, t_datosSeleccionChat *returnDatosSeleccionChat)
{
    char tipoSolicitud;
    sscanf (solicitud, "%c|%[^\n]", &tipoSolicitud, returnDatosSeleccionChat->nombreReceptor);
}

static bool sonDatosSeleccionChatInvalidos (const t_datosSeleccionChat *datosSeleccionChat)
{
    return ((strlen (datosSeleccionChat->nombreReceptor) < 3) || (sonTodosEspacios (datosSeleccionChat->nombreReceptor)));
}

static bool usuarioSeleccionadoNoExiste (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosSeleccionChat *datosSeleccionChat, int *returnIdUsuarioDelChatSeleccinado)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosSeleccionChat->nombreReceptor);

    return (!buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, returnIdUsuarioDelChatSeleccinado));
}

static bool usuarioSeleccionoSuPropioChat (int idCliente, int idUsuarioDelChatSeleccionado)
{
    return (idCliente == idUsuarioDelChatSeleccionado);
}

static t_estadoSolicitud seleccionarChat (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosSeleccionChat *datosSeleccionChat, int *returnIdUsuarioDelChatSeleccionado)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);

    if (sonDatosSeleccionChatInvalidos (datosSeleccionChat))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    if (usuarioSeleccionadoNoExiste (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosSeleccionChat, returnIdUsuarioDelChatSeleccionado))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    if (usuarioSeleccionoSuPropioChat (cliente->id, *returnIdUsuarioDelChatSeleccionado))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    return SOLICITUD_EXITO;
}

static void enviarRespuestaSeleccionChat (const t_nodoListaDoble *clienteAProcesar, t_respuestaSeleccionChat *respuestaSeleccionChat)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);
    char respuesta [MAX_BUFFER_RESPUESTA];

    snprintf (respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", respuestaSeleccionChat->estadoSolicitud, respuestaSeleccionChat->idUsuarioDelChatSeleccionado);
    socket_enviar (cliente->sock, respuesta);
    printf ("Respuesta enviada: %s\n\n", respuesta);
}

/*
 * Recibe los datos del usuario que envio la solicitud de la siguiente manera:
 * SOLICITUD_SELECCION_CHAT|nombre del usuario del chat seleccionado
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
 */
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{  
    t_datosSeleccionChat datosSeleccionChat;
    t_respuestaSeleccionChat respuestaSeleccionChat;

    extraerDatosSolicitudSeleccionChat (solicitudCliente->solicitud, &datosSeleccionChat);
    respuestaSeleccionChat.estadoSolicitud = seleccionarChat (contextoServidor, solicitudCliente->clienteAProcesar, &datosSeleccionChat, &(respuestaSeleccionChat.idUsuarioDelChatSeleccionado));
    enviarRespuestaSeleccionChat (solicitudCliente->clienteAProcesar, &respuestaSeleccionChat);
}

