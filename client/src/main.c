#include "logica/cliente.h"

int main()
{
    ContextoAplicacion contextoAplicacion;
    InterfacesGraficas interfacesGraficas;

    if (aplicacion_inicializar (&contextoAplicacion, &interfacesGraficas) == ERROR_INICIALIZACION)
    {
        aplicacion_liberar (&contextoAplicacion, &interfacesGraficas);
        return ERROR_INICIALIZACION;
    }
    aplicacion_configurar (&contextoAplicacion, &interfacesGraficas);

    while (APLICACION_ESTA_EJECUTANDOSE (contextoAplicacion.renderizado))
        aplicacion_ejecutar (&contextoAplicacion, &interfacesGraficas);

    aplicacion_liberar (&contextoAplicacion, &interfacesGraficas);
    return EXITO;
}
