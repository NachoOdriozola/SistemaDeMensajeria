#include "baseDeDatos/baseDeDatos.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ResultadoInicializacionBD existe_tabla_usuarios (sqlite3 *bd);
static CodigoRetorno crear_esquema (sqlite3 *bd);
static CodigoRetorno crear_sentencias_sqlite (sqlite3 *bd, SentenciasSqlite *sentencias);
static void liberar_sentencias_sqlite (SentenciasSqlite *sentencias);

static bool encontro_usuario (int resultadoConsulta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno bd_inicializar (sqlite3 **bd, SentenciasSqlite *sentenciasSqlite)
{
    ResultadoInicializacionBD respuestaInicializacionBD;

    if (sqlite3_open ("database/database.bd", bd) != SQLITE_OK)
    {
        printf("\nERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*bd));
        return ERROR_INICIALIZACION;
    }
    
    respuestaInicializacionBD = existe_tabla_usuarios (*bd);

    if (respuestaInicializacionBD == ERROR_PREPARACION_CONSULTA)
        return ERROR_INICIALIZACION;

    if (respuestaInicializacionBD == TABLA_NO_EXISTE)
        if (crear_esquema(*bd) == ERROR_INICIALIZACION)
            return ERROR_INICIALIZACION;

    if (crear_sentencias_sqlite (*bd, sentenciasSqlite) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void bd_configurar (sqlite3 *bd)
{
    sqlite3_exec (bd, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);
}

void bd_liberar (sqlite3 *bd, SentenciasSqlite *sentenciasSqlite)
{
    if (bd != NULL)
        sqlite3_close (bd);

    liberar_sentencias_sqlite (sentenciasSqlite);
}


bool bd_buscar_id_por_nombre (sqlite3_stmt *sentenciaBuscarIdPorNombre, const ParametrosBuscarUsuarioPorNombre *parametrosBuscarUsuarioPorNombre, int *returnIdUsuario)
{
    int resultadoConsulta;

    sqlite3_reset (sentenciaBuscarIdPorNombre);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarIdPorNombre);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarIdPorNombre, 1, parametrosBuscarUsuarioPorNombre->nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarIdPorNombre);
    if (encontro_usuario (resultadoConsulta))
    {
        if (returnIdUsuario != NULL)
            *returnIdUsuario = sqlite3_column_int (sentenciaBuscarIdPorNombre, 0);
        return true;
    }
    else
    {
        if (returnIdUsuario != NULL)
            *returnIdUsuario = ID_INVALIDO;
        return false;
    }
}

bool bd_buscar_id_y_contrasenia_por_nombre (sqlite3_stmt *sentenciaBuscarIdYContraseniaPorNombre, const ParametrosBuscarUsuarioPorNombre *parametrosBuscarUsuarioPorNombre, int *returnIdUsuario, char *returnContrasenia)
{
    int resultadoConsulta;
    const char *auxContrasenia;

    sqlite3_reset (sentenciaBuscarIdYContraseniaPorNombre);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarIdYContraseniaPorNombre);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarIdYContraseniaPorNombre, 1, parametrosBuscarUsuarioPorNombre->nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarIdYContraseniaPorNombre);
    if (encontro_usuario (resultadoConsulta))
    {
        *returnIdUsuario = sqlite3_column_int (sentenciaBuscarIdYContraseniaPorNombre, 0);
        auxContrasenia = (const char *) sqlite3_column_text (sentenciaBuscarIdYContraseniaPorNombre, 1);
        strcpy (returnContrasenia, auxContrasenia);
        return true;
    }
    else
    {
        *returnIdUsuario = ID_INVALIDO;
        *returnContrasenia = '\0';
        return false;
    }
}

bool bd_existe_usuario_con_correo (sqlite3_stmt *sentenciaBuscarIdPorCorreo, const ParametrosBuscarUsuarioPorCorreo *parametrosBuscarUsuarioPorCorreo)
{
    int resultadoConsulta;

    sqlite3_reset (sentenciaBuscarIdPorCorreo);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarIdPorCorreo);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarIdPorCorreo, 1, parametrosBuscarUsuarioPorCorreo->correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarIdPorCorreo);
    if (encontro_usuario (resultadoConsulta))
        return true;
    return false;
}

