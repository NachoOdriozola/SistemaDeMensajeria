#include "interfacesGraficas/interfazContactos/interfazContactos.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void establecer_y_posicionar_nombre_usuario (UiContactos *uiContactos, const char *nombreUsuario);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void ui_contactos_inicializar (UiContactos *uiContactos)
{
    //FUENTES
    _ui_contactos_inicializar_fuentes (&(uiContactos->fuentes));

    // TEXTOS
    _ui_contactos_inicializar_textos (&(uiContactos->textos));

    // ELEMENTOS
    _ui_contactos_inicializar_elementos (&(uiContactos->elementos));

    //VISTAS
    _ui_contactos_inicializar_vistas (&(uiContactos->vistas));
}

CodigoRetorno ui_contactos_crear (UiContactos *uiContactos)
{
    //FUENTES
    if (_ui_contactos_crear_fuentes (&(uiContactos->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_ui_contactos_crear_textos (&(uiContactos->textos), &(uiContactos->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_ui_contactos_crear_elementos (&(uiContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //VISTAS
    if (_ui_contactos_crear_vistas (&(uiContactos->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //LISTA DE MENSAJES
    _ui_contactos_lista_mensajes_crear (&(uiContactos->logica.contextoMensajes));

    return EXITO;
}

void ui_contactos_configurar (UiContactos *uiContactos)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _ui_contactos_configurar_interfaz (uiContactos);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _ui_contactos_configurar_textos (&(uiContactos->textos));

    // ELEMENTOS
    _ui_contactos_configurar_elementos (&(uiContactos->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTO
    _ui_contactos_establecer_tam_y_pos_ventana_textos (&(uiContactos->textos));

    // ELEMENTOS
    _ui_contactos_establecer_tam_y_pos_ventana_elementos (&(uiContactos->elementos));

    //VISTAS
    _ui_contactos_establecer_tam_vistas (&(uiContactos->vistas));
}

void ui_contactos_preparar (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    MAXIMIZAR_VENTANA (sfRenderWindow_getNativeHandle (contextoAplicacion->renderizado), SW_MAXIMIZE);
    establecer_y_posicionar_nombre_usuario (uiContactos, contextoAplicacion->usuario.nombre);
}

void ui_contactos_ejecutar (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    _ui_contactos_accionar (contextoAplicacion, uiContactos);
    _ui_contactos_actualizar (contextoAplicacion, uiContactos);
    _ui_contactos_renderizar (contextoAplicacion->renderizado, uiContactos);
}

void ui_contactos_liberar (UiContactos *uiContactos)
{
    //FUENTES
    _ui_contactos_liberar_fuentes (&(uiContactos->fuentes));

    // TEXTOS
    _ui_contactos_liberar_textos (&(uiContactos->textos));

    // ELEMENTOS
    _ui_contactos_liberar_elementos (&(uiContactos->elementos));

    //VISTAS
    _ui_contactos_liberar_vistas (&(uiContactos->vistas));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void establecer_y_posicionar_nombre_usuario (UiContactos *uiContactos, const char *nombreUsuario)
{
    sfFloatRect limitesNombreUsuario;
    unsigned short int pixeles = 32;
    
    sfText_setString (uiContactos->textos.nombreUsuario, nombreUsuario);
    do
    {
        sfText_setCharacterSize (uiContactos->textos.nombreUsuario, pixeles);
        centrar_texto_en_area (uiContactos->textos.nombreUsuario, 44, 888, 254, 120);
        limitesNombreUsuario = sfText_getLocalBounds (uiContactos->textos.nombreUsuario);
        pixeles -= 2;
    } while (limitesNombreUsuario.size.x > 254);
}

