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
 * \def CONTINUAR_APLICACION
 * \brief Codigo para continuar ejecutando la aplicacion.
 */
#define CONTINUAR_APLICACION 1

/**
 * \def DETENER_APLICACION
 * \brief Codigo para detener la aplicacion en caso de error o que el usuario la cierre.
 */
#define DETENER_APLICACION 0


/**
 * \def TAMANIO_BASE_MAXIMIZADO_X
 * \brief Tamanio en X de la ventana (QUE UTILIZO YO) maximizada. Utilizado para crear escalas de pixeles.
 */
#define TAMANIO_BASE_MAXIMIZADO_X 1920

/**
 * \def TAMANIO_BASE_MAXIMIZADO_Y
 * \brief Tamanio en Y de la ventana (QUE UTILIZO YO) maximizada. Utilizado para crear escalas de pixeles.
 */
#define TAMANIO_BASE_MAXIMIZADO_Y 1009


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
 * \def AUTENTICACION_AUTOMATICA
 * \brief Codigo de retorno para indicar que el usuario puede autenticarse automaticamente.
 */
#define AUTENTICACION_AUTOMATICA 1

/**
 * \def AUTENTICACION_MANUAL
 * \brief Codigo de retorno para indicar que el usuario debe autenticarse manualmente.
 */
#define AUTENTICACION_MANUAL 0


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
 * \brief Cantidad maxima de mensajes de la lista circular de mensajes que se guardan en memoria.
 */
#define MAX_MENSAJES_MEMORIA 5


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


//a chekear
#define MAX_BUFFER_MENSAJE 256

//a chekear
#define MI_USUARIO 1
#define OTRO_USUARIO 0



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
 * \struct s_usuario
 * \brief  Representa un usuario.
 */
typedef struct
{
    int id;                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];           /**< Nombre correspondiente del usuario. */
    unsigned short int interfazActual;          /**< Interfaz sobre la cual se encuentra ubicado actualmente. */
    unsigned short int ultimaInterfazUtilizada; /**< Ultima interfaz sobre la cual se encontro ubicado el usuario. */
} s_usuario;

/**
 * \struct s_ventana
 * \brief  Contiene valores importantes sobre el tamanio de la ventana.
 */
typedef struct
{
    sfVector2f tamVentana;      /**< Tamanio actual de la ventana. */
    sfVector2f escalaElementos; /**< Valores de escala de elementos en X e Y. */
    float escalaPixeles;        /**< Valor escala en pixeles. */
} s_ventana;

/**
 * \struct s_fuentes
 * \brief  Estructura que contiene las fuentes graficas para los textos.
 */
typedef struct
{
    sfFont *fuente1;
} s_fuentes;

/**
 * \struct s_mensajes
 * \brief
 */
typedef struct
{
    s_listaCircular listaMensajes; /**< Lista circular de mensajes. */
    s_nodo *siguienteMensaje;      /**< Puntero al nodo que contiene el siguiente mensaje en la lista circular de mensajes. */
    s_fuentes fuentes;
} s_mensajes;

/**
 * \struct s_aplicacion
 * \brief  Estructura base de la aplicacion
 */
typedef struct
{
    sfRenderWindow *renderizado;        /**< Renderizado de la ventana. */
    SOCKET sock;                        /**< Socket del usuario. */
    s_ventana ventana;
    s_usuario usuario;
    s_mensajes mensajes;
    s_listaSimple listaNotificaciones;  /**< Lista simple de notificaciones. */
} s_aplicacion;

/**
 * \struct s_notificacion
 * \brief  Estructura que contiene los elementos de una notificacion.
 */
typedef struct
{
    sfRectangleShape *recuadro;
    sfRectangleShape *botonAceptar;
    sfRectangleShape *botonRechazar;
    sfText *textoNotificacion;
    sfText *textoBotonAceptar;
    sfText *textoBotonRechazar;
} s_notificacion;

/**
 * \struct s_datosGuardados
 * \brief  Estructura que guarda los datos de autenticacion del usuario.
 */
