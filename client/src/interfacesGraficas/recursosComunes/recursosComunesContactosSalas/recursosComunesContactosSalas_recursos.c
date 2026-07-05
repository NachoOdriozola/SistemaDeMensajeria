#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas_recursos.h"


void _recursosComunesContactosSalas_inicializarValoresNulosFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

void _recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->auxEscribirMensaje = NULL;
    textos->proximaInterfaz = NULL;
    textos->nombreUsuario = NULL;
    textos->textoBotonEnviar = NULL;
    textos->tituloInterfaz = NULL;
}

void _recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = NULL;
    elementos->barraEscribirMensaje = NULL;
    elementos->botonEnviar = NULL;
    elementos->carpetaDecorativaFondo1 = NULL;
    elementos->carpetaDecorativaFondo2 = NULL;
    elementos->ojalilloArriba = NULL;
    elementos->ojalilloAbajo = NULL;
    elementos->ojalilloSelecInterfaz = NULL;
    elementos->separacionNombre = NULL;
    elementos->separacionTitulo = NULL;
    elementos->panelInterfaz = NULL;
    elementos->puntoInsercion = NULL;
    elementos->solapaCambiarInterfaz = NULL;
}

void _recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->ui = NULL;
    vistas->mensajes = NULL;
}


t_codigoRetorno _recursosComunesContactosSalas_inicializarFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("../../../client/assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }

    fuentes->cuerpo = sfFont_createFromFile ("../../../client/assets/fonts/fuenteCuerpo.ttf");
    if (!fuentes->cuerpo)
    {
        perror ("\nERROR - Crear fuente cuerpo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->auxEscribirMensaje = sfText_create ();
    if (!textos->auxEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto auxEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    textos->proximaInterfaz = sfText_create ();
    if (!textos->proximaInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto proximaInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    textos->nombreUsuario = sfText_create ();
    if (!textos->nombreUsuario)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoBotonEnviar = sfText_create ();
    if (!textos->textoBotonEnviar)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto textoBotonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloInterfaz = sfText_create ();
    if (!textos->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = sfRectangleShape_create ();
    if (!elementos->areaMensajes)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento areaMensajes.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->barraEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento barraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonEnviar = sfRectangleShape_create ();
    if (!elementos->botonEnviar)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento botonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo1 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo1)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento carpetaDecorativaFondo1.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo2 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo2)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento carpetaDecorativaFondo2.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloArriba = sfCircleShape_create ();
    if (!elementos->ojalilloArriba)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloArriba");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloAbajo = sfCircleShape_create ();
    if (!elementos->ojalilloAbajo)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloAbajo");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloSelecInterfaz = sfCircleShape_create ();
    if (!elementos->ojalilloSelecInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloSelecInterfaz");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionNombre = sfRectangleShape_create ();
    if (!elementos->separacionNombre)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento separacionNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionTitulo = sfRectangleShape_create ();
    if (!elementos->separacionTitulo)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento separacionTitulo.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->panelInterfaz = sfRectangleShape_create ();
    if (!elementos->panelInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento panelInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->solapaCambiarInterfaz = sfRectangleShape_create ();
    if (!elementos->solapaCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento solapaCambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

t_codigoRetorno _recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->ui = sfView_create ();
    if (!vistas->ui)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear vista de UI.\n");
        return ERROR_INICIALIZACION;
    }

    vistas->mensajes = sfView_create ();
    if (!vistas->mensajes)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear vista de mensajes.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


void _recursosComunesContactosSalas_configurarInterfaz (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // Deshabilitar foco
    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;

    // Setear cadenas vacias
    *(recursosComunesContactosSalas->logica.contextoMensajes.mensaje) = '\0';

    // Inicializar punto de insercion
    resetearPuntoInsercion (&(recursosComunesContactosSalas->logica.puntoInsercion));
}

void _recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // auxEscribirMensaje
    sfText_setFont (textos->auxEscribirMensaje, fuentes->cuerpo);
    sfText_setFillColor (textos->auxEscribirMensaje, sfColor_fromRGB (53, 53, 53));

    // proximaInterfaz
    sfText_setFont (textos->proximaInterfaz, fuentes->ui);
    sfText_setString (textos->proximaInterfaz, "SALAS");
    sfText_setFillColor (textos->proximaInterfaz, sfColor_fromRGB (94, 91, 87));
    sfText_rotate (textos->proximaInterfaz, -90);

    // nombreUsuario
    sfText_setFont (textos->nombreUsuario, fuentes->ui);
    sfText_setFillColor (textos->nombreUsuario, sfColor_fromRGB (43, 43, 43));

    // textoBotonEnviar
    sfText_setFont (textos->textoBotonEnviar, fuentes->ui);
    sfText_setString (textos->textoBotonEnviar, "ENVIAR");
    sfText_setFillColor (textos->textoBotonEnviar, sfColor_fromRGB (94, 91, 87));

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->ui);
    sfText_setString (textos->tituloInterfaz, "CONTACTOS");
    sfText_setFillColor (textos->tituloInterfaz, sfColor_fromRGB (43, 43, 43));
}

void _recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
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
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGB (212, 206, 194));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGBA (169, 163, 154, 191));

    // carpetaDecorativaFondo2
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGB (207, 201, 189));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGBA (169, 163, 154, 191));

    // ojalilloArriba
    sfCircleShape_setFillColor (elementos->ojalilloArriba, sfColor_fromRGBA (140, 136, 137, 191));
    sfCircleShape_setOutlineColor (elementos->ojalilloArriba, sfColor_fromRGBA (94, 91, 87, 191));

    // ojalilloAbajo
    sfCircleShape_setFillColor (elementos->ojalilloAbajo, sfColor_fromRGBA (140, 136, 137, 191));
    sfCircleShape_setOutlineColor (elementos->ojalilloAbajo, sfColor_fromRGBA (94, 91, 87, 191));

    // ojalilloSelecInterfaz
    sfCircleShape_setFillColor (elementos->ojalilloSelecInterfaz, sfColor_fromRGBA (140, 136, 137, 81));
    sfCircleShape_setOutlineColor (elementos->ojalilloSelecInterfaz, sfColor_fromRGBA (94, 91, 87, 61));

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

    // solapaCambiarInterfaz
    sfRectangleShape_setFillColor (elementos->solapaCambiarInterfaz, sfColor_fromRGB (217, 211, 199));
    sfRectangleShape_setOutlineColor (elementos->solapaCambiarInterfaz, sfColor_fromRGBA (169, 163, 154, 191));
}


