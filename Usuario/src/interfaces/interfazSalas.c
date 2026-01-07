#include "../../include/interfaces/interfazSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void cambiarInterfazAContactos (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas, const s_ventana *ventana);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */


static void interfazSalas_inicializarValoresNulosTextos (s_interfazSalasTextos *textos);
static void interfazSalas_inicializarValoresNulosElementos (s_interfazSalasElementos *elementos);

static int interfazSalas_inicializarTextos (s_interfazSalasTextos *textos);
static int interfazSalas_inicializarElementos (s_interfazSalasElementos *elementos);

static void interfazSalas_configurarTextos (s_interfazSalasTextos *textos, const s_fuentes *fuentes);
static void interfazSalas_configurarElementos (s_interfazSalasElementos *elementos);

static void interfazSalas_tamYPosVentanaTextos (s_interfazSalasTextos *textos, const s_ventana *ventana);
static void interfazSalas_tamYPosVentanaElementos (s_interfazSalasElementos *elementos, const s_ventana *ventana);

static void interfazSalas_renderizarVistaUI (s_aplicacion *aplicacion, const s_interfazSalas *interfazSalas, const s_recursosComunesContactosSalas *recursosComunesContactosSalas);
static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const s_interfazSalasTextos *textos);
static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const s_interfazSalasElementos *elementos);

