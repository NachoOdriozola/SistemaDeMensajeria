#include "interfacesGraficas/interfazRegistro/interfazRegistro.h"


void interfazRegistro_inicializarValoresNulos (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    _interfazRegistro_inicializarValoresNulosTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_inicializarValoresNulosElementos (&(interfazRegistro->elementos));
}

t_codigoRetorno interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    if (_interfazRegistro_inicializarTextos (&(interfazRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazRegistro_inicializarElementos (&(interfazRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazRegistro_configurarInterfaz (interfazRegistro, recursosComunesAutenticacionRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazRegistro_configurarTextos (&(interfazRegistro->textos), &(interfazRegistro->recursosComunesAutenticacionRegistro->fuentes));

    // ELEMENTOS
    _interfazRegistro_configurarElementos (&(interfazRegistro->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazRegistro_tamYPosVentanaTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_tamYPosVentanaElementos (&(interfazRegistro->elementos));
}

void interfazRegistro_ejecutar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    _interfazRegistro_accion (contextoAplicacion, interfazRegistro);
    _interfazRegistro_actualizar (contextoAplicacion, interfazRegistro);
    _interfazRegistro_renderizar (contextoAplicacion->renderizado, interfazRegistro);
}

void interfazRegistro_liberar (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS
    _interfazRegistro_liberarTextos (&(interfazRegistro->textos));

    // ELEMENTOS
    _interfazRegistro_liberarElementos (&(interfazRegistro->elementos));
}

