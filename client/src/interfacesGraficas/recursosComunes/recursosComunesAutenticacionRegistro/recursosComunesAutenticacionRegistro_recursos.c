#include "recursosComunesAutenticacionRegistro_recursos.h"


void _recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    fuentes->cuerpo = NULL;
    fuentes->ui = NULL;
}

void _recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
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

void _recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    elementos->barraEscribirContrasenia = NULL;
    elementos->barraEscribirNombre = NULL;
    elementos->botonIngresar = NULL;
    elementos->puntoInsercion = NULL;
    elementos->subrayadoTitulo = NULL;
}


t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
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

t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
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

t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
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


void _recursosComunesAutenticacionRegistro_configurarInterfaz (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    // Deshabilitar foco
    recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;

    // Inicializar el punto de insecion
    resetearPuntoInsercion (&(recursosComunesAutenticacionRegistro->logica.puntoInsercion));

    // Setear cadenas vacias
    *(recursosComunesAutenticacionRegistro->logica.contrasenia) = '\0';
    *(recursosComunesAutenticacionRegistro->logica.nombreUsuario) = '\0';
}

void _recursosComunesAutenticacionRegistro_configurarTextos (t_recursosComunesAutenticacionRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    // auxEscribirContrasenia
    sfText_setFont (textos->auxEscribirContrasenia, fuentes->cuerpo);
    sfText_setColor (textos->auxEscribirContrasenia, sfColor_fromRGB (53, 53, 53));

    // auxEscribirNombre
    sfText_setFont (textos->auxEscribirNombre, fuentes->cuerpo);
    sfText_setColor (textos->auxEscribirNombre, sfColor_fromRGB (53, 53, 53));

    // ingresarContrasenia
    sfText_setFont (textos->ingresarContrasenia, fuentes->ui);
    sfText_setColor (textos->ingresarContrasenia, sfColor_fromRGB (43, 43, 43));
    sfUint32 bufferIngresarContrasenia [] = {'C', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ':', 0};
    sfText_setUnicodeString (textos->ingresarContrasenia, bufferIngresarContrasenia);

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
    sfText_setColor (textos->textoCambiarInterfaz, sfColor_fromRGB (43, 43, 43));
    sfUint32 bufferTextoCambiarInterfaz [] = {0x00bf, 'N', 'o', ' ', 't', 'e', 'n', 0x00e9, 's', ' ', 'c', 'u', 'e', 'n', 't', 'a', '?', ' ', 'R', 'e', 'g', 'i', 's', 't', 'r', 'a', 't', 'e', ' ', 'a', 'c', 0x00e1, 0};
    sfText_setUnicodeString (textos->textoCambiarInterfaz, bufferTextoCambiarInterfaz);

    // tituloInterfaz
    sfText_setFont (textos->tituloInterfaz, fuentes->ui);
    sfText_setColor (textos->tituloInterfaz, sfColor_fromRGB (43, 43, 43));
    sfUint32 bufferTituloInterfaz [] = {'I', 'N', 'I', 'C', 'I', 'A', 'R', ' ', 'S', 'E', 'S', 'I', 0x00d3, 'N', 0};
    sfText_setUnicodeString (textos->tituloInterfaz, bufferTituloInterfaz);
}

void _recursosComunesAutenticacionRegistro_configurarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
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


void _recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
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

void _recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
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


void _recursosComunesAutenticacionRegistro_liberarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes)
{
    DESTRUCTOR_SEGURO_FUENTE (fuentes->cuerpo);
    DESTRUCTOR_SEGURO_FUENTE (fuentes->ui);
}

void _recursosComunesAutenticacionRegistro_liberarTextos (t_recursosComunesAutenticacionRegistroTextos *textos)
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

void _recursosComunesAutenticacionRegistro_liberarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos)
{
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirContrasenia);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->barraEscribirNombre);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->botonIngresar);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->puntoInsercion);
    DESTRUCTOR_SEGURO_RECTANGULO (elementos->subrayadoTitulo);
}


