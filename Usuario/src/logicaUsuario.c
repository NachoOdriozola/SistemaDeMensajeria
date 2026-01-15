#include "../include/logicaUsuario.h"



/* ============================
   FUNCIONES DE FUENTES
   ============================ */



int inicializarFuentes (t_fuentes *fuentes)
{
    //--------------- INICIALIZAR VALORES NULOS ---------------

    fuentes->fuente1 = NULL;


    //--------------- INICIALIZAR TEXTO ---------------

    fuentes->fuente1 = sfFont_createFromFile ("fuente1.ttf");
    if (!fuentes->fuente1)
    {
        perror ("ERROR - Crear fuente 1.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

void liberarFuentes (t_fuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->fuente1);
}



/* ============================
   FUNCIONES DE SOCKETS
   ============================ */



bool recibirRespuesta (SOCKET sock, char *bufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos;
        *bufferRespuesta = '\0';
        return RECIBIO_RESPUESTA;
    }

    return NO_RECIBIO_RESPUESTA;
}

void enviarSolicitudYRecibirRespuesta (SOCKET sock, const char *bufferSolicitud, char *bufferRespuesta)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    int bytesRecibidos;

    ioctlsocket (sock, FIONBIO, &modoSocket);
    send (sock, bufferSolicitud, strlen (bufferSolicitud), 0);
    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    bufferRespuesta += bytesRecibidos;
    *bufferRespuesta = '\0';
    modoSocket = 1;     // Socket modo no bloqueante
    ioctlsocket (sock, FIONBIO, &modoSocket);
}



/* ============================
   FUNCIONES DE GUARDADO DE AUTENTICACION
   ============================ */



int guardarDatosEnArchivo (int id, const char *bufferNombre)
{
    t_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "wb");
    if (!archDatos)
    {
        perror ("ERROR - Crear archivo para guardar inicio de sesion.\n");
        return ERROR_INICIALIZACION;
    }

    datosGuardados.id = id;
    strcpy (datosGuardados.nombre, bufferNombre);
    fwrite (&datosGuardados, sizeof (t_datosGuardados), 1, archDatos);

    fclose (archDatos);

    return EXITO;
}

bool verificarModoAutenticacion (t_usuario *usuario)
{
    t_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "rb");
    if (!archDatos)
        return AUTENTICACION_MANUAL;

    fread (&datosGuardados, sizeof (t_datosGuardados), 1, archDatos);
    usuario->id = datosGuardados.id;
    strcpy (usuario->nombre, datosGuardados.nombre);

    fclose (archDatos);

    return AUTENTICACION_AUTOMATICA;
}



/* ============================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================ */



bool clickEnRectangulo (const sfRenderWindow *renderizado, const sfRectangleShape *rectangulo)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteRectangulo;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, mouseMundo.x, mouseMundo.y);
}

bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto)
{
    sfVector2i mousePixel;
    sfVector2f mouseMundo;
    sfFloatRect limiteTexto;

    mousePixel = sfMouse_getPositionRenderWindow (renderizado);
    mouseMundo = sfRenderWindow_mapPixelToCoords (renderizado, mousePixel, NULL);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, mouseMundo.x, mouseMundo.y);
}



/* ============================
   FUNCIONES DE ESCRITURA
   ============================ */



void ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar)
{
    int largoBuffer;

    largoBuffer = strlen (buffer);

    if (eventoChar.text.unicode == 13) // Si la tecla es "Enter" retorna.
        return;

    if (eventoChar.text.unicode != 8) //Si la tecla no es "Backspace".
    {
        if (largoBuffer < tamMaxBuffer - 1)
        {
            buffer [largoBuffer] = (char)eventoChar.text.unicode;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    else if (largoBuffer > 0) // Si la tecla es "Backspace".
            buffer [largoBuffer - 1] = '\0';
}



/* ============================
   FUNCIONES DE PUNTO DE INSERCION
   ============================ */



void actualizarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion)
{
    (*contadorPuntoInsercion) ++;
    if (*contadorPuntoInsercion >= VELOCIDAD_PARPADEO_PUNTO_INSERCION)
    {
        *contadorPuntoInsercion = REINICIAR_CONTADOR_PUNTO_INSERCION;
        if (*puntoInsercion == DESHABILITAR_PUNTO_INSERCION)
            *puntoInsercion = HABILITAR_PUNTO_INSERCION;
        else
            *puntoInsercion = DESHABILITAR_PUNTO_INSERCION;
    }
}

void reiniciarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion)
{
    *puntoInsercion = DESHABILITAR_PUNTO_INSERCION;
    *contadorPuntoInsercion = REINICIAR_CONTADOR_PUNTO_INSERCION;
}