typedef struct
{
    int id;
    char nombre [MAX_NOMBRE_USUARIO];
} s_datosGuardados;



/* ============================
   FUNCIONES DE VENTANA
   ============================ */



/** \brief Crear escala en X e Y para elementos graficos.
 *
 * Crear valores escalares en X e Y, por medio de regla de 3, para poder establecer tamanios y posiciones de los elementos graficos en la ventana.
 *
 * \param ventana Puntero a la estructura que contiene los valores de la ventana.
 *
 */
void crearEscalaElementos (s_ventana *ventana);

/** \brief Crear escala en pixeles para elementos graficos.
 *
 * Crear valor escalar en pixeles, por medio de regla de 3, para poder establecer tamanios y posiciones de los elementos graficos en la ventana.
 * Selecciona el valor mas pequenio entre X e Y.
 *
 * \param ventana Puntero a la estructura que contiene los valores de la ventana.
 *
 */
void crearEscalaPixeles (s_ventana *ventana);

/** \brief Procesar el evento de maximizado automatico de la ventana y guardar sus valores.
 *
 * Procesar todos los eventos ocurridos hasta encontrar el de maximizado de la ventana, una vez encontrado, guarda los valores de la ventana en la
 * estructura de la ventana.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param ventana Puntero a la estructura que contiene los valores de la ventana.
 *
 */
void eventoMaximizadoAutomatico (sfRenderWindow *renderizado, s_ventana *ventana);

/** \brief Maximizar automaticamente la ventana y guardar sus valores.
 *
 * Maximizar la ventana y crear las escalas de elementos y pixeles.
 * Utilizar cuando se desee maximizar la ventana automaticamente (sin intervencion del usuario).
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param ventana Puntero a la estructura que contiene los valores de la ventana.
 *
 */
void maximizadoAutomaticoVentana (sfRenderWindow *renderizado, s_ventana *ventana);



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
int inicializarFuentes (s_fuentes *fuentes);

/** \brief Liberar todos los recursos graficos de fuentes creados.
 *
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas para los textos.
 *
 */
void liberarFuentes (s_fuentes *fuentes);



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
   FUNCIONES DE GUARDADO DE AUTENTICACION
   ============================ */



int guardarDatosEnArchivo (int id, const char *bufferContrasenia);

/** \brief Verificar como se autenticara el usuario.
 *
 * Intenta abrir el archivo que contiene los datos guardados del usuario. En caso de que no exista, el usuario debe autenticarse manualmente, en caso contrario se guardaran
 * sus datos en la estructura que contiene los datos del usuario en la aplicacion y se autenticara automaticamente.
 *
 * \param usuario Puntero a la estructura que contiene los datos del usuario.
 *
 * \return AUTENTICACION_AUTOMATICA si se guardaron los datos de autenticacion, AUTENTICACION_MANUAL en caso contrario.
 *
 */
bool verificarModoAutenticacion (s_usuario *usuario);



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



void asignarMensaje (s_aplicacion *aplicacion, const char *bufferMensaje, bool enviadoPor);
void modificarPosListaMensajes (void *mensaje);
void renderizarListaMensajes (void *mensaje, void *renderizado);
void setupListaMensajes (void *mensaje, void *fuente);
void tamListaMensajes (void *mensaje, void *escalaPixeles);
void liberarMensaje (void *mensaje);



/* ============================
   FUNCIONES DE NOTIFICACIONES
   ============================ */



int crearNotificacion (s_notificacion *notificacion);
void setupNotificacion (s_notificacion *notificacion, s_ventana ventana, s_fuentes fuentes);
int agregarNotificacion (s_listaSimple *listaNotificaciones, char *bufferNotificacion, s_ventana ventana, s_fuentes fuentes);
void liberarNotificacion (void *notificacion);
void renderizarListaNotificaciones (void *notificacion, void *renderizado);



#endif // LOGICAUSUARIO_H_INCLUDED




































