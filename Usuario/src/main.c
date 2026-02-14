#include "../include/main.h"



/* ============================
   MAIN
   ============================ */



int main()
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    t_contextoAplicacion contextoAplicacion;
    t_interfaces interfaces;


    // --------------- INICIALIZAR Y CONFIGURAR LOS RECURSOS DE LA APLICACION ---------------


    if (inicializarAplicacion (&contextoAplicacion, &interfaces) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar los recursos de la aplicacion.\n");
        liberarAplicacion (&contextoAplicacion, &interfaces);
        return ERROR_INICIALIZACION;
    }
    configurarAplicacion (&contextoAplicacion, &interfaces);

    if (iniciarAutenticacionManual (&contextoAplicacion, &interfaces) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos para autenticacion manual.\n");
        liberarAplicacion (&contextoAplicacion, &interfaces);
        return ERROR_INICIALIZACION;
    }


    // --------------- EJECUCION DEL BUCLE PRINCIPAL: funciones de las interfaces ---------------

    while (sfRenderWindow_isOpen (contextoAplicacion.renderizado))
    {
        switch (contextoAplicacion.usuario.interfazActual)
        {

        case INTERFAZ_AUTENTICACION:
            interfazAutenticacion_accion (&contextoAplicacion, &(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.autenticacion));
            interfazAutenticacion_actualizar (&(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.autenticacion));
            interfazAutenticacion_renderizar (contextoAplicacion.renderizado, &(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.autenticacion));
            if (contextoAplicacion.usuario.interfazActual == INTERFAZ_CONTACTOS)
            {
                iniciarMenuPrincipal (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas));
                recursosComunesAutenticacionRegistro_liberar (&(interfaces.recursosComunesAutenticacionRegistro));
                interfazAutenticacion_liberar (&(interfaces.autenticacion));
                interfazRegistro_liberar (&(interfaces.registro));
            }
            break;


        case INTERFAZ_REGISTRO:
            interfazRegistro_accion (&contextoAplicacion, &(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.registro));
            interfazRegistro_actualizar (&(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.registro));
            interfazRegistro_renderizar (contextoAplicacion.renderizado, &(interfaces.recursosComunesAutenticacionRegistro), &(interfaces.registro));
            if (contextoAplicacion.usuario.interfazActual == INTERFAZ_CONTACTOS)
            {
                iniciarMenuPrincipal (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas));
                recursosComunesAutenticacionRegistro_liberar (&(interfaces.recursosComunesAutenticacionRegistro));
                interfazAutenticacion_liberar (&(interfaces.autenticacion));
                interfazRegistro_liberar (&(interfaces.registro));
            }
            break;


        case INTERFAZ_CONTACTOS:
            interfazContactos_accion (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas), &(interfaces.contactos));
            interfazContactos_actualizar (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas), &(interfaces.contactos));
            interfazContactos_renderizar (contextoAplicacion.renderizado, &(interfaces.recursosComunesContactosSalas), &(interfaces.contactos));
            if (contextoAplicacion.usuario.interfazActual == INTERFAZ_CONFIG)
            {
                interfazConfig_inicializar (&(interfaces.config));
                interfazConfig_configurar (&(interfaces.config));
            }
            break;


        case INTERFAZ_SALAS:
            interfazSalas_accion (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas), &(interfaces.salas));
            interfazSalas_actualizar (&contextoAplicacion, &(interfaces.recursosComunesContactosSalas), &(interfaces.salas));
            interfazSalas_renderizar (contextoAplicacion.renderizado, &(interfaces.recursosComunesContactosSalas), &(interfaces.salas));
            if (contextoAplicacion.usuario.interfazActual == INTERFAZ_CONFIG)
            {
                interfazConfig_inicializar (&(interfaces.config));
                interfazConfig_configurar (&(interfaces.config));
            }
            break;


        case INTERFAZ_CONFIG:
            interfazConfig_accion (&contextoAplicacion, &(interfaces.config));
            interfazConfig_actualizar (&(interfaces.config));
            interfazConfig_renderizar (contextoAplicacion.renderizado, &(interfaces.config));
            if (contextoAplicacion.usuario.interfazActual != INTERFAZ_CONFIG)
                interfazConfig_liberar (&(interfaces.config));
            break;
        }
    }


    // --------------- LIBERAR LOS RECURSOS DE LA APLICACION ---------------


    liberarAplicacion (&contextoAplicacion, &interfaces);
    //system ("pause");

    return EXITO;
}



/* ============================
   FUNCIONES ESTRUCTURALES BASE
   ============================ */



int inicializarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces)
{
    printf ("-INICIALIZANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoAplicacion->estadoWinsock = false;
    contextoAplicacion->renderizado = NULL;
    contextoAplicacion->sock = INVALID_SOCKET;


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


    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ESENCIALES ---------------

    if (recursosComunesContactosSalas_inicializar (&(interfaces->recursosComunesContactosSalas)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos comunes contactos-salas.\n");
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR INTERFACES GRAFICAS ESENCIALES ---------------

    // Interfaz grafica de contactos

    if (interfazContactos_inicializar (&(interfaces->contactos)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de contactos.\n");
        return ERROR_INICIALIZACION;
    }


    // Interfaz grafica de salas

    if (interfazSalas_inicializar (&(interfaces->salas)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de salas.\n");
        return ERROR_INICIALIZACION;
    }


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

void configurarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces)
{
    printf ("-CONFIGURANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- CONFIGURAR RENDERIZADO ---------------

    sfRenderWindow_setFramerateLimit (contextoAplicacion->renderizado, 60);


    // --------------- CONFIGURAR Y ESTABLECER UN TAMANIO Y UNA POSICION SOBRE LA VENTANA A LOS RECURSOS GRAFICOS COMUNES ESENCIALES ---------------

    recursosComunesContactosSalas_configurar (&(interfaces->recursosComunesContactosSalas));


    // --------------- CONFIGURAR Y ESTABLECER UN TAMANIO Y UNA POSICION SOBRE LA VENTANA A LAS INTERFACES GRAFICAS ESENCIALES ---------------

    // Interfaz grafica de contactos

    interfazContactos_configurar (&(interfaces->contactos), &(interfaces->recursosComunesContactosSalas.fuentes));


    // Interfaz grafica de salas

    interfazSalas_configurar (&(interfaces->salas), &(interfaces->recursosComunesContactosSalas.fuentes));


    printf ("-CONFIGURACION EXITOSA-\n");
}

void liberarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces)
{
    printf ("-LIBERANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- LIBERAR INTERFACES GRAFICAS ESENCIALES ---------------

    // Interfaz grafica de contactos

    interfazContactos_liberar (&(interfaces->contactos));


    // Interfaz grafica de salas

    interfazSalas_liberar (&(interfaces->salas));


    // --------------- LIBERAR INTERFACES GRAFICAS DE AUTENTICACION ---------------

    // Interfaz grafica de autenticacion

    interfazAutenticacion_liberar (&(interfaces->autenticacion));


    // Interfaz grafica de registro

    interfazRegistro_liberar (&(interfaces->registro));


    // --------------- LIBERAR RECURSOS GRAFICOS COMUNES ---------------

    // Recursos graficos comunes entre interfaces de contactos y salas

    recursosComunesContactosSalas_liberar (&(interfaces->recursosComunesContactosSalas));


    // Recursos graficos comunes entre las interfaces de autenticacion y registro

    recursosComunesAutenticacionRegistro_liberar (&(interfaces->recursosComunesAutenticacionRegistro));


    // --------------- LIBERAR SOCKET DE LA APLICACION ---------------

    if (contextoAplicacion->sock != INVALID_SOCKET)
        closesocket (contextoAplicacion->sock);


    // --------------- LIBERAR RENDERIZADO ---------------

    if (contextoAplicacion->renderizado != NULL)
        sfRenderWindow_destroy (contextoAplicacion->renderizado);


    // --------------- LIBERAR WINSOCK API ---------------

    if (contextoAplicacion->estadoWinsock == true)
        WSACleanup ();


    printf ("-LIBERACION EXITOSA-\n");
}



/* ============================
   FUNCIONES DE INICIO
   ============================ */



void iniciarMenuPrincipal (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR APLICACION ---------------

    contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    sfText_setString (recursosComunesContactosSalas->textos.nombreUsuario, contextoAplicacion->usuario.nombre);
    posicionarNombreUsuario (recursosComunesContactosSalas->textos.nombreUsuario);


    // --------------- MAXIMIZAR VENTANA ---------------

    ShowWindow (sfRenderWindow_getSystemHandle (contextoAplicacion->renderizado), SW_MAXIMIZE);
}

int iniciarAutenticacionManual (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces)
{
    // --------------- CONFIGURAR APLICACION ---------------

    contextoAplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;


    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES DE AUTENTICACION ---------------

    if (recursosComunesAutenticacionRegistro_inicializar (&(interfaces->recursosComunesAutenticacionRegistro)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar recursos comunes autenticacion-registro.\n");
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR INTERFACES GRAFICAS DE AUTENTICACION ---------------

    // Interfaz grafica de autenticacion

    if (interfazAutenticacion_inicializar (&(interfaces->autenticacion)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de autenticacion.\n");
        return ERROR_INICIALIZACION;
    }


    // Interfaz grafica de registro

    if (interfazRegistro_inicializar (&(interfaces->registro)) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar interfaz de salas.\n");
        return ERROR_INICIALIZACION;
    }


    // --------------- CONFIGURAR Y ESTABLECER UN TAMANIO Y UNA POSICION SOBRE LA VENTANA A LOS RECURSOS GRAFICOS COMUNES DE AUTENTICACION ---------------

    recursosComunesAutenticacionRegistro_configurar (&(interfaces->recursosComunesAutenticacionRegistro));


    // --------------- CONFIGURAR Y ESTABLECER UN TAMANIO Y UNA POSICION SOBRE LA VENTANA A LAS INTERFACES GRAFICAS DE AUTENTICACION ---------------

    // Interfaz grafica de autenticacion

    interfazAutenticacion_configurar (&(interfaces->autenticacion), &(interfaces->recursosComunesAutenticacionRegistro.fuentes));


    // Interfaz grafica de registro

    interfazRegistro_configurar (&(interfaces->registro), &(interfaces->recursosComunesAutenticacionRegistro.fuentes));


    return EXITO;
}





























