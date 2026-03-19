#include "../include/logicaAplicacion.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int funcionHash (const void *clave);
static int cmpIdCliente (const void *a, const void *b);
//static void mostrarCliente (void *cliente);
static void liberarCliente (void *cliente);



/* ============================
   FUNCIONES ESTRUCTURALES BASE
   ============================ */



int inicializarBaseDatos(sqlite3 **bd)
{
    int resultado;
    char *error = NULL;
    char *consultaSQLITE, *pTemp;
    long tamConsulta;
    sqlite3_stmt *sentencia;
    FILE *arch;


    resultado = sqlite3_open ("../../../server/database/database.db", bd);
    if (resultado != SQLITE_OK)
    {
        printf("\nERROR - Abrir base de datos: %s.\n", sqlite3_errmsg (*bd));
        return ERROR_INICIALIZACION;
    }

    consultaSQLITE = malloc (MAX_BUFFER_CONSULTA_SQLITE);
    if (!consultaSQLITE)
    {
        perror ("\nERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    // Verificar si existe la tabla usuarios.
    strcpy (consultaSQLITE, "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'usuarios';");
    if (sqlite3_prepare_v2(*bd, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (*bd));
        free(consultaSQLITE);
        return ERROR_INICIALIZACION;
    }

    resultado = (sqlite3_step (sentencia) == SQLITE_ROW);
    sqlite3_finalize(sentencia);

    // Si no existe, ejecutar schema.sql.
    if (!resultado)
    {
        arch = fopen("schema.sql", "rb");
        if (!arch)
        {
            perror ("\nERROR - Abrir archivo schema.sql.\n");
            free(consultaSQLITE);
            return ERROR_INICIALIZACION;
        }

        fseek (arch, 0, SEEK_END);
        tamConsulta = ftell (arch);
        rewind (arch);

        if (tamConsulta >= MAX_BUFFER_CONSULTA_SQLITE)
        {
            pTemp = realloc (consultaSQLITE, tamConsulta + 1);
            if (!pTemp)
            {
                perror ("\nERROR - Sin memoria.\n");
                free(consultaSQLITE);
                fclose(arch);
                return ERROR_SIN_MEMORIA;
            }
            consultaSQLITE = pTemp;
        }

        fread (consultaSQLITE, 1, tamConsulta, arch);
        consultaSQLITE[tamConsulta] = '\0';

        resultado = sqlite3_exec (*bd, consultaSQLITE, 0, 0, &error);
        if (resultado != SQLITE_OK)
        {
            printf ("\nERROR - Ejecutar schema.sql: %s\n", error);
            sqlite3_free (error);
            free(consultaSQLITE);
            fclose(arch);
            return ERROR_OPERACION;
        }

        fclose(arch);
    }

    free(consultaSQLITE);

    return EXITO;
}

int inicializarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-INICIALIZANDO LOS RECURSOS DEL SERVIDOR-\t");

    int resultado;


    // --------------- INICIALIZAR VALORES NULOS ---------------

    contextoServidor->estadoWinsock = false;
    contextoServidor->sock = INVALID_SOCKET;
    contextoServidor->baseDeDatos = NULL;


    // --------------- CREAR TABLA HASH DE CLIENTES ---------------

    crearTablaHash (&(contextoServidor->tablaHashClientes), CANT_BUCKETS_TABLA_HASH);


    // --------------- CREAR LISTA SIMPLE DE CLIENTES NO AUTENTICADOS ---------------

    crearListaSimple (&(contextoServidor->listaSimpleClientesNoAutenticados));


    // --------------- INICIALIZAR WINSOCK API ---------------

    WSADATA wsaData;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("\nERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }
    contextoServidor->estadoWinsock = true;


    // --------------- INICIALIZAR SOCKET DEL SERVIDOR ---------------

    contextoServidor->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (contextoServidor->sock == INVALID_SOCKET)
    {
        printf ("\nERROR - Crear socket del servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }


    // --------------- INICIALIZAR BASE DE DATOS ---------------

    if (inicializarBaseDatos (&(contextoServidor->baseDeDatos)) != EXITO)
        return ERROR_INICIALIZACION;


    printf ("-INICIALIZACION EXITOSA-\n");
    return EXITO;
}

int configurarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-CONFIGURANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- CONFIGURAR SOCKET DEL SERVIDOR ---------------

    struct sockaddr_in dirServidor;
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    dirServidor.sin_family = AF_INET;
    dirServidor.sin_port = htons (PUERTO); // Escuchar en el puerto asignado.
    dirServidor.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones de cualquier direccion IP.
    if (bind (contextoServidor->sock, (struct sockaddr*)(&dirServidor), sizeof (dirServidor)) == SOCKET_ERROR)
    {
        printf ("\nERROR - Enlazar socket al servidor: %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }
    if (listen (contextoServidor->sock, SOMAXCONN) == SOCKET_ERROR)
    {
        printf ("\nERROR - Escuchar socket del servidor %d.\n", WSAGetLastError ());
        return ERROR_CONFIGURACION;
    }
    ioctlsocket (contextoServidor->sock, FIONBIO, &modoSocket);


    printf ("-CONFIGURACION EXITOSA-\n");
    return EXITO;
}

void liberarServidor (t_contextoServidor *contextoServidor)
{
    printf ("-LIBERANDO LOS RECURSOS DEL SERVIDOR-\t");


    // --------------- LIBERAR LISTA SIMPLE DE CLIENTES NO AUTENTICADOS ---------------

    vaciarListaSimpleConAccion (&(contextoServidor->listaSimpleClientesNoAutenticados), liberarCliente);


    // --------------- LIBERAR TABLA HASH ---------------

    eliminarTablaHashConAccion (&(contextoServidor->tablaHashClientes), liberarCliente);


    // --------------- CERRAR BASE DE DATOS ---------------

    if (contextoServidor->baseDeDatos != NULL)
        sqlite3_close (contextoServidor->baseDeDatos);


    // --------------- LIBERAR SOCKET DEL SERVIDOR ---------------

    if (contextoServidor->sock != INVALID_SOCKET)
        closesocket (contextoServidor->sock);


    // --------------- LIBERAR WINSOCK API ---------------

    if (contextoServidor->estadoWinsock == true)
        WSACleanup ();


    printf ("-LIBERACION EXITOSA-\n");
}



/* ============================
   FUNCIONES DE GESTION DE CLIENTES
   ============================ */



void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaSimple *listaSimpleClientesNoAutenticados)
{
    u_long modoSocket = 1; // Establecer socket en modo NO bloqueante.

    printf ("Nuevo cliente conectado.\n\n");
    ioctlsocket (nuevoCliente->sock, FIONBIO, &modoSocket);
    nuevoCliente->id = ID_INVALIDO; // Le asigna una ID invalida hasta que se autentifique.

    insertarAlInicioListaSimple (listaSimpleClientesNoAutenticados, nuevoCliente, sizeof (t_cliente)); // Insertar el cliente en la lista simple de clientes no autenticados.
}

bool recibirSolicitudEnListaSimple (t_listaSimple *listaSimple, t_nodo ***nodoDelCliente, char *bufferSolicitud)
{
    t_cliente *cliente;
    int bytesRecibidos;

    while (*listaSimple != NULL) // Mientras haya clientes en la lista simple.
    {
        cliente = (*listaSimple)->dato;
        bytesRecibidos = recv (cliente->sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
        if (bytesRecibidos > 0) // Si se recibio una solicitud.
        {
            // Asegura el caracter nulo al final de la solicitud.
            bufferSolicitud += bytesRecibidos;
            *bufferSolicitud = '\0';

            *nodoDelCliente = listaSimple; // Guarda la direccion del cliente que envio la solicitud.
            return RECIBIO_SOLICITUD;
        }

        if ((bytesRecibidos == 0) || ((bytesRecibidos == SOCKET_ERROR) && (WSAGetLastError() == WSAECONNRESET))) // Si el cliente perdio la conexi�n.
        {
            printf ("Cliente ID: %d desconectado.\n\n", cliente->id);
            eliminarNodoConAccionListaSimple (listaSimple, NULL, 0, liberarCliente); // Elimina el cliente desconectado de la lista simple.
        }
        else
            listaSimple = &((*listaSimple)->sig);
    }

    return NO_RECIBIO_SOLICITUD;
}

bool recibirSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodo ***nodoDelCliente, char *bufferSolicitud)
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i++) // Por cada bucket de la tabla hash.
    {
        if (recibirSolicitudEnListaSimple (&(tablaHash->buckets[i]), nodoDelCliente, bufferSolicitud) == RECIBIO_SOLICITUD) // Si se recibio una solicitud en su lista simple.
            return RECIBIO_SOLICITUD;
    }

    return NO_RECIBIO_SOLICITUD;
}



/* ============================
   FUNCIONES DE PROCESAMIENTO DE SOLICITUDES
   ============================ */



int manejarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreUsuario [MAX_NOMBRE_USUARIO], contraseniaUsuario [MAX_CONTRASENIA_USUARIO];

    t_cliente *cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = (t_cliente*)((*(clienteAProcesar))->dato);
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^|]|%[^\n]", nombreUsuario, contraseniaUsuario); // Extraer nombre y contrasenia de la solicitud recibida.

    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ? AND contrasenia = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contraseniaUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos con tal nombre y contrasenia.
    {
        cliente->id = sqlite3_column_int (sentencia, 0); // Recupera su ID y la guarda en el cliente correspondiente.

        vincularNodoATablaHash (&(contextoServidor->tablaHashClientes), &(cliente->id), funcionHash, desvincularNodoDeListaSimple (clienteAProcesar)); // Mover cliente de la lista simple de clientes no autenticados a la tabla hash.
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, cliente->id);
    }
    else
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO);
    sqlite3_finalize (sentencia);

    send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);

    return EXITO;
}

