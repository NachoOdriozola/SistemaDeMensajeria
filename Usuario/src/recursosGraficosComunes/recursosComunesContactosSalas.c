#include "../../include/recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void recursosComunesContactosSalas_inicializarValoresNulosTextos (s_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_inicializarValoresNulosElementos (s_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_inicializarValoresNulosVistas (s_recursosComunesContactosSalasVistas *vistas);

static int recursosComunesContactosSalas_inicializarTextos (s_recursosComunesContactosSalasTextos *textos);
static int recursosComunesContactosSalas_inicializarElementos (s_recursosComunesContactosSalasElementos *elementos);
static int recursosComunesContactosSalas_inicializarVistas (s_recursosComunesContactosSalasVistas *vistas);

static void recursosComunesContactosSalas_configurarTextos (s_recursosComunesContactosSalasTextos *textos, const s_fuentes *fuentes);
static void recursosComunesContactosSalas_configurarElementos (s_recursosComunesContactosSalasElementos *elementos);

static void recursosComunesContactosSalas_tamYPosVentanaTextos (s_recursosComunesContactosSalasTextos *textos, const s_ventana *ventana);
static void recursosComunesContactosSalas_tamYPosVentanaElementos (s_recursosComunesContactosSalasElementos *elementos, const s_ventana *ventana);

static void recursosComunesContactosSalas_liberarTextos (s_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_liberarElementos (s_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_liberarVistas (s_recursosComunesContactosSalasVistas *vistas);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesContactosSalas_inicializar (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
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

void recursosComunesContactosSalas_configurar (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_fuentes *fuentes)
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
}

void recursosComunesContactosSalas_tamYPosVentana (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana)
{
    // --------------- TAMANIO Y POSICION EN VENTANA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesContactosSalas_tamYPosVentanaTextos (&(recursosComunesContactosSalas->textos), ventana);


    // ELEMENTOS

    recursosComunesContactosSalas_tamYPosVentanaElementos (&(recursosComunesContactosSalas->elementos), ventana);
}

void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->alertaNotificaciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, textos->configuraciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreCambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->notificaciones, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->panelInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraSeparacionTitulo, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->solapaCambiarInterfaz, NULL);
}

void recursosComunesContactosSalas_liberar (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
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



void recursosComunesContactosSalas_tamVistas (s_recursosComunesContactosSalasVistas *vistas, const s_ventana *ventana)
{
    // UI
    sfView_setSize (vistas->UI, ventana->tamVentana);
    sfView_setCenter (vistas->UI, (sfVector2f){ventana->tamVentana.x / 2.0f, ventana->tamVentana.y / 2.0f});

    // mensajes
    sfView_setSize (vistas->mensajes, (sfVector2f){1470 * ventana->escalaElementos.x, 850 * ventana->escalaElementos.y});   // Vista del tamanio del sfRectangleShape *areaMensajes
    sfView_setCenter (vistas->mensajes, (sfVector2f){1165 * ventana->escalaElementos.x, 455 * ventana->escalaElementos.y}); // Centro del sfRectangleShape *areaMensajes
    sfView_setViewport(vistas->mensajes, (sfFloatRect){0.223f, 0.029f, 0.765f, 0.842f});                                    // Proporciones del sfRectangleShape *areaMensajes
}

int intentarEnvioMensaje (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
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

void manejarReciboMensaje (s_aplicacion *aplicacion, char *bufferRespuesta)
{
    int idEmisor;
    char texto [MAX_BUFFER_MENSAJE];

    sscanf (&(bufferRespuesta[2]), "%d|%[^\n]", &idEmisor, texto);
    asignarMensaje (aplicacion, texto, OTRO_USUARIO);
    printf ("EL: %s\n", texto);
}

void renderizarVistaMensajes (s_aplicacion *aplicacion, const s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- ESTABLECER VISTA DE MENSAJES ---------------

    sfRenderWindow_setView (aplicacion->renderizado, recursosComunesContactosSalas->vistas.mensajes);


    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------

    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), aplicacion->renderizado, renderizarListaMensajes);
}

