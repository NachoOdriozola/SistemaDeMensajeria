#include "interfacesGraficas/interfazAutenticacion/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static bool procesar_escribir_nombre (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);

static bool procesar_enter_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_interfazAutenticacion *interfazAutenticacion);

static void deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_accion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
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
                if (procesar_click_escribirNombre (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (procesar_click_escribirContrasenia (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (procesar_click_intentarAutenticar (contextoAplicacion, interfazAutenticacion)) break;
                if (procesar_click_cambiarAInterfazRegistro (contextoAplicacion, interfazAutenticacion)) break;
                deshabilitarFocos (interfazAutenticacion);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_nombre (interfazAutenticacion, evento)) break;
            if (procesar_escribir_contrasenia (interfazAutenticacion, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentarAutenticar (contextoAplicacion, interfazAutenticacion)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegarTextoDesdePortapapeles_escribir_nombre (interfazAutenticacion)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (interfazAutenticacion)) break;
            }

            break;


        default:
            break;
        }
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void posicionarPuntoInsercionBarraEscrituraNombre (t_interfazAutenticacion *interfazAutenticacion)
{
    sfFloatRect limitesAuxEscribirNombre;

    limitesAuxEscribirNombre = sfText_getGlobalBounds (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.width, 208});
}

static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_interfazAutenticacion *interfazAutenticacion)
{
    sfFloatRect limitesAuxEscribirContrasenia;

    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.width, 343});
}


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    deshabilitarFocos (interfazAutenticacion);
    _interfazAutenticacion_intentarAutenticar (contextoAplicacion, interfazAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    if (contextoAplicacion->solicitudEnCurso)
    {
        sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "No se puede cambiar de interfaz, hay una solicitud en curso . . .");
        centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
    }
    else
        _interfazAutenticacion_cambiarAInterfazRegistro (contextoAplicacion, interfazAutenticacion);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    _interfazAutenticacion_intentarAutenticar (contextoAplicacion, interfazAutenticacion);

    return EVENTO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setColor (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}
 
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion)
{
    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