int manejarSolicitudRegistro (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreUsuario [MAX_NOMBRE_USUARIO], contraseniaUsuario [MAX_CONTRASENIA_USUARIO], correoElectronico [MAX_CORREO_USUARIO];

    t_cliente *cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = (t_cliente*)((*(clienteAProcesar))->dato);
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^|]|%[^|]|%[^\n]", nombreUsuario, contraseniaUsuario, correoElectronico); // Extraer nombre y contrasenia de la solicitud recibida.

    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ? or correoElectronico = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos ya registrado con el mismo nombre o correo electronico.
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
        return EXITO;
    }


    strcpy (consultaSQLITE, "INSERT INTO usuarios (nombre, contrasenia, correoElectronico) VALUES (?, ?, ?);");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 2, contraseniaUsuario, -1, SQLITE_STATIC);
    sqlite3_bind_text (sentencia, 3, correoElectronico, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);


    strcpy (consultaSQLITE, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreUsuario, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    cliente->id = sqlite3_column_int (sentencia, 0); // Recupera su ID y la guarda en el cliente correspondiente.
    sqlite3_finalize (sentencia);

    vincularNodoATablaHash (&(contextoServidor->tablaHashClientes), &(cliente->id), funcionHash, desvincularNodoDeListaSimple (clienteAProcesar)); // Mover cliente de la lista simple de clientes no autenticados a la tabla hash.
    snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, cliente->id);
    send (cliente->sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);

    return EXITO;
}

int manejarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    int idEmisor, idReceptor, fecha = 0;
    char texto [MAX_BUFFER_MENSAJE];

    t_cliente cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;


    // --------------- LOGICA ---------------

    cliente = *((t_cliente*)((*(clienteAProcesar))->dato));
    sscanf (&(buffersComunicacion->solicitud[2]), "%d|%d|%[^\n]", &idEmisor, &idReceptor, texto);

    if (idEmisor == idReceptor)
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_ERROR_OPERACION_INVALIDA);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
        return ERROR_OPERACION;
    }

    strcpy (consultaSQLITE, "INSERT INTO mensajes (idEmisor, idReceptor, texto, fecha) VALUES (?, ?, ?, ?);");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_ERROR_SERVIDOR);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_int (sentencia, 1, idEmisor);
    sqlite3_bind_int (sentencia, 2, idReceptor);
    sqlite3_bind_text (sentencia, 3, texto, -1, SQLITE_STATIC);
    sqlite3_bind_int (sentencia, 4, fecha);

    sqlite3_step (sentencia);
    sqlite3_finalize (sentencia);

    snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c", RESPUESTA_EXITO);
    send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n", buffersComunicacion->respuesta);

    if (buscarClaveUnicaEnTablaHash (&(contextoServidor->tablaHashClientes), &idReceptor, funcionHash, &cliente, sizeof (t_cliente), cmpIdCliente))
    {
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d|%s", RESPUESTA_MENSAJE, idEmisor, texto);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        printf ("Respuesta enviada: %s\n", buffersComunicacion->respuesta);
    }
    printf ("\n");

    return EXITO;
}

