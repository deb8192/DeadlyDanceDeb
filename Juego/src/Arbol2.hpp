#include "hoja2.hpp"

#ifndef Arbol2_HPP
#define Arbol2_HPP

    class Arbol2
    {
        public:
            Arbol2();//define valores por defecto
            ~Arbol2(void);//destruye el arbol y sus hojas
            hoja2 * getCabeza();//nos devuelve la raiz que da acceso a todas las demas
            hoja2 * getEjecucionDirecta();//nos devuelve la hoja que tenga en ejecucion directa
            void setEjecucionDirecta(hoja2 * hoj);//nos sirve para poner una hoja como ejecucion directa para la proxima ejecucion
            hoja2 * crearHoja();//nos sirve para crear hojas vacias
            void crearRaiz();//crea la raiz que contendra todas las hojas hijas
            int siguiente(bool);//nos da el siguiente comportamiento segun la entrada y la hoja pueden haber hojas que sean negativas como la raiz, si hay algo en ejecucion directa se ejecuta sea lo que sea
            bool estadoActual();//si lo seguimos recorriendo true si terminamos false
        private:
            hoja2 * cabeza;//es la raiz que solo sirve como paso para las siguientes hojas directas
            hoja2 * ejecucionDirecta;//esta hoja la utilizaremos para cuando hayan tareas que se tienen que ejecutar directamente (cuando no las haya su valor sera nullptr)
            int profundidad; // tambien llamado altura nos dice cuantas hojas hay hasta el ultimo hijo desde la raiz
            int anchura;// dimension maxima del arbol en horizontal (sirve para representarlo de forma sencilla) 
            int estado;//esto sera true cuando se lo estan recorriendo, y false cuando no
    };

#endif

