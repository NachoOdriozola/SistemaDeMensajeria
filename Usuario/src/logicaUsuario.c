#include "../include/logicaUsuario.h"



/* ============================
   FUNCIONES DE VENTANA
   ============================ */



int ajustarVista (sfRenderWindow *renderizado, sfVector2f nuevoTamVentana)
{
    sfView *nuevaVista;

    nuevaVista = sfView_create ();
    if (!nuevaVista)
    {
        perror ("ERROR - Crear nueva vista para redimensionar la ventana.\n");
        return ERROR_SIN_MEMORIA;
    }

    sfView_setSize (nuevaVista, nuevoTamVentana);
    sfView_setCenter (nuevaVista, (sfVector2f){nuevoTamVentana.x / 2.0f, nuevoTamVentana.y / 2.0f});
    sfRenderWindow_setView (renderizado, nuevaVista);

    sfView_destroy (nuevaVista);

    return EXITO;
}

void crearEscalaElementos (s_ventana *ventana)
{
    ventana->escalaElementos.x = ventana->tamVentana.x / (float)TAMANIO_BASE_MAXIMIZADO_X;
    ventana->escalaElementos.y = ventana->tamVentana.y / (float)TAMANIO_BASE_MAXIMIZADO_Y;
}

void crearEscalaPixeles (s_ventana *ventana)
{
    ventana->escalaPixeles = fminf (ventana->tamVentana.x / (float)TAMANIO_BASE_MAXIMIZADO_X, ventana->tamVentana.y / (float)TAMANIO_BASE_MAXIMIZADO_Y);
}

void eventoMaximizadoAutomatico (sfRenderWindow *renderizado, s_ventana *ventana)
{
    sfEvent eventoPrimerMaximizado;
    sfVector2f nuevoTamVentana;

    // Procesar todos los eventos ocurridos hasta encontrar el de maximizado de la ventana.
    while (sfRenderWindow_pollEvent (renderizado, &eventoPrimerMaximizado))
    {
        if (eventoPrimerMaximizado.type == sfEvtResized)
        {
            nuevoTamVentana.x = eventoPrimerMaximizado.size.width;
            nuevoTamVentana.y = eventoPrimerMaximizado.size.height;
            break;
        }
    }
    ventana->tamVentana = nuevoTamVentana;
}

int maximizadoAutomaticoVentana (sfRenderWindow *renderizado, s_ventana *ventana)
{
    HWND hwnd;

    hwnd = sfRenderWindow_getSystemHandle (renderizado);
    ShowWindow (hwnd, SW_MAXIMIZE); // maximizar ventana.

    eventoMaximizadoAutomatico (renderizado, ventana);
    if (ajustarVista (renderizado, ventana->tamVentana) == ERROR_SIN_MEMORIA)
        return ERROR_INICIALIZACION;

    crearEscalaElementos (ventana);
    crearEscalaPixeles (ventana);

    return EXITO;
}

int manejarRedimensionamientoVentana (s_aplicacion *aplicacion, sfEvent eventoVentana)
{
    sfVector2f nuevoTamVentana;

    nuevoTamVentana.x = eventoVentana.size.width;
    nuevoTamVentana.y = eventoVentana.size.height;
    aplicacion->ventana.tamVentana = nuevoTamVentana;
    if (ajustarVista (aplicacion->renderizado, nuevoTamVentana) == ERROR_SIN_MEMORIA)
        return ERROR_SIN_MEMORIA;
    return EXITO;
}



/* ============================
   FUNCIONES DE FUENTES
   ============================ */



int inicializarFuentes (s_fuentes *fuentes)
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

void liberarFuentes (s_fuentes *fuentes)
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
        bufferRespuesta += bytesRecibidos - 1;
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
    send (sock, bufferSolicitud, MAX_BUFFER_SOLICITUD, 0);
    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    bufferRespuesta += bytesRecibidos - 1;
    *bufferRespuesta = '\0';
    modoSocket = 1;
    ioctlsocket (sock, FIONBIO, &modoSocket);
}



