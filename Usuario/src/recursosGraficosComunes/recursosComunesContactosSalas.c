#include "../../include/recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int recursosComunesContactosSalas_inicializarTexto (s_recursosComunesContactosSalasTexto *texto);
static int recursosComunesContactosSalas_inicializarElementos (s_recursosComunesContactosSalasElementos *elementos);

static void recursosComunesContactosSalas_configurarTexto (s_recursosComunesContactosSalasTexto *texto, const s_fuentes *fuentes);
static void recursosComunesContactosSalas_configurarElementos (s_recursosComunesContactosSalasElementos *elementos);

static void recursosComunesContactosSalas_tamYPosVentanaTexto (s_recursosComunesContactosSalasTexto *texto, const s_ventana *ventana);
static void recursosComunesContactosSalas_tamYPosVentanaElementos (s_recursosComunesContactosSalasElementos *elementos, const s_ventana *ventana);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesContactosSalas_inicializar (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    recursosComunesContactosSalas->texto.alertaNotificaciones = NULL;
    recursosComunesContactosSalas->texto.auxEscribirMensaje = NULL;
    recursosComunesContactosSalas->texto.cerrarVentanaEmergente = NULL;
    recursosComunesContactosSalas->texto.configuraciones = NULL;
    recursosComunesContactosSalas->texto.nombreCambiarInterfaz = NULL;
    recursosComunesContactosSalas->texto.nombreUsuario = NULL;
    recursosComunesContactosSalas->texto.notificaciones = NULL;
    recursosComunesContactosSalas->texto.tituloInterfaz = NULL;
    recursosComunesContactosSalas->texto.tituloVentanaEmergente = NULL;


    // ELEMENTOS

    recursosComunesContactosSalas->elementos.barraEscribirMensaje = NULL;
    recursosComunesContactosSalas->elementos.barraSeparacionNombre = NULL;
    recursosComunesContactosSalas->elementos.barraSeparacionTitulo = NULL;
    recursosComunesContactosSalas->elementos.panelInterfaz = NULL;
    recursosComunesContactosSalas->elementos.puntoInsercion = NULL;
    recursosComunesContactosSalas->elementos.solapaCambiarInterfaz = NULL;
    recursosComunesContactosSalas->elementos.ventanaEmergente = NULL;


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (recursosComunesContactosSalas_inicializarTexto (&(recursosComunesContactosSalas->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (recursosComunesContactosSalas_inicializarElementos (&(recursosComunesContactosSalas->elementos)) == ERROR_INICIALIZACION)
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

    // TEXTO

    recursosComunesContactosSalas_configurarTexto (&(recursosComunesContactosSalas->texto), fuentes);


    // ELEMENTOS

    recursosComunesContactosSalas_configurarElementos (&(recursosComunesContactosSalas->elementos));
}

void recursosComunesContactosSalas_tamYPosVentana (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana)
{
    // --------------- TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTO

    recursosComunesContactosSalas_tamYPosVentanaTexto (&(recursosComunesContactosSalas->texto), ventana);


    // ELEMENTOS

    recursosComunesContactosSalas_tamYPosVentanaElementos (&(recursosComunesContactosSalas->elementos), ventana);
}

void recursosComunesContactosSalas_renderizarTexto (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasTexto *recursosComunesContactosSalasTexto)
{
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->alertaNotificaciones, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->configuraciones, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->nombreCambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->notificaciones, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesContactosSalasTexto->tituloInterfaz, NULL);
}

void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasElementos *recursosComunesContactosSalasElementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalasElementos->panelInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalasElementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalasElementos->barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalasElementos->barraSeparacionTitulo, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalasElementos->solapaCambiarInterfaz, NULL);
}

