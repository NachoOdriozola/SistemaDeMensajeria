#include "../../../include/interfacesGraficas/interfazRegistro./interfazRegistro_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void desactivarRecursosInterfazRegistro (t_interfazRegistro *interfazRegistro);

static void posicionarPuntoInsercionBarraEscrituraNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void posicionarPuntoInsercionBarraEscrituraCorreo (t_interfazRegistro *interfazRegistro);

static bool sonDatosRegistroUsuarioValidos (t_interfazRegistro *interfazRegistro);
static  t_respuestaRegistro fabricarRespuestaRegistroInvalida ();
static void procesarSegunRespuestaRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const t_respuestaRegistro *respuestaRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_deshabilitarFocos (t_interfazRegistro *interfazRegistro)
{
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazRegistro->estadoFoco = IR_NINGUNO;
}


bool _interfazRegistro_manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro->recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    interfazRegistro->estadoFoco = IR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro->recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnRectangulo (renderizado, interfazRegistro->elementos.barraEscribirCorreo))
        return EVENTO_NO_MANEJADO;

    interfazRegistro->estadoFoco = ESCRIBIR_CORREO;
    interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarClickIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    t_respuestaRegistro respuestaRegistro;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;

    if (sonDatosRegistroUsuarioValidos (interfazRegistro))
        respuestaRegistro = enviarSolicitudRegistro (contextoAplicacion->sock, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, interfazRegistro->logica.correoElectronico);
    else
        respuestaRegistro = fabricarRespuestaRegistroInvalida ();

    procesarSegunRespuestaRegistro (contextoAplicacion, interfazRegistro, &respuestaRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarClickCambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    omitirEventosPendientes (contextoAplicacion->renderizado);
    desactivarRecursosInterfazRegistro (interfazRegistro);
    recursosComunesAutenticacionRegistro_activarInterfazAutenticacion (interfazRegistro->recursosComunesAutenticacionRegistro);
    contextoAplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;

    return EVENTO_MANEJADO;
}


bool _interfazRegistro_manejarEscribirNombre (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarEscribirContrasenia (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarEscribirCorreo (t_interfazRegistro *interfazRegistro, sfEvent eventoChar)
{
    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO, eventoChar) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


bool _interfazRegistro_manejarEnterIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    t_respuestaRegistro respuestaRegistro;

    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA) &&
        (interfazRegistro->estadoFoco != ESCRIBIR_CORREO))
        return EVENTO_NO_MANEJADO;

    if (sonDatosRegistroUsuarioValidos (interfazRegistro))
        respuestaRegistro = enviarSolicitudRegistro (contextoAplicacion->sock, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, interfazRegistro->logica.correoElectronico);
    else
        respuestaRegistro = fabricarRespuestaRegistroInvalida ();

    procesarSegunRespuestaRegistro (contextoAplicacion, interfazRegistro, &respuestaRegistro);
    
    return EVENTO_NO_MANEJADO;
}


bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirNombre (t_interfazRegistro *interfazRegistro)
{
    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazRegistro->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        sfText_setColor (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazRegistro->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}

bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirCorreo (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limiteTextoAux;

    if (interfazRegistro->estadoFoco != ESCRIBIR_CORREO)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazRegistro->logica.correoElectronico, MAX_CORREO_ELECTRONICO) == EXITO)
    {
        sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazRegistro->textos.auxEscribirCorreo, interfazRegistro->logica.correoElectronico, 415);
        posicionarPuntoInsercionBarraEscrituraCorreo (interfazRegistro);
    }

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetearInterfaz (t_interfazRegistro *interfazRegistro)
{
    // Deshabilitar foco.
    interfazRegistro->estadoFoco = IR_NINGUNO;

    // Setear cadenas vacias.
    *(interfazRegistro->logica.correoElectronico) = '\0';
}

static void desactivarTextosInterfazRegistro (t_interfazRegistroTextos *textos)
{
    // auxEscribirCorreo
    sfText_setString (textos->auxEscribirCorreo, "");
    sfText_setFillColor (textos->auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
}

static void desactivarRecursosInterfazRegistro (t_interfazRegistro *interfazRegistro)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    resetearInterfaz (interfazRegistro);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTO
    desactivarTextosInterfazRegistro (&(interfazRegistro->textos));
}


static void posicionarPuntoInsercionBarraEscrituraNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limitesAuxEscribirNombre;
    
    limitesAuxEscribirNombre = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.width, 198});
}

static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limitesAuxEscribirContrasenia;
    
    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.width, 323});
}

static void posicionarPuntoInsercionBarraEscrituraCorreo (t_interfazRegistro *interfazRegistro)
{
    sfFloatRect limitesAuxEscribirCorreo;

    limitesAuxEscribirCorreo = sfText_getGlobalBounds (interfazRegistro->textos.auxEscribirCorreo);
    sfRectangleShape_setPosition (interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirCorreo.width, 420});
}


static bool noEsNombreValido (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (strlen (recursosComunesAutenticacionRegistro->logica.nombreUsuario) < 3)
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (160, 100, 90));
        return 1;
    }
    return 0;
}

static bool noEsContraseniaValida (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (strlen (recursosComunesAutenticacionRegistro->logica.contrasenia) < 8)
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (160, 100, 90));
        return 1;
    }
    return 0;
}

static bool noEsCorreoElectronicoValido (t_interfazRegistro *interfazRegistro)
{
    char *ptr = strchr (interfazRegistro->logica.correoElectronico, '@'); // Se posiciona en el @

    if ((ptr == NULL) ||                                                                    // Si no tiene @
        (ptr == interfazRegistro->logica.correoElectronico) ||         // O empieza con @
        (strchr (ptr, '.') == NULL) ||                                                   // O no tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL))                                             // O tiene 2 arrobas
    {
        sfText_setColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (160, 100, 90));
        return 1;
    }
    return 0;
}

/*
 * Verificar si los datos de registro que envio el usuario son validos segun las restricciones del dominio. En caso de no ser validos, se modifica el color del texto grafico de input.
 */
static bool sonDatosRegistroUsuarioValidos (t_interfazRegistro *interfazRegistro)
{
    bool flag = 1;

    if (noEsNombreValido (interfazRegistro->recursosComunesAutenticacionRegistro))
        flag = 0;

    if (noEsContraseniaValida (interfazRegistro->recursosComunesAutenticacionRegistro))    
        flag = 0;

    if (noEsCorreoElectronicoValido (interfazRegistro))
        flag = 0;
    
    return flag;
}

/*
 * Fabricar una respuesta de registro invalida en caso de no tener que enviar una solicitud al servidor por la invalidez de los datos.
*/
static  t_respuestaRegistro fabricarRespuestaRegistroInvalida ()
{
    t_respuestaRegistro respuestaRegistroInvalida = {SOLICITUD_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO};
    return respuestaRegistroInvalida;
}

static void procesarSegunRespuestaRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const t_respuestaRegistro *respuestaRegistro)
{
    if (respuestaRegistro->estado == SOLICITUD_EXITO)
    {
        contextoAplicacion->usuario.id = respuestaRegistro->idUsuario;
        strcpy (contextoAplicacion->usuario.nombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
        contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    }
    else if (respuestaRegistro->estado == SOLICITUD_ERROR_CREDENCIALES_INVALIDAS)
    {
        sfUint32 bufferIngresoIncorrecto [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00F3, 'n', 'i', 'c', 'o', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
        sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferIngresoIncorrecto);
        centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
    }
}

