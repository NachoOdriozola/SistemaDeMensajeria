/**
 * \file   logicaUsuario.h
 * \brief  Define las estructuras principales del programa, y contiene funciones logicas generales.
 */



#ifndef LOGICAUSUARIO_H_INCLUDED
#define LOGICAUSUARIO_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaCircular.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def ANCHO_LOGICO_VENTANA
 * \brief Ancho/tamanio en x, logico de la ventana.
 */
#define ANCHO_LOGICO_VENTANA 1920

/**
 * \def ALTO_LOGICO_VENTANA
 * \brief Alto/tamanio en y, logico de la ventana.
 */
#define ALTO_LOGICO_VENTANA 1009


/**
 * \def INTERFAZ_AUTENTICACION
 * \brief Identificador de la interfaz de autenticacion.
 */
#define INTERFAZ_AUTENTICACION 1

/**
 * \def INTERFAZ_CONFIG
 * \brief Identificador de la interfaz de configuraciones.
 */
#define INTERFAZ_CONFIG 2

/**
 * \def INTERFAZ_CONTACTOS
 * \brief Identificador de la interfaz de contactos.
 */
#define INTERFAZ_CONTACTOS 3

/**
 * \def INTERFAZ_REGISTRO
 * \brief Identificador de la interfaz de registro.
 */
#define INTERFAZ_REGISTRO 4

/**
 * \def INTERFAZ_SALAS
 * \brief Identificador de la interfaz de salas.
 */
#define INTERFAZ_SALAS 5


/**
 * \def RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que se recibio una respuesta del servidor.
 */
#define RECIBIO_RESPUESTA 1

/**
 * \def NO_RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que no se recibio una respuesta del servidor.
 */
#define NO_RECIBIO_RESPUESTA 0


/**
 * \def MAX_MENSAJES_MEMORIA
 * \brief Cantidad maxima de mensajes que se guardan en memoria en la lista circular de mensajes.
 */
#define MAX_MENSAJES_MEMORIA 25


/**
 * \def EVENTO_MANEJADO
 * \brief Codigo de retorno para indicar que el evento fue manejado.
 */
#define EVENTO_MANEJADO 1

/**
 * \def EVENTO_NO_MANEJADO
 * \brief Codigo de retorno para indicar que el evento no fue manejado.
 */
#define EVENTO_NO_MANEJADO 0


/**
 * \def HABILITAR_PUNTO_INSERCION
 * \brief Codigo para activar el punto de insercion.
 */
#define HABILITAR_PUNTO_INSERCION 1

/**
 * \def DESHABILITAR_PUNTO_INSERCION
 * \brief Codigo para desactivar el punto de insercion.
 */
#define DESHABILITAR_PUNTO_INSERCION 0

/**
 * \def VELOCIDAD_PARPADEO_PUNTO_INSERCION
 * \brief Constante que determina la velocidad de parpadeo del punto de insercion.
 */
#define VELOCIDAD_PARPADEO_PUNTO_INSERCION 22

/**
 * \def REINICIAR_CONTADOR_PUNTO_INSERCION
 * \brief Constante para reiniciar el contador del punto de insercion.
 */
#define REINICIAR_CONTADOR_PUNTO_INSERCION 0



/* ============================
   MACROS
   ============================ */



/**
 * \brief Libera de forma segura un objeto de tipo vista (sfView) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfView_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfView` a destruir.
 */
#define DESTRUCTOR_SEGURO_VISTA(x) if(x) {sfView_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo texto (sfText) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfText_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfText` a destruir.
 */
#define DESTRUCTOR_SEGURO_TEXTO(x) if(x) {sfText_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo rectangulo (sfRectangleShape) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfRectangleShape_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfRectangleShape` a destruir.
 */
#define DESTRUCTOR_SEGURO_RECTANGULO(x) if(x) {sfRectangleShape_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo circulo (sfCircleShape) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfCircleShape_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfCircleShape` a destruir.
 */
#define DESTRUCTOR_SEGURO_CIRCULO(x) if(x) {sfCircleShape_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo fuente (sfFont) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfFont_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfFont` a destruir.
 */
#define DESTRUCTOR_SEGURO_FUENTE(x) if(x) {sfFont_destroy(x); x = NULL;}



/* ============================
   ESTRUCTURAS
   ============================ */



/**
 * \struct t_usuario
 * \brief  Representa un usuario.
 */
typedef struct
{
    int id;                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];           /**< Nombre correspondiente del usuario. */
    unsigned short int interfazActual;          /**< Interfaz sobre la cual se encuentra ubicado actualmente. */
} t_usuario;

/**
 * \struct t_fuentes
 * \brief  Estructura que contiene las fuentes graficas para los textos.
 */
typedef struct
{
    sfFont *ui;             /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;         /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} t_fuentes;

/**
 * \struct t_mensajes
 * \brief
 */
