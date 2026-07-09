#include "../../../include/interfacesGraficas/interfazSalas/interfazSalas_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */



/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazSalas_resetear (sfRenderWindow *renderizado, t_interfazSalas *interfazSalas)
{
    // --------------- RESETEAR INTERFAZ ---------------

    omitirEventosPendientes (renderizado);
    _interfazSalas_deshabilitarFocos (interfazSalas);
}

void _interfazSalas_deshabilitarFocos (t_interfazSalas *interfazSalas)
{
    interfazSalas->recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    interfazSalas->estadoFoco = IS_NINGUNO;
}


bool _interfazSalas_manejarClickCambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazSalas->recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    interfazSalas_resetear (contextoAplicacion->renderizado, interfazSalas);
    recursosComunesContactosSalas_activarInterfazContactos (interfazSalas->recursosComunesContactosSalas);
    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */



