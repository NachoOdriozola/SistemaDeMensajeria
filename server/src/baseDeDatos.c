#include "../include/baseDeDatos.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static t_respuestaInicializacionDB existeTablaUsuarios (sqlite3 *db);
static t_codigoRetorno crearEsquema (sqlite3 *db);
static t_codigoRetorno inicializarSentenciasSqlite (sqlite3 *db, t_sentenciasSqlite *sentencias);
static void liberarSentenciasSqlite (t_sentenciasSqlite *sentencias);

static bool encontroUnUsuario (int resultadoConsulta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


t_codigoRetorno inicializarBaseDatos (sqlite3 **db, t_sentenciasSqlite *sentenciasSqlite)
{
    t_respuestaInicializacionDB respuestaInicializacionDB;

    if (sqlite3_open ("../../../server/database/database.db", db) != SQLITE_OK)
    {
        printf("\nERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*db));
        return ERROR_INICIALIZACION;
    }
    
    respuestaInicializacionDB = existeTablaUsuarios (*db);

    if (respuestaInicializacionDB == ERROR_PREPARACION_CONSULTA)
        return ERROR_INICIALIZACION;

    if (respuestaInicializacionDB == TABLA_NO_EXISTE)
        if (crearEsquema(*db) == ERROR_INICIALIZACION)
            return ERROR_INICIALIZACION;

    if (inicializarSentenciasSqlite (*db, sentenciasSqlite) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void configurarBaseDeDatos (sqlite3 *db)
{
    sqlite3_exec (db, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);
}

void liberarBaseDeDatos (sqlite3 *db, t_sentenciasSqlite *sentenciasSqlite)
{
    if (db != NULL)
        sqlite3_close (db);

    liberarSentenciasSqlite (sentenciasSqlite);
}


bool buscarUsuarioPorNombre_recuperarId (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosBuscarUsuarioPorNombre *datosBuscarUsuarioPorNombre, int *returnIdUsuario)
{
    int resultadoConsulta;

    sqlite3_reset (sentenciaBuscarUsuarioPorNombre_recuperarId);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarUsuarioPorNombre_recuperarId);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarUsuarioPorNombre_recuperarId, 1, datosBuscarUsuarioPorNombre->nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarUsuarioPorNombre_recuperarId);
    if (encontroUnUsuario (resultadoConsulta))
    {
        if (returnIdUsuario != NULL)
            *returnIdUsuario = sqlite3_column_int (sentenciaBuscarUsuarioPorNombre_recuperarId, 0);
        return true;
    }
    else
    {
        if (returnIdUsuario != NULL)
            *returnIdUsuario = ID_INVALIDO;
        return false;
    }
}

bool buscarUsuarioPorNombre_recuperarIdYContrasenia (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, const t_datosBuscarUsuarioPorNombre *datosBuscarUsuarioPorNombre, int *returnIdUsuario, char *returnContrasenia)
{
    int resultadoConsulta;
    const char *auxContrasenia;

    sqlite3_reset (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, 1, datosBuscarUsuarioPorNombre->nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia);
    if (encontroUnUsuario (resultadoConsulta))
    {
        *returnIdUsuario = sqlite3_column_int (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, 0);
        auxContrasenia = (const char *) sqlite3_column_text (sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, 1);
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

bool buscarUsuarioPorCorreo (sqlite3_stmt *sentenciaBuscarUsuarioPorCorreo, const t_datosBuscarUsuarioPorCorreo *datosBuscarUsuarioPorCorreo)
{
    int resultadoConsulta;

    sqlite3_reset (sentenciaBuscarUsuarioPorCorreo);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaBuscarUsuarioPorCorreo);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaBuscarUsuarioPorCorreo, 1, datosBuscarUsuarioPorCorreo->correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentenciaBuscarUsuarioPorCorreo);
    if (encontroUnUsuario (resultadoConsulta))
        return true;
    return false;
}

void insertarUsuario (sqlite3_stmt *sentenciaInsertarUsuario, const t_datosInsertarUsuario *datosInsertarUsuario)
{
    sqlite3_reset (sentenciaInsertarUsuario);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaInsertarUsuario);    // Limpia bindings previos.

    sqlite3_bind_text (sentenciaInsertarUsuario, 1, datosInsertarUsuario->nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentenciaInsertarUsuario, 2, datosInsertarUsuario->contrasenia, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentenciaInsertarUsuario, 3, datosInsertarUsuario->correoElectronico, -1, SQLITE_STATIC);

    sqlite3_step (sentenciaInsertarUsuario);
}

void insertarMensaje (sqlite3_stmt *sentenciaInsertarMensaje, const t_datosInsertarMensaje *datosInsertarMensaje)
{
    sqlite3_reset (sentenciaInsertarMensaje);                   // Limpia el estado de la ejecucion anterior.
    sqlite3_clear_bindings (sentenciaInsertarMensaje);    // Limpia bindings previos.

    sqlite3_bind_int (sentenciaInsertarMensaje, 1, datosInsertarMensaje->idEmisor);
    sqlite3_bind_int (sentenciaInsertarMensaje, 2, datosInsertarMensaje->idReceptor);
    sqlite3_bind_text (sentenciaInsertarMensaje, 3, datosInsertarMensaje->texto, -1, SQLITE_STATIC);

    sqlite3_step (sentenciaInsertarMensaje);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static t_respuestaInicializacionDB existeTablaUsuarios (sqlite3 *db)
{
    sqlite3_stmt *sentencia;
    int resultado;

    if (sqlite3_prepare_v2 (db, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';", -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (db));
        return ERROR_PREPARACION_CONSULTA;
    }

    resultado = sqlite3_step (sentencia);
    sqlite3_finalize(sentencia);

    if (resultado == SQLITE_ROW)
        return TABLA_EXISTE;
    return TABLA_NO_EXISTE;
}

static t_codigoRetorno crearEsquema (sqlite3 *db)
{
    FILE *archEsquema;
    long tamArchEsquema;
    char *consulta;

    archEsquema = fopen("../../../server/database/schema.sql", "rb");
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

    if (sqlite3_exec (db, consulta, NULL, NULL, NULL) != SQLITE_OK)
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

static t_codigoRetorno inicializarSentenciasSqlite (sqlite3 *db, t_sentenciasSqlite *sentencias)
{
    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios WHERE nombre = ?;", -1, &(sentencias->buscarUsuarioPorNombre_recuperarId), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarUsuarioPorNombre_recuperarId.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (db, "SELECT id, hashContrasenia FROM usuarios WHERE nombre = ?;", -1, &(sentencias->buscarUsuarioPorNombre_recuperarIdYContrasenia), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarUsuarioPorNombre_recuperarIdYContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (db, "SELECT id FROM usuarios WHERE correoElectronico = ?;", -1, &(sentencias->buscarUsuarioPorCorreo), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta buscarUsuarioPorCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (db, "INSERT INTO usuarios (nombre, hashContrasenia, correoElectronico) VALUES (?, ?, ?);", -1, &(sentencias->insertarUsuario), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta insertarUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    if (sqlite3_prepare_v2 (db, "INSERT INTO mensajes (idEmisor, idReceptor, texto) VALUES (?, ?, ?);", -1, &(sentencias->insertarMensaje), NULL) != SQLITE_OK)
    {
        perror ("\nERROR - Preparando consulta insertarMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

static void liberarSentenciasSqlite (t_sentenciasSqlite *sentencias)
{
    sqlite3_finalize (sentencias->buscarUsuarioPorNombre_recuperarId);
    sqlite3_finalize (sentencias->buscarUsuarioPorNombre_recuperarIdYContrasenia);
    sqlite3_finalize (sentencias->buscarUsuarioPorCorreo);
    sqlite3_finalize (sentencias->insertarUsuario);
    sqlite3_finalize (sentencias->insertarMensaje);
}


static bool encontroUnUsuario (int resultadoConsulta)
{
    return ((resultadoConsulta == SQLITE_ROW) ? (true) : (false));
}