void recursosComunesContactosSalas_liberar (s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO

    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.alertaNotificaciones);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.auxEscribirMensaje);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.cerrarVentanaEmergente);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.configuraciones);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.nombreCambiarInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.nombreUsuario);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.notificaciones);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.tituloInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesContactosSalas->texto.tituloVentanaEmergente);


    // ELEMENTOS

    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.barraEscribirMensaje);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.barraSeparacionNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.barraSeparacionTitulo);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.panelInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.solapaCambiarInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesContactosSalas->elementos.ventanaEmergente);
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Crear todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesContactosSalas_inicializarTexto (s_recursosComunesContactosSalasTexto *texto)
{
    texto->alertaNotificaciones = sfText_create ();
    if (!texto->alertaNotificaciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto alertaNotificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    texto->auxEscribirMensaje = sfText_create ();
    if (!texto->auxEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto auxEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    texto->cerrarVentanaEmergente = sfText_create ();
    if (!texto->cerrarVentanaEmergente)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto cerrarVentanaEmergente.\n");
        return ERROR_INICIALIZACION;
    }

    texto->configuraciones = sfText_create ();
    if (!texto->configuraciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto configuraciones.\n");
        return ERROR_INICIALIZACION;
    }

    texto->nombreCambiarInterfaz = sfText_create ();
    if (!texto->nombreCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreCambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    texto->nombreUsuario = sfText_create ();
    if (!texto->nombreUsuario)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    texto->notificaciones = sfText_create ();
    if (!texto->notificaciones)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto notificaciones.\n");
        return ERROR_INICIALIZACION;
    }

    texto->tituloInterfaz = sfText_create ();
    if (!texto->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    texto->tituloVentanaEmergente = sfText_create ();
    if (!texto->tituloVentanaEmergente)
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

/** \brief Configurar los recursos graficos de texto comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Configura todos los recursos gráficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void recursosComunesContactosSalas_configurarTexto (s_recursosComunesContactosSalasTexto *texto, const s_fuentes *fuentes)
{
    // alertaNotificaciones
    sfText_setFont (texto->alertaNotificaciones, fuentes->fuente1);
    sfText_setString (texto->alertaNotificaciones, "!");
    sfText_setFillColor (texto->alertaNotificaciones, sfColor_fromRGB (255, 0, 0));

    // auxEscribirMensaje
    sfText_setFont (texto->auxEscribirMensaje, fuentes->fuente1);
    sfText_setFillColor (texto->auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));

    // cerrarVentanaEmergente
    sfText_setFont (texto->cerrarVentanaEmergente, fuentes->fuente1);
    sfText_setString (texto->cerrarVentanaEmergente, "X");
    sfText_setFillColor (texto->cerrarVentanaEmergente, sfColor_fromRGB (40, 54, 54));

    // configuraciones
    sfText_setFont (texto->configuraciones, fuentes->fuente1);
    sfText_setString (texto->configuraciones, "C");
    sfText_setFillColor (texto->configuraciones, sfColor_fromRGB (40, 54, 54));

    // nombreCambiarInterfaz
    sfText_setFont (texto->nombreCambiarInterfaz, fuentes->fuente1);
    sfText_setString (texto->nombreCambiarInterfaz, "SALAS");
    sfText_setFillColor (texto->nombreCambiarInterfaz, sfColor_fromRGB (34, 48, 48));
    sfText_rotate (texto->nombreCambiarInterfaz, -90);

    // nombreUsuario
    sfText_setFont (texto->nombreUsuario, fuentes->fuente1);
    sfText_setFillColor (texto->nombreUsuario, sfColor_fromRGB (34, 48, 48));

    // notificaciones
    sfText_setFont (texto->notificaciones, fuentes->fuente1);
    sfText_setString (texto->notificaciones, "N");
    sfText_setFillColor (texto->notificaciones, sfColor_fromRGB (34, 48, 48));

    // tituloInterfaz
    sfText_setFont (texto->tituloInterfaz, fuentes->fuente1);
    sfText_setString (texto->tituloInterfaz, "CONTACTOS");
    sfText_setFillColor (texto->tituloInterfaz, sfColor_fromRGB (34, 48, 48));

    // tituloVentanaEmergente
    sfText_setFont (texto->tituloVentanaEmergente, fuentes->fuente1);
    sfText_setFillColor (texto->tituloVentanaEmergente, sfColor_fromRGB (40, 54, 54));
}

/** \brief Configurar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void recursosComunesContactosSalas_configurarElementos (s_recursosComunesContactosSalasElementos *elementos)
{
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

/** \brief Establecer el tamaño y la posicion en pantalla de cada texto grafico comun (compartido) entre las interfaces de contactos y salas.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaTexto (s_recursosComunesContactosSalasTexto *texto, const s_ventana *ventana)
{
    // alertaNotificaciones
    sfText_setPosition (texto->alertaNotificaciones, (sfVector2f){320 * ventana->escalaElementos.x, 40 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->alertaNotificaciones, 38 * ventana->escalaPixeles);

    // auxEscribirMensaje
    sfText_setPosition (texto->auxEscribirMensaje, (sfVector2f){510 * ventana->escalaElementos.x, 912 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->auxEscribirMensaje, 26 * ventana->escalaPixeles);

    // cerrarVentanaEmergente
    sfText_setPosition (texto->cerrarVentanaEmergente, (sfVector2f){1070 * ventana->escalaElementos.x, 390 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->cerrarVentanaEmergente, 36 * ventana->escalaPixeles);

    // configuraciones
    sfText_setPosition (texto->configuraciones, (sfVector2f){305 * ventana->escalaElementos.x, 922 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->configuraciones, 46 * ventana->escalaPixeles);

    // nombreCambiarInterfaz
    sfText_setPosition (texto->nombreCambiarInterfaz, (sfVector2f){352 * ventana->escalaElementos.x, 574 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->nombreCambiarInterfaz, 46 * ventana->escalaPixeles);
    sfText_setLetterSpacing (texto->nombreCambiarInterfaz, 10 * ventana->escalaPixeles);

    // nombreUsuario
    sfText_setPosition (texto->nombreUsuario, (sfVector2f){35 * ventana->escalaElementos.x, 925 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->nombreUsuario, 36 * ventana->escalaPixeles);

    // notificaciones
    sfText_setPosition (texto->notificaciones, (sfVector2f){300 * ventana->escalaElementos.x, 35 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->notificaciones, 42 * ventana->escalaPixeles);

    // tituloInterfaz
    sfText_setPosition (texto->tituloInterfaz, (sfVector2f){62 * ventana->escalaElementos.x, 45 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->tituloInterfaz, 36 * ventana->escalaPixeles);

    // tituloVentanaEmergente
    sfText_setPosition (texto->tituloVentanaEmergente, (sfVector2f){840 * ventana->escalaElementos.x, 400 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->tituloVentanaEmergente, 32 * ventana->escalaPixeles);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico común (compartido) entre las interfaces de contactos y salas.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void recursosComunesContactosSalas_tamYPosVentanaElementos (s_recursosComunesContactosSalasElementos *elementos, const s_ventana *ventana)
{
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



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



bool manejarEscribirMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE)
    {
        ingresarCaracterABuffer (recursosComunesContactosSalas->bufferMensaje, MAX_BUFFER_MENSAJE, eventoChar);
        sfText_setString (recursosComunesContactosSalas->texto.auxEscribirMensaje, recursosComunesContactosSalas->bufferMensaje);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->texto.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){(512.5 * (ventana->escalaElementos.x)) + limiteTextoAux.width, 943 * (ventana->escalaElementos.y)});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

bool manejarEnterEnviarMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_aplicacion *aplicacion)
{
    if ((recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE) && (strlen (recursosComunesContactosSalas->bufferMensaje) > 0))
    {
        asignarMensaje (aplicacion, recursosComunesContactosSalas->bufferMensaje, MI_USUARIO);
        *(recursosComunesContactosSalas->bufferMensaje) = '\0';
        //enviar paquete
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}


























