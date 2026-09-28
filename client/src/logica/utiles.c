#include "logica/utiles.h"


/* ============================================================================================================================================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================================================================================================================================ */


bool clickEnRectangulo (const sfRenderWindow *renderizado, const sfRectangleShape *rectangulo)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteRectangulo;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, (sfVector2f){mouseMundo.x, mouseMundo.y});
}

bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteTexto;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, (sfVector2f){mouseMundo.x, mouseMundo.y});
}

void centrarTextoEnArea (sfText *texto, float posXInicial, float posYInicial, float anchoArea, float altoArea)
{
    sfFloatRect limites;

    limites = sfText_getLocalBounds(texto);

    sfText_setPosition (texto, (sfVector2f)
                        {
                            round (posXInicial + anchoArea / 2.f - limites.size.x / 2.f - limites.position.x),
                            round (posYInicial + altoArea / 2.f - limites.size.y /2.f - limites.position.y)
                        });
}

static bool textoEntraEnBarraEscritura (sfText *texto, float anchoBarraEscritura)
{
    sfFloatRect limitesTexto = sfText_getLocalBounds(texto);

    return (limitesTexto.size.x <= anchoBarraEscritura);
}

void limitarVisualizacionTextoSobreBarraEscritura (sfText *texto, const char *cadena, float anchoBarraEscritura)
{
    unsigned short int i;

    for (i = 0; i <= (strlen(cadena)); i++)
    {
        sfText_setString(texto, cadena + i);
        if (textoEntraEnBarraEscritura (texto, anchoBarraEscritura))
            return;
    }
}

void omitirEventosPendientes (sfRenderWindow *renderizado)
{
    sfEvent evento;
    while (sfRenderWindow_pollEvent (renderizado, &evento)){continue;}
}


/* ============================================================================================================================================
   FUNCIONES DE ESCRITURA
   ============================================================================================================================================ */


static bool noEsCaracterImprimible (char caracter)
{
    return ((caracter < 32) || (caracter > 126));
}

static bool noEsBackspace (char caracter)
{
    return (caracter != 8);
}

static void agregarCaracterAlBuffer (char *buffer, char caracter, int largoBuffer)
{
    buffer [largoBuffer] = caracter;
    buffer [largoBuffer + 1] = '\0';
}

static void eliminarUltimoCaracter (char *buffer, int largoBuffer)
{
    buffer [largoBuffer - 1] = '\0';
}

t_codigoRetorno ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar)
{
    int largoBuffer;
    char caracter = (char)eventoChar.text.unicode;

    if (noEsCaracterImprimible (caracter) && noEsBackspace (caracter))
        return ERROR_OPERACION;

    // Se utiliza largoBuffer y se envia como argumento para evitar calcularlo multiples veces.
    largoBuffer = strlen (buffer);

    if (noEsBackspace (caracter))
    {
        if (largoBuffer < tamMaxBuffer - 1) // tamMaxBuffer - 1 para asegurar el '\0' al final del buffer.
            agregarCaracterAlBuffer (buffer, caracter, largoBuffer);
    }
    else if (largoBuffer > 0) // Si el caracter es "Backspace" y el buffer no esta vacio.
        eliminarUltimoCaracter (buffer, largoBuffer);

    return EXITO;
}

t_codigoRetorno pegarTextoDesdePortapapelesABuffer (char *buffer, int tamMaxBuffer)
{
    const uint32_t *texto, *pTexto;
    int largoBuffer, espacioDisponibleEnBuffer, largoTextoPortapapeles = 0;

    texto = sfClipboard_getUnicodeString ();
    pTexto = texto;

    largoBuffer = strlen (buffer);
    espacioDisponibleEnBuffer = tamMaxBuffer - largoBuffer - 1; // -1 para asegurar el '\0' al final del buffer.

    while (*pTexto != 0)
    {
        if (noEsCaracterImprimible ((char)(*pTexto)))
            return ERROR_OPERACION;
        largoTextoPortapapeles ++;
        pTexto ++;
    }

    if (largoTextoPortapapeles > espacioDisponibleEnBuffer)
        return ERROR_OPERACION;

    pTexto = texto;
    buffer = buffer + largoBuffer;
    while (*pTexto != 0)
    {
        *buffer = (char)(*pTexto);
        buffer ++;
        pTexto ++;
    }
    *buffer = '\0';

    return EXITO;
}

bool sonTodosEspacios (const char *mensaje)
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


bool esNombreValido (const char *nombre)
{
    int largoNombre = strlen (nombre);

    return (((largoNombre >= 3) && (largoNombre < MAX_NOMBRE_USUARIO)) && (!sonTodosEspacios (nombre)));
}

bool esContraseniaValida (const char *contrasenia)
{
    int largoContrasenia = strlen (contrasenia);

    return (((largoContrasenia >= 8) && (largoContrasenia < MAX_CONTRASENIA)) && (!sonTodosEspacios (contrasenia)));
}

bool esCorreoElectronicoValido (const char *correo)
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


void resetearPuntoInsercion (t_puntoInsercion *puntoInsercion)
{
    puntoInsercion->estado = DESHABILITADO;
    puntoInsercion->contador = CONTADOR_REINICIAR;
}

bool puntoInsercionHabilitado (const t_puntoInsercion *puntoInsercion)
{
    if (puntoInsercion->estado == HABILITADO)
        return 1;
    return 0;
}

void actualizarPuntoInsercion (t_puntoInsercion *puntoInsercion)
{
    puntoInsercion->contador ++;
    if (puntoInsercion->contador >= VELOCIDAD_PARPADEO_PUNTO_INSERCION)
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


void textoDeCarga_iniciar (t_textoDeCarga *textoDeCarga)
{
    textoDeCarga->estado = TEXTO_DE_CARGA_ESTADO_INICIAL;
    textoDeCarga->contador = CONTADOR_REINICIAR;
}

bool textoDeCarga_actualizar (t_textoDeCarga *textoDeCarga)
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

void textoDeCarga_modificarTextoSegunEstado (t_textoDeCarga *textoDeCarga, char *texto)
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

void log_warning_respuestaRecibidaDeOtraInterfaz ()
{
    puts ("\nWARNING - La respuesta recibida del servidor no corresponde a la interfaz sobre la que esta situado el usuario.");
}
