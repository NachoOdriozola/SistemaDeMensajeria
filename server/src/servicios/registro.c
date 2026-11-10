#include "servicios/registro.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_registro_invalido (const SolicitudRegistro *solicitudRegistro);
static ResultadoBd nombre_ya_existe (Bd *bd, const SolicitudRegistro *solicitudRegistro);
static ResultadoBd correo_ya_existe (Bd *bd, const SolicitudRegistro *solicitudRegistro);
static CodigoRetorno hashear_contrasenia (SolicitudRegistro *solicitudRegistro);
static ResultadoBd insertar_usuario (Bd *bd, const SolicitudRegistro *solicitudRegistro);
static ResultadoBd recuperar_id (Bd *bd, const SolicitudRegistro *solicitudRegistro, int *returnIdUsuario);
static CodigoRetorno conectar_usuario (RegistroClientes *registroClientes, Cliente **cliente, int idCliente);
static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuario);
static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado);
static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno registro_procesar (Servicios *servicios, Cliente *cliente, SolicitudRegistro *solicitudRegistro)
{
    ResultadoBd resultadoBd;
    int idUsuario;

    if (es_registro_invalido (solicitudRegistro))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_CREDENCIALES_INVALIDAS);

    resultadoBd = nombre_ya_existe (servicios->bd, solicitudRegistro);
    if (resultadoBd == BD_ENCONTRO)
        return rechazar (servicios, cliente, RESPUESTA_ERROR_NOMBRE_YA_EXISTENTE);
    if (resultadoBd == BD_ERROR_EJECUCION)
        return fallar (servicios, cliente);

    resultadoBd = correo_ya_existe (servicios->bd, solicitudRegistro);
    if (resultadoBd == BD_ENCONTRO)
        return rechazar (servicios, cliente, RESPUESTA_ERROR_CORREO_YA_EXISTENTE);
    if (resultadoBd == BD_ERROR_EJECUCION)
        return fallar (servicios, cliente);

    if (hashear_contrasenia (solicitudRegistro) != EXITO)
        return fallar (servicios, cliente);

    if (insertar_usuario (servicios->bd, solicitudRegistro) != BD_EXITO)
        return fallar (servicios, cliente);

    if (recuperar_id (servicios->bd, solicitudRegistro, &idUsuario) != BD_ENCONTRO)
        return fallar (servicios, cliente);

    if (conectar_usuario (servicios->registroClientes, &cliente, idUsuario) != EXITO)
        return fallar (servicios, cliente);

    if (guardar_respuesta (servicios, cliente, RESPUESTA_EXITO, idUsuario) != EXITO)
        return ERROR_SIN_MEMORIA;

    logs_escribir (LOG_INFO, "registro", "Cliente id=%d registrado", cliente_obtener_id (cliente));
    return EXITO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool son_todos_espacios (const char *cad)
{
    if (*cad == '\0')
        return false;

    while (*cad == ' ')
        cad ++;

    if (*cad == '\0')
        return true;
    return false;
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

static bool es_registro_invalido (const SolicitudRegistro *solicitudRegistro)
{
    int largo;

    largo = strlen (solicitudRegistro->nombreUsuario);
    if ((largo < 3) || (largo > MAX_NOMBRE_USUARIO) || son_todos_espacios (solicitudRegistro->nombreUsuario))
        return 1;
    
    largo = strlen (solicitudRegistro->contrasenia);
    if ((largo < 8) || (largo > MAX_CONTRASENIA) || son_todos_espacios (solicitudRegistro->contrasenia))
        return 1;

    if (es_correo_electronico_invalido (solicitudRegistro->correoElectronico))
        return 1;

    return 0;
}

static ResultadoBd nombre_ya_existe (Bd *bd, const SolicitudRegistro *solicitudRegistro)
{
    return (bd_buscar_id_usuario_por_nombre (bd, solicitudRegistro->nombreUsuario, NULL));
}

static ResultadoBd correo_ya_existe (Bd *bd, const SolicitudRegistro *solicitudRegistro)
{
    return (bd_buscar_id_usuario_por_correo (bd, solicitudRegistro->correoElectronico, NULL));
}

static CodigoRetorno hashear_contrasenia (SolicitudRegistro *solicitudRegistro)
{
    char contraseniaHasheada [crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str (contraseniaHasheada, solicitudRegistro->contrasenia, strlen (solicitudRegistro->contrasenia), 3, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0)
        return ERROR_INICIALIZACION;

    strcpy (solicitudRegistro->contrasenia, contraseniaHasheada);
    
    return EXITO;
}

static ResultadoBd insertar_usuario (Bd *bd, const SolicitudRegistro *solicitudRegistro)
{
    ParametrosInsertarUsuario parametrosInsertarUsuario;

    strcpy (parametrosInsertarUsuario.nombreUsuario, solicitudRegistro->nombreUsuario);
    strcpy (parametrosInsertarUsuario.contrasenia, solicitudRegistro->contrasenia);
    strcpy (parametrosInsertarUsuario.correoElectronico, solicitudRegistro->correoElectronico);

    return (bd_insertar_usuario (bd, &parametrosInsertarUsuario));
}

static ResultadoBd recuperar_id (Bd *bd, const SolicitudRegistro *solicitudRegistro, int *returnIdUsuario)
{
    return (bd_buscar_id_usuario_por_nombre (bd, solicitudRegistro->nombreUsuario, returnIdUsuario));
}

static CodigoRetorno conectar_usuario (RegistroClientes *registroClientes, Cliente **cliente, int idCliente)
{
    return registro_clientes_promover_cliente (registroClientes, cliente, idCliente);
}

static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuario)
{
    RespuestaRegistro respuesta;

    respuesta.estado = estado;
    respuesta.idUsuario = idUsuario;

    if (servicios_guardar_respuesta (servicios, cliente, RESPUESTA_REGISTRO, &respuesta, sizeof (respuesta)) != EXITO)
    {
        cliente_marcar_desconectado (cliente);
        logs_escribir (LOG_ERROR, "registro", "Registro fallido y cliente desconectado.");
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado)
{
    if (guardar_respuesta (servicios, cliente, estado, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_AVISO, "registro", "Registro rechazado.");
    return ERROR_OPERACION_INVALIDA;
}

static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente)
{
    if (guardar_respuesta (servicios, cliente, RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_ERROR, "registro", "Registro fallido.");
    return ERROR_EJECUCION;
}
