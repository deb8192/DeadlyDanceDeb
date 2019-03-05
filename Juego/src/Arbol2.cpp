#include "Arbol2.hpp"

Arbol2::Arbol2()
{
    cabeza = nullptr;
    ejecucionDirecta = nullptr;
    profundidad =0; 
    anchura = 0;
    estado = false;
}

Arbol2::~Arbol2(void)
{

}

hoja2 * Arbol2::getCabeza()
{
    return cabeza;
}

hoja2 * Arbol2::getEjecucionDirecta()
{
    return ejecucionDirecta;
}

void Arbol2::setEjecucionDirecta(hoja2 * hoj)
{
    ejecucionDirecta = hoj;
}

hoja2 * Arbol2::crearHoja()
{
    hoja2 * nuevaHojaVacia = new hoja2();
    return nuevaHojaVacia;
}

int Arbol2::siguiente(bool valor)
{
    if(ejecucionDirecta != nullptr)//esto significa que este arbol se esta ejecutando o entrado en una tarea repetitiva
    {
        if(valor)
        {
            hoja2 * hoja = ejecucionDirecta->siguiente(ejecucionDirecta);
            ejecucionDirecta = hoja;
            if(ejecucionDirecta == nullptr)
            {
                //esto significa que no hay mas tareas en esta rama por lo que reiniciamos 
                estado = false;
                return 0;//esto significa que no hay mas tareas en esta rama por lo que reiniciamos 
            }
            else
            {
                //esto significa que hay una siguiente tarea que comprobar
                estado = true;
                return ejecucionDirecta->conseguirComportamiento();
            }
        }
        else
        {
            //es false por lo que pasamos a la siguiente rama por arriba o hermana vamos al padre y le preguntamos si tiene otro hijo despues que este, si lo tiene se lo pedimos
            hoja2 * hoja =ejecucionDirecta->siguienteRama(ejecucionDirecta);
            ejecucionDirecta = hoja;
            if(ejecucionDirecta == nullptr)//no hay mas ramas no se cumple nada (se puede decir que se queda parado)
            {
                estado = false;
                return 0;
            }
            else
            {
                //si que hay rama a comprobar
                estado = true;
                return ejecucionDirecta->conseguirComportamiento();
            }
        } 
    }
    else
    {
        //estamos en la primera ejecucion 
        
        if(cabeza == nullptr) //si es nula la cabeza no se ha definido arbol
            return 0;

        ejecucionDirecta = cabeza->siguiente(ejecucionDirecta);//siguiente hijo(primero)
        if(ejecucionDirecta == nullptr)
        {
            estado = false;
            return 0;
        }
        else
        {
            estado = true;
            return ejecucionDirecta->conseguirComportamiento();
        }
    }

    estado = true;//sale arbol
    return 0;//no hace nada
}

 bool Arbol2::estadoActual()
 {
     if(estado)
     {
         return false;
     }
     else
     {
         return true;
     }
 }

 void Arbol2::setCabeza(hoja2 * hoj)
 {
     //para asignar la cabeza del arbol
     //no se recomienda cambiarla cuando ya esta definida
     cabeza = hoj;
 }