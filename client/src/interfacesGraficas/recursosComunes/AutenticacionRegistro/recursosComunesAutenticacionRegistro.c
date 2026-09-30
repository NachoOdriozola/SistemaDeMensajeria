#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"


void ui_acceso_inicializar (UiAcceso *uiAcceso)
{
    // FUENTES
    _ui_acceso_inicializar_fuentes (&(uiAcceso->fuentes));

    // TEXTOS
    _ui_acceso_inicializar_textos (&(uiAcceso->textos));

    // ELEMENTOS
    _ui_acceso_inicializar_elementos (&(uiAcceso->elementos));

    //VISTAS
    _ui_acceso_inicializar_vistas (&(uiAcceso->vistas));
}

CodigoRetorno ui_acceso_crear (UiAcceso *uiAcceso)
{
    // FUENTES
    if (_ui_acceso_crear_fuentes (&(uiAcceso->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_ui_acceso_crear_textos (&(uiAcceso->textos), &(uiAcceso->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_ui_acceso_crear_elementos (&(uiAcceso->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //VISTAS
    if (_ui_acceso_crear_vistas (&(uiAcceso->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void ui_acceso_configurar (UiAcceso *uiAcceso)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _ui_acceso_configurar_interfaz (uiAcceso);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_acceso_configurar_textos (&(uiAcceso->textos));

    // ELEMENTOS
    _ui_acceso_configurar_elementos (&(uiAcceso->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_acceso_establecer_tam_y_pos_ventana_textos (&(uiAcceso->textos));

    // ELEMENTO
    _ui_acceso_establecer_tam_y_pos_ventana_elementos (&(uiAcceso->elementos));

    //VISTAS
    _ui_acceso_establecer_tam_vistas (&(uiAcceso->vistas));
}

void ui_acceso_activar_interfaz_autenticacion (UiAcceso *uiAcceso)
{
    _ui_acceso_activar_interfaz_autenticacion (uiAcceso);
}

void ui_acceso_activar_interfaz_registro (UiAcceso *uiAcceso)
{
    _ui_acceso_activar_interfaz_registro (uiAcceso);
}

void ui_acceso_renderizar_textos (sfRenderWindow *renderizado, const UiAccesoTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->botonIngresar, NULL);
    sfRenderWindow_drawText (renderizado, textos->cambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->feedbackUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void ui_acceso_renderizar_Elementos (sfRenderWindow *renderizado, const UiAccesoElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->subrayadoTitulo, NULL);
}

void ui_acceso_liberar (UiAcceso *uiAcceso)
{
    // FUENTES
    _ui_acceso_liberar_fuentes (&(uiAcceso->fuentes));

    // TEXTOS
    _ui_acceso_liberar_textos (&(uiAcceso->textos));

    // ELEMENTOS
    _ui_acceso_liberar_elementos (&(uiAcceso->elementos));

    //VISTAS
    _ui_acceso_liberar_vistas (&(uiAcceso->vistas));
}

