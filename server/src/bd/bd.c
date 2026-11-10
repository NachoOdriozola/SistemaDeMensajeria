#include "bd/bd.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ResultadoBd existen_tablas (sqlite3 *conexion);
static ResultadoBd crear_esquema (sqlite3 *conexion);
static ResultadoBd crear_sentencias (Bd *bd);
static void liberar_sentencias (Sentencias *sentencias);

static void limpiar_sentencia (sqlite3_stmt *sentencia);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


ResultadoBd bd_inicializar (Bd *bd)
{
    ResultadoBd resultadoBd;

    bd->conexion = NULL;

    if (sqlite3_open ("database/database.db", &(bd->conexion)) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Apertura de archivo 'database.db': %s", sqlite3_errmsg (bd->conexion));
        return BD_ERROR_INICIALIZACION;
    }
    
    resultadoBd = existen_tablas (bd->conexion);
    if ((resultadoBd == BD_ERROR_INICIALIZACION) || (resultadoBd == BD_ERROR_EJECUCION))
    {
        logs_escribir (LOG_ERROR, "bd", "Verificacion de existencia de tablas.");
        sqlite3_close (bd->conexion);
        return resultadoBd;
    }

    if (resultadoBd == BD_NO_ENCONTRO)
    {
        resultadoBd = crear_esquema (bd->conexion);
        if (resultadoBd != BD_EXITO)
        {
            logs_escribir (LOG_ERROR, "bd", "Creacion de tablas.");
            sqlite3_close (bd->conexion);
            return resultadoBd;
        }
    }

    resultadoBd = crear_sentencias (bd);
    if (resultadoBd != BD_EXITO)
    {
        logs_escribir (LOG_ERROR, "bd", "Creacion de sentencias.");
        sqlite3_close (bd->conexion);
        return resultadoBd;
    }

    if (sqlite3_exec (bd->conexion, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Configuracion de modo WAL: %s", sqlite3_errmsg (bd->conexion));
        sqlite3_close (bd->conexion);
        liberar_sentencias (&(bd->sentencias));
        return BD_ERROR_EJECUCION;
    }

    return BD_EXITO;
}

void bd_liberar (Bd *bd)
{
    if (bd->conexion != NULL)
        sqlite3_close (bd->conexion);

    liberar_sentencias (&(bd->sentencias));
}


ResultadoBd bd_buscar_id_usuario_por_nombre (Bd *bd, const char *nombre, int *returnId)
{
    sqlite3_stmt *sentencia = bd->sentencias.buscarIdPorNombre;
    ResultadoBd resultadoBd;
    int resultadoConsulta;

    limpiar_sentencia (sentencia);

    if (sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Bind de datos para consulta: %s", sqlite3_errmsg (bd->conexion));
        limpiar_sentencia (sentencia);
        return BD_ERROR_EJECUCION;
    }

    resultadoConsulta = sqlite3_step (sentencia);

    if (resultadoConsulta == SQLITE_ROW)
    {
        if (returnId != NULL)
            *returnId = sqlite3_column_int (sentencia, 0);
        resultadoBd = BD_ENCONTRO;
    }

    if (resultadoConsulta == SQLITE_DONE)
        resultadoBd = BD_NO_ENCONTRO;

    if ((resultadoConsulta != SQLITE_ROW) && (resultadoConsulta != SQLITE_DONE))
    {
        resultadoBd = BD_ERROR_EJECUCION;
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (bd->conexion));
    }

    limpiar_sentencia (sentencia);
    return resultadoBd;
}

ResultadoBd bd_buscar_id_y_contrasenia_usuario_por_nombre (Bd *bd, const char *nombre, ResultadoConsultaIdYContrasenia *returnResultadoConsultaIdYContrasenia)
{
    sqlite3_stmt *sentencia = bd->sentencias.buscarIdYContraseniaPorNombre;
    ResultadoBd resultadoBd;
    int resultadoConsulta;
    const char *auxContrasenia;

    limpiar_sentencia (sentencia);

    if (sqlite3_bind_text (sentencia, 1, nombre, -1, SQLITE_STATIC) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Bind de datos para consulta: %s", sqlite3_errmsg (bd->conexion));
        limpiar_sentencia (sentencia);
        return BD_ERROR_EJECUCION;
    }

    resultadoConsulta = sqlite3_step (sentencia);

    if (resultadoConsulta == SQLITE_ROW)
    {
        if (returnResultadoConsultaIdYContrasenia != NULL)
        {
            returnResultadoConsultaIdYContrasenia->idUsuario = sqlite3_column_int (sentencia, 0);
            auxContrasenia = (const char *) sqlite3_column_text (sentencia, 1);
            strcpy (returnResultadoConsultaIdYContrasenia->contrasenia, auxContrasenia);
        }
        resultadoBd = BD_ENCONTRO;
    }

    if (resultadoConsulta == SQLITE_DONE)
        resultadoBd = BD_NO_ENCONTRO;

    if ((resultadoConsulta != SQLITE_ROW) && (resultadoConsulta != SQLITE_DONE))
    {
        resultadoBd = BD_ERROR_EJECUCION;
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (bd->conexion));
    }

    limpiar_sentencia (sentencia);
    return resultadoBd;
}

