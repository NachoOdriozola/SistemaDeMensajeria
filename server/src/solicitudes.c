#include "../include/solicitudes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente);

static void intentarEnviarRespuestasPendientes (t_contextoServidor *contextoServidor);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void procesarSolicitudes (t_contextoServidor *contextoServidor)
{
    t_solicitudCliente solicitudCliente;
    char headerTipoSolicitud;

    while (noEsColaVacia (&(contextoServidor->solicitudes)))
    {
        desacolar (&(contextoServidor->solicitudes), &solicitudCliente, sizeof (t_solicitudCliente));
        headerTipoSolicitud = *(solicitudCliente.solicitud);
        switch (headerTipoSolicitud)
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
    intentarEnviarRespuestasPendientes (contextoServidor);
}


/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */


static void intentarEnviarRespuestasPendientes (t_contextoServidor *contextoServidor)
{
    t_listaSimple *pl = &(contextoServidor->respuestasPendientes);
    t_respuestaCliente *respuestaPendienteACliente;
    t_resultadoEnvio resultadoEnvio;

    while (*pl != NULL)
    {
        respuestaPendienteACliente = (t_respuestaCliente*)((*pl)->dato);
        resultadoEnvio = intentarEnviarRespuestaPendienteACliente (respuestaPendienteACliente);
        if ((resultadoEnvio == ENVIO_COMPLETO) || (resultadoEnvio == ENVIO_ERROR_CONEXION))
        {
            printf ("\nSe envio respuesta pendiente a cliente: %d\n", respuestaPendienteACliente->clienteAResponder->id);
            eliminarNodoListaSimple (pl, NULL, 0);
        }
        else
            pl = &((*pl)->sig); // Si todavia no se puede enviar la respuesta al cliente por buffer lleno, lo mantiene en la lista hasta que se pueda enviar.
    }
}


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


static void extraerDatosSolicitudAutenticacion (const char *solicitud, t_datosEnvioSolicitudAutenticacion *returnDatosEnvioSolicitudAutenticacion)
{
    memcpy (returnDatosEnvioSolicitudAutenticacion, solicitud, sizeof (t_datosEnvioSolicitudAutenticacion));
}

static bool sonDatosAutenticacionUsuarioInvalidos (const t_datosEnvioSolicitudAutenticacion *datosEnvioSolicitudAutenticacion)
{
    if ((strlen (datosEnvioSolicitudAutenticacion->nombreUsuario) < 3) || (sonTodosEspacios (datosEnvioSolicitudAutenticacion->nombreUsuario)))
        return 1;
    
    if ((strlen (datosEnvioSolicitudAutenticacion->contrasenia) < 8) || (sonTodosEspacios (datosEnvioSolicitudAutenticacion->contrasenia)))
        return 1;

    return 0;
}

static bool usuarioNoExiste (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, const t_datosEnvioSolicitudAutenticacion *datosEnvioSolicitudAutenticacion, int *returnIdUsuario, char *returnContrasenia)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosEnvioSolicitudAutenticacion->nombreUsuario);

    return (!buscarUsuarioPorNombre_recuperarIdYContrasenia (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, &datosBuscarUsuarioPorNombre, returnIdUsuario, returnContrasenia));
}

static bool contraseniaNoCoincide (const t_datosEnvioSolicitudAutenticacion *datosEnvioSolicitudAutenticacion, const char *hashContrasenia)
{
    return (crypto_pwhash_str_verify (hashContrasenia, datosEnvioSolicitudAutenticacion->contrasenia, strlen (datosEnvioSolicitudAutenticacion->contrasenia)));
}

static bool usuarioEstaConectado (t_tablaHash *clientes, int *idUsuario)
{
    return buscarClaveUnicaEnTablaHash (clientes, idUsuario, funcionHash, NULL, 0, cmpIdCliente);
}

