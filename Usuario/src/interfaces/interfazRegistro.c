#include "../../include/interfaces/interfazRegistro.h"



/* ============================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================ */



static int intentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static void cambiarInterfazAAutenticacion (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos);

static int interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos);
static int interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_fuentes *fuentes);
static void interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos);
static void interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos);

static void interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos);



/* ============================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickIntentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickCambiarInterfazAAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

static bool manejarEnterIntentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTOS

    interfazRegistro_inicializarValoresNulosTextos (&(interfazRegistro->textos));


    // ELEMENTOS

    interfazRegistro_inicializarValoresNulosElementos (&(interfazRegistro->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTOS

    if (interfazRegistro_inicializarTextos (&(interfazRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazRegistro_inicializarElementos (&(interfazRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, const t_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    interfazRegistro->habilitaciones.escribirCorreo = DESHABILITAR_ESCRIBIR_CORREO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(interfazRegistro->bufferCorreo) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazRegistro_configurarTextos (&(interfazRegistro->textos), fuentes);


    // ELEMENTOS

    interfazRegistro_configurarElementos (&(interfazRegistro->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazRegistro_tamYPosVentanaTextos (&(interfazRegistro->textos));


    // ELEMENTOS

    interfazRegistro_tamYPosVentanaElementos (&(interfazRegistro->elementos));
}

void interfazRegistro_accion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
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
            if (manejarClickEscribirNombre (aplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirContrasenia (aplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickEscribirCorreo (aplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickIntentarRegistro (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
            if (manejarClickCambiarInterfazAAutenticacion (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtTextEntered:
        if (evento.text.unicode < 128)
        {
            if (manejarEscribirNombre (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirContrasenia (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirCorreo (recursosComunesAutenticacionRegistro, interfazRegistro, evento) == EVENTO_MANEJADO) break;
        }
        break;


    case sfEvtKeyPressed:
        if (evento.key.code == sfKeyEnter)
        {
            if (manejarEnterIntentarRegistro (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
        }
        break;


    default:
        break;
    }
}

void interfazRegistro_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
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
        (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA ||
         interfazRegistro->habilitaciones.escribirCorreo == HABILITAR_ESCRIBIR_CORREO))
        actualizarPuntoInsercion (&(recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion), &(recursosComunesAutenticacionRegistro->habilitaciones.contadorPuntoInsercion));
    else
        reiniciarPuntoInsercion (&(recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion), &(recursosComunesAutenticacionRegistro->habilitaciones.contadorPuntoInsercion));
}

void interfazRegistro_renderizar (sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazRegistro *interfazRegistro)
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));


    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------

    // ELEMENTOS

    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(recursosComunesAutenticacionRegistro->elementos));
    interfazRegistro_renderizarElementos (renderizado, &(interfazRegistro->elementos));


    // TEXTOS

    recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(recursosComunesAutenticacionRegistro->textos));
    interfazRegistro_renderizarTextos (renderizado, &(interfazRegistro->textos));


    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------

    if (recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion == HABILITAR_PUNTO_INSERCION)
        sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);


    sfRenderWindow_display (renderizado);
}

void interfazRegistro_liberar (t_interfazRegistro *interfazRegistro)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    interfazRegistro_liberarTextos (&(interfazRegistro->textos));


    // ELEMENTOS

    interfazRegistro_liberarElementos (&(interfazRegistro->elementos));
}



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/** \brief Intentar registrar usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * INDICE_SOLICITUD_REGISTRO|nombre|contrasenia|correoElectronico
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si se ejecuto con exito, guarda el ID del usuario y selecciona la interfaz de contactos como menu principal.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EXITO si se pudo enviar correctamente, ERROR_INICIALIZACION en caso contrario.
 */
static int intentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];
    char estadoRespuesta;
    int id;

    snprintf (bufferSolicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s|%s", INDICE_SOLICITUD_REGISTRO, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia, interfazRegistro->bufferCorreo);
    enviarSolicitudYRecibirRespuesta (aplicacion->sock, bufferSolicitud, bufferRespuesta);
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
            printf ("Nombre o correo electronico ya registrado.\n");
            sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Nombre o correo electrónico ya registrado");
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
        }
        else
            printf ("Error de servidor.\n");
    }

    return ERROR_INICIALIZACION;
}

/** \brief Modificar las configuraciones de los recursos graficos para adaptarlos a la interfaz de autenticacion.
 *
 * Modificar unicamente los recursos graficos de texto o elementos que se necesiten adaptar para cambiar a la interfaz de autenticacion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 */
