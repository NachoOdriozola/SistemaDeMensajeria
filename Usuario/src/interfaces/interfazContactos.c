#include "../../include/interfaces/interfazContactos.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void desactivarInterfazContactos (t_interfazContactos *interfazContactos);
static void renderizarAgendarContacto (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos);
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos);
static void interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos);

static int interfazContactos_inicializarTextos (t_interfazContactosTextos *textos);
static int interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
static void interfazContactos_configurarElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos);
static void interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos);

static void interfazContactos_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos);
static void interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos);
static void interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos);

static void interfazContactos_liberarTextos (t_interfazContactosTextos *textos);
static void interfazContactos_liberarElementos (t_interfazContactosElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirAgendarContacto (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickAgendarContacto (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);
static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);

static bool manejarEscribirAgendarContacto (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos, sfEvent eventoChar);

static bool manejarEnterIntentarAgendarContacto (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */


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
                if (manejarClickEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesContactosSalas, interfazContactos);
            }
            break;


        case sfEvtTextEntered:
            if (evento.text.unicode < 128)
            {
                if (manejarEscribirMensaje (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
            }
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
            {
                if (manejarEnterEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            }

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
            manejarReciboMensaje (&(recursosComunesContactosSalas->contextoMensajes), bufferRespuesta);
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



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
/*
void intentarSolicitudAmistad (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char *bufferSolicitud, *bufferRespuesta;
    char estadoSolicitud;

    bufferSolicitud = malloc (MAX_BUFFER_SOLICITUD);
    if (!bufferSolicitud)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }

    sprintf (bufferSolicitud, "%c|%s|%s", SOLICITUD_AGENDAR_CONTACTO, contextoAplicacion->usuario.nombre, interfazContactos->bufferAgendarContacto);
    printf ("Enviado: %s\n", bufferSolicitud);
    enviarSolicitudYRecibirRespuesta (contextoAplicacion->sock, bufferSolicitud, bufferRespuesta, MAX_BUFFER_RESPUESTA);
    sscanf (bufferRespuesta, "%c", &estadoSolicitud);

    free (bufferSolicitud);
    free (bufferRespuesta);

    if (estadoSolicitud == RESPUESTA_EXITO)
        printf ("Le envio la solicitud de amistad.\n");
    else if (estadoSolicitud == RESPUESTA_ERROR_SERVIDOR)
        printf ("No se envio la solicitud de amistad.\n");
}
*/

/** \brief Desactivar la interfaz de contactos para cambiar de interfaz.
 *
 * Modificar los estados de foco y los recursos graficos de texto y/o elementos que se necesiten desactivar para cambiar de interfaz.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
static void desactivarInterfazContactos (t_interfazContactos *interfazContactos)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazContactos->estadoFoco = ICT_NINGUNO;
}

/** \brief Renderizar los recursos graficos de agendar contacto.
 *
 * Si se encuentra habilitada la ventana emergente de agendar contacto, renderizar los elementos y textos graficos.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
static void renderizarAgendarContacto (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos)
{
    if ((interfazContactos->estadoFoco == AGENDAR_CONTACTO) || (interfazContactos->estadoFoco == ESCRIBIR_AGENDAR_CONTACTO))
    {
        // ELEMENTOS

        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalas->elementos.ventanaEmergente, NULL);
        sfRenderWindow_drawRectangleShape (renderizado, interfazContactos->elementos.barraEscribirAgendarContacto, NULL);


        // TEXTOS

        sfRenderWindow_drawText (renderizado, interfazContactos->textos.auxAgendarContacto, NULL);
        sfRenderWindow_drawText (renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente, NULL);
        sfRenderWindow_drawText (renderizado, recursosComunesContactosSalas->textos.tituloVentanaEmergente, NULL);
    }
}

/** \brief Deshabilitar los estados de foco de los recursos comunes entre las interfaces de contactos y salas y de la interfaz de contactos.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    interfazContactos->estadoFoco = ICT_NINGUNO;
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos de la interfaz de contactos.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 */
static void interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos)
{
    textos->agendarContacto = NULL;
    textos->auxAgendarContacto = NULL;
    textos->auxContactoSeleccionado = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos de la interfaz de contactos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 */
static void interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = NULL;
    elementos->barraEscribirAgendarContacto = NULL;
}

/** \brief Inicializar los recursos graficos de textos de la interfaz de contactos.
 *
 * Crea todos los recursos graficos de textos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazContactos_inicializarTextos (t_interfazContactosTextos *textos)
{
    textos->agendarContacto = sfText_create ();
    if (!textos->agendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto agendarContacto.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxAgendarContacto = sfText_create ();
    if (!textos->auxAgendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxAgendarContacto.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxContactoSeleccionado = sfText_create ();
    if (!textos->auxContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos de la interfaz de contactos.
 *
 * Crea todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos)
{
    elementos->areaContactoSeleccionado = sfRectangleShape_create ();
    if (!elementos->areaContactoSeleccionado)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento areaContactoSeleccionado.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirAgendarContacto = sfRectangleShape_create ();
    if (!elementos->barraEscribirAgendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento barraEscribirAgendarContacto.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de textos de la interfaz de contactos.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // agendarContacto
    sfText_setFont (textos->agendarContacto, fuentes->ui);
    sfText_setString (textos->agendarContacto, "+");
    sfText_setFillColor (textos->agendarContacto, sfColor_fromRGB (34, 48, 48));

    // auxAgregarContacto
    sfText_setFont (textos->auxAgendarContacto, fuentes->cuerpo);
    sfText_setFillColor (textos->auxAgendarContacto, sfColor_fromRGB (40, 54, 54));

    // auxContactoSeleccionado
    sfText_setFont (textos->auxContactoSeleccionado, fuentes->cuerpo);
    sfText_setFillColor (textos->auxContactoSeleccionado, sfColor_fromRGB (94, 91, 87));
    sfText_setString (textos->auxContactoSeleccionado, "amigo");

}

/** \brief Configurar los recursos graficos de elementos de la interfaz de contactos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_configurarElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setFillColor (elementos->areaContactoSeleccionado, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaContactoSeleccionado, sfColor_fromRGB (107, 94, 75));

    // barraEscribirAgendarContacto
    sfRectangleShape_setFillColor (elementos->barraEscribirAgendarContacto, sfColor_fromRGB (208, 208, 208));
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico de la interfaz de contactos.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos)
{
    // agendarContacto
    sfText_setPosition (textos->agendarContacto, (sfVector2f){220, 35});
    sfText_setCharacterSize (textos->agendarContacto, 60);

    // auxAgendarContacto
    sfText_setPosition (textos->auxAgendarContacto, (sfVector2f){802, 600});
    sfText_setCharacterSize (textos->auxAgendarContacto, 26);

    // auxContactoSeleccionado
    sfText_setCharacterSize (textos->auxContactoSeleccionado, 24);
    centrarTextoEnArea (textos->auxContactoSeleccionado, 852, 25, 600, 40);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana cada elemento grafico de la interfaz de contactos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos)
{
    // areaContactoSeleccionado
    sfRectangleShape_setPosition (elementos->areaContactoSeleccionado, (sfVector2f){852, 25});
    sfRectangleShape_setSize (elementos->areaContactoSeleccionado, (sfVector2f){600, 40});
    sfRectangleShape_setOutlineThickness (elementos->areaContactoSeleccionado, 2);

    // barraEscribirAgendarContacto
    sfRectangleShape_setPosition (elementos->barraEscribirAgendarContacto, (sfVector2f){800, 600});
    sfRectangleShape_setSize (elementos->barraEscribirAgendarContacto, (sfVector2f){280, 42});
}

/** \brief Renderizar la vista de UI de la interfaz de contactos.
 *
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de contactos y de los recursos comunes (compartidos) entre las
 * interfaces de contactos y salas. Ademas, si se encuentran habilitados, renderiza la ventana emergente de agendar contacto, notificaciones y el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
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

/** \brief Renderizar los recursos graficos de textos de la interfaz de contactos.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos)
{
    //sfRenderWindow_drawText (renderizado, textos->agendarContacto, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxContactoSeleccionado, NULL);
}

/** \brief Renderizar los recursos graficos de elementos de la interfaz de contactos.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaContactoSeleccionado, NULL);
}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de contactos.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 */
static void interfazContactos_liberarTextos (t_interfazContactosTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->agendarContacto);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxAgendarContacto);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxContactoSeleccionado);
}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de contactos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 */
static void interfazContactos_liberarElementos (t_interfazContactosElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaContactoSeleccionado);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirAgendarContacto);
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en agendar un nuevo contacto.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickAgendarContacto (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    if (!clickEnTexto (renderizado, interfazContactos->textos.agendarContacto))
        return EVENTO_NO_MANEJADO;

    if (interfazContactos->estadoFoco == ICT_NINGUNO)
        interfazContactos->estadoFoco = AGENDAR_CONTACTO;
    else
        interfazContactos->estadoFoco = ICT_NINGUNO;

    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    sfText_setString (recursosComunesContactosSalas->textos.tituloVentanaEmergente, "AGENDAR CONTACTO");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloVentanaEmergente, (sfVector2f){830, 400});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir un nombre para agendarlo como un nuevo contacto.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