/* ============================
   FUNCIONES DE LISTA DE MENSAJES
   ============================ */



void asignarMensaje (t_aplicacion *aplicacion, const char *bufferMensaje, bool enviadoPor)
{
    sfText *mensaje;
    sfFloatRect bordesMensaje;

    mapListaCircular (&(aplicacion->mensajes.listaMensajes), modificarPosListaMensajes);
    mensaje = *((sfText**)aplicacion->mensajes.siguienteMensaje->dato);

    sfText_setString (mensaje, bufferMensaje);
    if (enviadoPor == MI_USUARIO)
    {
        bordesMensaje = sfText_getLocalBounds (mensaje);
        sfText_setPosition (mensaje, (sfVector2f){1780 - bordesMensaje.width, 827});
    }
    else
        sfText_setPosition (mensaje, (sfVector2f){510, 827});

    aplicacion->mensajes.siguienteMensaje = aplicacion->mensajes.siguienteMensaje->sig;
}

void modificarPosListaMensajes (void *mensaje)
{
    sfVector2f pos;

    pos = sfText_getPosition (*((sfText**)mensaje));
    pos.y -= 80;
    sfText_setPosition (*((sfText**)mensaje), pos);
}

void renderizarListaMensajes (void *mensaje, void *renderizado)
{
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *((sfText**)mensaje), NULL);
}

void setupListaMensajes (void *mensaje, void *fuente)
{
    sfText_setFont (*((sfText**)mensaje), (sfFont*)fuente);
    sfText_setFillColor (*((sfText**)mensaje), sfColor_fromRGB (34, 48, 48));
}

void tamListaMensajes (void *mensaje)
{
    sfText_setCharacterSize (*((sfText**)mensaje), 26);
}

void liberarMensaje (void *mensaje)
{
    sfText_destroy (*((sfText**)mensaje));
}



/* ============================
   FUNCIONES DE NOTIFICACIONES
   ============================ */



