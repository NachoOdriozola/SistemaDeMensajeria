#include "interfacesGraficas/interfazAutenticacion/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void posicionar_punto_insercion_nombre (UiAutenticacion *uiAutenticacion);
static void posicionar_punto_insercion_contrasenia (UiAutenticacion *uiAutenticacion);

static bool procesar_click_escribir_nombre (const sfRenderWindow *renderizado, UiAutenticacion *uiAutenticacion);
static bool procesar_click_escribir_contrasenia (const sfRenderWindow *renderizado, UiAutenticacion *uiAutenticacion);
static bool procesar_click_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);
static bool procesar_click_cambiar_a_ui_registro (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);

static bool procesar_escribir_nombre (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, sfEvent eventoChar);

static bool procesar_enter_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);

static bool procesar_pegar_nombre_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);
static bool procesar_pegar_contrasenia_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);

static void deshabilitar_focos (UiAutenticacion *uiAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_autenticacion_accionar (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
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
                if (procesar_click_escribir_nombre (contextoAplicacion->renderizado, uiAutenticacion)) break;
                if (procesar_click_escribir_contrasenia (contextoAplicacion->renderizado, uiAutenticacion)) break;
                if (procesar_click_intentar_autenticacion (contextoAplicacion, uiAutenticacion)) break;
                if (procesar_click_cambiar_a_ui_registro (contextoAplicacion, uiAutenticacion)) break;
                deshabilitar_focos (uiAutenticacion);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_nombre (contextoAplicacion, uiAutenticacion, evento)) break;
            if (procesar_escribir_contrasenia (contextoAplicacion, uiAutenticacion, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentar_autenticacion (contextoAplicacion, uiAutenticacion)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegar_nombre_desde_portapapeles (contextoAplicacion, uiAutenticacion)) break;
                if (procesar_pegar_contrasenia_desde_portapapeles (contextoAplicacion, uiAutenticacion)) break;
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


static void mostrar_feedback_cargando_solicitud (UiAutenticacion *uiAutenticacion)
{
    texto_de_carga_iniciar (&(uiAutenticacion->uiAcceso->logica.textoDeCarga));
    sfText_setString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, "Cargando");
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_credenciales_invalidas (UiAutenticacion *uiAutenticacion)
{
    uint32_t bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
    sfText_setUnicodeString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, bufferErrorCredenciales);
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_error_conexion (UiAutenticacion *uiAutenticacion)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, bufferErrorConexion);
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void procesar_resultado_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, ResultadoIntentoAutenticacion resultadoIntentoAutenticacion)
{
    switch (resultadoIntentoAutenticacion)
    {
        case INTENTO_AUTENTICACION_SOLICITUD_ENVIADA:
            mostrar_feedback_cargando_solicitud (uiAutenticacion);
            break;
        
        case INTENTO_AUTENTICACION_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credenciales_invalidas (uiAutenticacion);
            break;

        case INTENTO_AUTENTICACION_ERROR_CONEXION:
            mostrar_feedback_error_conexion (uiAutenticacion);
            break;

        default:
            break;
    }
}


static void posicionar_punto_insercion_nombre (UiAutenticacion *uiAutenticacion)
{
    sfFloatRect limitesAuxEscribirNombre;

    limitesAuxEscribirNombre = sfText_getGlobalBounds (uiAutenticacion->uiAcceso->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (uiAutenticacion->uiAcceso->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.size.x, 208});
}

static void posicionar_punto_insercion_contrasenia (UiAutenticacion *uiAutenticacion)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (uiAutenticacion->uiAcceso->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (uiAutenticacion->uiAcceso->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.size.x, 343});
}


static bool procesar_click_escribir_nombre (const sfRenderWindow *renderizado, UiAutenticacion *uiAutenticacion)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiAutenticacion->uiAcceso->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    uiAutenticacion->uiAcceso->foco = ESCRIBIR_NOMBRE;
    uiAutenticacion->foco = UI_AUTENTICACION_NINGUNO;
    posicionar_punto_insercion_nombre (uiAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribir_contrasenia (const sfRenderWindow *renderizado, UiAutenticacion *uiAutenticacion)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiAutenticacion->uiAcceso->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    uiAutenticacion->uiAcceso->foco = ESCRIBIR_CONTRASENIA;
    uiAutenticacion->foco = UI_AUTENTICACION_NINGUNO;
    posicionar_punto_insercion_contrasenia (uiAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if (!se_clickeo_en_rectangulo (contextoAplicacion->renderizado, uiAutenticacion->uiAcceso->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
        
    if (!comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        ResultadoIntentoAutenticacion resultadoIntentoAutenticacion;

        deshabilitar_focos (uiAutenticacion);
        resultadoIntentoAutenticacion = _ui_autenticacion_intentar_autenticacion (contextoAplicacion, uiAutenticacion);
        procesar_resultado_autenticacion (contextoAplicacion, uiAutenticacion, resultadoIntentoAutenticacion);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiar_a_ui_registro (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if (!se_clickeo_en_texto (contextoAplicacion->renderizado, uiAutenticacion->uiAcceso->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    _ui_autenticacion_cambiar_a_ui_registro (contextoAplicacion, uiAutenticacion);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, sfEvent eventoChar)
{
    if (uiAutenticacion->uiAcceso->foco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiAutenticacion->uiAcceso->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiAutenticacion->uiAcceso->textos.auxEscribirNombre, uiAutenticacion->uiAcceso->logica.nombreUsuario, 415);
        posicionar_punto_insercion_nombre (uiAutenticacion);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, sfEvent eventoChar)
{
    if (uiAutenticacion->uiAcceso->foco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiAutenticacion->uiAcceso->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiAutenticacion->uiAcceso->textos.auxEscribirContrasenia, uiAutenticacion->uiAcceso->logica.contrasenia, 415);
        posicionar_punto_insercion_contrasenia (uiAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if ((uiAutenticacion->uiAcceso->foco != ESCRIBIR_NOMBRE) &&
        (uiAutenticacion->uiAcceso->foco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    if (!comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        ResultadoIntentoAutenticacion resultadoIntentoAutenticacion;

        resultadoIntentoAutenticacion = _ui_autenticacion_intentar_autenticacion (contextoAplicacion, uiAutenticacion);
        procesar_resultado_autenticacion (contextoAplicacion, uiAutenticacion, resultadoIntentoAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_pegar_nombre_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if (uiAutenticacion->uiAcceso->foco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiAutenticacion->uiAcceso->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiAutenticacion->uiAcceso->textos.auxEscribirNombre, uiAutenticacion->uiAcceso->logica.nombreUsuario, 415);
        posicionar_punto_insercion_nombre (uiAutenticacion);
    }

    return EVENTO_MANEJADO;
}
 
static bool procesar_pegar_contrasenia_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if (uiAutenticacion->uiAcceso->foco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiAutenticacion->uiAcceso->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiAutenticacion->uiAcceso->textos.auxEscribirContrasenia, uiAutenticacion->uiAcceso->logica.contrasenia, 415);
        posicionar_punto_insercion_contrasenia (uiAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitar_focos (UiAutenticacion *uiAutenticacion)
{
    uiAutenticacion->uiAcceso->foco = UI_ACCESO_NINGUNO;
    uiAutenticacion->foco = UI_AUTENTICACION_NINGUNO;
}

