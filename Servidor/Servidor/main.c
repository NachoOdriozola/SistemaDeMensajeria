#include "main.h"

int main ()
{
    s_servidor servidor;
    sqlite3 *db;
    WSADATA wsaData;

    char ingresoTeclaApagar = '\0';
    char bufferSolicitud [MAX_BUFFER_SOLICITUD];
    char solicitud;


    ///INICIALIZAR WINSOCK
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }


    if (inicializar (&servidor, &db) == ERROR_INICIALIZACION)
    {
        liberar (&servidor, db);
        return ERROR_INICIALIZACION;
    }
    if (setup (&servidor) == ERROR_INICIALIZACION)
    {
        liberar (&servidor, db);
        return ERROR_INICIALIZACION;
    }


    printf ("SERVIDOR INICIADO CORRECTAMENTE.\n\n");
    printf ("Presione la tecla '%c' para apagar el servidor.\n", TECLA_APAGAR_SERVIDOR);

    while (ingresoTeclaApagar != TECLA_APAGAR_SERVIDOR)
    {
        aceptarCliente (&servidor);

        if (recibirSolicitud (&servidor, bufferSolicitud, &solicitud) == SOLICITUD_RECIBIDA)
        {
            printf ("Recibido: %c|%s\n", solicitud, bufferSolicitud);
            switch (solicitud)
            {
            case INDICE_INICIO_SESION:
                procesarInicioSesion (&servidor, db, bufferSolicitud);
                break;

            case INDICE_REGISTRO:
                procesarRegistro (&servidor, db, bufferSolicitud);
                break;

            case INDICE_MENSAJE:
                break;

            case INDICE_SOLICITUD_AMISTAD:
                procesarSolicitudAmistad (&servidor, db, bufferSolicitud);
                break;

            case INDICE_NOTIFICACIONES:
                procesarNotificaciones (&servidor, db, bufferSolicitud);
                break;
            }
        }

        if (kbhit ())
        {
            ingresoTeclaApagar = getch ();
            ingresoTeclaApagar = toupper (ingresoTeclaApagar);
            if (ingresoTeclaApagar != TECLA_APAGAR_SERVIDOR)
                    printf ("Tecla incorrecta.\nPresione la tecla '%c' para apagar el servidor.\n", TECLA_APAGAR_SERVIDOR);
        }

        Sleep (10);
    }

    liberar (&servidor, db);

    system ("pause");

    return OK;
}


///FUNCIONES ESTRUCTURALES


int inicializar (s_servidor *servidor, sqlite3 **db)
{
    printf ("INICIALIZANDO SERVIDOR.\n");


    ///INICIALIZAR SERVIDOR
    servidor->sockServidor = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servidor->sockServidor == INVALID_SOCKET)
    {
        printf ("ERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR LISTA DE CLIENTES
    crearLista (&(servidor->listaClientes));


    ///INICIALIZAR BASE DE DATOS
    int resultado;

    resultado = sqlite3_open ("DBappMensajes.db", db);
    if (resultado)
    {
        printf ("ERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*db));
        return ERROR_INICIALIZACION;
    }
    printf ("BASE DE DATOS ABIERTA CORRECTAMENTE.\n");


    return OK;
}

int setup (s_servidor *servidor)
{
    printf ("SETUP DE SERVIDOR.\n");


    ///SETUP SERVIDOR

    struct sockaddr_in dirServidor;
    u_long modoSocket = 1; //modo no bloqueante

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons (PUERTO); //Escucha en este puerto
    dirServidor.sin_addr.s_addr = INADDR_ANY; //Acepta cualquier direccion IP
    if (bind (servidor->sockServidor, (struct sockaddr*)(&dirServidor), sizeof (dirServidor)) == SOCKET_ERROR)
    {
        printf ("ERROR - Bind socket al servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    if (listen (servidor->sockServidor, SOMAXCONN) == SOCKET_ERROR)
    {
        printf ("ERROR - Listen socket del servidor %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    ioctlsocket (servidor->sockServidor, FIONBIO, &modoSocket);


    return OK;
}

void liberar (s_servidor *servidor, sqlite3 *db)
{
    vaciarListaConAccion (&(servidor->listaClientes), liberarCliente);
    sqlite3_close (db);
    closesocket (servidor->sockServidor);
    WSACleanup ();
}












