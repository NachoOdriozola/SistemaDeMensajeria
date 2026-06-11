#include "../../include/recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void recursosComunesContactosSalas_inicializarValoresNulosFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
static void recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas);

static int recursosComunesContactosSalas_inicializarFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
static int recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos);
static int recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos);
static int recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas);
static int recursosComunesContactosSalas_inicializarListaMensajes (t_contextoMensajes *contextoMensajes);

static void recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
static void recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos);

static void recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas);

static void recursosComunesContactosSalas_liberarFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
static void recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos);
static void recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos);
static void recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas);



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



void recursosComunesContactosSalas_inicializarValoresNulos (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // FUENTES

    recursosComunesContactosSalas_inicializarValoresNulosFuentes (&(recursosComunesContactosSalas->fuentes));


    // TEXTOS

    recursosComunesContactosSalas_inicializarValoresNulosTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_inicializarValoresNulosElementos (&(recursosComunesContactosSalas->elementos));


    // VISTAS

    recursosComunesContactosSalas_inicializarValoresNulosVistas (&(recursosComunesContactosSalas->vistas));


    // LISTA DE MENSAJES

    crearListaCircular (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes));
}

int recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // FUENTES

    if (recursosComunesContactosSalas_inicializarFuentes (&(recursosComunesContactosSalas->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // TEXTOS

    if (recursosComunesContactosSalas_inicializarTextos (&(recursosComunesContactosSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (recursosComunesContactosSalas_inicializarElementos (&(recursosComunesContactosSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // VISTAS

    if (recursosComunesContactosSalas_inicializarVistas (&(recursosComunesContactosSalas->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // LISTA DE MENSAJES

    if (recursosComunesContactosSalas_inicializarListaMensajes (&(recursosComunesContactosSalas->contextoMensajes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR FOCO ---------------

    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;


    // --------------- CONFIGURAR PUNTO DE INSERCION ---------------

    resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesContactosSalas_configurarTextos (&(recursosComunesContactosSalas->textos), &(recursosComunesContactosSalas->fuentes));


    // ELEMENTOS

    recursosComunesContactosSalas_configurarElementos (&(recursosComunesContactosSalas->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTO

    recursosComunesContactosSalas_tamYPosVentanaTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_tamYPosVentanaElementos (&(recursosComunesContactosSalas->elementos));


    // VISTAS

    recursosComunesContactosSalas_tamVistas (&(recursosComunesContactosSalas->vistas));


    // --------------- CONFIGURAR CONTEXTO DE MENSAJES ---------------

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';
    recursosComunesContactosSalas->contextoMensajes.primerMensaje = recursosComunesContactosSalas->contextoMensajes.listaMensajes;
    recursosComunesContactosSalas->contextoMensajes.ultimoMensaje = recursosComunesContactosSalas->contextoMensajes.listaMensajes;

    mapListaCircularConComplemento (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), recursosComunesContactosSalas->fuentes.cuerpo, configurarMensaje);
    mapListaCircular (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), tamMensaje);
}

void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, textos->proximaInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoBotonEnviar, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaMensajes, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonEnviar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo2, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo1, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->solapaCambiarInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->panelInterfaz, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloArriba, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloAbajo, NULL);
    sfRenderWindow_drawCircleShape (renderizado, elementos->ojalilloSelecInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionTitulo, NULL);
}

void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // FUENTES

    recursosComunesContactosSalas_liberarFuentes (&(recursosComunesContactosSalas->fuentes));


    // TEXTOS

    recursosComunesContactosSalas_liberarTextos (&(recursosComunesContactosSalas->textos));


    // ELEMENTOS

    recursosComunesContactosSalas_liberarElementos (&(recursosComunesContactosSalas->elementos));


    // VISTAS

    recursosComunesContactosSalas_liberarVistas (&(recursosComunesContactosSalas->vistas));


    // LISTA DE MENSAJES

    mapListaCircular (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), liberarMensaje);
}



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



void activarInterfazContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR FOCO ---------------

    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';


    // --------------- CONFIGURAR PUNTO DE INSERCION ---------------

    resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    // auxEscribirMensaje
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");

    // proximaInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.proximaInterfaz, "SALAS");
    sfText_setPosition (recursosComunesContactosSalas->textos.proximaInterfaz, (sfVector2f){343, 530});

    // tituloInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.tituloInterfaz, "CONTACTOS");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloInterfaz, (sfVector2f){79, 37});


    // ELEMENTOS
}

void activarInterfazSalas (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR FOCO ---------------

    recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesContactosSalas->contextoMensajes.bufferMensaje) = '\0';


    // --------------- CONFIGURAR PUNTO DE INSERCION ---------------

    resetearPuntoInsercion (&(recursosComunesContactosSalas->puntoInsercion));


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    // auxEscribirMensaje
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");

    // proximaInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.proximaInterfaz, "CONTACTOS");
    sfText_setPosition (recursosComunesContactosSalas->textos.proximaInterfaz, (sfVector2f){343, 567});

    // tituloInterfaz
    sfText_setString (recursosComunesContactosSalas->textos.tituloInterfaz, "SALAS");
    sfText_setPosition (recursosComunesContactosSalas->textos.tituloInterfaz, (sfVector2f){120, 37});


    // ELEMENTOS
}

void renderizarVistaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- ESTABLECER VISTA DE MENSAJES ---------------

    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.mensajes);


    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------

    mapListaCircularConComplemento (&(recursosComunesContactosSalas->contextoMensajes.listaMensajes), renderizado, renderizarMensaje);
}

void establecerYPosicionarNombreUsuario (t_recursosComunesContactosSalas *recursosComunesContactosSalas, const char *nombreUsuario)
{
    sfFloatRect limites;
    unsigned short int i = 30;

    sfText_setString (recursosComunesContactosSalas->textos.nombreUsuario, nombreUsuario);
    
    sfText_setCharacterSize (recursosComunesContactosSalas->textos.nombreUsuario, 32);
    centrarTextoEnArea (recursosComunesContactosSalas->textos.nombreUsuario, 44, 888, 254, 120);

    limites = sfText_getLocalBounds (recursosComunesContactosSalas->textos.nombreUsuario);
    while ((limites.width > 254) && (i > 10)) // Mientras el nombre sobrepase el area.
    {
        sfText_setCharacterSize (recursosComunesContactosSalas->textos.nombreUsuario, i);
        centrarTextoEnArea (recursosComunesContactosSalas->textos.nombreUsuario, 44, 888, 254, 120);
        limites = sfText_getLocalBounds (recursosComunesContactosSalas->textos.nombreUsuario);
        i -= 2;
    }
}



/* ============================================================================================================================================
   FUNCIONES DE LISTA DE MENSAJES
   ============================================================================================================================================ */



void configurarMensaje (void *mensaje, void *fuente)
{
    sfText_setFont (*((sfText**)mensaje), (sfFont*)fuente);
    sfText_setFillColor (*((sfText**)mensaje), sfColor_fromRGB (53, 53, 53));
}

void tamMensaje (void *mensaje)
{
    sfText_setCharacterSize (*((sfText**)mensaje), 22);
    sfText_setLineSpacing (*((sfText**)mensaje), 1.3);
}

void renderizarMensaje (void *mensaje, void *renderizado)
{
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *((sfText**)mensaje), NULL);
}

void vaciarMensaje (void *mensaje)
{
    sfText_setString (*((sfText**)mensaje), "");
}

void liberarMensaje (void *mensaje)
{
    DESTRUCTOR_SEGURO_TEXTO (*((sfText**)mensaje));
}

void modificarPosMensaje (void *mensaje, void *desplazamientoY)
{
    sfVector2f pos;

    pos = sfText_getPosition (*((sfText**)mensaje));
    pos.y -= *((float*)desplazamientoY);
    sfText_setPosition (*((sfText**)mensaje), pos);
}

void establecerSaltoDeLineaMensaje(sfText *texto, const char *bufferMensaje, float anchoMax)
{
    int largoPalabra, i;
    int largoActual;
    sfVector2f posUltimoCaracter;
    char bufferTexto[MAX_BUFFER_MENSAJE + 100] = "";

    while (*bufferMensaje)
    {
        // Establecer la longitud de la palabra.
        largoPalabra = 0;
        while ((bufferMensaje[largoPalabra] != '\0') && (bufferMensaje[largoPalabra] != ' '))
            largoPalabra++;

        // Procesar palabra caracter por caracter.
        for (i = 0; i < largoPalabra; i++)
        {
            largoActual = strlen (bufferTexto);

            bufferTexto[largoActual] = bufferMensaje[i];
            bufferTexto[largoActual + 1] = '\0';

            sfText_setString (texto, bufferTexto);
            posUltimoCaracter = sfText_findCharacterPos (texto, strlen(bufferTexto));
            if (posUltimoCaracter.x >= anchoMax)
                strcat (bufferTexto, "\n"); // Agregar salto de linea si la palabra sobrepaso el ancho permitido.
        }

        bufferMensaje += largoPalabra;
        if (*bufferMensaje == ' ')
        {
            strcat (bufferTexto, " ");
            bufferMensaje++;
        }
    }
    sfText_setString(texto, bufferTexto);
}

void insertarMensaje (t_contextoMensajes *contextoMensajes, const char *bufferMensaje, t_origenMensaje origen)
{
    sfText *mensaje;
    sfFloatRect limites;
    float desplazamientoY;

    mensaje = *((sfText**)contextoMensajes->primerMensaje->dato);

    sfText_setPosition (mensaje, (sfVector2f){0, 0});
    establecerSaltoDeLineaMensaje (mensaje, bufferMensaje, 700);

    limites = sfText_getLocalBounds (mensaje);
    desplazamientoY = limites.height + 35;
    mapListaCircularConComplemento (&(contextoMensajes->listaMensajes), &(desplazamientoY), modificarPosMensaje);

    if (origen == MENSAJE_PROPIO)
        sfText_setPosition (mensaje, (sfVector2f){1824 - limites.width - limites.left, 825 - limites.height});
    else
        sfText_setPosition (mensaje, (sfVector2f){485, 825 - limites.height});

    if (contextoMensajes->primerMensaje->sig == contextoMensajes->ultimoMensaje)
        contextoMensajes->ultimoMensaje = contextoMensajes->ultimoMensaje->sig;
    contextoMensajes->primerMensaje = contextoMensajes->primerMensaje->sig;
}



/* ============================================================================================================================================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================================================================================================================================ */



void manejarRedimensionamientoVentanaContactosSalas (sfRenderWindow *renderizado, t_recursosComunesContactosSalasVistas *vistas, sfEvent eventoRedimensionamiento)
{
    sfVector2u tamVentana;

    if (eventoRedimensionamiento.size.width < ANCHO_MINIMO_VENTANA)
        tamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        tamVentana.x = eventoRedimensionamiento.size.width;

    if (eventoRedimensionamiento.size.height < ALTO_MINIMO_VENTANA)
        tamVentana.y = ALTO_MINIMO_VENTANA;
    else
        tamVentana.y = eventoRedimensionamiento.size.height;

    sfRenderWindow_setSize (renderizado, tamVentana);

    // Redimensionar vista UI.
    sfView_setSize (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});
}


bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfFloatRect limiteTextoAux;

    if (!clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    recursosComunesContactosSalas->estadoFoco = ESCRIBIR_MENSAJE;
    limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451 + limiteTextoAux.width, 942});

    return EVENTO_MANEJADO;
}

bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    if (!clickEnRectangulo (renderizado, recursosComunesContactosSalas->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;
    recursosComunesContactosSalas->estadoFoco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}


bool manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (recursosComunesContactosSalas->contextoMensajes.bufferMensaje, MAX_BUFFER_MENSAJE, eventoChar) != CARACTER_INVALIDO)
    {
        limitarVisualizarTextoSobreBarra (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->contextoMensajes.bufferMensaje, 1250);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451 + limiteTextoAux.width, 942});
    }

    return EVENTO_MANEJADO;
}


bool manejarPegarPortapapelesEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfFloatRect limiteTextoAux;

    if (recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (!pegarDesdePortapapeles (recursosComunesContactosSalas->contextoMensajes.bufferMensaje, MAX_BUFFER_MENSAJE))
    {
        limitarVisualizarTextoSobreBarra (recursosComunesContactosSalas->textos.auxEscribirMensaje, recursosComunesContactosSalas->contextoMensajes.bufferMensaje, 1250);
        limiteTextoAux = sfText_getGlobalBounds (recursosComunesContactosSalas->textos.auxEscribirMensaje);
        sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451 + limiteTextoAux.width, 942});
    }

    return EVENTO_MANEJADO;
}


bool manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfVector2f tamVista, posCentro;
    sfVector2f posUltimoMensaje;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentro = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)recursosComunesContactosSalas->contextoMensajes.ultimoMensaje->dato));
    if (posCentro.y - tamVista.y / 2.f > posUltimoMensaje.y)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}

bool manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    sfVector2f tamVista, posCentro;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentro = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);
    if (posCentro.y + tamVista.y / 2.f < 870)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}


bool manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll)
{
    sfVector2f tamVista, posCentro;
    sfVector2f posUltimoMensaje;
    float desplazamientoY;
    float superiorVista, inferiorVista;
    float limiteSuperior, limiteInferior;

    if (recursosComunesContactosSalas->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (recursosComunesContactosSalas->vistas.mensajes);
    posCentro = sfView_getCenter (recursosComunesContactosSalas->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)recursosComunesContactosSalas->contextoMensajes.ultimoMensaje->dato));

    desplazamientoY = -eventoScroll.mouseWheelScroll.delta * VELOCIDAD_SCROLL;

    superiorVista = posCentro.y - tamVista.y / 2.f;
    inferiorVista = posCentro.y + tamVista.y / 2.f;

    limiteSuperior = posUltimoMensaje.y;
    limiteInferior = 870;

    if ((desplazamientoY < 0) && (superiorVista + desplazamientoY < limiteSuperior))
        desplazamientoY = limiteSuperior - superiorVista;

    if ((desplazamientoY > 0) && (inferiorVista + desplazamientoY > limiteInferior))
        desplazamientoY = limiteInferior - inferiorVista;

    if (desplazamientoY != 0)
        sfView_move (recursosComunesContactosSalas->vistas.mensajes, (sfVector2f){0, desplazamientoY});

    return EVENTO_MANEJADO;
}



