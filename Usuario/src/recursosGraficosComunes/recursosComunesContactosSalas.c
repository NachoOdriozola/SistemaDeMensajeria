#include "../../include/recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas);

static int recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos);
static int recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos);
static int recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas);

static void recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_fuentes *fuentes);
static void recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos);

static void recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas);

static void recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTOS

    recursosComunesContactosSalas_inicializarValoresNulosTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_inicializarValoresNulosElementos (&(recursosComunesContactosSalas->elementos));


    // VISTAS

    recursosComunesContactosSalas_inicializarValoresNulosVistas (&(recursosComunesContactosSalas->vistas));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTOS

    if (recursosComunesContactosSalas_inicializarTextos (&(recursosComunesContactosSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (recursosComunesContactosSalas_inicializarElementos (&(recursosComunesContactosSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // --------------- INICIALIZAR VISTAS ---------------

    if (recursosComunesContactosSalas_inicializarVistas (&(recursosComunesContactosSalas->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesContactosSalas->habilitaciones.escribirMensaje = DESHABILITAR_ESCRIBIR_MENSAJE;
    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
    recursosComunesContactosSalas->habilitaciones.puntoInsercion = DESHABILITAR_PUNTO_INSERCION;
    recursosComunesContactosSalas->habilitaciones.contadorPuntoInsercion = REINICIAR_CONTADOR_PUNTO_INSERCION;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->bufferMensaje) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesContactosSalas_configurarTextos (&(recursosComunesContactosSalas->textos), fuentes);


    // ELEMENTOS

    recursosComunesContactosSalas_configurarElementos (&(recursosComunesContactosSalas->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTO

    recursosComunesContactosSalas_tamYPosVentanaTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_tamYPosVentanaElementos (&(recursosComunesContactosSalas->elementos));


    // VISTAS

    recursosComunesContactosSalas_tamVistas (&(recursosComunesContactosSalas->vistas));
}

void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->alertaNotificaciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, textos->configuraciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreCambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->notificaciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->panelInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraSeparacionTitulo, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->solapaCambiarInterfaz, NULL);
}

void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesContactosSalas_liberarTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_liberarElementos (&(recursosComunesContactosSalas->elementos));


    // --------------- LIBERAR VISTAS ---------------

    recursosComunesContactosSalas_liberarVistas (&(recursosComunesContactosSalas->vistas));
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



int intentarEnvioMensaje (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];
    char estadoRespuesta;
    int idReceptor;

    idReceptor = atoi (&(recursosComunesContactosSalas->bufferMensaje[0]));
    snprintf (bufferSolicitud, MAX_BUFFER_SOLICITUD, "%c|%d|%d|%s", INDICE_SOLICITUD_MENSAJE, aplicacion->usuario.id, idReceptor, &(recursosComunesContactosSalas->bufferMensaje[1]));
    enviarSolicitudYRecibirRespuesta (aplicacion->sock, bufferSolicitud, bufferRespuesta);
    sscanf (bufferRespuesta, "%c", &estadoRespuesta);
    if (estadoRespuesta != INDICE_RESPUESTA_EXITO)
    {
        printf ("Error servidor.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

void manejarReciboMensaje (t_aplicacion *aplicacion, char *bufferRespuesta)
{
    int idEmisor;
    char texto [MAX_BUFFER_MENSAJE];

    sscanf (&(bufferRespuesta[2]), "%d|%[^\n]", &idEmisor, texto);
    asignarMensaje (aplicacion, texto, OTRO_USUARIO);
    printf ("EL: %s\n", texto);
}

void renderizarVistaMensajes (t_aplicacion *aplicacion, const t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- ESTABLECER VISTA DE MENSAJES ---------------

    sfRenderWindow_setView (aplicacion->renderizado, recursosComunesContactosSalas->vistas.mensajes);


    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------

    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), aplicacion->renderizado, renderizarListaMensajes);
}

void renderizarNotificaciones (t_aplicacion *aplicacion, const t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->habilitaciones.notificaciones == HABILITAR_NOTIFICACIONES)
    {
        // ELEMENTOS

        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, recursosComunesContactosSalas->elementos.ventanaEmergente, NULL);


        // TEXTOS

        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente, NULL);
        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->textos.tituloVentanaEmergente, NULL);


        // LISTA DE NOTIFICACIONES

        mapListaSimpleConComplemento (&(aplicacion->listaNotificaciones), aplicacion->renderizado, renderizarListaNotificaciones);
    }
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->alertaNotificaciones = NULL;
    textos->auxEscribirMensaje = NULL;
    textos->cerrarVentanaEmergente = NULL;
    textos->configuraciones = NULL;
    textos->nombreCambiarInterfaz = NULL;
    textos->nombreUsuario = NULL;
    textos->notificaciones = NULL;
    textos->tituloInterfaz = NULL;
    textos->tituloVentanaEmergente = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = NULL;
    elementos->barraEscribirMensaje = NULL;
    elementos->barraSeparacionNombre = NULL;
    elementos->barraSeparacionTitulo = NULL;
    elementos->panelInterfaz = NULL;
    elementos->puntoInsercion = NULL;
    elementos->solapaCambiarInterfaz = NULL;
    elementos->ventanaEmergente = NULL;
}

/** \brief Establecer en NULL a todas las vistas comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * \param vistas Puntero a la estructura que contiene las variables de las vistas de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->UI = NULL;
    vistas->mensajes = NULL;
}

/** \brief Inicializar los recursos graficos de textos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Crear todos los recursos graficos de textos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->alertaNotificaciones = sfText_create ();
    if (!textos->alertaNotificaciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto alertaNotificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxEscribirMensaje = sfText_create ();
    if (!textos->auxEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto auxEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    textos->cerrarVentanaEmergente = sfText_create ();
    if (!textos->cerrarVentanaEmergente)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto cerrarVentanaEmergente.\n");
        return ERROR_INICIALIZACION;
    }

    textos->configuraciones = sfText_create ();
    if (!textos->configuraciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto configuraciones.\n");
        return ERROR_INICIALIZACION;
    }

    textos->nombreCambiarInterfaz = sfText_create ();
    if (!textos->nombreCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreCambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    textos->nombreUsuario = sfText_create ();
    if (!textos->nombreUsuario)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    textos->notificaciones = sfText_create ();
    if (!textos->notificaciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto notificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloInterfaz = sfText_create ();
    if (!textos->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloVentanaEmergente = sfText_create ();
    if (!textos->tituloVentanaEmergente)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto tituloVentanaEmergente.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Crear todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = sfRectangleShape_create ();
    if (!elementos->areaMensajes)
    {
        printf ("\nERROR - Recursos comunes contactos-salas, crear elemento areaMensajes.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->barraEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento barraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraSeparacionNombre = sfRectangleShape_create ();
    if (!elementos->barraSeparacionNombre)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento barraSeparacionNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraSeparacionTitulo = sfRectangleShape_create ();
    if (!elementos->barraSeparacionTitulo)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento barraSeparacionTitulo.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->panelInterfaz = sfRectangleShape_create ();
    if (!elementos->panelInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento panelInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->solapaCambiarInterfaz = sfRectangleShape_create ();
    if (!elementos->solapaCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento solapaCambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->ventanaEmergente = sfRectangleShape_create ();
    if (!elementos->ventanaEmergente)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ventanaEmergente.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar las vistas comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * Crear todas las vistas. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param vistas Puntero a la estructura que contiene las variables de las vistas de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->UI = sfView_create ();
    if (!vistas->UI)
    {
        printf ("\nERROR - Recursos comunes contactos-salas, crear vista de UI.\n");
        return ERROR_INICIALIZACION;
    }

    vistas->mensajes = sfView_create ();
    if (!vistas->mensajes)
    {
        printf ("\nERROR - Recursos comunes contactos-salas, crear vista de mensajes.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de textos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_fuentes *fuentes)
{
    // alertaNotificaciones
    sfText_setFont (textos->alertaNotificaciones, fuentes->fuente1);
    sfText_setString (textos->alertaNotificaciones, "!");
    sfText_setFillColor (textos->alertaNotificaciones, sfColor_fromRGB (255, 0, 0));

    // auxEscribirMensaje
    sfText_setFont (textos->auxEscribirMensaje, fuentes->fuente1);
    sfText_setFillColor (textos->auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));

    // cerrarVentanaEmergente
    sfText_setFont (textos->cerrarVentanaEmergente, fuentes->fuente1);
    sfText_setString (textos->cerrarVentanaEmergente, "X");
    sfText_setFillColor (textos->cerrarVentanaEmergente, sfColor_fromRGB (40, 54, 54));

    // configuraciones
    sfText_setFont (textos->configuraciones, fuentes->fuente1);
    sfText_setString (textos->configuraciones, "C");
    sfText_setFillColor (textos->configuraciones, sfColor_fromRGB (40, 54, 54));

    // nombreCambiarInterfaz
    sfText_setFont (textos->nombreCambiarInterfaz, fuentes->fuente1);
    sfText_setString (textos->nombreCambiarInterfaz, "SALAS");
    sfText_setFillColor (textos->nombreCambiarInterfaz, sfColor_fromRGB (34, 48, 48));
    sfText_rotate (textos->nombreCambiarInterfaz, -90);

    // nombreUsuario
    sfText_setFont (textos->nombreUsuario, fuentes->fuente1);
    sfText_setFillColor (textos->nombreUsuario, sfColor_fromRGB (34, 48, 48));

    // notificaciones
    sfText_setFont (textos->notificaciones, fuentes->fuente1);
    sfText_setString (textos->notificaciones, "N");
    sfText_setFillColor (textos->notificaciones, sfColor_fromRGB (34, 48, 48));

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->fuente1);
    sfText_setString (textos->tituloInterfaz, "CONTACTOS");
    sfText_setFillColor (textos->tituloInterfaz, sfColor_fromRGB (34, 48, 48));

    // tituloVentanaEmergente
    sfText_setFont (textos->tituloVentanaEmergente, fuentes->fuente1);
    sfText_setFillColor (textos->tituloVentanaEmergente, sfColor_fromRGB (40, 54, 54));
}

/** \brief Configurar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    // areaMensajes
    sfRectangleShape_setFillColor (elementos->areaMensajes, sfColor_fromRGB (223, 231, 233));

    // barraEscribirMensaje
    sfRectangleShape_setFillColor (elementos->barraEscribirMensaje, sfColor_fromRGB (208, 208, 208));

    // barraSeparacionNombre
    sfRectangleShape_setFillColor (elementos->barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    // barraSeparacionTitulo
    sfRectangleShape_setFillColor (elementos->barraSeparacionTitulo, sfColor_fromRGB (82, 61, 53));

    // panelInterfaz
    sfRectangleShape_setFillColor (elementos->panelInterfaz, sfColor_fromRGB (232, 217, 205));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);

    // solapaCambiarInterfaz
    sfRectangleShape_setFillColor (elementos->solapaCambiarInterfaz, sfColor_fromRGB (255, 229, 127));

    // ventanaEmergente
    sfRectangleShape_setFillColor (elementos->ventanaEmergente, sfColor_fromRGB (255, 229, 127));
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico comun (compartido) entre las interfaces de contactos y salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos)
{
    // alertaNotificaciones
    sfText_setPosition (textos->alertaNotificaciones, (sfVector2f){320, 40});
    sfText_setCharacterSize (textos->alertaNotificaciones, 38);

    // auxEscribirMensaje
    sfText_setPosition (textos->auxEscribirMensaje, (sfVector2f){510, 912});
    sfText_setCharacterSize (textos->auxEscribirMensaje, 26);

    // cerrarVentanaEmergente
    sfText_setPosition (textos->cerrarVentanaEmergente, (sfVector2f){1070, 390});
    sfText_setCharacterSize (textos->cerrarVentanaEmergente, 36);

    // configuraciones
    sfText_setPosition (textos->configuraciones, (sfVector2f){305, 922});
    sfText_setCharacterSize (textos->configuraciones, 46);

    // nombreCambiarInterfaz
    sfText_setPosition (textos->nombreCambiarInterfaz, (sfVector2f){352, 574});
    sfText_setCharacterSize (textos->nombreCambiarInterfaz, 46);
    sfText_setLetterSpacing (textos->nombreCambiarInterfaz, 10);

    // nombreUsuario
    sfText_setPosition (textos->nombreUsuario, (sfVector2f){35, 925});
    sfText_setCharacterSize (textos->nombreUsuario, 36);

    // notificaciones
    sfText_setPosition (textos->notificaciones, (sfVector2f){300, 35});
    sfText_setCharacterSize (textos->notificaciones, 42);

    // tituloInterfaz
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){62, 45});
    sfText_setCharacterSize (textos->tituloInterfaz, 36);

    // tituloVentanaEmergente
    sfText_setPosition (textos->tituloVentanaEmergente, (sfVector2f){840, 400});
    sfText_setCharacterSize (textos->tituloVentanaEmergente, 32);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico comun (compartido) entre las interfaces de contactos y salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    // areaMensajes
    sfRectangleShape_setPosition (elementos->areaMensajes, (sfVector2f){430, 30});
    sfRectangleShape_setSize (elementos->areaMensajes, (sfVector2f){1470, 850});

    // barraEscribirMensaje
    sfRectangleShape_setPosition (elementos->barraEscribirMensaje, (sfVector2f){490, 909});
    sfRectangleShape_setSize (elementos->barraEscribirMensaje, (sfVector2f){1350, 42});

    // barraSeparacionNombre
    sfRectangleShape_setPosition (elementos->barraSeparacionNombre, (sfVector2f){24, 888});
    sfRectangleShape_setSize (elementos->barraSeparacionNombre, (sfVector2f){250, 3});

    // barraSeparacionTitulo
    sfRectangleShape_setPosition (elementos->barraSeparacionTitulo, (sfVector2f){24, 120});
    sfRectangleShape_setSize (elementos->barraSeparacionTitulo, (sfVector2f){250, 3});

    // panelInterfaz
    sfRectangleShape_setPosition (elementos->panelInterfaz, (sfVector2f){0, 0});
    sfRectangleShape_setSize (elementos->panelInterfaz, (sfVector2f){350, 1009});

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){26, 2});

    // solapaCambiarInterfaz
    sfRectangleShape_setPosition (elementos->solapaCambiarInterfaz, (sfVector2f){350, 124});
    sfRectangleShape_setSize (elementos->solapaCambiarInterfaz, (sfVector2f){60, 759});

    // ventanaEmergente
    sfRectangleShape_setPosition (elementos->ventanaEmergente, (sfVector2f){760, 380});
    sfRectangleShape_setSize (elementos->ventanaEmergente, (sfVector2f){400, 300});
}

/** \brief Establecer un tamanio y una posicion a cada vista comun (compartido) entre las interfaces de contactos y salas.
 *
 * \param vistas Puntero a la estructura que contiene las variables de las vistas de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    // UI
    sfView_setSize (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});

    // mensajes
    sfView_setSize (vistas->mensajes, (sfVector2f){1470, 850});                             // Vista del tamanio del sfRectangleShape *areaMensajes
    sfView_setCenter (vistas->mensajes, (sfVector2f){1165, 455});                           // Centro del sfRectangleShape *areaMensajes
    sfView_setViewport(vistas->mensajes, (sfFloatRect){0.223f, 0.029f, 0.765f, 0.842f});    // Proporciones del sfRectangleShape *areaMensajes
}

/** \brief Liberar, de manera segura, todas los textos comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->alertaNotificaciones);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirMensaje);
    DESTRUCTOR_SEGURO_TEXTO (textos->cerrarVentanaEmergente);
    DESTRUCTOR_SEGURO_TEXTO (textos->configuraciones);
    DESTRUCTOR_SEGURO_TEXTO (textos->nombreCambiarInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->nombreUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->notificaciones);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloVentanaEmergente);
}

/** \brief Liberar, de manera segura, todas los elementos comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaMensajes);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirMensaje);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraSeparacionNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraSeparacionTitulo);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->panelInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->solapaCambiarInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->ventanaEmergente);
}

/** \brief Liberar, de manera segura, todas las vistas comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * \param vistas Puntero a la estructura que contiene las variables de las vistas de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->UI);
    DESTRUCTOR_SEGURO_VISTA (vistas->mensajes);
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



void manejarRedimensionamientoVentanaContactosSalas (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoRedimensionamiento)
{
    sfVector2u tamVentana;

    if (eventoRedimensionamiento.size.width < ANCHO_MINIMO_VENTANA)
        tamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        tamVentana.x = eventoRedimensionamiento.size.width;

    if (eventoRedimensionamiento.size.height < ALTO_MINIMO_VENTANA)
        tamVentana.y = ALTO_MINIMO_VENTANA;
    else
        tamVentana.y = eventoRedimensionamiento.size.height;

    sfRenderWindow_setSize (aplicacion->renderizado, tamVentana);

    // Redimensionar vista UI
    sfView_setSize (recursosComunesContactosSalas->vistas.UI, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (recursosComunesContactosSalas->vistas.UI, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});
}

bool manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE)
    {
        ingresarCaracterABuffer (recursosComunesContactosSalas->bufferMensaje, MAX_BUFFER_MENSAJE, eventoChar);
        sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->bufferMensaje);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){512.5 + limiteTextoAux.width, 943});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarEnterEnviarMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_aplicacion *aplicacion)
{
    if ((recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE) && (strlen (recursosComunesContactosSalas->bufferMensaje) > 0))
    {
        if (intentarEnvioMensaje (aplicacion, recursosComunesContactosSalas) == EXITO)
        {
            asignarMensaje (aplicacion, recursosComunesContactosSalas->bufferMensaje, MI_USUARIO);
            printf ("YO: %s\n", &(recursosComunesContactosSalas->bufferMensaje[1]));
        }
        *(recursosComunesContactosSalas->bufferMensaje) = '\0';
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -eventoScroll.mouseWheelScroll.delta * VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}


