typedef struct
{
    t_listaCircular listaMensajes;      /**< Lista circular de mensajes. */
    t_nodo *primerMensaje;              /**< Puntero al primer mensaje de la lista circular de mensajes. */
    t_nodo *ultimoMensaje;              /**< Puntero al ultimo mensaje de la lista circular de mensajes. */
    t_fuentes fuentes;
} t_mensajes;

/**
 * \struct t_aplicacion
 * \brief  Estructura base de la aplicacion
 */
typedef struct
{
    sfRenderWindow *renderizado;        /**< Renderizado de la ventana. */
    SOCKET sock;                        /**< Socket del usuario. */
    t_usuario usuario;
    t_mensajes mensajes;
    t_listaSimple listaNotificaciones;  /**< Lista simple de notificaciones. */
} t_aplicacion;

/**
 * \struct t_notificacion
 * \brief  Estructura que contiene los elementos de una notificacion.
 * \note Estructura NO ACTIVA en el Incremento 1.
 */
typedef struct
{
    sfRectangleShape *recuadro;
    sfRectangleShape *botonAceptar;
    sfRectangleShape *botonRechazar;
    sfText *textoNotificacion;
    sfText *textoBotonAceptar;
    sfText *textoBotonRechazar;
} t_notificacion;

typedef enum
{
    MENSAJE_PROPIO,
    MENSAJE_REMOTO
} t_origenMensaje;



/* ============================
   FUNCIONES DE FUENTES
   ============================ */



/** \brief Inicializar los recursos graficos de las fuentes graficas para texto.
 *
 * Establecer todas las variables graficas de fuentes en NULL y luego crearlas desde archivos .ttf.
 *
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas para los textos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int inicializarFuentes (t_fuentes *fuentes);

/** \brief Liberar todos los recursos graficos de fuentes creados.
 *
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas para los textos.
 *
 */
void liberarFuentes (t_fuentes *fuentes);



/* ============================
   FUNCIONES DE SOCKETS
   ============================ */



/** \brief Recibir una respuesta del servidor a traves del socket.
 *
 * Intentar leer datos disponibles en el socket especificado.
 * Si se recibe una respuesta, asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * No bloquea el socket.
 *
 * \param sock Socket del usuario desde el cual se recibe la respuesta.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 *
 * \return RECIBIO_RESPUESTA en caso de que haya recibido respuesta, NO_RECIBIO_RESPUESTA en caso contrario.
 *
 */
bool recibirRespuesta (SOCKET sock, char *bufferRespuesta);

/** \brief Enviar una solicitud al servidor y esperar a recibir su respuesta.
 *
 * Envia una solicitud almacenada en el bufferSolicitud y recibe una respuesta que se almacenara en el bufferRespuesa. Todo el proceso se comunica mediante el socket especificado.
 * Asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * Cambiar temporalmente el modo del socket a bloqueante para asegurar que el envio y la recepcion se completen antes de continuar. Una vez realizado el proceso, se desbloquea.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param bufferSolicitud Buffer que contiene la solicitud a enviar.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 *
 */
void enviarSolicitudYRecibirRespuesta (SOCKET sock, const char *bufferSolicitud, char *bufferRespuesta);



/* ============================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================ */



/** \brief Verificar si el usuario clickeo un rectangulo grafico en pantalla.
 *
 * Obtiene la posicion del mouse en pantalla y los limites del rectangulo para saber si el usuario lo clickeo.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param rectangulo Puntero al rectangulo grafico.
 *
 * \return True en caso de que el usuario lo clickeo, False en caso contrario.
 *
 */
bool clickEnRectangulo (const sfRenderWindow *renderizado, const sfRectangleShape *rectangulo);

/** \brief Verificar si el usuario clickeo un texto grafico en pantalla.
 *
 * Obtiene la posicion del mouse en pantalla y los limites del texto para saber si el usuario lo clickeo.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param texto Puntero al texto grafico.
 *
 * \return True en caso de que el usuario lo clickeo, False en caso contrario.
 *
 */
bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto);

/** \brief Centrar un texto dentro de una area.
 *
 * \param texto Puntero al texto sfText a centrar.
 * \param posXInicial Posicion en X donde comienza el area.
 * \param posYInicial Posicion en Y donde comienza el area.
 * \param anchoArea Ancho (x) del area.
 * \param altoArea Alto (y) del area.
 *
 */
void centrarTextoEnArea (sfText *texto, float posXInicial, float posYInicial, float anchoArea, float altoArea);

/** \brief Posicionar y centrar el nombre de usuario.
 *
 * Si el nombre de usuario no entra dentro del area establecida, se achica el tamanio del texto hasta que quede centrado.
 *
 * \param nombre Puntero al texto del nombre sfText a posicionar.
 *
 */
void posicionarNombreUsuario (sfText *nombre);

/** \brief Limitar la visualizacion de texto ingresado por el usuario sobre la barra de escritura.
 *
 * \param texto Puntero al texto sfText ingresado por el usuario.
 * \param bufferTexto Puntero al buffer que contiene el texto a mostrar.
 * \param anchoBarra Ancho de la barra de escritura.
 */