void _recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos)
{
    // auxEscribirMensaje
    sfText_setPosition (textos->auxEscribirMensaje, (sfVector2f){449, 912});
    sfText_setCharacterSize (textos->auxEscribirMensaje, 24);

    // proximaInterfaz
    sfText_setPosition (textos->proximaInterfaz, (sfVector2f){343, 530});
    sfText_setCharacterSize (textos->proximaInterfaz, 20);
    sfText_setLetterSpacing (textos->proximaInterfaz, 5);

    // textoBotonEnviar
    sfText_setCharacterSize (textos->textoBotonEnviar, 22);
    centrarTextoEnArea (textos->textoBotonEnviar, 1747, 909, 115, 35);

    // tituloInterfaz
    sfText_setCharacterSize (textos->tituloInterfaz, 36);
    centrarTextoEnArea (textos->tituloInterfaz, 0, 0, 340, 120);
}

void _recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos)
{
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
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo1, (sfVector2f){370, 130});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo1, (sfVector2f){20, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo1, 1);

    // carpetaDecorativaFondo2
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo2, (sfVector2f){390.2, 195});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo2, (sfVector2f){16, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo2, 1);

    // ojalilloArriba
    sfCircleShape_setPosition (elementos->ojalilloArriba, (sfVector2f){5, 400});
    sfCircleShape_setRadius (elementos->ojalilloArriba, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloArriba, 1);

    // ojalilloAbajo
    sfCircleShape_setPosition (elementos->ojalilloAbajo, (sfVector2f){5, 600});
    sfCircleShape_setRadius (elementos->ojalilloAbajo, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloAbajo, 1);

    // ojalilloSelecInterfaz
    sfCircleShape_setPosition (elementos->ojalilloSelecInterfaz, (sfVector2f){347, 80});
    sfCircleShape_setRadius (elementos->ojalilloSelecInterfaz, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloSelecInterfaz, 1);

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

    // solapaCambiarInterfaz
    sfRectangleShape_setPosition (elementos->solapaCambiarInterfaz, (sfVector2f){342.5, 65});
    sfRectangleShape_setSize (elementos->solapaCambiarInterfaz, (sfVector2f){28, 1009});
    sfRectangleShape_setOutlineThickness (elementos->solapaCambiarInterfaz, 1.5);
}

void _recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    // UI
    sfView_setSize (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});

    // mensajes
    sfView_setSize (vistas->mensajes, (sfVector2f){1420, 780});                                          // Vista del tamanio del sfRectangleShape *areaMensajes
    sfView_setCenter (vistas->mensajes, (sfVector2f){1152, 480});                                      // Centro del sfRectangleShape *areaMensajes
    sfView_setViewport(vistas->mensajes, (sfFloatRect){0.230f, 0.089f, 0.740f, 0.773f});    // Proporciones del sfRectangleShape *areaMensajes
}


void _recursosComunesContactosSalas_liberarFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

void _recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirMensaje);
    DESTRUCTOR_SEGURO_TEXTO (textos->proximaInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->nombreUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoBotonEnviar);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
}

void _recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaMensajes);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirMensaje);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonEnviar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo1);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo2);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloArriba);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloAbajo);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloSelecInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionTitulo);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->panelInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->solapaCambiarInterfaz);
}

void _recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->ui);
    DESTRUCTOR_SEGURO_VISTA (vistas->mensajes);
}

