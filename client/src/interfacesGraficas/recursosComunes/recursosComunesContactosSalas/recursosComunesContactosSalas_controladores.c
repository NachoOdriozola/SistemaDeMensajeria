#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetearInterfaz (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

static void activarInterfazContactos_configurarTextos (t_recursosComunesContactosSalasTextos *textos);

static void activarInterfazSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos);

static void posicionarPuntoInsercion (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void recursosComunesContactosSalas_manejarRedimensionamientoVentana (sfRenderWindow *renderizado, t_recursosComunesContactosSalasVistas *vistas, sfEvent eventoRedimensionamiento)
{
    sfVector2u nuevoTamVentana;

    if (eventoRedimensionamiento.size.width < ANCHO_MINIMO_VENTANA)
        nuevoTamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        nuevoTamVentana.x = eventoRedimensionamiento.size.width;

    if (eventoRedimensionamiento.size.height < ALTO_MINIMO_VENTANA)
        nuevoTamVentana.y = ALTO_MINIMO_VENTANA;
    else
        nuevoTamVentana.y = eventoRedimensionamiento.size.height;

    sfRenderWindow_setSize (renderizado, nuevoTamVentana);

    // Redimensionar vista UI.
    sfView_setSize (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});
}


void recursosComunesContactosSalas_activarInterfazContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- RESETEAR INTERFAZ ---------------
    resetearInterfaz (recursosComunesContactosSalas);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTO
    activarInterfazContactos_configurarTextos (&(recursosComunesContactosSalas->textos));
}

void recursosComunesContactosSalas_activarInterfazSalas (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- RESETEAR INTERFAZ ---------------
    resetearInterfaz (recursosComunesContactosSalas);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    activarInterfazSalas_configurarTextos (&(recursosComunesContactosSalas->textos));
}


void recursosComunesContactosSalas_establecerNombreUsuario (t_recursosComunesContactosSalas *recursosComunesContactosSalas, const char *nombreUsuario)
{
    sfText_setString (recursosComunesContactosSalas->textos.nombreUsuario, nombreUsuario);
}

void recursosComunesContactosSalas_posicionarNombreUsuario (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfFloatRect limitesNombreUsuario;
    unsigned short int pixeles = 32;
    
    do
    {
        sfText_setCharacterSize (recursosComunesContactosSalas->textos.nombreUsuario, pixeles);
        centrarTextoEnArea (recursosComunesContactosSalas->textos.nombreUsuario, 44, 888, 254, 120);
        limitesNombreUsuario = sfText_getLocalBounds (recursosComunesContactosSalas->textos.nombreUsuario);
        pixeles -= 2;
    } while (limitesNombreUsuario.width > 254);
}


bool recursosComunesContactosSalas_manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    recursosComunesContactosSalas->estadoFoco = ESCRIBIR_MENSAJE;
    posicionarPuntoInsercion (recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}

bool recursosComunesContactosSalas_manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;

    recursosComunesContactosSalas->estadoFoco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}


bool recursosComunesContactosSalas_manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar)
{
    if (recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesContactosSalas->logica.contextoMensajes.mensaje, MAX_MENSAJE, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion (recursosComunesContactosSalas);
    }

    return EVENTO_MANEJADO;
}


bool recursosComunesContactosSalas_manejarPegarTextoDesdePortapapelesAEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (recursosComunesContactosSalas->logica.contextoMensajes.mensaje, MAX_MENSAJE) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion (recursosComunesContactosSalas);
    }

    return EVENTO_MANEJADO;
}


bool recursosComunesContactosSalas_manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfVector2f tamVista, posCentroVista;
    sfVector2f posUltimoMensaje;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentroVista = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(recursosComunesContactosSalas->logica.contextoMensajes.ultimoMensaje->dato)));

    if (posCentroVista.y - tamVista.y / 2.f > posUltimoMensaje.y)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}

bool recursosComunesContactosSalas_manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfVector2f tamVista, posCentroVista;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentroVista = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);

    if (posCentroVista.y + tamVista.y / 2.f < 870)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}


bool recursosComunesContactosSalas_manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll)
{
    sfVector2f tamVista, posCentro;
    sfVector2f posUltimoMensaje;
    float desplazamientoY;
    float superiorVista, inferiorVista;
    float limiteSuperior, limiteInferior;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentro = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(recursosComunesContactosSalas->logica.contextoMensajes.ultimoMensaje->dato)));

    desplazamientoY = -eventoScroll.mouseWheelScroll.delta * VELOCIDAD_SCROLL;

    superiorVista = posCentro.y - tamVista.y / 2.f;
    inferiorVista = posCentro.y + tamVista.y / 2.f;

    limiteSuperior = posUltimoMensaje.y;
    limiteInferior = 870;

    if ((desplazamientoY < 0) && (superiorVista + desplazamientoY < limiteSuperior))
        desplazamientoY = limiteSuperior - superiorVista;

    if ((desplazamientoY > 0) && (inferiorVista + desplazamientoY > limiteInferior))
        desplazamientoY = limiteInferior - inferiorVista;

    if (desplazamientoY != 0)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, desplazamientoY});

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetearInterfaz (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // Deshabilitar foco
    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;

    // Setear cadenas vacias
    *(recursosComunesContactosSalas->logica.contextoMensajes.mensaje) = '\0';

    // Resetear el punto de insercion
    resetearPuntoInsercion (&(recursosComunesContactosSalas->logica.puntoInsercion));
}


static void activarInterfazContactos_configurarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    // auxEscribirMensaje
    sfText_setString (textos->auxEscribirMensaje, "");

    // proximaInterfaz
    sfText_setString (textos->proximaInterfaz, "SALAS");
    sfText_setPosition (textos->proximaInterfaz, (sfVector2f){343, 530});

    // tituloInterfaz
    sfText_setString (textos->tituloInterfaz, "CONTACTOS");
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){79, 37});
}


static void activarInterfazSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    // auxEscribirMensaje
    sfText_setString (textos->auxEscribirMensaje, "");

    // proximaInterfaz
    sfText_setString (textos->proximaInterfaz, "CONTACTOS");
    sfText_setPosition (textos->proximaInterfaz, (sfVector2f){343, 567});

    // tituloInterfaz
    sfText_setString (textos->tituloInterfaz, "SALAS");
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){120, 37});
}


static void posicionarPuntoInsercion (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfFloatRect limitesAuxEscribirMensaje;

    limitesAuxEscribirMensaje = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451 + limitesAuxEscribirMensaje.width, 942});
}

