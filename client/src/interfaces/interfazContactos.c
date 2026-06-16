#include "../../include/interfaces/interfazContactos.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazContactos (t_interfazContactos *interfazContactos);
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);

static void interfazContactos_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos);

static void manejarReciboMensaje (t_contextoMensajes *contextoMensajes, char *bufferRespuesta, int idContactoSeleccionado);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);

static bool manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos);
static void interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos);

static int interfazContactos_inicializarTextos (t_interfazContactosTextos *textos);
static int interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
static void interfazContactos_configurarElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos);
static void interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos);
static void interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos);

static void interfazContactos_liberarTextos (t_interfazContactosTextos *textos);
static void interfazContactos_liberarElementos (t_interfazContactosElementos *elementos);



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */

   

void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos)
{
    // TEXTOS

    interfazContactos_inicializarValoresNulosTextos (&(interfazContactos->textos));


    // ELEMENTOS

    interfazContactos_inicializarValoresNulosElementos (&(interfazContactos->elementos));
}

int interfazContactos_inicializar (t_interfazContactos *interfazContactos)
{
    // TEXTOS

    if (interfazContactos_inicializarTextos (&(interfazContactos->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazContactos_inicializarElementos (&(interfazContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazContactos_configurar (t_interfazContactos *interfazContactos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // --------------- CONFIGURAR CONTACTO SELECCIONADO ---------------

    interfazContactos->idContactoSeleccionado = ID_INVALIDO;


    // --------------- CONFIGURAR FOCO ---------------

    interfazContactos->estadoFoco = ICT_NINGUNO;


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazContactos_configurarTextos (&(interfazContactos->textos), fuentes);


    // ELEMENTOS

    interfazContactos_configurarElementos (&(interfazContactos->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazContactos_tamYPosVentanaTextos (&(interfazContactos->textos));


    // ELEMENTOS

    interfazContactos_tamYPosVentanaElementos (&(interfazContactos->elementos));
}

void interfazContactos_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    sfEvent evento;


    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {

        case sfEvtClosed:
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtResized:
            manejarRedimensionamientoVentanaContactosSalas (contextoAplicacion->renderizado, &(recursosComunesContactosSalas->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (manejarClickEscribirMensaje (contextoAplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
                if (manejarClickCambiarInterfazSalas (contextoAplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
                if (manejarClickAreaMensajes (contextoAplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
                if (manejarClickEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesContactosSalas, interfazContactos);
            }
            break;


        case sfEvtTextEntered:
            if (manejarEscribirMensaje (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (manejarEnterEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirMensaje (recursosComunesContactosSalas) == EVENTO_MANEJADO) break;

            if (evento.key.code == sfKeyUp)
                if (manejarDesplazarArribaAreaMensajes (recursosComunesContactosSalas) == EVENTO_MANEJADO) break;

            if (evento.key.code == sfKeyDown)
                if (manejarDesplazarAbajoAreaMensajes (recursosComunesContactosSalas) == EVENTO_MANEJADO) break;

            break;


        case sfEvtMouseWheelScrolled:
            if (manejarScrollAreaMensajes (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
            break;


        default:
            break;
        }
    }
}

void interfazContactos_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    // --------------- RECIBIR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];

    if (recibirRespuesta (contextoAplicacion->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA) == RECIBIO_RESPUESTA)
    {
        switch (*bufferRespuesta)
        {
        case RESPUESTA_MENSAJE:
            manejarReciboMensaje (&(recursosComunesContactosSalas->contextoMensajes), bufferRespuesta, interfazContactos->idContactoSeleccionado);
            break;
        }
    }


    // --------------- PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
    else if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
        resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
}

void interfazContactos_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------

    renderizarVistaMensajes (renderizado, recursosComunesContactosSalas);


    // --------------- RENDERIZAR VISTA DE UI ---------------

    interfazContactos_renderizarVistaUI (renderizado, recursosComunesContactosSalas, interfazContactos);


    sfRenderWindow_display (renderizado);
}

void interfazContactos_liberar (t_interfazContactos *interfazContactos)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazContactos_liberarTextos (&(interfazContactos->textos));


    // ELEMENTOS

    interfazContactos_liberarElementos (&(interfazContactos->elementos));
}



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazContactos (t_interfazContactos *interfazContactos)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazContactos->estadoFoco = ICT_NINGUNO;
}

static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    interfazContactos->estadoFoco = ICT_NINGUNO;
}


/*
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de salas y de los recursos comunes (compartidos) entre las interfaces de contactos y salas.
 * Ademas, si se encuentra habilitado, renderiza el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 */
static void interfazContactos_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos)
{
    // --------------- ESTABLECER VISTA DE UI ---------------

    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.UI);


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesContactosSalas_renderizarElementos (renderizado, &(recursosComunesContactosSalas->elementos));
    interfazContactos_renderizarElementos (renderizado, &(interfazContactos->elementos));


    // TEXTOS

    recursosComunesContactosSalas_renderizarTextos (renderizado, &(recursosComunesContactosSalas->textos));
    interfazContactos_renderizarTextos (renderizado, &(interfazContactos->textos));


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}


static void manejarReciboMensaje (t_contextoMensajes *contextoMensajes, char *bufferRespuesta, int idContactoSeleccionado)
{
    int idEmisor;
    char texto [MAX_MENSAJE];

    sscanf (&(bufferRespuesta[2]), "%d|%[^\n]", &idEmisor, texto);
    if (idEmisor == idContactoSeleccionado)
        insertarMensaje (contextoMensajes, texto, MENSAJE_REMOTO);
}



/* ============================================================================================================================================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    t_respuestaSeleccionContacto respuestaSeleccionContacto;
    char estadoRespuestaMensaje;
    int largoMensaje;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    largoMensaje = strlen (recursosComunesContactosSalas->contextoMensajes.bufferMensaje);

    if (largoMensaje == 0)
        return EVENTO_NO_MANEJADO;

    if (*(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) == '/') // Si es un comando para seleccionar un chat con un contacto
    {
        if ((largoMensaje - 1 >= 3) && (largoMensaje  -1 < MAX_NOMBRE_USUARIO))
        {
                respuestaSeleccionContacto = enviarSolicitudSeleccionarContacto (contextoAplicacion->sock, contextoAplicacion->usuario.nombre, &(recursosComunesContactosSalas->contextoMensajes.bufferMensaje[1]));
                if (respuestaSeleccionContacto.estado == SOLICITUD_EXITO)
                {
                    interfazContactos->idContactoSeleccionado = respuestaSeleccionContacto.idUsuario;
                    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, &(recursosComunesContactosSalas->contextoMensajes.bufferMensaje[1]));
                    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
                    mapListaCircular (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), vaciarMensaje);
                }
        }
    }
    else // Es un mensaje
    {
        if (enviarSolicitudMensaje (contextoAplicacion->sock, contextoAplicacion->usuario.id, interfazContactos->idContactoSeleccionado, recursosComunesContactosSalas->contextoMensajes.bufferMensaje) == SOLICITUD_EXITO)
            insertarMensaje (&(recursosComunesContactosSalas->contextoMensajes), recursosComunesContactosSalas->contextoMensajes.bufferMensaje, MENSAJE_PROPIO);
    }

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->contextoMensajes.bufferMensaje);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451, 942});


    return EVENTO_MANEJADO;
}

static bool manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_SALAS;
    desactivarRecursosInterfazContactos (interfazContactos);
    activarInterfazSalas (recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}


static bool manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    t_respuestaSeleccionContacto respuestaSeleccionContacto;
    char estadoRespuestaMensaje;
    int largoMensaje;

    if (recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    largoMensaje = strlen (recursosComunesContactosSalas->contextoMensajes.bufferMensaje);

    if (largoMensaje == 0)
        return EVENTO_NO_MANEJADO;

    if (*(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) == '/') // Si es un comando para seleccionar un chat con un contacto
    {
        if ((largoMensaje - 1 >= 3) && (largoMensaje  -1 < MAX_NOMBRE_USUARIO))
        {
                respuestaSeleccionContacto = enviarSolicitudSeleccionarContacto (contextoAplicacion->sock, contextoAplicacion->usuario.nombre, &(recursosComunesContactosSalas->contextoMensajes.bufferMensaje[1]));
                if (respuestaSeleccionContacto.estado == SOLICITUD_EXITO)
                {
                    interfazContactos->idContactoSeleccionado = respuestaSeleccionContacto.idUsuario;
                    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, &(recursosComunesContactosSalas->contextoMensajes.bufferMensaje[1]));
                    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
                    mapListaCircular (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), vaciarMensaje);
                }
        }
    }
    else // Es un mensaje
    {
        if (enviarSolicitudMensaje (contextoAplicacion->sock, contextoAplicacion->usuario.id, interfazContactos->idContactoSeleccionado, recursosComunesContactosSalas->contextoMensajes.bufferMensaje) == SOLICITUD_EXITO)
            insertarMensaje (&(recursosComunesContactosSalas->contextoMensajes), recursosComunesContactosSalas->contextoMensajes.bufferMensaje, MENSAJE_PROPIO);
    }

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->contextoMensajes.bufferMensaje);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451, 942});


    return EVENTO_MANEJADO;
}



/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos)
{
    textos->auxContactoSeleccionado = NULL;
}

static void interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = NULL;
}


static int interfazContactos_inicializarTextos (t_interfazContactosTextos *textos)
{
    textos->auxContactoSeleccionado = sfText_create ();
    if (!textos->auxContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = sfRectangleShape_create ();
    if (!elementos->areaContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento areaContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}


static void interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // auxContactoSeleccionado
    sfText_setFont (textos->auxContactoSeleccionado, fuentes->cuerpo);
    sfText_setFillColor (textos->auxContactoSeleccionado, sfColor_fromRGB (94, 91, 87));
}

static void interfazContactos_configurarElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setFillColor (elementos->areaContactoSeleccionado, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaContactoSeleccionado, sfColor_fromRGB (107, 94, 75));
}


static void interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos)
{
    // auxContactoSeleccionado
    sfText_setCharacterSize (textos->auxContactoSeleccionado, 24);
    centrarTextoEnArea (textos->auxContactoSeleccionado, 852, 25, 600, 40);
}

static void interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setPosition (elementos->areaContactoSeleccionado, (sfVector2f){852, 25});
    sfRectangleShape_setSize (elementos->areaContactoSeleccionado, (sfVector2f){600, 40});
    sfRectangleShape_setOutlineThickness (elementos->areaContactoSeleccionado, 2);
}


static void interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxContactoSeleccionado, NULL);
}

static void interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaContactoSeleccionado, NULL);
}


static void interfazContactos_liberarTextos (t_interfazContactosTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxContactoSeleccionado);
}

static void interfazContactos_liberarElementos (t_interfazContactosElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaContactoSeleccionado);
}
























