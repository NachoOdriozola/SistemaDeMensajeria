#include "utiles.h"


///FUNCIONES UTILES


void ajustarVista (s_aplicacion *app, sfVector2f nuevoTamPantalla)
{
    sfView *nuevaVista;

    nuevaVista = sfView_create ();
    if (!nuevaVista)
    {
        perror ("ERROR - Crear nueva vista para redimensionar ventana.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
        return;
    }

    sfView_setSize (nuevaVista, nuevoTamPantalla);
    sfView_setCenter (nuevaVista, (sfVector2f){nuevoTamPantalla.x / 2.0f, nuevoTamPantalla.y / 2.0f});
    sfRenderWindow_setView (app->renderizado, nuevaVista);

    sfView_destroy (nuevaVista);
}

bool clickEnRectangulo (sfRenderWindow *renderizado, sfRectangleShape *rectangulo)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}

bool clickEnTexto (sfRenderWindow *renderizado, sfText *texto)
{
    sfVector2i posMouse;
    sfFloatRect limiteTexto;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, posMouse.x, posMouse.y);
}

void ingresoTexto (char *buffer, int maxIngreso, sfEvent evento)
{
    int largoBuffer;

    largoBuffer = strlen (buffer);

    if ((evento.text.unicode != 13) && (evento.text.unicode != 8)) //Detecta que no sea la tecla "Enter" ni "Backspace"
    {
        if (largoBuffer < maxIngreso)
        {
            buffer [largoBuffer] = (char)evento.text.unicode;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    else if ((evento.text.unicode == 8) && (largoBuffer > 0)) //Detecta que sea la tecla "Backspace"
        buffer [largoBuffer - 1] = '\0';
}

void enviarSolicitudUsuario (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta)
{
    char bufferSolicitudLocal [MAX_BUFFER_SOLICITUD];
    char bufferRespuestaLocal [MAX_BUFFER_RESPUESTA];

    send (sock, bufferSolicitud, sizeof (bufferSolicitudLocal), 0);
    recv (sock, bufferRespuesta, sizeof (bufferRespuestaLocal), 0);
}

void asignarMensaje (s_aplicacion *app, const char *bufferMensaje, bool enviadoPor)
{
    s_mensaje *mensaje;
    sfFloatRect bordesMensaje;

    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), &(app->ventana.escalaPixeles), modificarPosListaMensajes);
    mensaje = app->mensajes.siguienteMensaje->dato;
    sfText_setString (mensaje->mensaje, bufferMensaje);
    if (enviadoPor == MI_USUARIO)
    {
        bordesMensaje = sfText_getLocalBounds (mensaje->mensaje);
        mensaje->posMensaje = (sfVector2f){(1780 * app->ventana.escalaElementos.x) - bordesMensaje.width, 827 * app->ventana.escalaElementos.y};
    }
    else
    {
        mensaje->posMensaje = (sfVector2f){510 * app->ventana.escalaElementos.x, 827 * app->ventana.escalaElementos.y};
    }
    sfText_setPosition (mensaje->mensaje, mensaje->posMensaje);

    app->mensajes.siguienteMensaje = app->mensajes.siguienteMensaje->sig;
}

void modificarPosListaMensajes (void *mensaje, void *escalaPixeles)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    float y = *(float*)escalaPixeles;

    x->posMensaje.y -= 80 * y;
    sfText_setPosition (x->mensaje, x->posMensaje);
}

void renderizarListaMensajes (void *mensaje, void *renderizado)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfRenderWindow *y = (sfRenderWindow*)renderizado;

    sfRenderWindow_drawText (y, x->mensaje, NULL);
}





















