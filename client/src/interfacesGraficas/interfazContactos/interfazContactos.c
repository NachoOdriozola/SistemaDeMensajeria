#include "interfacesGraficas/interfazContactos/interfazContactos.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void establecerYPosicionarNombreUsuario (t_interfazContactos *interfazContactos, const char *nombreUsuario);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos)
{
    //FUENTES
    _interfazContactos_inicializarValoresNulosFuentes (&(interfazContactos->fuentes));

    // TEXTOS
    _interfazContactos_inicializarValoresNulosTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_inicializarValoresNulosElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_inicializarValoresNulosVistas (&(interfazContactos->vistas));
}

t_codigoRetorno interfazContactos_inicializar (t_interfazContactos *interfazContactos)
{
    //FUENTES
    if (_interfazContactos_inicializarFuentes (&(interfazContactos->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_interfazContactos_inicializarTextos (&(interfazContactos->textos), &(interfazContactos->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazContactos_inicializarElementos (&(interfazContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //VISTAS
    if (_interfazContactos_inicializarVistas (&(interfazContactos->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //LISTA DE MENSAJES
    _interfazContactos_listaMensajes_crear (&(interfazContactos->logica.contextoMensajes));

    return EXITO;
}

void interfazContactos_configurar (t_interfazContactos *interfazContactos)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazContactos_configurarInterfaz (interfazContactos);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazContactos_configurarTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_configurarElementos (&(interfazContactos->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTO
    _interfazContactos_tamYPosVentanaTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_tamYPosVentanaElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_tamVistas (&(interfazContactos->vistas));
}

void interfazContactos_prepararInterfaz (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    MAXIMIZAR_VENTANA (sfRenderWindow_getNativeHandle (contextoAplicacion->renderizado), SW_MAXIMIZE);
    establecerYPosicionarNombreUsuario (interfazContactos, contextoAplicacion->usuario.nombre);
}

void interfazContactos_ejecutar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    _interfazContactos_accion (contextoAplicacion, interfazContactos);
    _interfazContactos_actualizar (contextoAplicacion, interfazContactos);
    _interfazContactos_renderizar (contextoAplicacion->renderizado, interfazContactos);
}

void interfazContactos_liberar (t_interfazContactos *interfazContactos)
{
    //FUENTES
    _interfazContactos_liberarFuentes (&(interfazContactos->fuentes));

    // TEXTOS
    _interfazContactos_liberarTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_liberarElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_liberarVistas (&(interfazContactos->vistas));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void establecerYPosicionarNombreUsuario (t_interfazContactos *interfazContactos, const char *nombreUsuario)
{
    sfFloatRect limitesNombreUsuario;
    unsigned short int pixeles = 32;
    
    sfText_setString (interfazContactos->textos.nombreUsuario, nombreUsuario);
    do
    {
        sfText_setCharacterSize (interfazContactos->textos.nombreUsuario, pixeles);
        centrarTextoEnArea (interfazContactos->textos.nombreUsuario, 44, 888, 254, 120);
        limitesNombreUsuario = sfText_getLocalBounds (interfazContactos->textos.nombreUsuario);
        pixeles -= 2;
    } while (limitesNombreUsuario.size.x > 254);
}

