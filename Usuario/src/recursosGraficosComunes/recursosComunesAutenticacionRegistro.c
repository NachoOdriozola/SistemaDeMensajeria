#include "../../include/recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static int recursosComunesAutenticacionRegistro_inicializarTexto (s_recursosComunesAutenticacionRegistroTexto *texto);
static int recursosComunesAutenticacionRegistro_inicializarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_configurarTexto (s_recursosComunesAutenticacionRegistroTexto *texto, const s_fuentes *fuentes);
static void recursosComunesAutenticacionRegistro_configurarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_tamYPosVentanaTexto (s_recursosComunesAutenticacionRegistroTexto *texto);
static void recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesAutenticacionRegistro_inicializar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTO

    recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia = NULL;
    recursosComunesAutenticacionRegistro->texto.auxEscribirNombre = NULL;
    recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion = NULL;
    recursosComunesAutenticacionRegistro->texto.guardarAutenticacion = NULL;
    recursosComunesAutenticacionRegistro->texto.ingresarContrasenia = NULL;
    recursosComunesAutenticacionRegistro->texto.ingresarNombre = NULL;
    recursosComunesAutenticacionRegistro->texto.ingresoIncorrecto = NULL;
    recursosComunesAutenticacionRegistro->texto.textoBotonIngresar = NULL;
    recursosComunesAutenticacionRegistro->texto.tituloInterfaz = NULL;


    // ELEMENTOS

    recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia = NULL;
    recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre = NULL;
    recursosComunesAutenticacionRegistro->elementos.botonGuardarAutenticacion = NULL;
    recursosComunesAutenticacionRegistro->elementos.botonIngresar = NULL;
    recursosComunesAutenticacionRegistro->elementos.puntoInsercion = NULL;
    recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo = NULL;


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTO

    if (recursosComunesAutenticacionRegistro_inicializarTexto (&(recursosComunesAutenticacionRegistro->texto)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (recursosComunesAutenticacionRegistro_inicializarElementos (&(recursosComunesAutenticacionRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void recursosComunesAutenticacionRegistro_configurar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_fuentes *fuentes)
{
    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->habilitaciones.escribirContrasenia = DESHABILITAR_ESCRIBIR_CONTRASENIA;
    recursosComunesAutenticacionRegistro->habilitaciones.escribirNombre = DESHABILITAR_ESCRIBIR_NOMBRE;
    recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion = DESHABILITAR_GUARDAR_AUTENTICACION;
    recursosComunesAutenticacionRegistro->habilitaciones.ingresar = DESHABILITAR_INGRESAR;
    recursosComunesAutenticacionRegistro->habilitaciones.puntoInsercion = DESHABILITAR_PUNTO_INSERCION;
    recursosComunesAutenticacionRegistro->habilitaciones.contadorPuntoInsercion = REINICIAR_CONTADOR_PUNTO_INSERCION;


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTO

    recursosComunesAutenticacionRegistro_configurarTexto (&(recursosComunesAutenticacionRegistro->texto), fuentes);


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_configurarElementos (&(recursosComunesAutenticacionRegistro->elementos));


    // --------------- TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTO

    recursosComunesAutenticacionRegistro_tamYPosVentanaTexto (&(recursosComunesAutenticacionRegistro->texto));


    // ELEMENTO

    recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

void recursosComunesAutenticacionRegistro_renderizarTexto (sfRenderWindow *renderizado, const s_recursosComunesAutenticacionRegistroTexto *recursosComunesAutenticacionRegistroTexto)
{
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->auxEscribirNombre, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->auxGuardarAutenticacion, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->guardarAutenticacion, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->ingresarContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->ingresarNombre, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->ingresoIncorrecto, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->textoBotonIngresar, NULL);
    sfRenderWindow_drawText (renderizado, recursosComunesAutenticacionRegistroTexto->tituloInterfaz, NULL);
}

void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const s_recursosComunesAutenticacionRegistroElementos *recursosComunesAutenticacionRegistroElementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistroElementos->barraEscribirContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistroElementos->barraEscribirNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistroElementos->botonGuardarAutenticacion, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistroElementos->botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, recursosComunesAutenticacionRegistroElementos->subrayadoTitulo, NULL);
}

void recursosComunesAutenticacionRegistro_liberar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // TEXTO

    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.auxEscribirContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.auxEscribirNombre);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.guardarAutenticacion);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.ingresarContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.ingresarNombre);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.ingresoIncorrecto);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.textoBotonIngresar);
    DESTRUCTOR_SEGURO_TEXTO (recursosComunesAutenticacionRegistro->texto.tituloInterfaz);


    // ELEMENTOS

    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.botonGuardarAutenticacion);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.botonIngresar);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (recursosComunesAutenticacionRegistro->elementos.subrayadoTitulo);
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Inicializar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Crear todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param texto Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesAutenticacionRegistro_inicializarTexto (s_recursosComunesAutenticacionRegistroTexto *texto)
{
    texto->auxEscribirContrasenia = sfText_create ();
    if (!texto->auxEscribirContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    texto->auxEscribirNombre = sfText_create ();
    if (!texto->auxEscribirNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirNombre.\n");
        return ERROR_INICIALIZACION;
    }

    texto->auxGuardarAutenticacion = sfText_create ();
    if (!texto->auxGuardarAutenticacion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxGuardarAutenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    texto->guardarAutenticacion = sfText_create ();
    if (!texto->guardarAutenticacion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto guardarAutenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    texto->ingresarContrasenia = sfText_create ();
    if (!texto->ingresarContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    texto->ingresarNombre = sfText_create ();
    if (!texto->ingresarNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarNombre.\n");
        return ERROR_INICIALIZACION;
    }

    texto->ingresoIncorrecto = sfText_create ();
    if (!texto->ingresoIncorrecto)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresoIncorrecto.\n");
        return ERROR_INICIALIZACION;
    }

    texto->textoBotonIngresar = sfText_create ();
    if (!texto->textoBotonIngresar)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto textoBotonIngresar.\n");
        return ERROR_INICIALIZACION;
    }

    texto->tituloInterfaz = sfText_create ();
    if (!texto->tituloInterfaz)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto tituloInterfaz.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Crear todos los recursos graficos de elementos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesAutenticacionRegistro_inicializarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos)
{
    elementos->barraEscribirContrasenia = sfRectangleShape_create ();
    if (!elementos->barraEscribirContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento barraEscribirContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->barraEscribirNombre = sfRectangleShape_create ();
    if (!elementos->barraEscribirNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento barraEscribirNombre.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonGuardarAutenticacion = sfRectangleShape_create ();
    if (!elementos->botonGuardarAutenticacion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento botonGuardarAutenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->botonIngresar = sfRectangleShape_create ();
    if (!elementos->botonIngresar)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento botonIngresar.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->puntoInsercion = sfRectangleShape_create ();
    if (!elementos->puntoInsercion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento puntoInsercion.\n");
        return ERROR_INICIALIZACION;
    }

    elementos->subrayadoTitulo = sfRectangleShape_create ();
    if (!elementos->subrayadoTitulo)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear elemento subrayadoTitulo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Configurar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Configura todos los recursos graficos de texto.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void recursosComunesAutenticacionRegistro_configurarTexto (s_recursosComunesAutenticacionRegistroTexto *texto, const s_fuentes *fuentes)
{
    // auxEscribirContrasenia
    sfText_setFont (texto->auxEscribirContrasenia, fuentes->fuente1);
    sfText_setColor (texto->auxEscribirContrasenia, sfColor_fromRGB (40, 54, 54));

    // auxEscribirNombre
    sfText_setFont (texto->auxEscribirNombre, fuentes->fuente1);
    sfText_setColor (texto->auxEscribirNombre, sfColor_fromRGB (40, 54, 54));

    // auxGuardarAutenticacion
    sfText_setFont (texto->auxGuardarAutenticacion, fuentes->fuente1);
    sfText_setString (texto->auxGuardarAutenticacion, "X");
    sfText_setColor (texto->auxGuardarAutenticacion, sfColor_fromRGB (209, 0, 31));

    // guardarAutenticacion
    sfText_setFont (texto->guardarAutenticacion, fuentes->fuente1);
    sfText_setString (texto->guardarAutenticacion, "¿Desea guardar sus datos e iniciar sesion\nautomaticamente cuando inicie la aplicacion?");
    sfText_setColor (texto->guardarAutenticacion, sfColor_fromRGB (40, 54, 54));

    // ingresarContrasenia
    sfText_setFont (texto->ingresarContrasenia, fuentes->fuente1);
    sfText_setString (texto->ingresarContrasenia, "Ingrese su contraseña:");
    sfText_setColor (texto->ingresarContrasenia, sfColor_fromRGB (40, 54, 54));

    // ingresarNombre
    sfText_setFont (texto->ingresarNombre, fuentes->fuente1);
    sfText_setString (texto->ingresarNombre, "Ingrese su nombre:");
    sfText_setColor (texto->ingresarNombre, sfColor_fromRGB (34, 48, 48));

    // ingresoIncorrecto
    sfText_setFont (texto->ingresoIncorrecto, fuentes->fuente1);
    sfText_setFillColor (texto->ingresoIncorrecto, sfColor_fromRGB (40, 54, 54));

    // textoBotonIngresar
    sfText_setFont (texto->textoBotonIngresar, fuentes->fuente1);
    sfText_setString (texto->textoBotonIngresar, "INGRESAR");
    sfText_setColor (texto->textoBotonIngresar, sfColor_fromRGB (40, 54, 54));

    // tituloInterfaz
    sfText_setFont (texto->tituloInterfaz, fuentes->fuente1);
    sfText_setString (texto->tituloInterfaz, "INICIAR SESION");
    sfText_setColor (texto->tituloInterfaz, sfColor_fromRGB (34, 48, 48));
}

/** \brief Configurar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Configura todos los recursos graficos de elementos.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_configurarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setFillColor (elementos->barraEscribirContrasenia, sfColor_fromRGB (208, 208, 208));

    // barraEscribirNombre
    sfRectangleShape_setFillColor (elementos->barraEscribirNombre, sfColor_fromRGB (208, 208, 208));

    // botonIngresar
    sfRectangleShape_setFillColor (elementos->botonIngresar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setOutlineColor (elementos->botonIngresar, sfColor_fromRGB (40, 54, 54));

    // botonGuardarAutenticacion
    sfRectangleShape_setFillColor (elementos->botonGuardarAutenticacion, sfColor_fromRGB (208, 208, 208));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);

    // subrayadoTitulo
    sfRectangleShape_setFillColor (elementos->subrayadoTitulo, sfColor_fromRGB (34, 48, 48));
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_tamYPosVentanaTexto (s_recursosComunesAutenticacionRegistroTexto *texto)
{
    // auxEscribirContrasenia
    sfText_setPosition (texto->auxEscribirContrasenia, (sfVector2f){64, 262});
    sfText_setCharacterSize (texto->auxEscribirContrasenia, 24);

    // auxEscribirNombre
    sfText_setPosition (texto->auxEscribirNombre, (sfVector2f){64, 167});
    sfText_setCharacterSize (texto->auxEscribirNombre, 24);

    // auxGuardarAutenticacion
    sfText_setPosition (texto->auxGuardarAutenticacion, (sfVector2f){415, 318});
    sfText_setCharacterSize (texto->auxGuardarAutenticacion, 30);

    // guardarAutenticacion
    sfText_setPosition (texto->guardarAutenticacion, (sfVector2f){55, 311});
    sfText_setCharacterSize (texto->guardarAutenticacion, 22);

    // ingresarContrasenia
    sfText_setPosition (texto->ingresarContrasenia, (sfVector2f){55, 215});
    sfText_setCharacterSize (texto->ingresarContrasenia, 28);

    // ingresarNombre
    sfText_setPosition (texto->ingresarNombre, (sfVector2f){55, 120});
    sfText_setCharacterSize (texto->ingresarNombre, 28);

    // ingresoIncorrecto
    sfText_setPosition (texto->ingresoIncorrecto, (sfVector2f){55, 384});
    sfText_setCharacterSize (texto->ingresoIncorrecto, 24);

    // textoBotonIngresar
    sfText_setPosition (texto->textoBotonIngresar, (sfVector2f){227, 412});
    sfText_setCharacterSize (texto->textoBotonIngresar, 28);

    // tituloInterfaz
    sfText_setPosition (texto->tituloInterfaz, (sfVector2f){190, 25});
    sfText_setCharacterSize (texto->tituloInterfaz, 36);
}

/** \brief Establecer el tamanio y la posicion en pantalla de cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * Establecer a todos los textos graficos un tamanio y posicion sobre la ventana.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (s_recursosComunesAutenticacionRegistroElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setPosition (elementos->barraEscribirContrasenia, (sfVector2f){55, 263});
    sfRectangleShape_setSize (elementos->barraEscribirContrasenia, (sfVector2f){420, 30});

    // barraEscribirNombre
    sfRectangleShape_setPosition (elementos->barraEscribirNombre, (sfVector2f){55, 168});
    sfRectangleShape_setSize (elementos->barraEscribirNombre, (sfVector2f){420, 30});

    // botonGuardarAutenticacion
    sfRectangleShape_setPosition (elementos->botonGuardarAutenticacion, (sfVector2f){406, 322});
    sfRectangleShape_setSize (elementos->botonGuardarAutenticacion, (sfVector2f){30, 30});

    // botonIngresar
    sfRectangleShape_setPosition (elementos->botonIngresar, (sfVector2f){195, 413});
    sfRectangleShape_setSize (elementos->botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (elementos->botonIngresar, 2);

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){26, 2});

    // subrayadoTitulo
    sfRectangleShape_setPosition (elementos->subrayadoTitulo, (sfVector2f){175, 75});
    sfRectangleShape_setSize (elementos->subrayadoTitulo, (sfVector2f){172, 2.5});
}



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



bool manejarClickGuardarAutenticacion (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if (clickEnRectangulo (renderizado, recursosComunesAutenticacionRegistro->elementos.botonGuardarAutenticacion))
    {
        if (recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion == DESHABILITAR_GUARDAR_AUTENTICACION)
        {
            recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion = HABILITAR_GUARDAR_AUTENTICACION;
            sfText_setString (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, "V");
            sfText_setColor (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, sfColor_fromRGB (76, 175, 80));
        }
        else
        {
            recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion = DESHABILITAR_GUARDAR_AUTENTICACION;
            sfText_setString (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, "X");
            sfText_setColor (recursosComunesAutenticacionRegistro->texto.auxGuardarAutenticacion, sfColor_fromRGB (209, 0, 31));
        }
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}



















