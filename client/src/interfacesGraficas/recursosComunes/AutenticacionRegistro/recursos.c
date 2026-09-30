#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursos.h"


void _ui_acceso_inicializar_fuentes (UiAccesoFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

void _ui_acceso_inicializar_textos (UiAccesoTextos *textos)
{
    textos->auxEscribirContrasenia = NULL;
    textos->auxEscribirNombre = NULL;
    textos->botonIngresar = NULL;
    textos->cambiarInterfaz = NULL;
    textos->feedbackUsuario = NULL;
    textos->ingresarContrasenia = NULL;
    textos->ingresarNombre = NULL;
    textos->tituloInterfaz = NULL;
}

void _ui_acceso_inicializar_elementos (UiAccesoElementos *elementos)
{
    elementos->barraEscribirContrasenia = NULL;
    elementos->barraEscribirNombre = NULL;
    elementos->botonIngresar = NULL;
    elementos->puntoInsercion = NULL;
    elementos->subrayadoTitulo = NULL;
}

void _ui_acceso_inicializar_vistas (UiAccesoVistas *vistas)
{
    vistas->ui = NULL;
}


CodigoRetorno _ui_acceso_crear_fuentes (UiAccesoFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }

    fuentes->cuerpo = sfFont_createFromFile ("assets/fonts/fuenteCuerpo.ttf");
    if (!fuentes->cuerpo)
    {
        perror ("\nERROR - Crear fuente cuerpo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

CodigoRetorno _ui_acceso_crear_textos (UiAccesoTextos *textos, const UiAccesoFuentes *fuentes)
{
    textos->auxEscribirContrasenia = sfText_create (fuentes->cuerpo);
    if (!textos->auxEscribirContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxEscribirNombre = sfText_create (fuentes->cuerpo);
    if (!textos->auxEscribirNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirNombre.\n");
        return ERROR_INICIALIZACION;
    }

    textos->botonIngresar = sfText_create (fuentes->ui);
    if (!textos->botonIngresar)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto botonIngresar.\n");
        return ERROR_INICIALIZACION;
    }

    textos->cambiarInterfaz = sfText_create (fuentes->ui);
    if (!textos->cambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto cambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    textos->feedbackUsuario = sfText_create (fuentes->ui);
    if (!textos->feedbackUsuario)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto feedbackUsuario.\n");
        return ERROR_INICIALIZACION;
    }
    
    textos->ingresarContrasenia = sfText_create (fuentes->ui);
    if (!textos->ingresarContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarNombre = sfText_create (fuentes->ui);
    if (!textos->ingresarNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarNombre.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloInterfaz = sfText_create (fuentes->ui);
    if (!textos->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

CodigoRetorno _ui_acceso_crear_elementos (UiAccesoElementos *elementos)
{
    elementos->barraEscribirContrasenia = sfRectangleShape_create ();
    if (!elementos->barraEscribirContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento barraEscribirContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirNombre = sfRectangleShape_create ();
    if (!elementos->barraEscribirNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento barraEscribirNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonIngresar = sfRectangleShape_create ();
    if (!elementos->botonIngresar)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento botonIngresar.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->subrayadoTitulo = sfRectangleShape_create ();
    if (!elementos->subrayadoTitulo)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento subrayadoTitulo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

CodigoRetorno _ui_acceso_crear_vistas (UiAccesoVistas *vistas)
{
    vistas->ui = sfView_create ();
    if (!vistas->ui)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear vista de UI.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}


void _ui_acceso_configurar_interfaz (UiAcceso *uiAcceso)
{
    // Deshabilitar foco
    uiAcceso->foco = UI_ACCESO_NINGUNO;

    // Inicializar el punto de insecion
    punto_insercion_resetear (&(uiAcceso->logica.puntoInsercion));

    // Setear cadenas vacias
    *(uiAcceso->logica.contrasenia) = '\0';
    *(uiAcceso->logica.nombreUsuario) = '\0';
}

void _ui_acceso_configurar_textos (UiAccesoTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setFillColor (textos->auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));

    // auxEscribirNombre
    sfText_setFillColor (textos->auxEscribirNombre, sfColor_fromRGB (53, 53, 53));

    // botonIngresar
    sfText_setString (textos->botonIngresar, "INGRESAR");
    sfText_setFillColor (textos->botonIngresar, sfColor_fromRGB (94, 91, 87));

    // cambiarInterfaz
    sfText_setFillColor (textos->cambiarInterfaz, sfColor_fromRGB (43, 43, 43));
    uint32_t bufferCambiarInterfaz [] = {0x00bf, 'N', 'o', ' ', 't', 'e', 'n', 0x00e9, 's', ' ', 'c', 'u', 'e', 'n', 't', 'a', '?', ' ', 'R', 'e', 'g', 'i', 's', 't', 'r', 'a', 't', 'e', ' ', 'a', 'c', 0x00e1, 0};
    sfText_setUnicodeString (textos->cambiarInterfaz, bufferCambiarInterfaz);

    // feedbackUsuario
    sfText_setFillColor (textos->feedbackUsuario, sfColor_fromRGB (43, 43, 43));
    
    // ingresarContrasenia
    sfText_setFillColor (textos->ingresarContrasenia, sfColor_fromRGB (43, 43, 43));
    uint32_t bufferIngresarContrasenia [] = {'C', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ':', 0};
    sfText_setUnicodeString (textos->ingresarContrasenia, bufferIngresarContrasenia);

    // ingresarNombre
    sfText_setString (textos->ingresarNombre, "Nombre de usuario:");
    sfText_setFillColor (textos->ingresarNombre, sfColor_fromRGB (43, 43, 43));

    // tituloInterfaz
    sfText_setFillColor (textos->tituloInterfaz, sfColor_fromRGB (43, 43, 43));
    uint32_t bufferTituloInterfaz [] = {'I', 'N', 'I', 'C', 'I', 'A', 'R', ' ', 'S', 'E', 'S', 'I', 0x00d3, 'N', 0};
    sfText_setUnicodeString (textos->tituloInterfaz, bufferTituloInterfaz);
}

void _ui_acceso_configurar_elementos (UiAccesoElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setFillColor (elementos->barraEscribirContrasenia, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirContrasenia, sfColor_fromRGB (169, 163, 154));

    // barraEscribirNombre
    sfRectangleShape_setFillColor (elementos->barraEscribirNombre, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirNombre, sfColor_fromRGB (169, 163, 154));

    // botonIngresar
    sfRectangleShape_setFillColor (elementos->botonIngresar, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->botonIngresar, sfColor_fromRGB (169, 163, 154));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (94, 91, 87));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);

    // subrayadoTitulo
    sfRectangleShape_setFillColor (elementos->subrayadoTitulo, sfColor_fromRGB (43, 43, 43));
}


void _ui_acceso_establecer_tam_y_pos_ventana_textos (UiAccesoTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setPosition (textos->auxEscribirContrasenia, (sfVector2f){42, 315});
    sfText_setCharacterSize (textos->auxEscribirContrasenia, 22);

    // auxEscribirNombre
    sfText_setPosition (textos->auxEscribirNombre, (sfVector2f){42, 180});
    sfText_setCharacterSize (textos->auxEscribirNombre, 22);

    // botonIngresar
    sfText_setCharacterSize (textos->botonIngresar, 24);
    centrar_texto_en_area (textos->botonIngresar, 180, 405, 140, 35);

    // cambiarInterfaz
    sfText_setCharacterSize (textos->cambiarInterfaz, 26);
    centrar_texto_en_area (textos->cambiarInterfaz, 0, 530, 500, 90);

    // feedbackUsuario
    sfText_setCharacterSize (textos->feedbackUsuario, 24);

    // ingresarContrasenia
    sfText_setPosition (textos->ingresarContrasenia, (sfVector2f){35, 255});
    sfText_setCharacterSize (textos->ingresarContrasenia, 28);

    // ingresarNombre
    sfText_setPosition (textos->ingresarNombre, (sfVector2f){35, 120});
    sfText_setCharacterSize (textos->ingresarNombre, 28);

    // tituloInterfaz
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){120, 25});
    sfText_setCharacterSize (textos->tituloInterfaz, 36);
}

void _ui_acceso_establecer_tam_y_pos_ventana_elementos (UiAccesoElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setPosition (elementos->barraEscribirContrasenia, (sfVector2f){35, 315});
    sfRectangleShape_setSize (elementos->barraEscribirContrasenia, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirContrasenia, 2);

    // barraEscribirNombre
    sfRectangleShape_setPosition (elementos->barraEscribirNombre, (sfVector2f){35, 180});
    sfRectangleShape_setSize (elementos->barraEscribirNombre, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirNombre, 2);

    // botonIngresar
    sfRectangleShape_setPosition (elementos->botonIngresar, (sfVector2f){180, 405});
    sfRectangleShape_setSize (elementos->botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (elementos->botonIngresar, 2);

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){26, 2});

    // subrayadoTitulo
    sfRectangleShape_setPosition (elementos->subrayadoTitulo, (sfVector2f){120, 75});
    sfRectangleShape_setSize (elementos->subrayadoTitulo, (sfVector2f){260, 2.5});
}

void _ui_acceso_establecer_tam_vistas (UiAccesoVistas *vistas)
{
    // UI
    sfView_setSize (vistas->ui, (sfVector2f){500, 620});
    sfView_setCenter (vistas->ui, (sfVector2f){500 / 2.0f, 620 / 2.0f});
}


void _ui_acceso_liberar_fuentes (UiAccesoFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

void _ui_acceso_liberar_textos (UiAccesoTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->botonIngresar);
    DESTRUCTOR_SEGURO_TEXTO (textos->cambiarInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->feedbackUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
}

void _ui_acceso_liberar_elementos (UiAccesoElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirContrasenia);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonIngresar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->subrayadoTitulo);
}

void _ui_acceso_liberar_vistas (UiAccesoVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->ui);
}
