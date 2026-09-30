#include "logica/utiles.h"


/* ============================================================================================================================================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================================================================================================================================ */


bool se_clickeo_en_rectangulo (const sfRenderWindow *renderizado, const sfRectangleShape *rectangulo)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteRectangulo;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, (sfVector2f){mouseMundo.x, mouseMundo.y});
}

bool se_clickeo_en_texto (const sfRenderWindow *renderizado, const sfText *texto)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteTexto;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, (sfVector2f){mouseMundo.x, mouseMundo.y});
}

void centrar_texto_en_area (sfText *texto, float posXInicial, float posYInicial, float anchoArea, float altoArea)
{
    sfFloatRect limites;

    limites = sfText_getLocalBounds(texto);

    sfText_setPosition (texto, (sfVector2f)
                        {
                            round (posXInicial + anchoArea / 2.f - limites.size.x / 2.f - limites.position.x),
                            round (posYInicial + altoArea / 2.f - limites.size.y /2.f - limites.position.y)
                        });
}

static bool texto_entra_en_barra_escritura (sfText *texto, float anchoBarraEscritura)
{
    sfFloatRect limitesTexto = sfText_getLocalBounds(texto);

    return (limitesTexto.size.x <= anchoBarraEscritura);
}

void limitar_visualizacion_texto_sobre_barra_escritura (sfText *texto, const char *cadena, float anchoBarraEscritura)
{
    unsigned short int i;

    for (i = 0; i <= (strlen(cadena)); i++)
    {
        sfText_setString(texto, cadena + i);
        if (texto_entra_en_barra_escritura (texto, anchoBarraEscritura))
            return;
    }
}

void omitir_eventos_pendientes (sfRenderWindow *renderizado)
{
    sfEvent evento;
    
    while (sfRenderWindow_pollEvent (renderizado, &evento)){continue;}
}


/* ============================================================================================================================================
   FUNCIONES DE ESCRITURA
   ============================================================================================================================================ */


static bool no_es_caracter_imprimible (char caracter)
{
    return ((caracter < 32) || (caracter > 126));
}

static bool no_es_backspace (char caracter)
{
    return (caracter != 8);
}

static void agregar_caracter_al_buffer (char *buffer, char caracter, int largoBuffer)
{
    buffer [largoBuffer] = caracter;
    buffer [largoBuffer + 1] = '\0';
}

static void eliminar_ultimo_caracter (char *buffer, int largoBuffer)
{
    buffer [largoBuffer - 1] = '\0';
}

CodigoRetorno ingresar_caracter_a_buffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar)
{
    int largoBuffer;
    char caracter = (char)eventoChar.text.unicode;

    if (no_es_caracter_imprimible (caracter) && no_es_backspace (caracter))
        return ERROR_OPERACION;

    // Se utiliza largoBuffer y se envia como argumento para evitar calcularlo multiples veces.
    largoBuffer = strlen (buffer);

    if (no_es_backspace (caracter))
    {
        if (largoBuffer < tamMaxBuffer - 1) // tamMaxBuffer - 1 para asegurar el '\0' al final del buffer.
            agregar_caracter_al_buffer (buffer, caracter, largoBuffer);
    }
    else if (largoBuffer > 0) // Si el caracter es "Backspace" y el buffer no esta vacio.
        eliminar_ultimo_caracter (buffer, largoBuffer);

    return EXITO;
}

CodigoRetorno pegar_texto_desde_portapapeles_a_buffer (char *buffer, int tamMaxBuffer)
{
    const uint32_t *texto, *auxTexto;
    int largoBuffer, espacioDisponibleEnBuffer, largoTextoPortapapeles = 0;

    texto = sfClipboard_getUnicodeString ();
    auxTexto = texto;

    largoBuffer = strlen (buffer);
    espacioDisponibleEnBuffer = tamMaxBuffer - largoBuffer - 1; // -1 para asegurar el '\0' al final del buffer.

    while (*auxTexto != 0)
    {
        if (no_es_caracter_imprimible ((char)(*auxTexto)))
            return ERROR_OPERACION;
        largoTextoPortapapeles ++;
        auxTexto ++;
    }

    if (largoTextoPortapapeles > espacioDisponibleEnBuffer)
        return ERROR_OPERACION;

    auxTexto = texto;
    buffer = buffer + largoBuffer;
    while (*auxTexto != 0)
    {
        *buffer = (char)(*auxTexto);
        buffer ++;
        auxTexto ++;
    }
    *buffer = '\0';

    return EXITO;
}

