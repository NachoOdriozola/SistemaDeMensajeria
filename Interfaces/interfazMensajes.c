#include "interfazMensajes.h"


///FUNCIONES ESTRUCTURALES


int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR TEXTO
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Crear fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.textoUsuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->texto.textoUsuariosActivos)
    {
        perror ("ERROR - Crear texto usuarios activos.\n");
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
        perror ("ERROR - Crear texto auxiliar para escribir mensaje.\n");
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
        perror ("ERROR - Crear barra para ingresar mensaje.\n");
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
    //Texto usuarios activos
    sfText_setFont (recursosGraficosMensajes->texto.textoUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.textoUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.textoUsuariosActivos, sfColor_fromRGB (34, 48, 48));

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
    sfText_setPosition (recursosGraficosMensajes->texto.textoUsuariosActivos, (sfVector2f){62 * app->ventana.escalaElementos.x, 45 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.textoUsuariosActivos, 36 * app->ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.nombreUsuario, (sfVector2f){35 * app->ventana.escalaElementos.x, 925 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.nombreUsuario, 36 * app->ventana.escalaPixeles);

    //Texto auxiliar para escribir mensaje
    sfText_setPosition (recursosGraficosMensajes->texto.auxEscribirMensaje, (sfVector2f){450 * app->ventana.escalaElementos.x, 912 * app->ventana.escalaElementos.y});
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
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){430 * app->ventana.escalaElementos.x, 909 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){1350 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});


    ///SETUP TAM MENSAJES
    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), &(app->ventana.escalaPixeles), tamListaMensajes);
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosMensajes->elementos.barraIngresarMensaje))
                recursosGraficosMensajes->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosMensajes->habilitarEscritura = DESHABILITAR_ESCRITURA;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosMensajes->bufferEscribirMensaje, MAX_BUFFER_MENSAJE - 5, evento);
            sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosMensajes->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (strlen (recursosGraficosMensajes->bufferEscribirMensaje) > 0))
        {
            enviarPaqueteMensaje (app, sock->sock, recursosGraficosMensajes);
        }
        break;

    default:
        break;
    }
}

void actualizarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    int bytesRecibidos;
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE];

    bytesRecibidos = recv (sock->sock, bufferPaquete, sizeof (bufferPaquete), 0);
    if (bytesRecibidos > 0)
    {
        bufferPaquete [bytesRecibidos] = '\0';
        asignarMensaje (app, recursosGraficosMensajes, bufferPaquete, OTRO_USUARIO);
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
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.textoUsuariosActivos, NULL);
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
    sfText_destroy (recursosGraficosMensajes->texto.textoUsuariosActivos);
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


void enviarPaqueteMensaje (s_aplicacion *app, SOCKET sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE], *ptrBufferPaquete = bufferPaquete;

    s_mensaje *mensaje;

    mensaje = recursosGraficosMensajes->siguienteMensaje->dato;
    ajustarMensajeDerecha (recursosGraficosMensajes->bufferEscribirMensaje, mensaje->mensaje, 780 * app->ventana.escalaElementos.x);

    //Logica para enviar el paquete del mensaje
    strcpy (ptrBufferPaquete, app->usuario.nombreUsuario);
    ptrBufferPaquete += strlen (ptrBufferPaquete);
    *ptrBufferPaquete = '\n';
    ptrBufferPaquete ++;
    strcpy (ptrBufferPaquete, recursosGraficosMensajes->bufferEscribirMensaje);
    send (sock, bufferPaquete, sizeof (bufferPaquete), 0);

    //Asigna el mensaje a la lista de mensajes para el renderizado
    //asignarMensaje (app, recursosGraficosMensajes, recursosGraficosMensajes->bufferEscribirMensaje, MI_USUARIO);

    //Pone el texto auxiliar para escribir un nuevo mensaje de 0
    *(recursosGraficosMensajes->bufferEscribirMensaje) = '\0';
    sfText_setString (recursosGraficosMensajes->texto.auxEscribirMensaje, recursosGraficosMensajes->bufferEscribirMensaje);
}


void ajustarMensajeDerecha(char* mensaje, sfText* texto, float anchoMaximo)
{
    char buffer[1024] = ""; // Donde se almacenará el mensaje ajustado
    char* palabra = strtok(mensaje, " "); // Dividimos el mensaje por palabras
    char lineaActual[256] = "";

    // Iteramos sobre cada palabra del mensaje
    while (palabra != NULL) {
        char pruebaLinea[256];
        snprintf(pruebaLinea, sizeof(pruebaLinea), "%s %s", lineaActual, palabra);

        // Ajustamos temporalmente el texto para medirlo
        sfText_setString(texto, pruebaLinea);
        sfFloatRect bounds = sfText_getLocalBounds(texto);

        if (bounds.width > anchoMaximo) {
            // Si la línea supera el ancho máximo, se rompe
            strcat(buffer, lineaActual);
            strcat(buffer, "\n");
            snprintf(lineaActual, sizeof(lineaActual), "%s", palabra); // Nueva línea con la palabra que quedó fuera
        } else {
            // Si cabe, se agrega la palabra a la línea actual
            snprintf(lineaActual, sizeof(lineaActual), "%s", pruebaLinea);
        }

        palabra = strtok(NULL, " "); // Siguiente palabra
    }

    // Agregar la última línea
    strcat(buffer, lineaActual);

    // Guardar el mensaje ajustado con '\n'
    strcpy(mensaje, buffer);
}


void asignarMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, const char *bufferMensaje, bool enviadoPor)
{
    s_mensaje *mensaje;
    sfFloatRect bordesMensaje;

    mapListaCircularConComplemento (&(recursosGraficosMensajes->listaMensajes), &(app->ventana.escalaPixeles), modificarPosicionListaMensajes);
    mensaje = recursosGraficosMensajes->siguienteMensaje->dato;
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

    recursosGraficosMensajes->siguienteMensaje = recursosGraficosMensajes->siguienteMensaje->sig;
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






































