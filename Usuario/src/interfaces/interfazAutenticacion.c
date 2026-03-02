#include "../../include/interfaces/interfazAutenticacion.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static int intentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void desactivarInterfazAutenticacion (t_interfazAutenticacion *interfazAutenticacion);
static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos);
static void interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos);

static int interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos);
static int interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static void interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos);
static void interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos);
static void interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos);
static void interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickCambiarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);
static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);

static bool manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

static bool manejarPegarPortapapelesEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarPegarPortapapelesEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



void interfazAutenticacion_inicializarValoresNulos (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS

    interfazAutenticacion_inicializarValoresNulosTextos (&(interfazAutenticacion->textos));


    // ELEMENTOS

    interfazAutenticacion_inicializarValoresNulosElementos (&(interfazAutenticacion->elementos));
}

int interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion)
{
    // TEXTOS

    if (interfazAutenticacion_inicializarTextos (&(interfazAutenticacion->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazAutenticacion_inicializarElementos (&(interfazAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazAutenticacion->estadoFoco = IA_NINGUNO;


    // --------------- CONFIGURAR BUFFERS ---------------




    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazAutenticacion_configurarTextos (&(interfazAutenticacion->textos), fuentes);


    // ELEMENTOS

    interfazAutenticacion_configurarElementos (&(interfazAutenticacion->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazAutenticacion_tamYPosVentanaTextos (&(interfazAutenticacion->textos));


    // ELEMENTOS

    interfazAutenticacion_tamYPosVentanaElementos (&(interfazAutenticacion->elementos));
}

void interfazAutenticacion_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
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
            sfRenderWindow_setSize (contextoAplicacion->renderizado, (sfVector2u){500, 620});
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (manejarClickEscribirNombre (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickEscribirContrasenia (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickIntentarAutenticacion (contextoAplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickCambiarInterfazRegistro (contextoAplicacion, recursosComunesAutenticacionRegistro, interfazAutenticacion) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesAutenticacionRegistro, interfazAutenticacion);
            }
            break;


        case sfEvtTextEntered:
            if (evento.text.unicode < 128)
            {
                if (manejarEscribirNombre (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
                if (manejarEscribirContrasenia (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
            }
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (manejarEnterIntentarAutenticacion (contextoAplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirNombre (recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirContrasenia (recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;

            break;


        default:
            break;
        }
    }
}

void interfazAutenticacion_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- PUNTO DE INSERCION ---------------

    if ((recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA))
        actualizarPuntoInsercion (&(recursosComunesAutenticacionRegistro->puntoInsercion));
    else if (puntoInsercionHabilitado (&(recursosComunesAutenticacionRegistro->puntoInsercion)))
        resetearPuntoInsercion (&(recursosComunesAutenticacionRegistro->puntoInsercion));
}

void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazAutenticacion *interfazAutenticacion)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(recursosComunesAutenticacionRegistro->elementos));
    interfazAutenticacion_renderizarElementos (renderizado, &(interfazAutenticacion->elementos));


    // TEXTOS

    recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(recursosComunesAutenticacionRegistro->textos));
    interfazAutenticacion_renderizarTextos (renderizado, &(interfazAutenticacion->textos));


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (puntoInsercionHabilitado (&(recursosComunesAutenticacionRegistro->puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);


    sfRenderWindow_display (renderizado);
}

void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazAutenticacion_liberarTextos (&(interfazAutenticacion->textos));


    // ELEMENTOS

    interfazAutenticacion_liberarElementos (&(interfazAutenticacion->elementos));
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/** \brief Intentar autenticar usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_AUTENTICACION|nombre|contrasenia
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si se ejecuto con exito, guarda el ID del usuario y selecciona la interfaz de contactos como menu principal.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EXITO si se pudo enviar correctamente, ERROR_INICIALIZACION en caso contrario.
 */
static int intentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];
    char estadoRespuesta;
    int id;

    snprintf (bufferSolicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", SOLICITUD_AUTENTICACION, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
    enviarSolicitudYRecibirRespuesta (contextoAplicacion->sock, bufferSolicitud, bufferRespuesta, MAX_BUFFER_RESPUESTA);
    sscanf (bufferRespuesta, "%c|%d", &estadoRespuesta, &id);

    if (estadoRespuesta == RESPUESTA_EXITO)
    {
        contextoAplicacion->usuario.id = id;
        contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
        strcpy (contextoAplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
        return EXITO;
    }
    else
    {
        if (estadoRespuesta == RESPUESTA_ERROR_CREDENCIALES)
        {
            printf ("Nombre o contrasenia incorrectos.\n");
            sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Nombre o contraseña incorrectos");
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
        }
        else
            printf ("Error servidor.\n");
    }

    return ERROR_INICIALIZACION;
}

/** \brief Analizar si se habilita, o no, el ingreso del usuario.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((strlen (recursosComunesAutenticacionRegistro->bufferNombre) > 0) &&
        (strlen (recursosComunesAutenticacionRegistro->bufferContrasenia) > 0))
        recursosComunesAutenticacionRegistro->ingreso = HABILITADO;
    else
        recursosComunesAutenticacionRegistro->ingreso = DESHABILITADO;
}

/** \brief Desactivar la interfaz de autenticacion para cambiar de interfaz.
 *
 * Modificar los estados de foco y los recursos graficos de texto y/o elementos que se necesiten desactivar para cambiar de interfaz.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
static void desactivarInterfazAutenticacion (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

/** \brief Deshabilitar los estados de foco de los recursos comunes entre las interfaces de autenticacion y registro y de la interfaz de autenticacion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos de la interfaz de autenticacion.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 */
static void interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos)
{

}

/** \brief Establecer en NULL a todos los elementos graficos de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 */
static void interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos)
{

}

/** \brief Inicializar los recursos graficos de texto de la interfaz de autenticacion.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos)
{


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos de la interfaz de autenticacion.
 *
 * Crea todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos)
{


    return EXITO;
}

/** \brief Configurar los recursos graficos de texto de la interfaz de autenticacion.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{

}

/** \brief Configurar los recursos graficos de elementos de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos)
{

}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos)
{

}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos)
{

}

/** \brief Renderizar los recursos graficos de textos de la interfaz de autenticacion.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos)
{

}

/** \brief Renderizar los recursos graficos de elementos de la interfaz de autenticacion.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos)
{

}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de autenticacion.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos)
{

}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos)
{

}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en la barra para escribir el nombre de usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 208});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir la contrasenia del usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 343});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para intentar autenticar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    intentarAutenticacion (contextoAplicacion, recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el texto para cambiar a la interfaz de registro.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    sfEvent evento;

    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_REGISTRO;
    desactivarInterfazAutenticacion (interfazAutenticacion);
    activarInterfazRegistro (recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de escribir el nombre de usuario.
 *
 * Si se encuentra el foco en escribir nombre, intenta agregar el caracter al buffer del nombre.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO, eventoChar) == CARACTER_INVALIDO)
        return EVENTO_NO_MANEJADO;

    estadoHabilitarIngreso (recursosComunesAutenticacionRegistro);
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 208});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de escribir la contrasenia del usuario.
 *
 * Si se encuentra el foco en escribir contrasenia, intenta agregar el caracter al buffer de la contrasenia.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO, eventoChar) == CARACTER_INVALIDO)
        return EVENTO_NO_MANEJADO;

    estadoHabilitarIngreso (recursosComunesAutenticacionRegistro);
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 343});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de presionado de la tecla "enter" para intentar autenticar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if ((recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    intentarAutenticacion (contextoAplicacion, recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de pegar desde el portapapeles al buffer de escribir nombre.
 *
 * Si se encuentra el foco en escribir nombre, intenta agregar el caracter al buffer del nombre.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarPegarPortapapelesEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO))
    {
        estadoHabilitarIngreso (recursosComunesAutenticacionRegistro);
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 208});
    }

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de pegar desde el portapapeles al buffer de escribir contrasenia.
 *
 * Si se encuentra el foco en escribir contrasenia, intenta agregar el caracter al buffer de la contrasenia.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarPegarPortapapelesEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO))
    {
        estadoHabilitarIngreso (recursosComunesAutenticacionRegistro);
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 343});
    }

    return EVENTO_MANEJADO;
}



































