#include "../../../include/interfacesGraficas/interfazAutenticacion/interfazAutenticacion.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);
static void actualizar (t_interfazAutenticacion *interfazAutenticacion);
static void renderizar (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazAutenticacion_inicializarValoresNulos (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS
    _interfazAutenticacion_inicializarValoresNulosTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_inicializarValoresNulosElementos (&(interfazAutenticacion->elementos));
}

t_codigoRetorno interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS
    if (_interfazAutenticacion_inicializarTextos (&(interfazAutenticacion->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazAutenticacion_inicializarElementos (&(interfazAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazAutenticacion_configurarInterfaz (interfazAutenticacion, recursosComunesAutenticacionRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazAutenticacion_configurarTextos (&(interfazAutenticacion->textos), &(interfazAutenticacion->recursosComunesAutenticacionRegistro->fuentes));

    // ELEMENTOS
    _interfazAutenticacion_configurarElementos (&(interfazAutenticacion->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazAutenticacion_tamYPosVentanaTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_tamYPosVentanaElementos (&(interfazAutenticacion->elementos));
}

void ejecutarInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    accion (contextoAplicacion, interfazAutenticacion);
    actualizar (interfazAutenticacion);
    renderizar (contextoAplicacion->renderizado, interfazAutenticacion);
}

void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS
    _interfazAutenticacion_liberarTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_liberarElementos (&(interfazAutenticacion->elementos));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    sfEvent evento;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {
        case sfEvtClosed:
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtResized:
            sfRenderWindow_setSize (contextoAplicacion->renderizado, (sfVector2u){500, 620});
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (_interfazAutenticacion_manejarClickEscribirNombre (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (_interfazAutenticacion_manejarClickEscribirContrasenia (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (_interfazAutenticacion_manejarClickIntentarAutenticacion (contextoAplicacion, interfazAutenticacion)) break;
                if (_interfazAutenticacion_manejarClickCambiarAInterfazRegistro (contextoAplicacion, interfazAutenticacion)) break;
                _interfazAutenticacion_deshabilitarFocos (interfazAutenticacion);
            }
            break;


        case sfEvtTextEntered:
            if (_interfazAutenticacion_manejarEscribirNombre (interfazAutenticacion, evento)) break;
            if (_interfazAutenticacion_manejarEscribirContrasenia (interfazAutenticacion, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (_interfazAutenticacion_manejarEnterIntentarAutenticacion (contextoAplicacion, interfazAutenticacion)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (_interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirNombre (interfazAutenticacion)) break;
                if (_interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (interfazAutenticacion)) break;
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
static void actualizar (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- PUNTO DE INSERCION ---------------
    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA))
        actualizarPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de autenticacion en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos));
    _interfazAutenticacion_renderizarElementos (renderizado, &(interfazAutenticacion->elementos));

    // TEXTOS
    recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(interfazAutenticacion->recursosComunesAutenticacionRegistro->textos));
    _interfazAutenticacion_renderizarTextos (renderizado, &(interfazAutenticacion->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}

