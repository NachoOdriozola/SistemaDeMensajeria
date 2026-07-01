#include "../../../include/interfacesGraficas/interfazRegistro/interfazRegistro.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static void actualizar (t_interfazRegistro *interfazRegistro);
static void renderizar (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazRegistro_inicializarValoresNulos (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    _interfazRegistro_inicializarValoresNulosTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_inicializarValoresNulosElementos (&(interfazRegistro->elementos));
}

t_codigoRetorno interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    if (_interfazRegistro_inicializarTextos (&(interfazRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazRegistro_inicializarElementos (&(interfazRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazRegistro_configurarInterfaz (interfazRegistro, recursosComunesAutenticacionRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazRegistro_configurarTextos (&(interfazRegistro->textos), &(interfazRegistro->recursosComunesAutenticacionRegistro->fuentes));

    // ELEMENTOS
    _interfazRegistro_configurarElementos (&(interfazRegistro->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazRegistro_tamYPosVentanaTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_tamYPosVentanaElementos (&(interfazRegistro->elementos));
}

void ejecutarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    accion (contextoAplicacion, interfazRegistro);
    actualizar (interfazRegistro);
    renderizar (contextoAplicacion->renderizado, interfazRegistro);
}

void interfazRegistro_liberar (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    _interfazRegistro_liberarTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_liberarElementos (&(interfazRegistro->elementos));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
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
                if (_interfazRegistro_manejarClickEscribirNombre (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (_interfazRegistro_manejarClickEscribirContrasenia (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (_interfazRegistro_manejarClickEscribirCorreo (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (_interfazRegistro_manejarClickIntentarRegistro (contextoAplicacion, interfazRegistro)) break;
                if (_interfazRegistro_manejarClickCambiarAInterfazAutenticacion (contextoAplicacion, interfazRegistro)) break;
                _interfazRegistro_deshabilitarFocos (interfazRegistro);
            }
            break;


        case sfEvtTextEntered:
            if (_interfazRegistro_manejarEscribirNombre (interfazRegistro, evento)) break;
            if (_interfazRegistro_manejarEscribirContrasenia (interfazRegistro, evento)) break;
            if (_interfazRegistro_manejarEscribirCorreo (interfazRegistro, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (_interfazRegistro_manejarEnterIntentarRegistro (contextoAplicacion, interfazRegistro)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (_interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirNombre (interfazRegistro)) break;
                if (_interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (interfazRegistro)) break;
                if (_interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirCorreo (interfazRegistro)) break;
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
static void actualizar (t_interfazRegistro *interfazRegistro)
{
    // --------------- PUNTO DE INSERCION ---------------
    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA ||
         interfazRegistro->estadoFoco == ESCRIBIR_CORREO))
        actualizarPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de registro en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(interfazRegistro->recursosComunesAutenticacionRegistro->elementos));
    _interfazRegistro_renderizarElementos (renderizado, &(interfazRegistro->elementos));

    // TEXTOS
    recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(interfazRegistro->recursosComunesAutenticacionRegistro->textos));
    _interfazRegistro_renderizarTextos (renderizado, &(interfazRegistro->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}
