#include "../../include/interfaces/interfazConfig.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazConfig_inicializarValoresNulosFuentes (t_interfazConfigFuentes *fuentes);
static void interfazConfig_inicializarValoresNulosTextos (t_interfazConfigTextos *textos);
static void interfazConfig_inicializarValoresNulosElementos (t_interfazConfigElementos *elementos);

static int interfazConfig_inicializarFuentes (t_interfazConfigFuentes *fuentes);
static int interfazConfig_inicializarTextos (t_interfazConfigTextos *textos);
static int interfazConfig_inicializarElementos (t_interfazConfigElementos *elementos);

static void interfazConfig_configurarTextos (t_interfazConfigTextos *textos, const t_interfazConfigFuentes *fuentes);
static void interfazConfig_configurarElementos (t_interfazConfigElementos *elementos);

static void interfazConfig_tamYPosVentanaTextos (t_interfazConfigTextos *textos);
static void interfazConfig_tamYPosVentanaElementos (t_interfazConfigElementos *elementos);

static void interfazConfig_renderizarTextos (sfRenderWindow *renderizado, const t_interfazConfigTextos *textos);
static void interfazConfig_renderizarElementos (sfRenderWindow *renderizado, const t_interfazConfigElementos *elementos);

static void interfazConfig_liberarFuentes (t_interfazConfigFuentes *fuentes);
static void interfazConfig_liberarTextos (t_interfazConfigTextos *textos);
static void interfazConfig_liberarElementos (t_interfazConfigElementos *elementos);



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



int interfazConfig_inicializar (t_interfazConfig *interfazConfig)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // FUENTES

    interfazConfig_inicializarValoresNulosFuentes (&(interfazConfig->fuentes));


    // TEXTOS

    interfazConfig_inicializarValoresNulosTextos (&(interfazConfig->textos));


    // ELEMENTOS

    interfazConfig_inicializarValoresNulosElementos (&(interfazConfig->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // FUENTES

    if (interfazConfig_inicializarFuentes (&(interfazConfig->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // TEXTOS

    if (interfazConfig_inicializarTextos (&(interfazConfig->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazConfig_inicializarElementos (&(interfazConfig->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazConfig_configurar (t_interfazConfig *interfazConfig)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazConfig->estadoFoco = ICF_NINGUNO;


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazConfig_configurarTextos (&(interfazConfig->textos), &(interfazConfig->fuentes));


    // ELEMENTOS

    interfazConfig_configurarElementos (&(interfazConfig->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazConfig_tamYPosVentanaTextos (&(interfazConfig->textos));


    // ELEMENTOS

    interfazConfig_tamYPosVentanaElementos (&(interfazConfig->elementos));
}

void interfazConfig_accion (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig)
{
    sfEvent evento;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {

        case sfEvtClosed:
            interfazConfig_liberar (interfazConfig);
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (clickEnRectangulo (contextoAplicacion->renderizado, interfazConfig->elementos.rectanguloVolver))
                    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
            }
            break;


        default:
            break;
        }
    }
}

void interfazConfig_actualizar (t_interfazConfig *interfazConfig)
{

}

void interfazConfig_renderizar (sfRenderWindow *renderizado, const t_interfazConfig *interfazConfig)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    interfazConfig_renderizarElementos (renderizado, &(interfazConfig->elementos));


    // TEXTOS

    interfazConfig_renderizarTextos (renderizado, &(interfazConfig->textos));


    sfRenderWindow_display (renderizado);
}

void interfazConfig_liberar (t_interfazConfig *interfazConfig)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // FUENTES

    interfazConfig_liberarFuentes (&(interfazConfig->fuentes));


    // TEXTOS

    interfazConfig_liberarTextos (&(interfazConfig->textos));


    // ELEMENTOS

    interfazConfig_liberarElementos (&(interfazConfig->elementos));
}



/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazConfig_inicializarValoresNulosFuentes (t_interfazConfigFuentes *fuentes)
{
    fuentes->ui = NULL;
}

static void interfazConfig_inicializarValoresNulosTextos (t_interfazConfigTextos *textos)
{
    textos->textoConfig = NULL;
}

static void interfazConfig_inicializarValoresNulosElementos (t_interfazConfigElementos *elementos)
{
    elementos->rectanguloVolver = NULL;
}


static int interfazConfig_inicializarFuentes (t_interfazConfigFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("../../../client/assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int interfazConfig_inicializarTextos (t_interfazConfigTextos *textos)
{
    textos->textoConfig = sfText_create ();
    if (!textos->textoConfig)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear texto textoConfig.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int interfazConfig_inicializarElementos (t_interfazConfigElementos *elementos)
{
    elementos->rectanguloVolver = sfRectangleShape_create ();
    if (!elementos->rectanguloVolver)
    {
        perror ("\nERROR - Interfaz de configuraciones, crear elemento rectanguloVolver.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


static void interfazConfig_configurarTextos (t_interfazConfigTextos *textos, const t_interfazConfigFuentes *fuentes)
{
    // textoConfig
    sfText_setFont (textos->textoConfig, fuentes->ui);
    sfText_setString (textos->textoConfig, "CONFIGURACIONES");
    sfText_setFillColor (textos->textoConfig, sfColor_fromRGB (0, 0, 0));
}

static void interfazConfig_configurarElementos (t_interfazConfigElementos *elementos)
{
    // rectanguloVolver
    sfRectangleShape_setFillColor (elementos->rectanguloVolver, sfColor_fromRGB (0, 0, 0));
}


static void interfazConfig_tamYPosVentanaTextos (t_interfazConfigTextos *textos)
{
    // textoConfig
    sfText_setPosition (textos->textoConfig, (sfVector2f){1000, 500});
    sfText_setCharacterSize (textos->textoConfig, 36);
}

static void interfazConfig_tamYPosVentanaElementos (t_interfazConfigElementos *elementos)
{
    // rectanguloVolver
    sfRectangleShape_setPosition (elementos->rectanguloVolver, (sfVector2f){1000, 650});
    sfRectangleShape_setSize (elementos->rectanguloVolver, (sfVector2f){60, 60});
}


static void interfazConfig_renderizarTextos (sfRenderWindow *renderizado, const t_interfazConfigTextos *textos)
{
     sfRenderWindow_drawText (renderizado, textos->textoConfig, NULL);
}

static void interfazConfig_renderizarElementos (sfRenderWindow *renderizado, const t_interfazConfigElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->rectanguloVolver, NULL);
}


static void interfazConfig_liberarFuentes (t_interfazConfigFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

static void interfazConfig_liberarTextos (t_interfazConfigTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->textoConfig);
}

static void interfazConfig_liberarElementos (t_interfazConfigElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->rectanguloVolver);
}











