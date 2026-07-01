#include "../include/cliente.h"

int main()
{
    t_contextoAplicacion contextoAplicacion;
    t_interfacesGraficas interfacesGraficas;

    if (inicializarAplicacion (&contextoAplicacion, &interfacesGraficas) == ERROR_INICIALIZACION)
    {
        liberarAplicacion (&contextoAplicacion, &interfacesGraficas);
        return ERROR_INICIALIZACION;
    }
    configurarAplicacion (&contextoAplicacion, &interfacesGraficas);

    while (APLICACION_ESTA_EJECUTANDOSE (contextoAplicacion.renderizado))
        ejecutarAplicacion (&contextoAplicacion, &interfacesGraficas);

    liberarAplicacion (&contextoAplicacion, &interfacesGraficas);
    return EXITO;
}
