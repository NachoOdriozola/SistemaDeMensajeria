#include "interfacesGraficas/interfazRegistro/recursos.h"


void _ui_registro_inicializar_textos (UiRegistroTextos *textos)
{
    textos->auxEscribirCorreo = NULL;
    textos->ingresarCorreo = NULL;
    textos->informacionContrasenia = NULL;
    textos->informacionNombre = NULL;
}

void _ui_registro_inicializar_elementos (UiRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = NULL;
}


CodigoRetorno _ui_registro_crear_textos (UiRegistroTextos *textos, const UiAccesoFuentes *fuentes)
{
    textos->auxEscribirCorreo = sfText_create (fuentes->cuerpo);
    if (!textos->auxEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto auxEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarCorreo = sfText_create (fuentes->ui);
    if (!textos->ingresarCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto ingresarCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->informacionContrasenia = sfText_create (fuentes->ui);
    if (!textos->informacionContrasenia)
    {
        perror ("\nERROR - Interfaz de registro, crear texto informacionContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->informacionNombre = sfText_create (fuentes->ui);
    if (!textos->informacionNombre)
    {
        perror ("\nERROR - Interfaz de registro, crear texto informacionNombre.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

CodigoRetorno _ui_registro_crear_elementos (UiRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = sfRectangleShape_create ();
    if (!elementos->barraEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento barraEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


void _ui_registro_configurar_interfaz (UiRegistro *uiRegistro)
{
    // Deshabilitar foco
    uiRegistro->foco = UI_REGISTRO_NINGUNO;

    // Setear cadena vacia
    *(uiRegistro->logica.correoElectronico) = '\0';
}

void _ui_registro_configurar_textos (UiRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setFillColor (textos->auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));

    // ingresarCorreo
    sfText_setFillColor (textos->ingresarCorreo, sfColor_fromRGB (43, 43, 43));
    uint32_t bufferIngresarCorreo [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', 0};
    sfText_setUnicodeString (textos->ingresarCorreo, bufferIngresarCorreo);

    // informacionContrasenia
    sfText_setFillColor (textos->informacionContrasenia, sfColor_fromRGB (94, 91, 87));
    uint32_t bufferInformacionContrasenia [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '8', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->informacionContrasenia, bufferInformacionContrasenia);

    // informacionNombre
    sfText_setFillColor (textos->informacionNombre, sfColor_fromRGB (94, 91, 87));
    uint32_t bufferInformacionNombre [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '3', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->informacionNombre, bufferInformacionNombre);
}

void _ui_registro_configurar_elementos (UiRegistroElementos *elementos)
{
    // barraEscribirCorreo
    sfRectangleShape_setFillColor (elementos->barraEscribirCorreo, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirCorreo, sfColor_fromRGB (169, 163, 154));
}


void _ui_registro_establecer_tam_y_pos_ventana_textos (UiRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setPosition (textos->auxEscribirCorreo, (sfVector2f){42, 392});
    sfText_setCharacterSize (textos->auxEscribirCorreo, 22);

    // ingresarCorro
    sfText_setPosition (textos->ingresarCorreo, (sfVector2f){35, 350});
    sfText_setCharacterSize (textos->ingresarCorreo, 28);

    // informacionContrasenia
    sfText_setPosition (textos->informacionContrasenia, (sfVector2f){35, 260});
    sfText_setCharacterSize (textos->informacionContrasenia, 20);

    // informacionNombre
    sfText_setPosition (textos->informacionNombre, (sfVector2f){35, 135});
    sfText_setCharacterSize (textos->informacionNombre, 20);
}

void _ui_registro_establecer_tam_y_pos_ventana_elementos (UiRegistroElementos *elementos)
{
    // barraEscribirCorro
    sfRectangleShape_setPosition (elementos->barraEscribirCorreo, (sfVector2f){35, 392});
    sfRectangleShape_setSize (elementos->barraEscribirCorreo, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirCorreo, 2);
}


void _ui_registro_liberar_textos (UiRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->informacionContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->informacionNombre);
}

void _ui_registro_liberar_elementos (UiRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirCorreo);
}

