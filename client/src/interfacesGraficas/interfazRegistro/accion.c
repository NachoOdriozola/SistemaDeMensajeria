#include "interfacesGraficas/interfazRegistro/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_escribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);
static bool procesar_click_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static bool procesar_click_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

static bool procesar_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool procesar_escribir_correo (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

static bool procesar_enter_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static bool procesar_pegarTextoDesdePortapapeles_escribir_correo (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

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
            if (procesar_escribir_nombre (contextoAplicacion, interfazRegistro, evento)) break;
            if (procesar_escribir_contrasenia (contextoAplicacion, interfazRegistro, evento)) break;
            if (procesar_escribir_correo (contextoAplicacion, interfazRegistro, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentarRegistrar (contextoAplicacion, interfazRegistro)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegarTextoDesdePortapapeles_escribir_nombre (contextoAplicacion, interfazRegistro)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (contextoAplicacion, interfazRegistro)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_correo (contextoAplicacion, interfazRegistro)) break;
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


static void mostrar_feedback_cargando (t_interfazRegistro *interfazRegistro)
{
    textoDeCarga_iniciar (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.textoDeCarga));
    sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Cargando");
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_errorConexion (t_interfazRegistro *interfazRegistro)
{
    sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_credencialesInvalidas (t_interfazRegistro *interfazRegistro)
{
    sfUint32 bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferDatosInvalidos);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_datosInvalidos (t_interfazRegistro *interfazRegistro, const _t_resultado_validacionDatosRegistro *resultado_validacionDatosRegistro)
{
    if (!resultado_validacionDatosRegistro->nombreValido)
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (160, 100, 90));

    if (!resultado_validacionDatosRegistro->contraseniaValida)
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (160, 100, 90));

    if (!resultado_validacionDatosRegistro->correoValido)
        sfText_setColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (160, 100, 90));
}

static void intentarRegistrarYProcesarResultadoOperacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    _t_resultado_intentarRegistrar resultado_intentarRegistrar;

    resultado_intentarRegistrar = _interfazRegsitro_intentar_registrar (contextoAplicacion, interfazRegistro);
    switch (resultado_intentarRegistrar.tipo)
    {
        case INTENTARREGISTRAR_RESULTADO_EXITO:
            mostrar_feedback_cargando (interfazRegistro);
            break;
        
        case INTENTARREGISTRAR_RESULTADO_ERROR_CONEXION:
            mostrar_feedback_errorConexion (interfazRegistro);
            break;
        
        case INTENTARREGISTRAR_RESULTADO_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credencialesInvalidas (interfazRegistro);
            mostrar_datosInvalidos (interfazRegistro, &(resultado_intentarRegistrar.validacion));
            break;

        default:
            break;
    }
}


static void posicionarPuntoInsercion_escribirNombre (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirNombre;
    
    limitesAuxEscribirNombre = sfText_getGlobalBounds (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.width, 198});
}

static void posicionarPuntoInsercion_escribirContrasenia (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.width, 323});
}

static void posicionarPuntoInsercion_escribirCorreo (t_interfazRegistro *interfazRegistro)
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
    posicionarPuntoInsercion_escribirNombre (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    posicionarPuntoInsercion_escribirContrasenia (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->elementos.barraEscribirCorreo))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->estadoFoco = ESCRIBIR_CORREO;
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    posicionarPuntoInsercion_escribirCorreo (interfazRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
        
    if (!comunicacion_haySolicitudEnCurso (contextoAplicacion))
    {
        deshabilitarFocos (interfazRegistro);
        intentarRegistrarYProcesarResultadoOperacion (contextoAplicacion, interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    _interfazRegistro_cambiarAInterfaz_autenticacion (contextoAplicacion, interfazRegistro);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercion_escribirNombre (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercion_escribirContrasenia (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_correo (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO, eventoChar) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercion_escribirCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA) &&
        (interfazRegistro->estadoFoco != ESCRIBIR_CORREO))
        return EVENTO_NO_MANEJADO;

    if (!comunicacion_haySolicitudEnCurso (contextoAplicacion))
        intentarRegistrarYProcesarResultadoOperacion (contextoAplicacion, interfazRegistro);

    return EVENTO_NO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercion_escribirNombre (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercion_escribirContrasenia (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegarTextoDesdePortapapeles_escribir_correo (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercion_escribirCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitarFocos (t_interfazRegistro *interfazRegistro)
{
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazRegistro->estadoFoco = IR_NINGUNO;
}