void renderizarNotificaciones (s_aplicacion *aplicacion, const s_recursosComunesContactosSalas *recursosComunesContactosSalas)
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
static void recursosComunesContactosSalas_inicializarValoresNulosTextos (s_recursosComunesContactosSalasTextos *textos)
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
static void recursosComunesContactosSalas_inicializarValoresNulosElementos (s_recursosComunesContactosSalasElementos *elementos)
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
static void recursosComunesContactosSalas_inicializarValoresNulosVistas (s_recursosComunesContactosSalasVistas *vistas)
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
static int recursosComunesContactosSalas_inicializarTextos (s_recursosComunesContactosSalasTextos *textos)
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
static int recursosComunesContactosSalas_inicializarElementos (s_recursosComunesContactosSalasElementos *elementos)
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
static int recursosComunesContactosSalas_inicializarVistas (s_recursosComunesContactosSalasVistas *vistas)
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
static void recursosComunesContactosSalas_configurarTextos (s_recursosComunesContactosSalasTextos *textos, const s_fuentes *fuentes)
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
static void recursosComunesContactosSalas_configurarElementos (s_recursosComunesContactosSalasElementos *elementos)
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
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaTextos (s_recursosComunesContactosSalasTextos *textos, const s_ventana *ventana)
{
    // alertaNotificaciones
    sfText_setPosition (textos->alertaNotificaciones, (sfVector2f){320 * ventana->escalaElementos.x, 40 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->alertaNotificaciones, 38 * ventana->escalaPixeles);

    // auxEscribirMensaje
    sfText_setPosition (textos->auxEscribirMensaje, (sfVector2f){510 * ventana->escalaElementos.x, 912 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->auxEscribirMensaje, 26 * ventana->escalaPixeles);

    // cerrarVentanaEmergente
    sfText_setPosition (textos->cerrarVentanaEmergente, (sfVector2f){1070 * ventana->escalaElementos.x, 390 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->cerrarVentanaEmergente, 36 * ventana->escalaPixeles);

    // configuraciones
    sfText_setPosition (textos->configuraciones, (sfVector2f){305 * ventana->escalaElementos.x, 922 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->configuraciones, 46 * ventana->escalaPixeles);

    // nombreCambiarInterfaz
    sfText_setPosition (textos->nombreCambiarInterfaz, (sfVector2f){352 * ventana->escalaElementos.x, 574 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->nombreCambiarInterfaz, 46 * ventana->escalaPixeles);
    sfText_setLetterSpacing (textos->nombreCambiarInterfaz, 10 * ventana->escalaPixeles);

    // nombreUsuario
    sfText_setPosition (textos->nombreUsuario, (sfVector2f){35 * ventana->escalaElementos.x, 925 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->nombreUsuario, 36 * ventana->escalaPixeles);

    // notificaciones
    sfText_setPosition (textos->notificaciones, (sfVector2f){300 * ventana->escalaElementos.x, 35 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->notificaciones, 42 * ventana->escalaPixeles);

    // tituloInterfaz
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){62 * ventana->escalaElementos.x, 45 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->tituloInterfaz, 36 * ventana->escalaPixeles);

    // tituloVentanaEmergente
    sfText_setPosition (textos->tituloVentanaEmergente, (sfVector2f){840 * ventana->escalaElementos.x, 400 * ventana->escalaElementos.y});
    sfText_setCharacterSize (textos->tituloVentanaEmergente, 32 * ventana->escalaPixeles);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico común (compartido) entre las interfaces de contactos y salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaElementos (s_recursosComunesContactosSalasElementos *elementos, const s_ventana *ventana)
{
    // areaMensajes
    sfRectangleShape_setPosition (elementos->areaMensajes, (sfVector2f){430 * ventana->escalaElementos.x, 30 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->areaMensajes, (sfVector2f){1470 * ventana->escalaElementos.x, 850 * ventana->escalaElementos.y});

    // barraEscribirMensaje
    sfRectangleShape_setPosition (elementos->barraEscribirMensaje, (sfVector2f){490 * ventana->escalaElementos.x, 909 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->barraEscribirMensaje, (sfVector2f){1350 * ventana->escalaElementos.x, 42 * ventana->escalaElementos.y});

    // barraSeparacionNombre
    sfRectangleShape_setPosition (elementos->barraSeparacionNombre, (sfVector2f){24 * ventana->escalaElementos.x, 888 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->barraSeparacionNombre, (sfVector2f){250 * ventana->escalaElementos.x, 3 * ventana->escalaElementos.y});

    // barraSeparacionTitulo
    sfRectangleShape_setPosition (elementos->barraSeparacionTitulo, (sfVector2f){24 * ventana->escalaElementos.x, 120 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->barraSeparacionTitulo, (sfVector2f){250 * ventana->escalaElementos.x, 3 * ventana->escalaElementos.y});

    // panelInterfaz
    sfRectangleShape_setPosition (elementos->panelInterfaz, (sfVector2f){0, 0});
    sfRectangleShape_setSize (elementos->panelInterfaz, (sfVector2f){350 * ventana->escalaElementos.x, 1009 * ventana->escalaElementos.y});

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){26 * ventana->escalaElementos.x, 2 * ventana->escalaElementos.y});

    // solapaCambiarInterfaz
    sfRectangleShape_setPosition (elementos->solapaCambiarInterfaz, (sfVector2f){350 * ventana->escalaElementos.x, 124 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->solapaCambiarInterfaz, (sfVector2f){60 * ventana->escalaElementos.x, 759 * ventana->escalaElementos.y});

    // ventanaEmergente
    sfRectangleShape_setPosition (elementos->ventanaEmergente, (sfVector2f){760 * ventana->escalaElementos.x, 380 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->ventanaEmergente, (sfVector2f){400 * ventana->escalaElementos.x, 300 * ventana->escalaElementos.y});
}

/** \brief Liberar, de manera segura, todas los textos comunes (compartidas) entre las interfaces de contactos y salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 */
static void recursosComunesContactosSalas_liberarTextos (s_recursosComunesContactosSalasTextos *textos)
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
static void recursosComunesContactosSalas_liberarElementos (s_recursosComunesContactosSalasElementos *elementos)
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
static void recursosComunesContactosSalas_liberarVistas (s_recursosComunesContactosSalasVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->UI);
    DESTRUCTOR_SEGURO_VISTA (vistas->mensajes);
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



void manejarRedimensionamientoVentanaContactosSalas (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoRedimensionamiento)
{
    if (eventoRedimensionamiento.size.width < ANCHO_MINIMO_VENTANA)
        aplicacion->ventana.tamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        aplicacion->ventana.tamVentana.x = eventoRedimensionamiento.size.width;

    if (eventoRedimensionamiento.size.height < ALTO_MINIMO_VENTANA)
        aplicacion->ventana.tamVentana.y = ALTO_MINIMO_VENTANA;
    else
        aplicacion->ventana.tamVentana.y = eventoRedimensionamiento.size.height;

    sfRenderWindow_setSize (aplicacion->renderizado, (sfVector2u){((unsigned int)(aplicacion->ventana.tamVentana.x)), ((unsigned int)(aplicacion->ventana.tamVentana.y))});

    crearEscalaElementos (&(aplicacion->ventana));
    crearEscalaPixeles (&(aplicacion->ventana));

    recursosComunesContactosSalas_tamYPosVentana (recursosComunesContactosSalas, &(aplicacion->ventana));

    // Redimensionar vista UI
    sfView_setSize (recursosComunesContactosSalas->vistas.UI, aplicacion->ventana.tamVentana);
    sfView_setCenter (recursosComunesContactosSalas->vistas.UI, (sfVector2f){aplicacion->ventana.tamVentana.x / 2.0f, aplicacion->ventana.tamVentana.y / 2.0f});
}

bool manejarEscribirMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE)
    {
        ingresarCaracterABuffer (recursosComunesContactosSalas->bufferMensaje, MAX_BUFFER_MENSAJE, eventoChar);
        sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->bufferMensaje);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){(512.5 * (ventana->escalaElementos.x)) + limiteTextoAux.width, 943 * (ventana->escalaElementos.y)});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarEnterEnviarMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_aplicacion *aplicacion)
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

bool manejarDesplazarArribaAreaMensajes (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarDesplazarAbajoAreaMensajes (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarScrollAreaMensajes (s_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll)
{
    if (recursosComunesContactosSalas->habilitaciones.areaMensajes == HABILITAR_AREA_MENSAJES)
    {
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -eventoScroll.mouseWheelScroll.delta * VELOCIDAD_SCROLL});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}


























