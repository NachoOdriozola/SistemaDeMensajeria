#include "../../../include/interfacesGraficas/interfazConfig/interfazConfig.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig);
static void actualizar (t_interfazConfig *interfazConfig);
static void renderizar (sfRenderWindow *renderizado, const t_interfazConfig *interfazConfig);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


t_codigoRetorno interfazConfig_inicializar (t_interfazConfig *interfazConfig)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------
    // FUENTES
    _interfazConfig_inicializarValoresNulosFuentes (&(interfazConfig->fuentes));

    // TEXTOS
    _interfazConfig_inicializarValoresNulosTextos (&(interfazConfig->textos));

    // ELEMENTOS
    _interfazConfig_inicializarValoresNulosElementos (&(interfazConfig->elementos));

    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------
    // FUENTES
    if (_interfazConfig_inicializarFuentes (&(interfazConfig->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_interfazConfig_inicializarTextos (&(interfazConfig->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazConfig_inicializarElementos (&(interfazConfig->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazConfig_configurar (t_interfazConfig *interfazConfig)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazConfig_configurarInterfaz (interfazConfig);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazConfig_configurarTextos (&(interfazConfig->textos), &(interfazConfig->fuentes));

    // ELEMENTOS
    _interfazConfig_configurarElementos (&(interfazConfig->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazConfig_tamYPosVentanaTextos (&(interfazConfig->textos));

    // ELEMENTOS
    _interfazConfig_tamYPosVentanaElementos (&(interfazConfig->elementos));
}

void ejecutarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig)
{
    accion (contextoAplicacion, interfazConfig);
    actualizar (interfazConfig);
    renderizar (contextoAplicacion->renderizado, interfazConfig);
}

void interfazConfig_liberar (t_interfazConfig *interfazConfig)
{
    // FUENTES
    _interfazConfig_liberarFuentes (&(interfazConfig->fuentes));

    // TEXTOS
    _interfazConfig_liberarTextos (&(interfazConfig->textos));

    // ELEMENTOS
    _interfazConfig_liberarElementos (&(interfazConfig->elementos));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig)
{
    sfEvent evento;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {

        case sfEvtClosed:
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (clickEnRectangulo (contextoAplicacion->renderizado, interfazConfig->elementos.rectanguloVolver))
                    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
            }
            break;


        default:
            break;
        }
    }
}

/*
*Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
* Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void actualizar (t_interfazConfig *interfazConfig)
{

}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de configuraciones en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, const t_interfazConfig *interfazConfig)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (223, 231, 233));

    // --------------- RENDERIZAR RECURSOS GRAFICOS --------------- 
    // ELEMENTOS
    _interfazConfig_renderizarElementos (renderizado, &(interfazConfig->elementos));

    // TEXTOS
    _interfazConfig_renderizarTextos (renderizado, &(interfazConfig->textos));

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}