/* ============================================================================================================================================
   FUNCIONES COMPLEMENTARIAS
   ============================================================================================================================================ */



static void recursosComunesContactosSalas_inicializarValoresNulosFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

static void recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->auxEscribirMensaje = NULL;
    textos->proximaInterfaz = NULL;
    textos->nombreUsuario = NULL;
    textos->textoBotonEnviar = NULL;
    textos->tituloInterfaz = NULL;
}

static void recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = NULL;
    elementos->barraEscribirMensaje = NULL;
    elementos->botonEnviar = NULL;
    elementos->carpetaDecorativaFondo1 = NULL;
    elementos->carpetaDecorativaFondo2 = NULL;
    elementos->ojalilloArriba = NULL;
    elementos->ojalilloAbajo = NULL;
    elementos->ojalilloSelecInterfaz = NULL;
    elementos->separacionNombre = NULL;
    elementos->separacionTitulo = NULL;
    elementos->panelInterfaz = NULL;
    elementos->puntoInsercion = NULL;
    elementos->solapaCambiarInterfaz = NULL;
}

static void recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->UI = NULL;
    vistas->mensajes = NULL;
}


static int recursosComunesContactosSalas_inicializarFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("../../../client/assets/fonts/fuenteUI.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }

    fuentes->cuerpo = sfFont_createFromFile ("../../../client/assets/fonts/fuenteCuerpo.ttf");
    if (!fuentes->cuerpo)
    {
        perror ("\nERROR - Crear fuente cuerpo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    textos->auxEscribirMensaje = sfText_create ();
    if (!textos->auxEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto auxEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    textos->proximaInterfaz = sfText_create ();
    if (!textos->proximaInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto proximaInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    textos->nombreUsuario = sfText_create ();
    if (!textos->nombreUsuario)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto nombreUsuario.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoBotonEnviar = sfText_create ();
    if (!textos->textoBotonEnviar)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto textoBotonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloInterfaz = sfText_create ();
    if (!textos->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    elementos->areaMensajes = sfRectangleShape_create ();
    if (!elementos->areaMensajes)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento areaMensajes.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirMensaje = sfRectangleShape_create ();
    if (!elementos->barraEscribirMensaje)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento barraEscribirMensaje.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonEnviar = sfRectangleShape_create ();
    if (!elementos->botonEnviar)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento botonEnviar.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo1 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo1)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento carpetaDecorativaFondo1.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->carpetaDecorativaFondo2 = sfRectangleShape_create ();
    if (!elementos->carpetaDecorativaFondo2)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento carpetaDecorativaFondo2.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloArriba = sfCircleShape_create ();
    if (!elementos->ojalilloArriba)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloArriba");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloAbajo = sfCircleShape_create ();
    if (!elementos->ojalilloAbajo)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloAbajo");
        return ERROR_INICIALIZACION;
    }

    elementos->ojalilloSelecInterfaz = sfCircleShape_create ();
    if (!elementos->ojalilloSelecInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento ojalilloSelecInterfaz");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionNombre = sfRectangleShape_create ();
    if (!elementos->separacionNombre)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento separacionNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->separacionTitulo = sfRectangleShape_create ();
    if (!elementos->separacionTitulo)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento separacionTitulo.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->panelInterfaz = sfRectangleShape_create ();
    if (!elementos->panelInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento panelInterfaz.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->solapaCambiarInterfaz = sfRectangleShape_create ();
    if (!elementos->solapaCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear elemento solapaCambiarInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    vistas->UI = sfView_create ();
    if (!vistas->UI)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear vista de UI.\n");
        return ERROR_INICIALIZACION;
    }

    vistas->mensajes = sfView_create ();
    if (!vistas->mensajes)
    {
        perror ("\nERROR - Recursos comunes contactos-salas, crear vista de mensajes.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

static int recursosComunesContactosSalas_inicializarListaMensajes (t_contextoMensajes *contextoMensajes)
{
    sfText *vecMensajes [MAX_MENSAJES_MEMORIA];
    unsigned short int i;

    for (i = 0; i < MAX_MENSAJES_MEMORIA; i ++)
        vecMensajes[i] = NULL;

    for (i = 0; i < MAX_MENSAJES_MEMORIA; i ++)
    {
        vecMensajes[i] = sfText_create ();
        if (!(vecMensajes[i]))
        {
            printf ("\nERROR - No se pudo crear el mensaje[%u].\n", i);
            return ERROR_INICIALIZACION;
        }
        insertarSegundoCircular (&(contextoMensajes->listaMensajes), &(vecMensajes[i]), sizeof (sfText*));
    }


    return EXITO;
}


static void recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes)
{
    // auxEscribirMensaje
    sfText_setFont (textos->auxEscribirMensaje, fuentes->cuerpo);
    sfText_setFillColor (textos->auxEscribirMensaje, sfColor_fromRGB (53, 53, 53));

    // proximaInterfaz
    sfText_setFont (textos->proximaInterfaz, fuentes->ui);
    sfText_setString (textos->proximaInterfaz, "SALAS");
    sfText_setFillColor (textos->proximaInterfaz, sfColor_fromRGB (94, 91, 87));
    sfText_rotate (textos->proximaInterfaz, -90);

    // nombreUsuario
    sfText_setFont (textos->nombreUsuario, fuentes->ui);
    sfText_setFillColor (textos->nombreUsuario, sfColor_fromRGB (43, 43, 43));

    // textoBotonEnviar
    sfText_setFont (textos->textoBotonEnviar, fuentes->ui);
    sfText_setString (textos->textoBotonEnviar, "ENVIAR");
    sfText_setFillColor (textos->textoBotonEnviar, sfColor_fromRGB (94, 91, 87));

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->ui);
    sfText_setString (textos->tituloInterfaz, "CONTACTOS");
    sfText_setFillColor (textos->tituloInterfaz, sfColor_fromRGB (43, 43, 43));
}

static void recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    // areaMensajes
    sfRectangleShape_setFillColor (elementos->areaMensajes, sfColor_fromRGBA (244, 241, 236, 0));
    sfRectangleShape_setOutlineColor (elementos->areaMensajes, sfColor_fromRGB (107, 94, 75));

    // barraEscribirMensaje
    sfRectangleShape_setFillColor (elementos->barraEscribirMensaje, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirMensaje, sfColor_fromRGB (169, 163, 154));

    // botonEnviar
    sfRectangleShape_setFillColor (elementos->botonEnviar, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->botonEnviar, sfColor_fromRGB (169, 163, 154));

    // carpetaDecorativaFondo1
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGB (212, 206, 194));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo1, sfColor_fromRGBA (169, 163, 154, 191));

    // carpetaDecorativaFondo2
    sfRectangleShape_setFillColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGB (207, 201, 189));
    sfRectangleShape_setOutlineColor (elementos->carpetaDecorativaFondo2, sfColor_fromRGBA (169, 163, 154, 191));

    // ojalilloArriba
    sfCircleShape_setFillColor (elementos->ojalilloArriba, sfColor_fromRGBA (140, 136, 137, 191));
    sfCircleShape_setOutlineColor (elementos->ojalilloArriba, sfColor_fromRGBA (94, 91, 87, 191));

    // ojalilloAbajo
    sfCircleShape_setFillColor (elementos->ojalilloAbajo, sfColor_fromRGBA (140, 136, 137, 191));
    sfCircleShape_setOutlineColor (elementos->ojalilloAbajo, sfColor_fromRGBA (94, 91, 87, 191));

    // ojalilloSelecInterfaz
    sfCircleShape_setFillColor (elementos->ojalilloSelecInterfaz, sfColor_fromRGBA (140, 136, 137, 81));
    sfCircleShape_setOutlineColor (elementos->ojalilloSelecInterfaz, sfColor_fromRGBA (94, 91, 87, 61));

    // separacionNombre
    sfRectangleShape_setFillColor (elementos->separacionNombre, sfColor_fromRGB (107, 94, 75));

    // separacionTitulo
    sfRectangleShape_setFillColor (elementos->separacionTitulo, sfColor_fromRGB (107, 94, 75));

    // panelInterfaz
    sfRectangleShape_setFillColor (elementos->panelInterfaz, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->panelInterfaz, sfColor_fromRGB (169, 163, 154));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (94, 91, 87));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);

    // solapaCambiarInterfaz
    sfRectangleShape_setFillColor (elementos->solapaCambiarInterfaz, sfColor_fromRGB (217, 211, 199));
    sfRectangleShape_setOutlineColor (elementos->solapaCambiarInterfaz, sfColor_fromRGBA (169, 163, 154, 191));
}


