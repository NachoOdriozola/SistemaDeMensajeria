#include "especificas.h"


///FUNCIONES DE INICIALIZACION ESPECIFICAS


int verificarDatosGuardados (s_aplicacion *app)
{
    s_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "rb");
    if (!archDatos)
        return INICIO_SESION_MANUAL;

    fread (&datosGuardados, sizeof (s_datosGuardados), 1, archDatos);
    app->usuario.id = datosGuardados.id;
    strcpy (app->usuario.nombre, datosGuardados.nombre);

    fclose (archDatos);

    return INICIO_SESION_AUTOMATICO;
}

int inicializarFuentes (s_fuentes *fuentes)
{
    fuentes->fuente1 = sfFont_createFromFile ("fuente1.ttf");
    if (!fuentes->fuente1)
    {
        perror ("ERROR - Crear fuente 1.\n");
        return ERROR_INICIALIZACION;
    }

    return OK;
}

void liberarFuentes (s_fuentes *fuentes)
{
    sfFont_destroy (fuentes->fuente1);
}

void crearEscalaElementos (s_aplicacion *app)
{
    app->ventana.escalaElementos.x = app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_MAXIMIZADO_X;
    app->ventana.escalaElementos.y = app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_MAXIMIZADO_Y;
}

void crearEscalaPixeles (s_aplicacion *app)
{
    app->ventana.escalaPixeles = fminf (app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_MAXIMIZADO_X, app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_MAXIMIZADO_Y);
}

void eventoMaximizadoAutomatico (s_aplicacion *app)
{
    sfEvent eventoPrimerMaximizado;
    sfVector2f nuevoTamPantalla;

    //Proceso todos los eventos acumulados hasta encontrar el maximizado.
    while (sfRenderWindow_pollEvent (app->renderizado, &eventoPrimerMaximizado))
    {
        if (eventoPrimerMaximizado.type == sfEvtResized)
        {
            nuevoTamPantalla.x = eventoPrimerMaximizado.size.width;
            nuevoTamPantalla.y = eventoPrimerMaximizado.size.height;
        }
    }
    app->ventana.tamOriginalPantalla = nuevoTamPantalla;
    app->ventana.tamActualPantalla = nuevoTamPantalla;
}

void maximizadoAutomaticoVentana (s_aplicacion *app)
{
    HWND hwnd;

    hwnd = sfRenderWindow_getSystemHandle (app->renderizado);
    ShowWindow (hwnd, SW_MAXIMIZE);

    eventoMaximizadoAutomatico (app);
    ajustarVista (app, app->ventana.tamOriginalPantalla);
    crearEscalaElementos (app);
    crearEscalaPixeles (app);
}

void setupListaMensajes (void *mensaje, void *fuente)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    sfFont *y = (sfFont*)fuente;

    sfText_setFont (x->mensaje, y);
    sfText_setFillColor (x->mensaje, sfColor_fromRGB (34, 48, 48));
}

void tamListaMensajes (void *mensaje, void *escalaPixeles)
{
    s_mensaje *x = (s_mensaje*)mensaje;
    float y = *(float*)escalaPixeles;

    sfText_setCharacterSize (x->mensaje, 26 * y);
}

void liberarMensaje (void *mensaje)
{
    s_mensaje *x = (s_mensaje*)mensaje;

    sfText_destroy (x->mensaje);
}











