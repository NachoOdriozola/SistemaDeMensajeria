#include "../include/utiles.h"



/* ============================
   FUNCIONES DE SOCKETS
   ============================ */



bool recibirRespuesta (SOCKET sock, char *bufferRespuesta, int tamMaxBufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = recv (sock, bufferRespuesta, tamMaxBufferRespuesta, 0);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos;
        *bufferRespuesta = '\0';
        return RECIBIO_RESPUESTA;
    }

    return NO_RECIBIO_RESPUESTA;
}

void enviarSolicitudYRecibirRespuesta (SOCKET sock, const char *bufferSolicitud, char *bufferRespuesta, int tamMaxBufferRespuesta)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    int bytesRecibidos;

    ioctlsocket (sock, FIONBIO, &modoSocket);
    send (sock, bufferSolicitud, strlen (bufferSolicitud), 0);
    bytesRecibidos = recv (sock, bufferRespuesta, tamMaxBufferRespuesta, 0);
    bufferRespuesta += bytesRecibidos;
    *bufferRespuesta = '\0';
    modoSocket = 1;     // Socket modo no bloqueante
    ioctlsocket (sock, FIONBIO, &modoSocket);
}




/* ============================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================ */



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

    if (limites.width <= anchoBarra)
        return;

    for (i = 0; i < (strlen(bufferTexto)); i++)
    {
        sfText_setString(texto, bufferTexto + i);
        limites = sfText_getLocalBounds(texto);
        if (limites.width <= anchoBarra)
            break;
    }
}



/* ============================
   FUNCIONES DE ESCRITURA
   ============================ */



void ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar)
{
    int largoBuffer;

    largoBuffer = strlen (buffer);

    if (eventoChar.text.unicode == 13) // Si la tecla es "Enter" retorna.
        return;

    if (eventoChar.text.unicode != 8) //Si la tecla no es "Backspace".
    {
        if (largoBuffer < tamMaxBuffer - 1)
        {
            buffer [largoBuffer] = (char)eventoChar.text.unicode;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    else if (largoBuffer > 0) // Si la tecla es "Backspace".
            buffer [largoBuffer - 1] = '\0';
}



/* ============================
   FUNCIONES DE PUNTO DE INSERCION
   ============================ */



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



























