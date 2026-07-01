#include "../../../../include/interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas_mensajes.h"


void _recursosComunesContactosSalas_configurarContextoMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    *(recursosComunesContactosSalas->logica.contextoMensajes.mensaje) = '\0';
    recursosComunesContactosSalas->logica.contextoMensajes.primerMensaje = recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes;
    recursosComunesContactosSalas->logica.contextoMensajes.ultimoMensaje = recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes;

    mapListaCircularConComplemento (&(recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes), recursosComunesContactosSalas->fuentes.cuerpo, configurarMensaje);
    mapListaCircular (&(recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes), tamMensaje);
}

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
    char bufferTexto[MAX_MENSAJE + 100] = "";

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

void renderizarVistaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- ESTABLECER VISTA DE MENSAJES ---------------

    sfRenderWindow_setView (renderizado, recursosComunesContactosSalas->vistas.mensajes);


    // --------------- RENDERIZAR LISTA DE MENSAJES ---------------

    mapListaCircularConComplemento (&(recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes), renderizado, renderizarMensaje);
}

