#include "../../include/interfaces/interfazRegistro.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazRegistro (t_interfazRegistro *interfazRegistro);
static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

static int validarIngresoDatos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarClickCambiarInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);
static bool manejarEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

static bool manejarEnterIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

static bool manejarPegarPortapapelesEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarPegarPortapapelesEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);
static bool manejarPegarPortapapelesEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos);

static int interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos);
static int interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static void interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos);

static void interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos);
static void interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos);

static void interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos);
static void interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos);



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



void interfazRegistro_inicializarValoresNulos (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS

    interfazRegistro_inicializarValoresNulosTextos (&(interfazRegistro->textos));


    // ELEMENTOS

    interfazRegistro_inicializarValoresNulosElementos (&(interfazRegistro->elementos));
}

int interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro)
{
    // TEXTOS

    if (interfazRegistro_inicializarTextos (&(interfazRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (interfazRegistro_inicializarElementos (&(interfazRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    interfazRegistro->estadoFoco = IR_NINGUNO;


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

void interfazRegistro_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
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
                if (manejarClickEscribirNombre (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickEscribirContrasenia (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickEscribirCorreo (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickIntentarRegistro (contextoAplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
                if (manejarClickCambiarInterfazAutenticacion (contextoAplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;
                deshabilitarFocos (recursosComunesAutenticacionRegistro, interfazRegistro);
            }
            break;


        case sfEvtTextEntered:
            if (manejarEscribirNombre (recursosComunesAutenticacionRegistro, interfazRegistro, evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirContrasenia (recursosComunesAutenticacionRegistro, interfazRegistro, evento) == EVENTO_MANEJADO) break;
            if (manejarEscribirCorreo (recursosComunesAutenticacionRegistro, interfazRegistro, evento) == EVENTO_MANEJADO) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (manejarEnterIntentarRegistro (contextoAplicacion, recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirNombre (recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirContrasenia (recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (manejarPegarPortapapelesEscribirCorreo (recursosComunesAutenticacionRegistro, interfazRegistro) == EVENTO_MANEJADO) break;

            break;


        default:
            break;
        }
    }
}

void interfazRegistro_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    // --------------- PUNTO DE INSERCION ---------------

    if ((recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA ||
         interfazRegistro->estadoFoco == ESCRIBIR_CORREO))
        actualizarPuntoInsercion (&(recursosComunesAutenticacionRegistro->puntoInsercion));
    else if (puntoInsercionHabilitado (&(recursosComunesAutenticacionRegistro->puntoInsercion)))
        resetearPuntoInsercion (&(recursosComunesAutenticacionRegistro->puntoInsercion));
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

    if (puntoInsercionHabilitado (&(recursosComunesAutenticacionRegistro->puntoInsercion)))
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



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



static void desactivarRecursosInterfazRegistro (t_interfazRegistro *interfazRegistro)
{
    // --------------- CONFIGURAR FOCO ---------------

    interfazRegistro->estadoFoco = IR_NINGUNO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(interfazRegistro->bufferCorreo) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirCorreo
    sfText_setString (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, "");
    if (interfazRegistro->textos.inputCorreo.validez == INPUT_INVALIDO)
    {
        interfazRegistro->textos.inputCorreo.validez = INPUT_VALIDO;
        sfText_setFillColor (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
    }


    // ELEMENTOS
}

static void deshabilitarFocos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazRegistro->estadoFoco = IR_NINGUNO;
}


/*
 * Validar si los datos ingresados son adecuados segun las restricciones establecidas.
 * En caso de no ser validos, se establece su validez como invalidos y se modifica el color del texto grafico de input.
 */
static int validarIngresoDatos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    bool flag = 0;

    // NOMBRE

    if (strlen (recursosComunesAutenticacionRegistro->bufferNombre) < 3)
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, sfColor_fromRGB (160, 100, 90));
        recursosComunesAutenticacionRegistro->textos.inputNombre.validez = INPUT_INVALIDO;
        flag = 1;
    }


    // CONTRASENIA

    if (strlen (recursosComunesAutenticacionRegistro->bufferContrasenia) < 8)
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, sfColor_fromRGB (160, 100, 90));
        recursosComunesAutenticacionRegistro->textos.inputContrasenia.validez = INPUT_INVALIDO;
        flag = 1;
    }


    // CORREO ELECTRONICO

    char *ptr;

    ptr = strchr (interfazRegistro->bufferCorreo, '@');
    if ((ptr == NULL) || // No tiene arroba
        (ptr == interfazRegistro->bufferCorreo) || // Empieza con @
        (strchr (ptr, '.') == NULL) || // No tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL)) // Tiene 2 arrobas
    {
        sfText_setColor (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, sfColor_fromRGB (160, 100, 90));
        interfazRegistro->textos.inputCorreo.validez = INPUT_INVALIDO;
        flag = 1;
    }


    if (flag)
        return INGRESO_INVALIDO;
    return INGRESO_VALIDO;
}

static void estadoHabilitarIngreso (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    if ((strlen (recursosComunesAutenticacionRegistro->bufferNombre) > 0) &&
        (strlen (recursosComunesAutenticacionRegistro->bufferContrasenia) > 0) &&
        (strlen (interfazRegistro->bufferCorreo) > 0))
        recursosComunesAutenticacionRegistro->ingreso = HABILITADO;
    else
        recursosComunesAutenticacionRegistro->ingreso = DESHABILITADO;
}



/* ============================================================================================================================================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



static bool manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 198});

    return EVENTO_MANEJADO;
}

static bool manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 323});

    return EVENTO_MANEJADO;
}

static bool manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, interfazRegistro->elementos.barraEscribirCorreo))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->estadoFoco = ESCRIBIR_CORREO;
    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    limiteTextoAux = sfText_getGlobalBounds (interfazRegistro->textos.inputCorreo.auxEscribirCorreo);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 420});

    return EVENTO_MANEJADO;
}

static bool manejarClickIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    t_respuestaRegistro respuestaRegistro;

    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    if (validarIngresoDatos (recursosComunesAutenticacionRegistro, interfazRegistro) == INGRESO_INVALIDO)
        return EVENTO_MANEJADO;

    respuestaRegistro = enviarSolicitudRegistrar (contextoAplicacion->sock, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia, interfazRegistro->bufferCorreo);
    if (respuestaRegistro.estado == RESPUESTA_EXITO)
    {
        contextoAplicacion->usuario.id = respuestaRegistro.idUsuario;
        strcpy (contextoAplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
        contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    }
    else if (respuestaRegistro.estado == RESPUESTA_ERROR_CREDENCIALES_INVALIDAS)
    {
        sfUint32 bufferIngresoIncorrecto [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00F3, 'n', 'i', 'c', 'o', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
        sfText_setUnicodeString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferIngresoIncorrecto);
        centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
    }

    return EVENTO_MANEJADO;
}

static bool manejarClickCambiarInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfEvent evento;

    if (!clickEnTexto (contextoAplicacion->renderizado, recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento)){continue;}

    contextoAplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;
    desactivarRecursosInterfazRegistro (interfazRegistro);
    activarInterfazAutenticacion (recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}


static bool manejarEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO, eventoChar) == CARACTER_INVALIDO)
        return EVENTO_NO_MANEJADO;

    estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
    if (recursosComunesAutenticacionRegistro->textos.inputNombre.validez == INPUT_INVALIDO)
    {
        recursosComunesAutenticacionRegistro->textos.inputNombre.validez = INPUT_VALIDO;
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
    }
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 198});

    return EVENTO_MANEJADO;
}

static bool manejarEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO, eventoChar) == CARACTER_INVALIDO)
        return EVENTO_NO_MANEJADO;

    estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
    if (recursosComunesAutenticacionRegistro->textos.inputContrasenia.validez == INPUT_INVALIDO)
    {
        recursosComunesAutenticacionRegistro->textos.inputContrasenia.validez = INPUT_VALIDO;
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
    }
    limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 323});

    return EVENTO_MANEJADO;
}

static bool manejarEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->bufferCorreo, MAX_CORREO_USUARIO, eventoChar) == CARACTER_INVALIDO)
        return EVENTO_NO_MANEJADO;

    estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
    if (interfazRegistro->textos.inputCorreo.validez == INPUT_INVALIDO)
    {
        interfazRegistro->textos.inputCorreo.validez = INPUT_VALIDO;
        sfText_setFillColor (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
    }
    limitarVisualizarTextoSobreBarra (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, interfazRegistro->bufferCorreo, 415);
    limiteTextoAux = sfText_getGlobalBounds (interfazRegistro->textos.inputCorreo.auxEscribirCorreo);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 420});

    return EVENTO_MANEJADO;
}


static bool manejarEnterIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    t_respuestaRegistro respuestaRegistro;

    if (recursosComunesAutenticacionRegistro->ingreso == DESHABILITADO)
        return EVENTO_NO_MANEJADO;

    if ((recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA) &&
        (interfazRegistro->estadoFoco != ESCRIBIR_CORREO))
        return EVENTO_NO_MANEJADO;

    if (validarIngresoDatos (recursosComunesAutenticacionRegistro, interfazRegistro) == INGRESO_INVALIDO)
        return EVENTO_MANEJADO;

    respuestaRegistro = enviarSolicitudRegistrar (contextoAplicacion->sock, recursosComunesAutenticacionRegistro->bufferNombre, recursosComunesAutenticacionRegistro->bufferContrasenia, interfazRegistro->bufferCorreo);
    if (respuestaRegistro.estado == RESPUESTA_EXITO)
    {
        contextoAplicacion->usuario.id = respuestaRegistro.idUsuario;
        strcpy (contextoAplicacion->usuario.nombre, recursosComunesAutenticacionRegistro->bufferNombre);
        contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    }
    else if (respuestaRegistro.estado == RESPUESTA_ERROR_CREDENCIALES_INVALIDAS)
    {
        sfUint32 bufferIngresoIncorrecto [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00F3, 'n', 'i', 'c', 'o', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
        sfText_setUnicodeString (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferIngresoIncorrecto);
        centrarTextoEnArea (recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
    }

    return EVENTO_NO_MANEJADO;
}


static bool manejarPegarPortapapelesEscribirNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (recursosComunesAutenticacionRegistro->bufferNombre, MAX_NOMBRE_USUARIO))
    {
        estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
        if (recursosComunesAutenticacionRegistro->textos.inputNombre.validez == INPUT_INVALIDO)
        {
            recursosComunesAutenticacionRegistro->textos.inputNombre.validez = INPUT_VALIDO;
            sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        }
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre, recursosComunesAutenticacionRegistro->bufferNombre, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputNombre.auxEscribirNombre);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 198});
    }

    return EVENTO_MANEJADO;
}

static bool manejarPegarPortapapelesEscribirContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (recursosComunesAutenticacionRegistro->bufferContrasenia, MAX_CONTRASENIA_USUARIO))
    {
        estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
        if (recursosComunesAutenticacionRegistro->textos.inputContrasenia.validez == INPUT_INVALIDO)
        {
            recursosComunesAutenticacionRegistro->textos.inputContrasenia.validez = INPUT_VALIDO;
            sfText_setColor (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        }
        limitarVisualizarTextoSobreBarra (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia, recursosComunesAutenticacionRegistro->bufferContrasenia, 415);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.inputContrasenia.auxEscribirContrasenia);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 323});
    }

    return EVENTO_MANEJADO;
}

static bool manejarPegarPortapapelesEscribirCorreo (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (interfazRegistro->bufferCorreo, MAX_CORREO_USUARIO))
    {
        estadoHabilitarIngreso (recursosComunesAutenticacionRegistro, interfazRegistro);
        if (interfazRegistro->textos.inputCorreo.validez == INPUT_INVALIDO)
        {
            interfazRegistro->textos.inputCorreo.validez = INPUT_VALIDO;
            sfText_setFillColor (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        }
        limitarVisualizarTextoSobreBarra (interfazRegistro->textos.inputCorreo.auxEscribirCorreo, interfazRegistro->bufferCorreo, 415);
        limiteTextoAux = sfText_getGlobalBounds (interfazRegistro->textos.inputCorreo.auxEscribirCorreo);
        sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limiteTextoAux.width, 420});
    }

    return EVENTO_MANEJADO;
}




/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos)
{
    textos->inputCorreo.auxEscribirCorreo = NULL;
    textos->ingresarCorreo = NULL;
    textos->textoInformativoContrasenia = NULL;
    textos->textoInformativoNombre = NULL;
}

static void interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos)
{
    elementos->barraEscribirCorreo = NULL;
}


static int interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos)
{
    textos->inputCorreo.auxEscribirCorreo = sfText_create ();
    if (!textos->inputCorreo.auxEscribirCorreo)
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


static void interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // auxEscribirCorreo
    sfText_setFont (textos->inputCorreo.auxEscribirCorreo, fuentes->cuerpo);
    sfText_setFillColor (textos->inputCorreo.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
    textos->inputCorreo.validez = INPUT_VALIDO;

    // ingresarCorreo
    sfText_setFont (textos->ingresarCorreo, fuentes->ui);
    sfText_setFillColor (textos->ingresarCorreo, sfColor_fromRGB (43, 43, 43));
    sfUint32 bufferIngresarCorreo [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', 0};
    sfText_setUnicodeString (textos->ingresarCorreo, bufferIngresarCorreo);

    // textoInformativoContrasenia
    sfText_setFont (textos->textoInformativoContrasenia, fuentes->ui);
    sfText_setFillColor (textos->textoInformativoContrasenia, sfColor_fromRGB (94, 91, 87));
    sfUint32 bufferTextoInformativoContrasenia [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '8', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->textoInformativoContrasenia, bufferTextoInformativoContrasenia);

    // textoInformativoNombre
    sfText_setFont (textos->textoInformativoNombre, fuentes->ui);
    sfText_setFillColor (textos->textoInformativoNombre, sfColor_fromRGB (94, 91, 87));
    sfUint32 bufferTextoInformativoNombre [] = {'M', 0x00ed, 'n', 'i', 'm', 'o', ' ', '3', ' ', 'c', 'a', 'r', 'a', 'c', 't', 'e', 'r', 'e', 's', 0};
    sfText_setUnicodeString (textos->textoInformativoNombre, bufferTextoInformativoNombre);
}

static void interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorreo
    sfRectangleShape_setFillColor (elementos->barraEscribirCorreo, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirCorreo, sfColor_fromRGB (169, 163, 154));
}


static void interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setPosition (textos->inputCorreo.auxEscribirCorreo, (sfVector2f){42, 392});
    sfText_setCharacterSize (textos->inputCorreo.auxEscribirCorreo, 22);

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

static void interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos)
{
    // barraEscribirCorro
    sfRectangleShape_setPosition (elementos->barraEscribirCorreo, (sfVector2f){35, 392});
    sfRectangleShape_setSize (elementos->barraEscribirCorreo, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirCorreo, 2);
}


static void interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->inputCorreo.auxEscribirCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoInformativoNombre, NULL);
}

static void interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirCorreo, NULL);
}


static void interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->inputCorreo.auxEscribirCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarCorreo);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoInformativoContrasenia);
}

static void interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirCorreo);
}
































