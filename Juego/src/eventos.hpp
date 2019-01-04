//esto contiene todos los nombres y ids de los eventos (es comodo si se quiere utilizar en el algun sitio)
namespace idsEventos 
{
    enum Enum 
    {
        // Teclas y raton
        KEY_A = 1,
        KEY_S,
        KEY_D,
        KEY_W,
        KEY_ESPACIO,
        KEY_ACEPTAR,
        KEY_G_DEBUG,
        KEY_P,
        KEY_Q,
        KEY_E,
        RMOUSE_DOWN,
        LMOUSE_DOWN,
        RMOUSE_UP,
        LMOUSE_UP,
        MOUSE_MOVED,
        KEY_J,
        RMOUSE_PRESSED_DOWN,
        LMOUSE_PRESSED_DOWN,

        // Botones
        GUI_ID_EMPEZAR_BUTTON = 101,
        GUI_ID_SALIR_BUTTON,
        GUI_ID_CREDITOS_BUTTON,
        GUI_ID_SUBIR_SONIDO,
        //meter aqui los nuevos eventos
        
        GUI_ID_PUZZLES_BUTTON,//105
        GUI_ID_OP1,
        GUI_ID_OP2,
        GUI_ID_OP3,
        GUI_ID_OP4,
        GUI_ID_ARBOLES_BUTTON,//110
        GUI_ID_BACK_MENU_BUTTON,
        GUI_ID_REINICIAR_HANOI,
        GUI_ID_MENU_BUTTON,
        GUI_ID_REINICIAR_BUTTON,
        //fin de los nuevos eventos
        GUI_ID_CONFIGURACION_BUTTON,
        UltimoEvento = GUI_ID_CONFIGURACION_BUTTON
    };
}