static void recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos)
{
    // auxEscribirMensaje
    sfText_setPosition (textos->auxEscribirMensaje, (sfVector2f){449, 912});
    sfText_setCharacterSize (textos->auxEscribirMensaje, 24);

    // proximaInterfaz
    sfText_setPosition (textos->proximaInterfaz, (sfVector2f){343, 530});
    sfText_setCharacterSize (textos->proximaInterfaz, 20);
    sfText_setLetterSpacing (textos->proximaInterfaz, 5);

    // textoBotonEnviar
    sfText_setCharacterSize (textos->textoBotonEnviar, 22);
    centrarTextoEnArea (textos->textoBotonEnviar, 1747, 909, 115, 35);

    // tituloInterfaz
    sfText_setCharacterSize (textos->tituloInterfaz, 36);
    centrarTextoEnArea (textos->tituloInterfaz, 0, 0, 340, 120);
}

static void recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    // areaMensajes
    sfRectangleShape_setPosition (elementos->areaMensajes, (sfVector2f){442, 90});
    sfRectangleShape_setSize (elementos->areaMensajes, (sfVector2f){1420, 780});
    sfRectangleShape_setOutlineThickness (elementos->areaMensajes, 2);

    // barraEscribirMensaje
    sfRectangleShape_setPosition (elementos->barraEscribirMensaje, (sfVector2f){442, 909});
    sfRectangleShape_setSize (elementos->barraEscribirMensaje, (sfVector2f){1265, 38});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirMensaje, 2);

    // botonEnviar
    sfRectangleShape_setPosition (elementos->botonEnviar, (sfVector2f){1747, 909});
    sfRectangleShape_setSize (elementos->botonEnviar, (sfVector2f){115, 35});
    sfRectangleShape_setOutlineThickness (elementos->botonEnviar, 2);

    // carpetaDecorativaFondo1
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo1, (sfVector2f){370, 130});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo1, (sfVector2f){20, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo1, 1);

    // carpetaDecorativaFondo2
    sfRectangleShape_setPosition (elementos->carpetaDecorativaFondo2, (sfVector2f){390.2, 195});
    sfRectangleShape_setSize (elementos->carpetaDecorativaFondo2, (sfVector2f){16, 1009});
    sfRectangleShape_setOutlineThickness (elementos->carpetaDecorativaFondo2, 1);

    // ojalilloArriba
    sfCircleShape_setPosition (elementos->ojalilloArriba, (sfVector2f){5, 400});
    sfCircleShape_setRadius (elementos->ojalilloArriba, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloArriba, 1);

    // ojalilloAbajo
    sfCircleShape_setPosition (elementos->ojalilloAbajo, (sfVector2f){5, 600});
    sfCircleShape_setRadius (elementos->ojalilloAbajo, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloAbajo, 1);

    // ojalilloSelecInterfaz
    sfCircleShape_setPosition (elementos->ojalilloSelecInterfaz, (sfVector2f){347, 80});
    sfCircleShape_setRadius (elementos->ojalilloSelecInterfaz, 8);
    sfCircleShape_setOutlineThickness (elementos->ojalilloSelecInterfaz, 1);

    // separacionNombre
    sfRectangleShape_setPosition (elementos->separacionNombre, (sfVector2f){44, 889});
    sfRectangleShape_setSize (elementos->separacionNombre, (sfVector2f){254, 2});

    // separacionTitulo
    sfRectangleShape_setPosition (elementos->separacionTitulo, (sfVector2f){44, 120});
    sfRectangleShape_setSize (elementos->separacionTitulo, (sfVector2f){254, 2});

    // panelInterfaz
    sfRectangleShape_setPosition (elementos->panelInterfaz, (sfVector2f){0, 0});
    sfRectangleShape_setSize (elementos->panelInterfaz, (sfVector2f){340, 1009});
    sfRectangleShape_setOutlineThickness (elementos->panelInterfaz, 2);

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){28, 2});

    // solapaCambiarInterfaz
    sfRectangleShape_setPosition (elementos->solapaCambiarInterfaz, (sfVector2f){342.5, 65});
    sfRectangleShape_setSize (elementos->solapaCambiarInterfaz, (sfVector2f){28, 1009});
    sfRectangleShape_setOutlineThickness (elementos->solapaCambiarInterfaz, 1.5);
}

