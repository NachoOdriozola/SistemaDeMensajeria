#include "logica/cliente.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void inicializar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);

static bool usuario_se_autentico (ContextoAplicacion *contextoAplicacion);
static void cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);

static bool usuario_salio_ui_contactos (ContextoAplicacion *contextoAplicacion);
static void cambiar_ui (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno aplicacion_inicializar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    printf ("-INICIALIZANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- INICIALIZAR VALORES NULOS DE LA APLICACION ---------------

    inicializar (contextoAplicacion, interfacesGraficas);

    // --------------- INICIALIZAR SOCKET ---------------

    if (socket_inicializar () == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // --------------- INICIALIZAR RENDERIZADO ---------------

    contextoAplicacion->renderizado = sfRenderWindow_create ((sfVideoMode){500, 620}, "Aplicacion", sfDefaultStyle, sfWindowed, NULL);
    if (!contextoAplicacion->renderizado)
    {
        perror ("\nERROR - Crear renderizado.\n");
        return ERROR_INICIALIZACION;
    }

    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ---------------

    if (ui_acceso_crear (&(interfacesGraficas->uiAcceso)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos comunes autenticacion-registro.\n");
        return ERROR_INICIALIZACION;
    }

    // --------------- INICIALIZAR INTERFACES GRAFICAS ---------------

    if (ui_contactos_crear (&(interfacesGraficas->uiContactos)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de contactos.\n");
        return ERROR_INICIALIZACION;
    }
    
    if (ui_autenticacion_crear (&(interfacesGraficas->uiAutenticacion), &(interfacesGraficas->uiAcceso)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de autenticacion.\n");
        return ERROR_INICIALIZACION;
    }
    
    if (ui_registro_crear (&(interfacesGraficas->uiRegistro), &(interfacesGraficas->uiAcceso)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de registro.\n");
        return ERROR_INICIALIZACION;
    }

    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

void aplicacion_configurar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    printf ("-CONFIGURANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- CONFIGURAR APLICACION ---------------

    sfRenderWindow_setFramerateLimit (contextoAplicacion->renderizado, 60);
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
    comunicacion_inicializar (contextoAplicacion);
    omitir_eventos_pendientes (contextoAplicacion->renderizado);

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS COMUNES ---------------

    ui_acceso_configurar (&(interfacesGraficas->uiAcceso));

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS DE LAS INTERFACES Y ASIGNAR LOS RECURSOS COMUNES ---------------

    ui_contactos_configurar (&(interfacesGraficas->uiContactos));
    ui_autenticacion_configurar (&(interfacesGraficas->uiAutenticacion));
    ui_registro_configurar (&(interfacesGraficas->uiRegistro));


    printf ("-CONFIGURACION EXITOSA-\n");
}

void aplicacion_ejecutar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    switch (contextoAplicacion->interfazActual)
        {
        case INTERFAZ_AUTENTICACION:
            ui_autenticacion_ejecutar (contextoAplicacion, &(interfacesGraficas->uiAutenticacion));
            if (usuario_se_autentico (contextoAplicacion))
                cambiar_a_ui_contactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_REGISTRO:
            ui_registro_ejecutar (contextoAplicacion, &(interfacesGraficas->uiRegistro));
            if (usuario_se_autentico (contextoAplicacion))
                cambiar_a_ui_contactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_CONTACTOS:
            ui_contactos_ejecutar (contextoAplicacion, &(interfacesGraficas->uiContactos));
            if (usuario_salio_ui_contactos (contextoAplicacion))
                cambiar_ui (contextoAplicacion, interfacesGraficas);
            break;
        }
}

void aplicacion_liberar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    printf ("-LIBERANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- LIBERAR INTERFACES GRAFICAS ---------------

    ui_autenticacion_liberar (&(interfacesGraficas->uiAutenticacion));
    ui_registro_liberar (&(interfacesGraficas->uiRegistro));
    ui_contactos_liberar (&(interfacesGraficas->uiContactos));

    // --------------- LIBERAR RECURSOS GRAFICOS COMUNES ---------------

    ui_acceso_liberar (&(interfacesGraficas->uiAcceso));

    // --------------- LIBERAR SOCKET ---------------

    comunicacion_finalizar (&(contextoAplicacion->sock));
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
static void inicializar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    // --------------- CONTEXTO DE LA APLICACION ---------------
    contextoAplicacion->renderizado = NULL;
    contextoAplicacion->sock = INVALID_SOCKET;

    // --------------- RECURSOS GRAFICOS COMUNES ---------------
    ui_acceso_inicializar (&(interfacesGraficas->uiAcceso));

    // --------------- INTERFACES GRAFICAS ---------------
    ui_contactos_inicializar (&(interfacesGraficas->uiContactos));
    ui_autenticacion_inicializar (&(interfacesGraficas->uiAutenticacion));
    ui_registro_inicializar (&(interfacesGraficas->uiRegistro));
}


static bool usuario_se_autentico (ContextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->interfazActual == INTERFAZ_CONTACTOS);
}

static void liberar_uis_acceso (InterfacesGraficas *interfacesGraficas)
{
    ui_acceso_liberar (&(interfacesGraficas->uiAcceso));
    ui_autenticacion_liberar (&(interfacesGraficas->uiAutenticacion));
    ui_registro_liberar (&(interfacesGraficas->uiRegistro));
}

static void cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    liberar_uis_acceso (interfacesGraficas);
    ui_contactos_preparar (contextoAplicacion, &(interfacesGraficas->uiContactos));
}


static bool usuario_salio_ui_contactos (ContextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->interfazActual != INTERFAZ_CONTACTOS);
}

static void preparar_uis_acceso (sfRenderWindow *renderizado, InterfacesGraficas *interfacesGraficas)
{
    sfRenderWindow_setSize (renderizado, (sfVector2u){500, 620});

    ui_acceso_crear (&(interfacesGraficas->uiAcceso));
    ui_autenticacion_crear (&(interfacesGraficas->uiAutenticacion), &(interfacesGraficas->uiAcceso));
    ui_registro_crear (&(interfacesGraficas->uiRegistro), &(interfacesGraficas->uiAcceso));

    ui_acceso_configurar (&(interfacesGraficas->uiAcceso));
    ui_autenticacion_configurar (&(interfacesGraficas->uiAutenticacion));
    ui_registro_configurar (&(interfacesGraficas->uiRegistro));

    sfRenderWindow_setView (renderizado, interfacesGraficas->uiAcceso.vistas.ui);

    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfacesGraficas->uiAcceso.textos.feedbackUsuario, bufferErrorConexion);
    centrar_texto_en_area (interfacesGraficas->uiAcceso.textos.feedbackUsuario, 0, 440, 500, 130);
}

static void cambiar_ui (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas)
{
    if (contextoAplicacion->interfazActual == INTERFAZ_AUTENTICACION)
        preparar_uis_acceso (contextoAplicacion->renderizado, interfacesGraficas);
}