void limitarVisualizarTextoSobreBarra (sfText *texto, const char *bufferTexto, float anchoBarra);



/* ============================
   FUNCIONES DE ESCRITURA
   ============================ */



/** \brief Ingresar un caracter almacenado en un evento a un buffer.
 *
 * Procesar el caracter y colocarlo en la posicion que corresponda dentro del buffer.
 * Acepta el caracter "Backspace" para borrado de texto.
 * Si la tecla es "Enter" retorna.
 *
 * \param buffer Puntero al buffer donde se almacenara el caracter.
 * \param tamMaxBuffer Tamanio maximo del buffer. Es por como esta definido, ej: char buffer [5], el tamanio maximo es '5'.
 * \param eventoChar Variable de evento que contiene el caracter.
 *
 */
void ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar);



/* ============================
   FUNCIONES DE PUNTO DE INSERCION
   ============================ */



/** \brief Actualizar el punto de insercion segun su estado.
 *
 * Avanzar el contador del punto de insercion. Si el punto de insercion alcanza la velocidad (constante) establecida, se reinicia el contador y se actualiza (activa/desactiva) segun su estado:
 * si el punto de insercion esta deshabilitado, se habilita.
 * si el punto de insercion esta habilitado, se deshabilita.
 *
 * \param puntoInsercion Habilitacion para activar/desactivar (mostrar o no) el punto de insercion.
 * \param contadorPuntoInsercion Contador para activar/desactivar determinado tiempo el punto de insercion.
 *
 */
void actualizarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion);

/** \brief Reiniciar el punto de insercion.
 *
 * Deshabilitar (desactivar) el parpadeo del punto de insercion y reiniciar su contador.
 *
 * \param puntoInsercion Habilitacion para activar/desactivar (mostrar o no) el punto de insercion.
 * \param contadorPuntoInsercion Contador para activar/desactivar determinado tiempo el punto de insercion.
 *
 */
void reiniciarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion);



/* ============================
   FUNCIONES DE LISTA DE MENSAJES
   ============================ */



/** \brief Configurar un mensaje.
 *
 * Establecerle un color y la fuente enviada como parametro.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param fuente Puntero a fuente sfFont.
 *
 */
void configurarMensaje (void *mensaje, void *fuente);

/** \brief Establecer un tamanio a un mensaje. Ademas, agrega un espaciado de linea.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void tamMensaje (void *mensaje);

/** \brief Renderizar un mensaje.
 *
 * No se limpia ni muestra la ventana, solo lo renderiza.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void renderizarMensaje (void *mensaje, void *renderizado);

/** \brief Liberar un mensaje sfText.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void liberarMensaje (void *mensaje);

/** \brief Modificar la posicion de un mensaje.
 *
 * Unicamente modifica la posicion en Y del mensaje.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param desplazamientoY Puntero a la cantidad de desplazamiento en Y que se desea modificar.
 *
 */
void modificarPosMensaje (void *mensaje, void *desplazamientoY);

/** \brief Establecer los saltos de linea necesarios a un mensaje sfText.
 *
 * Establecer una cadena valida al texto sfText, con saltos de linea incorporados, que las lineas no sobrepasen el ancho maximo enviado como parametro.
 *
 * \param texto Puntero al mensaje sfText.
 * \param bufferMensaje Buffer que almacena el mensaje completo (sin saltos de linea).
 * \param anchoMax Ancho maximo que no debe sobrepasar los limites del mensaje.
 *
 */
void establecerSaltoDeLineaMensaje (sfText *texto, const char *bufferMensaje, float anchoMax);

/** \brief Insertar un mensaje a la lista circular de mensajes.
 *
 * Trabaja sobre el puntero al nodo del primer mensaje de la lista circular.
 * Establecer los saltos de linea necesarios para que el mensaje no sobrepase los limites establecidos.
 * Desplazar en Y a toda la lista circular de mensajes. El desplazamiento depende del alto del mensaje a insertar.
 * Dependiendo del origen del mensaje, se establece una posicion u otra al mismo.
 * Actualizar correspondientemente los punteros a nodo del primer y ultimo mensaje de la lista circular de mensajes.
 *
 * \param mensajes Puntero a la estructura que almacena datos sobre los mensajes.
 * \param bufferMensaje Buffer que almacena el mensaje completo.
 * \param origen Origen de quien envio mensaje.
 *
 */
void insertarMensaje (t_mensajes *mensajes, const char *bufferMensaje, t_origenMensaje origen);



/* ============================
   FUNCIONES DE NOTIFICACIONES
   ============================ */



/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
int crearNotificacion (t_notificacion *notificacion);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void setupNotificacion (t_notificacion *notificacion, t_fuentes fuentes);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
int agregarNotificacion (t_listaSimple *listaNotificaciones, char *bufferNotificacion, t_fuentes fuentes);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void liberarNotificacion (void *notificacion);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void renderizarListaNotificaciones (void *notificacion, void *renderizado);



#endif // LOGICAUSUARIO_H_INCLUDED




































