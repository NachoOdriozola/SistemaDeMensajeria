#include "../include/logicaAplicacion.h"

int main ()
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    t_servidor servidor;
    t_nodo **clienteAProcesar;
    t_buffersComunicacion buffersComunicacion;
    char ingresoCaracter = '\0';

    t_cliente nuevoCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente;

    tamNuevoCliente = sizeof (dirNuevoCliente);


    // --------------- INICIALIZAR Y CONFIGURAR LOS RECURSOS DEL SERVIDOR ---------------


    if (inicializarServidor (&servidor) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Inicializacion de servidor.\n");
        return ERROR_INICIALIZACION;
    }
    if (configurarServidor (&servidor) == ERROR_CONFIGURACION)
    {
        perror ("ERROR - configuracion de servidor.\n");
        liberarServidor (&servidor);
        return ERROR_CONFIGURACION;
    }
    printf ("-SERVIDOR INICIADO CORRECTAMENTE-\n\n");


    // --------------- EJECUCION DEL BUCLE PRINCIPAL: acepta nuevos clientes, recibe solicitudes y las procesa ---------------


    printf ("Escriba el caracter '%c' para apagar el servidor.\n\n", CARACTER_APAGAR_SERVIDOR);

    while (ingresoCaracter != CARACTER_APAGAR_SERVIDOR)
    {
        // Si hay un cliente nuevo, lo acepta y lo inserta en la lista simple de clientes conectados pero no autenticados.
        nuevoCliente.sock = accept (servidor.sock, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);
        if (nuevoCliente.sock != INVALID_SOCKET)
            procesarNuevoCliente (&nuevoCliente, &(servidor.listaSimpleClientesNoAutenticados));

        // Si un cliente de la lista simple de no autenticados o de la tabla hash envia una solicitud, guarda su direccion y la solicitud para procesarla.
        if ((recibirSolicitudEnListaSimple (&(servidor.listaSimpleClientesNoAutenticados), &clienteAProcesar, buffersComunicacion.solicitud) == RECIBIO_SOLICITUD) ||
            (recibirSolicitudEnTablaHash (&(servidor.tablaHashClientes), &clienteAProcesar, buffersComunicacion.solicitud) == RECIBIO_SOLICITUD))
        {
            printf ("Solicitud recibida: %s\n", buffersComunicacion.solicitud);
            switch (buffersComunicacion.solicitud[0])
            {
            case INDICE_SOLICITUD_AUTENTICACION:
                manejarSolicitudAutenticacion (&servidor, clienteAProcesar, &buffersComunicacion);
                break;

            case INDICE_SOLICITUD_REGISTRO:
                manejarSolicitudRegistro (&servidor, clienteAProcesar, &buffersComunicacion);
                break;

            case INDICE_SOLICITUD_MENSAJE:
                manejarEnvioMensaje (&servidor, clienteAProcesar, &buffersComunicacion);
                break;

            case INDICE_SOLICITUD_AGENDAR_CONTACTO:
                //manejarSolicitudContacto (&servidor, clienteAProcesar, &buffersComunicacion);
                break;
            }
        }

        if (kbhit ()) // Detecta si el usuario presiono una tecla en consola.
        {
            ingresoCaracter = getch ();
            ingresoCaracter = toupper (ingresoCaracter);
            if (ingresoCaracter != CARACTER_APAGAR_SERVIDOR)
                    printf ("Caracter incorrecto.\nEscriba el caracter '%c' para apagar el servidor.\n\n", CARACTER_APAGAR_SERVIDOR);
        }

        Sleep (10); // Pausa para evitar ciclos innecesarios.
    }


    // --------------- LIBERAR LOS RECURSOS DEL SERVIDOR Y RETORNAR ---------------


    liberarServidor (&servidor);

    system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.

    return EXITO;
}



































