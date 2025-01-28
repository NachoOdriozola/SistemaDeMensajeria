#include "interfazAmigos.h"


///FUNCIONES ESTRUCTURALES


int inicializarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///INICIALIZAR TEXTO
    recursosGraficosAmigos->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosAmigos->texto.fuente)
    {
        perror ("ERROR - Crear fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.textoUsuariosActivos = sfText_create ();
    if (!recursosGraficosAmigos->texto.textoUsuariosActivos)
    {
        perror ("ERROR - Crear texto usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosAmigos->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosAmigos->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Crear texto auxiliar para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosAmigos->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.recIzquierda)
    {
        perror ("ERROR - Crear rectangulo de la izquierda.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Crear barra de separacion de usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Crear barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Crear barra para ingresar mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.rectanguloSalas = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloSalas)
    {
        perror ("ERROR - Crear rectangulo para ir a las salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.rectanguloConfig = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloConfig)
    {
        perror ("ERROR - Crear rectangulo para ir a la config.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR LISTA DE MENASJES
    unsigned short int i;
    s_mensaje mensajes [MAX_MENSAJES_EN_MEM], *ptrMensaje = mensajes;

    crearListaCircular (&(recursosGraficosAmigos->listaMensajes));
    for (i = 0; i < MAX_MENSAJES_EN_MEM; i ++)
    {
        ptrMensaje->mensaje = sfText_create ();
        insertarSegundoCircular (&(recursosGraficosAmigos->listaMensajes), ptrMensaje, sizeof (s_mensaje));
        ptrMensaje ++;
    }


    return OK;
}

void setupAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///SETUP ESCRITURA
    recursosGraficosAmigos->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosAmigos->bufferEscribirMensaje) = '\0';


    ///SETUP TEXTO
    //Texto usuarios activos
    sfText_setFont (recursosGraficosAmigos->texto.textoUsuariosActivos, recursosGraficosAmigos->texto.fuente);
    sfText_setString (recursosGraficosAmigos->texto.textoUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosAmigos->texto.textoUsuariosActivos, sfColor_fromRGB (34, 48, 48));

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosAmigos->texto.nombreUsuario, recursosGraficosAmigos->texto.fuente);
    sfText_setColor (recursosGraficosAmigos->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir mensaje
    sfText_setFont (recursosGraficosAmigos->texto.auxEscribirMensaje, recursosGraficosAmigos->texto.fuente);
    sfText_setColor (recursosGraficosAmigos->texto.auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));


    ///SETUP ELEMENTOS
    //Rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));

    //Barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //Barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //Barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));

    //Rectangulo para ir a las salas
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloSalas, sfColor_fromRGB (0, 0, 0));

    //Rectangulo para ir a las config
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloConfig, sfColor_fromRGB (0, 150, 150));


    ///SETUP MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosAmigos->listaMensajes), recursosGraficosAmigos->texto.fuente, setupListaMensajes);
    recursosGraficosAmigos->siguienteMensaje = recursosGraficosAmigos->listaMensajes;
}

void TamYPosPantallaAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///SETUP POS Y TAM TEXTO
    //Texto usuarios activos
    sfText_setPosition (recursosGraficosAmigos->texto.textoUsuariosActivos, (sfVector2f){62 * app->ventana.escalaElementos.x, 45 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.textoUsuariosActivos, 36 * app->ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosAmigos->texto.nombreUsuario, (sfVector2f){35 * app->ventana.escalaElementos.x, 925 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.nombreUsuario, 36 * app->ventana.escalaPixeles);

    //Texto auxiliar para escribir mensaje
    sfText_setPosition (recursosGraficosAmigos->texto.auxEscribirMensaje, (sfVector2f){450 * app->ventana.escalaElementos.x, 912 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.auxEscribirMensaje, 26 * app->ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.recIzquierda, (sfVector2f){300 * app->ventana.escalaElementos.x, 1009 * app->ventana.escalaElementos.y});

    //Barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, (sfVector2f){24 * app->ventana.escalaElementos.x, 120 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){24 * app->ventana.escalaElementos.x, 888 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){430 * app->ventana.escalaElementos.x, 909 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){1350 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});

    //Rectangulo para ir a las salas
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){150 * app->ventana.escalaElementos.x, 500 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){60 * app->ventana.escalaElementos.x, 60 * app->ventana.escalaElementos.y});

    //Rectangulo para ir a las config
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloConfig, (sfVector2f){150 * app->ventana.escalaElementos.x, 650 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloConfig, (sfVector2f){60 * app->ventana.escalaElementos.x, 60 * app->ventana.escalaElementos.y});


    ///SETUP TAM MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosAmigos->listaMensajes), &(app->ventana.escalaPixeles), tamListaMensajes);
}

void accionAmigos (s_aplicacion *app, s_socket *sock, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;


    sfRenderWindow_pollEvent (app->renderizado, &evento);
    switch (evento.type)
    {
    case sfEvtClosed:
        app->aplicacionEjecutandose = CERRAR_APLICACION;
        break;

    case sfEvtResized:
        nuevoTamPantalla.x = evento.size.width;
        nuevoTamPantalla.y = evento.size.height;
        app->ventana.tamActualPantalla = nuevoTamPantalla;
        ajustarVista (app, nuevoTamPantalla);
        break;

    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje))
                recursosGraficosAmigos->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosAmigos->habilitarEscritura = DESHABILITAR_ESCRITURA;


            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas))
                app->interfaz = INTERFAZ_SALAS;

            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.rectanguloConfig))
                app->interfaz = INTERFAZ_CONFIG;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosAmigos->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosAmigos->bufferEscribirMensaje, MAX_BUFFER_MENSAJE - 5, evento);
            sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, recursosGraficosAmigos->bufferEscribirMensaje);
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosAmigos->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (strlen (recursosGraficosAmigos->bufferEscribirMensaje) > 0))
        {
            enviarPaqueteMensaje (app, sock->sock, recursosGraficosAmigos);
        }
        break;

    default:
        break;
    }
}

