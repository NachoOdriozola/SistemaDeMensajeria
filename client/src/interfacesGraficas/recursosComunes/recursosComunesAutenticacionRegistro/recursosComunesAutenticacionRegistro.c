#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"


void recursosComunesAutenticacionRegistro_inicializarValoresNulos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // FUENTES
    _recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (&(recursosComunesAutenticacionRegistro->fuentes));

    // TEXTOS
    _recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (&(recursosComunesAutenticacionRegistro->textos));

    // ELEMENTOS
    _recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

t_codigoRetorno recursosComunesAutenticacionRegistro_inicializar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // FUENTES
    if (_recursosComunesAutenticacionRegistro_inicializarFuentes (&(recursosComunesAutenticacionRegistro->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_recursosComunesAutenticacionRegistro_inicializarTextos (&(recursosComunesAutenticacionRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_recursosComunesAutenticacionRegistro_inicializarElementos (&(recursosComunesAutenticacionRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void recursosComunesAutenticacionRegistro_configurar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _recursosComunesAutenticacionRegistro_configurarInterfaz (recursosComunesAutenticacionRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _recursosComunesAutenticacionRegistro_configurarTextos (&(recursosComunesAutenticacionRegistro->textos), &(recursosComunesAutenticacionRegistro->fuentes));

    // ELEMENTOS
    _recursosComunesAutenticacionRegistro_configurarElementos (&(recursosComunesAutenticacionRegistro->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTOS
    _recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (&(recursosComunesAutenticacionRegistro->textos));

    // ELEMENTO
    _recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

void recursosComunesAutenticacionRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresoIncorrecto, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoBotonIngresar, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoCambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->subrayadoTitulo, NULL);
}

void recursosComunesAutenticacionRegistro_liberar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // FUENTES
    _recursosComunesAutenticacionRegistro_liberarFuentes (&(recursosComunesAutenticacionRegistro->fuentes));

    // TEXTOS
    _recursosComunesAutenticacionRegistro_liberarTextos (&(recursosComunesAutenticacionRegistro->textos));

    // ELEMENTOS
    _recursosComunesAutenticacionRegistro_liberarElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