bool son_todos_espacios (const char *mensaje)
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
   VALIDACIONES DE DATOS
   ============================================================================================================================================ */


bool es_nombre_valido (const char *nombre)
{
    int largoNombre = strlen (nombre);

    return (((largoNombre >= 3) && (largoNombre < MAX_NOMBRE_USUARIO)) && (!son_todos_espacios (nombre)));
}

bool es_contrasenia_valida (const char *contrasenia)
{
    int largoContrasenia = strlen (contrasenia);

    return (((largoContrasenia >= 8) && (largoContrasenia < MAX_CONTRASENIA)) && (!son_todos_espacios (contrasenia)));
}

bool es_correo_electronico_valido (const char *correo)
{
    char *ptr = strchr (correo, '@'); // Se posiciona en el @

    if ((ptr == NULL) ||                            // Si no tiene @
        (ptr == correo) ||                          // O empieza con @
        (strchr (ptr, '.') == NULL) ||           // O no tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL))     // O tiene 2 arrobas
        return false;
    return true;
}


/* ============================================================================================================================================
   FUNCIONES DE PUNTO DE INSERCION
   ============================================================================================================================================ */


void punto_insercion_resetear (PuntoInsercion *puntoInsercion)
{
    puntoInsercion->estado = DESHABILITADO;
    puntoInsercion->contador = CONTADOR_REINICIAR;
}

bool punto_insercion_esta_habilitado (const PuntoInsercion *puntoInsercion)
{
    if (puntoInsercion->estado == HABILITADO)
        return 1;
    return 0;
}

void punto_insercion_actualizar (PuntoInsercion *puntoInsercion)
{
    puntoInsercion->contador ++;
    if (puntoInsercion->contador >= PUNTO_INSERCION_VELOCIDAD_PARPADEO)
    {
        puntoInsercion->contador = CONTADOR_REINICIAR;
        if (puntoInsercion->estado == DESHABILITADO)
            puntoInsercion->estado = HABILITADO;
        else
            puntoInsercion->estado = DESHABILITADO;
    }
}


/* ============================================================================================================================================
   FUNCIONES DE BARRA DE CARGA
   ============================================================================================================================================ */


void texto_de_carga_iniciar (TextoDeCarga *textoDeCarga)
{
    textoDeCarga->estado = TEXTO_DE_CARGA_ESTADO_INICIAL;
    textoDeCarga->contador = CONTADOR_REINICIAR;
}

bool texto_de_carga_actualizar (TextoDeCarga *textoDeCarga)
{
    if (textoDeCarga->contador >= TEXTO_DE_CARGA_VELOCIDAD_ACTUALIZACION)
    {
        textoDeCarga->estado ++;
        if (textoDeCarga->estado > TEXTO_DE_CARGA_ESTADO_FINAL)
            textoDeCarga->estado = TEXTO_DE_CARGA_ESTADO_INICIAL;
        textoDeCarga->contador = CONTADOR_REINICIAR;
        return true;
    }
    else
    {
        textoDeCarga->contador ++;
        return false;
    }
}

void texto_de_carga_modificar_texto (TextoDeCarga *textoDeCarga, char *texto)
{
    switch (textoDeCarga->estado)
    {
        case 1:
            strcat (texto, " .");
            break;

        case 2:
            strcat (texto, " . .");
            break;

        case 3:
            strcat (texto, " . . .");
            break;
        
        default:
            break;
    }
}


/* ============================================================================================================================================
   LOGS
   ============================================================================================================================================ */


void log_error_conexion ()
{
    puts ("\nERROR - Se perdio la conexion con el servidor");
}

void log_warning_respuesta_recibida_otra_ui ()
{
    puts ("\nWARNING - La respuesta recibida del servidor no corresponde a la interfaz sobre la que esta situado el usuario.");
}