static void cambiarInterfazAAutenticacion (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';
    *(interfazRegistro->bufferCorreo) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirContrasenia
    sfText_setString (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, "");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, (sfVector2f){42, 315});

    // auxEscribirCorreo
    sfText_setString (interfazRegistro->textos.auxEscribirCorreo, "");

    // auxEscribirNombre
    sfText_setString (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, "");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, (sfVector2f){42, 180});

    // ingresarContrasenia
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.ingresarContrasenia, (sfVector2f){35, 255});

    // ingresarNombre
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.ingresarNombre, (sfVector2f){35, 120});

    // ingresoIncorrecto
    sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "");

    // textoBotonIngresar
    sfText_setString (recursosComunesAutenticacionRegistro->textos.textoBotonIngresar, "INGRESAR");
    centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.textoBotonIngresar, 180, 405, 140, 35);

    // textoCambiarInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz, "¿No tenés cuenta? Registrate acá");
    centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz, 0, 530, 500, 90);

    // tituloInterfaz
    sfText_setString (recursosComunesAutenticacionRegistro->textos.tituloInterfaz, "INICIAR SESIÓN");
    sfText_setPosition (recursosComunesAutenticacionRegistro->textos.tituloInterfaz, (sfVector2f){120, 25});


    // ELEMENTOS

    // barraEscribirContrasenia
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia, (sfVector2f){35, 315});

    // barraEscribirNombre
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre, (sfVector2f){35, 180});

    // botonIngresar
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.botonIngresar, (sfVector2f){180, 405});

    // subrayadoTitulo
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo, (sfVector2f){120, 75});
    sfRectangleShape_setSize (recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo, (sfVector2f){260, 2.5});
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos de la interfaz de registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 */
static void interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos)
{
    textos->auxEscribirCorreo = NULL;
    textos->ingresarCorreo = NULL;
    textos->textoInformativoContrasenia = NULL;
    textos->textoInformativoNombre = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos de la interfaz de registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 */
static void interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = NULL;
}

/** \brief Inicializar los recursos graficos de texto de la interfaz de registro.
 *
 * Crea todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos)
{
    textos->auxEscribirCorreo = sfText_create ();
    if (!textos->auxEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto auxEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarCorreo = sfText_create ();
    if (!textos->ingresarCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear texto ingresarCorreo.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoInformativoContrasenia = sfText_create ();
    if (!textos->textoInformativoContrasenia)
    {
        perror ("\nERROR - Interfaz de registro, crear texto textoInformativoContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoInformativoNombre = sfText_create ();
    if (!textos->textoInformativoNombre)
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
static int interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = sfRectangleShape_create ();
    if (!elementos->barraEscribirCorreo)
    {
        perror ("\nERROR - Interfaz de registro, crear elemento barraEscribirCorreo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de textos de la interfaz de registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_fuentes *fuentes)
{
    // auxEscribirCorreo
    sfText_setFont (textos->auxEscribirCorreo, fuentes->cuerpo);
    sfText_setFillColor (textos->auxEscribirCorreo, sfColor_fromRGB (94, 91, 87));

    // ingresarCorreo
    sfText_setFont (textos->ingresarCorreo, fuentes->ui);
    sfText_setString (textos->ingresarCorreo, "Correo electrónico:");
    sfText_setFillColor (textos->ingresarCorreo, sfColor_fromRGB (43, 43, 43));

    // textoInformativoContrasenia
    sfText_setFont (textos->textoInformativoContrasenia, fuentes->ui);
    sfText_setString (textos->textoInformativoContrasenia, "Mínimo 8 caracteres");
    sfText_setFillColor (textos->textoInformativoContrasenia, sfColor_fromRGB (94, 91, 87));

    // textoInformativoNombre
    sfText_setFont (textos->textoInformativoNombre, fuentes->ui);
    sfText_setString (textos->textoInformativoNombre, "Entre 3 y 25 caracteres");
    sfText_setFillColor (textos->textoInformativoNombre, sfColor_fromRGB (94, 91, 87));
}

/** \brief Configurar los recursos graficos de elementos de la interfaz de registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorreo
    sfRectangleShape_setFillColor (elementos->barraEscribirCorreo, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirCorreo, sfColor_fromRGB (169, 163, 154));
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico de la interfaz de registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setPosition (textos->auxEscribirCorreo, (sfVector2f){42, 392});
    sfText_setCharacterSize (textos->auxEscribirCorreo, 22);

    // ingresarCorro
    sfText_setPosition (textos->ingresarCorreo, (sfVector2f){35, 350});
    sfText_setCharacterSize (textos->ingresarCorreo, 28);

    // textoInformativoContrasenia
    sfText_setPosition (textos->textoInformativoContrasenia, (sfVector2f){35, 260});
    sfText_setCharacterSize (textos->textoInformativoContrasenia, 20);

    // textoInformativoNombre
    sfText_setPosition (textos->textoInformativoNombre, (sfVector2f){35, 135});
    sfText_setCharacterSize (textos->textoInformativoNombre, 20);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada elemento grafico de la interfaz de registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorro
    sfRectangleShape_setPosition (elementos->barraEscribirCorreo, (sfVector2f){35, 392});
    sfRectangleShape_setSize (elementos->barraEscribirCorreo, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirCorreo, 2);
}

/** \brief Renderizar los recursos graficos de textos de la interfaz de registro.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoNombre, NULL);
}

/** \brief Renderizar los recursos graficos de elementos de la interfaz de registro.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 *
 */
