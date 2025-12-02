#include "../../include/interfaces/interfazAutenticacion.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static void cambiarInterfazARegistro (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int interfazAutenticacion_inicializarTexto (s_interfazAutenticacionTexto *texto);
static int interfazAutenticacion_inicializarElementos (s_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_configurarTexto (s_interfazAutenticacionTexto *texto, const s_fuentes *fuentes);
static void interfazAutenticacion_configurarElementos (s_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_tamYPosVentanaTexto (s_interfazAutenticacionTexto *texto);
static void interfazAutenticacion_tamYPosVentanaElementos (s_interfazAutenticacionElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */


static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickIntentarAutenticar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickCambiarInterfazRegistro (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_interfazAutenticacion *interfazAutenticacion);
static bool manejarEscribirNombre (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEnterIntentarAutenticacion (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazAutenticacion_inicializar (s_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    interfazAutenticacion->texto.textoRegistrarUsuario = NULL;


    // ELEMENTOS



    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (interfazAutenticacion_inicializarTexto (&(interfazAutenticacion->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazAutenticacion_inicializarElementos (&(interfazAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazAutenticacion_configurar (s_interfazAutenticacion *interfazAutenticacion, const s_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------




    // --------------- CONFIGURAR BUFFERS ---------------




    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazAutenticacion_configurarTexto (&(interfazAutenticacion->texto), fuentes);


    // ELEMENTOS

    interfazAutenticacion_configurarElementos (&(interfazAutenticacion->elementos));


    // --------------- TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazAutenticacion_tamYPosVentanaTexto (&(interfazAutenticacion->texto));


    // ELEMENTOS

    interfazAutenticacion_tamYPosVentanaElementos (&(interfazAutenticacion->elementos));
}

void interfazAutenticacion_accion (s_aplicacion *aplicacion, const s_interfazAutenticacion *interfazAutenticacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfEvent evento;


    sfRenderWindow_pollEvent (aplicacion->renderizado, &evento);
    switch (evento.type)
    {

    case sfEvtClosed:
        aplicacion->aplicacionEjecutandose = DETENER_APLICACION;
        break;


    case sfEvtResized:
        sfRenderWindow_setSize (aplicacion->renderizado, (sfVector2u){560, 660});
        break;


    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (manejarClickEscribirNombre (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirContrasenia (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickIntentarAutenticar (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazRegistro (aplicacion, recursosComunesAutenticacionRegistro, interfazAutenticacion) == EVENTO_MANEJADO) break;
            if (manejarClickGuardarAutenticacion (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
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
        {
            if (manejarEnterIntentarAutenticacion (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
        }
        break;


    default:
        break;
    }
}

void interfazAutenticacion_actualizar (s_interfazAutenticacion *interfazAutenticacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    int largoBufferEscribirNombre, largoBufferEscribirContrasenia;

    largoBufferEscribirNombre = strlen (recursosComunesAutenticacionRegistro->bufferNombre);
    largoBufferEscribirContrasenia = strlen (recursosComunesAutenticacionRegistro->bufferContrasenia);


    if ((largoBufferEscribirNombre > 0) && (largoBufferEscribirContrasenia > 0))
        recursosComunesAutenticacionRegistro->habilitaciones.ingresar = HABILITAR_INGRESAR;
    else
        recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;


    // --------------- PUNTO DE INSERCION ---------------

    if ((recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE) ||
        (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA))
        actualizarPuntoInsercion (&(recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion), &(recursosComunesAutenticacionRegistro->habilitaciones.contadorPuntoInsercion));
    else
        reiniciarPuntoInsercion (&(recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion), &(recursosComunesAutenticacionRegistro->habilitaciones.contadorPuntoInsercion));
}

void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const s_interfazAutenticacion *interfazAutenticacion, const s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(recursosComunesAutenticacionRegistro->elementos));


    // TEXTO

    recursosComunesAutenticacionRegistro_renderizarTexto (renderizado, &(recursosComunesAutenticacionRegistro->texto));
    sfRenderWindow_drawText (renderizado, interfazAutenticacion->texto.textoRegistrarUsuario, NULL);


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);


    sfRenderWindow_display (renderizado);
}

void interfazAutenticacion_liberar (s_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO


    DESTRUCTOR_SEGURO_TEXTO (interfazAutenticacion->texto.textoRegistrarUsuario);


    // ELEMENTOS


}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarIngreso (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    char *bufferSolicitud, *bufferRespuesta;
    char estadoSolicitud;
    int id;

    bufferSolicitud = malloc (MAX_BUFFER_SOLICITUD);
    if (!bufferSolicitud)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }
    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        free (bufferSolicitud);
        perror ("ERROR - Sin memoria.\n");
        return;
    }

    sprintf (bufferSolicitud, "%c|%s|%s", INDICE_AUTENTICACION, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
    enviarSolicitudYRecibirRespuesta (aplicacion->sock, bufferSolicitud, bufferRespuesta);
    sscanf (bufferRespuesta, "%c|%d", &estadoSolicitud, &id);

    free (bufferSolicitud);
    free (bufferRespuesta);

    if (estadoSolicitud == INDICE_RESPUESTA_SOLICITUD_ACEPTADA)
    {
        aplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
        aplicacion->usuario.id = id;
        strcpy (aplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
        if (recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion == HABILITAR_GUARDAR_AUTENTICACION)
            guardarDatosEnArchivo (aplicacion->usuario.id, recursosComunesAutenticacionRegistro->bufferNombre);
    }
    else
        printf ("Usuario o contrasenia incorrectos.\n");
}

/** \brief Modificar las configuraciones de los recursos graficos para adaptarlos a la interfaz de registro.
 *
 * Modificar unicamente los recursos graficos de texto o elementos que se necesiten adaptar para cambiar a la interfaz de registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
static void cambiarInterfazARegistro (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirContrasenia
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia, (sfVector2f){64, 329});

    // auxEscribirNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre, (sfVector2f){64, 173});

    // auxGuardarAutenticacion
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, (sfVector2f){415, 378});

    // ingresarNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.ingresarNombre, (sfVector2f){55, 90});

    // ingresoIncorrecto
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.ingresoIncorrecto, (sfVector2f){55, 400});

    // guardarAutenticacion
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.guardarAutenticacion, (sfVector2f){55, 371});

    // textoBotonIngresar
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.textoBotonIngresar, (sfVector2f){226, 451});

    // tituloInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->texto.tituloInterfaz, "REGISTRAR");
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.tituloInterfaz, (sfVector2f){196, 25});


    // ELEMENTOS

    // barraEscribirContrasenia
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia, (sfVector2f){55, 331});

    // barraEscribirNombre
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre, (sfVector2f){55, 175});

    // botonGuardarAutenticacion
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonGuardarAutenticacion, (sfVector2f){406, 382});

    // botonIngresar
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonIngresar, (sfVector2f){200, 452});
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto de la interfaz de autenticacion.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazAutenticacion_inicializarTexto (s_interfazAutenticacionTexto *texto)
{
    texto->textoRegistrarUsuario = sfText_create ();
    if (!texto->textoRegistrarUsuario)
    {
        perror ("\nERROR - Interfaz de autenticacion, crear texto textoRegistrarUsuario.\n");
        return ERROR_INICIALIZACION;
    }


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
static int interfazAutenticacion_inicializarElementos (s_interfazAutenticacionElementos *elementos)
{



    return EXITO;
}

/** \brief Configurar los recursos graficos de texto de la interfaz de autenticacion.
 *
 * Configura todos los recursos graficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazAutenticacion_configurarTexto (s_interfazAutenticacionTexto *texto, const s_fuentes *fuentes)
{
    // textoRegistrarUsuario
    sfText_setFont (texto->textoRegistrarUsuario, fuentes->fuente1);
    sfText_setString (texto->textoRegistrarUsuario, "¿No tenes usuario? Registrate aca.");
    sfText_setColor (texto->textoRegistrarUsuario, sfColor_fromRGB (40, 54, 54));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de autenticacion.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_configurarElementos (s_interfazAutenticacionElementos *elementos)
{

}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico de la interfaz de autenticacion.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_tamYPosVentanaTexto (s_interfazAutenticacionTexto *texto)
{
    // textoRegistrarUsuario
    sfText_setPosition (texto->textoRegistrarUsuario, (sfVector2f){126, 490});
    sfText_setCharacterSize (texto->textoRegistrarUsuario, 26);
    sfText_setLetterSpacing (texto->textoRegistrarUsuario, 1.3);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada elemento grafico de la interfaz de autenticacion.
 *
 * Establecer a todos los elementos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_tamYPosVentanaElementos (s_interfazAutenticacionElementos *elementos)
{

}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en la barra para escribir el nombre de usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = HABILITAR_ESCRIBIR_NOMBRE;
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 196.5});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = DESHABILITAR_ESCRIBIR_NOMBRE;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir la contrasenia de usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = HABILITAR_ESCRIBIR_CONTRASENIA;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 291.5});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para intentar autenticar.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickIntentarAutenticar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) && (clickEnRectangulo (aplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar)))
    {
        intentarIngreso (aplicacion, recursosComunesAutenticacionRegistro);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el texto para cambiar a la interfaz de registro.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazRegistro (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_interfazAutenticacion *interfazAutenticacion)
{
    if (clickEnTexto (aplicacion->renderizado, interfazAutenticacion->texto.textoRegistrarUsuario))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_REGISTRO;
        cambiarInterfazARegistro (recursosComunesAutenticacionRegistro);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir el nombre de usuario.
 *
 * Si se encuentra habilitado el escribir mensaje, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirNombre (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE)
    {
        ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferNombre, MAX_INGRESO_NOMBRE, eventoChar);
        sfText_setString (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 196.5});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir la contrasenia de usuario.
 *
 * Si se encuentra habilitado el escribir mensaje, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirContrasenia (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA)
    {
        ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_INGRESO_NOMBRE, eventoChar);
        sfText_setString (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 291.5});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de presionado de la tecla "enter" para intentar autenticar.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEnterIntentarAutenticacion (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) &&
        ((recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE) || (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA)))
    {
        intentarIngreso (aplicacion, recursosComunesAutenticacionRegistro);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}







































