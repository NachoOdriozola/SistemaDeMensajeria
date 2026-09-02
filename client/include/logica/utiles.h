/**
 * \file   utiles.h
 * \brief  Contiene constantes, macros, estructuras y funciones logicas utiles.
 */


#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "constantes.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


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
 * \def CONTADOR_REINICIAR
 * \brief Constante para reiniciar el contador.
 */
#define CONTADOR_REINICIAR 0


/**
 * \def VELOCIDAD_PARPADEO_PUNTO_INSERCION
 * \brief Constante que determina la velocidad de parpadeo del punto de insercion.
 */
#define VELOCIDAD_PARPADEO_PUNTO_INSERCION 22


/**
 * \def TEXTO_DE_CARGA_ESTADO_INICIAL
 * \brief Estado con el que comienza el texto de carga.
 */
#define TEXTO_DE_CARGA_ESTADO_INICIAL 0

/**
 * \def TEXTO_DE_CARGA_ESTADO_FINAL
 * \brief Estado con el que finaliza el texto de carga.
 */
#define TEXTO_DE_CARGA_ESTADO_FINAL 3

/**
 * \def TEXTO_DE_CARGA_VELOCIDAD_ACTUALIZACION
 * \brief Velocidad con la que cambia de estado del texto de carga.
 */
#define TEXTO_DE_CARGA_VELOCIDAD_ACTUALIZACION 18


/* ============================================================================================================================================
   MACROS
   ============================================================================================================================================ */


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


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \enum t_habilitacion
 * \brief Representa el estado de habilitacion de un recurso o funcionalidad. Activo (HABILITADO) o inactivo (DESHABILITADO).
 */
typedef enum
{
    HABILITADO,
    DESHABILITADO
} t_habilitacion;

/** \struct t_puntoInsercion
 * \brief Gestiona el punto de insercion logicamente.
 */
typedef struct
{
    t_habilitacion estado;                    /**< Activar/desactivar el punto de insercion. */
    unsigned short int contador;        /**< Contador para determinar el tiempo en el que se activa/desactiva el punto de insercion. */
} t_puntoInsercion;


/** \struct t_textoDeCarga
 * \brief Gestiona el texto de carga logicamente.
 */
typedef struct
{
   unsigned short int estado;             /**< Estado en el que se encuentra el texto de carga. */
   unsigned short int contador;         /**< Contador para modificar el estado. */
} t_textoDeCarga;


/* ============================================================================================================================================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================================================================================================================================ */


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

/** \brief Limitar la visualizacion de texto ingresado por el usuario en caso de que no entre sobre la barra de escritura.
 * 
 * \param texto Puntero al texto sfText ingresado por el usuario.
 * \param cadena Cadena que contiene el texto a mostrar.
 * \param anchoBarraEscritura Ancho de la barra de escritura.
 */
void limitarVisualizacionTextoSobreBarraEscritura (sfText *texto, const char *cadena, float anchoBarraEscritura);

/** \brief Omitir eventos pendientes a procesar. Invocar cuando se necesite desactivar una interfaz y no procesar sus eventos pendientes.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void omitirEventosPendientes (sfRenderWindow *renderizado);


/* ============================================================================================================================================
   FUNCIONES DE ESCRITURA
   ============================================================================================================================================ */


/** \brief Ingresar un caracter almacenado en un evento a un buffer.
 *
 * Si es un caracter de control, retorna.
 * Colocar el caracter en la posicion que corresponda dentro del buffer.
 * Acepta el caracter "Backspace" para borrado de texto.
 * Verifica el uso de solo caracteres ASCII imprimibles (1 Byte).
 *
 * \param buffer Puntero al buffer donde se almacenara el caracter.
 * \param tamMaxBuffer Tamanio maximo del buffer. Es por como esta definido, ej: char buffer [5], el tamanio maximo es '5'.
 * \param eventoChar Variable de evento que contiene el caracter.
 *
 * \return ERROR_OPERACION en caso de que el caracter ingresado no sea valido (es un caracter de control), EXITO en caso contrario.
 *
 */
t_codigoRetorno ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar);

/** \brief Pegar texto desde el portapapeles a buffer.
 *
 * Verifica que el portapapeles no contenga caracteres invalidos (no ASCII imprimible (1 Byte)).
 * Verifica que el buffer tenga espacio suficiente para pegar el portapapeles.
 * Copia el texto del portapapeles al buffer y asegura terminar la cadena con '\0'.
 *
 * \param buffer Puntero al buffer donde se almacenara la copia del portapapeles.
 * \param tamMaxBuffer Tamanio maximo del buffer. Es por como esta definido, ej: char buffer [5], el tamanio maximo es '5'.
 *
 * \return ERROR_OPERACION en caso de que el portapapeles contenga caracteres invalidos o en caso de que el buffer no tenga espacio suficiente para pegar el portapapeles, EXITO en caso contrario.
 *
 */