static void interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirCorreo, NULL);
}

/** \brief Liberar, de manera segura, todas los textos graficos de la interfaz de registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de la interfaz de registro.
 */
static void interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoContrasenia);
}

/** \brief Liberar, de manera segura, todas los elementos graficos de la interfaz de registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de la interfaz de registro.
 */
static void interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirCorreo);
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en la barra para escribir el nombre de usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = HABILITAR_ESCRIBIR_NOMBRE;
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
        interfazRegistro->habilitaciones.escribirCorreo = DESHABILITAR_ESCRIBIR_CORREO;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 198});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = DESHABILITAR_ESCRIBIR_NOMBRE;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir la contrasenia del usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
    {
        recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = HABILITAR_ESCRIBIR_CONTRASENIA;
        interfazRegistro->habilitaciones.escribirCorreo = DESHABILITAR_ESCRIBIR_CORREO;
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 323});
        return EVENTO_MANEJADO;
    }
    recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de click en la barra para escribir el correo electronico del usuario.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (clickEnRectangulo (renderizado, interfazRegistro->elementos.barraEscribirCorreo))
    {
        interfazRegistro->habilitaciones.escribirCorreo = HABILITAR_ESCRIBIR_CORREO;
        limiteTextoAux = sfText_getGlobalBounds (interfazRegistro->textos.auxEscribirCorreo);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 420});
        return EVENTO_MANEJADO;
    }
    interfazRegistro->habilitaciones.escribirCorreo = DESHABILITAR_ESCRIBIR_CORREO;
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
static bool manejarClickIntentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) && (clickEnRectangulo (aplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar)))
    {
        intentarRegistro (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro);
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
static bool manejarClickCambiarInterfazAAutenticacion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    if (clickEnTexto (aplicacion->renderizado, recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
    {
        aplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;
        cambiarInterfazAAutenticacion (recursosComunesAutenticacionRegistro, interfazRegistro);
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir el nombre de usuario.
 *
 * Si se encuentra habilitado el escribir nombre, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
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

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE)
    {
        ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO, eventoChar);
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 198});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir la contrasenia del usuario.
 *
 * Si se encuentra habilitado el escribir contrasenia, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
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

    if (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA)
    {
        ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO, eventoChar);
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 323});
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}

/** \brief Manejar el evento de escribir el correo electronico del usuario.
 *
 * Si se encuentra habilitado el escribir correo, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
static bool manejarEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->habilitaciones.escribirCorreo == HABILITAR_ESCRIBIR_CORREO)
    {
        ingresarCaracterABuffer (interfazRegistro->bufferCorreo, MAX_CORREO_USUARIO, eventoChar);
        limitarVisualizarTextoSobreBarra (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->bufferCorreo, 415);
        limiteTextoAux = sfText_getGlobalBounds (interfazRegistro->textos.auxEscribirCorreo);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 420});
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
static bool manejarEnterIntentarRegistro (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    if ((recursosComunesAutenticacionRegistro->habilitaciones.ingresar == HABILITAR_INGRESAR) &&
        (
         (recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre == HABILITAR_ESCRIBIR_NOMBRE) ||
         (recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia == HABILITAR_ESCRIBIR_CONTRASENIA) ||
         (interfazRegistro->habilitaciones.escribirCorreo == HABILITAR_ESCRIBIR_CORREO)
        )
       )
    {
        intentarRegistro (aplicacion, recursosComunesAutenticacionRegistro, interfazRegistro);
        return EVENTO_NO_MANEJADO;
    }
    return EVENTO_MANEJADO;
}


































