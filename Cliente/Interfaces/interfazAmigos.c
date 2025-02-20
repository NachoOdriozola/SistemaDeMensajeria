#include "interfazAmigos.h"


///FUNCIONES ESTRUCTURALES


int inicializarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///INICIALIZAR TEXTO

    recursosGraficosAmigos->texto.amigos = sfText_create ();
    if (!recursosGraficosAmigos->texto.amigos)
    {
        perror ("ERROR - Crear texto amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.agregarAmigos = sfText_create ();
    if (!recursosGraficosAmigos->texto.agregarAmigos)
    {
        perror ("ERROR - Crear texto para agregar amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.notificaciones = sfText_create ();
    if (!recursosGraficosAmigos->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto notificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.alertaNotificaciones = sfText_create ();
    if (!recursosGraficosAmigos->texto.alertaNotificaciones)
    {
        perror ("ERROR - Crear alerta de notificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.salas = sfText_create ();
    if (!recursosGraficosAmigos->texto.salas)
    {
        perror ("ERROR - Crear texto salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosAmigos->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.interfazConfig = sfText_create ();
    if (!recursosGraficosAmigos->texto.interfazConfig)
    {
        perror ("ERROR - Crear texto para cambiar a la interfaz de configuraciones.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosAmigos->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Crear texto auxiliar para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.cerrarPestania = sfText_create ();
    if (!recursosGraficosAmigos->texto.cerrarPestania)
    {
        perror ("ERROR - Crear cerrar pestania.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.tituloAgregarAmigos = sfText_create ();
    if (!recursosGraficosAmigos->texto.tituloAgregarAmigos)
    {
        perror ("ERROR - Crear titulo agregar amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.auxAgregarAmigos = sfText_create ();
    if (!recursosGraficosAmigos->texto.auxAgregarAmigos)
    {
        perror ("ERROR - Crear texto auxiliar para agregar amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.tituloNotificaciones = sfText_create ();
    if (!recursosGraficosAmigos->texto.tituloNotificaciones)
    {
        perror ("ERROR - Crear titulo notificaciones.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS

    recursosGraficosAmigos->elementos.rectanguloAmigos = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloAmigos)
    {
        perror ("ERROR - Crear rectangulo de amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.rectanguloSalas = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloSalas)
    {
        perror ("ERROR - Crear rectangulo de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas)
    {
        perror ("ERROR - Crear cuadrado para relieve de rectangulo de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraSeparacionAmigos = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraSeparacionAmigos)
    {
        perror ("ERROR - Crear barra de separacion de amigos.\n");
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

    recursosGraficosAmigos->elementos.recBasePestania = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.recBasePestania)
    {
        perror ("ERROR - Crear rectangulo base para pestania.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraAgregarAmigos = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraAgregarAmigos)
    {
        perror ("ERROR - Crear barra para agregar amigos.\n");
        return ERROR_INICIALIZACION;
    }



    return OK;
}

void setupAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos, s_fuentes fuentes)
{
    ///SETUP HABILITACIONES Y ESCRITURA

    recursosGraficosAmigos->habilitaciones.agregarAmigos = DESHABILITAR_AGREGAR_AMIGOS;
    recursosGraficosAmigos->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
    recursosGraficosAmigos->habilitaciones.escrituraMensajes = DESHABILITAR_ESCRITURA_MENSAJES;
    recursosGraficosAmigos->habilitaciones.escrituraAgregarAmigos = DESHABILITAR_ESCRITURA_AGREGAR_AMIGOS;
    recursosGraficosAmigos->habilitaciones.contComprobarNotificaciones = 0;
    *(recursosGraficosAmigos->bufferEscribirMensaje) = '\0';
    *(recursosGraficosAmigos->bufferAgregarAmigos) = '\0';



    ///SETUP TEXTO

    //Texto amigos
    sfText_setFont (recursosGraficosAmigos->texto.amigos, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.amigos, "AMIGOS");
    sfText_setFillColor (recursosGraficosAmigos->texto.amigos, sfColor_fromRGB (34, 48, 48));

    //Texto agregar amigos
    sfText_setFont (recursosGraficosAmigos->texto.agregarAmigos, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.agregarAmigos, "+");
    sfText_setFillColor (recursosGraficosAmigos->texto.agregarAmigos, sfColor_fromRGB (34, 48, 48));

    //Texto notificaciones
    sfText_setFont (recursosGraficosAmigos->texto.notificaciones, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.notificaciones, "N");
    sfText_setFillColor (recursosGraficosAmigos->texto.notificaciones, sfColor_fromRGB (34, 48, 48));

    //Alerta de notificaciones
    sfText_setFont (recursosGraficosAmigos->texto.alertaNotificaciones, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.alertaNotificaciones, "!");
    sfText_setFillColor (recursosGraficosAmigos->texto.alertaNotificaciones, sfColor_fromRGB (255, 0, 0));

    //Texto salas
    sfText_setFont (recursosGraficosAmigos->texto.salas, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.salas, "SALAS");
    sfText_setFillColor (recursosGraficosAmigos->texto.salas, sfColor_fromRGB (34, 48, 48));
    sfText_rotate (recursosGraficosAmigos->texto.salas, -90);

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosAmigos->texto.nombreUsuario, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosAmigos->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto para cambiar a la interfaz de config
    sfText_setFont (recursosGraficosAmigos->texto.interfazConfig, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.interfazConfig, "C");
    sfText_setFillColor (recursosGraficosAmigos->texto.interfazConfig, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar escribir mensaje
    sfText_setFont (recursosGraficosAmigos->texto.auxEscribirMensaje, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosAmigos->texto.auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));

    //Cerrar pestania
    sfText_setFont (recursosGraficosAmigos->texto.cerrarPestania, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.cerrarPestania, "X");
    sfText_setFillColor (recursosGraficosAmigos->texto.cerrarPestania, sfColor_fromRGB (40, 54, 54));

    //Titulo agregar amigos
    sfText_setFont (recursosGraficosAmigos->texto.tituloAgregarAmigos, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.tituloAgregarAmigos, "AGREGAR AMIGOS");
    sfText_setFillColor (recursosGraficosAmigos->texto.tituloAgregarAmigos, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar para agregar amigos
    sfText_setFont (recursosGraficosAmigos->texto.auxAgregarAmigos, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosAmigos->texto.auxAgregarAmigos, sfColor_fromRGB (40, 54, 54));

    //Titulo notificaciones
    sfText_setFont (recursosGraficosAmigos->texto.tituloNotificaciones, fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.tituloNotificaciones, "NOTIFICACIONES");
    sfText_setFillColor (recursosGraficosAmigos->texto.tituloNotificaciones, sfColor_fromRGB (40, 54, 54));



    ///SETUP ELEMENTOS

    //Rectangulo de amigos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloAmigos, sfColor_fromRGB (232, 217, 205));

    //Rectangulo de salas
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloSalas, sfColor_fromRGB (255, 229, 127));

    //Cuadrado para relieve de rectangulo de salas
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, sfColor_fromRGB (189, 139, 37));

    //Barra separacion de amigos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionAmigos, sfColor_fromRGB (82, 61, 53));

    //Barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //Barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));

    //Rectangulo base para pestania
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.recBasePestania, sfColor_fromRGB (255, 229, 127));

    //Barra para agregar amigos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraAgregarAmigos, sfColor_fromRGB (208, 208, 208));
}

void tamYPosPantallaAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos, s_ventana ventana)
{
    ///SETUP POS Y TAM TEXTO

    //Texto amigos
    sfText_setPosition (recursosGraficosAmigos->texto.amigos, (sfVector2f){62 * ventana.escalaElementos.x, 45 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.amigos, 36 * ventana.escalaPixeles);

    //Texto agregar amigos
    sfText_setPosition (recursosGraficosAmigos->texto.agregarAmigos, (sfVector2f){220 * ventana.escalaElementos.x, 35 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.agregarAmigos, 60 * ventana.escalaPixeles);

    //Texto notificaciones
    sfText_setPosition (recursosGraficosAmigos->texto.notificaciones, (sfVector2f){300 * ventana.escalaElementos.x, 35 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.notificaciones, 42 * ventana.escalaPixeles);

    //Alerta de notificaciones
    sfText_setPosition (recursosGraficosAmigos->texto.alertaNotificaciones, (sfVector2f){320 * ventana.escalaElementos.x, 40 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.alertaNotificaciones, 38 * ventana.escalaPixeles);

    //Texto salas
    sfText_setPosition (recursosGraficosAmigos->texto.salas, (sfVector2f){353 * ventana.escalaElementos.x, 574 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.salas, 46 * ventana.escalaPixeles);
    sfText_setLetterSpacing (recursosGraficosAmigos->texto.salas, 10 * ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosAmigos->texto.nombreUsuario, (sfVector2f){35 * ventana.escalaElementos.x, 925 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.nombreUsuario, 36 * ventana.escalaPixeles);

    //Texto para cambiar a la interfaz de config
    sfText_setPosition (recursosGraficosAmigos->texto.interfazConfig, (sfVector2f){305 * ventana.escalaElementos.x, 922 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.interfazConfig, 46 * ventana.escalaPixeles);

    //Texto auxiliar para escribir mensaje
    sfText_setPosition (recursosGraficosAmigos->texto.auxEscribirMensaje, (sfVector2f){510 * ventana.escalaElementos.x, 912 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.auxEscribirMensaje, 26 * ventana.escalaPixeles);

    //Cerrar pestania
    sfText_setPosition (recursosGraficosAmigos->texto.cerrarPestania, (sfVector2f){1070 * ventana.escalaElementos.x, 390 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.cerrarPestania, 36 * ventana.escalaPixeles);

    //Titulo agregar amigos
    sfText_setPosition (recursosGraficosAmigos->texto.tituloAgregarAmigos, (sfVector2f){840 * ventana.escalaElementos.x, 400 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.tituloAgregarAmigos, 32 * ventana.escalaPixeles);

    //Texto auxiliar para agregar amigos
    sfText_setPosition (recursosGraficosAmigos->texto.auxAgregarAmigos, (sfVector2f){802 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.auxAgregarAmigos, 26 * ventana.escalaPixeles);

    //Titulo notificaciones
    sfText_setPosition (recursosGraficosAmigos->texto.tituloNotificaciones, (sfVector2f){840 * ventana.escalaElementos.x, 400 * ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.tituloNotificaciones, 32 * ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS

    //Rectangulo de amigos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloAmigos, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloAmigos, (sfVector2f){350 * ventana.escalaElementos.x, 1009 * ventana.escalaElementos.y});

    //Rectangulo de salas
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){350 * ventana.escalaElementos.x, 124 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){60 * ventana.escalaElementos.x, 759 * ventana.escalaElementos.y});

    //Cuadrado para relieve de rectangulo de salas
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, (sfVector2f){350 * ventana.escalaElementos.x, 117 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, (sfVector2f){25 * ventana.escalaElementos.x, 20 * ventana.escalaElementos.y});

    //Barra separacion de amigos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionAmigos, (sfVector2f){24 * ventana.escalaElementos.x, 120 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionAmigos, (sfVector2f){250 * ventana.escalaElementos.x, 3 * ventana.escalaElementos.y});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){24 * ventana.escalaElementos.x, 888 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){250 * ventana.escalaElementos.x, 3 * ventana.escalaElementos.y});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){490 * ventana.escalaElementos.x, 909 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){1350 * ventana.escalaElementos.x, 42 * ventana.escalaElementos.y});

    //Rectangulo base para pestania
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.recBasePestania, (sfVector2f){760 * ventana.escalaElementos.x, 380 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.recBasePestania, (sfVector2f){400 * ventana.escalaElementos.x, 300 * ventana.escalaElementos.y});

    //Barra para agregar amigos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraAgregarAmigos, (sfVector2f){800 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraAgregarAmigos, (sfVector2f){280 * ventana.escalaElementos.x, 42 * ventana.escalaElementos.y});
}

void accionAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
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
            if (clickEnTexto (app->renderizado, recursosGraficosAmigos->texto.agregarAmigos))
            {
                recursosGraficosAmigos->habilitaciones.agregarAmigos = HABILITAR_AGREGAR_AMIGOS;
                recursosGraficosAmigos->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
            }

            if (clickEnTexto (app->renderizado, recursosGraficosAmigos->texto.notificaciones))
            {
                recursosGraficosAmigos->habilitaciones.notificaciones = HABILITAR_NOTIFICACIONES;
                recursosGraficosAmigos->habilitaciones.agregarAmigos = DESHABILITAR_AGREGAR_AMIGOS;
            }

            if (clickEnTexto (app->renderizado, recursosGraficosAmigos->texto.cerrarPestania))
            {
                recursosGraficosAmigos->habilitaciones.agregarAmigos = DESHABILITAR_AGREGAR_AMIGOS;
                recursosGraficosAmigos->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
            }


            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje))
                recursosGraficosAmigos->habilitaciones.escrituraMensajes = HABILITAR_ESCRITURA_MENSAJES;
            else
                recursosGraficosAmigos->habilitaciones.escrituraMensajes = DESHABILITAR_ESCRITURA_MENSAJES;

            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.barraAgregarAmigos))
                recursosGraficosAmigos->habilitaciones.escrituraAgregarAmigos = HABILITAR_ESCRITURA_AGREGAR_AMIGOS;
            else
                recursosGraficosAmigos->habilitaciones.escrituraAgregarAmigos = DESHABILITAR_ESCRITURA_AGREGAR_AMIGOS;


            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas))
                app->interfaz = INTERFAZ_SALAS;

            if (clickEnTexto (app->renderizado, recursosGraficosAmigos->texto.interfazConfig))
            {
                app->interfaz = INTERFAZ_CONFIG;
                app->usuario.ultimaInterfaz = INTERFAZ_AMIGOS;
            }
        }
        break;

    case sfEvtTextEntered:
        if (evento.text.unicode < 128)
        {
            if (recursosGraficosAmigos->habilitaciones.escrituraMensajes == HABILITAR_ESCRITURA_MENSAJES)
            {
                ingresoTexto (recursosGraficosAmigos->bufferEscribirMensaje, MAX_BUFFER_MENSAJE - 1, evento);
                sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, recursosGraficosAmigos->bufferEscribirMensaje);
            }

            if (recursosGraficosAmigos->habilitaciones.escrituraAgregarAmigos == HABILITAR_ESCRITURA_AGREGAR_AMIGOS)
            {
                ingresoTexto (recursosGraficosAmigos->bufferAgregarAmigos, MAX_NOMBRE_USUARIO - 1, evento);
                sfText_setString (recursosGraficosAmigos->texto.auxAgregarAmigos, recursosGraficosAmigos->bufferAgregarAmigos);
            }
        }
        break;

    case sfEvtKeyPressed:
        if (evento.key.code == sfKeyEnter)
        {
            if ((recursosGraficosAmigos->habilitaciones.escrituraMensajes == HABILITAR_ESCRITURA_MENSAJES) && (strlen (recursosGraficosAmigos->bufferEscribirMensaje) > 0))
            {
                printf ("enviar paquete.\n");
                //enviar paquete
            }

            if ((recursosGraficosAmigos->habilitaciones.agregarAmigos == HABILITAR_ESCRITURA_AGREGAR_AMIGOS) && (strlen (recursosGraficosAmigos->bufferAgregarAmigos) > 0))
            {
                intentarSolicitudAmistad (app, recursosGraficosAmigos);
            }
        }
        break;

    default:
        break;
    }
}

void actualizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    int bytesRecibidos;
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE];

    bytesRecibidos = recv (app->sock, bufferPaquete, sizeof (bufferPaquete), 0);
    if (bytesRecibidos > 0)
    {
        bufferPaquete [bytesRecibidos] = '\0';
        asignarMensaje (app, bufferPaquete, OTRO_USUARIO);
    }


    ///COMPROBAR NOTIFICACIONES
    if (recursosGraficosAmigos->habilitaciones.contComprobarNotificaciones == 3000)
    {
        comprobarNotificaciones (app, recursosGraficosAmigos);
        recursosGraficosAmigos->habilitaciones.contComprobarNotificaciones = -1;
    }
    recursosGraficosAmigos->habilitaciones.contComprobarNotificaciones ++;


    ///TEXTO AUXILIAR ESCRIBIR MENSAJE
    if ((recursosGraficosAmigos->habilitaciones.escrituraMensajes == DESHABILITAR_ESCRITURA_MENSAJES) && ((strlen (recursosGraficosAmigos->bufferEscribirMensaje) == 0)))
        sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, "Escribir mensaje...");

    ///TEXTO AUXILIAR AGREGAR AMIGOS
    if ((recursosGraficosAmigos->habilitaciones.escrituraAgregarAmigos == DESHABILITAR_ESCRITURA_AGREGAR_AMIGOS) && (strlen (recursosGraficosAmigos->bufferAgregarAmigos) == 0))
        sfText_setString (recursosGraficosAmigos->texto.auxAgregarAmigos, "Escribir nombre...");
}

void renderizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.amigos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.agregarAmigos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.notificaciones, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.alertaNotificaciones, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.salas, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.interfazConfig, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.auxEscribirMensaje, NULL);


    ///RENDERIZAR AGREGAR AMIGOS
    if (recursosGraficosAmigos->habilitaciones.agregarAmigos == HABILITAR_AGREGAR_AMIGOS)
    {
        sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.recBasePestania, NULL);
        sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraAgregarAmigos, NULL);
        sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.tituloAgregarAmigos, NULL);
        sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.auxAgregarAmigos, NULL);
        sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.cerrarPestania, NULL);
    }


    ///RENDERIZAR NOTIFICACIONES
    if (recursosGraficosAmigos->habilitaciones.notificaciones == HABILITAR_NOTIFICACIONES)
    {
        sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.recBasePestania, NULL);
        sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.tituloNotificaciones, NULL);
        sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.cerrarPestania, NULL);
        mapListaCircularConComplemento (&(app->listaNotificaciones), app->renderizado, renderizarListaMensajes);
        //NO FUNCIONA PORQUE ES S_MENSAJE NO ES SFTEXT PERO ME TENGO QUE IR
    }


    ///RENDERIZAR LISTA DE MENSAJES
    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), app->renderizado, renderizarListaMensajes);


    sfRenderWindow_display (app->renderizado);
}

void liberarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///LIBERAR TEXTO
    sfText_destroy (recursosGraficosAmigos->texto.amigos);
    sfText_destroy (recursosGraficosAmigos->texto.agregarAmigos);
    sfText_destroy (recursosGraficosAmigos->texto.notificaciones);
    sfText_destroy (recursosGraficosAmigos->texto.alertaNotificaciones);
    sfText_destroy (recursosGraficosAmigos->texto.salas);
    sfText_destroy (recursosGraficosAmigos->texto.nombreUsuario);
    sfText_destroy (recursosGraficosAmigos->texto.interfazConfig);
    sfText_destroy (recursosGraficosAmigos->texto.auxEscribirMensaje);
    sfText_destroy (recursosGraficosAmigos->texto.cerrarPestania);
    sfText_destroy (recursosGraficosAmigos->texto.tituloAgregarAmigos);
    sfText_destroy (recursosGraficosAmigos->texto.auxAgregarAmigos);
    sfText_destroy (recursosGraficosAmigos->texto.tituloNotificaciones);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloAmigos);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloSalas);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionAmigos);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraIngresarMensaje);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.recBasePestania);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraAgregarAmigos);
}


