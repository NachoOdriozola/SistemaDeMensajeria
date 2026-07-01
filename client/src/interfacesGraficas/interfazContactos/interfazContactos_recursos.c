#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_recursos.h"


void _interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos)
{
    textos->auxContactoSeleccionado = NULL;
}

void _interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = NULL;
}


t_codigoRetorno _interfazContactos_inicializarTextos (t_interfazContactosTextos *textos)
{
    textos->auxContactoSeleccionado = sfText_create ();
    if (!textos->auxContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = sfRectangleShape_create ();
    if (!elementos->areaContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento areaContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


void _interfazContactos_configurarInterfaz (t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // Asignar recursos comunes
    interfazContactos->recursosComunesContactosSalas = recursosComunesContactosSalas;

    // Establecer un id invalido al usuario del chat seleccionado
    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO;

    // Setear cadena vacia
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';

    // Deshabilitar foco
    interfazContactos->estadoFoco = ICT_NINGUNO;
}

void _interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // auxContactoSeleccionado
    sfText_setFont (textos->auxContactoSeleccionado, fuentes->cuerpo);
    sfText_setFillColor (textos->auxContactoSeleccionado, sfColor_fromRGB (94, 91, 87));
}

void _interfazContactos_configurarElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setFillColor (elementos->areaContactoSeleccionado, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaContactoSeleccionado, sfColor_fromRGB (107, 94, 75));
}


void _interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos)
{
    // auxContactoSeleccionado
    sfText_setCharacterSize (textos->auxContactoSeleccionado, 24);
    centrarTextoEnArea (textos->auxContactoSeleccionado, 852, 25, 600, 40);
}

void _interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setPosition (elementos->areaContactoSeleccionado, (sfVector2f){852, 25});
    sfRectangleShape_setSize (elementos->areaContactoSeleccionado, (sfVector2f){600, 40});
    sfRectangleShape_setOutlineThickness (elementos->areaContactoSeleccionado, 2);
}


void _interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxContactoSeleccionado, NULL);
}

void _interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaContactoSeleccionado, NULL);
}


void _interfazContactos_liberarTextos (t_interfazContactosTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxContactoSeleccionado);
}

void _interfazContactos_liberarElementos (t_interfazContactosElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaContactoSeleccionado);
}

