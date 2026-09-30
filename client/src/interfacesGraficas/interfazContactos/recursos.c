#include "interfacesGraficas/interfazContactos/recursos.h"


void _ui_contactos_inicializar_fuentes (UiContactosFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

void _ui_contactos_inicializar_textos (UiContactosTextos *textos)
{
    textos->auxContactoSeleccionado = NULL;
    textos->auxEscribirMensaje = NULL;
    textos->botonEnviar = NULL;
    textos->feedbackUsuario = NULL;
    textos->informacionSeleccionChat = NULL;
    textos->nombreUsuario = NULL;
    textos->tituloContactos = NULL;
}

void _ui_contactos_inicializar_elementos (UiContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = NULL;
    elementos->areaMensajes = NULL;
    elementos->barraEscribirMensaje = NULL;
    elementos->botonEnviar = NULL;
    elementos->carpetaDecorativaFondo1 = NULL;
    elementos->carpetaDecorativaFondo2 = NULL;
    elementos->carpetaDecorativaFondo3 = NULL;
    elementos->panelInterfaz = NULL;
    elementos->puntoInsercion = NULL;
    elementos->separacionNombre = NULL;
    elementos->separacionTitulo = NULL;
}

void _ui_contactos_inicializar_vistas (UiContactosVistas *vistas)
{
    vistas->mensajes = NULL;
    vistas->ui = NULL;
}


CodigoRetorno _ui_contactos_crear_fuentes (UiContactosFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Interfaz de contactos, crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }

    fuentes->cuerpo = sfFont_createFromFile ("assets/fonts/fuenteCuerpo.ttf");
    if (!fuentes->cuerpo)
    {
        perror ("\nERROR - Interfaz de contactos, crear fuente cuerpo.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

CodigoRetorno _ui_contactos_crear_textos (UiContactosTextos *textos, const UiContactosFuentes *fuentes)
{
    textos->auxContactoSeleccionado = sfText_create (fuentes->cuerpo);
    if (!textos->auxContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxEscribirMensaje = sfText_create (fuentes->cuerpo);
    if (!textos->auxEscribirMensaje)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    textos->botonEnviar = sfText_create (fuentes->ui);
    if (!textos->botonEnviar)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto botonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    textos->feedbackUsuario = sfText_create (fuentes->ui);
    if (!textos->feedbackUsuario)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto feedbackUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    textos->informacionSeleccionChat = sfText_create (fuentes->ui);
    if (!textos->informacionSeleccionChat)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto informacionSeleccionChat.\n");
        return ERROR_INICIALIZACION;
    }

    textos->nombreUsuario = sfText_create (fuentes->ui);
    if (!textos->nombreUsuario)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto nombreUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloContactos = sfText_create (fuentes->ui);
    if (!textos->tituloContactos)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto tituloContactos.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

CodigoRetorno _ui_contactos_crear_elementos (UiContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = sfRectangleShape_create ();
    if (!elementos->areaContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento areaContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->areaMensajes = sfRectangleShape_create ();
    if (!elementos->areaMensajes)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento areaMensajes.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->barraEscribirMensaje)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento barraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonEnviar = sfRectangleShape_create ();
    if (!elementos->botonEnviar)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento botonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo1 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo1)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento carpetaDecorativaFondo1.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo2 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo2)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento carpetaDecorativaFondo2.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo3 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo3)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento carpetaDecorativaFondo3.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->panelInterfaz = sfRectangleShape_create ();
    if (!elementos->panelInterfaz)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento panelInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionNombre = sfRectangleShape_create ();
    if (!elementos->separacionNombre)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento separacionNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionTitulo = sfRectangleShape_create ();
    if (!elementos->separacionTitulo)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento separacionTitulo.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

CodigoRetorno _ui_contactos_crear_vistas (UiContactosVistas *vistas)
{
    vistas->ui = sfView_create ();
    if (!vistas->ui)
    {
        perror ("\nERROR - Interfaz de contactos, crear vista de UI.\n");
        return ERROR_INICIALIZACION;
    }

    vistas->mensajes = sfView_create ();
    if (!vistas->mensajes)
    {
        perror ("\nERROR - Interfaz de contactos, crear vista de mensajes.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}


void _ui_contactos_configurar_interfaz (UiContactos *uiContactos)
{
    // Establecer un id invalido al usuario del chat seleccionado
    uiContactos->logica.idUsuarioChatSeleccionado = ID_INVALIDO;

    // Setear cadena vacia
    *(uiContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    *(uiContactos->logica.contextoMensajes.mensaje) = '\0';

    // Deshabilitar foco
    uiContactos->foco = UI_CONTACTOS_NINGUNO;

    // Inicializar punto de insercion
    punto_insercion_resetear (&(uiContactos->logica.puntoInsercion));
}

void _ui_contactos_configurar_textos (UiContactosTextos *textos)
{
    // auxContactoSeleccionado
    sfText_setFillColor (textos->auxContactoSeleccionado, sfColor_fromRGB (94, 91, 87));

    // auxEscribirMensaje
    sfText_setFillColor (textos->auxEscribirMensaje, sfColor_fromRGB (53, 53, 53));

    // botonEnviar
    sfText_setString (textos->botonEnviar, "ENVIAR");
    sfText_setFillColor (textos->botonEnviar, sfColor_fromRGB (94, 91, 87));
    
    // feedbackUsuario
    sfText_setFillColor (textos->feedbackUsuario, sfColor_fromRGB (94, 91, 87));

    // informacionSeleccionChat
    sfText_setFillColor (textos->informacionSeleccionChat, sfColor_fromRGBA (94, 91, 87, 191));
    sfText_setString (textos->informacionSeleccionChat, "Seleccione un chat con un usuario");

    // nombreUsuario
    sfText_setFillColor (textos->nombreUsuario, sfColor_fromRGB (43, 43, 43));

    // tituloContactos
    sfText_setString (textos->tituloContactos, "CONTACTOS");
    sfText_setFillColor (textos->tituloContactos, sfColor_fromRGB (43, 43, 43));
}

void _ui_contactos_configurar_elementos (UiContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setFillColor (elementos->areaContactoSeleccionado, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaContactoSeleccionado, sfColor_fromRGB (107, 94, 75));

    // areaMensajes
    sfRectangleShape_setFillColor (elementos->areaMensajes, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaMensajes, sfColor_fromRGB (107, 94, 75));

    // barraEscribirMensaje
    sfRectangleShape_setFillColor (elementos->barraEscribirMensaje, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirMensaje, sfColor_fromRGB (169, 163, 154));

    // botonEnviar
    sfRectangleShape_setFillColor (elementos->botonEnviar, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->botonEnviar, sfColor_fromRGB (169, 163, 154));
    
    // carpetaDecorativaFondo1
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGB (217, 211, 199));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGBA (169, 163, 154, 191));

    // carpetaDecorativaFondo2
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGB (212, 206, 194));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGBA (169, 163, 154, 191));

    // carpetaDecorativaFondo3
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo3, sfColor_fromRGB (207, 201, 189));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo3, sfColor_fromRGBA (169, 163, 154, 191));

    // separacionNombre
    sfRectangleShape_setFillColor (elementos->separacionNombre, sfColor_fromRGB (107, 94, 75));

    // separacionTitulo
    sfRectangleShape_setFillColor (elementos->separacionTitulo, sfColor_fromRGB (107, 94, 75));

    // panelInterfaz
    sfRectangleShape_setFillColor (elementos->panelInterfaz, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->panelInterfaz, sfColor_fromRGB (169, 163, 154));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (94, 91, 87));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);
}


