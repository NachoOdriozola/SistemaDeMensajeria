#include "../../include/recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (s_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static int recursosComunesAutenticacionRegistro_inicializarTextos (s_recursosComunesAutenticacionRegistroTextos *textos);
static int recursosComunesAutenticacionRegistro_inicializarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_configurarTextos (s_recursosComunesAutenticacionRegistroTextos *textos, const s_fuentes *fuentes);
static void recursosComunesAutenticacionRegistro_configurarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (s_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_liberarTextos (s_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_liberarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesAutenticacionRegistro_inicializar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // TEXTOS

    recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (&(recursosComunesAutenticacionRegistro->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // TEXTOS

    if (recursosComunesAutenticacionRegistro_inicializarTextos (&(recursosComunesAutenticacionRegistro->textos)) == ERROR_INICIALIZACION)
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

    // TEXTOS

    recursosComunesAutenticacionRegistro_configurarTextos (&(recursosComunesAutenticacionRegistro->textos), fuentes);


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_configurarElementos (&(recursosComunesAutenticacionRegistro->elementos));


    // --------------- TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTO

    recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

void recursosComunesAutenticacionRegistro_renderizarTextos (sfRenderWindow *renderizado, const s_recursosComunesAutenticacionRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxGuardarAutenticacion, NULL);
    sfRenderWindow_drawText (renderizado, textos->guardarAutenticacion, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresoIncorrecto, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoBotonIngresar, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
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

    // TEXTOS

    recursosComunesAutenticacionRegistro_liberarTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_liberarElementos (&(recursosComunesAutenticacionRegistro->elementos));
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todos los textos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (s_recursosComunesAutenticacionRegistroTextos *textos)
{
    textos->auxEscribirContrasenia = NULL;
    textos->auxEscribirNombre = NULL;
    textos->auxGuardarAutenticacion = NULL;
    textos->guardarAutenticacion = NULL;
    textos->ingresarContrasenia = NULL;
    textos->ingresarNombre = NULL;
    textos->ingresoIncorrecto = NULL;
    textos->textoBotonIngresar = NULL;
    textos->tituloInterfaz = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (s_recursosComunesAutenticacionRegistroElementos *elementos)
{
    elementos->barraEscribirContrasenia = NULL;
    elementos->barraEscribirNombre = NULL;
    elementos->botonGuardarAutenticacion = NULL;
    elementos->botonIngresar = NULL;
    elementos->puntoInsercion = NULL;
    elementos->subrayadoTitulo = NULL;
}

/** \brief Inicializar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Crear todos los recursos graficos de texto. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesAutenticacionRegistro_inicializarTextos (s_recursosComunesAutenticacionRegistroTextos *textos)
{
    textos->auxEscribirContrasenia = sfText_create ();
    if (!textos->auxEscribirContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxEscribirNombre = sfText_create ();
    if (!textos->auxEscribirNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxEscribirNombre.\n");
        return ERROR_INICIALIZACION;
    }

    textos->auxGuardarAutenticacion = sfText_create ();
    if (!textos->auxGuardarAutenticacion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto auxGuardarAutenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    textos->guardarAutenticacion = sfText_create ();
    if (!textos->guardarAutenticacion)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto guardarAutenticacion.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarContrasenia = sfText_create ();
    if (!textos->ingresarContrasenia)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarContrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresarNombre = sfText_create ();
    if (!textos->ingresarNombre)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresarNombre.\n");
        return ERROR_INICIALIZACION;
    }

    textos->ingresoIncorrecto = sfText_create ();
    if (!textos->ingresoIncorrecto)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto ingresoIncorrecto.\n");
        return ERROR_INICIALIZACION;
    }

    textos->textoBotonIngresar = sfText_create ();
    if (!textos->textoBotonIngresar)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto textoBotonIngresar.\n");
        return ERROR_INICIALIZACION;
    }

    textos->tituloInterfaz = sfText_create ();
    if (!textos->tituloInterfaz)
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
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
static void recursosComunesAutenticacionRegistro_configurarTextos (s_recursosComunesAutenticacionRegistroTextos *textos, const s_fuentes *fuentes)
{
    // auxEscribirContrasenia
    sfText_setFont (textos->auxEscribirContrasenia, fuentes->fuente1);
    sfText_setColor (textos->auxEscribirContrasenia, sfColor_fromRGB (40, 54, 54));

    // auxEscribirNombre
    sfText_setFont (textos->auxEscribirNombre, fuentes->fuente1);
    sfText_setColor (textos->auxEscribirNombre, sfColor_fromRGB (40, 54, 54));

    // auxGuardarAutenticacion
    sfText_setFont (textos->auxGuardarAutenticacion, fuentes->fuente1);
    sfText_setString (textos->auxGuardarAutenticacion, "X");
    sfText_setColor (textos->auxGuardarAutenticacion, sfColor_fromRGB (209, 0, 31));

    // guardarAutenticacion
    sfText_setFont (textos->guardarAutenticacion, fuentes->fuente1);
    sfText_setString (textos->guardarAutenticacion, "¿Desea guardar sus datos e iniciar sesion\nautomaticamente cuando inicie la aplicacion?");
    sfText_setColor (textos->guardarAutenticacion, sfColor_fromRGB (40, 54, 54));

    // ingresarContrasenia
    sfText_setFont (textos->ingresarContrasenia, fuentes->fuente1);
    sfText_setString (textos->ingresarContrasenia, "Ingrese su contraseña:");
    sfText_setColor (textos->ingresarContrasenia, sfColor_fromRGB (40, 54, 54));

    // ingresarNombre
    sfText_setFont (textos->ingresarNombre, fuentes->fuente1);
    sfText_setString (textos->ingresarNombre, "Ingrese su nombre:");
    sfText_setColor (textos->ingresarNombre, sfColor_fromRGB (34, 48, 48));

    // ingresoIncorrecto
    sfText_setFont (textos->ingresoIncorrecto, fuentes->fuente1);
    sfText_setFillColor (textos->ingresoIncorrecto, sfColor_fromRGB (40, 54, 54));

    // textoBotonIngresar
    sfText_setFont (textos->textoBotonIngresar, fuentes->fuente1);
    sfText_setString (textos->textoBotonIngresar, "INGRESAR");
    sfText_setColor (textos->textoBotonIngresar, sfColor_fromRGB (40, 54, 54));

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->fuente1);
    sfText_setString (textos->tituloInterfaz, "INICIAR SESION");
    sfText_setColor (textos->tituloInterfaz, sfColor_fromRGB (34, 48, 48));
}

/** \brief Configurar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro.
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

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (s_recursosComunesAutenticacionRegistroTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setPosition (textos->auxEscribirContrasenia, (sfVector2f){64, 262});
    sfText_setCharacterSize (textos->auxEscribirContrasenia, 24);

    // auxEscribirNombre
    sfText_setPosition (textos->auxEscribirNombre, (sfVector2f){64, 167});
    sfText_setCharacterSize (textos->auxEscribirNombre, 24);

    // auxGuardarAutenticacion
    sfText_setPosition (textos->auxGuardarAutenticacion, (sfVector2f){415, 318});
    sfText_setCharacterSize (textos->auxGuardarAutenticacion, 30);

    // guardarAutenticacion
    sfText_setPosition (textos->guardarAutenticacion, (sfVector2f){55, 311});
    sfText_setCharacterSize (textos->guardarAutenticacion, 22);

    // ingresarContrasenia
    sfText_setPosition (textos->ingresarContrasenia, (sfVector2f){55, 215});
    sfText_setCharacterSize (textos->ingresarContrasenia, 28);

    // ingresarNombre
    sfText_setPosition (textos->ingresarNombre, (sfVector2f){55, 120});
    sfText_setCharacterSize (textos->ingresarNombre, 28);

    // ingresoIncorrecto
    sfText_setPosition (textos->ingresoIncorrecto, (sfVector2f){55, 384});
    sfText_setCharacterSize (textos->ingresoIncorrecto, 24);

    // textoBotonIngresar
    sfText_setPosition (textos->textoBotonIngresar, (sfVector2f){227, 412});
    sfText_setCharacterSize (textos->textoBotonIngresar, 28);

    // tituloInterfaz
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){190, 25});
    sfText_setCharacterSize (textos->tituloInterfaz, 36);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
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

/** \brief Liberar, de manera segura, todas los textos graficos comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_liberarTextos (s_recursosComunesAutenticacionRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxGuardarAutenticacion);
    DESTRUCTOR_SEGURO_TEXTO (textos->guardarAutenticacion);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresoIncorrecto);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoBotonIngresar);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
}

/** \brief Liberar, de manera segura, todas los elementos graficos comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_liberarElementos (s_recursosComunesAutenticacionRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirContrasenia);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonGuardarAutenticacion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonIngresar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->subrayadoTitulo);
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
            sfText_setString (recursosComunesAutenticacionRegistro->textos.auxGuardarAutenticacion, "V");
            sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxGuardarAutenticacion, sfColor_fromRGB (76, 175, 80));
        }
        else
        {
            recursosComunesAutenticacionRegistro->habilitaciones.guardarAutenticacion = DESHABILITAR_GUARDAR_AUTENTICACION;
            sfText_setString (recursosComunesAutenticacionRegistro->textos.auxGuardarAutenticacion, "X");
            sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxGuardarAutenticacion, sfColor_fromRGB (209, 0, 31));
        }
        return EVENTO_MANEJADO;
    }
    return EVENTO_NO_MANEJADO;
}



















