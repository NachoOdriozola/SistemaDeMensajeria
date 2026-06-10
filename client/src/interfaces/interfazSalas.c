#include "../../include/interfaces/interfazSalas.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazSalas (t_interfazSalas *interfazSalas);
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactoSalas, t_interfazSalas *interfazSalas);

static void interfazSalas_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickCambiarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazSalas_inicializarValoresNulosTextos (t_interfazSalasTextos *textos);
static void interfazSalas_inicializarValoresNulosElementos (t_interfazSalasElementos *elementos);

static int interfazSalas_inicializarTextos (t_interfazSalasTextos *textos);
static int interfazSalas_inicializarElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_configurarTextos (t_interfazSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
static void interfazSalas_configurarElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_tamYPosVentanaTextos (t_interfazSalasTextos *textos);
static void interfazSalas_tamYPosVentanaElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const t_interfazSalasTextos *textos);
static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const t_interfazSalasElementos *elementos);

static void interfazSalas_liberarTextos (t_interfazSalasTextos *textos);
static void interfazSalas_liberarElementos (t_interfazSalasElementos *elementos);



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



void interfazSalas_inicializarValoresNulos (t_interfazSalas *interfazSalas)
{
    // TEXTOS

    interfazSalas_inicializarValoresNulosTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_inicializarValoresNulosElementos (&(interfazSalas->elementos));
}

int interfazSalas_inicializar (t_interfazSalas *interfazSalas)
{
    // TEXTOS

    if (interfazSalas_inicializarTextos (&(interfazSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazSalas_inicializarElementos (&(interfazSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazSalas_configurar (t_interfazSalas *interfazSalas, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazSalas->estadoFoco = IS_NINGUNO;


    // --------------- CONFIGURAR BUFFERS ---------------



    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_configurarTextos (&(interfazSalas->textos), fuentes);


    // ELEMENTOS

    interfazSalas_configurarElementos (&(interfazSalas->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_tamYPosVentanaTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_tamYPosVentanaElementos (&(interfazSalas->elementos));
}

void interfazSalas_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    sfEvent evento;


    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {

        case sfEvtClosed:
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtResized:
            manejarRedimensionamientoVentanaContactosSalas (contextoAplicacion->renderizado, &(recursosComunesContactosSalas->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (manejarClickCambiarInterfazContactos (contextoAplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesContactosSalas, interfazSalas);
            }
            break;


        default:
            break;
        }
    }
}

void interfazSalas_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    // --------------- PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
    else if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
        resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
}

void interfazSalas_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------

    //renderizarVistaMensajes (renderizado, recursosComunesContactosSalas);


    // --------------- RENDERIZAR VISTA DE UI ---------------

    interfazSalas_renderizarVistaUI (renderizado, recursosComunesContactosSalas, interfazSalas);


    sfRenderWindow_display (renderizado);
}

void interfazSalas_liberar (t_interfazSalas *interfazSalas)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_liberarTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_liberarElementos (&(interfazSalas->elementos));
}



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazSalas (t_interfazSalas *interfazSalas)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazSalas->estadoFoco = IS_NINGUNO;
}

static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactoSalas, t_interfazSalas *interfazSalas)
{
    recursosComunesContactoSalas->estadoFoco = RCCS_NINGUNO;
    interfazSalas->estadoFoco = IS_NINGUNO;
}


/*
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de salas y de los recursos comunes (compartidos) entre las interfaces de contactos y salas.
 * Ademas, si se encuentra habilitado, renderiza el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 */
static void interfazSalas_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas)
{
    // --------------- ESTABLECER VISTA DE UI ---------------

    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.UI);


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesContactosSalas_renderizarElementos (renderizado, &(recursosComunesContactosSalas->elementos));
    interfazSalas_renderizarElementos (renderizado, &(interfazSalas->elementos));


    // TEXTOS

    recursosComunesContactosSalas_renderizarTextos (renderizado, &(recursosComunesContactosSalas->textos));
    interfazSalas_renderizarTextos (renderizado, &(interfazSalas->textos));


    sfRenderWindow_drawRectangleShape (renderizado, interfazSalas->elementos.taparBarraEscribirMensaje, NULL); // TAPAR LOS ELEMENTOS GRAFICOS QUE NO SE ENCUENTREN ACTIVOS EN EL INCREMENTO 1.


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}



/* ============================================================================================================================================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickCambiarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    desactivarRecursosInterfazSalas (interfazSalas);
    activarInterfazContactos (recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}



/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazSalas_inicializarValoresNulosTextos (t_interfazSalasTextos *textos)
{
    textos->textoEnDesarrollo = NULL;
}

static void interfazSalas_inicializarValoresNulosElementos (t_interfazSalasElementos *elementos)
{
    elementos->taparBarraEscribirMensaje = NULL;
}


static int interfazSalas_inicializarTextos (t_interfazSalasTextos *textos)
{
    textos->textoEnDesarrollo = sfText_create ();
    if (!textos->textoEnDesarrollo)
    {
        perror ("\nERROR - Interfaz de salas, crear texto textoEnDesarrollo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int interfazSalas_inicializarElementos (t_interfazSalasElementos *elementos)
{
    elementos->taparBarraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->taparBarraEscribirMensaje)
    {
        perror ("\nERROR - Interfaz de salas, crear elemento taparBarraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}


static void interfazSalas_configurarTextos (t_interfazSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // textoEnDesarrollo
    sfText_setFont (textos->textoEnDesarrollo, fuentes->ui);
    sfText_setFillColor (textos->textoEnDesarrollo, sfColor_fromRGBA (94, 91, 87, 191));
    sfUint32 bufferTextoEnDesarrollo [] = {'S', 'a', 'l', 'a', 's', ' ', 'p', 0x00fa, 'b', 'l', 'i', 'c', 'a', 's', ' ', '.', ' ', 'P', 'r', 0x00f3, 'x', 'i', 'm', 'a', 'm', 'e', 'n', 't', 'e', 0};
    sfText_setUnicodeString (textos->textoEnDesarrollo, bufferTextoEnDesarrollo);
}

static void interfazSalas_configurarElementos (t_interfazSalasElementos *elementos)
{
    // taparBarraEscribirMensaje
    sfRectangleShape_setFillColor (elementos->taparBarraEscribirMensaje, sfColor_fromRGB (244, 241, 236));
}


static void interfazSalas_tamYPosVentanaTextos (t_interfazSalasTextos *textos)
{
    // textoEnDesarrollo
    sfText_setCharacterSize (textos->textoEnDesarrollo, 30);
    centrarTextoEnArea (textos->textoEnDesarrollo, 442, 90, 1420, 780);
}

static void interfazSalas_tamYPosVentanaElementos (t_interfazSalasElementos *elementos)
{
    // taparBarraEscribirMensaje
    sfRectangleShape_setPosition (elementos->taparBarraEscribirMensaje, (sfVector2f){440, 905});
    sfRectangleShape_setSize (elementos->taparBarraEscribirMensaje, (sfVector2f){1920, 45});
}


static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const t_interfazSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->textoEnDesarrollo, NULL);
}

static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const t_interfazSalasElementos *elementos)
{

}


static void interfazSalas_liberarTextos (t_interfazSalasTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->textoEnDesarrollo);
}

static void interfazSalas_liberarElementos (t_interfazSalasElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->taparBarraEscribirMensaje);
}








































