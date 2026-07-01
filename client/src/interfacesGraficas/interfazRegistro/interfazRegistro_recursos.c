#include "../../../include/interfacesGraficas./interfazRegistro/interfazRegistro_recursos.h"


void _interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos)
{
    textos->auxEscribirCorreo = NULL;
    textos->ingresarCorreo = NULL;
    textos->textoInformativoContrasenia = NULL;
    textos->textoInformativoNombre = NULL;
}

void _interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = NULL;
}


t_codigoRetorno _interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos)
{
    textos->auxEscribirCorreo = sfText_create ();
    if (!textos->auxEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto auxEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarCorreo = sfText_create ();
    if (!textos->ingresarCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto ingresarCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoInformativoContrasenia = sfText_create ();
    if (!textos->textoInformativoContrasenia)
    {
        perror ("\nERROR - Interfaz de registro, crear texto textoInformativoContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoInformativoNombre = sfText_create ();
    if (!textos->textoInformativoNombre)
    {
        perror ("\nERROR - Interfaz de registro, crear texto textoInformativoNombre.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = sfRectangleShape_create ();
    if (!elementos->barraEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento barraEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


void _interfazRegistro_configurarInterfaz (t_interfazRegistro *interfazRegistro, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // Asignar recursos comunes
    interfazRegistro->recursosComunesAutenticacionRegistro = recursosComunesAutenticacionRegistro;

    // Deshabilitar foco
    interfazRegistro->estadoFoco = IR_NINGUNO;

    // Setear cadena vacia
    *(interfazRegistro->logica.correoElectronico) = '\0';
}

void _interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // auxEscribirCorreo
    sfText_setFont (textos->auxEscribirCorreo, fuentes->cuerpo);
    sfText_setFillColor (textos->auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));

    // ingresarCorreo
    sfText_setFont (textos->ingresarCorreo, fuentes->ui);
    sfText_setFillColor (textos->ingresarCorreo, sfColor_fromRGB (43, 43, 43));
    sfUint32 bufferIngresarCorreo [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', 0};
    sfText_setUnicodeString (textos->ingresarCorreo, bufferIngresarCorreo);

    // textoInformativoContrasenia
    sfText_setFont (textos->textoInformativoContrasenia, fuentes->ui);
    sfText_setFillColor (textos->textoInformativoContrasenia, sfColor_fromRGB (94, 91, 87));
    sfUint32 bufferTextoInformativoContrasenia [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '8', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->textoInformativoContrasenia, bufferTextoInformativoContrasenia);

    // textoInformativoNombre
    sfText_setFont (textos->textoInformativoNombre, fuentes->ui);
    sfText_setFillColor (textos->textoInformativoNombre, sfColor_fromRGB (94, 91, 87));
    sfUint32 bufferTextoInformativoNombre [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '3', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->textoInformativoNombre, bufferTextoInformativoNombre);
}

void _interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorreo
    sfRectangleShape_setFillColor (elementos->barraEscribirCorreo, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirCorreo, sfColor_fromRGB (169, 163, 154));
}


void _interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setPosition (textos->auxEscribirCorreo, (sfVector2f){42, 392});
    sfText_setCharacterSize (textos->auxEscribirCorreo, 22);

    // ingresarCorro
    sfText_setPosition (textos->ingresarCorreo, (sfVector2f){35, 350});
    sfText_setCharacterSize (textos->ingresarCorreo, 28);

    // textoInformativoContrasenia
    sfText_setPosition (textos->textoInformativoContrasenia, (sfVector2f){35, 260});
    sfText_setCharacterSize (textos->textoInformativoContrasenia, 20);

    // textoInformativoNombre
    sfText_setPosition (textos->textoInformativoNombre, (sfVector2f){35, 135});
    sfText_setCharacterSize (textos->textoInformativoNombre, 20);
}

void _interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorro
    sfRectangleShape_setPosition (elementos->barraEscribirCorreo, (sfVector2f){35, 392});
    sfRectangleShape_setSize (elementos->barraEscribirCorreo, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirCorreo, 2);
}


void _interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoNombre, NULL);
}

void _interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirCorreo, NULL);
}


void _interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoContrasenia);
}

void _interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirCorreo);
}

