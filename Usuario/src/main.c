#include "../include/main.h"



/* ============================
   MAIN
   ============================ */



int main()
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    s_aplicacion aplicacion;
    s_interfaces interfaces;


    // --------------- INICIALIZAR Y CONFIGURAR LOS RECURSOS DE LA APLICACION ---------------


    if (inicializarAplicacion (&aplicacion, &interfaces) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializar los recursos de la aplicacion.\n");
        return ERROR_INICIALIZACION;
    }
    configurarAplicacion (&aplicacion, &interfaces);


    if (verificarModoAutenticacion (&(aplicacion.usuario)) == AUTENTICACION_AUTOMATICA)
        iniciarMenuPrincipal (&aplicacion, &interfaces);
    else
    {
        if (iniciarAutenticacionManual (&aplicacion, &interfaces) == ERROR_INICIALIZACION)
        {
            perror ("\nERROR - Inicializar recursos para autenticacion manual.\n");
            liberarAplicacion (&aplicacion, &interfaces);
            return ERROR_INICIALIZACION;
        }
    }


    // --------------- EJECUCION DEL BUCLE PRINCIPAL: funciones de las interfaces ---------------

    //sfRenderWindow_close ()
    while (aplicacion.aplicacionEjecutandose == CONTINUAR_APLICACION)
    {
        switch (aplicacion.usuario.interfazActual)
        {

        case INTERFAZ_AUTENTICACION:
            interfazAutenticacion_accion (&aplicacion, &(interfaces.autenticacion), &(interfaces.recursosComunesAutenticacionRegistro));
            interfazAutenticacion_actualizar (&(interfaces.autenticacion), &(interfaces.recursosComunesAutenticacionRegistro));
            interfazAutenticacion_renderizar (aplicacion.renderizado, &(interfaces.autenticacion), &(interfaces.recursosComunesAutenticacionRegistro));
            if (aplicacion.usuario.interfazActual == INTERFAZ_CONTACTOS)
            {
                iniciarMenuPrincipal (&aplicacion, &interfaces);
                recursosComunesAutenticacionRegistro_liberar (&(interfaces.recursosComunesAutenticacionRegistro));
                interfazAutenticacion_liberar (&(interfaces.autenticacion));
                interfazRegistro_liberar (&(interfaces.registro));
            }
            break;


        case INTERFAZ_REGISTRO:
            interfazRegistro_accion (&aplicacion, &(interfaces.registro), &(interfaces.recursosComunesAutenticacionRegistro));
            interfazRegistro_actualizar (&(interfaces.registro), &(interfaces.recursosComunesAutenticacionRegistro));
            interfazRegistro_renderizar (aplicacion.renderizado, &(interfaces.registro), &(interfaces.recursosComunesAutenticacionRegistro));
            if (aplicacion.usuario.interfazActual == INTERFAZ_CONTACTOS)
            {
                iniciarMenuPrincipal (&aplicacion, &interfaces);
                recursosComunesAutenticacionRegistro_liberar (&(interfaces.recursosComunesAutenticacionRegistro));
                interfazAutenticacion_liberar (&(interfaces.autenticacion));
                interfazRegistro_liberar (&(interfaces.registro));
            }
            break;


        case INTERFAZ_CONTACTOS:
            interfazContactos_accion (&aplicacion, &(interfaces.contactos), &(interfaces.recursosComunesContactosSalas));
            interfazContactos_actualizar (&aplicacion, &(interfaces.contactos), &(interfaces.recursosComunesContactosSalas));
            interfazContactos_renderizar (&aplicacion, &(interfaces.contactos), &(interfaces.recursosComunesContactosSalas));
            if (aplicacion.usuario.interfazActual == INTERFAZ_CONFIG)
            {
                interfazConfig_inicializar (&(interfaces.config));
                interfazConfig_configurar (&(interfaces.config), &(aplicacion.mensajes.fuentes), &(aplicacion.ventana));
            }
            break;


        case INTERFAZ_SALAS:
            interfazSalas_accion (&aplicacion, &(interfaces.salas), &(interfaces.recursosComunesContactosSalas));
            interfazSalas_actualizar (&aplicacion, &(interfaces.salas), &(interfaces.recursosComunesContactosSalas));
            interfazSalas_renderizar (&aplicacion, &(interfaces.salas), &(interfaces.recursosComunesContactosSalas));
            if (aplicacion.usuario.interfazActual == INTERFAZ_CONFIG)
            {
                interfazConfig_inicializar (&(interfaces.config));
                interfazConfig_configurar (&(interfaces.config), &(aplicacion.mensajes.fuentes), &(aplicacion.ventana));
            }
            break;


        case INTERFAZ_CONFIG:
            interfazConfig_accion (&aplicacion, &(interfaces.config));
            interfazConfig_actualizar (&(interfaces.config));
            interfazConfig_renderizar (aplicacion.renderizado, &(interfaces.config));
            if (aplicacion.usuario.interfazActual != INTERFAZ_CONFIG)
                interfazConfig_liberar (&(interfaces.config));
            break;
        }
    }


    // --------------- LIBERAR LOS RECURSOS DE LA APLICACION ---------------


    liberarAplicacion (&aplicacion, &interfaces);
    system ("pause");

    return EXITO;
}



