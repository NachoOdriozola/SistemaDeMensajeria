#include "servidor/solicitudes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_solicitud_autenticacion (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente);
static void procesar_solicitud_registro (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente);
static void procesar_solicitud_envio_mensaje (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente);
static void procesar_solicitud_seleccion_chat (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente);

static void intentar_enviar_respuestas_pendientes (ContextoServidor *contextoServidor);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void procesar_solicitudes (ContextoServidor *contextoServidor)
{
    SolicitudCliente solicitudCliente;
    char headerTipoSolicitud;

    while (cola_no_esta_vacia (&(contextoServidor->solicitudes)))
    {
        cola_sacar (&(contextoServidor->solicitudes), &solicitudCliente, sizeof (SolicitudCliente));
        headerTipoSolicitud = *(solicitudCliente.solicitud);
        switch (headerTipoSolicitud)
        {
            case SOLICITUD_AUTENTICACION:
                procesar_solicitud_autenticacion (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_REGISTRO:
                procesar_solicitud_registro (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_ENVIO_MENSAJE:
                procesar_solicitud_envio_mensaje (contextoServidor, &solicitudCliente);
                break;
    
            case SOLICITUD_SELECCION_CHAT:
                procesar_solicitud_seleccion_chat (contextoServidor, &solicitudCliente);
                break;
    
            default:
                break;
        }
    }
    intentar_enviar_respuestas_pendientes (contextoServidor);
}


/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */


static void intentar_enviar_respuestas_pendientes (ContextoServidor *contextoServidor)
{
    ListaSimple *pl = &(contextoServidor->respuestasPendientes);
    RespuestaCliente *respuestaPendienteCliente;
    ResultadoEnvio resultadoEnvio;

    while (*pl != NULL)
    {
        respuestaPendienteCliente = (RespuestaCliente*)((*pl)->dato);
        resultadoEnvio = intentar_enviar_respuesta_pendiente_cliente (respuestaPendienteCliente);
        if ((resultadoEnvio == ENVIO_COMPLETO) || (resultadoEnvio == ENVIO_ERROR_CONEXION))
        {
            printf ("\nSe envio respuesta pendiente a cliente: %d\n", respuestaPendienteCliente->clienteAResponder->id);
            lista_simple_eliminar_nodo (pl, NULL, 0);
        }
        else
            pl = &((*pl)->sig); // Si todavia no se puede enviar la respuesta al cliente por buffer lleno, lo mantiene en la lista hasta que se pueda enviar.
    }
}


static void conectar_usuario (TablaHash *clientes, ListaDoble *clientesNoAutenticados, NodoListaDoble *clienteAProcesar, int idUsuario)
{
    Cliente *cliente = (Cliente*)(clienteAProcesar->dato);
    
    cliente->id = idUsuario;
    
    // Mover el cliente de la lista simple de clientes no autenticados a la tabla hash de clientes autenticados.
    lista_doble_desvincular_nodo (clientesNoAutenticados, clienteAProcesar);
    tabla_hash_vincular_nodo (clientes, &(cliente->id), aplicar_hash_id_cliente, clienteAProcesar);
}

static bool son_todos_espacios (const char *mensaje)
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


static void extraer_solicitud_autenticacion (const char *solicitud, SolicitudAutenticacion *returnSolicitudAutenticacion)
{
    memcpy (returnSolicitudAutenticacion, solicitud, sizeof (SolicitudAutenticacion));
}

static bool son_datos_autenticacion_invalidos (const SolicitudAutenticacion *solicitudAutenticacion)
{
    if ((strlen (solicitudAutenticacion->nombreUsuario) < 3) || (son_todos_espacios (solicitudAutenticacion->nombreUsuario)))
        return 1;
    
    if ((strlen (solicitudAutenticacion->contrasenia) < 8) || (son_todos_espacios (solicitudAutenticacion->contrasenia)))
        return 1;

    return 0;
}

static bool usuario_no_existe (sqlite3_stmt *sentenciaBuscarIdYContraseniaPorNombre, const SolicitudAutenticacion *solicitudAutenticacion, int *returnIdUsuario, char *returnContrasenia)
{
    ParametrosBuscarUsuarioPorNombre parametrosBuscarUsuarioPorNombre;

    strcpy (parametrosBuscarUsuarioPorNombre.nombreUsuario, solicitudAutenticacion->nombreUsuario);

    return (!bd_buscar_id_y_contrasenia_por_nombre (sentenciaBuscarIdYContraseniaPorNombre, &parametrosBuscarUsuarioPorNombre, returnIdUsuario, returnContrasenia));
}

static bool contrasenia_no_coincide (const SolicitudAutenticacion *solicitudAutenticacion, const char *hashContrasenia)
{
    return (crypto_pwhash_str_verify (hashContrasenia, solicitudAutenticacion->contrasenia, strlen (solicitudAutenticacion->contrasenia)));
}

static bool usuario_esta_conectado (TablaHash *clientes, int *idUsuario)
{
    return tabla_hash_buscar_clave_unica (clientes, idUsuario, aplicar_hash_id_cliente, NULL, 0, cmp_id_cliente);
}

static void autenticar_cliente (ContextoServidor *contextoServidor, NodoListaDoble *clienteAProcesar, const SolicitudAutenticacion *solicitudAutenticacion, RespuestaAutenticacion *returnRespuestaAutenticacion)
{
    char hashContrasenia [MAX_CONTRASENIA];

    if ((son_datos_autenticacion_invalidos (solicitudAutenticacion)) ||
        (usuario_no_existe (contextoServidor->sentenciasSqlite.buscarIdYContraseniaPorNombre, solicitudAutenticacion, &(returnRespuestaAutenticacion->idUsuario), hashContrasenia)) ||
        (contrasenia_no_coincide (solicitudAutenticacion, hashContrasenia)))
    {
        returnRespuestaAutenticacion->estado = SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
        returnRespuestaAutenticacion->idUsuario = ID_INVALIDO;
        return;
    }

    if (usuario_esta_conectado (&(contextoServidor->clientes), &(returnRespuestaAutenticacion->idUsuario)))
    {
        returnRespuestaAutenticacion->estado = SOLICITUD_ERROR_OPERACION_INVALIDA;
        returnRespuestaAutenticacion->idUsuario = ID_INVALIDO;
        return;
    }
            
    conectar_usuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, returnRespuestaAutenticacion->idUsuario);

    returnRespuestaAutenticacion->estado = SOLICITUD_EXITO;
}

static void fabricar_respuesta_autenticacion (RespuestaCliente *respuestaCliente, const NodoListaDoble *clienteAResponder, RespuestaAutenticacion *respuestaAutenticacion)
{
    Cliente *cliente = (Cliente*)(clienteAResponder->dato);

    respuestaAutenticacion->header.tipoPaquete = RESPUESTA_SOLICITUD_AUTENTICACION;
    respuestaAutenticacion->header.bytesTransmitidos = sizeof (RespuestaAutenticacion);

    respuestaCliente->datosAEnviar = (char*)(respuestaAutenticacion);
    respuestaCliente->tamDatosAEnviar = sizeof (RespuestaAutenticacion);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudAutenticacion.
 * 
 * Consultar en la base de datos si las credenciales del usuario existen y son validas.
 * Verificar que el usuario no se encuentre conectado.
 * Si el usuario no se encuentra conectado, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaAutenticacion.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso de que el usuario ya se encuentre conectado.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos, el usuario no exista o que la contrasenia sea incorrecta.
 */
static void procesar_solicitud_autenticacion (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente)
{
    SolicitudAutenticacion solicitudAutenticacion;
    RespuestaAutenticacion respuestaAutenticacion;
    RespuestaCliente respuestaCliente;

    extraer_solicitud_autenticacion (solicitudCliente->solicitud, &solicitudAutenticacion);
    printf ("Solicitud recibida: %c|%s|%s\n", solicitudAutenticacion.header.tipoPaquete, solicitudAutenticacion.nombreUsuario, solicitudAutenticacion.contrasenia);
    autenticar_cliente (contextoServidor, solicitudCliente->clienteAProcesar, &solicitudAutenticacion, &respuestaAutenticacion);
    fabricar_respuesta_autenticacion (&respuestaCliente, solicitudCliente->clienteAProcesar, &respuestaAutenticacion);
    if (enviar_respuesta_cliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", respuestaAutenticacion.header.tipoPaquete, respuestaAutenticacion.estado, respuestaAutenticacion.idUsuario);
}


/* ============================================================================================================================================
   FUNCIONES REGISTRO
   ============================================================================================================================================ */


static void extraer_solicitud_registro (const char *solicitud, SolicitudRegistro *returnSolicitudRegistro)
{
    memcpy (returnSolicitudRegistro, solicitud, sizeof (SolicitudRegistro));
}

static bool es_correo_electronico_invalido (const char *correoElectronico)
{
    char *ptr = strchr (correoElectronico, '@'); // Se posiciona en el @

    if ((ptr == NULL) ||                                // Si no tiene @
        (ptr == correoElectronico) ||            // O empieza con @
        (strchr (ptr, '.') == NULL) ||               // O no tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL))         // O tiene 2 arrobas
        return 1;

    return 0;
}

static bool son_datos_registro_invalidos (const SolicitudRegistro *solicitudRegistro)
{
    if ((strlen (solicitudRegistro->nombreUsuario) < 3) || son_todos_espacios (solicitudRegistro->nombreUsuario))
        return 1;
    
    if ((strlen (solicitudRegistro->contrasenia) < 8) || son_todos_espacios (solicitudRegistro->contrasenia))
        return 1;

    if (es_correo_electronico_invalido (solicitudRegistro->correoElectronico))
        return 1;

    return 0;
}

static bool nombre_ya_existe (sqlite3_stmt *sentenciaBuscarIdPorNombre, const SolicitudRegistro *solicitudRegistro)
{
    ParametrosBuscarUsuarioPorNombre parametrosBuscarUsuarioPorNombre;

    strcpy (parametrosBuscarUsuarioPorNombre.nombreUsuario, solicitudRegistro->nombreUsuario);

    return (bd_buscar_id_por_nombre (sentenciaBuscarIdPorNombre, &parametrosBuscarUsuarioPorNombre, NULL));
}

static bool correo_ya_existe (sqlite3_stmt *sentenciaBuscarIdPorCorreo, const SolicitudRegistro *solicitudRegistro)
{
    ParametrosBuscarUsuarioPorCorreo parametrosBuscarUsuarioPorCorreo;

    strcpy (parametrosBuscarUsuarioPorCorreo.correoElectronico, solicitudRegistro->correoElectronico);

    return (bd_existe_usuario_con_correo (sentenciaBuscarIdPorCorreo, &parametrosBuscarUsuarioPorCorreo));
}

static CodigoRetorno hashear_contrasenia (SolicitudRegistro *solicitudRegistro)
{
    char contraseniaHasheada [crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str (contraseniaHasheada, solicitudRegistro->contrasenia, strlen (solicitudRegistro->contrasenia), 3, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0)
        return ERROR_INICIALIZACION;

    strcpy (solicitudRegistro->contrasenia, contraseniaHasheada);
    
    return EXITO;
}

static void insertar_usuario (sqlite3_stmt *sentenciaInsertarUsuario, const SolicitudRegistro *solicitudRegistro)
{
    ParametrosInsertarUsuario parametrosInsertarUsuario;

    strcpy (parametrosInsertarUsuario.nombreUsuario, solicitudRegistro->nombreUsuario);
    strcpy (parametrosInsertarUsuario.contrasenia, solicitudRegistro->contrasenia);
    strcpy (parametrosInsertarUsuario.correoElectronico, solicitudRegistro->correoElectronico);

    bd_insertar_usuario (sentenciaInsertarUsuario, &parametrosInsertarUsuario);
}

static void recuperar_id_usuario_registrado (sqlite3_stmt *sentenciaBuscarIdPorNombre, const SolicitudRegistro *solicitudRegistro, int *returnIdUsuario)
{
    ParametrosBuscarUsuarioPorNombre parametrosBuscarUsuarioPorNombre;

    strcpy (parametrosBuscarUsuarioPorNombre.nombreUsuario, solicitudRegistro->nombreUsuario);

    bd_buscar_id_por_nombre (sentenciaBuscarIdPorNombre, &parametrosBuscarUsuarioPorNombre, returnIdUsuario);
}

static void registrar_usuario (ContextoServidor *contextoServidor, NodoListaDoble *clienteAProcesar, SolicitudRegistro *solicitudRegistro, RespuestaRegistro *returnRespuestaRegistro)
{
    returnRespuestaRegistro->idUsuario = ID_INVALIDO;

    if (son_datos_registro_invalidos (solicitudRegistro))
    {
        returnRespuestaRegistro->estado = SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
        return;
    }

    if (nombre_ya_existe (contextoServidor->sentenciasSqlite.buscarIdPorNombre, solicitudRegistro))
    {
        returnRespuestaRegistro->estado = SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE;
        return;
    }

    if (correo_ya_existe (contextoServidor->sentenciasSqlite.buscarIdPorCorreo, solicitudRegistro))
    {
        returnRespuestaRegistro->estado = SOLICITUD_ERROR_CORREO_YA_EXISTENTE;
        return;
    }

    if (hashear_contrasenia (solicitudRegistro) == ERROR_INICIALIZACION)
    {
        returnRespuestaRegistro->estado = SOLICITUD_ERROR_SERVIDOR;
        return;
    }

    insertar_usuario (contextoServidor->sentenciasSqlite.insertarUsuario, solicitudRegistro);
    recuperar_id_usuario_registrado (contextoServidor->sentenciasSqlite.buscarIdPorNombre, solicitudRegistro, &(returnRespuestaRegistro->idUsuario));
    conectar_usuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, returnRespuestaRegistro->idUsuario);

    returnRespuestaRegistro->estado = SOLICITUD_EXITO;
}

static void fabricar_respuesta_registro (RespuestaCliente *respuestaCliente, const NodoListaDoble *clienteAResponder, RespuestaRegistro *respuestaRegistro)
{
    Cliente *cliente = (Cliente*)(clienteAResponder->dato);

    respuestaRegistro->header.tipoPaquete = RESPUESTA_SOLICITUD_REGISTRO;
    respuestaRegistro->header.bytesTransmitidos = sizeof (RespuestaRegistro);

    respuestaCliente->datosAEnviar = (char*)(respuestaRegistro);
    respuestaCliente->tamDatosAEnviar = sizeof (RespuestaRegistro);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudRegistro.
 * 
 * Verificar en la base de datos si ya existe un usuario registrado con el mismo nombre de usuario o correo electronico.
 * Si el usuario se puede registrar, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaRegistro.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE|ID invalido #En caso de que el nombre de usuario ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CORREO_YA_EXISTENTE|ID invalido #En caso de que el correo electronico ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_SERVIDOR|ID invalido #En caso de problemas al hashear la contrasenia.
 */
static void procesar_solicitud_registro (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente)
{
    SolicitudRegistro solicitudRegistro;
    RespuestaRegistro respuestaRegistro;
    RespuestaCliente respuestaCliente;

    extraer_solicitud_registro (solicitudCliente->solicitud, &solicitudRegistro);
    printf ("Solicitud recibida: %c|%s|%s|%s\n", solicitudRegistro.header.tipoPaquete, solicitudRegistro.nombreUsuario, solicitudRegistro.contrasenia, solicitudRegistro.correoElectronico);
    registrar_usuario (contextoServidor, solicitudCliente->clienteAProcesar, &solicitudRegistro, &respuestaRegistro);
    fabricar_respuesta_registro (&respuestaCliente, solicitudCliente->clienteAProcesar, &respuestaRegistro);
    if (enviar_respuesta_cliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", respuestaRegistro.header.tipoPaquete, respuestaRegistro.estado, respuestaRegistro.idUsuario);
}


/* ============================================================================================================================================
   FUNCIONES ENVIO MENSAJES
   ============================================================================================================================================ */


static void extrar_solicitud_envio_mensaje (const char *solicitud, SolicitudEnvioMensaje *returnSolicitudEnvioMensaje)
{
    memcpy (returnSolicitudEnvioMensaje, solicitud, sizeof (SolicitudEnvioMensaje));
}

static bool son_emisor_o_receptor_invalidos (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return ((solicitudEnvioMensaje->idEmisor == ID_INVALIDO) || (solicitudEnvioMensaje->idReceptor == ID_INVALIDO));
}

static bool emisor_es_receptor (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return (solicitudEnvioMensaje->idEmisor == solicitudEnvioMensaje->idReceptor);
}

static bool son_datos_envio_mensaje_invalidos (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return ((*(solicitudEnvioMensaje->texto) == '\0') || 
                (son_todos_espacios (solicitudEnvioMensaje->texto)) ||
                (son_emisor_o_receptor_invalidos (solicitudEnvioMensaje)) || 
                (emisor_es_receptor (solicitudEnvioMensaje)));
}

static void insertar_mensaje (sqlite3_stmt *sentenciaInsertarMensaje, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    ParametrosInsertarMensaje parametrosInsertarMensaje;

    parametrosInsertarMensaje.idEmisor = solicitudEnvioMensaje->idEmisor;
    parametrosInsertarMensaje.idReceptor = solicitudEnvioMensaje->idReceptor;
    strcpy (parametrosInsertarMensaje.texto, solicitudEnvioMensaje->texto);

    bd_insertar_mensaje (sentenciaInsertarMensaje, &parametrosInsertarMensaje);
}

static bool receptor_esta_conectado (TablaHash *clientes, const int *idReceptor, Cliente *returnCliente)
{
    return tabla_hash_buscar_clave_unica (clientes, idReceptor, aplicar_hash_id_cliente, returnCliente, sizeof (Cliente), cmp_id_cliente);
}

static void fabricar_respuesta_recepcion_mensaje (RespuestaCliente *respuestaCliente, Cliente *cliente, RespuestaRecepcionMensaje *respuestaRecepcionMensaje, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    respuestaRecepcionMensaje->header.tipoPaquete = RESPUESTA_RECEPCION_MENSAJE;
    respuestaRecepcionMensaje->header.bytesTransmitidos = sizeof (RespuestaRecepcionMensaje);

    respuestaRecepcionMensaje->idEmisor = solicitudEnvioMensaje->idEmisor;
    strcpy (respuestaRecepcionMensaje->texto, solicitudEnvioMensaje->texto);

    respuestaCliente->datosAEnviar = (char*)(respuestaRecepcionMensaje);
    respuestaCliente->tamDatosAEnviar = sizeof (RespuestaRecepcionMensaje);
    respuestaCliente->clienteAResponder = cliente;
}

static void enviar_mensaje_receptor (ContextoServidor *contextoServidor, Cliente *cliente, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    RespuestaRecepcionMensaje respuestaRecepcionMensaje;
    RespuestaCliente respuestaCliente;

    fabricar_respuesta_recepcion_mensaje (&respuestaCliente, cliente, &respuestaRecepcionMensaje, solicitudEnvioMensaje);

    if (enviar_respuesta_cliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%d\n", respuestaRecepcionMensaje.header.tipoPaquete, respuestaRecepcionMensaje.idEmisor, respuestaRecepcionMensaje.texto);
}

static void enviar_mensaje (ContextoServidor *contextoServidor, const SolicitudEnvioMensaje *solicitudEnvioMensaje, RespuestaEnvioMensaje *returnRespuestaEnvioMensaje)
{
    Cliente clienteReceptor;

    if (son_datos_envio_mensaje_invalidos (solicitudEnvioMensaje))
    {
        returnRespuestaEnvioMensaje->estado = SOLICITUD_ERROR_OPERACION_INVALIDA;
        return;
    }

    insertar_mensaje (contextoServidor->sentenciasSqlite.insertarMensaje, solicitudEnvioMensaje);
    if (receptor_esta_conectado (&(contextoServidor->clientes), &(solicitudEnvioMensaje->idReceptor), &clienteReceptor))
        enviar_mensaje_receptor (contextoServidor, &clienteReceptor, solicitudEnvioMensaje);

    returnRespuestaEnvioMensaje->estado = SOLICITUD_EXITO;
}

static void fabricar_respuesta_envio_mensaje (RespuestaCliente *respuestaCliente, const NodoListaDoble *clienteAResponder, RespuestaEnvioMensaje *respuestaEnvioMensaje)
{
    Cliente *cliente = (Cliente*)(clienteAResponder->dato);

    respuestaEnvioMensaje->header.tipoPaquete = RESPUESTA_SOLICITUD_ENVIO_MENSAJE;
    respuestaEnvioMensaje->header.bytesTransmitidos = sizeof (RespuestaEnvioMensaje);

    respuestaCliente->datosAEnviar = (char*)(respuestaEnvioMensaje);
    respuestaCliente->tamDatosAEnviar = sizeof (RespuestaEnvioMensaje);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudEnvioMensaje.
 * 
 * Antes de enviar el mensaje, verifica que el ID del emisor o del receptor sean validos y que no sean los mismos.
 * El mensaje es almacenado en la base de datos antes de ser reenviado al receptor.
 * Si el receptor se encuentra conectado, le reenvia el mensaje con una cadena compuesta de la siguiente manera:
 * tipo respuesta mensaje|id del emisor|texto del mensaje
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaEnvioMensaje.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_EXITO #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_ERROR_OPERACION_INVALIDA #En caso que sean datos de envio de mensaje invalidos o que el emisor sea el receptor.
 */
static void procesar_solicitud_envio_mensaje (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente)
{
    SolicitudEnvioMensaje solicitudEnvioMensaje;
    RespuestaEnvioMensaje respuestaEnvioMensaje;
    RespuestaCliente respuestaCliente;

    extrar_solicitud_envio_mensaje (solicitudCliente->solicitud, &solicitudEnvioMensaje);
    printf("Solicitud recibida: %c|%d|%d|%s\n", solicitudEnvioMensaje.header.tipoPaquete, solicitudEnvioMensaje.idEmisor, solicitudEnvioMensaje.idReceptor, solicitudEnvioMensaje.texto);
    enviar_mensaje (contextoServidor, &solicitudEnvioMensaje, &respuestaEnvioMensaje);
    fabricar_respuesta_envio_mensaje (&respuestaCliente, solicitudCliente->clienteAProcesar, &respuestaEnvioMensaje);
    if (enviar_respuesta_cliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c\n\n", respuestaEnvioMensaje.header.tipoPaquete, respuestaEnvioMensaje.estado);
}


/* ============================================================================================================================================
   FUNCIONES SELECCION CHAT
   ============================================================================================================================================ */


static void extraer_solicitud_seleccion_chat (const char *solicitud, SolicitudSeleccionChat *returnSolicitudSeleccionChat)
{
    memcpy (returnSolicitudSeleccionChat, solicitud, sizeof (SolicitudSeleccionChat));
}

static bool son_datos_seleccion_chat_invalidos (const SolicitudSeleccionChat *solicitudSeleccionChat)
{
    return ((strlen (solicitudSeleccionChat->nombreUsuarioChatSeleccionado) < 3) || (son_todos_espacios (solicitudSeleccionChat->nombreUsuarioChatSeleccionado)));
}

static bool usuario_seleccionado_no_existe (sqlite3_stmt *sentenciaBuscarIdPorNombre, const SolicitudSeleccionChat *solicitudSeleccionChat, int *returnIdUsuarioChatSeleccinado)
{
    ParametrosBuscarUsuarioPorNombre parametrosBuscarUsuarioPorNombre;

    strcpy (parametrosBuscarUsuarioPorNombre.nombreUsuario, solicitudSeleccionChat->nombreUsuarioChatSeleccionado);

    return (!bd_buscar_id_por_nombre (sentenciaBuscarIdPorNombre, &parametrosBuscarUsuarioPorNombre, returnIdUsuarioChatSeleccinado));
}

static bool usuario_selecciono_su_propio_chat (int idCliente, int idUsuarioChatSeleccionado)
{
    return (idCliente == idUsuarioChatSeleccionado);
}

static void seleccionar_chat (ContextoServidor *contextoServidor, NodoListaDoble *clienteAProcesar, const SolicitudSeleccionChat *solicitudSeleccionChat, RespuestaSeleccionChat *returnRespuestaSeleccionChat)
{
    Cliente *cliente = (Cliente*)(clienteAProcesar->dato);

    if ((son_datos_seleccion_chat_invalidos (solicitudSeleccionChat)) ||
        (usuario_seleccionado_no_existe (contextoServidor->sentenciasSqlite.buscarIdPorNombre, solicitudSeleccionChat, &(returnRespuestaSeleccionChat->idUsuarioChatSeleccionado))) ||
        (usuario_selecciono_su_propio_chat (cliente->id, returnRespuestaSeleccionChat->idUsuarioChatSeleccionado)))
    {
        returnRespuestaSeleccionChat->estado = SOLICITUD_ERROR_OPERACION_INVALIDA;
        returnRespuestaSeleccionChat->idUsuarioChatSeleccionado = ID_INVALIDO;
        return;
    }

    returnRespuestaSeleccionChat->estado = SOLICITUD_EXITO;
}

static void fabricar_respuesta_seleccion_chat (RespuestaCliente *respuestaCliente, const NodoListaDoble *clienteAResponder, RespuestaSeleccionChat *respuestaSeleccionChat)
{
    Cliente *cliente = (Cliente*)(clienteAResponder->dato);

    respuestaSeleccionChat->header.tipoPaquete = RESPUESTA_SOLICITUD_SELECCION_CHAT;
    respuestaSeleccionChat->header.bytesTransmitidos = sizeof (RespuestaSeleccionChat);

    respuestaCliente->datosAEnviar = (char*)(respuestaSeleccionChat);
    respuestaCliente->tamDatosAEnviar = sizeof (RespuestaSeleccionChat);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudSeleccionChat.
 *
 * Verificar que el usuario seleccionado existe.
 * Verificar que el usuario no haya seleccionado su propio chat.
 *
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaSeleccionChat.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_EXITO|ID del usuario del chat seleccionado #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso que sean datos de seleccion de chat invalidos, que el usuario seleccionado no exista o que el usuario selecciono su propio chat.
 */
static void procesar_solicitud_seleccion_chat (ContextoServidor *contextoServidor, SolicitudCliente *solicitudCliente)
{  
    SolicitudSeleccionChat solicitudSeleccionChat;
    RespuestaSeleccionChat respuestaSeleccionChat;
    RespuestaCliente respuestaCliente;

    extraer_solicitud_seleccion_chat (solicitudCliente->solicitud, &solicitudSeleccionChat);
    printf ("Solicitud recibida: %c|%s\n", solicitudSeleccionChat.header.tipoPaquete, solicitudSeleccionChat.nombreUsuarioChatSeleccionado);
    seleccionar_chat (contextoServidor, solicitudCliente->clienteAProcesar, &solicitudSeleccionChat, &respuestaSeleccionChat);
    fabricar_respuesta_seleccion_chat (&respuestaCliente, solicitudCliente->clienteAProcesar, &respuestaSeleccionChat);
    if (enviar_respuesta_cliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", respuestaSeleccionChat.header.tipoPaquete, respuestaSeleccionChat.estado, respuestaSeleccionChat.idUsuarioChatSeleccionado);
}

