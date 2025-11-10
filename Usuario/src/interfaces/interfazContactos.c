#include "../../include/interfaces/interfazContactos.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void cambiarInterfazASalas (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int interfazContactos_inicializarTexto (s_interfazContactosTexto *texto);
static int interfazContactos_inicializarElementos (s_interfazContactosElementos *elementos);

static void interfazContactos_configurarTexto (s_interfazContactosTexto *texto, const s_fuentes *fuentes);
static void interfazContactos_configurarElementos (s_interfazContactosElementos *elementos);

static void interfazContactos_tamYPosVentanaTexto (s_interfazContactosTexto *texto, const s_ventana *ventana);
static void interfazContactos_tamYPosVentanaElementos (s_interfazContactosElementos *elementos, const s_ventana *ventana);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana);
static bool manejarClickEscribirAgendarContacto (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana);
static bool manejarClickNotificaciones (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos);
static bool manejarClickAgendarContacto (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos);
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos);
static bool manejarClickSolapaCambiarInterfaz (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos);
static bool manejarClickCambiarInterfazConfig (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos);

static bool manejarEscribirAgendarContacto (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana, sfEvent eventoChar);

static bool manejarEnterIntentarAgendarContacto (s_interfazContactos *interfazContactos, s_aplicacion *aplicacion);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazContactos_inicializar (s_interfazContactos *interfazContactos)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    interfazContactos->texto.agendarContacto = NULL;
    interfazContactos->texto.auxAgendarContacto = NULL;


    // ELEMENTOS

    interfazContactos->elementos.barraEscribirAgendarContacto = NULL;


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (interfazContactos_inicializarTexto (&(interfazContactos->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazContactos_inicializarElementos (&(interfazContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazContactos_configurar (s_interfazContactos *interfazContactos, const s_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;
    interfazContactos->habilitaciones.escribirAgendarContacto = DESHABILITAR_ESCRIBIR_AGENDAR_CONTACTO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(interfazContactos->bufferAgendarContacto) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazContactos_configurarTexto (&(interfazContactos->texto), fuentes);


    // ELEMENTOS

    interfazContactos_configurarElementos (&(interfazContactos->elementos));
}

void interfazContactos_tamYPosVentana (s_interfazContactos *interfazContactos, const s_ventana *ventana)
{
    // --------------- TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazContactos_tamYPosVentanaTexto (&(interfazContactos->texto), ventana);


    // ELEMENTOS

    interfazContactos_tamYPosVentanaElementos (&(interfazContactos->elementos), ventana);
}

void interfazContactos_accion (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfEvent evento;


    sfRenderWindow_pollEvent (aplicacion->renderizado, &evento);
    switch (evento.type)
    {

    case sfEvtClosed:
        aplicacion->aplicacionEjecutandose = DETENER_APLICACION;
        break;


    case sfEvtResized:
        if (manejarRedimensionamientoVentana (aplicacion, evento) == ERROR_SIN_MEMORIA)
            aplicacion->aplicacionEjecutandose = DETENER_APLICACION;
        break;


    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (manejarClickEscribirMensaje (aplicacion->renderizado, recursosComunesContactosSalas, interfazContactos, &(aplicacion->ventana)) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirAgendarContacto (aplicacion->renderizado, recursosComunesContactosSalas, interfazContactos, &(aplicacion->ventana)) == EVENTO_MANEJADO) break;
            if (manejarClickNotificaciones (aplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
            if (manejarClickAgendarContacto (aplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
            if (manejarClickCerrarVentanaEmergente (aplicacion->renderizado, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
            if (manejarClickSolapaCambiarInterfaz (aplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazConfig (aplicacion, recursosComunesContactosSalas, interfazContactos) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtTextEntered:
        if (evento.text.unicode < 128)
        {
            if (manejarEscribirMensaje (recursosComunesContactosSalas, &(aplicacion->ventana), evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirAgendarContacto (recursosComunesContactosSalas, interfazContactos, &(aplicacion->ventana), evento) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtKeyPressed:
        if (evento.key.code == sfKeyEnter)
        {
            if (manejarEnterEnviarMensaje (recursosComunesContactosSalas, aplicacion) == EVENTO_MANEJADO) break;
            if (manejarEnterIntentarAgendarContacto (interfazContactos, aplicacion) == EVENTO_MANEJADO) break;
        }
        break;


    default:
        break;
    }
}

void interfazContactos_actualizar (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // RECIBIR MENSAJES DE OTROS USUARIOS
    char *bufferRespuesta;

    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    if (recibirRespuesta (aplicacion->sock, bufferRespuesta) == RECIBIO_RESPUESTA)
    {
        switch (*bufferRespuesta)
        {
        case INDICE_RESPUESTA_SOLICITUD_AMISTAD:
            agregarNotificacion (&(aplicacion->listaNotificaciones), bufferRespuesta, aplicacion->ventana, aplicacion->mensajes.fuentes);
            break;

        case INDICE_RESPUESTA_MENSAJE:
            break;
        }
    }
    free (bufferRespuesta);


    // --------------- PUNTO DE INSERCION ---------------

    if ((recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE) ||
        (interfazContactos->habilitaciones.escribirAgendarContacto == HABILITAR_ESCRIBIR_AGENDAR_CONTACTO))
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion), &(recursosComunesContactosSalas->habilitaciones.contadorPuntoInsercion));
    else
        reiniciarPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion), &(recursosComunesContactosSalas->habilitaciones.contadorPuntoInsercion));
}

void interfazContactos_renderizar (s_aplicacion *aplicacion, const s_interfazContactos *interfazContactos, const s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfRenderWindow_clear (aplicacion->renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesContactosSalas_renderizarElementos (aplicacion->renderizado, &(recursosComunesContactosSalas->elementos));


    // TEXTO

    recursosComunesContactosSalas_renderizarTexto (aplicacion->renderizado, &(recursosComunesContactosSalas->texto));
    sfRenderWindow_drawText (aplicacion->renderizado, interfazContactos->texto.agendarContacto, NULL);


    // --------------- RENDERIZAR AGENDAR CONTACTOS ---------------

    if (interfazContactos->habilitaciones.agendarContacto == HABILITAR_AGENDAR_CONTACTO)
    {
        // ELEMENTOS

        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, recursosComunesContactosSalas->elementos.ventanaEmergente, NULL);
        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, interfazContactos->elementos.barraEscribirAgendarContacto, NULL);


        // TEXTO

        sfRenderWindow_drawText (aplicacion->renderizado, interfazContactos->texto.auxAgendarContacto, NULL);
        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->texto.cerrarVentanaEmergente, NULL);
        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->texto.tituloVentanaEmergente, NULL);
    }


    // --------------- RENDERIZAR NOTIFICACIONES ---------------

    if (recursosComunesContactosSalas->habilitaciones.notificaciones == HABILITAR_NOTIFICACIONES)
    {
        // ELEMENTOS

        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, recursosComunesContactosSalas->elementos.ventanaEmergente, NULL);


        // TEXTO

        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->texto.cerrarVentanaEmergente, NULL);
        sfRenderWindow_drawText (aplicacion->renderizado, recursosComunesContactosSalas->texto.tituloVentanaEmergente, NULL);


        // LISTA DE NOTIFICACIONES

        mapListaSimpleConComplemento (&(aplicacion->listaNotificaciones), aplicacion->renderizado, renderizarListaNotificaciones);
    }


    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------

    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), aplicacion->renderizado, renderizarListaMensajes);


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, recursosComunesContactosSalas->elementos.puntoInsercion, NULL);


    sfRenderWindow_display (aplicacion->renderizado);
}

void interfazContactos_liberar (s_interfazContactos *interfazContactos)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO

    DESTRUCTOR_SEGURO_TEXTO (interfazContactos->texto.agendarContacto);
    DESTRUCTOR_SEGURO_TEXTO (interfazContactos->texto.auxAgendarContacto);


    // ELEMENTOS

    DESTRUCTOR_SEGURO_RECTANGULO (interfazContactos->elementos.barraEscribirAgendarContacto);
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarSolicitudAmistad (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos)
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

    sprintf (bufferSolicitud, "%c|%s|%s", INDICE_AGENDARCONTACTO, aplicacion->usuario.nombre, interfazContactos->bufferAgendarContacto);
    printf ("Enviado: %s\n", bufferSolicitud);
    enviarSolicitudYRecibirRespuesta (aplicacion->sock, bufferSolicitud, bufferRespuesta);
    sscanf (bufferRespuesta, "%c", &estadoSolicitud);

    free (bufferSolicitud);
    free (bufferRespuesta);

    if (estadoSolicitud == INDICE_RESPUESTA_SOLICITUD_ACEPTADA)
        printf ("Le envio la solicitud de amistad.\n");
    else if (estadoSolicitud == INDICE_RESPUESTA_SOLICITUD_RECHAZADA)
        printf ("No se envio la solicitud de amistad.\n");
}

/** \brief Modificar las configuraciones de las habilitaciones, buffers y recursos graficos para adaptarlos a la interfaz de salas.
 *
 * Deshabilitar las habilitaciones y restablecer los buffers al inicio.
 * Modificar unicamente los recursos graficos de texto y/o elementos que se necesiten adaptar para cambiar a la interfaz de salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void cambiarInterfazASalas (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
    interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->bufferMensaje) = '\0';
    *(interfazContactos->bufferAgendarContacto) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirMensaje
    sfText_setString (recursosComunesContactosSalas->texto.auxEscribirMensaje, "");

    // nombreCambiarInterfaz
    sfText_setString (recursosComunesContactosSalas->texto.nombreCambiarInterfaz, "CONTACTOS");
    sfText_setPosition (recursosComunesContactosSalas->texto.nombreCambiarInterfaz, (sfVector2f){352 * ventana->escalaElementos.x, 600 * ventana->escalaElementos.y});

    // tituloInterfaz
    sfText_setString (recursosComunesContactosSalas->texto.tituloInterfaz, "SALAS");
    sfText_setPosition (recursosComunesContactosSalas->texto.tituloInterfaz, (sfVector2f){70 * ventana->escalaElementos.x, 45 * ventana->escalaElementos.y});


    // ELEMENTOS
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto de la interfaz de contactos.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazContactos_inicializarTexto (s_interfazContactosTexto *texto)
{
    texto->agendarContacto = sfText_create ();
    if (!texto->agendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto agendarContacto.\n");
        return ERROR_INICIALIZACION;
    }

    texto->auxAgendarContacto = sfText_create ();
    if (!texto->auxAgendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear texto auxAgendarContacto.\n");
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
static int interfazContactos_inicializarElementos (s_interfazContactosElementos *elementos)
{
    elementos->barraEscribirAgendarContacto = sfRectangleShape_create ();
    if (!elementos->barraEscribirAgendarContacto)
    {
        perror ("\nERROR - Interfaz de contactos, crear elemento barraEscribirAgendarContacto.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de texto de la interfaz de contactos.
 *
 * Configura todos los recursos graficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazContactos_configurarTexto (s_interfazContactosTexto *texto, const s_fuentes *fuentes)
{
    // agendarContacto
    sfText_setFont (texto->agendarContacto, fuentes->fuente1);
    sfText_setString (texto->agendarContacto, "+");
    sfText_setFillColor (texto->agendarContacto, sfColor_fromRGB (34, 48, 48));

    // auxAgregarContacto
    sfText_setFont (texto->auxAgendarContacto, fuentes->fuente1);
    sfText_setFillColor (texto->auxAgendarContacto, sfColor_fromRGB (40, 54, 54));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de contactos.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 *
 */
static void interfazContactos_configurarElementos (s_interfazContactosElementos *elementos)
{
    // barraEscribirAgendarContacto
    sfRectangleShape_setFillColor (elementos->barraEscribirAgendarContacto, sfColor_fromRGB (208, 208, 208));
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico de la interfaz de contactos.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazContactos_tamYPosVentanaTexto (s_interfazContactosTexto *texto, const s_ventana *ventana)
{
    // agendarContacto
    sfText_setPosition (texto->agendarContacto, (sfVector2f){220 * ventana->escalaElementos.x, 35 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->agendarContacto, 60 * ventana->escalaPixeles);

    // auxAgendarContacto
    sfText_setPosition (texto->auxAgendarContacto, (sfVector2f){802 * ventana->escalaElementos.x, 600 * ventana->escalaElementos.y});
    sfText_setCharacterSize (texto->auxAgendarContacto, 26 * ventana->escalaPixeles);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada elemento grafico de la interfaz de contactos.
 *
 * Establecer a todos los elementos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazContactos_tamYPosVentanaElementos (s_interfazContactosElementos *elementos, const s_ventana *ventana)
{
    // barraEscribirAgendarContacto
    sfRectangleShape_setPosition (elementos->barraEscribirAgendarContacto, (sfVector2f){800 * ventana->escalaElementos.x, 600 * ventana->escalaElementos.y});
    sfRectangleShape_setSize (elementos->barraEscribirAgendarContacto, (sfVector2f){280 * ventana->escalaElementos.x, 42 * ventana->escalaElementos.y});
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */


/** \brief Manejar el evento de click en la barra para escribir mensaje.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.barraEscribirMensaje))
    {
        recursosComunesContactosSalas->habilitaciones.escribirMensaje = HABILITAR_ESCRIBIR_MENSAJE;
        interfazContactos->habilitaciones.escribirAgendarContacto = DESHABILITAR_ESCRIBIR_AGENDAR_CONTACTO;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->texto.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){512.5 * ventana->escalaElementos.x + limiteTextoAux.width, 943 * ventana->escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    recursosComunesContactosSalas->habilitaciones.escribirMensaje = DESHABILITAR_ESCRIBIR_MENSAJE;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir un nombre para agendarlo como un nuevo contacto.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirAgendarContacto (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, interfazContactos->elementos.barraEscribirAgendarContacto))
    {
        interfazContactos->habilitaciones.escribirAgendarContacto = HABILITAR_ESCRIBIR_AGENDAR_CONTACTO;
        limiteTextoAux = sfText_getGlobalBounds (interfazContactos->texto.auxAgendarContacto);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){805.5 * ventana->escalaElementos.x + limiteTextoAux.width, 632 * ventana->escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    interfazContactos->habilitaciones.escribirAgendarContacto = DESHABILITAR_ESCRIBIR_AGENDAR_CONTACTO;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en abrir notificaciones.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickNotificaciones (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos)
{
    if (clickEnTexto (aplicacion->renderizado, recursosComunesContactosSalas->texto.notificaciones))
    {
        if (recursosComunesContactosSalas->habilitaciones.notificaciones == DESHABILITAR_NOTIFICACIONES)
            recursosComunesContactosSalas->habilitaciones.notificaciones = HABILITAR_NOTIFICACIONES;
        else
            recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
        interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;
        *(interfazContactos->bufferAgendarContacto) = '\0';
        sfText_setString (recursosComunesContactosSalas->texto.tituloVentanaEmergente, "NOTIFICACIONES");
        sfText_setPosition (recursosComunesContactosSalas->texto.tituloVentanaEmergente, (sfVector2f){840 * aplicacion->ventana.escalaElementos.x, 400 * aplicacion->ventana.escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en agendar un nuevo contacto.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickAgendarContacto (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos)
{
    if (clickEnTexto (aplicacion->renderizado, interfazContactos->texto.agendarContacto))
    {
        if (interfazContactos->habilitaciones.agendarContacto == DESHABILITAR_AGENDAR_CONTACTO)
            interfazContactos->habilitaciones.agendarContacto = HABILITAR_AGENDAR_CONTACTO;
        else
            interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;
        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
        sfText_setString (recursosComunesContactosSalas->texto.tituloVentanaEmergente, "AGENDAR CONTACTO");
        sfText_setPosition (recursosComunesContactosSalas->texto.tituloVentanaEmergente, (sfVector2f){830 * aplicacion->ventana.escalaElementos.x, 400 * aplicacion->ventana.escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en cerrar la ventana emergente.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos)
{
    if (clickEnTexto (renderizado, recursosComunesContactosSalas->texto.cerrarVentanaEmergente))
    {
        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
        interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;
        *(interfazContactos->bufferAgendarContacto) = '\0';
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la solapa para cambiar de interfaz.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickSolapaCambiarInterfaz (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos)
{
    if (clickEnRectangulo (aplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_SALAS;
        cambiarInterfazASalas (recursosComunesContactosSalas, interfazContactos, &(aplicacion->ventana));
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para cambiar a la interfaz de configuraciones.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazConfig (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos)
{
    if (clickEnTexto (aplicacion->renderizado, recursosComunesContactosSalas->texto.configuraciones))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_CONFIG;
        aplicacion->usuario.ultimaInterfazUtilizada = INTERFAZ_CONTACTOS;

        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;

        interfazContactos->habilitaciones.agendarContacto = DESHABILITAR_AGENDAR_CONTACTO;
        *(interfazContactos->bufferAgendarContacto) = '\0';

        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir un nombre para agendarlo como un nuevo contacto.
 *
 * Si se encuentra habilitada la escritura para agendar un nuevo contacto, se agrega el caracter al buffer que contiene el nombre del contacto, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirAgendarContacto (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazContactos *interfazContactos, const s_ventana *ventana, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (interfazContactos->habilitaciones.escribirAgendarContacto == HABILITAR_ESCRIBIR_AGENDAR_CONTACTO)
    {
        ingresarCaracterABuffer (interfazContactos->bufferAgendarContacto, MAX_NOMBRE_USUARIO - 1, eventoChar);
        sfText_setString (interfazContactos->texto.auxAgendarContacto, interfazContactos->bufferAgendarContacto);
        limiteTextoAux = sfText_getGlobalBounds (interfazContactos->texto.auxAgendarContacto);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){805.5 * ventana->escalaElementos.x + limiteTextoAux.width, 632 * ventana->escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de enviar solicitud de contacto.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEnterIntentarAgendarContacto (s_interfazContactos *interfazContactos, s_aplicacion *aplicacion)
{
    if ((interfazContactos->habilitaciones.agendarContacto == HABILITAR_ESCRIBIR_AGENDAR_CONTACTO) && (strlen (interfazContactos->bufferAgendarContacto) > 0))
    {
        intentarSolicitudAmistad (aplicacion, interfazContactos);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}





























