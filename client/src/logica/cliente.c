#include "logica/cliente.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void inicializarValoresNulosAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

static bool usuarioSeAutentico (t_contextoAplicacion *contextoAplicacion);
static void cambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

static bool usuarioSalioDelMenuPrincipal (t_contextoAplicacion *contextoAplicacion);
static void cambiarDeInterfaz (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


t_codigoRetorno inicializarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    printf ("-INICIALIZANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- INICIALIZAR VALORES NULOS DE LA APLICACION ---------------

    inicializarValoresNulosAplicacion (contextoAplicacion, interfacesGraficas);

    // --------------- INICIALIZAR SOCKET ---------------

    if (socket_inicializar () == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // --------------- INICIALIZAR RENDERIZADO ---------------

    contextoAplicacion->renderizado = sfRenderWindow_create ((sfVideoMode){500, 620}, "Aplicacion", sfDefaultStyle, NULL);
    if (!contextoAplicacion->renderizado)
    {
        perror ("\nERROR - Crear renderizado.\n");
        return ERROR_INICIALIZACION;
    }

    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ---------------

    if (recursosComunesAutenticacionRegistro_inicializar (&(interfacesGraficas->recursosComunesAutenticacionRegistro)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos comunes autenticacion-registro.\n");
        return ERROR_INICIALIZACION;
    }

    // --------------- INICIALIZAR INTERFACES GRAFICAS ---------------

    if (interfazContactos_inicializar (&(interfacesGraficas->contactos)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de contactos.\n");
        return ERROR_INICIALIZACION;
    }

    if (interfazAutenticacion_inicializar (&(interfacesGraficas->autenticacion)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de autenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    if (interfazRegistro_inicializar (&(interfacesGraficas->registro)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de registro.\n");
        return ERROR_INICIALIZACION;
    }


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

void configurarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    printf ("-CONFIGURANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- CONFIGURAR APLICACION ---------------

    sfRenderWindow_setFramerateLimit (contextoAplicacion->renderizado, 60);
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
    contextoAplicacion->solicitudEnCurso = false;
    omitirEventosPendientes (contextoAplicacion->renderizado);

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS COMUNES ---------------

    recursosComunesAutenticacionRegistro_configurar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS DE LAS INTERFACES Y ASIGNAR LOS RECURSOS COMUNES ---------------

    interfazContactos_configurar (&(interfacesGraficas->contactos));
    interfazAutenticacion_configurar (&(interfacesGraficas->autenticacion), &(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazRegistro_configurar (&(interfacesGraficas->registro), &(interfacesGraficas->recursosComunesAutenticacionRegistro));


    printf ("-CONFIGURACION EXITOSA-\n");
}

void ejecutarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    switch (contextoAplicacion->interfazActual)
        {
        case INTERFAZ_AUTENTICACION:
            interfazAutenticacion_ejecutar (contextoAplicacion, &(interfacesGraficas->autenticacion));
            if (usuarioSeAutentico (contextoAplicacion))
                cambiarAInterfazContactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_REGISTRO:
            interfazRegistro_ejecutar (contextoAplicacion, &(interfacesGraficas->registro));
            if (usuarioSeAutentico (contextoAplicacion))
                cambiarAInterfazContactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_CONTACTOS:
            interfazContactos_ejecutar (contextoAplicacion, &(interfacesGraficas->contactos));
            if (usuarioSalioDelMenuPrincipal (contextoAplicacion))
                cambiarDeInterfaz (contextoAplicacion, interfacesGraficas);
            break;
        }
}

void liberarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    printf ("-LIBERANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- LIBERAR INTERFACES GRAFICAS ---------------

    interfazAutenticacion_liberar (&(interfacesGraficas->autenticacion));
    interfazRegistro_liberar (&(interfacesGraficas->registro));
    interfazContactos_liberar (&(interfacesGraficas->contactos));

    // --------------- LIBERAR RECURSOS GRAFICOS COMUNES ---------------

    recursosComunesAutenticacionRegistro_liberar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- LIBERAR SOCKET ---------------

    socket_cerrar (&(contextoAplicacion->sock));
    socket_finalizar ();

    // --------------- LIBERAR RENDERIZADO ---------------

    if (contextoAplicacion->renderizado != NULL)
        sfRenderWindow_destroy (contextoAplicacion->renderizado);


    system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.
    printf ("-LIBERACION EXITOSA-\n");
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
* Inicializar con valores nulos todos los recursos de la aplicacion.
* Evita problemas en la liberacion de recursos en caso de errores.
*/
static void inicializarValoresNulosAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    // --------------- CONTEXTO DE LA APLICACION ---------------
    contextoAplicacion->renderizado = NULL;
    contextoAplicacion->sock = INVALID_SOCKET;

    // --------------- RECURSOS GRAFICOS COMUNES ---------------
    recursosComunesAutenticacionRegistro_inicializarValoresNulos (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- INTERFACES GRAFICAS ---------------
    interfazContactos_inicializarValoresNulos (&(interfacesGraficas->contactos));
    interfazAutenticacion_inicializarValoresNulos (&(interfacesGraficas->autenticacion));
    interfazRegistro_inicializarValoresNulos (&(interfacesGraficas->registro));
}


static bool usuarioSeAutentico (t_contextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->interfazActual == INTERFAZ_CONTACTOS);
}

static void liberarRecursosGraficosAutenticacion (t_interfacesGraficas *interfacesGraficas)
{
    recursosComunesAutenticacionRegistro_liberar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazAutenticacion_liberar (&(interfacesGraficas->autenticacion));
    interfazRegistro_liberar (&(interfacesGraficas->registro));
}

static void cambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    liberarRecursosGraficosAutenticacion (interfacesGraficas);
    interfazContactos_prepararInterfaz (contextoAplicacion, &(interfacesGraficas->contactos));
}


static bool usuarioSalioDelMenuPrincipal (t_contextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->interfazActual != INTERFAZ_CONTACTOS);
}

static void prepararInterfacesAutenticacion (sfRenderWindow *renderizado, t_interfacesGraficas *interfacesGraficas)
{
    sfRenderWindow_setSize (renderizado, (sfVector2u){500, 620});

    recursosComunesAutenticacionRegistro_inicializar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazAutenticacion_inicializar (&(interfacesGraficas->autenticacion));
    interfazRegistro_inicializar (&(interfacesGraficas->registro));

    recursosComunesAutenticacionRegistro_configurar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazAutenticacion_configurar (&(interfacesGraficas->autenticacion), &(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazRegistro_configurar (&(interfacesGraficas->registro), &(interfacesGraficas->recursosComunesAutenticacionRegistro));

    sfRenderWindow_setView (renderizado, interfacesGraficas->recursosComunesAutenticacionRegistro.vistas.ui);

    sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfacesGraficas->recursosComunesAutenticacionRegistro.textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfacesGraficas->recursosComunesAutenticacionRegistro.textos.feedbackUsuario, 0, 440, 500, 130);
}

static void cambiarDeInterfaz (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    if (contextoAplicacion->interfazActual == INTERFAZ_AUTENTICACION)
        prepararInterfacesAutenticacion (contextoAplicacion->renderizado, interfacesGraficas);
}