void _ui_contactos_establecer_tam_y_pos_ventana_textos (UiContactosTextos *textos)
{
    // auxContactoSeleccionado
    sfText_setCharacterSize (textos->auxContactoSeleccionado, 24);
    centrar_texto_en_area (textos->auxContactoSeleccionado, 852, 25, 600, 40);
    
    // auxEscribirMensaje
    sfText_setPosition (textos->auxEscribirMensaje, (sfVector2f){449, 912});
    sfText_setCharacterSize (textos->auxEscribirMensaje, 24);

    // botonEnviar
    sfText_setCharacterSize (textos->botonEnviar, 22);
    centrar_texto_en_area (textos->botonEnviar, 1747, 909, 115, 35);

    // feedbackUsuario
    sfText_setCharacterSize (textos->feedbackUsuario, 22);
    sfText_setPosition (textos->feedbackUsuario, (sfVector2f){442, 964});

    // informacionSeleccionChat
    sfText_setCharacterSize (textos->informacionSeleccionChat, 30);
    centrar_texto_en_area (textos->informacionSeleccionChat, 442, 90, 1420, 780);

    // tituloContactos
    sfText_setCharacterSize (textos->tituloContactos, 36);
    centrar_texto_en_area (textos->tituloContactos, 0, 0, 340, 120);
}

