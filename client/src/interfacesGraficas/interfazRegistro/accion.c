#include "interfacesGraficas/interfazRegistro/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_escribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static bool procesar_click_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

static bool procesar_escribir_nombre (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool procesar_escribir_correo (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

static bool procesar_enter_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_interfazRegistro *interfazRegistro);
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_interfazRegistro *interfazRegistro);
static bool procesar_pegarTextoDesdePortapapeles_escribir_correo (t_interfazRegistro *interfazRegistro);

static void deshabilitarFocos (t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_accion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
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
                if (procesar_click_escribirNombre (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (procesar_click_escribirContrasenia (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (procesar_click_escribirCorreo (contextoAplicacion->renderizado, interfazRegistro)) break;
                if (procesar_click_intentarRegistrar (contextoAplicacion, interfazRegistro)) break;
                if (procesar_click_cambiarAInterfazAutenticacion (contextoAplicacion, interfazRegistro)) break;
                deshabilitarFocos (interfazRegistro);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_nombre (interfazRegistro, evento)) break;
            if (procesar_escribir_contrasenia (interfazRegistro, evento)) break;
            if (procesar_escribir_correo (interfazRegistro, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentarRegistrar (contextoAplicacion, interfazRegistro)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegarTextoDesdePortapapeles_escribir_nombre (interfazRegistro)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (interfazRegistro)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_correo (interfazRegistro)) break;
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


static void posicionarPuntoInsercionBarraEscrituraNombre (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirNombre;
    
    limitesAuxEscribirNombre = sfText_getGlobalBounds (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.width, 198});
}

static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.width, 323});
}

static void posicionarPuntoInsercionBarraEscrituraCorreo (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirCorreo;

    limitesAuxEscribirCorreo = sfText_getGlobalBounds (interfazRegistro->textos.auxEscribirCorreo);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirCorreo.width, 420});
}


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->elementos.barraEscribirCorreo))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->estadoFoco = ESCRIBIR_CORREO;
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
        
    deshabilitarFocos (interfazRegistro);
    _interfazRegsitro_intentarRegistrar (contextoAplicacion, interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    if (contextoAplicacion->solicitudEnCurso)
    {
        sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "No se puede cambiar de interfaz, hay una solicitud en curso . . .");
        centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
    }
    else
        _interfazRegistro_cambiarAInterfazAutenticacion (contextoAplicacion, interfazRegistro);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_correo (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO, eventoChar) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA) &&
        (interfazRegistro->estadoFoco != ESCRIBIR_CORREO))
        return EVENTO_NO_MANEJADO;

    _interfazRegsitro_intentarRegistrar (contextoAplicacion, interfazRegistro);
    
    return EVENTO_NO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_interfazRegistro *interfazRegistro)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegarTextoDesdePortapapeles_escribir_correo (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitarFocos (t_interfazRegistro *interfazRegistro)
{
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazRegistro->estadoFoco = IR_NINGUNO;
}
