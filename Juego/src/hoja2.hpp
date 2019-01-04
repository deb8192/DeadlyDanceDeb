
#include <iostream>//para mostrar errores
#include <vector>//para tener los diferentes objetos,enemigos, jugadores.


#ifndef hoja2_HPP
#define hoja2_HPP


    class hoja2
    {
        public:
            hoja2(hoja2 *, hoja2 *);//constructor con padre
            hoja2();//constructor sin padre ni hijos
            ~hoja2(void);//se destruye a si misma y a sus hojas hijas ( si las tuviera )
            void setPadre(hoja2 *);//solo tiene un padre
            void agregarHijo(hoja2 *);//puede tener varios
            hoja2 * getPadre();//consegimos el padre de la hoja que lo llame (en el caso de la raiz sera nullptr)
            void definirComportamientoHoja(int);//define el comportamiento (esto es fijo una vez puesto no se recomienda cambiarlo a no ser que sepas muy bien lo que haces si no puede hacer comportamientos raros)
            int conseguirComportamiento();//nos devuelve el numero de comportamiento que realiza
            void definirRepiticion(bool rep);//define si es repetitivo
            void definirNumeroRepeticiones(int numero);//numero de repeticiones si es repetitivo
            hoja2 * siguiente(hoja2 *);//si tiene hijos devuelve el primero, si no devuelve nullptr
            hoja2 * siguienteRama(hoja2 *);//si tiene hermanos o superiores a la derecha se pasa a ellos, si no devuelve nullptr
            bool getEsRepetitivo();
            int getNumeroRepeticiones();
            void setRepeticionActual(int);
            int getRepeticionActual();

        protected:
            int comportamiento;//numero de comportamiento 
            bool esRepetitivo;//indica si esta tarea se repite si es asi se tendria que definir cuantas veces
            int numeroRepeticiones;//indica el numero de veces que se repite la accion
            int repeticionActual;//cuando llega a cero se pone de nuevo al valor de numeroRepeticiones
            hoja2 * padre;//esto puede ser vacio
            std::vector<hoja2 *> hijos; //los hijos que puede tener
 
    };

#endif