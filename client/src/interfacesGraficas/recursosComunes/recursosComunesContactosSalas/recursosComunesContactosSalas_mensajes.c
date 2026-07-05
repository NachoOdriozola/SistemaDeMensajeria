#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas_mensajes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void configurarMensaje (sfText *mensaje, sfFont *fuente);
static void establecerTextoConSaltosDeLineaAlMensaje (sfText *texto, const char *bufferMensaje, float anchoMax);
static void desplazarHaciaArribaTodosLosMensajes (t_listaDoble *mensajes, float desplazamientoY);
static void establecerPosicionMensajeSegunOrigen (sfText *mensaje, t_origenMensaje origenMensaje);
static bool esElPrimerMensaje (t_contextoMensajes *contextoMensajes);
static void guardarSuReferencia (t_contextoMensajes *contextoMensajes);
static void renderizarMensaje (void *mensaje, void *renderizado);
static void liberarMensaje (void *mensaje);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _recursosComunesContactosSalas_crearListaMensajes (t_contextoMensajes *contextoMensajes)
{
    crearListaDoble (&(contextoMensajes->mensajes));
    contextoMensajes->ultimoMensaje = NULL;
}

t_codigoRetorno recursosComunesContactosSalas_insertarMensajeAListaMensajes (t_contextoMensajes *contextoMensajes, char *mensaje, t_origenMensaje origenMensaje, t_recursosComunesContactosSalasFuentes *fuentes)
{
    sfText *mensajeGrafico;

    mensajeGrafico = sfText_create ();
    if (!mensajeGrafico)
    {
        perror ("\nERROR - Crear mensaje grafico.\n");
        return ERROR_SIN_MEMORIA;
    }
    configurarMensaje (mensajeGrafico, fuentes->cuerpo);
    establecerTextoConSaltosDeLineaAlMensaje (mensajeGrafico, mensaje, 700);
    desplazarHaciaArribaTodosLosMensajes (&(contextoMensajes->mensajes), (sfText_getLocalBounds (mensajeGrafico)).height + 35);
    establecerPosicionMensajeSegunOrigen (mensajeGrafico, origenMensaje);
    if (insertarAlInicioListaDoble (&(contextoMensajes->mensajes), &mensajeGrafico, sizeof (sfText*)) != 0) // 0 es exito.
        return ERROR_SIN_MEMORIA;
    if (esElPrimerMensaje (contextoMensajes))
        guardarSuReferencia (contextoMensajes);

    return EXITO;
}

void recursosComunesContactosSalas_setearVistaMensajesYRenderizarListaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- SETEAR VISTA DE MENSAJES ---------------
    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.mensajes);

    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------
    mapListaDobleConComplemento (&(recursosComunesContactosSalas->logica.contextoMensajes.mensajes), renderizarMensaje, renderizado);
}