void bd_insertar_usuario (sqlite3_stmt *sentenciaInsertarUsuario, const ParametrosInsertarUsuario *parametrosInsertarUsuario)
{
    sqlite3_reset (sentenciaInsertarUsuario);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaInsertarUsuario);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaInsertarUsuario, 1, parametrosInsertarUsuario->nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentenciaInsertarUsuario, 2, parametrosInsertarUsuario->contrasenia, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentenciaInsertarUsuario, 3, parametrosInsertarUsuario->correoElectronico, -1, SQLITE_STATIC);

    sqlite3_step (sentenciaInsertarUsuario);
}

void bd_insertar_mensaje (sqlite3_stmt *sentenciaInsertarMensaje, const ParametrosInsertarMensaje *parametrosInsertarMensaje)
{
    sqlite3_reset (sentenciaInsertarMensaje);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaInsertarMensaje);    // Limpia bindings previos.

    sqlite3_bind_int (sentenciaInsertarMensaje, 1, parametrosInsertarMensaje->idEmisor);
    sqlite3_bind_int (sentenciaInsertarMensaje, 2, parametrosInsertarMensaje->idReceptor);
    sqlite3_bind_text (sentenciaInsertarMensaje, 3, parametrosInsertarMensaje->texto, -1, SQLITE_STATIC);

    sqlite3_step (sentenciaInsertarMensaje);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ResultadoInicializacionBD existe_tabla_usuarios (sqlite3 *bd)
{
    sqlite3_stmt *sentencia;
    int resultado;

    if (sqlite3_prepare_v2 (bd, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (bd));
        return ERROR_PREPARACION_CONSULTA;
    }

    resultado = sqlite3_step (sentencia);
    sqlite3_finalize(sentencia);

    if (resultado == SQLITE_ROW)
        return TABLA_EXISTE;
    return TABLA_NO_EXISTE;
}

static CodigoRetorno crear_esquema (sqlite3 *bd)
{
    FILE *archEsquema;
    long tamArchEsquema;
    char *consulta;

    archEsquema = fopen("database/schema.sql", "rb");
    if (!archEsquema)
    {
        perror ("\nERROR - Abrir archivo schema.sql.\n");
        return ERROR_INICIALIZACION;
    }

    fseek (archEsquema, 0, SEEK_END);
    tamArchEsquema = ftell (archEsquema);
    rewind (archEsquema);

    consulta = malloc (tamArchEsquema + 1); // +1 para el '\0'.
    if (!consulta)
    {
        perror ("\nERROR - Sin memoria.\n");
        fclose(archEsquema);
        return ERROR_INICIALIZACION;
    }

    fread (consulta, 1, tamArchEsquema, archEsquema);
    consulta[tamArchEsquema] = '\0';

    if (sqlite3_exec (bd, consulta, NULL, NULL, NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Ejecutar schema.sql.\n");
        fclose(archEsquema);
        free (consulta);
        return ERROR_INICIALIZACION;
    }

    fclose(archEsquema);
    free (consulta);

    return EXITO;
}

static CodigoRetorno crear_sentencias_sqlite (sqlite3 *bd, SentenciasSqlite *sentencias)
{
    if (sqlite3_prepare_v2 (bd, "SELECT id FROM usuarios WHERE nombre = ?;", -1, &(sentencias->buscarIdPorNombre), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarIdPorNombre.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (bd, "SELECT id, hashContrasenia FROM usuarios WHERE nombre = ?;", -1, &(sentencias->buscarIdYContraseniaPorNombre), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarIdYContraseniaPorNombre.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (bd, "SELECT id FROM usuarios WHERE correoElectronico = ?;", -1, &(sentencias->buscarIdPorCorreo), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarIdPorCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (bd, "INSERT INTO usuarios (nombre, hashContrasenia, correoElectronico) VALUES (?, ?, ?);", -1, &(sentencias->insertarUsuario), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta insertarUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (bd, "INSERT INTO mensajes (idEmisor, idReceptor, texto) VALUES (?, ?, ?);", -1, &(sentencias->insertarMensaje), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta insertarMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

static void liberar_sentencias_sqlite (SentenciasSqlite *sentencias)
{
    sqlite3_finalize (sentencias->buscarIdPorNombre);
    sqlite3_finalize (sentencias->buscarIdYContraseniaPorNombre);
    sqlite3_finalize (sentencias->buscarIdPorCorreo);
    sqlite3_finalize (sentencias->insertarUsuario);
    sqlite3_finalize (sentencias->insertarMensaje);
}


static bool encontro_usuario (int resultadoConsulta)
{
    return ((resultadoConsulta == SQLITE_ROW) ? (true) : (false));
}
