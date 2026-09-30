#include "interfacesGraficas/interfazAutenticacion/interfazAutenticacion.h"


void ui_autenticacion_inicializar (UiAutenticacion *uiAutenticacion)
{
    // TEXTOS
    _ui_autenticacion_inicializar_textos (&(uiAutenticacion->textos));

    // ELEMENTOS
    _ui_autenticacion_inicializar_elementos (&(uiAutenticacion->elementos));
}

CodigoRetorno ui_autenticacion_crear (UiAutenticacion *uiAutenticacion, UiAcceso *uiAcceso)
{
    // --------------- ASIGNAR RECURSOS COMUNES ---------------

    uiAutenticacion->uiAcceso = uiAcceso;

    // --------------- CREAR RECURSOS GRAFICOS ---------------

    // TEXTOS
    if (_ui_autenticacion_crear_textos (&(uiAutenticacion->textos), &(uiAutenticacion->uiAcceso->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_ui_autenticacion_crear_elementos (&(uiAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void ui_autenticacion_configurar (UiAutenticacion *uiAutenticacion)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _ui_autenticacion_configurar_interfaz (uiAutenticacion);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_autenticacion_configurar_textos (&(uiAutenticacion->textos));

    // ELEMENTOS
    _ui_autenticacion_configurar_elementos (&(uiAutenticacion->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_autenticacion_establecer_tam_y_pos_ventana_textos (&(uiAutenticacion->textos));

    // ELEMENTOS
    _ui_autenticacion_establecer_tam_y_pos_ventana_elementos (&(uiAutenticacion->elementos));
}

void ui_autenticacion_ejecutar (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    _ui_autenticacion_accionar (contextoAplicacion, uiAutenticacion);
    _ui_autenticacion_actualizar (contextoAplicacion, uiAutenticacion);
    _ui_autenticacion_renderizar (contextoAplicacion->renderizado, uiAutenticacion);
}

void ui_autenticacion_liberar (UiAutenticacion *uiAutenticacion)
{
    // TEXTOS
    _ui_autenticacion_liberar_textos (&(uiAutenticacion->textos));

    // ELEMENTOS
    _ui_autenticacion_liberar_elementos (&(uiAutenticacion->elementos));
}