static bool manejarClickEscribirAgendarContacto (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    sfFloatRect limiteTextoAux;

    if ((interfazContactos->estadoFoco != AGENDAR_CONTACTO) || (!clickEnRectangulo (renderizado, interfazContactos->elementos.barraEscribirAgendarContacto)))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = ESCRIBIR_AGENDAR_CONTACTO;
    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    limiteTextoAux = sfText_getGlobalBounds (interfazContactos->textos.auxAgendarContacto);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){805.5 + limiteTextoAux.width, 632});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en abrir notificaciones.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.notificaciones))
        return EVENTO_NO_MANEJADO;

    if (recursosComunesContactosSalas->estadoFoco == RCCS_NINGUNO)
        recursosComunesContactosSalas->estadoFoco = NOTIFICACIONES;
    else
        recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;

    interfazContactos->estadoFoco = ICT_NINGUNO;
    *(interfazContactos->bufferAgendarContacto) = '\0';
    sfText_setString (recursosComunesContactosSalas->textos.tituloVentanaEmergente, "NOTIFICACIONES");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloVentanaEmergente, (sfVector2f){840, 400});

    return EVENTO_MANEJADO;
}
*/

/** \brief Manejar el evento de click en cerrar la ventana emergente.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente))
        return EVENTO_NO_MANEJADO;

    deshabilitarFocos (recursosComunesContactosSalas, interfazContactos);
    *(interfazContactos->bufferAgendarContacto) = '\0';

    return EVENTO_MANEJADO;
}
*/

