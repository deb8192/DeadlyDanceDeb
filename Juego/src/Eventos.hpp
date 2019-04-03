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
        KEY_U,          // DESACTIVAR FISICAS JUGADOR

        // TO DO: poner para que se utilizan
        KEY_ESPACIO,    // ATAQUE NORMAL
        KEY_ACEPTAR,    // --------------- POR AHORA NO SE SABE
        KEY_B,          // TRASLADAR JUGADOR AL BOSS
        KEY_C,          // MULTICAMARA
        KEY_E,          // COGER/SOLTAR OBJETOS
        KEY_I,          // TRASLADAR JUGADOR DONDE COFRE ARANA
        KEY_J,          // BAJAR VIDA
        KEY_H,          // SUBIR VIDA
        KEY_Z,          // --------------- POR AHORA NADA
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
        GUI_ID_CONFIGURACION_BUTTON,
        
        GUI_ID_ATRAS_BUTTON,
        GUI_ID_REINICIAR_HANOI,
        GUI_ID_MENU_BUTTON,
        GUI_ID_REINICIAR_BUTTON,
        GUI_ID_CONTINUAR,

        // IDs para cosas de Puzzles en MotorGrafico
        GUI_ID_ATRAS_PUZ,
        GUI_ID_OP1,
        GUI_ID_OP2,
        GUI_ID_OP3,
        GUI_ID_OP4,
        GUI_ID_PUZZLE, 

        UltimoEvento = GUI_ID_PUZZLE
    };
}