void recursosComunesContactosSalas_vaciarListaMensajes (t_contextoMensajes *contextoMensajes)
{
    mapListaDoble (&(contextoMensajes->mensajes), liberarMensaje);
    contextoMensajes->ultimoMensaje = NULL;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Aun no establece la posicion ni el contenido del mensaje.
*/
static void configurarMensaje (sfText *mensajeGrafico, sfFont *fuente)
{
    sfText_setFont (mensajeGrafico, fuente);
    sfText_setFillColor (mensajeGrafico, sfColor_fromRGB (53, 53, 53));
    sfText_setCharacterSize (mensajeGrafico, 22);
    sfText_setLineSpacing (mensajeGrafico, 1.3);
}

static int encontrarUnaPalabraYRetornarSuLargo (const char *cadena)
{
    int largoPalabra = 0;

    while ((cadena[largoPalabra] != '\0') && (cadena[largoPalabra] != ' '))
        largoPalabra++;

    return largoPalabra;
}

static bool palabraSobrepasoAnchoPermitido (sfVector2f posUltimoCaracter, float anchoMaxMensaje)
{
    return (posUltimoCaracter.x >= anchoMaxMensaje);
}

static void agregarSaltoDeLinea (char *cadena)
{
    strcat (cadena, "\n");
}

/*
 * Si la palabra sobrepasa el ancho permitido, agrega un salto de linea.
*/
static void procesarPalabra (sfText *mensajeGrafico, const char *cadenaMensaje, char *auxCadenaMensaje, float anchoMaxMensaje, int largoPalabra)
{
    int largoAuxCadenaMensaje, i;
    sfVector2f posUltimoCaracter;

    for (i = 0; i < largoPalabra; i++)
    {
        largoAuxCadenaMensaje = strlen (auxCadenaMensaje);

        auxCadenaMensaje[largoAuxCadenaMensaje] = cadenaMensaje[i];
        auxCadenaMensaje[largoAuxCadenaMensaje + 1] = '\0';

        sfText_setString (mensajeGrafico, auxCadenaMensaje);
        posUltimoCaracter = sfText_findCharacterPos (mensajeGrafico, largoAuxCadenaMensaje + 1);

        if (palabraSobrepasoAnchoPermitido (posUltimoCaracter, anchoMaxMensaje))
            agregarSaltoDeLinea (auxCadenaMensaje);
    }
}

static void encontrarPrimerCaracterProximaPalabra (const char **cadenaMensaje, char *auxCadenaMensaje, int largoUltimaPalabra)
{
    (*cadenaMensaje) += largoUltimaPalabra;
    while (**cadenaMensaje == ' ')
    {
        strcat (auxCadenaMensaje, " ");
        (*cadenaMensaje) ++;
    }
}

/*
* El ancho maximo del mensaje tiene que ser enviado en pixeles.
*/
static void establecerTextoConSaltosDeLineaAlMensaje (sfText *mensajeGrafico, const char *cadenaMensaje, float anchoMaxMensaje)
{
    char auxCadenaMensaje [MAX_MENSAJE + 100] = ""; // Almacena la cadena del mensaje mas los saltos de linea a agregar.
    int largoPalabra;

    sfText_setPosition (mensajeGrafico, (sfVector2f){0, 0}); // Establece una posicion ficticia al mensaje para que pueda ser procesado.

    while (*cadenaMensaje != '\0')
    {
        largoPalabra = encontrarUnaPalabraYRetornarSuLargo (cadenaMensaje);
        procesarPalabra (mensajeGrafico, cadenaMensaje, auxCadenaMensaje, anchoMaxMensaje, largoPalabra);
        encontrarPrimerCaracterProximaPalabra (&cadenaMensaje, auxCadenaMensaje, largoPalabra);
    }

    sfText_setString(mensajeGrafico, auxCadenaMensaje);
}

static void modificarPosMensaje (void *mensaje, void *desplazamientoY)
{
    sfVector2f pos;

    pos = sfText_getPosition (*((sfText**)mensaje));
    pos.y -= *((float*)desplazamientoY);
    sfText_setPosition (*((sfText**)mensaje), pos);
}

static void desplazarHaciaArribaTodosLosMensajes (t_listaDoble *mensajes, float desplazamientoY)
{
    mapListaDobleConComplemento (mensajes, modificarPosMensaje, &desplazamientoY);
}

static void establecerPosicionMensajeSegunOrigen (sfText *mensaje, t_origenMensaje origenMensaje)
{
    sfFloatRect limitesMensaje = sfText_getLocalBounds (mensaje);

    if (origenMensaje == MENSAJE_PROPIO)
        sfText_setPosition (mensaje, (sfVector2f){1824 - limitesMensaje.width - limitesMensaje.left, 825 - limitesMensaje.height});
    else
        sfText_setPosition (mensaje, (sfVector2f){485, 825 - limitesMensaje.height});
}

static bool esElPrimerMensaje (t_contextoMensajes *contextoMensajes)
{
    return (contextoMensajes->ultimoMensaje == NULL);
}

static void guardarSuReferencia (t_contextoMensajes *contextoMensajes)
{
    contextoMensajes->ultimoMensaje = contextoMensajes->mensajes;
}

static void renderizarMensaje (void *mensaje, void *renderizado)
{
    sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *((sfText**)mensaje), NULL);
}

static void liberarMensaje (void *mensaje)
{
    DESTRUCTOR_SEGURO_TEXTO (*((sfText**)mensaje));
}

