#include "../../include/interfaces/interfazRegistro.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */


static void cambiarInterfazAAutenticacion (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);


/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int interfazRegistro_inicializarTexto (s_interfazRegistroTexto *texto);
static int interfazRegistro_inicializarElementos (s_interfazRegistroElementos *elementos);

static void interfazRegistro_configurarTexto (s_interfazRegistroTexto *texto, const s_fuentes *fuentes);
static void interfazRegistro_configurarElementos (s_interfazRegistroElementos *elementos);

static void interfazRegistro_tamYPosVentanaTexto (s_interfazRegistroTexto *texto);
static void interfazRegistro_tamYPosVentanaElementos (s_interfazRegistroElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickIntentarRegistrar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickCambiarInterfazAutenticacion (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_interfazRegistro *interfazRegistro);
static bool manejarEscribirNombre (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEnterIntentarRegistrar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazRegistro_inicializar (s_interfazRegistro *interfazRegistro)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    interfazRegistro->texto.textoInformativoContrasenia = NULL;
    interfazRegistro->texto.textoInformativoNombre = NULL;


    // ELEMENTOS

    interfazRegistro->elementos.flechaVolverBarra = NULL;
    interfazRegistro->elementos.flechaVolverTriangulo1 = NULL;
    interfazRegistro->elementos.flechaVolverTriangulo2 = NULL;


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (interfazRegistro_inicializarTexto (&(interfazRegistro->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazRegistro_inicializarElementos (&(interfazRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazRegistro_configurar (s_interfazRegistro *interfazRegistro, const s_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------




    // --------------- CONFIGURAR BUFFERS ---------------




    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazRegistro_configurarTexto (&(interfazRegistro->texto), fuentes);


    // ELEMENTOS

    interfazRegistro_configurarElementos (&(interfazRegistro->elementos));


    // --------------- TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTO

    interfazRegistro_tamYPosVentanaTexto (&(interfazRegistro->texto));


    // ELEMENTOS

    interfazRegistro_tamYPosVentanaElementos (&(interfazRegistro->elementos));
}

void interfazRegistro_accion (s_aplicacion *aplicacion, const s_interfazRegistro *interfazRegistro, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
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
            if (manejarClickEscribirNombre (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirContrasenia (aplicacion->renderizado, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickIntentarRegistrar (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazAutenticacion (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
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
            if (manejarEnterIntentarRegistrar (aplicacion, recursosComunesAutenticacionRegistro) == EVENTO_MANEJADO) break;
        }
        break;


    default:
        break;
    }
}

void interfazRegistro_actualizar (s_interfazRegistro *interfazRegistro, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
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

void interfazRegistro_renderizar (sfRenderWindow *renderizado, const s_interfazRegistro *interfazRegistro, const s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (223, 231, 233));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(recursosComunesAutenticacionRegistro->elementos));
    sfRenderWindow_drawRectangleShape (renderizado, interfazRegistro->elementos.flechaVolverBarra, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, interfazRegistro->elementos.flechaVolverTriangulo1, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, interfazRegistro->elementos.flechaVolverTriangulo2, NULL);


    // TEXTO

    recursosComunesAutenticacionRegistro_renderizarTexto (renderizado, &(recursosComunesAutenticacionRegistro->texto));
    sfRenderWindow_drawText (renderizado, interfazRegistro->texto.textoInformativoContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, interfazRegistro->texto.textoInformativoNombre, NULL);


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);


    sfRenderWindow_display (renderizado);
}

void interfazRegistro_liberar (s_interfazRegistro *interfazRegistro)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO

    DESTRUCTOR_SEGURO_TEXTO (interfazRegistro->texto.textoInformativoNombre);
    DESTRUCTOR_SEGURO_TEXTO (interfazRegistro->texto.textoInformativoContrasenia);


    // ELEMENTOS

    DESTRUCTOR_SEGURO_RECTANGULO (interfazRegistro->elementos.flechaVolverBarra);
    DESTRUCTOR_SEGURO_RECTANGULO (interfazRegistro->elementos.flechaVolverTriangulo1);
    DESTRUCTOR_SEGURO_RECTANGULO (interfazRegistro->elementos.flechaVolverTriangulo2);
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarRegistro (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
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

    sprintf (bufferSolicitud, "%c|%s|%s", INDICE_REGISTRO, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
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
        printf ("No se pudo registrar al usuario.\n");
}

/** \brief Modificar las configuraciones de los recursos graficos para adaptarlos a la interfaz de autenticacion.
 *
 * Modificar unicamente los recursos graficos de texto o elementos que se necesiten adaptar para cambiar a la interfaz de autenticacion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
static void cambiarInterfazAAutenticacion (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirContrasenia
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia, (sfVector2f){64, 262});

    // auxEscribirNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre, (sfVector2f){64, 167});

    // auxGuardarAutenticacion
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, (sfVector2f){415, 318});

    // guardarAutenticacion
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.guardarAutenticacion, (sfVector2f){55, 311});

    // ingresarNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.ingresarNombre, (sfVector2f){55, 120});

    // ingresoIncorrecto
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.ingresoIncorrecto, (sfVector2f){55, 384});

    // textoBotonIngresar
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.textoBotonIngresar, (sfVector2f){227, 412});

    // tituloInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->texto.tituloInterfaz, "AUTENTICAR");
    sfText_setPosition (recursosComunesAutenticacionRegistro->texto.tituloInterfaz, (sfVector2f){190, 25});


    // ELEMENTOS

    // barraEscribirContrasenia
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia, (sfVector2f){55, 263});

    // barraEscribirNombre
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre, (sfVector2f){55, 168});

    // botonGuardarAutenticacion
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonGuardarAutenticacion, (sfVector2f){406, 322});

    // botonIngresar
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonIngresar, (sfVector2f){195, 413});
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto de la interfaz de registro.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazRegistro_inicializarTexto (s_interfazRegistroTexto *texto)
{
    texto->textoInformativoContrasenia = sfText_create ();
    if (!texto->textoInformativoContrasenia)
    {
        perror ("\nERROR - Interfaz de registro, crear texto textoInformativoContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    texto->textoInformativoNombre = sfText_create ();
    if (!texto->textoInformativoNombre)
    {
        perror ("\nERROR - Interfaz de registro, crear texto textoInformativoNombre.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos de la interfaz de registro.
 *
 * Crea todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazRegistro_inicializarElementos (s_interfazRegistroElementos *elementos)
{
    elementos->flechaVolverBarra = sfRectangleShape_create ();
    if (!elementos->flechaVolverBarra)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento flechaVolverBarra.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->flechaVolverTriangulo1 = sfRectangleShape_create ();
    if (!elementos->flechaVolverTriangulo1)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento flechaVolverTriangulo1.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->flechaVolverTriangulo2 = sfRectangleShape_create ();
    if (!elementos->flechaVolverTriangulo2)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento flechaVolverTriangulo2.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de texto de la interfaz de registro.
 *
 * Configura todos los recursos graficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazRegistro_configurarTexto (s_interfazRegistroTexto *texto, const s_fuentes *fuentes)
{
    // textoInformativoContrasenia
    sfText_setFont (texto->textoInformativoContrasenia, fuentes->fuente1);
    sfText_setString (texto->textoInformativoContrasenia, "La contraseña debe contener al menos 8 caracteres, 1 mayuscula,\n 1 numero y 1 caracter especial");
    sfText_setFillColor (texto->textoInformativoContrasenia, sfColor_fromRGB (34, 48, 48));

    // textoInformativoNombre
    sfText_setFont (texto->textoInformativoNombre, fuentes->fuente1);
    sfText_setString (texto->textoInformativoNombre, "La longitud maxima del nombre es hasta 25 caracteres");
    sfText_setFillColor (texto->textoInformativoNombre, sfColor_fromRGB (34, 48, 48));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de registro.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_configurarElementos (s_interfazRegistroElementos *elementos)
{
    // flechaVolverBarra
    sfRectangleShape_setFillColor (elementos->flechaVolverBarra, sfColor_fromRGB (34, 48, 48));

    // flechaVolverTriangulo1
    sfRectangleShape_setFillColor (elementos->flechaVolverTriangulo1, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (elementos->flechaVolverTriangulo1, 45);

    // flechaVolverTriangulo2
    sfRectangleShape_setFillColor (elementos->flechaVolverTriangulo2, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (elementos->flechaVolverTriangulo2, -45);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico de la interfaz de registro.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_tamYPosVentanaTexto (s_interfazRegistroTexto *texto)
{
    // textoInformativoContrasenia
    sfText_setPosition (texto->textoInformativoContrasenia, (sfVector2f){55, 255});
    sfText_setCharacterSize (texto->textoInformativoContrasenia, 24);

    // textoInformativoNombre
    sfText_setPosition (texto->textoInformativoNombre, (sfVector2f){55, 120});
    sfText_setCharacterSize (texto->textoInformativoNombre, 24);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada elemento grafico de la interfaz de registro.
 *
 * Establecer a todos los elementos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_tamYPosVentanaElementos (s_interfazRegistroElementos *elementos)
{
    // flechaVolverBarra
    sfRectangleShape_setPosition (elementos->flechaVolverBarra, (sfVector2f){25, 20});
    sfRectangleShape_setSize (elementos->flechaVolverBarra, (sfVector2f){25, 2.5});

    // flechaVolverTriangulo1
    sfRectangleShape_setPosition (elementos->flechaVolverTriangulo1, (sfVector2f){25, 20});
    sfRectangleShape_setSize (elementos->flechaVolverTriangulo1, (sfVector2f){10, 2.5});

    // flechaVolverTriangulo2
    sfRectangleShape_setPosition (elementos->flechaVolverTriangulo2, (sfVector2f){23.5, 20.5});
    sfRectangleShape_setSize (elementos->flechaVolverTriangulo2, (sfVector2f){10, 2.1});
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
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 203.3});
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
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 359});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el boton para intentar registrar.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickIntentarRegistrar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) && (clickEnRectangulo (aplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar)))
    {
        intentarRegistro (aplicacion, recursosComunesAutenticacionRegistro);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en el texto para cambiar a la interfaz de autenticacion.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickCambiarInterfazAutenticacion (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_interfazRegistro *interfazRegistro)
{
    if (clickEnRectangulo (aplicacion->renderizado, interfazRegistro->elementos.flechaVolverBarra))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;
        cambiarInterfazAAutenticacion (recursosComunesAutenticacionRegistro);
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
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 203.3});
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
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){65.7 + limiteTextoAux.width, 359});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de presionado de la tecla "enter" para intentar registrar.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEnterIntentarRegistrar (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) &&
        ((recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE) || (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA)))
    {
        intentarRegistro (aplicacion, recursosComunesAutenticacionRegistro);
        return EVENTO_NO_MANEJADO;
    }
    return EVENTO_MANEJADO;
}


































