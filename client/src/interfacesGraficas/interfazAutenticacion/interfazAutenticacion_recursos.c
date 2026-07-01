#include "../../../include/interfacesGraficas/interfazAutenticacion/interfazAutenticacion_recursos.h"


void _interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos)
{

}

void _interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos)
{

}


t_codigoRetorno _interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos)
{


    return EXITO;
}

t_codigoRetorno _interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos)
{


    return EXITO;
}


void _interfazAutenticacion_configurarInterfaz (t_interfazAutenticacion *interfazAutenticacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // Asignar recursos comunes
    interfazAutenticacion->recursosComunesAutenticacionRegistro = recursosComunesAutenticacionRegistro;

    // Deshabilitar foco
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

void _interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{

}

void _interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos)
{

}


void _interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos)
{

}

void _interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos)
{

}


void _interfazAutenticacion_renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos)
{

}

void _interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos)
{

}


void _interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos)
{

}

void _interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos)
{

}