int manejarSolicitudSeleccionContacto (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------

    char nombreReceptor [MAX_NOMBRE_USUARIO];
    int idReceptor;

    t_cliente cliente;

    char consultaSQLITE [MAX_BUFFER_CONSULTA_SQLITE];
    sqlite3_stmt *sentencia;
    int resultadoConsulta;


    // --------------- LOGICA ---------------

    cliente = *((t_cliente*)((*(clienteAProcesar))->dato));
    sscanf (&(buffersComunicacion->solicitud[2]), "%[^\n]", nombreReceptor);

    strcpy (consultaSQLITE, "SELECT id FROM usuarios where nombre = ?;");
    if (sqlite3_prepare_v2 (contextoServidor->baseDeDatos, consultaSQLITE, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("\nERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (contextoServidor->baseDeDatos));
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO);
        send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreReceptor, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta == SQLITE_ROW) // Si encontro un usuario en la base de datos con tal nombre.
    {
        idReceptor = sqlite3_column_int (sentencia, 0);

        if (idReceptor == cliente.id) // Si el receptor es el emisor.
        {
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_OPERACION_INVALIDA, ID_INVALIDO);
            send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
            printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);
            return ERROR_OPERACION;
        }
        else
            snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_EXITO, idReceptor);
    }
    else
        snprintf (buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, "%c|%d", RESPUESTA_ERROR_USUARIO_NO_ENCONTRADO, ID_INVALIDO);
    sqlite3_finalize (sentencia);

    send (cliente.sock, buffersComunicacion->respuesta, strlen (buffersComunicacion->respuesta), 0);
    printf ("Respuesta enviada: %s\n\n", buffersComunicacion->respuesta);


    return EXITO;
}

