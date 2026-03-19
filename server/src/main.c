#include "../include/logicaAplicacion.h"

int main ()
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    t_contextoServidor contextoServidor;
    t_nodo **clienteAProcesar;
    t_buffersComunicacion buffersComunicacion;
    char ingresoCaracter = '\0';

    t_cliente nuevoCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente;

    tamNuevoCliente = sizeof (dirNuevoCliente);


    // --------------- INICIALIZAR Y CONFIGURAR LOS RECURSOS DEL SERVIDOR ---------------


    if (inicializarServidor (&contextoServidor) == ERROR_INICIALIZACION)
    {
        perror ("\nERROR - Inicializacion de servidor.\n");
        liberarServidor (&contextoServidor);
        system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.
        return ERROR_INICIALIZACION;
    }
    if (configurarServidor (&contextoServidor) == ERROR_CONFIGURACION)
    {
        perror ("\nERROR - configuracion de servidor.\n");
        liberarServidor (&contextoServidor);
        system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.
        return ERROR_CONFIGURACION;
    }
    printf ("-SERVIDOR INICIADO CORRECTAMENTE-\n\n");


    // --------------- EJECUCION DEL BUCLE PRINCIPAL: acepta nuevos clientes, recibe solicitudes y las procesa ---------------


    printf ("Escriba el caracter '%c' para apagar el servidor.\n\n", CARACTER_APAGAR_SERVIDOR);

    while (ingresoCaracter != CARACTER_APAGAR_SERVIDOR)
    {
        // Si hay un cliente nuevo, lo acepta y lo inserta en la lista simple de clientes conectados pero no autenticados.
        nuevoCliente.sock = accept (contextoServidor.sock, (struct sockaddr*)(&dirNuevoCliente), &tamNuevoCliente);
        if (nuevoCliente.sock != INVALID_SOCKET)
            procesarNuevoCliente (&nuevoCliente, &(contextoServidor.listaSimpleClientesNoAutenticados));

        // Si un cliente de la lista simple de no autenticados o de la tabla hash envia una solicitud, guarda su direccion y la solicitud para procesarla.
        if ((recibirSolicitudEnListaSimple (&(contextoServidor.listaSimpleClientesNoAutenticados), &clienteAProcesar, buffersComunicacion.solicitud) == RECIBIO_SOLICITUD) ||
            (recibirSolicitudEnTablaHash (&(contextoServidor.tablaHashClientes), &clienteAProcesar, buffersComunicacion.solicitud) == RECIBIO_SOLICITUD))
        {
            printf ("Solicitud recibida: %s\n", buffersComunicacion.solicitud);
            switch (*(buffersComunicacion.solicitud))
            {
            case SOLICITUD_AUTENTICACION:
                manejarSolicitudAutenticacion (&contextoServidor, clienteAProcesar, &buffersComunicacion);
                break;

            case SOLICITUD_REGISTRO:
                manejarSolicitudRegistro (&contextoServidor, clienteAProcesar, &buffersComunicacion);
                break;

            case SOLICITUD_MENSAJE:
                manejarSolicitudEnvioMensaje (&contextoServidor, clienteAProcesar, &buffersComunicacion);
                break;

            case SOLICITUD_SELECCIONAR_CONTACTO:
                manejarSolicitudSeleccionContacto (&contextoServidor, clienteAProcesar, &buffersComunicacion);

            case SOLICITUD_AGENDAR_CONTACTO:
                //manejarSolicitudContacto (&contextoServidor, clienteAProcesar, &buffersComunicacion);
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


    liberarServidor (&contextoServidor);

    system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.

    return EXITO;
}



































