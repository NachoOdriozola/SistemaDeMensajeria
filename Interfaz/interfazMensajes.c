#include "interfazMensajes.h"

///FUNCIONES ESTRUCTURALES

int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR TEXTO
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
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



    ///INICIALIZAR MENSAJES
    unsigned short int i;
    s_mensaje mensajes [MAX_MENSAJES_EN_MEM], *ptrMensaje = mensajes;

    crearListaCircular (&(recursosGraficosMensajes->listaMensajes));
    for (i = 0; i < MAX_MENSAJES_EN_MEM; i ++)
    {
        ptrMensaje->mensaje = sfText_create ();
        insertarSegundoCircular (&(recursosGraficosMensajes->listaMensajes), ptrMensaje, sizeof (s_mensaje));
        ptrMensaje ++;
    }


    return OK;
}

void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///HABILITAR ESCRITURA
    recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosMensajes->bufferEscribirMensaje) = '\0';



    ///SETUP TEXTO
    //Texto auxiliar usuarios activos
    sfText_setFont (recursosGraficosMensajes->texto.auxUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.auxUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.auxUsuariosActivos, sfColor_fromRGB (34, 48, 48));

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosMensajes->texto.nombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.nombreUsuario, "mi usuario");
    sfText_setColor (recursosGraficosMensajes->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto para escribir mensaje
    sfText_setFont (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.auxEscribirMensaje, sfColor_fromRGB (255, 255, 255));



    ///SETUP ELEMENTOS
    //Rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));

    //Barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //Barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //Barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));



    ///SETUP MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), recursosGraficosMensajes->texto.fuente, setupListaMensaje);
    recursosGraficosMensajes->siguienteMensaje = recursosGraficosMensajes->listaMensajes;
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;
    int largoBufferMensaje;


    sfRenderWindow_pollEvent (app->renderizado, &evento);
    switch (evento.type)
    {
    case sfEvtClosed:
        app->aplicacionEjecutandose = CERRAR_APLICACION;
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
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.text.unicode < 128) &&
            (evento.text.unicode != 13) && //Detecta que no sea la tecla "Enter"
            ((largoBufferMensaje = strlen(recursosGraficosMensajes->bufferEscribirMensaje)) < MAX_BUFFER - 1))
        {
            if (evento.text.unicode != 8) //Detecta que no sea la tecla "Backspace"
            {
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje] = (char)evento.text.unicode;
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje + 1] = '\0';
            }
            else if (largoBufferMensaje > 0)
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje - 1] = '\0';

            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
        }
        break;

    case sfEvtKeyPressed:
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.key.code == sfKeyEnter) &&
            (strlen (recursosGraficosMensajes->bufferEscribirMensaje) > 0))
        {
            send (sock->sock, recursosGraficosMensajes->bufferEscribirMensaje, MAX_BUFFER, 0);
            asignarMensaje (app, recursosGraficosMensajes, recursosGraficosMensajes->bufferEscribirMensaje, MI_USUARIO);
            *(recursosGraficosMensajes->bufferEscribirMensaje) = '\0';
            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
        }

    default:
        break;
    }
}

void actualizarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    char bufferMensaje [MAX_BUFFER];
    int bytesRecibidos;

    bytesRecibidos = recv (sock->sock, bufferMensaje, MAX_BUFFER - 1, 0);
    if (bytesRecibidos > 0)
    {
        bufferMensaje [bytesRecibidos] = '\0';
        asignarMensaje (app, recursosGraficosMensajes, bufferMensaje, OTRO_USUARIO);
    }


    ///TEXTO AUXILIAR ESCRIBIR MENSAJE
    if ((recursosGraficosMensajes->habilitarEscritura == DESHABILITAR_ESCRITURA) && ((strlen (recursosGraficosMensajes->bufferEscribirMensaje) == 0)))
        sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, "Escribir mensaje...");
}

void renderizarMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.auxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.auxEscribirMensaje, NULL);


    ///RENDERIZAR LISTA DE MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), app->renderizado, renderizarListaMensajes);


    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosMensajes->texto.fuente);
    sfText_destroy (recursosGraficosMensajes->texto.auxUsuariosActivos);
    sfText_destroy (recursosGraficosMensajes->texto.nombreUsuario);
    sfText_destroy (recursosGraficosMensajes->texto.auxEscribirMensaje);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraIngresarMensaje);


    ///LIBERAR MENSAJES
    vaciarListaCircularConAccion (&(recursosGraficosMensajes->listaMensajes), liberarMensaje);
}

///FUNCIONES LOGICAS

void asignarMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, const char *bufferMensaje, bool enviadoPor)
{
    s_mensaje *mensaje;

    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), &(app->ventana.escala), modificarPosicionMensajes);
    mensaje = recursosGraficosMensajes->siguienteMensaje->dato;
    sfText_setString (mensaje->mensaje, bufferMensaje);
    mensaje->posicionMensaje.y = app->ventana.tamActualPantalla.y / 1.22;
    if (enviadoPor == MI_USUARIO)
        mensaje->posicionMensaje.x = app->ventana.tamActualPantalla.x / 1.52;
    else
        mensaje->posicionMensaje.x = app->ventana.tamActualPantalla.x / 4;
    sfText_setPosition (mensaje->mensaje, mensaje->posicionMensaje);
    mensaje->enviadoPor = enviadoPor;

    recursosGraficosMensajes->siguienteMensaje = recursosGraficosMensajes->siguienteMensaje->sig;
}

void modificarTamPantalla (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2f nuevoTamPantalla)
{
    //TAM REAL 1920 X 1009
    ///PRIMER MAXIMIZADO INICIAL
    if (app->primerMaximizado == PRIMER_MAXIMIZADO)
    {
        app->ventana.tamOriginalPantalla = nuevoTamPantalla;
        app->primerMaximizado = NO_PRIMER_MAXIMIZADO;
    }


    ///AJUSTAR VISTA
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


    ///ESCALA TEXTO
    float escala;

    escala = sqrt ((nuevoTamPantalla.x * nuevoTamPantalla.y) / (app->ventana.tamOriginalPantalla.x * app->ventana.tamOriginalPantalla.y));
    app->ventana.escala = escala;


    ///MODIFICAR TAM TEXTO
    //Texto auxiliar usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.auxUsuariosActivos, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 20.18});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxUsuariosActivos, 28 * escala);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.nombreUsuario, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 1.08});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.nombreUsuario, 28 * escala);

    //Texto para escribir mensaje
    sfText_setPosition (recursosGraficosMensajes->texto.auxEscribirMensaje, (sfVector2f){nuevoTamPantalla.x / 3.84, nuevoTamPantalla.y / 1.103});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxEscribirMensaje, 24 * escala);



    ///MODIFICAR TAM ELEMENTOS
    //Rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){nuevoTamPantalla.x / 6.4, nuevoTamPantalla.y});

    //Barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 8.4});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 1.13});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 4, nuevoTamPantalla.y / 1.11});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 1.6, nuevoTamPantalla.y / 24});


    ///MODIFICAR TAM MENSAJES
    mapListaCircularConDobleComplemento (&(recursosGraficosMensajes->listaMensajes), &nuevoTamPantalla, app, modificarTamYPosMensajes);


    ///MODIFICAR TAM ACTUAL DE LA PANTALLA
    app->ventana.tamActualPantalla = nuevoTamPantalla;
}

bool clickEnEscribirMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (app->renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (recursosGraficosMensajes->elementos.barraIngresarMensaje);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}

///FUNCIONES COMPLEMENTARIAS

void setupListaMensaje (void *mensaje, void *fuente)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfFont *y = (sfFont*)fuente;

    sfText_setFont (x->mensaje, y);
    sfText_setColor (x->mensaje, sfColor_fromRGB (34, 48, 48));
}

void modificarPosicionMensajes (void *mensaje, void *escala)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    float y = *(float*)escala;

    x->posicionMensaje.y -= 70 * y;
    sfText_setPosition (x->mensaje, x->posicionMensaje);
}

void modificarTamYPosMensajes (void *mensaje, void *nuevoTamPantalla, void *app)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfVector2f y = *(sfVector2f*)nuevoTamPantalla;
    s_aplicacion *z = (s_aplicacion*)app;

    sfText_setCharacterSize (x->mensaje, 26 * z->ventana.escala);
    y.y = (y.y * x->posicionMensaje.y) / z->ventana.tamActualPantalla.y;
    if (x->enviadoPor == MI_USUARIO)
        y.x /= 1.52;
    else
        y.x /= 4;

    sfText_setPosition (x->mensaje, y);
    x->posicionMensaje = y;
}

void renderizarListaMensajes (void *mensaje, void *renderizado)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfRenderWindow *y = (sfRenderWindow*)renderizado;

    sfRenderWindow_drawText (y, x->mensaje, NULL);
}

void liberarMensaje (void *mensaje)
{
    s_mensaje *x = (s_mensaje*)mensaje;

    sfText_destroy (x->mensaje);
}






































