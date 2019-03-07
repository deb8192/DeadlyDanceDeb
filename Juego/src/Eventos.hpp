//esto contiene todos los nombres y ids de los eventos (es comodo si se quiere utilizar en el algun sitio)
namespace idsEventos 
{
    enum Enum 
    {
        // Teclas y raton
        KEY_A = 1,  // IZQ
        KEY_S,      // ATRAS
        KEY_D,      // DER
        KEY_W,      // DELANTE
        KEY_ESC,    // PAUSA o SALIR
        KEY_P,          // PAUSA
        KEY_K,          // MATAR PERSONAJE
        KEY_G_DEBUG,    // DEBUG
        KEY_1,
        KEY_2,

        // TO DO: poner para que se utilizan
        KEY_ESPACIO,    // ATAQUE NORMAL
        KEY_ACEPTAR,    // --------------- POR AHORA NO SE SABE
        KEY_B,          // TRASLADAR JUGADOR AL BOSS
        KEY_C,          // ACTIVAR/DESACTIVAR PATHFINDING
        KEY_E,          // COGER/SOLTAR OBJETOS
        KEY_I,          // --------------- POR AHORA NADA
        KEY_J,          // BAJAR VIDA
        KEY_Q,          // ATAQUE ESPECIAL
        RMOUSE_DOWN,    // ATAQUE ESPECIAL
        LMOUSE_DOWN,    // ATAQUE NORMAL
        RMOUSE_UP,      //
        LMOUSE_UP,      //
        MOUSE_MOVED,    //
        RMOUSE_PRESSED_DOWN,    //
        LMOUSE_PRESSED_DOWN,    //
        

        // Botones
        GUI_ID_EMPEZAR_BUTTON = 101,
        GUI_ID_SALIR_BUTTON,
        GUI_ID_CREDITOS_BUTTON,
        GUI_ID_SUBIR_SONIDO,
        GUI_ID_PUZZLES_BUTTON,//105
        GUI_ID_OP1,
        GUI_ID_OP2,
        GUI_ID_OP3,
        GUI_ID_OP4,
        GUI_ID_ATRAS_BUTTON,//110
        GUI_ID_REINICIAR_HANOI,
        GUI_ID_MENU_BUTTON,
        GUI_ID_REINICIAR_BUTTON,
        GUI_ID_CONTINUAR,
        GUI_ID_ARBOLES_BUTTON,

        //fin de los nuevos eventos
        GUI_ID_CONFIGURACION_BUTTON,
        UltimoEvento = GUI_ID_CONFIGURACION_BUTTON
    };
}

