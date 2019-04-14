#ifndef ConstantesComunes_HPP
#define ConstantesComunes_HPP

//esto contiene todas las constantes y variables de texto para comparativas en el programa (es comodo si se quiere utilizar en el algun sitio)
//using Constantes = struct
typedef struct
{
    /** Angulos en grados y radianes y relacion para sus cambios de escala **/
    const float PI = 3.14159265358979323846;
    const float PI_RADIAN = 180.0f;
    const float PI_MEDIOS = 90.0f;
    const float PI_CUARTOS = 45.0f;
    const float PI_OCTAVOS = 22.5f;
    const short CERO = 0;
    const short UNO = 1;
    const short DOS = 2;
    const short TRES = 3;
    const short CUATRO = 4;
    const short CINCO = 5;
    const short SEIS = 6;
    const short SIETE = 7;
    const short OCHO = 8;
    const short NUEVE = 9;
    const short DIEZ = 10;
    const short DIECIOCHO = 18;
    const short CIEN = 100;
    const float DEG_TO_RAD = 0.0174532925199432957f;
    const float RAD_TO_DEG = 57.295779513082320876f;

    /******************** Porcentajes *******************/
    const float UN_CUARTO = 0.25f;
    const float UN_MEDIO = 0.5f;
    const float TRES_CUARTOS = 0.75f;
    const float UN_TERCIO = 0.33f;
    const float DOS_TERCIOS = 0.66f;

    /*************** Strings arbol de comportamiento **************/
    //Comparadores del cargado de arboles
    const char* SELECTOR = "selector";
    const char* SEL_ALEATORIO = "selector-aleatorio";
    const char* SECUENCIA = "secuencia";
    const char* SEC_ALEATORIA = "secuencia-aleatoria";
    const char* TAREA = "tarea";
    const char* ITERATOR = "iterador";
    const char* RAIZ = "Root";
    const char* COMPOSICION = "Composition";
    const char* DECORADOR = "Decorator";
    const char* HOJA = "Leaf";
    const char* PIZARRA = "Blackboard";
    const char* LEE = "lee";
    const char* ESCRIBE = "escribe";
    const char* VERDADERO = "true";
    const char* FALSO = "false";
    const char* RANDOM = "random";

    //Comparadores de la lectura de las acciones de las tareas
    const char* PERSIGUE = "persigue";
    const char* ATACAR = "ataca";
    const char* VER = "ve";
    const char* PIDE_AYUDA = "pide-ayuda";
    const char* MERODEA = "merodea";
    const char* OIR = "oye";
    const char* BUSCAR = "busca";
    const char* CURARSE = "curarse";
    const char* AUXILIAR = "acude";
    const char* DEFENDERSE = "defensa";
    const char* COMPROBAR = "comprueba";
    const char* ATRAVESAR = "atraviesa";
    const char* NO_VE = "no-ve";
    const char* NO_OYE = "no-oye";
    const char* CAMBIA = "cambia";
    const char* ESTA = "esta";
    const char* DEBE = "debe";


    //Comparadores de la lectura de los objetivos de las tareas
    const char* JUGADOR = "jugador";
    const char* ZONA_COFRES = "zona-cofres";
    const char* AYUDA = "ayuda";
    const char* NORMAL = "modo-normal";
    const char* PELIGRO = "modo-peligro";
    const char* ATAQUE = "modo-ataque";
    const char* OCULTACION = "modo-ocultacion";
    const char* ULTIMA_PUERTA = "ultima-puerta";
    const char* PUERTA = "puerta";
    const char* MECANISMO = "mecanismo";
    const char* COFRE = "cofre";
    const char* ESCONDITE = "escondite";
    const char* ACCIONADO = "accionado";
    const char* NO_ACCIONADO = "no-accionado";

    /**************************** String & char cargado mapas ************************/
    // String de los tipos de zonas
    const char* ZCHEST = "zChest";
    const char* ZDARK = "zDark";
    const char* ZHIDE = "zHide";

    // Chars que indican los tipos de waypoints

    const char WAYP_A = 'a';   //Waypoint central
    const char WAYP_B = 'b';   //Waypoint de acceso horizontal
    const char WAYP_C = 'c';   //Waypoint de acceso vertical

    const unsigned short HEAVY = 1;
    const unsigned short BAILAORA = 2;

    // Tipos de objetos interactuables y recolectables
    const unsigned short PALANCA = 0;
    const unsigned short LLAVE = 1;
    const unsigned short PUERTA2 = 2;
    const unsigned short PUERTA_OBJ = 3;
    const unsigned short COFRE_OBJ = 4;
    const unsigned short ARMA = 5;
    const unsigned short POWERUP = 6;

    // Meter las armas seguidas:
    const unsigned short ARPA = 7;
    const unsigned short GUITARRA = 8;
    const unsigned short FLAUTA = 9;

    const unsigned short ORO = 10;
    const unsigned short VIDA = 11;
    const unsigned short ENERGIA = 12;

    const unsigned short PARED_ROMPIBLE = 14;

    // Sin utilizar por ahora
    /*

    const unsigned short PARED_INVISIBLE = 12;
    const unsigned short PARED_OBSTACULO = 13;
    const unsigned short SUELO = 15;
    const unsigned short BASE = 16;
    const unsigned short DECO = 17;*/

    // Tipos de enemigos
    const unsigned short POLLO = 0;
    const unsigned short MURCI = 1;
    const unsigned short ARANA = 2;
    const unsigned short GUARDIAN_A = 3;
    const unsigned short GUARDIAN_B = 4;
    const unsigned short BOSS = 5;

    // Codigo de la puerta del boss
    const unsigned short PUERTA_BOSS = 20;

} Constantes;
#endif