/* ============================
   FUNCIONES ESTRUCTURALES BASE
   ============================ */



int inicializarAplicacion (s_aplicacion *aplicacion, s_interfaces *interfaces)
{
    printf ("-INICIALIZANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- INICIALIZAR WINSOCK API ---------------

    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("\nERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR RENDERIZADO ---------------

    aplicacion->renderizado = sfRenderWindow_create ((sfVideoMode){560, 660}, "Aplicacion", sfDefaultStyle, NULL);
    if (!aplicacion->renderizado)
    {
        perror ("\nERROR - Crear renderizado.\n");
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR SOCKET DE LA APLICACION ---------------

    struct sockaddr_in dirCliente;
    u_long modoSocket = 0; // Establecer socket en modo NO bloqueante.

    aplicacion->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (aplicacion->sock == INVALID_SOCKET)
    {
        printf ("\nERROR - Crear el socket: %d.\n", WSAGetLastError ());
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }

    dirCliente.sin_family = AF_INET;
    dirCliente.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirCliente.sin_addr.s_addr = inet_addr ("127.0.0.1"); // Aceptar conexiones de cualquier direccion IP.
    if (connect (aplicacion->sock, (struct sockaddr*)&(dirCliente), sizeof (dirCliente)) == SOCKET_ERROR)
    {
        printf ("\nERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        closesocket (aplicacion->sock);
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }
    ioctlsocket (aplicacion->sock, FIONBIO, &modoSocket);
    printf ("-CONECTADO CON EL SERVIDOR-\t");


    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ---------------

    if (recursosComunesContactosSalas_inicializar (&(interfaces->recursosComunesContactosSalas)) == ERROR_INICIALIZACION)
    {
        closesocket (aplicacion->sock);
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR INTERFACES GRAFICAS ESENCIALES ---------------

    // Interfaz grafica de contactos

    if (interfazContactos_inicializar (&(interfaces->contactos)) == ERROR_INICIALIZACION)
    {
        recursosComunesContactosSalas_liberar (&(interfaces->recursosComunesContactosSalas));
        closesocket (aplicacion->sock);
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }


    // Interfaz grafica de salas

    if (interfazSalas_inicializar (&(interfaces->salas)) == ERROR_INICIALIZACION)
    {
        interfazContactos_liberar (&(interfaces->contactos));
        recursosComunesContactosSalas_liberar (&(interfaces->recursosComunesContactosSalas));
        closesocket (aplicacion->sock);
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR FUENTES ---------------

    if (inicializarFuentes (&(aplicacion->mensajes.fuentes)) == ERROR_INICIALIZACION)
    {
        interfazSalas_liberar (&(interfaces->salas));
        interfazContactos_liberar (&(interfaces->contactos));
        recursosComunesContactosSalas_liberar (&(interfaces->recursosComunesContactosSalas));
        closesocket (aplicacion->sock);
        sfRenderWindow_destroy (aplicacion->renderizado);
        WSACleanup ();
        return ERROR_INICIALIZACION;
    }


    // --------------- CREAR E INICIALIZAR LISTA DE MENSAJES ---------------

    unsigned short int i;
    sfText *mensajes [MAX_MENSAJES_MEMORIA];

    crearListaCircular (&(aplicacion->mensajes.listaMensajes));
    for (i = 0; i < MAX_MENSAJES_MEMORIA; i ++)
    {
        mensajes[i] = sfText_create ();
        if (!mensajes[i])
        {
            printf ("\nERROR - No se pudo crear mensaje[%u].\n", i);
            vaciarListaCircularConAccion (&(aplicacion->mensajes.listaMensajes), liberarMensaje);
            liberarFuentes (&(aplicacion->mensajes.fuentes));
            interfazSalas_liberar (&(interfaces->salas));
            interfazContactos_liberar (&(interfaces->contactos));
            recursosComunesContactosSalas_liberar (&(interfaces->recursosComunesContactosSalas));
            closesocket (aplicacion->sock);
            sfRenderWindow_destroy (aplicacion->renderizado);
            WSACleanup ();
            continue;
        }

        insertarSegundoCircular (&(aplicacion->mensajes.listaMensajes), &(mensajes[i]), sizeof (sfText*));
    }


    // --------------- CREAR LISTA DE NOTIFICACIONES ---------------

    crearListaSimple (&(aplicacion->listaNotificaciones));


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

void configurarAplicacion (s_aplicacion *aplicacion, s_interfaces *interfaces)
{
    printf ("-CONFIGURANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- CONFIGURAR APLICACION ---------------

    sfRenderWindow_setFramerateLimit (aplicacion->renderizado, 60);
    aplicacion->aplicacionEjecutandose = CONTINUAR_APLICACION;


    // --------------- CONFIGURAR RECURSOS GRAFICOS COMUNES ---------------

    recursosComunesContactosSalas_configurar (&(interfaces->recursosComunesContactosSalas), &(aplicacion->mensajes.fuentes));


    // --------------- CONFIGURAR INTERFACES GRAFICAS ESENCIALES ---------------

    // Interfaz grafica de contactos
    interfazContactos_configurar (&(interfaces->contactos), &(aplicacion->mensajes.fuentes));

    // Interfaz grafica de salas
    interfazSalas_configurar (&(interfaces->salas), &(aplicacion->mensajes.fuentes));


    // --------------- CONFIGURAR LISTA DE MENSAJES ---------------
    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), aplicacion->mensajes.fuentes.fuente1, setupListaMensajes);
    aplicacion->mensajes.siguienteMensaje = aplicacion->mensajes.listaMensajes;


    printf ("-CONFIGURACION EXITOSA-\n");
}

void liberarAplicacion (s_aplicacion *aplicacion, s_interfaces *interfaces)
{
    printf ("-LIBERANDO LOS RECURSOS DE LA APLICACION-\t");


    // --------------- LIBERAR LISTA DE NOTIFICACIONES ---------------

    vaciarListaSimpleConAccion (&(aplicacion->listaNotificaciones), liberarNotificacion);


    // --------------- LIBERAR LISTA DE MENSAJES ---------------

    vaciarListaCircularConAccion (&(aplicacion->mensajes.listaMensajes), liberarMensaje);


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


    // --------------- LIBERAR FUENTES ---------------

    liberarFuentes (&(aplicacion->mensajes.fuentes));


    // --------------- LIBERAR SOCKET DE LA APLICACION ---------------

    closesocket (aplicacion->sock);


    // --------------- LIBERAR RENDERIZADO ---------------

    sfRenderWindow_destroy (aplicacion->renderizado);


    // --------------- LIBERAR WINSOCK API ---------------

    WSACleanup ();


    printf ("-LIBERACION EXITOSA-\n");
}



/* ============================
   FUNCIONES DE INICIO
   ============================ */



void iniciarMenuPrincipal (s_aplicacion *aplicacion, s_interfaces *interfaces)
{
    // --------------- CONFIGURAR APLICACION ---------------

    aplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
    sfText_setString (interfaces->recursosComunesContactosSalas.texto.nombreUsuario, aplicacion->usuario.nombre);


    // --------------- CONFIGURAR VENTANA ---------------

    maximizadoAutomaticoVentana (aplicacion->renderizado, &(aplicacion->ventana));


    // --------------- CONFIGURAR VISTAS DE LOS RECURSOS GRAFICOS COMUNES ESENCIALES ---------------

    recursosComunesContactosSalas_tamVistas (&(interfaces->recursosComunesContactosSalas.vistas), &(aplicacion->ventana));


    // --------------- CONFIGURAR TAMANIO Y POSICION SOBRE LA VENTANA DE LOS RECURSOS GRAFICOS COMUNES ESENCIALES ---------------

    recursosComunesContactosSalas_tamYPosVentana (&(interfaces->recursosComunesContactosSalas), &(aplicacion->ventana));


    // --------------- CONFIGURAR TAMANIO Y POSICION SOBRE LA VENTANA DE LOS RECURSOS GRAFICOS ESENCIALES ---------------

    interfazContactos_tamYPosVentana (&(interfaces->contactos), &(aplicacion->ventana));
    interfazSalas_tamYPosVentana (&(interfaces->salas), &(aplicacion->ventana));
    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), &(aplicacion->ventana.escalaPixeles), tamListaMensajes);
}

int iniciarAutenticacionManual (s_aplicacion *aplicacion, s_interfaces *interfaces)
{
    // --------------- CONFIGURAR APLICACION ---------------

    aplicacion->usuario.interfazActual = INTERFAZ_AUTENTICACION;


    // --------------- INICIALIZAR RECURSOS GRAFICOS COMUNES ---------------

    if (recursosComunesAutenticacionRegistro_inicializar (&(interfaces->recursosComunesAutenticacionRegistro)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // --------------- INICIALIZAR INTERFACES GRAFICAS DE AUTENTICACION ---------------

    // Interfaz gráfica de autenticacion

    if (interfazAutenticacion_inicializar (&(interfaces->autenticacion)) == ERROR_INICIALIZACION)
    {
        recursosComunesAutenticacionRegistro_liberar (&(interfaces->recursosComunesAutenticacionRegistro));
        return ERROR_INICIALIZACION;
    }

    // Interfaz gráfica de registro

    if (interfazRegistro_inicializar (&(interfaces->registro)) == ERROR_INICIALIZACION)
    {
        interfazAutenticacion_liberar (&(interfaces->autenticacion));
        recursosComunesAutenticacionRegistro_liberar (&(interfaces->recursosComunesAutenticacionRegistro));
        return ERROR_INICIALIZACION;
    }


    // --------------- CONFIGURAR INTERFACES GRAFICAS DE AUTENTICACIÓN ---------------

    recursosComunesAutenticacionRegistro_configurar (&(interfaces->recursosComunesAutenticacionRegistro), &(aplicacion->mensajes.fuentes));
    interfazAutenticacion_configurar (&(interfaces->autenticacion), &(aplicacion->mensajes.fuentes));
    interfazRegistro_configurar (&(interfaces->registro), &(aplicacion->mensajes.fuentes));


    return EXITO;
}





