static void interfazSalas_liberarTextos (s_interfazSalasTextos *textos);
static void interfazSalas_liberarElementos (s_interfazSalasElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana);
static bool manejarClickNotificaciones (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickSolapaCambiarInterfaz (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas);
static bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickCambiarInterfazConfig (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazSalas_inicializar (s_interfazSalas *interfazSalas)
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

void interfazSalas_configurar (s_interfazSalas *interfazSalas, const s_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------



    // --------------- CONFIGURAR BUFFERS ---------------



    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_configurarTextos (&(interfazSalas->textos), fuentes);


    // ELEMENTOS

    interfazSalas_configurarElementos (&(interfazSalas->elementos));
}

void interfazSalas_tamYPosVentana (s_interfazSalas *interfazSalas, const s_ventana *ventana)
{
    // --------------- TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazSalas_tamYPosVentanaTextos (&(interfazSalas->textos), ventana);


    // ELEMENTOS

    interfazSalas_tamYPosVentanaElementos (&(interfazSalas->elementos), ventana);
}

void interfazSalas_accion (s_aplicacion *aplicacion, s_interfazSalas *interfazSalas, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfEvent evento;


    sfRenderWindow_pollEvent (aplicacion->renderizado, &evento);
    switch (evento.type)
    {

    case sfEvtClosed:
        sfRenderWindow_close (aplicacion->renderizado);
        break;


    case sfEvtResized:
        manejarRedimensionamientoVentanaContactosSalas (aplicacion, recursosComunesContactosSalas, evento);
        interfazSalas_tamYPosVentana (interfazSalas, &(aplicacion->ventana));
        break;


    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (manejarClickEscribirMensaje (aplicacion->renderizado, recursosComunesContactosSalas, &(aplicacion->ventana)) == EVENTO_MANEJADO) break;
            if (manejarClickNotificaciones (aplicacion, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            if (manejarClickCerrarVentanaEmergente (aplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            if (manejarClickSolapaCambiarInterfaz (aplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
            if (manejarClickAreaMensajes (aplicacion->renderizado, recursosComunesContactosSalas) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazConfig (aplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtTextEntered:
        if (evento.text.unicode < 128)
        {
            if (manejarEscribirMensaje (recursosComunesContactosSalas, &(aplicacion->ventana), evento) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtKeyPressed:
        if (evento.key.code == sfKeyEnter)
        {
            if (manejarEnterEnviarMensaje (recursosComunesContactosSalas, aplicacion) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtMouseWheelScrolled:
        if (manejarScrollAreaMensajes (recursosComunesContactosSalas, evento) == EVENTO_MANEJADO) break;
        break;


    default:
        break;
    }
}

void interfazSalas_actualizar (s_aplicacion *aplicacion, s_interfazSalas *interfazSalas, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
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
        case INDICE_RESPUESTA_AGENDAR_CONTACTO:
            agregarNotificacion (&(aplicacion->listaNotificaciones), bufferRespuesta, aplicacion->ventana, aplicacion->mensajes.fuentes);
            break;

        case INDICE_RESPUESTA_MENSAJE:
            break;
        }
    }
    free (bufferRespuesta);


    // --------------- PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->habilitaciones.escribirMensaje == HABILITAR_ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion), &(recursosComunesContactosSalas->habilitaciones.contadorPuntoInsercion));
    else
        reiniciarPuntoInsercion (&(recursosComunesContactosSalas->habilitaciones.puntoInsercion), &(recursosComunesContactosSalas->habilitaciones.contadorPuntoInsercion));
}

void interfazSalas_renderizar (s_aplicacion *aplicacion, const s_interfazSalas *interfazSalas, const s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfRenderWindow_clear (aplicacion->renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------

    renderizarVistaMensajes (aplicacion, recursosComunesContactosSalas);


    // --------------- RENDERIZAR VISTA DE UI ---------------

    interfazSalas_renderizarVistaUI (aplicacion, interfazSalas, recursosComunesContactosSalas);


    sfRenderWindow_display (aplicacion->renderizado);
}

void interfazSalas_liberar (s_interfazSalas *interfazSalas)
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
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void cambiarInterfazAContactos (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas, const s_ventana *ventana)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITAR_AREA_MENSAJES;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->bufferMensaje) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirMensaje
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");

    // nombreCambiarInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.nombreCambiarInterfaz, "SALAS");
    sfText_setPosition (recursosComunesContactosSalas->textos.nombreCambiarInterfaz, (sfVector2f){352 * ventana->escalaElementos.x, 574 * ventana->escalaElementos.y});

    // tituloInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.tituloInterfaz, "CONTACTOS");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloInterfaz, (sfVector2f){62 * ventana->escalaElementos.x, 45 * ventana->escalaElementos.y});


    // ELEMENTOS

}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 */
static void interfazSalas_inicializarValoresNulosTextos (s_interfazSalasTextos *textos)
{

}

/** \brief Establecer en NULL a todos los elementos graficos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 */
static void interfazSalas_inicializarValoresNulosElementos (s_interfazSalasElementos *elementos)
{

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
static int interfazSalas_inicializarTextos (s_interfazSalasTextos *textos)
{



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
static int interfazSalas_inicializarElementos (s_interfazSalasElementos *elementos)
{



    return EXITO;
}

/** \brief Configurar los recursos graficos de textos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazSalas_configurarTextos (s_interfazSalasTextos *textos, const s_fuentes *fuentes)
{

}

/** \brief Configurar los recursos graficos de elementos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_configurarElementos (s_interfazSalasElementos *elementos)
{

}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazSalas_tamYPosVentanaTextos (s_interfazSalasTextos *textos, const s_ventana *ventana)
{

}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
static void interfazSalas_tamYPosVentanaElementos (s_interfazSalasElementos *elementos, const s_ventana *ventana)
{

}

/** \brief Renderizar la vista de UI de la interfaz de salas.
 *
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de salas y de los recursos comunes (compartidos) entre las
 * interfaces de contactos y salas. Ademas, si se encuentran habilitados, renderiza la ventana emergente de notificaciones y el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
static void interfazSalas_renderizarVistaUI (s_aplicacion *aplicacion, const s_interfazSalas *interfazSalas, const s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- ESTABLECER VISTA DE UI ---------------

    sfRenderWindow_setView (aplicacion->renderizado, recursosComunesContactosSalas->vistas.UI);


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesContactosSalas_renderizarElementos (aplicacion->renderizado, &(recursosComunesContactosSalas->elementos));
    interfazSalas_renderizarElementos (aplicacion->renderizado, &(interfazSalas->elementos));


    // TEXTOS

    recursosComunesContactosSalas_renderizarTextos (aplicacion->renderizado, &(recursosComunesContactosSalas->textos));
    interfazSalas_renderizarTextos (aplicacion->renderizado, &(interfazSalas->textos));


    // --------------- RENDERIZAR NOTIFICACIONES ---------------

    renderizarNotificaciones (aplicacion, recursosComunesContactosSalas);


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
        sfRenderWindow_drawRectangleShape (aplicacion->renderizado, recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}

/** \brief Renderizar los recursos graficos de textos de la interfaz de salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const s_interfazSalasTextos *textos)
{

}

/** \brief Renderizar los recursos graficos de elementos de la interfaz de salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 *
 */
static void interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const s_interfazSalasElementos *elementos)
{

}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de salas.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de salas.
 */
static void interfazSalas_liberarTextos (s_interfazSalasTextos *textos)
{

}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de salas.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de salas.
 */
static void interfazSalas_liberarElementos (s_interfazSalasElementos *elementos)
{

}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en la barra para escribir mensaje.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.barraEscribirMensaje))
    {
        recursosComunesContactosSalas->habilitaciones.escribirMensaje = HABILITAR_ESCRIBIR_MENSAJE;
        recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITAR_AREA_MENSAJES;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){(512.5 * (ventana->escalaElementos.x)) + limiteTextoAux.width, 943 * (ventana->escalaElementos.y)});
        return EVENTO_MANEJADO;
    }
    recursosComunesContactosSalas->habilitaciones.escribirMensaje = DESHABILITAR_ESCRIBIR_MENSAJE;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en abrir notificaciones.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickNotificaciones (const s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (clickEnTexto (aplicacion->renderizado, recursosComunesContactosSalas->textos.notificaciones))
    {
        if (recursosComunesContactosSalas->habilitaciones.notificaciones == DESHABILITAR_NOTIFICACIONES)
            recursosComunesContactosSalas->habilitaciones.notificaciones = HABILITAR_NOTIFICACIONES;
        else
            recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
        recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITAR_AREA_MENSAJES;
        sfText_setString (recursosComunesContactosSalas->textos.tituloVentanaEmergente, "NOTIFICACIONES");
        sfText_setPosition (recursosComunesContactosSalas->textos.tituloVentanaEmergente, (sfVector2f){840 * aplicacion->ventana.escalaElementos.x, 400 * aplicacion->ventana.escalaElementos.y});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en cerrar la ventana emergente.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (clickEnTexto (renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente))
    {
        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;
        recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITAR_AREA_MENSAJES;
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la solapa para cambiar de interfaz.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickSolapaCambiarInterfaz (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas)
{
    if (clickEnRectangulo (aplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
        cambiarInterfazAContactos (recursosComunesContactosSalas, interfazSalas, &(aplicacion->ventana));
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

static bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, s_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.areaMensajes))
    {
        recursosComunesContactosSalas->habilitaciones.areaMensajes = HABILITAR_AREA_MENSAJES;
        return EVENTO_MANEJADO;
    }
    recursosComunesContactosSalas->habilitaciones.areaMensajes = DESHABILITAR_AREA_MENSAJES;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para cambiar a la interfaz de configuraciones.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazConfig (s_aplicacion *aplicacion, s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_interfazSalas *interfazSalas)
{
    if (clickEnTexto (aplicacion->renderizado, recursosComunesContactosSalas->textos.configuraciones))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_CONFIG;
        aplicacion->usuario.ultimaInterfazUtilizada = INTERFAZ_SALAS;

        recursosComunesContactosSalas->habilitaciones.notificaciones = DESHABILITAR_NOTIFICACIONES;

        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}










































