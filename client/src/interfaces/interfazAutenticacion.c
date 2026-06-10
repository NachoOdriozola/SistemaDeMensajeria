#include "../../include/interfaces/interfazAutenticacion.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================================================================================================================================ */


   
   static void desactivarRecursosInterfazAutenticacion (t_interfazAutenticacion *interfazAutenticacion);
   static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);
   
   static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);


   
/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarClickCambiarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);
static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, sfEvent eventoChar);

static bool manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

static bool manejarPegarPortapapelesEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static bool manejarPegarPortapapelesEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



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



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



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
            if (manejarEscribirNombre (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirContrasenia (recursosComunesAutenticacionRegistro, evento) == EVENTO_MANEJADO) break;
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



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazAutenticacion (t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}


static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((strlen (recursosComunesAutenticacionRegistro->bufferNombre) > 0) &&
        (strlen (recursosComunesAutenticacionRegistro->bufferContrasenia) > 0))
        recursosComunesAutenticacionRegistro->ingreso = HABILITADO;
    else
        recursosComunesAutenticacionRegistro->ingreso = DESHABILITADO;
}



/* ============================================================================================================================================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



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

static bool manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    t_respuestaAutenticacion respuestaAutenticacion;

    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    respuestaAutenticacion = enviarSolicitudAutenticar (contextoAplicacion->sock, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
    switch (respuestaAutenticacion.estado)
    {
        case RESPUESTA_EXITO:
            contextoAplicacion->usuario.id = respuestaAutenticacion.idUsuario;
            strcpy (contextoAplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
            contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
            break;

        case RESPUESTA_ERROR_CREDENCIALES_INVALIDAS:
            sfUint32 bufferIngresoIncorrecto [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
            sfText_setUnicodeString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferIngresoIncorrecto);
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;

        case RESPUESTA_ERROR_OPERACION_INVALIDA:

            sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Usuario ya conectado");
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;
    }

    return EVENTO_MANEJADO;
}

static bool manejarClickCambiarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion)
{
    sfEvent evento;

    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_REGISTRO;
    desactivarRecursosInterfazAutenticacion (interfazAutenticacion);
    activarInterfazRegistro (recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}


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


static bool manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    t_respuestaAutenticacion respuestaAutenticacion;

    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if ((recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    respuestaAutenticacion = enviarSolicitudAutenticar (contextoAplicacion->sock, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia);
    switch (respuestaAutenticacion.estado)
    {
        case RESPUESTA_EXITO:
            contextoAplicacion->usuario.id = respuestaAutenticacion.idUsuario;
            strcpy (contextoAplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
            contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
            break;

        case RESPUESTA_ERROR_CREDENCIALES_INVALIDAS:
            sfUint32 bufferIngresoIncorrecto [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
            sfText_setUnicodeString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferIngresoIncorrecto);
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;

        case RESPUESTA_ERROR_OPERACION_INVALIDA:

            sfText_setString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Usuario ya conectado");
            centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;
    }

    return EVENTO_MANEJADO;
}


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



/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos)
{

}

static void interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos)
{

}


static int interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos)
{


    return EXITO;
}

static int interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos)
{


    return EXITO;
}


static void interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{

}

static void interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos)
{

}


static void interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos)
{

}

static void interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos)
{

}


static void interfazAutenticacion_renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos)
{

}

static void interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos)
{

}


static void interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos)
{

}

static void interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos)
{

}

































