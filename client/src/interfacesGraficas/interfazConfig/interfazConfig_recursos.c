#include "../../../include/interfacesGraficas/interfazConfig/interfazConfig_recursos.h"


void _interfazConfig_inicializarValoresNulosFuentes (t_interfazConfigFuentes *fuentes)
{
    fuentes->ui = NULL;
}

void _interfazConfig_inicializarValoresNulosTextos (t_interfazConfigTextos *textos)
{
    textos->textoConfig = NULL;
}

void _interfazConfig_inicializarValoresNulosElementos (t_interfazConfigElementos *elementos)
{
    elementos->rectanguloVolver = NULL;
}


t_codigoRetorno _interfazConfig_inicializarFuentes (t_interfazConfigFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("../../../client/assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _interfazConfig_inicializarTextos (t_interfazConfigTextos *textos)
{
    textos->textoConfig = sfText_create ();
    if (!textos->textoConfig)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear texto textoConfig.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _interfazConfig_inicializarElementos (t_interfazConfigElementos *elementos)
{
    elementos->rectanguloVolver = sfRectangleShape_create ();
    if (!elementos->rectanguloVolver)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear elemento rectanguloVolver.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


void _interfazConfig_configurarInterfaz (t_interfazConfig *interfazConfig)
{
    // Deshabilitar foco
    interfazConfig->estadoFoco = ICF_NINGUNO;
}

void _interfazConfig_configurarTextos (t_interfazConfigTextos *textos, const t_interfazConfigFuentes *fuentes)
{
    // textoConfig
    sfText_setFont (textos->textoConfig, fuentes->ui);
    sfText_setString (textos->textoConfig, "CONFIGURACIONES");
    sfText_setFillColor (textos->textoConfig, sfColor_fromRGB (0, 0, 0));
}

void _interfazConfig_configurarElementos (t_interfazConfigElementos *elementos)
{
    // rectanguloVolver
    sfRectangleShape_setFillColor (elementos->rectanguloVolver, sfColor_fromRGB (0, 0, 0));
}


void _interfazConfig_tamYPosVentanaTextos (t_interfazConfigTextos *textos)
{
    // textoConfig
    sfText_setPosition (textos->textoConfig, (sfVector2f){1000, 500});
    sfText_setCharacterSize (textos->textoConfig, 36);
}

void _interfazConfig_tamYPosVentanaElementos (t_interfazConfigElementos *elementos)
{
    // rectanguloVolver
    sfRectangleShape_setPosition (elementos->rectanguloVolver, (sfVector2f){1000, 650});
    sfRectangleShape_setSize (elementos->rectanguloVolver, (sfVector2f){60, 60});
}


void _interfazConfig_renderizarTextos (sfRenderWindow *renderizado, const t_interfazConfigTextos *textos)
{
     sfRenderWindow_drawText (renderizado, textos->textoConfig, NULL);
}

void _interfazConfig_renderizarElementos (sfRenderWindow *renderizado, const t_interfazConfigElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->rectanguloVolver, NULL);
}


void _interfazConfig_liberarFuentes (t_interfazConfigFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

void _interfazConfig_liberarTextos (t_interfazConfigTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->textoConfig);
}

void _interfazConfig_liberarElementos (t_interfazConfigElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->rectanguloVolver);
}

