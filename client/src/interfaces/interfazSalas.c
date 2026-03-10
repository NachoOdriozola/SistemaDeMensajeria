#include "../../include/interfaces/interfazSalas.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void desactivarInterfazSalas (t_interfazSalas *interfazSalas);
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactoSalas, t_interfazSalas *interfazSalas);



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



//static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
//static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
static bool manejarClickCambiarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);
//static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



void interfazSalas_inicializarValoresNulos (t_interfazSalas *interfazSalas)
{
    // TEXTOS

    interfazSalas_inicializarValoresNulosTextos (&(interfazSalas->textos));


    // ELEMENTOS

    interfazSalas_inicializarValoresNulosElementos (&(interfazSalas->elementos));
}

int interfazSalas_inicializar (t_interfazSalas *interfazSalas)
{
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
    // --------------- CONFIGURAR FOCO ---------------

    interfazSalas->estadoFoco = IS_NINGUNO;


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
                if (manejarClickCambiarInterfazContactos (contextoAplicacion, recursosComunesContactosSalas, interfazSalas) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesContactosSalas, interfazSalas);
            }
            break;


        default:
            break;
        }
    }
}

void interfazSalas_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    // --------------- PUNTO DE INSERCION ---------------

    if (recursosComunesContactosSalas->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
    else if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
        resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));
}

void interfazSalas_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------

    //renderizarVistaMensajes (renderizado, recursosComunesContactosSalas);


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



/** \brief Desactivar la interfaz de salas para cambiar de interfaz.
 *
 * Modificar los estados de foco y los recursos graficos de texto y/o elementos que se necesiten desactivar para cambiar de interfaz.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
static void desactivarInterfazSalas (t_interfazSalas *interfazSalas)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazSalas->estadoFoco = IS_NINGUNO;
}

/** \brief Deshabilitar los estados de foco de los recursos comunes entre las interfaces de contactos y salas y de la interfaz de salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
static void deshabilitarFocos (t_recursosComunesContactosSalas *recursosComunesContactoSalas, t_interfazSalas *interfazSalas)
{
    recursosComunesContactoSalas->estadoFoco = RCCS_NINGUNO;
    interfazSalas->estadoFoco = IS_NINGUNO;
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
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
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


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (puntoInsercionHabilitado (&(recursosComunesContactosSalas->puntoInsercion)))
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



/** \brief Manejar el evento de click en abrir notificaciones.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
/*
static bool manejarClickNotificaciones (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.notificaciones))
        return EVENTO_NO_MANEJADO;

    if (recursosComunesContactosSalas->estadoFoco == RCCS_NINGUNO)
        recursosComunesContactosSalas->estadoFoco = NOTIFICACIONES;
    else
        recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;

    sfText_setString (recursosComunesContactosSalas->textos.tituloVentanaEmergente, "NOTIFICACIONES");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloVentanaEmergente, (sfVector2f){840, 400});

    return EVENTO_MANEJADO;
}
*/

/** \brief Manejar el evento de click en cerrar la ventana emergente.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarClickCerrarVentanaEmergente (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnTexto (renderizado, recursosComunesContactosSalas->textos.cerrarVentanaEmergente))
        return EVENTO_NO_MANEJADO;

    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;

    return EVENTO_MANEJADO;
}
*/

/** \brief Manejar el evento de click en la solapa para cambiar de interfaz.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    desactivarInterfazSalas (interfazSalas);
    activarInterfazContactos (recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para cambiar a la interfaz de configuraciones.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
 /*
static bool manejarClickCambiarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas)
{
    sfEvent evento;

    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesContactosSalas->textos.configuraciones))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONFIG;
    desactivarInterfazSalas (interfazSalas);
    activarInterfazContactos (recursosComunesContactosSalas);
    deshabilitarFocos (recursosComunesContactosSalas, interfazSalas);

    return EVENTO_MANEJADO;
}
*/









































