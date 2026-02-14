#include "../../include/interfaces/interfazSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void cambiarInterfazAContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void interfazSalas_inicializarValoresNulosTextos (t_interfazSalasTextos *textos);
static void interfazSalas_inicializarValoresNulosElementos (t_interfazSalasElementos *elementos);

static int interfazSalas_inicializarTextos (t_interfazSalasTextos *textos);
static int interfazSalas_inicializarElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_configurarTextos (t_interfazSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
static void interfazSalas_configurarElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_tamYPosVentanaTextos (t_interfazSalasTextos *textos);
static void interfazSalas_tamYPosVentanaElementos (t_interfazSalasElementos *elementos);

static void interfazSalas_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas);
static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const t_interfazSalasTextos *textos);
static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const t_interfazSalasElementos *elementos);

static void interfazSalas_liberarTextos (t_interfazSalasTextos *textos);
static void interfazSalas_liberarElementos (t_interfazSalasElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickSolapaCambiarInterfaz (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);
static bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazSalas_inicializar (t_interfazSalas *interfazSalas)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTOS

    interfazSalas_inicializarTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_inicializarElementos (&(interfazSalas->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTOS

    if (interfazSalas_inicializarTextos (&(interfazSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazSalas_inicializarElementos (&(interfazSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazSalas_configurar (t_interfazSalas *interfazSalas, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------



    // --------------- CONFIGURAR BUFFERS ---------------



    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_configurarTextos (&(interfazSalas->textos), fuentes);


    // ELEMENTOS

    interfazSalas_configurarElementos (&(interfazSalas->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_tamYPosVentanaTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_tamYPosVentanaElementos (&(interfazSalas->elementos));
}

void interfazSalas_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    sfEvent evento;


    sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento);
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
            //if (manejarClickEscribirMensaje (contextoAplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            //if (manejarClickNotificaciones (contextoAplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            //if (manejarClickCerrarVentanaEmergente (contextoAplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            if (manejarClickSolapaCambiarInterfaz (contextoAplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
            //if (manejarClickAreaMensajes (contextoAplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            //if (manejarClickCambiarInterfazConfig (contextoAplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
            //if (manejarClickEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtTextEntered:
        if (evento.text.unicode < 128)
        {
            //if (manejarEscribirMensaje (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtKeyPressed:
        if (evento.key.code == sfKeyEnter)
        {
            //if (manejarEnterEnviarMensaje (contextoAplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtMouseWheelScrolled:
        //if (manejarScrollAreaMensajes (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
        break;


    default:
        break;
    }
}

void interfazSalas_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    // RECIBIR MENSAJES DE OTROS USUARIOS
    char *bufferRespuesta;

    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    if (recibirRespuesta (contextoAplicacion->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA) == RECIBIO_RESPUESTA)
    {
        switch (*bufferRespuesta)
        {
        case RESPUESTA_AGENDAR_CONTACTO:
            //agregarNotificacion (&(recursosComunesContactosSalas->listaNotificaciones), bufferRespuesta, &(recursosComunesContactosSalas->fuentes));
            break;

        case RESPUESTA_MENSAJE:
            break;
        }
    }
    free (bufferRespuesta);


    // --------------- PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITADO)
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion));
    else
        resetearPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion));
}

void interfazSalas_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------

    renderizarVistaMensajes (renderizado, recursosComunesContactosSalas);


    // --------------- RENDERIZAR VISTA DE UI ---------------

    interfazSalas_renderizarVistaUI (renderizado, recursosComunesContactosSalas, interfazSalas);


    sfRenderWindow_display (renderizado);
}

void interfazSalas_liberar (t_interfazSalas *interfazSalas)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_liberarTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_liberarElementos (&(interfazSalas->elementos));
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/** \brief Modificar las configuraciones de las habilitaciones, buffers y recursos graficos para adaptarlos a la interfaz de contactos.
 *
 * Deshabilitar las habilitaciones y restablecer los buffers al inicio.
 * Modificar unicamente los recursos graficos de texto y/o elementos que se necesiten adaptar para cambiar a la interfaz de contactos.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
static void cambiarInterfazAContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITADO;
    recursosComunesContactosSalas->habilitaciones.escribirMensaje = DESHABILITADO;
    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITADO;

    resetearPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion));


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirMensaje
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");

    // proximaInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.proximaInterfaz, "SALAS");
    sfText_setPosition (recursosComunesContactosSalas->textos.proximaInterfaz, (sfVector2f){343, 530});

    // tituloInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.tituloInterfaz, "CONTACTOS");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloInterfaz, (sfVector2f){79, 37});


    // ELEMENTOS

}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 */
static void interfazSalas_inicializarValoresNulosTextos (t_interfazSalasTextos *textos)
{
    textos->textoEnDesarrollo = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 */
static void interfazSalas_inicializarValoresNulosElementos (t_interfazSalasElementos *elementos)
{
    elementos->taparBarraEscribirMensaje = NULL;
}

/** \brief Inicializar los recursos graficos de textos de la interfaz de salas.
 *
 * Crea todos los recursos graficos de textos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazSalas_inicializarTextos (t_interfazSalasTextos *textos)
{
    textos->textoEnDesarrollo = sfText_create ();
    if (!textos->textoEnDesarrollo)
    {
        perror ("\nERROR - Interfaz de salas, crear texto textoEnDesarrollo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos de la interfaz de salas.
 *
 * Crea todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazSalas_inicializarElementos (t_interfazSalasElementos *elementos)
{
    elementos->taparBarraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->taparBarraEscribirMensaje)
    {
        perror ("\nERROR - Interfaz de salas, crear elemento taparBarraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

/** \brief Configurar los recursos graficos de textos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
static void interfazSalas_configurarTextos (t_interfazSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // textoEnDesarrollo
    sfText_setFont (textos->textoEnDesarrollo, fuentes->ui);
    sfText_setString (textos->textoEnDesarrollo, "Salas públicas . Próximamente");
    sfText_setFillColor (textos->textoEnDesarrollo, sfColor_fromRGBA (94, 91, 87, 191));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_configurarElementos (t_interfazSalasElementos *elementos)
{
    // taparBarraEscribirMensaje
    sfRectangleShape_setFillColor (elementos->taparBarraEscribirMensaje, sfColor_fromRGB (244, 241, 236));
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_tamYPosVentanaTextos (t_interfazSalasTextos *textos)
{
    // textoEnDesarrollo
    sfText_setCharacterSize (textos->textoEnDesarrollo, 30);
    centrarTextoEnArea (textos->textoEnDesarrollo, 442, 90, 1420, 780);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_tamYPosVentanaElementos (t_interfazSalasElementos *elementos)
{
    // taparBarraEscribirMensaje
    sfRectangleShape_setPosition (elementos->taparBarraEscribirMensaje, (sfVector2f){440, 905});
    sfRectangleShape_setSize (elementos->taparBarraEscribirMensaje, (sfVector2f){1920, 45});
}

/** \brief Renderizar la vista de UI de la interfaz de salas.
 *
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de salas y de los recursos comunes (compartidos) entre las
 * interfaces de contactos y salas. Ademas, si se encuentran habilitados, renderiza la ventana emergente de notificaciones y el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
static void interfazSalas_renderizarVistaUI (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas)
{
    // --------------- ESTABLECER VISTA DE UI ---------------

    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.UI);


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesContactosSalas_renderizarElementos (renderizado, &(recursosComunesContactosSalas->elementos));
    interfazSalas_renderizarElementos (renderizado, &(interfazSalas->elementos));


    // TEXTOS

    recursosComunesContactosSalas_renderizarTextos (renderizado, &(recursosComunesContactosSalas->textos));
    interfazSalas_renderizarTextos (renderizado, &(interfazSalas->textos));


    sfRenderWindow_drawRectangleShape (renderizado, interfazSalas->elementos.taparBarraEscribirMensaje, NULL); // TAPAR LOS ELEMENTOS GRAFICOS QUE NO SE ENCUENTREN ACTIVOS EN EL INCREMENTO 1.


    // --------------- RENDERIZAR NOTIFICACIONES ---------------

    renderizarNotificaciones (renderizado, recursosComunesContactosSalas);


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}

/** \brief Renderizar los recursos graficos de textos de la interfaz de salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const t_interfazSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->textoEnDesarrollo, NULL);
}

/** \brief Renderizar los recursos graficos de elementos de la interfaz de salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const t_interfazSalasElementos *elementos)
{

}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 */
static void interfazSalas_liberarTextos (t_interfazSalasTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->textoEnDesarrollo);
}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 */
static void interfazSalas_liberarElementos (t_interfazSalasElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->taparBarraEscribirMensaje);
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en la barra para escribir mensaje.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.barraEscribirMensaje))
    {
        recursosComunesContactosSalas->habilitaciones.escribirMensaje = HABILITADO;
        recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITADO;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451 + limiteTextoAux.width, 942});
        return EVENTO_MANEJADO;
    }
    recursosComunesContactosSalas->habilitaciones.escribirMensaje = DESHABILITADO;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en abrir notificaciones.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.notificaciones))
        return EVENTO_NO_MANEJADO;

    if (recursosComunesContactosSalas->habilitaciones.notificaciones == DESHABILITADO)
        recursosComunesContactosSalas->habilitaciones.notificaciones = HABILITADO;
    else
        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITADO;
    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITADO;
    sfText_setString (recursosComunesContactosSalas->textos.tituloVentanaEmergente, "NOTIFICACIONES");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloVentanaEmergente, (sfVector2f){840, 400});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en cerrar la ventana emergente.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente))
        return EVENTO_NO_MANEJADO;

    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITADO;
    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITADO;

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en la solapa para cambiar de interfaz.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickSolapaCambiarInterfaz (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    cambiarInterfazAContactos (recursosComunesContactosSalas, interfazSalas);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el area de mensajes.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.areaMensajes))
    {
        recursosComunesContactosSalas->habilitaciones.areaMensajes = HABILITADO;
        return EVENTO_MANEJADO;
    }
    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITADO;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para cambiar a la interfaz de configuraciones.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesContactosSalas->textos.configuraciones))
        return EVENTO_NO_MANEJADO;

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONFIG;
    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITADO;

    return EVENTO_MANEJADO;
}










