///FUNCIONES LOGICAS


void intentarSolicitudAmistad (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    char *bufferSolicitud, *bufferRespuesta;
    char estadoSolicitud;

    bufferSolicitud = malloc (MAX_BUFFER_SOLICITUD);
    if (!bufferSolicitud)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }

    sprintf (bufferSolicitud, "%c|%d|%s|%s", INDICE_SOLICITUD_AMISTAD, app->usuario.id, app->usuario.nombre, recursosGraficosAmigos->bufferAgregarAmigos);
    printf ("Enviado: %s\n", bufferSolicitud);
    enviarYRecibirSolicitud (app->sock, bufferSolicitud, bufferRespuesta);
    sscanf (bufferRespuesta, "%c", &estadoSolicitud);

    free (bufferSolicitud);
    free (bufferRespuesta);

    if (estadoSolicitud == SOLICITUD_ACEPTADA)
        printf ("Le envio la solicitud de amistad.\n");
    else if (estadoSolicitud == SOLICITUD_RECHAZADA)
        printf ("No se envio la solicitud de amistad.\n");
}

void comprobarNotificaciones (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    char *bufferSolicitud, *bufferRespuesta, *ptrBufferRespuesta;
    char estadoSolicitud;
    char *nombreEmisor;

    bufferSolicitud = malloc (MAX_BUFFER_SOLICITUD);
    if (!bufferSolicitud)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    nombreEmisor = malloc (50);
    if (!nombreEmisor)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }


    ioctlsocket (app->sock, FIONBIO, &modoSocket);
    ptrBufferRespuesta = bufferRespuesta;


    sprintf (bufferSolicitud, "%c|%d", INDICE_NOTIFICACIONES, app->usuario.id);
    enviarYRecibirSolicitud (app->sock, bufferSolicitud, bufferRespuesta);
    estadoSolicitud = *ptrBufferRespuesta;
    if (estadoSolicitud == SOLICITUD_ACEPTADA)
    {
        sfText_setString (recursosGraficosAmigos->texto.alertaNotificaciones, "!");
        while ((ptrBufferRespuesta = strchr (ptrBufferRespuesta, '|')) != NULL)
        {
            ptrBufferRespuesta ++;
            sscanf (ptrBufferRespuesta, "%[^|]", nombreEmisor);
            strcat (nombreEmisor, " quiere ser tu amigo!");
            agregarNotificacion (&(app->listaNotificaciones), app->ventana, app->mensajes.fuentes, nombreEmisor);
        }
    }
    else
        sfText_setString (recursosGraficosAmigos->texto.alertaNotificaciones, "");


    modoSocket = 1;
    ioctlsocket (app->sock, FIONBIO, &modoSocket);

    free (bufferSolicitud);
    free (bufferRespuesta);
    free (nombreEmisor);
}






