/* ============================
   FUNCIONES DE GUARDADO DE AUTENTICACION
   ============================ */



int guardarDatosEnArchivo (int id, const char *bufferNombre)
{
    s_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "wb");
    if (!archDatos)
    {
        perror ("ERROR - Crear archivo para guardar inicio de sesion.\n");
        return ERROR_INICIALIZACION;
    }

    datosGuardados.id = id;
    strcpy (datosGuardados.nombre, bufferNombre);
    fwrite (&datosGuardados, sizeof (s_datosGuardados), 1, archDatos);

    fclose (archDatos);

    return EXITO;
}

bool verificarModoAutenticacion (s_usuario *usuario)
{
    s_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "rb");
    if (!archDatos)
        return AUTENTICACION_MANUAL;

    fread (&datosGuardados, sizeof (s_datosGuardados), 1, archDatos);
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
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}

bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto)
{
    sfVector2i posMouse;
    sfFloatRect limiteTexto;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteTexto = sfText_getGlobalBounds (texto);

    return sfFloatRect_contains (&limiteTexto, posMouse.x, posMouse.y);
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



void asignarMensaje (s_aplicacion *aplicacion, const char *bufferMensaje, bool enviadoPor)
{
    sfText *mensaje;
    sfFloatRect bordesMensaje;

    mapListaCircularConComplemento (&(aplicacion->mensajes.listaMensajes), &(aplicacion->ventana.escalaPixeles), modificarPosListaMensajes);
    mensaje = *(sfText**)aplicacion->mensajes.siguienteMensaje->dato;
    sfText_setString (mensaje, bufferMensaje);
    if (enviadoPor == MI_USUARIO)
    {
        bordesMensaje = sfText_getLocalBounds (mensaje);
        sfText_setPosition (mensaje, (sfVector2f){(1780 * aplicacion->ventana.escalaElementos.x) - bordesMensaje.width, 827 * aplicacion->ventana.escalaElementos.y});
    }
    else
        sfText_setPosition (mensaje, (sfVector2f){510 * aplicacion->ventana.escalaElementos.x, 827 * aplicacion->ventana.escalaElementos.y});

    aplicacion->mensajes.siguienteMensaje = aplicacion->mensajes.siguienteMensaje->sig;
}

void modificarPosListaMensajes (void *mensaje, void *escalaPixeles)
{
    sfVector2f pos;

    pos = sfText_getPosition (*(sfText**)mensaje);
    pos.y -= 80 * (*(float*)escalaPixeles);
    sfText_setPosition (*(sfText**)mensaje, pos);
}

void renderizarListaMensajes (void *mensaje, void *renderizado)
{
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *(sfText**)mensaje, NULL);
}

void setupListaMensajes (void *mensaje, void *fuente)
{
    sfText_setFont (*(sfText**)mensaje, (sfFont*)fuente);
    sfText_setFillColor (*(sfText**)mensaje, sfColor_fromRGB (34, 48, 48));
}

void tamListaMensajes (void *mensaje, void *escalaPixeles)
{
    sfText_setCharacterSize (*(sfText**)mensaje, 26 * (*(float*)escalaPixeles));
}

void liberarMensaje (void *mensaje)
{
    sfText_destroy (*(sfText**)mensaje);
}



/* ============================
   FUNCIONES DE NOTIFICACIONES
   ============================ */



int crearNotificacion (s_notificacion *notificacion)
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

