#include "interfacesGraficas/interfazAutenticacion/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void posicionarPuntoInsercion_escribirNombre (t_interfazAutenticacion *interfazAutenticacion);
static void posicionarPuntoInsercion_escribirContrasenia (t_interfazAutenticacion *interfazAutenticacion);

static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_click_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static bool procesar_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);
static bool procesar_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);

static bool procesar_enter_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static void deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_accion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
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
                if (procesar_click_escribirNombre (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (procesar_click_escribirContrasenia (contextoAplicacion->renderizado, interfazAutenticacion)) break;
                if (procesar_click_intentarAutenticar (contextoAplicacion, interfazAutenticacion)) break;
                if (procesar_click_cambiarAInterfazRegistro (contextoAplicacion, interfazAutenticacion)) break;
                deshabilitarFocos (interfazAutenticacion);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_nombre (contextoAplicacion, interfazAutenticacion, evento)) break;
            if (procesar_escribir_contrasenia (contextoAplicacion, interfazAutenticacion, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_intentarAutenticar (contextoAplicacion, interfazAutenticacion)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
            {
                if (procesar_pegarTextoDesdePortapapeles_escribir_nombre (contextoAplicacion, interfazAutenticacion)) break;
                if (procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (contextoAplicacion, interfazAutenticacion)) break;
            }

            break;


        default:
            break;
        }
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void mostrar_feedback_cargando (t_interfazAutenticacion *interfazAutenticacion)
{
    textoDeCarga_iniciar (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.textoDeCarga));
    sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Cargando");
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_credencialesInvalidas (t_interfazAutenticacion *interfazAutenticacion)
{
    uint32_t bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorCredenciales);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_errorConexion (t_interfazAutenticacion *interfazAutenticacion)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void intentarAutenticarYProcesarResultadoOperacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    _t_resultado_intentarAutenticar resultado_intentarAutenticar;

    resultado_intentarAutenticar = _interfazAutenticacion_intentar_autenticar (contextoAplicacion, interfazAutenticacion);
    switch (resultado_intentarAutenticar)
    {
        case INTENTARAUTENTICAR_RESULTADO_EXITO:
            mostrar_feedback_cargando (interfazAutenticacion);
            break;
        
        case INTENTARAUTENTICAR_RESULTADO_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credencialesInvalidas (interfazAutenticacion);
            break;

        case INTENTARAUTENTICAR_RESULTADO_ERROR_CONEXION:
            mostrar_feedback_errorConexion (interfazAutenticacion);
            break;

        default:
            break;
    }
}


static void posicionarPuntoInsercion_escribirNombre (t_interfazAutenticacion *interfazAutenticacion)
{
    sfFloatRect limitesAuxEscribirNombre;

    limitesAuxEscribirNombre = sfText_getGlobalBounds (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.size.x, 208});
}

static void posicionarPuntoInsercion_escribirContrasenia (t_interfazAutenticacion *interfazAutenticacion)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.size.x, 343});
}


static bool procesar_click_escribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
    posicionarPuntoInsercion_escribirNombre (interfazAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_escribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
    posicionarPuntoInsercion_escribirContrasenia (interfazAutenticacion);

    return EVENTO_MANEJADO;
}

static bool procesar_click_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
        
    if (!comunicacion_haySolicitudEnCurso (contextoAplicacion))
    {
        deshabilitarFocos (interfazAutenticacion);
        intentarAutenticarYProcesarResultadoOperacion (contextoAplicacion, interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_click_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.cambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    _interfazAutenticacion_cambiarAInterfaz_registro (contextoAplicacion, interfazAutenticacion);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercion_escribirNombre (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}

static bool procesar_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercion_escribirContrasenia (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    if (!comunicacion_haySolicitudEnCurso (contextoAplicacion))
        intentarAutenticarYProcesarResultadoOperacion (contextoAplicacion, interfazAutenticacion);

    return EVENTO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribir_nombre (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercion_escribirNombre (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}
 
static bool procesar_pegarTextoDesdePortapapeles_escribir_contrasenia (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercion_escribirContrasenia (interfazAutenticacion);
    }

    return EVENTO_MANEJADO;
}


static void deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion)
{
    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

