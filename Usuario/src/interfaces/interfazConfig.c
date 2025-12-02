#include "../../include/interfaces/interfazConfig.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int interfazConfig_inicializarTexto (s_interfazConfigTexto *texto);
static int interfazConfig_inicializarElementos (s_interfazConfigElementos *elementos);

static void interfazConfig_configurarTexto (s_interfazConfigTexto *texto, const s_fuentes *fuentes);
static void interfazConfig_configurarElementos (s_interfazConfigElementos *elementos);

static void interfazConfig_tamYPosVentanaTexto (s_interfazConfigTexto *texto, const s_ventana *ventana);
static void interfazConfig_tamYPosVentanaElementos (s_interfazConfigElementos *elementos, const s_ventana *ventana);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazConfig_inicializar (s_interfazConfig *interfazConfig)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    interfazConfig->texto.textoConfig = NULL;


    // ELEMENTOS

    interfazConfig->elementos.rectanguloVolver = NULL;


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (interfazConfig_inicializarTexto (&(interfazConfig->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazConfig_inicializarElementos (&(interfazConfig->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazConfig_configurar (s_interfazConfig *interfazConfig, const s_fuentes *fuentes, const s_ventana *ventana)
{
    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazConfig_configurarTexto (&(interfazConfig->texto), fuentes);


    // ELEMENTOS

    interfazConfig_configurarElementos (&(interfazConfig->elementos));


    // --------------- TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazConfig_tamYPosVentanaTexto (&(interfazConfig->texto), ventana);


    // ELEMENTOS

    interfazConfig_tamYPosVentanaElementos (&(interfazConfig->elementos), ventana);
}

void interfazConfig_accion (s_aplicacion *aplicacion, const s_interfazConfig *interfazConfig)
{
    sfEvent evento;

    sfRenderWindow_pollEvent (aplicacion->renderizado, &evento);
    switch (evento.type)
    {

    case sfEvtClosed:
        aplicacion->aplicacionEjecutandose = DETENER_APLICACION;
        break;


    case sfEvtResized:
       // if (manejarRedimensionamientoVentana (aplicacion, evento) == ERROR_SIN_MEMORIA)
        break;


    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnRectangulo (aplicacion->renderizado, interfazConfig->elementos.rectanguloVolver))
                aplicacion->usuario.interfazActual = aplicacion->usuario.ultimaInterfazUtilizada;
        }


    default:
        break;
    }
}

void interfazConfig_actualizar (s_interfazConfig *interfazConfig)
{

}

void interfazConfig_renderizar (sfRenderWindow *renderizado, const s_interfazConfig *interfazConfig)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    sfRenderWindow_drawRectangleShape (renderizado, interfazConfig->elementos.rectanguloVolver, NULL);


    // TEXTO

    sfRenderWindow_drawText (renderizado, interfazConfig->texto.textoConfig, NULL);


    sfRenderWindow_display (renderizado);
}

void interfazConfig_liberar (s_interfazConfig *interfazConfig)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO

    DESTRUCTOR_SEGURO_TEXTO (interfazConfig->texto.textoConfig);


    // ELEMENTOS

    DESTRUCTOR_SEGURO_RECTANGULO (interfazConfig->elementos.rectanguloVolver);
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto de la interfaz de configuraciones.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de configuraciones.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazConfig_inicializarTexto (s_interfazConfigTexto *texto)
{
    texto->textoConfig = sfText_create ();
    if (!texto->textoConfig)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear texto textoConfig.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos de la interfaz de configuraciones.
 *
 * Crea todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de configuraciones.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazConfig_inicializarElementos (s_interfazConfigElementos *elementos)
{
    elementos->rectanguloVolver = sfRectangleShape_create ();
    if (!elementos->rectanguloVolver)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear elemento rectanguloVolver.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de texto de la interfaz de configuraciones.
 *
 * Configura todos los recursos graficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de configuraciones.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazConfig_configurarTexto (s_interfazConfigTexto *texto, const s_fuentes *fuentes)
{
    // textoConfig
    sfText_setFont (texto->textoConfig, fuentes->fuente1);
    sfText_setString (texto->textoConfig, "CONFIGURACIONES");
    sfText_setFillColor (texto->textoConfig, sfColor_fromRGB (0, 0, 0));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de configuraciones.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de configuraciones.
 *
 */
static void interfazConfig_configurarElementos (s_interfazConfigElementos *elementos)
{
    // rectanguloVolver
    sfRectangleShape_setFillColor (elementos->rectanguloVolver, sfColor_fromRGB (0, 0, 0));
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico de la interfaz de configuraciones.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de configuraciones.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazConfig_tamYPosVentanaTexto (s_interfazConfigTexto *texto, const s_ventana *ventana)
{
    // textoConfig
    sfText_setPosition (texto->textoConfig, (sfVector2f){1000 * ventana->escalaElementos.x, 500 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->textoConfig, 36 * ventana->escalaPixeles);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada elemento grafico de la interfaz de configuraciones.
 *
 * Establecer a todos los elementos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de configuraciones.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazConfig_tamYPosVentanaElementos (s_interfazConfigElementos *elementos, const s_ventana *ventana)
{
    // rectanguloVolver
    sfRectangleShape_setPosition (elementos->rectanguloVolver, (sfVector2f){1000 * ventana->escalaElementos.x, 650 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->rectanguloVolver, (sfVector2f){60 * ventana->escalaElementos.x, 60 * ventana->escalaElementos.y});
}