static void autenticarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosEnvioSolicitudAutenticacion *datosEnvioSolicitudAutenticacion, t_datosRespuestaSolicitudAutenticacion *returnDatosRespuestaSolicitudAutenticacion)
{
    char hashContrasenia [MAX_CONTRASENIA];

    if ((sonDatosAutenticacionUsuarioInvalidos (datosEnvioSolicitudAutenticacion)) ||
        (usuarioNoExiste (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarIdYContrasenia, datosEnvioSolicitudAutenticacion, &(returnDatosRespuestaSolicitudAutenticacion->idUsuario), hashContrasenia)) ||
        (contraseniaNoCoincide (datosEnvioSolicitudAutenticacion, hashContrasenia)))
    {
        returnDatosRespuestaSolicitudAutenticacion->estadoSolicitud = SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
        returnDatosRespuestaSolicitudAutenticacion->idUsuario = ID_INVALIDO;
        return;
    }

    if (usuarioEstaConectado (&(contextoServidor->clientes), &(returnDatosRespuestaSolicitudAutenticacion->idUsuario)))
    {
        returnDatosRespuestaSolicitudAutenticacion->estadoSolicitud = SOLICITUD_ERROR_OPERACION_INVALIDA;
        returnDatosRespuestaSolicitudAutenticacion->idUsuario = ID_INVALIDO;
        return;
    }
            
    conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, returnDatosRespuestaSolicitudAutenticacion->idUsuario);

    returnDatosRespuestaSolicitudAutenticacion->estadoSolicitud = SOLICITUD_EXITO;
}

static void fabricarRespuestaSolicitudAutenticacion (t_respuestaCliente *respuestaCliente, const t_nodoListaDoble *clienteAResponder, t_datosRespuestaSolicitudAutenticacion *datosRespuestaSolicitudAutenticacion)
{
    t_cliente *cliente = (t_cliente*)(clienteAResponder->dato);

    datosRespuestaSolicitudAutenticacion->header.tipo = RESPUESTA_SOLICITUD_AUTENTICACION;
    datosRespuestaSolicitudAutenticacion->header.bytesTransmitidos = sizeof (t_datosRespuestaSolicitudAutenticacion);

    respuestaCliente->datosAEnviar = (char*)(datosRespuestaSolicitudAutenticacion);
    respuestaCliente->tamDatosAEnviar = sizeof (t_datosRespuestaSolicitudAutenticacion);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura t_datosEnvioSolicitudAutenticacion.
 * 
 * Consultar en la base de datos si las credenciales del usuario existen y son validas.
 * Verificar que el usuario no se encuentre conectado.
 * Si el usuario no se encuentra conectado, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura t_datosRespuestaSolicitudAutenticacion.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso de que el usuario ya se encuentre conectado.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos, el usuario no exista o que la contrasenia sea incorrecta.
 */
static void procesarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosEnvioSolicitudAutenticacion datosEnvioSolicitudAutenticacion;
    t_datosRespuestaSolicitudAutenticacion datosRespuestaSolicitudAutenticacion;
    t_respuestaCliente respuestaCliente;

    extraerDatosSolicitudAutenticacion (solicitudCliente->solicitud, &datosEnvioSolicitudAutenticacion);
    printf ("Solicitud recibida: %c|%s|%s\n", datosEnvioSolicitudAutenticacion.header.tipo, datosEnvioSolicitudAutenticacion.nombreUsuario, datosEnvioSolicitudAutenticacion.contrasenia);
    autenticarCliente (contextoServidor, solicitudCliente->clienteAProcesar, &datosEnvioSolicitudAutenticacion, &datosRespuestaSolicitudAutenticacion);
    fabricarRespuestaSolicitudAutenticacion (&respuestaCliente, solicitudCliente->clienteAProcesar, &datosRespuestaSolicitudAutenticacion);
    if (enviarRespuestaACliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", datosRespuestaSolicitudAutenticacion.header.tipo, datosRespuestaSolicitudAutenticacion.estadoSolicitud, datosRespuestaSolicitudAutenticacion.idUsuario);
}


/* ============================================================================================================================================
   FUNCIONES REGISTRO
   ============================================================================================================================================ */


static void extraerDatosSolicitudRegistro (const char *solicitud, t_datosEnvioSolicitudRegistro *returnDatosEnvioSolicitudRegistro)
{
    memcpy (returnDatosEnvioSolicitudRegistro, solicitud, sizeof (t_datosEnvioSolicitudRegistro));
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

static bool sonDatosRegistroUsuarioInvalidos (const t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro)
{
    if ((strlen (datosEnvioSolicitudRegistro->nombreUsuario) < 3) || sonTodosEspacios (datosEnvioSolicitudRegistro->nombreUsuario))
        return 1;
    
    if ((strlen (datosEnvioSolicitudRegistro->contrasenia) < 8) || sonTodosEspacios (datosEnvioSolicitudRegistro->contrasenia))
        return 1;

    if (esCorreoElectronicoInvalido (datosEnvioSolicitudRegistro->correoElectronico))
        return 1;

    return 0;
}

static nombreYaExistente (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosEnvioSolicitudRegistro->nombreUsuario);

    return (buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, NULL));
}

