#include "servicios/autenticacion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_autenticacion_invalida (const SolicitudAutenticacion *solicitudAutenticacion);
static ResultadoBd existe_usuario (Bd *bd, const SolicitudAutenticacion *solicitudAutenticacion, ResultadoConsultaIdYContrasenia *returnResultadoConsultaIdYContrasenia);
static bool contrasenia_no_coincide (const SolicitudAutenticacion *solicitudAutenticacion, const char *hashContrasenia);
static bool usuario_ya_esta_conectado (RegistroClientes *registroClientes, int id);
static CodigoRetorno conectar_usuario (RegistroClientes *registroClientes, Cliente **cliente, int idCliente);
static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuario);
static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado);
static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno autenticacion_procesar (Servicios *servicios, Cliente *cliente, const SolicitudAutenticacion *solicitudAutenticacion)
{
    ResultadoBd resultadoBd;
    ResultadoConsultaIdYContrasenia consulta;

    if (es_autenticacion_invalida (solicitudAutenticacion))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_CREDENCIALES_INVALIDAS);

    resultadoBd = existe_usuario (servicios->bd, solicitudAutenticacion, &consulta);
    if (resultadoBd == BD_NO_ENCONTRO)
        return rechazar (servicios, cliente, RESPUESTA_ERROR_CREDENCIALES_INVALIDAS);
    if (resultadoBd == BD_ERROR_EJECUCION)
        return fallar (servicios, cliente);

    if (contrasenia_no_coincide (solicitudAutenticacion, consulta.contrasenia))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_CREDENCIALES_INVALIDAS);

    if (usuario_ya_esta_conectado (servicios->registroClientes, consulta.idUsuario))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_OPERACION_INVALIDA);

    if (conectar_usuario (servicios->registroClientes, &cliente, consulta.idUsuario) != EXITO)
        return fallar (servicios, cliente);

    if (guardar_respuesta (servicios, cliente, RESPUESTA_EXITO, consulta.idUsuario) != EXITO)
        return ERROR_SIN_MEMORIA;

    logs_escribir (LOG_INFO, "autenticacion", "Cliente id=%d autenticado.", cliente_obtener_id (cliente));
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

static bool es_autenticacion_invalida (const SolicitudAutenticacion *solicitudAutenticacion)
{
    int largo;

    largo = strlen (solicitudAutenticacion->nombreUsuario);
    if ((largo < 3) || (largo > MAX_NOMBRE_USUARIO) || (son_todos_espacios (solicitudAutenticacion->nombreUsuario)))
        return 1;
    
    largo = strlen (solicitudAutenticacion->contrasenia);
    if ((largo < 8) || (largo > MAX_CONTRASENIA) || (son_todos_espacios (solicitudAutenticacion->contrasenia)))
        return 1;

    return 0;
}

static ResultadoBd existe_usuario (Bd *bd, const SolicitudAutenticacion *solicitudAutenticacion, ResultadoConsultaIdYContrasenia *returnResultadoConsultaIdYContrasenia)
{
    return (bd_buscar_id_y_contrasenia_usuario_por_nombre (bd, solicitudAutenticacion->nombreUsuario, returnResultadoConsultaIdYContrasenia));
}

static bool contrasenia_no_coincide (const SolicitudAutenticacion *solicitudAutenticacion, const char *hashContrasenia)
{
    if (crypto_pwhash_str_verify (hashContrasenia, solicitudAutenticacion->contrasenia, strlen (solicitudAutenticacion->contrasenia)) == -1)
        return 1;
    return 0;
}

static bool usuario_ya_esta_conectado (RegistroClientes *registroClientes, int id)
{
    return registro_clientes_buscar_autenticado (registroClientes, id, NULL);
}

static CodigoRetorno conectar_usuario (RegistroClientes *registroClientes, Cliente **cliente, int idCliente)
{
    return registro_clientes_promover_cliente (registroClientes, cliente, idCliente);
}

static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuario)
{
    RespuestaAutenticacion respuesta;

    respuesta.estado = estado;
    respuesta.idUsuario = idUsuario;

    if (servicios_guardar_respuesta (servicios, cliente, RESPUESTA_AUTENTICACION, &respuesta, sizeof (respuesta)) != EXITO)
    {
        cliente_marcar_desconectado (cliente);
        logs_escribir (LOG_ERROR, "autenticacion", "Autenticacion fallida y cliente desconectado.");
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado)
{
    if (guardar_respuesta (servicios, cliente, estado, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_AVISO, "autenticacion", "Autenticacion rechazada.");
    return ERROR_OPERACION_INVALIDA;
}

static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente)
{
    if (guardar_respuesta (servicios, cliente, RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_ERROR, "autenticacion", "Autenticacion fallida.");
    return ERROR_EJECUCION;
}