void _ui_contactos_establecer_tam_y_pos_ventana_elementos (UiContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setPosition (elementos->areaContactoSeleccionado, (sfVector2f){852, 25});
    sfRectangleShape_setSize (elementos->areaContactoSeleccionado, (sfVector2f){600, 40});
    sfRectangleShape_setOutlineThickness (elementos->areaContactoSeleccionado, 2);

    // areaMensajes
    sfRectangleShape_setPosition (elementos->areaMensajes, (sfVector2f){442, 90});
    sfRectangleShape_setSize (elementos->areaMensajes, (sfVector2f){1420, 780});
    sfRectangleShape_setOutlineThickness (elementos->areaMensajes, 2);

    // barraEscribirMensaje
    sfRectangleShape_setPosition (elementos->barraEscribirMensaje, (sfVector2f){442, 909});
    sfRectangleShape_setSize (elementos->barraEscribirMensaje, (sfVector2f){1265, 38});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirMensaje, 2);

    // botonEnviar
    sfRectangleShape_setPosition (elementos->botonEnviar, (sfVector2f){1747, 909});
    sfRectangleShape_setSize (elementos->botonEnviar, (sfVector2f){115, 35});
    sfRectangleShape_setOutlineThickness (elementos->botonEnviar, 2);

    // carpetaDecorativaFondo1
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo1, (sfVector2f){342.5, 65});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo1, (sfVector2f){28, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo1, 1.5);

    // carpetaDecorativaFondo2
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo2, (sfVector2f){370, 130});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo2, (sfVector2f){20, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo2, 1);

    // carpetaDecorativaFondo3
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo3, (sfVector2f){390.2, 195});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo3, (sfVector2f){16, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo3, 1);

    // separacionNombre
    sfRectangleShape_setPosition (elementos->separacionNombre, (sfVector2f){44, 889});
    sfRectangleShape_setSize (elementos->separacionNombre, (sfVector2f){254, 2});

    // separacionTitulo
    sfRectangleShape_setPosition (elementos->separacionTitulo, (sfVector2f){44, 120});
    sfRectangleShape_setSize (elementos->separacionTitulo, (sfVector2f){254, 2});

    // panelInterfaz
    sfRectangleShape_setPosition (elementos->panelInterfaz, (sfVector2f){0, 0});
    sfRectangleShape_setSize (elementos->panelInterfaz, (sfVector2f){340, 1009});
    sfRectangleShape_setOutlineThickness (elementos->panelInterfaz, 2);

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){28, 2});
}

void _ui_contactos_establecer_tam_vistas (UiContactosVistas *vistas)
{
    // UI
    sfView_setSize (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});

    // mensajes
    sfView_setSize (vistas->mensajes, (sfVector2f){1420, 780});                                          // Vista del tamanio del sfRectangleShape *areaMensajes
    sfView_setCenter (vistas->mensajes, (sfVector2f){1152, 480});                                      // Centro del sfRectangleShape *areaMensajes
    sfView_setViewport(vistas->mensajes, (sfFloatRect){0.230f, 0.089f, 0.740f, 0.773f});    // Proporciones del sfRectangleShape *areaMensajes
}


void _ui_contactos_liberar_fuentes (UiContactosFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

void _ui_contactos_liberar_textos (UiContactosTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxContactoSeleccionado);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirMensaje);
    DESTRUCTOR_SEGURO_TEXTO (textos->botonEnviar);
    DESTRUCTOR_SEGURO_TEXTO (textos->feedbackUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->informacionSeleccionChat);
    DESTRUCTOR_SEGURO_TEXTO (textos->nombreUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloContactos);
}

void _ui_contactos_liberar_elementos (UiContactosElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaContactoSeleccionado);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaMensajes);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirMensaje);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonEnviar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo1);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo2);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo3);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->panelInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionTitulo);
}

void _ui_contactos_liberar_vistas (UiContactosVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->mensajes);
    DESTRUCTOR_SEGURO_VISTA (vistas->ui);
}
