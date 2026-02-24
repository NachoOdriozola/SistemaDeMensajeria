#include "../../include/recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DECLARACIONES DE FUNCIONES COMPLEMENTARIAS
   ============================ */



static void recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

static int recursosComunesAutenticacionRegistro_inicializarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static int recursosComunesAutenticacionRegistro_inicializarTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
static int recursosComunesAutenticacionRegistro_inicializarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_configurarTextos (t_recursosComunesAutenticacionRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static void recursosComunesAutenticacionRegistro_configurarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

static void recursosComunesAutenticacionRegistro_liberarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
static void recursosComunesAutenticacionRegistro_liberarTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
static void recursosComunesAutenticacionRegistro_liberarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



int recursosComunesAutenticacionRegistro_inicializar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- INICIALIZAR VALORES NULOS ---------------

    // FUENTES

    recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (&(recursosComunesAutenticacionRegistro->fuentes));


    // TEXTOS

    recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (&(recursosComunesAutenticacionRegistro->elementos));


    // --------------- INICIALIZAR RECUROS GRAFICOS ---------------

    // FUENTES

    if (recursosComunesAutenticacionRegistro_inicializarFuentes (&(recursosComunesAutenticacionRegistro->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // TEXTOS

    if (recursosComunesAutenticacionRegistro_inicializarTextos (&(recursosComunesAutenticacionRegistro->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    // ELEMENTOS

    if (recursosComunesAutenticacionRegistro_inicializarElementos (&(recursosComunesAutenticacionRegistro->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return EXITO;
}

void recursosComunesAutenticacionRegistro_configurar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- CONFIGURAR FOCO ---------------

    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;


    // --------------- CONFIGURAR HABILITACIONES ---------------

    recursosComunesAutenticacionRegistro->ingreso = DESHABILITADO;


    // --------------- CONFIGURAR PUNTO DE INSERCION ---------------

    resetearPuntoInsercion (&(recursosComunesAutenticacionRegistro->puntoInsercion));


    // --------------- CONFIGURAR BUFFERS ---------------

    *(recursosComunesAutenticacionRegistro->bufferContrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->bufferNombre) = '\0';


    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesAutenticacionRegistro_configurarTextos (&(recursosComunesAutenticacionRegistro->textos), &(recursosComunesAutenticacionRegistro->fuentes));


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_configurarElementos (&(recursosComunesAutenticacionRegistro->elementos));


    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------

    // TEXTOS

    recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTO

    recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (&(recursosComunesAutenticacionRegistro->elementos));
}

void recursosComunesAutenticacionRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarNombre, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresoIncorrecto, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoBotonIngresar, NULL);
    sfRenderWindow_drawText (renderizado, textos->textoCambiarInterfaz, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloInterfaz, NULL);
}

void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->subrayadoTitulo, NULL);
}

void recursosComunesAutenticacionRegistro_liberar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // --------------- LIBERAR RECURSOS GRAFICOS ---------------

    // FUENTES

    recursosComunesAutenticacionRegistro_liberarFuentes (&(recursosComunesAutenticacionRegistro->fuentes));


    // TEXTOS

    recursosComunesAutenticacionRegistro_liberarTextos (&(recursosComunesAutenticacionRegistro->textos));


    // ELEMENTOS

    recursosComunesAutenticacionRegistro_liberarElementos (&(recursosComunesAutenticacionRegistro->elementos));
}



/* ============================
   FUNCIONES COMPLEMENTARIAS
   ============================ */



/** \brief Establecer en NULL a todas las fuentes graficas comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

/** \brief Establecer en NULL a todos los textos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
{
    textos->auxEscribirContrasenia = NULL;
    textos->auxEscribirNombre = NULL;
    textos->ingresarContrasenia = NULL;
    textos->ingresarNombre = NULL;
    textos->ingresoIncorrecto = NULL;
    textos->textoBotonIngresar = NULL;
    textos->textoCambiarInterfaz = NULL;
    textos->tituloInterfaz = NULL;
}

/** \brief Establecer en NULL a todos los elementos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 */
static void recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    elementos->barraEscribirContrasenia = NULL;
    elementos->barraEscribirNombre = NULL;
    elementos->botonIngresar = NULL;
    elementos->puntoInsercion = NULL;
    elementos->subrayadoTitulo = NULL;
}

/** \brief Inicializar los recursos graficos de fuentes comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Crear todos los recursos graficos de fuentes. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesAutenticacionRegistro_inicializarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    fuentes->ui = sfFont_createFromFile ("fuenteUi.ttf");
    if (!fuentes->ui)
    {
        perror ("\nERROR - Crear fuente UI.\n");
        return ERROR_INICIALIZACION;
    }

    fuentes->cuerpo = sfFont_createFromFile ("fuenteMensajes.ttf");
    if (!fuentes->cuerpo)
    {
        perror ("\nERROR - Crear fuente cuerpo.\n");
        return ERROR_INICIALIZACION;
    }


    return EXITO;
}

/** \brief Inicializar los recursos graficos de textos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Crear todos los recursos graficos de textos. Si ocurre un error en la creacion, se muestra un mensaje de error correspondiente.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
static int recursosComunesAutenticacionRegistro_inicializarTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
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

    textos->textoCambiarInterfaz = sfText_create ();
    if (!textos->textoCambiarInterfaz)
    {
        perror ("\nERROR - Recursos comunes autenticacion-registro, crear texto textoCambiarInterfaz.\n");
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
static int recursosComunesAutenticacionRegistro_inicializarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
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
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_configurarTextos (t_recursosComunesAutenticacionRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // auxEscribirContrasenia
    sfText_setFont (textos->auxEscribirContrasenia, fuentes->cuerpo);
    sfText_setColor (textos->auxEscribirContrasenia, sfColor_fromRGB (94, 91, 87));

    // auxEscribirNombre
    sfText_setFont (textos->auxEscribirNombre, fuentes->cuerpo);
    sfText_setColor (textos->auxEscribirNombre, sfColor_fromRGB (94, 91, 87));

    // ingresarContrasenia
    sfText_setFont (textos->ingresarContrasenia, fuentes->ui);
    sfText_setString (textos->ingresarContrasenia, "Contraseña:");
    sfText_setColor (textos->ingresarContrasenia, sfColor_fromRGB (43, 43, 43));

    // ingresarNombre
    sfText_setFont (textos->ingresarNombre, fuentes->ui);
    sfText_setString (textos->ingresarNombre, "Nombre de usuario:");
    sfText_setColor (textos->ingresarNombre, sfColor_fromRGB (43, 43, 43));

    // ingresoIncorrecto
    sfText_setFont (textos->ingresoIncorrecto, fuentes->ui);
    sfText_setFillColor (textos->ingresoIncorrecto, sfColor_fromRGB (43, 43, 43));

    // textoBotonIngresar
    sfText_setFont (textos->textoBotonIngresar, fuentes->ui);
    sfText_setString (textos->textoBotonIngresar, "INGRESAR");
    sfText_setColor (textos->textoBotonIngresar, sfColor_fromRGB (94, 91, 87));

    // textoCambiarInterfaz
    sfText_setFont (textos->textoCambiarInterfaz, fuentes->ui);
    sfText_setString (textos->textoCambiarInterfaz, "¿No tenés cuenta? Registrate acá");
    sfText_setColor (textos->textoCambiarInterfaz, sfColor_fromRGB (43, 43, 43));

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->ui);
    sfText_setString (textos->tituloInterfaz, "INICIAR SESIÓN");
    sfText_setColor (textos->tituloInterfaz, sfColor_fromRGB (43, 43, 43));
}

/** \brief Configurar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_configurarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setFillColor (elementos->barraEscribirContrasenia, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirContrasenia, sfColor_fromRGB (169, 163, 154));

    // barraEscribirNombre
    sfRectangleShape_setFillColor (elementos->barraEscribirNombre, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->barraEscribirNombre, sfColor_fromRGB (169, 163, 154));

    // botonIngresar
    sfRectangleShape_setFillColor (elementos->botonIngresar, sfColor_fromRGB (222, 216, 204));
    sfRectangleShape_setOutlineColor (elementos->botonIngresar, sfColor_fromRGB (169, 163, 154));

    // puntoInsercion
    sfRectangleShape_setFillColor (elementos->puntoInsercion, sfColor_fromRGB (94, 91, 87));
    sfRectangleShape_rotate (elementos->puntoInsercion, -90);

    // subrayadoTitulo
    sfRectangleShape_setFillColor (elementos->subrayadoTitulo, sfColor_fromRGB (43, 43, 43));
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
{
    // auxEscribirContrasenia
    sfText_setPosition (textos->auxEscribirContrasenia, (sfVector2f){42, 315});
    sfText_setCharacterSize (textos->auxEscribirContrasenia, 22);

    // auxEscribirNombre
    sfText_setPosition (textos->auxEscribirNombre, (sfVector2f){42, 180});
    sfText_setCharacterSize (textos->auxEscribirNombre, 22);

    // ingresarContrasenia
    sfText_setPosition (textos->ingresarContrasenia, (sfVector2f){35, 255});
    sfText_setCharacterSize (textos->ingresarContrasenia, 28);

    // ingresarNombre
    sfText_setPosition (textos->ingresarNombre, (sfVector2f){35, 120});
    sfText_setCharacterSize (textos->ingresarNombre, 28);

    // ingresoIncorrecto
    sfText_setCharacterSize (textos->ingresoIncorrecto, 24);

    // textoBotonIngresar
    sfText_setCharacterSize (textos->textoBotonIngresar, 24);
    centrarTextoEnArea (textos->textoBotonIngresar, 180, 405, 140, 35);

    // textoCambiarInterfaz
    sfText_setCharacterSize (textos->textoCambiarInterfaz, 26);
    centrarTextoEnArea (textos->textoCambiarInterfaz, 0, 530, 500, 90);

    // tituloInterfaz
    sfText_setPosition (textos->tituloInterfaz, (sfVector2f){120, 25});
    sfText_setCharacterSize (textos->tituloInterfaz, 36);
}

/** \brief Establecer un tamanio y una posicion sobre la ventana a cada texto grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    // barraEscribirContrasenia
    sfRectangleShape_setPosition (elementos->barraEscribirContrasenia, (sfVector2f){35, 315});
    sfRectangleShape_setSize (elementos->barraEscribirContrasenia, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirContrasenia, 2);

    // barraEscribirNombre
    sfRectangleShape_setPosition (elementos->barraEscribirNombre, (sfVector2f){35, 180});
    sfRectangleShape_setSize (elementos->barraEscribirNombre, (sfVector2f){430, 30});
    sfRectangleShape_setOutlineThickness (elementos->barraEscribirNombre, 2);

    // botonIngresar
    sfRectangleShape_setPosition (elementos->botonIngresar, (sfVector2f){180, 405});
    sfRectangleShape_setSize (elementos->botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (elementos->botonIngresar, 2);

    // puntoInsercion
    sfRectangleShape_setSize (elementos->puntoInsercion, (sfVector2f){26, 2});

    // subrayadoTitulo
    sfRectangleShape_setPosition (elementos->subrayadoTitulo, (sfVector2f){120, 75});
    sfRectangleShape_setSize (elementos->subrayadoTitulo, (sfVector2f){260, 2.5});
}

/** \brief Liberar, de manera segura, todas las fuentes graficas comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_liberarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

/** \brief Liberar, de manera segura, todas los textos graficos comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_liberarTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
{
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->auxEscribirNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarContrasenia);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresarNombre);
    DESTRUCTOR_SEGURO_TEXTO (textos->ingresoIncorrecto);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoBotonIngresar);
    DESTRUCTOR_SEGURO_TEXTO (textos->textoCambiarInterfaz);
    DESTRUCTOR_SEGURO_TEXTO (textos->tituloInterfaz);
}

/** \brief Liberar, de manera segura, todas los elementos graficos comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
static void recursosComunesAutenticacionRegistro_liberarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirContrasenia);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonIngresar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->subrayadoTitulo);
}




