void setupNotificacion (s_notificacion *notificacion, s_ventana ventana, s_fuentes fuentes)
{
    //SETUP ELEMENTOS

    //Recuadro
    sfRectangleShape_setFillColor (notificacion->recuadro, sfColor_fromRGB (255, 229, 127));
    sfRectangleShape_setOutlineColor (notificacion->recuadro, sfColor_fromRGB (156, 156, 156));
    sfRectangleShape_setOutlineThickness (notificacion->recuadro, 3 * ventana.escalaPixeles);
    sfRectangleShape_setPosition (notificacion->recuadro, (sfVector2f){650 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (notificacion->recuadro, (sfVector2f){350 * ventana.escalaElementos.x, 150 * ventana.escalaElementos.y});

    //Boton aceptar
    sfRectangleShape_setFillColor (notificacion->botonAceptar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setPosition (notificacion->botonAceptar, (sfVector2f){850 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (notificacion->botonAceptar, (sfVector2f){100 * ventana.escalaElementos.x, 35 * ventana.escalaElementos.y});

    //Boton rechazar
    sfRectangleShape_setFillColor (notificacion->botonRechazar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setPosition (notificacion->botonRechazar, (sfVector2f){1000 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfRectangleShape_setSize (notificacion->botonRechazar, (sfVector2f){100 * ventana.escalaElementos.x, 35 * ventana.escalaElementos.y});


    //SETUP TEXTO

    //Texto notificacion
    sfText_setFont (notificacion->textoNotificacion, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoNotificacion, sfColor_fromRGB (40, 54, 54));
    sfText_setPosition (notificacion->textoNotificacion, (sfVector2f){680 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfText_setCharacterSize (notificacion->textoNotificacion, 26 * ventana.escalaPixeles);

    //Texto boton aceptar
    sfText_setFont (notificacion->textoBotonAceptar, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoBotonAceptar, sfColor_fromRGB (40, 54, 54));
    sfText_setString (notificacion->textoBotonAceptar, "ACEPTAR");
    sfText_setPosition (notificacion->textoBotonAceptar, (sfVector2f){860 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfText_setCharacterSize (notificacion->textoBotonAceptar, 26 * ventana.escalaPixeles);

    //Texto boton rechazar
    sfText_setFont (notificacion->textoBotonRechazar, fuentes.fuente1);
    sfText_setFillColor (notificacion->textoBotonRechazar, sfColor_fromRGB (40, 54, 54));
    sfText_setString (notificacion->textoBotonRechazar, "RECHAZAR");
    sfText_setPosition (notificacion->textoBotonRechazar, (sfVector2f){1030 * ventana.escalaElementos.x, 600 * ventana.escalaElementos.y});
    sfText_setCharacterSize (notificacion->textoBotonRechazar, 26 * ventana.escalaPixeles);
}

int agregarNotificacion (s_listaSimple *listaNotificaciones, char *bufferNotificacion, s_ventana ventana, s_fuentes fuentes)
{
    s_notificacion notificacion;

    if (crearNotificacion (&notificacion) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;
    setupNotificacion (&notificacion, ventana, fuentes);

    bufferNotificacion += 2;
    sfText_setString (notificacion.textoNotificacion, bufferNotificacion);
    insertarAlInicioListaSimple (listaNotificaciones, &notificacion, sizeof (s_notificacion));
    bufferNotificacion -= 2;

    return EXITO;
}

void liberarNotificacion (void *notificacion)
{
    sfRectangleShape_destroy (((s_notificacion*)notificacion)->recuadro);
    sfRectangleShape_destroy (((s_notificacion*)notificacion)->botonAceptar);
    sfRectangleShape_destroy (((s_notificacion*)notificacion)->botonRechazar);
    sfText_destroy (((s_notificacion*)notificacion)->textoNotificacion);
    sfText_destroy (((s_notificacion*)notificacion)->textoBotonAceptar);
    sfText_destroy (((s_notificacion*)notificacion)->textoBotonRechazar);
}

void renderizarListaNotificaciones (void *notificacion, void *renderizado)
{
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->recuadro, NULL);
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->botonAceptar, NULL);
    sfRenderWindow_drawRectangleShape ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->botonRechazar, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->textoNotificacion, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->textoBotonAceptar, NULL);
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, ((s_notificacion*)notificacion)->textoBotonRechazar, NULL);
}


























