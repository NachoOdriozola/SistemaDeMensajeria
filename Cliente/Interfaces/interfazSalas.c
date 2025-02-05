#include "interfazSalas.h"


///FUNCIONES ESTRUCTURALES


int inicializarSalas (s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///INICIALIZAR TEXTO
    recursosGraficosSalas->texto.amigos = sfText_create ();
    if (!recursosGraficosSalas->texto.amigos)
    {
        perror ("ERROR - Crear texto amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->texto.salas = sfText_create ();
    if (!recursosGraficosSalas->texto.salas)
    {
        perror ("ERROR - Crear texto salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosSalas->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->texto.interfazConfig = sfText_create ();
    if (!recursosGraficosSalas->texto.interfazConfig)
    {
        perror ("ERROR - Crear texto para cambiar a la interfaz de configuraciones.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosSalas->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Crear texto auxiliar para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosSalas->elementos.rectanguloAmigos = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.rectanguloAmigos)
    {
        perror ("ERROR - Crear rectangulo de amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos)
    {
        perror ("ERROR - Crear cuadrado para relieve de rectangulo de amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.rectanguloSalas = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.rectanguloSalas)
    {
        perror ("ERROR - Crear rectangulo de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.barraSeparacionSalas = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.barraSeparacionSalas)
    {
        perror ("ERROR - Crear barra de separacion de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Crear barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Crear barra para ingresar mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.barraEscribiendoMensaje = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.barraEscribiendoMensaje)
    {
        perror ("ERROR - Crear barra de escribiendo mensaje.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///SETUP ESCRITURA
    recursosGraficosSalas->habilitaciones.habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosSalas->bufferEscribirMensaje) = '\0';


    ///BARRA DE ESCRIBIENDO MENSAJE
    recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje = DESHABILITAR_BARRA_ESCRIBIENDO_MENSAJE;
    recursosGraficosSalas->habilitaciones.tempHabilitarBarra = 0;


    ///SETUP TEXTO
    //Texto amigos
    sfText_setFont (recursosGraficosSalas->texto.amigos, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosSalas->texto.amigos, "AMIGOS");
    sfText_setFillColor (recursosGraficosSalas->texto.amigos, sfColor_fromRGB (34, 48, 48));
    sfText_rotate (recursosGraficosSalas->texto.amigos, -90);

    //Texto salas
    sfText_setFont (recursosGraficosSalas->texto.salas, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosSalas->texto.salas, "SALAS");
    sfText_setFillColor (recursosGraficosSalas->texto.salas, sfColor_fromRGB (34, 48, 48));

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosSalas->texto.nombreUsuario, app->mensajes.fuentes.fuente1);
    sfText_setFillColor (recursosGraficosSalas->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto para cambiar a la interfaz de config
    sfText_setFont (recursosGraficosSalas->texto.interfazConfig, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosSalas->texto.interfazConfig, "C");
    sfText_setFillColor (recursosGraficosSalas->texto.interfazConfig, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar escribir mensaje
    sfText_setFont (recursosGraficosSalas->texto.auxEscribirMensaje, app->mensajes.fuentes.fuente1);
    sfText_setFillColor (recursosGraficosSalas->texto.auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));


    ///SETUP ELEMENTOS
    //Rectangulo de amigos
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.rectanguloAmigos, sfColor_fromRGB (255, 229, 127));

    //Cuadrado para relieve de rectangulo de amigos
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos, sfColor_fromRGB (189, 139, 37));

    //Rectangulo de salas
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.rectanguloSalas, sfColor_fromRGB (232, 217, 205));

    //Barra separacion salas
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.barraSeparacionSalas, sfColor_fromRGB (82, 61, 53));

    //Barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //Barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));

    //Barra de escribiendo mensaje
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.barraEscribiendoMensaje, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (recursosGraficosSalas->elementos.barraEscribiendoMensaje, -90);
}

void tamYPosPantallaSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///SETUP POS Y TAM TEXTO
    //Texto amigos
    sfText_setPosition (recursosGraficosSalas->texto.amigos, (sfVector2f){3 * app->ventana.escalaElementos.x, 574 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.amigos, 46 * app->ventana.escalaPixeles);
    sfText_setLetterSpacing (recursosGraficosSalas->texto.amigos, 10 * app->ventana.escalaPixeles);

    //Texto salas
    sfText_setPosition (recursosGraficosSalas->texto.salas, (sfVector2f){122 * app->ventana.escalaElementos.x, 45 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.salas, 36 * app->ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosSalas->texto.nombreUsuario, (sfVector2f){95 * app->ventana.escalaElementos.x, 925 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.nombreUsuario, 36 * app->ventana.escalaPixeles);

    //Texto para cambiar a la interfaz de config
    sfText_setPosition (recursosGraficosSalas->texto.interfazConfig, (sfVector2f){365 * app->ventana.escalaElementos.x, 922 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.interfazConfig, 46 * app->ventana.escalaPixeles);

    //Texto auxiliar para escribir mensaje
    sfText_setPosition (recursosGraficosSalas->texto.auxEscribirMensaje, (sfVector2f){510 * app->ventana.escalaElementos.x, 912 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.auxEscribirMensaje, 26 * app->ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo de amigos
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.rectanguloAmigos, (sfVector2f){0, 124 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.rectanguloAmigos, (sfVector2f){60 * app->ventana.escalaElementos.x, 759 * app->ventana.escalaElementos.y});

    //Cuadrado para relieve de rectangulo de amigos
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos, (sfVector2f){0 * app->ventana.escalaElementos.x, 117 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos, (sfVector2f){25 * app->ventana.escalaElementos.x, 20 * app->ventana.escalaElementos.y});

    //Rectangulo de salas
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.rectanguloSalas, (sfVector2f){60 * app->ventana.escalaElementos.x, 0});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.rectanguloSalas, (sfVector2f){350 * app->ventana.escalaElementos.x, 1009 * app->ventana.escalaElementos.y});

    //Barra separacion salas
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.barraSeparacionSalas, (sfVector2f){84 * app->ventana.escalaElementos.x, 120 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.barraSeparacionSalas, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.barraSeparacionNombre, (sfVector2f){84 * app->ventana.escalaElementos.x, 888 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.barraSeparacionNombre, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.barraIngresarMensaje, (sfVector2f){490 * app->ventana.escalaElementos.x, 909 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.barraIngresarMensaje, (sfVector2f){1350 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});

    //Barra de escribiendo mensaje
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.barraEscribiendoMensaje, (sfVector2f){26 * app->ventana.escalaElementos.x, 2 * app->ventana.escalaElementos.y});
}

void accionSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;
    sfFloatRect limiteTextoAux;


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
            if (clickEnRectangulo (app->renderizado, recursosGraficosSalas->elementos.barraIngresarMensaje))
                recursosGraficosSalas->habilitaciones.habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosSalas->habilitaciones.habilitarEscritura = DESHABILITAR_ESCRITURA;


            if (clickEnRectangulo (app->renderizado, recursosGraficosSalas->elementos.rectanguloAmigos))
                app->interfaz = INTERFAZ_AMIGOS;

            if (clickEnTexto (app->renderizado, recursosGraficosSalas->texto.interfazConfig))
                app->interfaz = INTERFAZ_CONFIG;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosSalas->habilitaciones.habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosSalas->bufferEscribirMensaje, MAX_BUFFER_MENSAJE - 5, evento);
            sfText_setString (recursosGraficosSalas->texto.auxEscribirMensaje, recursosGraficosSalas->bufferEscribirMensaje);
            limiteTextoAux = sfText_getGlobalBounds (recursosGraficosSalas->texto.auxEscribirMensaje);
            sfRectangleShape_setPosition (recursosGraficosSalas->elementos.barraEscribiendoMensaje, (sfVector2f){(512.5 * app->ventana.escalaElementos.x) + limiteTextoAux.width, 940 * app->ventana.escalaElementos.y});
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosSalas->habilitaciones.habilitarEscritura == HABILITAR_ESCRITURA) &&
            (strlen (recursosGraficosSalas->bufferEscribirMensaje) > 0))
        {
            //enviar paquete mensaje
        }
        break;

    default:
        break;
    }
}

void actualizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    int largoBufferMensaje;

    largoBufferMensaje = strlen (recursosGraficosSalas->bufferEscribirMensaje);


    ///RECIBIR MENSAJES DE OTROS USUARIOS
    int bytesRecibidos;
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE];

    bytesRecibidos = recv (app->sock, bufferPaquete, sizeof (bufferPaquete), 0);
    if (bytesRecibidos > 0)
    {
        bufferPaquete [bytesRecibidos] = '\0';
        asignarMensaje (app, bufferPaquete, OTRO_USUARIO);
    }


    ///TEXTO AUXILIAR ESCRIBIR MENSAJE
    if ((recursosGraficosSalas->habilitaciones.habilitarEscritura == DESHABILITAR_ESCRITURA) && (largoBufferMensaje == 0))
        sfText_setString (recursosGraficosSalas->texto.auxEscribirMensaje, "Escribir mensaje...");


    ///BARRA DE ESCRIBIENDO MENSAJE
    if (recursosGraficosSalas->habilitaciones.habilitarEscritura == HABILITAR_ESCRITURA)
    {
        if (recursosGraficosSalas->habilitaciones.tempHabilitarBarra == 22)
        {
            recursosGraficosSalas->habilitaciones.tempHabilitarBarra = 0;
            if (recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje == HABILITAR_BARRA_ESCRIBIENDO_MENSAJE)
                recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje = DESHABILITAR_BARRA_ESCRIBIENDO_MENSAJE;
            else
                recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje = HABILITAR_BARRA_ESCRIBIENDO_MENSAJE;
        }
        recursosGraficosSalas->habilitaciones.tempHabilitarBarra ++;
    }
    else
    {
        recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje = DESHABILITAR_BARRA_ESCRIBIENDO_MENSAJE;
        recursosGraficosSalas->habilitaciones.tempHabilitarBarra = 0;
    }
}

void renderizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.rectanguloAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.rectanguloSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.barraSeparacionSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.amigos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.salas, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.interfazConfig, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.auxEscribirMensaje, NULL);


    ///BARRA DE ESCRIBIENDO MENSAJE
    if (recursosGraficosSalas->habilitaciones.habilitarBarraEscribiendoMensaje == HABILITAR_BARRA_ESCRIBIENDO_MENSAJE)
        sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.barraEscribiendoMensaje, NULL);


    ///RENDERIZAR LISTA DE MENSAJES
    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), app->renderizado, renderizarListaMensajes);


    sfRenderWindow_display (app->renderizado);
}

void liberarSalas (s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///LIBERAR TEXTO
    sfText_destroy (recursosGraficosSalas->texto.amigos);
    sfText_destroy (recursosGraficosSalas->texto.salas);
    sfText_destroy (recursosGraficosSalas->texto.nombreUsuario);
    sfText_destroy (recursosGraficosSalas->texto.interfazConfig);
    sfText_destroy (recursosGraficosSalas->texto.auxEscribirMensaje);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.rectanguloAmigos);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.cuadradoRelieveRecAmigos);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.rectanguloSalas);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.barraSeparacionSalas);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.barraIngresarMensaje);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.barraEscribiendoMensaje);
}















