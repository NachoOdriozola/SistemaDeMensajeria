#include "interfacesGraficas/interfazRegistro/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool procesar_click_escribir_nombre (const sfRenderWindow *renderizado, UiRegistro *uiRegistro);
static bool procesar_click_escribir_contrasenia (const sfRenderWindow *renderizado, UiRegistro *uiRegistro);
static bool procesar_click_escribir_correo (const sfRenderWindow *renderizado, UiRegistro *uiRegistro);
static bool procesar_click_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);
static bool procesar_click_cambiar_a_ui_autenticacion (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);

static bool procesar_escribir_nombre (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar);
static bool procesar_escribir_correo (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar);

static bool procesar_enter_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);

static bool procesar_pegar_nombre_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);
static bool procesar_pegar_contrasenia_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);
static bool procesar_pegar_correo_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);

static void deshabilitar_focos (UiRegistro *uiRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_registro_accionar (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
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
                if (procesar_click_escribir_nombre (contextoAplicacion->renderizado, uiRegistro)) break;
                if (procesar_click_escribir_contrasenia (contextoAplicacion->renderizado, uiRegistro)) break;
                if (procesar_click_escribir_correo (contextoAplicacion->renderizado, uiRegistro)) break;
                if (procesar_click_intentar_registro (contextoAplicacion, uiRegistro)) break;
                if (procesar_click_cambiar_a_ui_autenticacion (contextoAplicacion, uiRegistro)) break;
                deshabilitar_focos (uiRegistro);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_nombre (contextoAplicacion, uiRegistro, evento)) break;
            if (procesar_escribir_contrasenia (contextoAplicacion, uiRegistro, evento)) break;
            if (procesar_escribir_correo (contextoAplicacion, uiRegistro, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentar_registro (contextoAplicacion, uiRegistro)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegar_nombre_desde_portapapeles (contextoAplicacion, uiRegistro)) break;
                if (procesar_pegar_contrasenia_desde_portapapeles (contextoAplicacion, uiRegistro)) break;
                if (procesar_pegar_correo_desde_portapapeles (contextoAplicacion, uiRegistro)) break;
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


static void mostrar_feedback_cargando_solicitud (UiRegistro *uiRegistro)
{
    texto_de_carga_iniciar (&(uiRegistro->uiAcceso->logica.textoDeCarga));
    sfText_setString (uiRegistro->uiAcceso->textos.feedbackUsuario, "Cargando");
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_error_conexion (UiRegistro *uiRegistro)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (uiRegistro->uiAcceso->textos.feedbackUsuario, bufferErrorConexion);
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_credenciales_invalidas (UiRegistro *uiRegistro)
{
    uint32_t bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
    sfText_setUnicodeString (uiRegistro->uiAcceso->textos.feedbackUsuario, bufferDatosInvalidos);
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_datos_invalidos (UiRegistro *uiRegistro, const ValidacionRegistro *validacionRegistro)
{
    if (!validacionRegistro->nombreValido)
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirNombre, sfColor_fromRGB (160, 100, 90));

    if (!validacionRegistro->contraseniaValida)
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirContrasenia, sfColor_fromRGB (160, 100, 90));

    if (!validacionRegistro->correoValido)
        sfText_setFillColor (uiRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (160, 100, 90));
}

static void procesar_resultado_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, ResultadoIntentoRegistro resultadoIntentoRegistro)
{
    switch (resultadoIntentoRegistro.estado)
    {
        case INTENTO_REGISTRO_SOLICITUD_ENVIADA:
            mostrar_feedback_cargando_solicitud (uiRegistro);
            break;
        
        case INTENTO_REGISTRO_ERROR_CONEXION:
            mostrar_feedback_error_conexion (uiRegistro);
            break;
        
        case INTENTO_REGISTRO_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credenciales_invalidas (uiRegistro);
            mostrar_datos_invalidos (uiRegistro, &(resultadoIntentoRegistro.validacion));
            break;

        default:
            break;
    }
}


static void posicionar_punto_insercion_nombre (UiRegistro *uiRegistro)
{
    sfFloatRect limitesAuxEscribirNombre;
    
    limitesAuxEscribirNombre = sfText_getGlobalBounds (uiRegistro->uiAcceso->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (uiRegistro->uiAcceso->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.size.x, 198});
}

static void posicionar_punto_insercion_contrasenia (UiRegistro *uiRegistro)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (uiRegistro->uiAcceso->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (uiRegistro->uiAcceso->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.size.x, 323});
}

static void posicionar_punto_insercion_correo (UiRegistro *uiRegistro)
{
    sfFloatRect limitesAuxEscribirCorreo;

    limitesAuxEscribirCorreo = sfText_getGlobalBounds (uiRegistro->textos.auxEscribirCorreo);
    sfRectangleShape_setPosition (uiRegistro->uiAcceso->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirCorreo.size.x, 420});
}