/** \brief Manejar el evento de click en la solapa para cambiar de interfaz.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_SALAS;
    desactivarInterfazContactos (interfazContactos);
    activarInterfazSalas (recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para cambiar a la interfaz de configuraciones.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesContactosSalas->textos.configuraciones))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONFIG;
    desactivarInterfazContactos (interfazContactos);
    deshabilitarFocos (recursosComunesContactosSalas, interfazContactos);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de escribir un nombre para agendarlo como un nuevo contacto.
 *
 * Si se encuentra habilitada la escritura para agendar un nuevo contacto, se agrega el caracter al buffer que contiene el nombre del contacto, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarEscribirAgendarContacto (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (interfazContactos->estadoFoco != ESCRIBIR_AGENDAR_CONTACTO)
        return EVENTO_NO_MANEJADO;

    ingresarCaracterABuffer (interfazContactos->bufferAgendarContacto, MAX_NOMBRE_USUARIO - 1, eventoChar);
    sfText_setString (interfazContactos->textos.auxAgendarContacto, interfazContactos->bufferAgendarContacto);
    limiteTextoAux = sfText_getGlobalBounds (interfazContactos->textos.auxAgendarContacto);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){805.5 + limiteTextoAux.width, 632});

    return EVENTO_MANEJADO;
}
*/

/** \brief Manejar el evento de enviar solicitud de contacto.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarEnterIntentarAgendarContacto (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_AGENDAR_CONTACTO)
        return EVENTO_NO_MANEJADO;

    if (strlen (interfazContactos->bufferAgendarContacto) == 0)
        return EVENTO_NO_MANEJADO;

    intentarSolicitudAmistad (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}
*/





























