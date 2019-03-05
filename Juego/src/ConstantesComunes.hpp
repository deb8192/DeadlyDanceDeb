#ifndef ConstantesComunes_HPP
#define ConstantesComunes_HPP

//esto contiene todas las constantes y variables de texto para comparativas en el programa (es comodo si se quiere utilizar en el algun sitio)
using Constantes = struct
{
    /** Angulos en grados y radianes y relacion para sus cambios de escala **/
    const float PI = 3.14159265358979323846;
    const float PI_RADIAN = 180.0f;
    const float PI_MEDIOS = 90.0f;
    const float PI_CUARTOS = 45.0f;
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
    const short CIEN = 100;
    const float DEG_TO_RAD = 0.0174532925199432957f;
    const float RAD_TO_DEG = 57.295779513082320876f;

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

    //Comparadores de la lectura de los objetivos de las tareas
    const char* JUGADOR = "jugador";
    const char* ZONA_COFRES = "zona-cofres";

    /**************************** String cargado mapas ************************/
    const char* ZCHEST = "zChest";
    const char* ZDARK = "zDark";
};
#endif
