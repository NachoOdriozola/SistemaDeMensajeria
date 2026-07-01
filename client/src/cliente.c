#include "../include/cliente.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void inicializarValoresNulosAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

static bool usuarioSeAutentico (t_contextoAplicacion *contextoAplicacion);
static bool usuarioQuiereAbrirConfiguraciones (t_contextoAplicacion *contextoAplicacion);
static bool usuarioQuiereSalirConfiguraciones (t_contextoAplicacion *contextoAplicacion);

static void cambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);
static void cambiarAInterfazConfig (t_interfazConfig *interfazConfig);
static void salirInterfazConfig (t_interfazConfig *interfazConfig);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


t_codigoRetorno inicializarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    printf ("-INICIALIZANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- INICIALIZAR VALORES NULOS DE LA APLICACION ---------------

    inicializarValoresNulosAplicacion (contextoAplicacion, interfacesGraficas);

    // --------------- INICIALIZAR WINSOCK API ---------------

    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("\nERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }
    contextoAplicacion->estadoWinsock = true;

    // --------------- INICIALIZAR RENDERIZADO ---------------

    contextoAplicacion->renderizado = sfRenderWindow_create ((sfVideoMode){500, 620}, "Aplicacion", sfDefaultStyle, NULL);
    if (!contextoAplicacion->renderizado)
    {
        perror ("\nERROR - Crear renderizado.\n");
        return ERROR_INICIALIZACION;
    }

    // --------------- INICIALIZAR SOCKET DE LA APLICACION ---------------

    struct sockaddr_in dirCliente;
    u_long modoSocket = 0; // Establecer socket en modo NO bloqueante.

    contextoAplicacion->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (contextoAplicacion->sock == INVALID_SOCKET)
    {
        printf ("\nERROR - Crear el socket: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    dirCliente.sin_family = AF_INET;
    dirCliente.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirCliente.sin_addr.s_addr = inet_addr ("127.0.0.1"); // Aceptar conexiones de cualquier direccion IP.
    if (connect (contextoAplicacion->sock, (struct sockaddr*)&(dirCliente), sizeof (dirCliente)) == SOCKET_ERROR)
    {
        printf ("\nERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    ioctlsocket (contextoAplicacion->sock, FIONBIO, &modoSocket);
    printf ("-CONECTADO CON EL SERVIDOR-\t");

    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ---------------

    if (recursosComunesContactosSalas_inicializar (&(interfacesGraficas->recursosComunesContactosSalas)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos comunes contactos-salas.\n");
        return ERROR_INICIALIZACION;
    }

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

    if (interfazSalas_inicializar (&(interfacesGraficas->salas)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de salas.\n");
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
    contextoAplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;
    omitirEventosPendientes (contextoAplicacion->renderizado);

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS COMUNES ---------------

    recursosComunesContactosSalas_configurar (&(interfacesGraficas->recursosComunesContactosSalas));
    recursosComunesAutenticacionRegistro_configurar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- CONFIGURAR LOS RECURSOS GRAFICOS DE LAS INTERFACES Y ASIGNAR LOS RECURSOS COMUNES ---------------

    interfazContactos_configurar (&(interfacesGraficas->contactos), &(interfacesGraficas->recursosComunesContactosSalas));
    interfazSalas_configurar (&(interfacesGraficas->salas), &(interfacesGraficas->recursosComunesContactosSalas));
    interfazAutenticacion_configurar (&(interfacesGraficas->autenticacion), &(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazRegistro_configurar (&(interfacesGraficas->registro), &(interfacesGraficas->recursosComunesAutenticacionRegistro));


    printf ("-CONFIGURACION EXITOSA-\n");
}

void ejecutarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    switch (contextoAplicacion->usuario.interfazActual)
        {
        case INTERFAZ_AUTENTICACION:
            ejecutarInterfazAutenticacion (contextoAplicacion, &(interfacesGraficas->autenticacion));
            if (usuarioSeAutentico (contextoAplicacion))
                cambiarAInterfazContactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_REGISTRO:
            ejecutarInterfazRegistro (contextoAplicacion, &(interfacesGraficas->registro));
            if (usuarioSeAutentico (contextoAplicacion))
                cambiarAInterfazContactos (contextoAplicacion, interfacesGraficas);
            break;

        case INTERFAZ_CONTACTOS:
            ejecutarInterfazContactos (contextoAplicacion, &(interfacesGraficas->contactos));
            if (usuarioQuiereAbrirConfiguraciones (contextoAplicacion))
                cambiarAInterfazConfig (&(interfacesGraficas->config));
            break;

        case INTERFAZ_SALAS:
            ejecutarInterfazSalas (contextoAplicacion, &(interfacesGraficas->salas));
            if (usuarioQuiereAbrirConfiguraciones (contextoAplicacion))
                cambiarAInterfazConfig (&(interfacesGraficas->config));
            break;

        case INTERFAZ_CONFIG:
            ejecutarInterfazConfig (contextoAplicacion, &(interfacesGraficas->config));
            if (usuarioQuiereSalirConfiguraciones (contextoAplicacion))
                salirInterfazConfig (&(interfacesGraficas->config));
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
    interfazSalas_liberar (&(interfacesGraficas->salas));

    // --------------- LIBERAR RECURSOS GRAFICOS COMUNES ---------------

    recursosComunesContactosSalas_liberar (&(interfacesGraficas->recursosComunesContactosSalas));
    recursosComunesAutenticacionRegistro_liberar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- LIBERAR SOCKET DE LA APLICACION ---------------

    if (contextoAplicacion->sock != INVALID_SOCKET)
        closesocket (contextoAplicacion->sock);

    // --------------- LIBERAR RENDERIZADO ---------------

    if (contextoAplicacion->renderizado != NULL)
        sfRenderWindow_destroy (contextoAplicacion->renderizado);

    // --------------- LIBERAR WINSOCK API ---------------

    if (contextoAplicacion->estadoWinsock == true)
        WSACleanup ();


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
    contextoAplicacion->estadoWinsock = false;
    contextoAplicacion->renderizado = NULL;
    contextoAplicacion->sock = INVALID_SOCKET;

    // --------------- RECURSOS GRAFICOS COMUNES ---------------
    recursosComunesContactosSalas_inicializarValoresNulos (&(interfacesGraficas->recursosComunesContactosSalas));
    recursosComunesAutenticacionRegistro_inicializarValoresNulos (&(interfacesGraficas->recursosComunesAutenticacionRegistro));

    // --------------- INTERFACES GRAFICAS ---------------
    interfazContactos_inicializarValoresNulos (&(interfacesGraficas->contactos));
    interfazSalas_inicializarValoresNulos (&(interfacesGraficas->salas));
    interfazAutenticacion_inicializarValoresNulos (&(interfacesGraficas->autenticacion));
    interfazRegistro_inicializarValoresNulos (&(interfacesGraficas->registro));
}


static bool usuarioSeAutentico (t_contextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->usuario.interfazActual == INTERFAZ_CONTACTOS);
}

static bool usuarioQuiereAbrirConfiguraciones (t_contextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->usuario.interfazActual == INTERFAZ_CONFIG);
}

static bool usuarioQuiereSalirConfiguraciones (t_contextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->usuario.interfazActual != INTERFAZ_CONFIG);
}


static void liberarRecursosGraficosAutenticacion (t_interfacesGraficas *interfacesGraficas)
{
    recursosComunesAutenticacionRegistro_liberar (&(interfacesGraficas->recursosComunesAutenticacionRegistro));
    interfazAutenticacion_liberar (&(interfacesGraficas->autenticacion));
    interfazRegistro_liberar (&(interfacesGraficas->registro));
}

static void prepararInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    MAXIMIZAR_VENTANA (sfRenderWindow_getSystemHandle (contextoAplicacion->renderizado), SW_MAXIMIZE);
    recursosComunesContactosSalas_establecerNombreUsuario (&(interfacesGraficas->recursosComunesContactosSalas), contextoAplicacion->usuario.nombre);
    recursosComunesContactosSalas_posicionarNombreUsuario (&(interfacesGraficas->recursosComunesContactosSalas));
}

static void cambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas)
{
    liberarRecursosGraficosAutenticacion (interfacesGraficas);
    prepararInterfazContactos (contextoAplicacion, interfacesGraficas);
}

static void cambiarAInterfazConfig (t_interfazConfig *interfazConfig)
{
    interfazConfig_inicializar (interfazConfig);
    interfazConfig_configurar (interfazConfig);
}

static void salirInterfazConfig (t_interfazConfig *interfazConfig)
{
    interfazConfig_liberar (interfazConfig);
}