static void recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    // UI
    sfView_setSize (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->UI, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});

    // mensajes
    sfView_setSize (vistas->mensajes, (sfVector2f){1420, 780});                             // Vista del tamanio del sfRectangleShape *areaMensajes
    sfView_setCenter (vistas->mensajes, (sfVector2f){1152, 480});                           // Centro del sfRectangleShape *areaMensajes
    sfView_setViewport(vistas->mensajes, (sfFloatRect){0.230f, 0.089f, 0.740f, 0.773f});    // Proporciones del sfRectangleShape *areaMensajes
}


static void recursosComunesContactosSalas_liberarFuentes (t_recursosComunesContactosSalasFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

static void recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirMensaje);
    DESTRUCTOR_SEGURO_TEXTO (textos->proximaInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->nombreUsuario);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoBotonEnviar);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
}

static void recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->areaMensajes);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirMensaje);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonEnviar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo1);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->carpetaDecorativaFondo2);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloArriba);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloAbajo);
    DESTRUCTOR_SEGURO_CIRCULO (elementos->ojalilloSelecInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->separacionTitulo);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->panelInterfaz);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->solapaCambiarInterfaz);
}

static void recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas)
{
    DESTRUCTOR_SEGURO_VISTA (vistas->UI);
    DESTRUCTOR_SEGURO_VISTA (vistas->mensajes);
}





























