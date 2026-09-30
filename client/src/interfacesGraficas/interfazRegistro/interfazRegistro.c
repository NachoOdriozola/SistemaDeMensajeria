#include "interfacesGraficas/interfazRegistro/interfazRegistro.h"


void ui_registro_inicializar (UiRegistro *uiRegistro)
{
    // TEXTOS
    _ui_registro_inicializar_textos (&(uiRegistro->textos));

    // ELEMENTOS
    _ui_registro_inicializar_elementos (&(uiRegistro->elementos));
}

CodigoRetorno ui_registro_crear (UiRegistro *uiRegistro, UiAcceso *uiAcceso)
{
    // --------------- ASIGNAR RECURSOS COMUNES ---------------

    uiRegistro->uiAcceso = uiAcceso;

    // --------------- CREAR RECURSOS GRAFICOS ---------------

    // TEXTOS
    if (_ui_registro_crear_textos (&(uiRegistro->textos), &(uiRegistro->uiAcceso->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_ui_registro_crear_elementos (&(uiRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void ui_registro_configurar (UiRegistro *uiRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _ui_registro_configurar_interfaz (uiRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_registro_configurar_textos (&(uiRegistro->textos));

    // ELEMENTOS
    _ui_registro_configurar_elementos (&(uiRegistro->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_registro_establecer_tam_y_pos_ventana_textos (&(uiRegistro->textos));

    // ELEMENTOS
    _ui_registro_establecer_tam_y_pos_ventana_elementos (&(uiRegistro->elementos));
}

void ui_registro_ejecutar (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    _ui_registro_accionar (contextoAplicacion, uiRegistro);
    _ui_registro_actualizar (contextoAplicacion, uiRegistro);
    _ui_registro_renderizar (contextoAplicacion->renderizado, uiRegistro);
}

void ui_registro_liberar (UiRegistro *uiRegistro)
{
    // TEXTOS
    _ui_registro_liberar_textos (&(uiRegistro->textos));

    // ELEMENTOS
    _ui_registro_liberar_elementos (&(uiRegistro->elementos));
}