void actualizarAmigos (s_aplicacion *app, s_socket *sock, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    int bytesRecibidos;
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE];

    bytesRecibidos = recv (sock->sock, bufferPaquete, sizeof (bufferPaquete), 0);
    if (bytesRecibidos > 0)
    {
        bufferPaquete [bytesRecibidos] = '\0';
        asignarMensaje (app, recursosGraficosAmigos, bufferPaquete, OTRO_USUARIO);
    }


    ///TEXTO AUXILIAR ESCRIBIR MENSAJE
    if ((recursosGraficosAmigos->habilitarEscritura == DESHABILITAR_ESCRITURA) && ((strlen (recursosGraficosAmigos->bufferEscribirMensaje) == 0)))
        sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, "Escribir mensaje...");
}

void renderizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloConfig, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.textoUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.auxEscribirMensaje, NULL);


    ///RENDERIZAR LISTA DE MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosAmigos->listaMensajes), app->renderizado, renderizarListaMensajes);


    sfRenderWindow_display (app->renderizado);
}

void liberarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosAmigos->texto.fuente);
    sfText_destroy (recursosGraficosAmigos->texto.textoUsuariosActivos);
    sfText_destroy (recursosGraficosAmigos->texto.nombreUsuario);
    sfText_destroy (recursosGraficosAmigos->texto.auxEscribirMensaje);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraIngresarMensaje);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloSalas);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloConfig);


    ///LIBERAR MENSAJES
    vaciarListaCircularConAccion (&(recursosGraficosAmigos->listaMensajes), liberarMensaje);
}


///FUNCIONES LOGICAS


void enviarPaqueteMensaje (s_aplicacion *app, SOCKET sock, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE], *ptrBufferPaquete = bufferPaquete;

    //Asigna el mensaje a la lista de mensajes para el renderizado
    asignarMensaje (app, recursosGraficosAmigos, recursosGraficosAmigos->bufferEscribirMensaje, MI_USUARIO);

    //Logica para enviar el paquete del mensaje
    strcpy (ptrBufferPaquete, app->usuario.nombreUsuario);
    ptrBufferPaquete += strlen (ptrBufferPaquete);
    *ptrBufferPaquete = '\n';
    ptrBufferPaquete ++;
    strcpy (ptrBufferPaquete, recursosGraficosAmigos->bufferEscribirMensaje);
    send (sock, bufferPaquete, sizeof (bufferPaquete), 0);

    //Pone el texto auxiliar para escribir un nuevo mensaje de 0
    *(recursosGraficosAmigos->bufferEscribirMensaje) = '\0';
    sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, recursosGraficosAmigos->bufferEscribirMensaje);
}

void asignarMensaje (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos, const char *bufferMensaje, bool enviadoPor)
{
    s_mensaje *mensaje;
    sfFloatRect bordesMensaje;

    mapListaCircularConComplemento (&(recursosGraficosAmigos->listaMensajes), &(app->ventana.escalaPixeles), modificarPosListaMensajes);
    mensaje = recursosGraficosAmigos->siguienteMensaje->dato;
    sfText_setString (mensaje->mensaje, bufferMensaje);
    if (enviadoPor == MI_USUARIO)
    {
        bordesMensaje = sfText_getLocalBounds (mensaje->mensaje);
        mensaje->posicionMensaje = (sfVector2f){(1780 * app->ventana.escalaElementos.x) - bordesMensaje.width, 827 * app->ventana.escalaElementos.y};
    }
    else
    {
        mensaje->posicionMensaje = (sfVector2f){430 * app->ventana.escalaElementos.x, 827 * app->ventana.escalaElementos.y};
    }
    sfText_setPosition (mensaje->mensaje, mensaje->posicionMensaje);

    recursosGraficosAmigos->siguienteMensaje = recursosGraficosAmigos->siguienteMensaje->sig;
}


///FUNCIONES COMPLEMENTARIAS


void setupListaMensajes (void *mensaje, void *fuente)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfFont *y = (sfFont*)fuente;

    sfText_setFont (x->mensaje, y);
    sfText_setColor (x->mensaje, sfColor_fromRGB (34, 48, 48));
}

void tamListaMensajes (void *mensaje, void *escalaPixeles)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    float y = *(float*)escalaPixeles;

    sfText_setCharacterSize (x->mensaje, 26 * y);
}

void modificarPosListaMensajes (void *mensaje, void *escalaPixeles)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    float y = *(float*)escalaPixeles;

    x->posicionMensaje.y -= 80 * y;
    sfText_setPosition (x->mensaje, x->posicionMensaje);
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






