static bool procesar_click_escribir_nombre (const sfRenderWindow *renderizado, UiRegistro *uiRegistro)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiRegistro->uiAcceso->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    uiRegistro->uiAcceso->foco = ESCRIBIR_NOMBRE;
    uiRegistro->foco = UI_REGISTRO_NINGUNO;
    posicionar_punto_insercion_nombre (uiRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribir_contrasenia (const sfRenderWindow *renderizado, UiRegistro *uiRegistro)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiRegistro->uiAcceso->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    uiRegistro->uiAcceso->foco = ESCRIBIR_CONTRASENIA;
    uiRegistro->foco = UI_REGISTRO_NINGUNO;
    posicionar_punto_insercion_contrasenia (uiRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribir_correo (const sfRenderWindow *renderizado, UiRegistro *uiRegistro)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiRegistro->elementos.barraEscribirCorreo))
        return EVENTO_NO_MANEJADO;

    uiRegistro->foco = ESCRIBIR_CORREO;
    uiRegistro->uiAcceso->foco = UI_ACCESO_NINGUNO;
    posicionar_punto_insercion_correo (uiRegistro);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    if (!se_clickeo_en_rectangulo (contextoAplicacion->renderizado, uiRegistro->uiAcceso->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
        
    if (!comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        ResultadoIntentoRegistro resultadoIntentoRegistro;

        deshabilitar_focos (uiRegistro);
        resultadoIntentoRegistro = _ui_registro_intentar_registro (contextoAplicacion, uiRegistro);
        procesar_resultado_registro (contextoAplicacion, uiRegistro, resultadoIntentoRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiar_a_ui_autenticacion (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    if (!se_clickeo_en_texto (contextoAplicacion->renderizado, uiRegistro->uiAcceso->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    _ui_registro_cambiar_a_ui_autenticacion (contextoAplicacion, uiRegistro);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar)
{
    if (uiRegistro->uiAcceso->foco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiRegistro->uiAcceso->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->uiAcceso->textos.auxEscribirNombre, uiRegistro->uiAcceso->logica.nombreUsuario, 415);
        posicionar_punto_insercion_nombre (uiRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar)
{
    if (uiRegistro->uiAcceso->foco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiRegistro->uiAcceso->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->uiAcceso->textos.auxEscribirContrasenia, uiRegistro->uiAcceso->logica.contrasenia, 415);
        posicionar_punto_insercion_contrasenia (uiRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_correo (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, sfEvent eventoChar)
{
    if (uiRegistro->foco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO, eventoChar) == EXITO)
    {
        sfText_setFillColor (uiRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->textos.auxEscribirCorreo, uiRegistro->logica.correoElectronico, 415);
        posicionar_punto_insercion_correo (uiRegistro);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    if ((uiRegistro->uiAcceso->foco != ESCRIBIR_NOMBRE) &&
        (uiRegistro->uiAcceso->foco != ESCRIBIR_CONTRASENIA) &&
        (uiRegistro->foco != ESCRIBIR_CORREO))
        return EVENTO_NO_MANEJADO;

    if (!comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        ResultadoIntentoRegistro resultadoIntentoRegistro;

        resultadoIntentoRegistro = _ui_registro_intentar_registro (contextoAplicacion, uiRegistro);
        procesar_resultado_registro (contextoAplicacion, uiRegistro, resultadoIntentoRegistro);
    }

    return EVENTO_NO_MANEJADO;
}


static bool procesar_pegar_nombre_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    if (uiRegistro->uiAcceso->foco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiRegistro->uiAcceso->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->uiAcceso->textos.auxEscribirNombre, uiRegistro->uiAcceso->logica.nombreUsuario, 415);
        posicionar_punto_insercion_nombre (uiRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegar_contrasenia_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    sfFloatRect limiteTextoAux;

    if (uiRegistro->uiAcceso->foco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiRegistro->uiAcceso->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        sfText_setFillColor (uiRegistro->uiAcceso->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->uiAcceso->textos.auxEscribirContrasenia, uiRegistro->uiAcceso->logica.contrasenia, 415);
        posicionar_punto_insercion_contrasenia (uiRegistro);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_pegar_correo_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    sfFloatRect limiteTextoAux;

    if (uiRegistro->foco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO) == EXITO)
    {
        sfText_setFillColor (uiRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitar_visualizacion_texto_sobre_barra_escritura (uiRegistro->textos.auxEscribirCorreo, uiRegistro->logica.correoElectronico, 415);
        posicionar_punto_insercion_correo (uiRegistro);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitar_focos (UiRegistro *uiRegistro)
{
    uiRegistro->uiAcceso->foco = UI_ACCESO_NINGUNO;
    uiRegistro->foco = UI_REGISTRO_NINGUNO;
}