ResultadoBd bd_buscar_id_usuario_por_correo (Bd *bd, const char *correo, int *returnId)
{
    sqlite3_stmt *sentencia = bd->sentencias.buscarIdPorCorreo;
    ResultadoBd resultadoBd;
    int resultadoConsulta;

    limpiar_sentencia (sentencia);

    if (sqlite3_bind_text (sentencia, 1, correo, -1, SQLITE_STATIC) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Bind de datos para consulta: %s", sqlite3_errmsg (bd->conexion));
        limpiar_sentencia (sentencia);
        return BD_ERROR_EJECUCION;
    }

    resultadoConsulta = sqlite3_step (sentencia);

    if (resultadoConsulta == SQLITE_ROW)
    {
        if (returnId != NULL)
            *returnId = sqlite3_column_int (sentencia, 0);
        resultadoBd = BD_ENCONTRO;
    }

    if (resultadoConsulta == SQLITE_DONE)
        resultadoBd = BD_NO_ENCONTRO;
        
    if ((resultadoConsulta != SQLITE_ROW) && (resultadoConsulta != SQLITE_DONE))
    {
        resultadoBd = BD_ERROR_EJECUCION;
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (bd->conexion));
    }

    limpiar_sentencia (sentencia);
    return resultadoBd;
}

ResultadoBd bd_insertar_usuario (Bd *bd, const ParametrosInsertarUsuario *parametrosInsertarUsuario)
{
    sqlite3_stmt *sentencia = bd->sentencias.insertarUsuario;
    ResultadoBd resultadoBd;

    limpiar_sentencia (sentencia);

    if (
        (sqlite3_bind_text (sentencia, 1, parametrosInsertarUsuario->nombreUsuario, -1, SQLITE_STATIC) != SQLITE_OK) ||
        (sqlite3_bind_text (sentencia, 2, parametrosInsertarUsuario->contrasenia, -1, SQLITE_STATIC) != SQLITE_OK) ||
        (sqlite3_bind_text (sentencia, 3, parametrosInsertarUsuario->correoElectronico, -1, SQLITE_STATIC) != SQLITE_OK)
        )
    {
        logs_escribir (LOG_ERROR, "bd", "Bind de datos para consulta: %s", sqlite3_errmsg (bd->conexion));
        limpiar_sentencia (sentencia);
        return BD_ERROR_EJECUCION;
    }

    if (sqlite3_step (sentencia) == SQLITE_DONE)
        resultadoBd = BD_EXITO;
    else
    {
        resultadoBd = BD_ERROR_EJECUCION;
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (bd->conexion));
    }

    limpiar_sentencia (sentencia);
    return resultadoBd;
}

ResultadoBd bd_insertar_mensaje (Bd *bd, const ParametrosInsertarMensaje *parametrosInsertarMensaje)
{
    sqlite3_stmt *sentencia = bd->sentencias.insertarMensaje;
    ResultadoBd resultadoBd;

    limpiar_sentencia (sentencia);

    if (
        (sqlite3_bind_int (sentencia, 1, parametrosInsertarMensaje->idEmisor) != SQLITE_OK) ||
        (sqlite3_bind_int (sentencia, 2, parametrosInsertarMensaje->idReceptor) != SQLITE_OK) ||
        (sqlite3_bind_text (sentencia, 3, parametrosInsertarMensaje->texto, -1, SQLITE_STATIC) != SQLITE_OK)
        )
    {
        logs_escribir (LOG_ERROR, "bd", "Bind de datos para consulta: %s", sqlite3_errmsg (bd->conexion));
        limpiar_sentencia (sentencia);
        return BD_ERROR_EJECUCION;
    }

    if (sqlite3_step (sentencia) == SQLITE_DONE)
        resultadoBd = BD_EXITO;
    else
    {
        resultadoBd = BD_ERROR_EJECUCION;
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (bd->conexion));
    }

    limpiar_sentencia (sentencia);
    return resultadoBd;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ResultadoBd existen_tablas (sqlite3 *conexion)
{
    sqlite3_stmt *sentencia;
    int resultado;

    // No es sustituible por un sqlite3_exec porque siempre devuelve SQLITE_OK y no SQLITE_ROW para saber si existe la tabla.
    if (sqlite3_prepare_v2 (conexion, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';", -1, &sentencia, NULL) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Preparacion de consulta: %s", sqlite3_errmsg (conexion));
        return BD_ERROR_INICIALIZACION;
    }

    resultado = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);

    switch (resultado)
    {
        case SQLITE_ROW:
            return BD_ENCONTRO;

        case SQLITE_DONE:
            return BD_NO_ENCONTRO;
    
        default:
            logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (conexion));
            return BD_ERROR_EJECUCION;
    }
}

