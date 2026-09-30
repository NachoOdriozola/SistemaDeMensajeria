#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetear_interfaz (UiAcceso *uiAcceso);

static void configurar_textos_ui_autenticacion (UiAccesoTextos *textos);
static void configurar_elementos_ui_autenticacion (UiAccesoElementos *elementos);

static void configurar_textos_ui_registro (UiAccesoTextos *textos);
static void configurar_elementos_ui_registro (UiAccesoElementos *elementos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_acceso_activar_interfaz_autenticacion (UiAcceso *uiAcceso)
{
    // --------------- RESETEAR INTERFAZ ---------------
    resetear_interfaz (uiAcceso);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTO
    configurar_textos_ui_autenticacion (&(uiAcceso->textos));

    // ELEMENTOS
    configurar_elementos_ui_autenticacion (&(uiAcceso->elementos));
}

void _ui_acceso_activar_interfaz_registro (UiAcceso *uiAcceso)
{
    // --------------- RESETEAR INTERFAZ ---------------
    resetear_interfaz (uiAcceso);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTO
    configurar_textos_ui_registro (&(uiAcceso->textos));

    // ELEMENTOS
    configurar_elementos_ui_registro (&(uiAcceso->elementos));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetear_interfaz (UiAcceso *uiAcceso)
{
    // Deshabilitar foco
    uiAcceso->foco = UI_ACCESO_NINGUNO;

    // Setear cadenas vacias
    *(uiAcceso->logica.contrasenia) = '\0';
    *(uiAcceso->logica.nombreUsuario) = '\0';

    // Resetear el punto de insecion
    punto_insercion_resetear (&(uiAcceso->logica.puntoInsercion));
}


static void configurar_textos_ui_autenticacion (UiAccesoTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setString (textos->auxEscribirContrasenia, "");
    sfText_setPosition (textos->auxEscribirContrasenia, (sfVector2f){42, 315});
    sfText_setFillColor (textos->auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));

    // auxEscribirNombre
    sfText_setString (textos->auxEscribirNombre, "");
    sfText_setPosition (textos->auxEscribirNombre, (sfVector2f){42, 180});
    sfText_setFillColor (textos->auxEscribirNombre, sfColor_fromRGB (53, 53, 53));

    // botonIngresar
    sfText_setString (textos->botonIngresar, "INGRESAR");
    centrar_texto_en_area (textos->botonIngresar, 180, 405, 140, 35);

    // cambiarInterfaz
    uint32_t bufferCambiarInterfaz [] = {0x00bf, 'N', 'o', ' ', 't', 'e', 'n', 0x00e9, 's', ' ', 'c', 'u', 'e', 'n', 't', 'a', '?', ' ', 'R', 'e', 'g', 'i', 's', 't', 'r', 'a', 't', 'e', ' ', 'a', 'c', 0x00e1, 0};
    sfText_setUnicodeString (textos->cambiarInterfaz, bufferCambiarInterfaz);
    centrar_texto_en_area (textos->cambiarInterfaz, 0, 530, 500, 90);

    // feedbackUsuario
    sfText_setString (textos->feedbackUsuario, "");

    // ingresarContrasenia
    sfText_setPosition (textos->ingresarContrasenia, (sfVector2f){35, 255});

    // ingresarNombre
    sfText_setPosition (textos->ingresarNombre, (sfVector2f){35, 120});

    // tituloInterfaz
    uint32_t bufferTituloInterfaz [] = {'I', 'N', 'I', 'C', 'I', 'A', 'R', ' ', 'S', 'E', 'S', 'I', 0x00d3, 'N', 0};
    sfText_setUnicodeString (textos->tituloInterfaz, bufferTituloInterfaz);
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){120, 25});
}

static void configurar_elementos_ui_autenticacion (UiAccesoElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setPosition (elementos->barraEscribirContrasenia, (sfVector2f){35, 315});

    // barraEscribirNombre
    sfRectangleShape_setPosition (elementos->barraEscribirNombre, (sfVector2f){35, 180});

    // botonIngresar
    sfRectangleShape_setPosition (elementos->botonIngresar, (sfVector2f){180, 405});

    // subrayadoTitulo
    sfRectangleShape_setPosition (elementos->subrayadoTitulo, (sfVector2f){120, 75});
    sfRectangleShape_setSize (elementos->subrayadoTitulo, (sfVector2f){260, 2.5});
}


static void configurar_textos_ui_registro (UiAccesoTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setString (textos->auxEscribirContrasenia, "");
    sfText_setPosition (textos->auxEscribirContrasenia, (sfVector2f){42, 295});

    // auxEscribirNombre
    sfText_setString (textos->auxEscribirNombre, "");
    sfText_setPosition (textos->auxEscribirNombre, (sfVector2f){42, 170});

    // botonIngresar
    sfText_setString (textos->botonIngresar, "REGISTRAR");
    centrar_texto_en_area (textos->botonIngresar, 180, 452, 140, 35);

    // cambiarInterfaz
    uint32_t bufferCambiarInterfaz [] = {0x00bf, 'Y', 'a', ' ', 't', 'e', 'n', 0x00e9, 's', ' ', 'c', 'u', 'e', 'n', 't', 'a', '?', ' ', 'I', 'n', 'i', 'c', 'i', 0x00e1, ' ', 's', 'e', 's', 'i', 0x00f3, 'n', ' ', 'a', 'c', 0x00e1, 0};
    sfText_setUnicodeString (textos->cambiarInterfaz, bufferCambiarInterfaz);
    centrar_texto_en_area (textos->cambiarInterfaz, 0, 530, 500, 90);

    // feedbackUsuario
    sfText_setString (textos->feedbackUsuario, "");

    // ingresarContrasenia
    sfText_setPosition (textos->ingresarContrasenia, (sfVector2f){35, 225});

    // ingresarNombre
    sfText_setPosition (textos->ingresarNombre, (sfVector2f){35, 100});

    // tituloInterfaz
    sfText_setString (textos->tituloInterfaz, "CREAR CUENTA");
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){130, 25});
}

static void configurar_elementos_ui_registro (UiAccesoElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setPosition (elementos->barraEscribirContrasenia, (sfVector2f){35, 295});

    // barraEscribirNombre
    sfRectangleShape_setPosition (elementos->barraEscribirNombre, (sfVector2f){35, 170});

    // botonIngresar
    sfRectangleShape_setPosition (elementos->botonIngresar, (sfVector2f){180, 452});

    // subrayadoTitulo
    sfRectangleShape_setPosition (elementos->subrayadoTitulo, (sfVector2f){130, 75});
    sfRectangleShape_setSize (elementos->subrayadoTitulo, (sfVector2f){240, 2.5});
}