static correoYaExistente (sqlite3_stmt *sentenciaBuscarUsuarioPorCorreo, const t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro)
{
    t_datosBuscarUsuarioPorCorreo datosBuscarUsuarioPorCorreo;

    strcpy (datosBuscarUsuarioPorCorreo.correoElectronico, datosEnvioSolicitudRegistro->correoElectronico);

    return (buscarUsuarioPorCorreo (sentenciaBuscarUsuarioPorCorreo, &datosBuscarUsuarioPorCorreo));
}

static t_codigoRetorno hashearContrasenia (t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro)
{
    char contraseniaHasheada [crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str (contraseniaHasheada, datosEnvioSolicitudRegistro->contrasenia, strlen (datosEnvioSolicitudRegistro->contrasenia), 3, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0)
        return ERROR_INICIALIZACION;

    strcpy (datosEnvioSolicitudRegistro->contrasenia, contraseniaHasheada);
    
    return EXITO;
}

static void registrarUsuario (sqlite3_stmt *sentenciaInsertarUsuario, const t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro)
{
    t_datosInsertarUsuario datosInsertarUsuario;

    strcpy (datosInsertarUsuario.nombreUsuario, datosEnvioSolicitudRegistro->nombreUsuario);
    strcpy (datosInsertarUsuario.contrasenia, datosEnvioSolicitudRegistro->contrasenia);
    strcpy (datosInsertarUsuario.correoElectronico, datosEnvioSolicitudRegistro->correoElectronico);

    insertarUsuario (sentenciaInsertarUsuario, &datosInsertarUsuario);
}

static void recuperarIdUsuarioRecienRegistrado (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro, int *returnIdUsuario)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosEnvioSolicitudRegistro->nombreUsuario);

    buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, returnIdUsuario);
}

static void registrarCliente (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, t_datosEnvioSolicitudRegistro *datosEnvioSolicitudRegistro, t_datosRespuestaSolicitudRegistro *datosRespuestaSolicitudRegistro)
{
    datosRespuestaSolicitudRegistro->idUsuario = ID_INVALIDO;

    if (sonDatosRegistroUsuarioInvalidos (datosEnvioSolicitudRegistro))
    {
        datosRespuestaSolicitudRegistro->estadoSolicitud = SOLICITUD_ERROR_CREDENCIALES_INVALIDAS;
        return;
    }

    if (nombreYaExistente (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosEnvioSolicitudRegistro))
    {
        datosRespuestaSolicitudRegistro->estadoSolicitud = SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE;
        return;
    }

    if (correoYaExistente (contextoServidor->sentenciasSqlite.buscarUsuarioPorCorreo, datosEnvioSolicitudRegistro))
    {
        datosRespuestaSolicitudRegistro->estadoSolicitud = SOLICITUD_ERROR_CORREO_YA_EXISTENTE;
        return;
    }

    if (hashearContrasenia (datosEnvioSolicitudRegistro) == ERROR_INICIALIZACION)
    {
        datosRespuestaSolicitudRegistro->estadoSolicitud = SOLICITUD_ERROR_SERVIDOR;
        return;
    }

    registrarUsuario (contextoServidor->sentenciasSqlite.insertarUsuario, datosEnvioSolicitudRegistro);
    recuperarIdUsuarioRecienRegistrado (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosEnvioSolicitudRegistro, &(datosRespuestaSolicitudRegistro->idUsuario));
    conectarUsuario (&(contextoServidor->clientes), &(contextoServidor->clientesNoAutenticados), clienteAProcesar, datosRespuestaSolicitudRegistro->idUsuario);

    datosRespuestaSolicitudRegistro->estadoSolicitud = SOLICITUD_EXITO;
}