/*
int manejarSolicitudContacto (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion)
{
    // --------------- DECLARACION DE VARIABLES UTILIZADAS ---------------


    sqlite3_stmt *sentencia;
    char *consulta;
    int resultadoConsulta;

    t_cliente *clienteEmisor, clienteReceptor;
    int idReceptor;
    char *nombreEmisor, *nombreReceptor;

    bufferRespuesta = malloc (MAX_BUFFER_RESPUESTA);
    if (!bufferRespuesta)
    {
        perror ("ERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    consulta = malloc (MAX_BUFFER_CONSULTA_SQLITE);
    if (!consulta)
    {
        perror ("ERROR - Sin memoria.\n");
        free (bufferRespuesta);
        return ERROR_SIN_MEMORIA;
    }

    nombreEmisor = malloc (MAX_NOMBRE_USUARIO);
    if (!nombreEmisor)
    {
        perror ("ERROR - Sin memoria.\n");
        free (bufferRespuesta);
        free (consulta);
        return ERROR_SIN_MEMORIA;
    }

    nombreReceptor = malloc (MAX_NOMBRE_USUARIO);
    if (!nombreReceptor)
    {
        perror ("ERROR - Sin memoria.\n");
        free (bufferRespuesta);
        free (consulta);
        free (nombreEmisor);
        return ERROR_SIN_MEMORIA;
    }


    // --------------- LOGICA ---------------


    clienteEmisor = (*(clienteAProcesar))->dato;
    sscanf (bufferSolicitud, "%[^|]|%s", nombreEmisor, nombreReceptor); // Extraer el nombre del emisor y el nombre del receptor de la solicitud recibida.
    sprintf (bufferRespuesta, "%c", INDICE_RESPUESTA_SOLICITUD_RECHAZADA); // Respuesta por defecto: solicitud rechazada hasta validar los datos.


    strcpy (consulta, "SELECT id FROM usuarios WHERE nombre = ?;");
    if (sqlite3_prepare_v2 (servidor->baseDeDatos, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (servidor->baseDeDatos));
        send (clienteEmisor->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        printf ("Respuesta enviada: %s\n\n", bufferRespuesta);

        free (bufferRespuesta);
        free (consulta);
        free (nombreEmisor);
        free (nombreReceptor);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_text (sentencia, 1, nombreReceptor, -1, SQLITE_STATIC);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta != SQLITE_ROW) // Si el usuario con el nombre del receptor no existe en la base de datos.
    {
        sqlite3_finalize (sentencia);
        send (clienteEmisor->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        printf ("Respuesta enviada: %s\n\n", bufferRespuesta);

        free (bufferRespuesta);
        free (consulta);
        free (nombreEmisor);
        free (nombreReceptor);
        return EXITO;
    }
    idReceptor = sqlite3_column_int (sentencia, 0); // Recupero su ID.
    sqlite3_finalize (sentencia);


    strcpy (consulta, "INSERT INTO solicitudes_amistad (id_emisor, nombre_emisor, id_receptor) VALUES (?, ?, ?);");
    if (sqlite3_prepare_v2 (servidor->baseDeDatos, consulta, -1, &sentencia, NULL) != SQLITE_OK)
    {
        printf ("ERROR - Preparando consulta SQLite: %s.\n", sqlite3_errmsg (servidor->baseDeDatos));
        send (clienteEmisor->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        printf ("Respuesta enviada: %s\n\n", bufferRespuesta);

        free (bufferRespuesta);
        free (consulta);
        free (nombreEmisor);
        free (nombreReceptor);
        return ERROR_INICIALIZACION;
    }
    sqlite3_bind_int (sentencia, 1, clienteEmisor->id);
    sqlite3_bind_text (sentencia, 2, nombreEmisor, -1, SQLITE_STATIC);
    sqlite3_bind_int (sentencia, 3, idReceptor);

    resultadoConsulta = sqlite3_step (sentencia);
    if (resultadoConsulta != SQLITE_DONE)
    {
        sqlite3_finalize (sentencia);
        perror ("ERROR - Insertar solicitud de amistad en la base de datos.\n");
        send (clienteEmisor->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
        printf ("Respuesta enviada: %s\n\n", bufferRespuesta);

        free (bufferRespuesta);
        free (consulta);
        free (nombreEmisor);
        free (nombreReceptor);
        return ERROR_INICIALIZACION;
    }
    sqlite3_finalize (sentencia);


    sprintf (bufferRespuesta, "%c", INDICE_RESPUESTA_SOLICITUD_ACEPTADA);
    send (clienteEmisor->sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    printf ("Respuesta enviada: %s\n\n", bufferRespuesta);
    if (buscarClaveEnTablaHash (&(servidor->tablaHashClientes), &idReceptor, funcionHash, &clienteReceptor, sizeof (t_cliente), cmpIdCliente) == ENCONTRO) // Si el usuario receptor esta conectado.
    {
        sprintf (bufferRespuesta, "%c|%s quiere ser tu amigo!", INDICE_RESPUESTA_SOLICITUD_AMISTAD, nombreEmisor);
        send (clienteReceptor.sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    }


    // --------------- LIBERAR RECURSOS Y RETORNAR ---------------


    free (bufferRespuesta);
    free (consulta);
    free (nombreEmisor);
    free (nombreReceptor);

    return EXITO;
}
*/



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Calcular el indice del bucket de la tabla hash segun el ID del cliente.
 *
 * \param clave Puntero al ID del cliente.
 * \return Indice correspondiente al ID del cliente.
 *
 */
static int funcionHash (const void *clave)
{
    return *((int*)clave) % CANT_BUCKETS_TABLA_HASH;
}

/** \brief Comparar el ID de un cliente con una clave ID.
 *
 * \param cliente Puntero al cliente a comparar.
 * \param clave Puntero al ID con el que se comparara.
 * \return Diferencia entre el ID del cliente y la clave ID.
 *
 */
static int cmpIdCliente (const void *cliente, const void *clave)
{
    return (*((t_cliente*)cliente)).id - *((int*)clave);
}

/** \brief Mostrar el ID de un cliente en consola. Agrega salto de linea.
 *
 * \param cliente Puntero al cliente cuyo ID se desea mostrar.
 *
 */
/*
static void mostrarCliente (void *cliente) //Funci�n temporal
{
    printf ("%d\n", (*((t_cliente*)cliente)).id);
}
*/

/** \brief Liberar los recursos asociados a un cliente.
 *
 * \param cliente Puntero al cliente cuyos recursos seran liberados.
 *
 */
static void liberarCliente (void *cliente)
{
    closesocket (((t_cliente*)cliente)->sock);
}



