int crearNotificacion (t_notificacion *notificacion)
{
    //CREAR ELEMENTOS

    notificacion->recuadro = sfRectangleShape_create ();
    if (!notificacion->recuadro)
    {
        perror ("ERROR - Crear recuadro para notificacion.\n");
        return ERROR_INICIALIZACION;
    }

    notificacion->botonAceptar = sfRectangleShape_create ();
    if (!notificacion->botonAceptar)
    {
        perror ("ERROR - Crear boton aceptar para notificacion.\n");
        return ERROR_INICIALIZACION;
    }

    notificacion->botonRechazar = sfRectangleShape_create ();
    if (!notificacion->botonRechazar)
    {
        perror ("ERROR - Crear boton rechazar para notificacion.\n");
        return ERROR_INICIALIZACION;
    }


    //CREAR TEXTO

    notificacion->textoNotificacion = sfText_create ();
    if (!notificacion->textoNotificacion)
    {
        perror ("ERROR - Crear texto para notificacion.\n");
        return ERROR_INICIALIZACION;
    }

    notificacion->textoBotonAceptar = sfText_create ();
    if (!notificacion->textoBotonAceptar)
    {
        perror ("ERROR - Crear texto para boton aceptar.\n");
        return ERROR_INICIALIZACION;
    }

    notificacion->textoBotonRechazar = sfText_create ();
    if (!notificacion->textoBotonRechazar)
    {
        perror ("ERROR - Crear texto para boton rechazar.\n");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

void setupNotificacion (t_notificacion *notificacion, t_fuentes fuentes)
{
    //SETUP ELEMENTOS

    //Recuadro
    sfRectangleShape_setFillColor (notificacion->recuadro, sfColor_fromRGB (255, 229, 127));
    sfRectangleShape_setOutlineColor (notificacion->recuadro, sfColor_fromRGB (156, 156, 156));
    sfRectangleShape_setOutlineThickness (notificacion->recuadro, 3);
    sfRectangleShape_setPosition (notificacion->recuadro, (sfVector2f){650, 600});
    sfRectangleShape_setSize (notificacion->recuadro, (sfVector2f){350, 150});

    //Boton aceptar
    sfRectangleShape_setFillColor (notificacion->botonAceptar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setPosition (notificacion->botonAceptar, (sfVector2f){850, 600});
    sfRectangleShape_setSize (notificacion->botonAceptar, (sfVector2f){100, 35});

    //Boton rechazar
    sfRectangleShape_setFillColor (notificacion->botonRechazar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setPosition (notificacion->botonRechazar, (sfVector2f){1000, 600});
    sfRectangleShape_setSize (notificacion->botonRechazar, (sfVector2f){100, 35});


    //SETUP TEXTO

    //Texto notificacion
    sfText_setFont (notificacion->textoNotificacion, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoNotificacion, sfColor_fromRGB (40, 54, 54));
    sfText_setPosition (notificacion->textoNotificacion, (sfVector2f){680, 600});
    sfText_setCharacterSize (notificacion->textoNotificacion, 26);

    //Texto boton aceptar
    sfText_setFont (notificacion->textoBotonAceptar, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoBotonAceptar, sfColor_fromRGB (40, 54, 54));
    sfText_setString (notificacion->textoBotonAceptar, "ACEPTAR");
    sfText_setPosition (notificacion->textoBotonAceptar, (sfVector2f){860, 600});
    sfText_setCharacterSize (notificacion->textoBotonAceptar, 26);

    //Texto boton rechazar
    sfText_setFont (notificacion->textoBotonRechazar, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoBotonRechazar, sfColor_fromRGB (40, 54, 54));
    sfText_setString (notificacion->textoBotonRechazar, "RECHAZAR");
    sfText_setPosition (notificacion->textoBotonRechazar, (sfVector2f){1030, 600});
    sfText_setCharacterSize (notificacion->textoBotonRechazar, 26);
}

int agregarNotificacion (t_listaSimple *listaNotificaciones, char *bufferNotificacion, t_fuentes fuentes)
{
    t_notificacion notificacion;

    if (crearNotificacion (&notificacion) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;
    setupNotificacion (&notificacion, fuentes);

    bufferNotificacion += 2;
    sfText_setString (notificacion.textoNotificacion, bufferNotificacion);
    insertarAlInicioListaSimple (listaNotificaciones, &notificacion, sizeof (t_notificacion));
    bufferNotificacion -= 2;

    return EXITO;
}

void liberarNotificacion (void *notificacion)
{
    sfRectangleShape_destroy (((t_notificacion*)notificacion)->recuadro);
    sfRectangleShape_destroy (((t_notificacion*)notificacion)->botonAceptar);
    sfRectangleShape_destroy (((t_notificacion*)notificacion)->botonRechazar);
    sfText_destroy (((t_notificacion*)notificacion)->textoNotificacion);
    sfText_destroy (((t_notificacion*)notificacion)->textoBotonAceptar);
    sfText_destroy (((t_notificacion*)notificacion)->textoBotonRechazar);
}

void renderizarListaNotificaciones (void *notificacion, void *renderizado)
{
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->recuadro, NULL);
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->botonAceptar, NULL);
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->botonRechazar, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->textoNotificacion, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->textoBotonAceptar, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((t_notificacion*)notificacion)->textoBotonRechazar, NULL);
}


