static void fabricarRespuestaSolicitudRegistro (t_respuestaCliente *respuestaCliente, const t_nodoListaDoble *clienteAResponder, t_datosRespuestaSolicitudRegistro *datosRespuestaSolicitudRegistro)
{
    t_cliente *cliente = (t_cliente*)(clienteAResponder->dato);

    datosRespuestaSolicitudRegistro->header.tipo = RESPUESTA_SOLICITUD_REGISTRO;
    datosRespuestaSolicitudRegistro->header.bytesTransmitidos = sizeof (t_datosRespuestaSolicitudRegistro);

    respuestaCliente->datosAEnviar = (char*)(datosRespuestaSolicitudRegistro);
    respuestaCliente->tamDatosAEnviar = sizeof (t_datosRespuestaSolicitudRegistro);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura t_datosEnvioSolicitudRegistro.
 * 
 * Verificar en la base de datos si ya existe un usuario registrado con el mismo nombre de usuario o correo electronico.
 * Si el usuario se puede registrar, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura t_datosRespuestaSolicitudRegistro.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE|ID invalido #En caso de que el nombre de usuario ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CORREO_YA_EXISTENTE|ID invalido #En caso de que el correo electronico ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_SERVIDOR|ID invalido #En caso de problemas al hashear la contrasenia.
 */
static void procesarSolicitudRegistro (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosEnvioSolicitudRegistro datosEnvioSolicitudRegistro;
    t_datosRespuestaSolicitudRegistro datosRespuestaSolicitudRegistro;
    t_respuestaCliente respuestaCliente;

    extraerDatosSolicitudRegistro (solicitudCliente->solicitud, &datosEnvioSolicitudRegistro);
    printf ("Solicitud recibida: %c|%s|%s|%s\n", datosEnvioSolicitudRegistro.header.tipo, datosEnvioSolicitudRegistro.nombreUsuario, datosEnvioSolicitudRegistro.contrasenia, datosEnvioSolicitudRegistro.correoElectronico);
    registrarCliente (contextoServidor, solicitudCliente->clienteAProcesar, &datosEnvioSolicitudRegistro, &datosRespuestaSolicitudRegistro);
    fabricarRespuestaSolicitudRegistro (&respuestaCliente, solicitudCliente->clienteAProcesar, &datosRespuestaSolicitudRegistro);
    if (enviarRespuestaACliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", datosRespuestaSolicitudRegistro.header.tipo, datosRespuestaSolicitudRegistro.estadoSolicitud, datosRespuestaSolicitudRegistro.idUsuario);
}


/* ============================================================================================================================================
   FUNCIONES ENVIO MENSAJES
   ============================================================================================================================================ */


static void extrarDatosSolicitudEnvioMensaje (const char *solicitud, t_datosEnvioSolicitudEnvioMensaje *returnDatosEnvioSolicitudEnvioMensaje)
{
    memcpy (returnDatosEnvioSolicitudEnvioMensaje, solicitud, sizeof (t_datosEnvioSolicitudEnvioMensaje));
}

static bool sonEmisorOReceptorInvalidos (const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    return ((datosEnvioSolicitudEnvioMensaje->idEmisor == ID_INVALIDO) || (datosEnvioSolicitudEnvioMensaje->idReceptor == ID_INVALIDO));
}

static bool elEmisorEsElReceptor (const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    return (datosEnvioSolicitudEnvioMensaje->idEmisor == datosEnvioSolicitudEnvioMensaje->idReceptor);
}

static bool sonDatosEnvioMensajeInvalidos (const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    return ((*(datosEnvioSolicitudEnvioMensaje->texto) == '\0') || 
                (sonTodosEspacios (datosEnvioSolicitudEnvioMensaje->texto)) ||
                (sonEmisorOReceptorInvalidos (datosEnvioSolicitudEnvioMensaje)) || 
                (elEmisorEsElReceptor (datosEnvioSolicitudEnvioMensaje)));
}

static void almacenarMensaje (sqlite3_stmt *sentenciaInsertarMensaje, const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    t_datosInsertarMensaje datosInsertarMensaje;

    datosInsertarMensaje.idEmisor = datosEnvioSolicitudEnvioMensaje->idEmisor;
    datosInsertarMensaje.idReceptor = datosEnvioSolicitudEnvioMensaje->idReceptor;
    strcpy (datosInsertarMensaje.texto, datosEnvioSolicitudEnvioMensaje->texto);

    insertarMensaje (sentenciaInsertarMensaje, &datosInsertarMensaje);
}

static bool receptorEstaConectado (t_tablaHash *clientes, const int *idReceptor, t_cliente *returnCliente)
{
    return buscarClaveUnicaEnTablaHash (clientes, idReceptor, funcionHash, returnCliente, sizeof (t_cliente), cmpIdCliente);
}

static void fabricarRespuestaRecepcionMensaje (t_respuestaCliente *respuestaCliente, t_cliente *cliente, t_datosRespuestaRecepcionMensaje *datosRespuestaRecepcionMensaje, const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    datosRespuestaRecepcionMensaje->header.tipo = RESPUESTA_RECEPCION_MENSAJE;
    datosRespuestaRecepcionMensaje->header.bytesTransmitidos = sizeof (t_datosRespuestaRecepcionMensaje);

    datosRespuestaRecepcionMensaje->idEmisor = datosEnvioSolicitudEnvioMensaje->idEmisor;
    strcpy (datosRespuestaRecepcionMensaje->texto, datosEnvioSolicitudEnvioMensaje->texto);

    respuestaCliente->datosAEnviar = (char*)(datosRespuestaRecepcionMensaje);
    respuestaCliente->tamDatosAEnviar = sizeof (t_datosRespuestaRecepcionMensaje);
    respuestaCliente->clienteAResponder = cliente;
}

static void enviarMensajeAlReceptor (t_contextoServidor *contextoServidor, t_cliente *cliente, const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje)
{
    t_datosRespuestaRecepcionMensaje datosRespuestaRecepcionMensaje;
    t_respuestaCliente respuestaCliente;

    fabricarRespuestaRecepcionMensaje (&respuestaCliente, cliente, &datosRespuestaRecepcionMensaje, datosEnvioSolicitudEnvioMensaje);

    if (enviarRespuestaACliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%d\n", datosRespuestaRecepcionMensaje.header.tipo, datosRespuestaRecepcionMensaje.idEmisor);
}

static void enviarMensaje (t_contextoServidor *contextoServidor, const t_datosEnvioSolicitudEnvioMensaje *datosEnvioSolicitudEnvioMensaje, t_datosRespuestaSolicitudEnvioMensaje *datosRespuestaSolicitudEnvioMensaje)
{
    t_cliente clienteReceptor;

    if (sonDatosEnvioMensajeInvalidos (datosEnvioSolicitudEnvioMensaje))
    {
        datosRespuestaSolicitudEnvioMensaje->estadoSolicitud = SOLICITUD_ERROR_OPERACION_INVALIDA;
        return;
    }

    almacenarMensaje (contextoServidor->sentenciasSqlite.insertarMensaje, datosEnvioSolicitudEnvioMensaje);
    if (receptorEstaConectado (&(contextoServidor->clientes), &(datosEnvioSolicitudEnvioMensaje->idReceptor), &clienteReceptor))
        enviarMensajeAlReceptor (contextoServidor, &clienteReceptor, datosEnvioSolicitudEnvioMensaje);

    datosRespuestaSolicitudEnvioMensaje->estadoSolicitud = SOLICITUD_EXITO;
}

static void fabricarRespuestaSolicitudEnvioMensaje (t_respuestaCliente *respuestaCliente, const t_nodoListaDoble *clienteAResponder, t_datosRespuestaSolicitudEnvioMensaje *datosRespuestaSolicitudEnvioMensaje)
{
    t_cliente *cliente = (t_cliente*)(clienteAResponder->dato);

    datosRespuestaSolicitudEnvioMensaje->header.tipo = RESPUESTA_SOLICITUD_ENVIO_MENSAJE;
    datosRespuestaSolicitudEnvioMensaje->header.bytesTransmitidos = sizeof (t_datosRespuestaSolicitudEnvioMensaje);

    respuestaCliente->datosAEnviar = (char*)(datosRespuestaSolicitudEnvioMensaje);
    respuestaCliente->tamDatosAEnviar = sizeof (t_datosRespuestaSolicitudEnvioMensaje);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura t_datosEnvioSolicitudEnvioMensaje.
 * 
 * Antes de enviar el mensaje, verifica que el ID del emisor o del receptor sean validos y que no sean los mismos.
 * El mensaje es almacenado en la base de datos antes de ser reenviado al receptor.
 * Si el receptor se encuentra conectado, le reenvia el mensaje con una cadena compuesta de la siguiente manera:
 * tipo respuesta mensaje|id del emisor|texto del mensaje
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura t_datosRespuestaSolicitudEnvioMensaje.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_EXITO #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_ERROR_OPERACION_INVALIDA #En caso que sean datos de envio de mensaje invalidos o que el emisor sea el receptor.
 */
static void procesarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{
    t_datosEnvioSolicitudEnvioMensaje datosEnvioSolicitudEnvioMensaje;
    t_datosRespuestaSolicitudEnvioMensaje datosRespuestaSolicitudEnvioMensaje;
    t_respuestaCliente respuestaCliente;

    extrarDatosSolicitudEnvioMensaje (solicitudCliente->solicitud, &datosEnvioSolicitudEnvioMensaje);
    printf("Solicitud recibida: %c|%d|%d|%s\n", datosEnvioSolicitudEnvioMensaje.header.tipo, datosEnvioSolicitudEnvioMensaje.idEmisor, datosEnvioSolicitudEnvioMensaje.idReceptor, datosEnvioSolicitudEnvioMensaje.texto);
    enviarMensaje (contextoServidor, &datosEnvioSolicitudEnvioMensaje, &datosRespuestaSolicitudEnvioMensaje);
    fabricarRespuestaSolicitudEnvioMensaje (&respuestaCliente, solicitudCliente->clienteAProcesar, &datosRespuestaSolicitudEnvioMensaje);
    if (enviarRespuestaACliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c\n\n", datosRespuestaSolicitudEnvioMensaje.header.tipo, datosRespuestaSolicitudEnvioMensaje.estadoSolicitud);
}


/* ============================================================================================================================================
   FUNCIONES SELECCION CHAT
   ============================================================================================================================================ */


static void extraerDatosSolicitudSeleccionChat (const char *solicitud, t_datosEnvioSolicitudSeleccionChat *returnDatosEnvioSolicitudSeleccionChat)
{
    memcpy (returnDatosEnvioSolicitudSeleccionChat, solicitud, sizeof (t_datosEnvioSolicitudSeleccionChat));
}

static bool sonDatosSeleccionChatInvalidos (const t_datosEnvioSolicitudSeleccionChat *datosEnvioSolicitudSeleccionChat)
{
    return ((strlen (datosEnvioSolicitudSeleccionChat->nombreUsuarioChatSeleccionado) < 3) || (sonTodosEspacios (datosEnvioSolicitudSeleccionChat->nombreUsuarioChatSeleccionado)));
}

static bool usuarioSeleccionadoNoExiste (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosEnvioSolicitudSeleccionChat *datosEnvioSolicitudSeleccionChat, int *returnIdUsuarioDelChatSeleccinado)
{
    t_datosBuscarUsuarioPorNombre datosBuscarUsuarioPorNombre;

    strcpy (datosBuscarUsuarioPorNombre.nombreUsuario, datosEnvioSolicitudSeleccionChat->nombreUsuarioChatSeleccionado);

    return (!buscarUsuarioPorNombre_recuperarId (sentenciaBuscarUsuarioPorNombre_recuperarId, &datosBuscarUsuarioPorNombre, returnIdUsuarioDelChatSeleccinado));
}

static bool usuarioSeleccionoSuPropioChat (int idCliente, int idUsuarioDelChatSeleccionado)
{
    return (idCliente == idUsuarioDelChatSeleccionado);
}

static void seleccionarChat (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const t_datosEnvioSolicitudSeleccionChat *datosEnvioSolicitudSeleccionChat, t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    t_cliente *cliente = (t_cliente*)(clienteAProcesar->dato);

    if ((sonDatosSeleccionChatInvalidos (datosEnvioSolicitudSeleccionChat)) ||
        (usuarioSeleccionadoNoExiste (contextoServidor->sentenciasSqlite.buscarUsuarioPorNombre_recuperarId, datosEnvioSolicitudSeleccionChat, &(datosRespuestaSolicitudSeleccionChat->idUsuarioDelChatSeleccionado))) ||
        (usuarioSeleccionoSuPropioChat (cliente->id, datosRespuestaSolicitudSeleccionChat->idUsuarioDelChatSeleccionado)))
    {
        datosRespuestaSolicitudSeleccionChat->estadoSolicitud = SOLICITUD_ERROR_OPERACION_INVALIDA;
        datosRespuestaSolicitudSeleccionChat->idUsuarioDelChatSeleccionado = ID_INVALIDO;
        return;
    }

    datosRespuestaSolicitudSeleccionChat->estadoSolicitud = SOLICITUD_EXITO;
}

static void fabricarRespuestaSolicitudSeleccionChat (t_respuestaCliente *respuestaCliente, const t_nodoListaDoble *clienteAResponder, t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    t_cliente *cliente = (t_cliente*)(clienteAResponder->dato);

    datosRespuestaSolicitudSeleccionChat->header.tipo = RESPUESTA_SOLICITUD_SELECCION_CHAT;
    datosRespuestaSolicitudSeleccionChat->header.bytesTransmitidos = sizeof (t_datosRespuestaSolicitudSeleccionChat);

    respuestaCliente->datosAEnviar = (char*)(datosRespuestaSolicitudSeleccionChat);
    respuestaCliente->tamDatosAEnviar = sizeof (t_datosRespuestaSolicitudSeleccionChat);
    respuestaCliente->clienteAResponder = cliente;
}

/*
 * Recibe los datos del usuario que envio la solicitud con la estructura t_datosEnvioSolicitudSeleccionChat.
 *
 * Verificar que el usuario seleccionado existe.
 * Verificar que el usuario no haya seleccionado su propio chat.
 *
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura t_datosRespuestaSolicitudSeleccionChat.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_EXITO|ID del usuario del chat seleccionado #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso que sean datos de seleccion de chat invalidos, que el usuario seleccionado no exista o que el usuario selecciono su propio chat.
 */
static void procesarSolicitudSeleccionChat (t_contextoServidor *contextoServidor, t_solicitudCliente *solicitudCliente)
{  
    t_datosEnvioSolicitudSeleccionChat datosEnvioSolicitudSeleccionChat;
    t_datosRespuestaSolicitudSeleccionChat datosRespuestaSolicitudSeleccionChat;
    t_respuestaCliente respuestaCliente;

    extraerDatosSolicitudSeleccionChat (solicitudCliente->solicitud, &datosEnvioSolicitudSeleccionChat);
    printf ("Solicitud recibida: %c|%s\n", datosEnvioSolicitudSeleccionChat.header.tipo, datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado);
    seleccionarChat (contextoServidor, solicitudCliente->clienteAProcesar, &datosEnvioSolicitudSeleccionChat, &datosRespuestaSolicitudSeleccionChat);
    fabricarRespuestaSolicitudSeleccionChat (&respuestaCliente, solicitudCliente->clienteAProcesar, &datosRespuestaSolicitudSeleccionChat);
    if (enviarRespuestaACliente (contextoServidor, &respuestaCliente) == ENVIO_COMPLETO)
        printf ("Respuesta enviada: %c|%c|%d\n\n", datosRespuestaSolicitudSeleccionChat.header.tipo, datosRespuestaSolicitudSeleccionChat.estadoSolicitud, datosRespuestaSolicitudSeleccionChat.idUsuarioDelChatSeleccionado);
}

