#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"


void recursosComunesContactosSalas_inicializarValoresNulos (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // FUENTES
    _recursosComunesContactosSalas_inicializarValoresNulosFuentes (&(recursosComunesContactosSalas->fuentes));

    // TEXTOS
    _recursosComunesContactosSalas_inicializarValoresNulosTextos (&(recursosComunesContactosSalas->textos));

    // ELEMENTOS
    _recursosComunesContactosSalas_inicializarValoresNulosElementos (&(recursosComunesContactosSalas->elementos));

    // VISTAS
    _recursosComunesContactosSalas_inicializarValoresNulosVistas (&(recursosComunesContactosSalas->vistas));
}

t_codigoRetorno recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // FUENTES
    if (_recursosComunesContactosSalas_inicializarFuentes (&(recursosComunesContactosSalas->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_recursosComunesContactosSalas_inicializarTextos (&(recursosComunesContactosSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_recursosComunesContactosSalas_inicializarElementos (&(recursosComunesContactosSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // VISTAS
    if (_recursosComunesContactosSalas_inicializarVistas (&(recursosComunesContactosSalas->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // LISTA DE MENSAJES
    _recursosComunesContactosSalas_crearListaMensajes (&(recursosComunesContactosSalas->logica.contextoMensajes));

    return EXITO;
}

void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _recursosComunesContactosSalas_configurarInterfaz (recursosComunesContactosSalas);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _recursosComunesContactosSalas_configurarTextos (&(recursosComunesContactosSalas->textos), &(recursosComunesContactosSalas->fuentes));

    // ELEMENTOS
    _recursosComunesContactosSalas_configurarElementos (&(recursosComunesContactosSalas->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTO
    _recursosComunesContactosSalas_tamYPosVentanaTextos (&(recursosComunesContactosSalas->textos));

    // ELEMENTOS
    _recursosComunesContactosSalas_tamYPosVentanaElementos (&(recursosComunesContactosSalas->elementos));

    // VISTAS
    _recursosComunesContactosSalas_tamVistas (&(recursosComunesContactosSalas->vistas));
}

void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, textos->proximaInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoBotonEnviar, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaMensajes, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonEnviar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo2, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo1, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->solapaCambiarInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->panelInterfaz, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloArriba, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloAbajo, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloSelecInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionTitulo, NULL);
}

void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // FUENTES
    _recursosComunesContactosSalas_liberarFuentes (&(recursosComunesContactosSalas->fuentes));

    // TEXTOS
    _recursosComunesContactosSalas_liberarTextos (&(recursosComunesContactosSalas->textos));

    // ELEMENTOS
    _recursosComunesContactosSalas_liberarElementos (&(recursosComunesContactosSalas->elementos));

    // VISTAS
    _recursosComunesContactosSalas_liberarVistas (&(recursosComunesContactosSalas->vistas));

    // LISTA DE MENSAJES
    recursosComunesContactosSalas_vaciarListaMensajes (&(recursosComunesContactosSalas->logica.contextoMensajes));
}
