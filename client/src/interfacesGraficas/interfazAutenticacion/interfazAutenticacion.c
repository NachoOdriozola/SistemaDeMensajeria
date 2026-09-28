#include "interfacesGraficas/interfazAutenticacion/interfazAutenticacion.h"


void interfazAutenticacion_inicializarValoresNulos (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS
    _interfazAutenticacion_inicializarValoresNulosTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_inicializarValoresNulosElementos (&(interfazAutenticacion->elementos));
}

t_codigoRetorno interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- ASIGNAR RECURSOS COMUNES ---------------

    interfazAutenticacion->recursosComunesAutenticacionRegistro = recursosComunesAutenticacionRegistro;

    // --------------- CREAR RECURSOS GRAFICOS ---------------

    // TEXTOS
    if (_interfazAutenticacion_inicializarTextos (&(interfazAutenticacion->textos), &(interfazAutenticacion->recursosComunesAutenticacionRegistro->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazAutenticacion_inicializarElementos (&(interfazAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazAutenticacion_configurarInterfaz (interfazAutenticacion);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazAutenticacion_configurarTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_configurarElementos (&(interfazAutenticacion->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazAutenticacion_tamYPosVentanaTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_tamYPosVentanaElementos (&(interfazAutenticacion->elementos));
}

void interfazAutenticacion_ejecutar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    _interfazAutenticacion_accion (contextoAplicacion, interfazAutenticacion);
    _interfazAutenticacion_actualizar (contextoAplicacion, interfazAutenticacion);
    _interfazAutenticacion_renderizar (contextoAplicacion->renderizado, interfazAutenticacion);
}

void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS
    _interfazAutenticacion_liberarTextos (&(interfazAutenticacion->textos));

    // ELEMENTOS
    _interfazAutenticacion_liberarElementos (&(interfazAutenticacion->elementos));
}