t_codigoRetorno pegarTextoDesdePortapapelesABuffer (char *buffer, int tamMaxBuffer);

/** \brief Analizar si la cadena contiene todos espacios.
 *
 * \param mensaje Cadena a analizar.
 *
 * \return True en caso de que la cadena tenga todos espacios, False en caso contrario y en caso de cadena vacia.
 *
 */
bool sonTodosEspacios (const char *mensaje);


/* ============================================================================================================================================
   VALIDACIONES DE DATOS
   ============================================================================================================================================ */


/** \brief Analizar si el nombre es valido. Toma en cuenta las restricciones del dominio. Valida el caso de que sean todos espacios.
 *
 * \param nombre Nombre a analizar.
 *
 * \return True en caso de que sea valido, False en caso contrario.
 *
 */
bool esNombreValido (const char *nombre);

/** \brief Analizar si la contrasenia es valida. Toma en cuenta las restricciones del dominio. Valida el caso de que sean todos espacios.
 *
 * \param contrasenia Contrasenia a analizar.
 *
 * \return True en caso de que sea valido, False en caso contrario.
 *
 */
bool esContraseniaValida (const char *contrasenia);

/** \brief Analizar si el correo electronico es valido. Toma en cuenta las restricciones del dominio. Valida el caso de que sean todos espacios.
 *
 * \param correo Correo a analizar.
 *
 * \return True en caso de que sea valido, False en caso contrario.
 *
 */
bool esCorreoElectronicoValido (const char *correo);


/* ============================================================================================================================================
   FUNCIONES DE PUNTO DE INSERCION
   ============================================================================================================================================ */


/** \brief Inicializar o resetear el punto de insercion.
 *
 * Deshabilitar (desactivar) el parpadeo del punto de insercion y reiniciar su contador.
 *
 * \param puntoInsercion Puntero a la estructura que gestiona el punto de insercion.
 *
 */
void resetearPuntoInsercion (t_puntoInsercion *puntoInsercion);

/** \brief Preguntar si el punto de insercion esta habilitado o deshabilitado.
 *
 * \param puntoInsercion Puntero a la estructura que gestiona el punto de insercion.
 *
 * \return 1 si se encuentra habilitado, 0 si no lo esta.
 */
bool puntoInsercionHabilitado (const t_puntoInsercion *puntoInsercion);

/** \brief Actualizar el punto de insercion segun su estado.
 *
 * Avanzar el contador del punto de insercion. Si el punto de insercion alcanza la velocidad (constante) establecida, se reinicia el contador y se actualiza (activa/desactiva) segun su estado:
 * si el punto de insercion esta deshabilitado, se habilita.
 * si el punto de insercion esta habilitado, se deshabilita.
 *
 * \param puntoInsercion Puntero a la estructura que gestiona el punto de insercion.
 *
 */
void actualizarPuntoInsercion (t_puntoInsercion *puntoInsercion);


/* ============================================================================================================================================
   FUNCIONES DE BARRA DE CARGA
   ============================================================================================================================================ */


/** \brief Establecer el estado inicial del texto de carga y setear el contador.
 *
 * \param textoDeCarga Puntero a la estructura que gestiona el texto de carga.
 *
 */
void textoDeCarga_iniciar (t_textoDeCarga *textoDeCarga);

/** \brief Incrementar el contador. En caso de que alcance la velocidad de actualizacion de carga, modifica el estado. Si el texto ya se encuentra en el estado final, lo reestablece al estado inicial.
 *
 * \param textoDeCarga Puntero a la estructura que gestiona el texto de carga.
 *
 * \return True si se modifico el estado del texto de carga, False en caso contrario.
 * 
 */
bool textoDeCarga_actualizar (t_textoDeCarga *textoDeCarga);

/** \brief Concatenar al texto los puntos segun el estado de carga.
 *
 * \param textoDeCarga Puntero a la estructura que gestiona el texto de carga.
 *
 */
void textoDeCarga_modificarTextoSegunEstado (t_textoDeCarga *textoDeCarga, char *texto);


/* ============================================================================================================================================
   LOGS
   ============================================================================================================================================ */

   
/** \brief Realizar un log de error en caso de error de conexion.
 * 
 */
void log_error_conexion ();

/** \brief Realizar un log de warning en caso de recibir una respuesta que no pertenece a la interfaz sobre la que se encuentra situado el usuario.
 * 
 */
void log_warning_respuestaRecibidaDeOtraInterfaz ();


#endif // UTILES_H_INCLUDED
