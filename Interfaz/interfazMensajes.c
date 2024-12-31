#include "interfazMensajes.h"

int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR TEXTO
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.mensajeRecibido = sfText_create ();
    if (!recursosGraficosMensajes->texto.mensajeRecibido)
    {
        perror ("ERROR - Inicializar texto de mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.mensajeEnviado = sfText_create ();
    if (!recursosGraficosMensajes->texto.mensajeEnviado)
    {
        perror ("ERROR - Inicializar texto para mensaje enviado.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.auxUsuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->texto.auxUsuariosActivos)
    {
        perror ("ERROR - Inicializar texto auxiliar usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosMensajes->texto.nombreUsuario)
    {
        perror ("ERROR - Inicializar texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosMensajes->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Inicializar texto para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }



    ///INICIALIZAR ELEMENTOS
    recursosGraficosMensajes->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.recIzquierda)
    {
        perror ("ERROR - Inicializar rectangulo de la izquierda.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Inicializar barra de separacion de usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Inicializar barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Inicializar barra de ingresar mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return CONTINUAR_APLICACION;
}

void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///HABILITAR ESCRITURA
    recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosMensajes->bufferMensaje) = '\0';



    ///SETUP TEXTO
    //texto de mensajes recibidos
    sfText_setFont (recursosGraficosMensajes->texto.mensajeRecibido, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.mensajeRecibido, sfColor_fromRGB (0, 0, 0));

    //texto de mensaje enviado
    sfText_setFont (recursosGraficosMensajes->texto.mensajeEnviado, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.mensajeEnviado, sfColor_fromRGB (34, 48, 48));

    //texto auxiliar usuarios activos
    sfText_setFont (recursosGraficosMensajes->texto.auxUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.auxUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.auxUsuariosActivos, sfColor_fromRGB (34, 48, 48));

    //texto nombre de usuario
    sfText_setFont (recursosGraficosMensajes->texto.nombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.nombreUsuario, "mi usuario");
    sfText_setColor (recursosGraficosMensajes->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //texto para escribir mensaje
    sfText_setFont (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, "Ingrese mensaje...");
    sfText_setColor (recursosGraficosMensajes->texto.auxEscribirMensaje, sfColor_fromRGB (255, 255, 255));



    ///SETUP ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));

    //barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;

    sfRenderWindow_pollEvent (app->renderizado, &evento);
    switch (evento.type)
    {
    case sfEvtClosed:
        app->estado = CERRAR_APLICACION;
        break;

    case sfEvtResized:
        nuevoTamPantalla.x = evento.size.width;
        nuevoTamPantalla.y = evento.size.height;
        modificarTamPantalla (app, recursosGraficosMensajes, nuevoTamPantalla);
        break;

    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnEscribirMensaje (app, recursosGraficosMensajes))
                recursosGraficosMensajes->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128) && (evento.text.unicode != '\n') && (strlen(recursosGraficosMensajes->bufferMensaje) < MAX_BUFFER - 1))
        {
            int largoBufferMensaje;
            largoBufferMensaje = strlen (recursosGraficosMensajes->bufferMensaje);
            if (evento.text.unicode != '\b')
            {
                recursosGraficosMensajes->bufferMensaje [largoBufferMensaje] = (char)evento.text.unicode;
                recursosGraficosMensajes->bufferMensaje [largoBufferMensaje + 1] = '\0';
            }
            else if (largoBufferMensaje > 0)
                recursosGraficosMensajes->bufferMensaje [largoBufferMensaje - 1] = '\0';

            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferMensaje);
        }
        break;

    case sfEvtKeyPressed:
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.key.code == sfKeyEnter) && (strlen (recursosGraficosMensajes->bufferMensaje) > 0))
        {
            send (sock->sock, recursosGraficosMensajes->bufferMensaje, MAX_BUFFER, 0);
            sfText_setString (recursosGraficosMensajes->texto.mensajeEnviado, recursosGraficosMensajes->bufferMensaje);
            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, "Ingrese mensaje...");
            recursosGraficosMensajes->bufferMensaje [0] = '\0';
        }

    default:
        break;
    }
}

void actualizarMensajes (s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    char buffer [MAX_BUFFER];
    int bytesRecibidos;

    bytesRecibidos = recv (sock->sock, buffer, MAX_BUFFER - 1, 0);
    if (bytesRecibidos > 0)
    {
        buffer [bytesRecibidos] = '\0';
        sfText_setString (recursosGraficosMensajes->texto.mensajeRecibido, buffer);
    }
}

void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.mensajeRecibido, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.mensajeEnviado, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.auxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.auxEscribirMensaje, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosMensajes->texto.fuente);
    sfText_destroy (recursosGraficosMensajes->texto.mensajeRecibido);
    sfText_destroy (recursosGraficosMensajes->texto.mensajeEnviado);
    sfText_destroy (recursosGraficosMensajes->texto.auxUsuariosActivos);
    sfText_destroy (recursosGraficosMensajes->texto.nombreUsuario);
    sfText_destroy (recursosGraficosMensajes->texto.auxEscribirMensaje);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraIngresarMensaje);
}

void modificarTamPantalla (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2f nuevoTamPantalla)
{
    //TAM REAL 1920 1009
    sfView *nuevaVistaPantalla;
    sfVector2f centroPantalla;
    float escala;

    nuevaVistaPantalla = sfView_create ();
    if (!nuevaVistaPantalla)
    {
        perror ("ERROR - Inicializar nueva vista de pantalla.\n");
        app->estado = CERRAR_APLICACION;
        return;
    }

    sfView_setSize (nuevaVistaPantalla, nuevoTamPantalla);
    centroPantalla.x = nuevoTamPantalla.x / 2.0f;
    centroPantalla.y = nuevoTamPantalla.y / 2.0f;
    escala = sqrt ((nuevoTamPantalla.x * nuevoTamPantalla.y) / (app->tamOriginalPantalla.x * app->tamOriginalPantalla.y));
    sfView_setCenter(nuevaVistaPantalla, centroPantalla);
    sfRenderWindow_setView (app->renderizado, nuevaVistaPantalla);

    ///MODIFICAR TAM TEXTO
    //texto de mensajes recibidos
    sfText_setPosition (recursosGraficosMensajes->texto.mensajeRecibido, centroPantalla);
    sfText_setCharacterSize (recursosGraficosMensajes->texto.mensajeRecibido, 44 * escala);

    //texto auxiliar usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.auxUsuariosActivos, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 20.18});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxUsuariosActivos, 28 * escala);

    //texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.nombreUsuario, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 1.08});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.nombreUsuario, 28 * escala);

    //texto para escribir mensaje
    sfText_setPosition (recursosGraficosMensajes->texto.auxEscribirMensaje, (sfVector2f){nuevoTamPantalla.x / 3.84, nuevoTamPantalla.y / 1.103});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxEscribirMensaje, 24 * escala);

    //texto para mensaje enviado
    sfText_setPosition (recursosGraficosMensajes->texto.mensajeEnviado, (sfVector2f){nuevoTamPantalla.x / 1.37, nuevoTamPantalla.y / 1.26});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.mensajeEnviado, 34 * escala);


    ///MODIFICAR TAM ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){nuevoTamPantalla.x / 6.4, nuevoTamPantalla.y});

    //barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 8.4});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 1.13});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 4, nuevoTamPantalla.y / 1.11});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 1.6, nuevoTamPantalla.y / 24});


    ///LIBERAR RECURSOS
    sfView_destroy (nuevaVistaPantalla);
}

bool clickEnEscribirMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (app->renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (recursosGraficosMensajes->elementos.barraIngresarMensaje);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}










































