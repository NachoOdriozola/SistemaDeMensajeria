#include "../include/utiles.h"



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

    return sfFloatRect_contains (&limiteRectangulo, mouseMundo.x, mouseMundo.y);
}

bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteTexto;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, mouseMundo.x, mouseMundo.y);
}

void centrarTextoEnArea (sfText *texto, float posXInicial, float posYInicial, float anchoArea, float altoArea)
{
    sfFloatRect limites;

    limites = sfText_getLocalBounds(texto);

    sfText_setPosition (texto, (sfVector2f)
                        {
                            round (posXInicial + anchoArea / 2.f - limites.width / 2.f - limites.left),
                            round (posYInicial + altoArea / 2.f - limites.height /2.f - limites.top)
                        });
}

void limitarVisualizarTextoSobreBarra (sfText *texto, const char *bufferTexto, float anchoBarra)
{
    unsigned short int i;
    sfFloatRect limites;

    sfText_setString(texto, bufferTexto);
    limites = sfText_getLocalBounds(texto);

    if (limites.width <= anchoBarra) // Si el texto entra en la barra de escritura.
        return;

    for (i = 1; i <= (strlen(bufferTexto)); i++)
    {
        sfText_setString(texto, bufferTexto + i);
        limites = sfText_getLocalBounds(texto);
        if (limites.width <= anchoBarra)
            return;
    }
}



/* ============================================================================================================================================
   FUNCIONES DE ESCRITURA
   ============================================================================================================================================ */



int ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar)
{
    int largoBuffer;
    char caracter = (char)eventoChar.text.unicode;


    if ((caracter != 8) && ((caracter < 32) || (caracter > 126))) // Si es un caracter de control, o que no sea ASCII 1 Byte o que no sea el "Backspace".
        return CARACTER_INVALIDO;

    largoBuffer = strlen (buffer);

    if (caracter != 8) // Si el caracter no es "Backspace".
    {
        if (largoBuffer < tamMaxBuffer - 1)
        {
            buffer [largoBuffer] = caracter;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    else if (largoBuffer > 0) // Si el caracter es "Backspace" y el buffer no esta vacio.
        buffer [largoBuffer - 1] = '\0';

    return 0;
}

int pegarDesdePortapapeles (char *buffer, int tamMaxBuffer)
{
    const sfUint32 *texto, *pTexto;
    int largoTexto = 0, espacioDisponible;

    texto = sfClipboard_getUnicodeString ();
    pTexto = texto;

    espacioDisponible = tamMaxBuffer - 1 - strlen (buffer);

    while (*pTexto != 0)
    {
        if (*pTexto < 32 || *pTexto > 126)
            return CARACTER_INVALIDO;
        largoTexto ++;
        pTexto ++;
    }

    if (largoTexto > espacioDisponible)
        return 1;

    pTexto = texto;
    buffer = buffer + strlen (buffer);
    while (*pTexto != 0)
    {
        *buffer = (char)(*pTexto);
        buffer ++;
        pTexto ++;
    }
    *buffer = '\0';

    return 0;
}



/* ============================================================================================================================================
   FUNCIONES DE PUNTO DE INSERCION
   ============================================================================================================================================ */



void resetearPuntoInsercion (t_puntoInsercion *puntoInsercion)
{
    puntoInsercion->estado = DESHABILITADO;
    puntoInsercion->contador = REINICIAR_CONTADOR_PUNTO_INSERCION;
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
        puntoInsercion->contador = REINICIAR_CONTADOR_PUNTO_INSERCION;
        if (puntoInsercion->estado == DESHABILITADO)
            puntoInsercion->estado = HABILITADO;
        else
            puntoInsercion->estado = DESHABILITADO;
    }
}



























