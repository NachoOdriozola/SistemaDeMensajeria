#include "interfazMensajes.h"


///FUNCIONES ESTRUCTURALES


int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR TEXTO
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Crear fuente para recursos graficos de mensajes.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.auxTexto = sfText_create ();
    if (!recursosGraficosMensajes->texto.auxTexto)
    {
        perror ("ERROR - Crear texto temporal.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.usuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->texto.usuariosActivos)
    {
        perror ("ERROR - Crear texto auxiliar usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosMensajes->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosMensajes->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Crear texto para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }



    ///INICIALIZAR ELEMENTOS
    recursosGraficosMensajes->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.recIzquierda)
    {
        perror ("ERROR - Crear rectangulo de la izquierda.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Crear barra de separacion de usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Crear barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Crear barra de ingresar mensaje.\n");
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

void setupMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///SETUP ESCRITURA
    recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosMensajes->bufferEscribirMensaje) = '\0';


    ///SETUP TEXTO
    //Texto auxiliar
    sfText_setFont (recursosGraficosMensajes->texto.auxTexto, recursosGraficosMensajes->texto.fuente);

    //Texto auxiliar usuarios activos
    sfText_setFont (recursosGraficosMensajes->texto.usuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.usuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.usuariosActivos, sfColor_fromRGB (34, 48, 48));

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosMensajes->texto.nombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir mensaje
    sfText_setFont (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));


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
    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), recursosGraficosMensajes->texto.fuente, setupListaMensajes);
    recursosGraficosMensajes->siguienteMensaje = recursosGraficosMensajes->listaMensajes;
}

void TamYPosPantallaMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///SETUP POS Y TAM TEXTO
    //Texto usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.usuariosActivos, (sfVector2f){62 * app->ventana.escalaElementos.x, 45 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.usuariosActivos, 36 * app->ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.nombreUsuario, (sfVector2f){35 * app->ventana.escalaElementos.x, 925 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.nombreUsuario, 36 * app->ventana.escalaPixeles);

    //Texto para escribir mensaje
    sfText_setPosition (recursosGraficosMensajes->texto.auxEscribirMensaje, (sfVector2f){500 * app->ventana.escalaElementos.x, 912 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxEscribirMensaje, 26 * app->ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){300 * app->ventana.escalaElementos.x, 1009 * app->ventana.escalaElementos.y});

    //Barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){24 * app->ventana.escalaElementos.x, 120 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){24 * app->ventana.escalaElementos.x, 888 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){480 * app->ventana.escalaElementos.x, 909 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){1200 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});


    ///SETUP TAM MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), &(app->ventana.escalaPixeles), tamListaMensajes);
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;
    s_paqueteMensaje paqueteMensaje;
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
        app->ventana.tamActualPantalla = nuevoTamPantalla;
        ajustarVista (app, nuevoTamPantalla);
        break;

    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnRectangulo (app->renderizado, recursosGraficosMensajes->elementos.barraIngresarMensaje))
                recursosGraficosMensajes->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.text.unicode < 128) &&
            (evento.text.unicode != 13) && //Detecta que no sea la tecla "Enter"
            ((largoBufferMensaje = strlen(recursosGraficosMensajes->bufferEscribirMensaje)) < MAX_BUFFER_MENSAJE - 1))
        {
            if (evento.text.unicode != 8) //Detecta que no sea la tecla "Backspace"
            {
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje] = (char)evento.text.unicode;
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje + 1] = '\0';
            }
            else if (largoBufferMensaje > 0)
                recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje - 1] = '\0';
        }

        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.text.unicode == 8) && //Detecta que sea la tecla "Backspace"
            (largoBufferMensaje == MAX_BUFFER_MENSAJE - 1)) //Es el ultimo espacio
        {
            recursosGraficosMensajes->bufferEscribirMensaje [largoBufferMensaje - 1] = '\0';
        }

        sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (strlen (recursosGraficosMensajes->bufferEscribirMensaje) > 0))
        {
            strcpy (paqueteMensaje.nombreUsuario, app->usuario.nombreUsuario);
            paqueteMensaje.nombreUsuario [MAX_NOMBRE_USUARIO] = '\0';
            strcpy (paqueteMensaje.bufferMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
            paqueteMensaje.bufferMensaje [MAX_BUFFER_MENSAJE] = '\0';
            send (sock->sock, (char*)(&paqueteMensaje), sizeof (s_paqueteMensaje), 0);
            asignarMensaje (app, recursosGraficosMensajes, recursosGraficosMensajes->bufferEscribirMensaje, MI_USUARIO);
            *(recursosGraficosMensajes->bufferEscribirMensaje) = '\0';
            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
        }
        break;

    default:
        break;
    }
}

void actualizarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    s_paqueteMensaje paqueteMensaje;

    if (recibirMensajeCompleto (sock->sock, (char*)(&paqueteMensaje), sizeof (s_paqueteMensaje)) == sizeof (s_paqueteMensaje))
    {
        puts (paqueteMensaje.nombreUsuario);
        puts (paqueteMensaje.bufferMensaje);
    }

    //asignarMensaje (app, recursosGraficosMensajes, bufferMensaje, OTRO_USUARIO);

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
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.usuariosActivos, NULL);
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
    sfText_destroy (recursosGraficosMensajes->texto.auxTexto);
    sfText_destroy (recursosGraficosMensajes->texto.usuariosActivos);
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


int recibirMensajeCompleto (SOCKET sock, char *buffer, int tamBytesMensaje)
{
    int bytesTotalRecibidos = 0, bytesRecibidos;

    while (bytesTotalRecibidos < tamBytesMensaje)
    {
        bytesRecibidos = recv (sock, buffer + bytesTotalRecibidos, tamBytesMensaje - bytesTotalRecibidos, 0);
        if (bytesRecibidos < 0)
            return 1; //Error o conexion fallida
        bytesTotalRecibidos += bytesRecibidos;
    }

    return bytesTotalRecibidos;
}


void asignarMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, const char *bufferMensaje, bool enviadoPor)
{
    s_mensaje *mensaje;

    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), &(app->ventana.escalaPixeles), modificarPosicionListaMensajes);
    mensaje = recursosGraficosMensajes->siguienteMensaje->dato;
    sfText_setString (mensaje->mensaje, bufferMensaje);
    if (enviadoPor == MI_USUARIO)
        mensaje->posicionMensaje = (sfVector2f){1260 * app->ventana.escalaElementos.x, 827 * app->ventana.escalaElementos.y};
    else
        mensaje->posicionMensaje = (sfVector2f){480 * app->ventana.escalaElementos.x, 827 * app->ventana.escalaElementos.y};
    sfText_setPosition (mensaje->mensaje, mensaje->posicionMensaje);

    recursosGraficosMensajes->siguienteMensaje = recursosGraficosMensajes->siguienteMensaje->sig;
}

/*
void ajustarLargoMaxMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, char *bufferMensaje, sfVector2f posicion, unsigned int tamPixeles, float largoMax)
{
    float largoTexto, espacioActual = 0;
    unsigned longitudPalabra;
    char *ptrMensaje = bufferMensaje;

    char palabraActual [101] = '\0';
    char mensajeFinal [1024] = '\0';

    sfText_setPosition (recursosGraficosMensajes->texto.auxTexto, posicion);
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxTexto, tamPixeles * app->ventana.escalaPixeles);

    while (*ptrMensaje != '\0')
    {

    }
}
*/

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

void modificarPosicionListaMensajes (void *mensaje, void *escalaPixeles)
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






