static ResultadoBd crear_esquema (sqlite3 *conexion)
{
    FILE *archEsquema;
    long tamArchEsquema;
    char *consulta;

    archEsquema = fopen ("database/schema.sql", "rb");
    if (!archEsquema)
    {
        logs_escribir (LOG_ERROR, "bd", "Apertura de archivo 'schema.sql'.");
        return BD_ERROR_INICIALIZACION;
    }

    fseek (archEsquema, 0, SEEK_END);
    tamArchEsquema = ftell (archEsquema);
    rewind (archEsquema);

    consulta = malloc (tamArchEsquema + 1); // +1 para el '\0'.
    if (!consulta)
    {
        logs_escribir (LOG_ERROR, "bd", "Creacion de consulta: sin memoria");
        fclose(archEsquema);
        return BD_ERROR_INICIALIZACION;
    }

    fread (consulta, 1, tamArchEsquema, archEsquema);
    consulta[tamArchEsquema] = '\0';

    if (sqlite3_exec (conexion, consulta, NULL, NULL, NULL) != SQLITE_OK)
    {
        logs_escribir (LOG_ERROR, "bd", "Ejecucion de consulta: %s", sqlite3_errmsg (conexion));
        fclose(archEsquema);
        free (consulta);
        return BD_ERROR_EJECUCION;
    }

    fclose(archEsquema);
    free (consulta);

    return BD_EXITO;
}

static ResultadoBd crear_sentencias (Bd *bd)
{
    bd->sentencias.buscarIdPorCorreo = NULL;
    bd->sentencias.buscarIdPorNombre = NULL;
    bd->sentencias.buscarIdYContraseniaPorNombre = NULL;
    bd->sentencias.insertarMensaje = NULL;
    bd->sentencias.insertarUsuario = NULL;

    if (
        (sqlite3_prepare_v2 (bd->conexion, "SELECT id FROM usuarios WHERE nombre = ?;", -1, &(bd->sentencias.buscarIdPorNombre), NULL) != SQLITE_OK) ||
        (sqlite3_prepare_v2 (bd->conexion, "SELECT id, hashContrasenia FROM usuarios WHERE nombre = ?;", -1, &(bd->sentencias.buscarIdYContraseniaPorNombre), NULL) != SQLITE_OK) ||
        (sqlite3_prepare_v2 (bd->conexion, "SELECT id FROM usuarios WHERE correoElectronico = ?;", -1, &(bd->sentencias.buscarIdPorCorreo), NULL) != SQLITE_OK) ||
        (sqlite3_prepare_v2 (bd->conexion, "INSERT INTO usuarios (nombre, hashContrasenia, correoElectronico) VALUES (?, ?, ?);", -1, &(bd->sentencias.insertarUsuario), NULL) != SQLITE_OK) ||
        (sqlite3_prepare_v2 (bd->conexion, "INSERT INTO mensajes (idEmisor, idReceptor, texto) VALUES (?, ?, ?);", -1, &(bd->sentencias.insertarMensaje), NULL) != SQLITE_OK)
       )
    {
        logs_escribir (LOG_ERROR, "bd", "Preparacion de consulta: %s", sqlite3_errmsg (bd->conexion));
        return BD_ERROR_INICIALIZACION;
    }

    return BD_EXITO;
}

static void liberar_sentencias (Sentencias *sentencias)
{
    if (sentencias->buscarIdPorNombre != NULL)
        sqlite3_finalize (sentencias->buscarIdPorNombre);

    if (sentencias->buscarIdYContraseniaPorNombre != NULL)
        sqlite3_finalize (sentencias->buscarIdYContraseniaPorNombre);

    if (sentencias->buscarIdPorCorreo != NULL)
        sqlite3_finalize (sentencias->buscarIdPorCorreo);

    if (sentencias->insertarUsuario != NULL)
        sqlite3_finalize (sentencias->insertarUsuario);

    if (sentencias->insertarMensaje != NULL)
        sqlite3_finalize (sentencias->insertarMensaje);
}


static void limpiar_sentencia (sqlite3_stmt *sentencia)
{
    sqlite3_reset (sentencia);
    sqlite3_clear_bindings (sentencia);
}
