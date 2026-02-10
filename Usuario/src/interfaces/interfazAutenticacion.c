#include "../../include/interfaces/interfazAutenticacion.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static int intentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void cambiarInterfazARegistro (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos);
static void interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos);

static int interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos);
static int interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos);

static void interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_fuentes *fuentes);
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
static bool manejarClickIntentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickCambiarInterfazARegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);

static bool manejarEnterIntentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTOS

    interfazAutenticacion_inicializarValoresNulosTextos (&(interfazAutenticacion->textos));


    // ELEMENTOS

    interfazAutenticacion_inicializarValoresNulosElementos (&(interfazAutenticacion->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTOS

    if (interfazAutenticacion_inicializarTextos (&(interfazAutenticacion->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazAutenticacion_inicializarElementos (&(interfazAutenticacion->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, const t_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------




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

void interfazAutenticacion_accion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    sfEvent evento;


    sfRenderWindow_pollEvent (aplicacion->renderizado, &evento);
    switch (evento.type)
    {

    case sfEvtClosed:
        sfRenderWindow_close (aplicacion->renderizado);
        break;


    case sfEvtResized:
        sfRenderWindow_setSize (aplicacion->renderizado, (sfVector2u){500, 620});
        break;


    case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (manejarClickEscribirNombre (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirContrasenia (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickIntentarAutenticacion (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazARegistro (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
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

void interfazAutenticacion_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
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

void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazAutenticacion *interfazAutenticacion)
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

    if (recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
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
 * INDICE_SOLICITUD_AUTENTICACION|nombre|contrasenia
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si se ejecuto con exito, guarda el ID del usuario y selecciona la interfaz de contactos como menu principal.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se pudo enviar correctamente, ERROR_INICIALIZACION en caso contrario.
 */
static int intentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];
    char estadoRespuesta;
    int id;

    snprintf (bufferSolicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", INDICE_SOLICITUD_AUTENTICACION, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
    enviarSolicitudYRecibirRespuesta (aplicacion->sock, bufferSolicitud, bufferRespuesta, MAX_BUFFER_RESPUESTA);
    sscanf (bufferRespuesta, "%c|%d", &estadoRespuesta, &id);

    if (estadoRespuesta == INDICE_RESPUESTA_EXITO)
    {
        aplicacion->usuario.id = id;
        aplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
        strcpy (aplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
        return EXITO;
    }
    else
    {
        if (estadoRespuesta == INDICE_RESPUESTA_ERROR_CREDENCIALES)
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

/** \brief Modificar las configuraciones de los recursos graficos para adaptarlos a la interfaz de registro.
 *
 * Modificar unicamente los recursos graficos de texto o elementos que se necesiten adaptar para cambiar a la interfaz de registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
static void cambiarInterfazARegistro (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirContrasenia
    sfText_setString (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, "");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, (sfVector2f){42, 295});

    // auxEscribirNombre
    sfText_setString (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, "");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, (sfVector2f){42, 170});

    // ingresarContrasenia
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.ingresarContrasenia, (sfVector2f){35, 225});

    // ingresarNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.ingresarNombre, (sfVector2f){35, 100});

    // ingresoIncorrecto
    sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "");

    // textoBotonIngresar
    sfText_setString (recursosComunesAutenticacionRegistro->textos.textoBotonIngresar, "REGISTRAR");
    centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.textoBotonIngresar, 180, 452, 140, 35);

    // textoCambiarInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz, "¿Ya tenés cuenta? Iniciá sesión acá");
    centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz, 0, 530, 500, 90);

    // tituloInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->textos.tituloInterfaz, "CREAR CUENTA");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.tituloInterfaz, (sfVector2f){130, 25});


    // ELEMENTOS

    // barraEscribirContrasenia
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia, (sfVector2f){35, 295});

    // barraEscribirNombre
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre, (sfVector2f){35, 170});

    // botonIngresar
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonIngresar, (sfVector2f){180, 452});

    // subrayadoTitulo
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo, (sfVector2f){130, 75});
    sfRectangleShape_setSize (recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo, (sfVector2f){240, 2.5});
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
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_fuentes *fuentes)
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
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
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
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 *
 */
static void interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos)
{

}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de autenticacion.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de autenticacion.
 */
static void interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos)
{

}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de autenticacion.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de autenticacion.
 */
static void interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos)
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
static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = HABILITAR_ESCRIBIR_NOMBRE;
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 208});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = DESHABILITAR_ESCRIBIR_NOMBRE;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir la contrasenia del usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = HABILITAR_ESCRIBIR_CONTRASENIA;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 343});
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
static bool manejarClickIntentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (recursosComunesAutenticacionRegistro->habilitaciones.ingresar != HABILITAR_INGRESAR)
        return EVENTO_NO_MANEJADO;

    if (!clickEnRectangulo (aplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    intentarAutenticacion (aplicacion, recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de click en el texto para cambiar a la interfaz de registro.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazARegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (!clickEnTexto (aplicacion->renderizado, recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    aplicacion->usuario.interfazActual = INTERFAZ_REGISTRO;
    cambiarInterfazARegistro (recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
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
static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre != HABILITAR_ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO, eventoChar);
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 208});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de escribir la contrasenia del usuario.
 *
 * Si se encuentra habilitado el escribir mensaje, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia != HABILITAR_ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO, eventoChar);
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 343});

    return EVENTO_MANEJADO;
}

/** \brief Manejar el evento de presionado de la tecla "enter" para intentar autenticar.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEnterIntentarAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (recursosComunesAutenticacionRegistro->habilitaciones.ingresar != HABILITAR_INGRESAR)
        return EVENTO_NO_MANEJADO;

    if ((recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre != HABILITAR_ESCRIBIR_NOMBRE) &&
        (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia != HABILITAR_ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    intentarAutenticacion (aplicacion, recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}







































