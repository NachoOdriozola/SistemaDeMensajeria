#include "../../../include/interfacesGraficas/interfazSalas/interfazSalas_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void desactivarRecursosInterfazSalas (t_interfazSalas *interfazSalas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazSalas_deshabilitarFocos (t_interfazSalas *interfazSalas)
{
    interfazSalas->recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    interfazSalas->estadoFoco = IS_NINGUNO;
}


bool _interfazSalas_manejarClickCambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazSalas->recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    omitirEventosPendientes (contextoAplicacion->renderizado);
    desactivarRecursosInterfazSalas (interfazSalas);
    recursosComunesContactosSalas_activarInterfazContactos (interfazSalas->recursosComunesContactosSalas);
    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetearInterfaz (t_interfazSalas *interfazSalas)
{
    // Deshabilitar focos.
    interfazSalas->estadoFoco = IS_NINGUNO;
}

/*
 * Desactivar y resetear los recursos de la interfaz de salas en situaciones que la interfaz no continue con su actividad.
 */
static void desactivarRecursosInterfazSalas (t_interfazSalas *interfazSalas)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    resetearInterfaz (interfazSalas);
}

