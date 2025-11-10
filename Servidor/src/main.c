#include "../include/logicaServidor.h"

int main ()
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    s_servidor servidor;
    s_nodo **clienteAProcesar;
    char ingresoCaracter = '\0', *bufferSolicitud, indiceTipoSolicitud;

    s_cliente nuevoCliente;
    struct sockaddr_in dirNuevoCliente;
    int tamNuevoCliente;

    bufferSolicitud = malloc (MAX_BUFFER_SOLICITUD);
    if (!bufferSolicitud)
    {
        perror ("ERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    tamNuevoCliente = sizeof (dirNuevoCliente);


    // --------------- INICIALIZAR Y CONFIGURAR LOS RECURSOS DEL SERVIDOR ---------------

    
    if (inicializarServidor (&servidor) == ERROR_INICIALIZACION)
    {
        liberarServidor (&servidor);
        free (bufferSolicitud);
        return ERROR_INICIALIZACION;
    }
    if (configurarServidor (&servidor) == ERROR_CONFIGURACION)
    {
        liberarServidor (&servidor);
        free (bufferSolicitud);
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
        if ((recibirSolicitudEnListaSimple (&(servidor.listaSimpleClientesNoAutenticados), &clienteAProcesar, bufferSolicitud) == RECIBIO_SOLICITUD) ||
            (recibirSolicitudEnTablaHash (&(servidor.tablaHashClientes), &clienteAProcesar, bufferSolicitud) == RECIBIO_SOLICITUD))
        {
            printf ("Solicitud recibida: %s\n", bufferSolicitud);
            indiceTipoSolicitud = *bufferSolicitud; // Guarda el indice de la solicitud.
            bufferSolicitud += 2; // Mover el puntero dos lugares para tener la solicitud limpia. Evita tener el indice de la solicitud y el separador '|'.

            switch (indiceTipoSolicitud)
            {
            case INDICE_AUTENTICACION:
                procesarInicioSesion (&servidor, clienteAProcesar, bufferSolicitud);
                break;

            case INDICE_REGISTRO:
                procesarRegistro (&servidor, clienteAProcesar, bufferSolicitud);
                break;

            case INDICE_MENSAJE:
                break;

            case INDICE_AGENDARCONTACTO:
                procesarSolicitudAmistad (&servidor, clienteAProcesar, bufferSolicitud);
                break;
            }

            bufferSolicitud -= 2; // Retroceder los dos lugares avanzados para volver a la posicion original del puntero (malloc).
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


    // --------------- LIBERAR LOS RECURSOS DEL SERVIDOR ---------------


    liberarServidor (&servidor);
    free (bufferSolicitud);

    system ("pause"); // Evita que la ventana de la consola se cierre inmediatamente.

    return EXITO;
}



































