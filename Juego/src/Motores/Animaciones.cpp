#include "Animaciones.hpp"

Animaciones::Animaciones()
{
    _ejecucion = nullptr;//cuando se llame a procesarAnimacion se llamara a la animacion que haya en _ejecucion
    _animaciones = nullptr;//contiene todos los estados de la entidad (moverse, coger objetos...)
    numEstados = 0;
    cambio = false;
    id = 0;
}

Animaciones::Animaciones(const char * ruta)
{
    pugi::xml_document doc;//instanciamos el objeto de la libreria xml
    pugi::xml_parse_result result =  doc.load_file(ruta);//cargamos el archivo
    
    if(result)
    {
        //existe el documento
        pugi::xml_node hijo = doc.child("Animaciones");
        
        if(hijo)
        {
            int comportamientos = hijo.attribute("numeroAnimaciones").as_int();//nos devuelve un int
            
            if(comportamientos > 0)
            {
                _animaciones = new Animacion * [comportamientos];
                numEstados = comportamientos;
                int i = 0;
                
                for(pugi::xml_node hij = hijo.child("Animacion"); hij; hij = hij.next_sibling("Animacion"))
                {
                    _animaciones[i] = new Animacion();
                    i++;
                }

                i = 0;
                
                for(pugi::xml_node hij = hijo.child("Animacion"); hij; hij = hij.next_sibling("Animacion"))
                {
                    if(i == 0)
                    {
                        _ejecucion = _animaciones[i]; 
                        //std::cout << "se asigna al estado " <<  hij.attribute("nombre").value() << std::endl;
                        cambio = true;
                    }

                    //std::cout << "cargando animacion " <<  hij.attribute("nombre").value() << std::endl;
                    _animaciones[i]->SetInicio(hij.attribute("inicio").as_int());
                    _animaciones[i]->SetFinal(hij.attribute("final").as_int());
                    _animaciones[i]->SetVelocidad(hij.attribute("velocidad").as_int());      
                    _animaciones[i]->SetTermina(hij.attribute("terminar").as_bool());
                    _animaciones[i]->SetSalta(hij.attribute("salto").as_bool());
                    _animaciones[i]->SetRepite(hij.attribute("bucle").as_bool());
                    
                    if(hij.attribute("dondesaltar") && hij.attribute("dondesaltar").as_int() != -1)
                    {
                        _animaciones[i]->AsignarSiguiente(_animaciones[hij.attribute("dondesaltar").as_int()]);
                    }
                                        
                    i++;
                }
            }
        }
    }
    else
    {
        //mensaje de error
        std::cout << "\e[1;31m ERROR: \e[0m" << "No se ha podido cargar la logica de animaciones de la ruta -> " << ruta << std::endl;
    }
    
}

void Animaciones::ProcesarAnimacion(unsigned int frame_actual)
{
    if(id != 0 && _ejecucion != nullptr)
    {
        if(_ejecucion->GetTermina())
        {                  // std::cout << " entro en procesar animacion " << _ejecucion->GetSiguiente()->GetFinal() << std::endl;
            //esta puesto que termina entonces debemos hacer que termine saltando al estado que ponga
            if(frame_actual+2 >= _ejecucion->GetFinal() && _ejecucion->GetSalta())
            {
                //saltamos al siguiente estado automaticamente
                if(_ejecucion->GetSiguiente() != nullptr)
                {
                    cambio = true;
                    _ejecucion = _ejecucion->GetSiguiente();
                }
            }
            return;
        }
    }
}

void Animaciones::CambiarEstado(unsigned int e, unsigned int start, unsigned int actual)
{
    if(_ejecucion != nullptr && _animaciones != nullptr && ExisteEstado(e))
    {
        if(_ejecucion != _animaciones[e])
        {
            if((!_ejecucion->GetTermina()) || actual >= _ejecucion->GetFinal())//la logica prevalece sobre el usuario
            {
                cambio = true;
                _ejecucion = _animaciones[e];
            }
        }
    }
}

void Animaciones::AsignarID(unsigned int ID)
{
    id = ID;
}

bool Animaciones::ExisteEstado(unsigned int e)
{
    if(e < numEstados)
    {
        return true;
    }

    return false;
}

bool Animaciones::SePuedeCambiarEstado(unsigned int frame_actual)
{
    if(_ejecucion != nullptr)
    {
        if(_ejecucion->GetTermina())
        {
            //comprobamos si ha terminado
            if(_ejecucion->GetFinal() <= frame_actual)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            //si termina es false significa que no hay que esperar a que se cambie por lo que se devuelve true
            return true;
        }
    }
    return false;
}

unsigned int * Animaciones::Update()
{
    if(cambio)
    {
        unsigned int * devolucion = new unsigned int [3];
        devolucion[0] = _ejecucion->GetInicio();
        devolucion[1] = _ejecucion->GetFinal();
        devolucion[2] = _ejecucion->GetVelocidad();
        cambio = false;
        return devolucion;
    }

    return nullptr;
}

int Animaciones::buscarNumeroEstado(Animacion * e)
{
    for(int i = 0;i < (int)numEstados;i++)
    {
        if(e == _animaciones[i])
        {
            return i;
        }
    }

    return -1;
}

unsigned int Animaciones::GetID()
{
    return id;
}

bool Animaciones::GetEstaEnBucle()
{
    if(_ejecucion != nullptr)
    {
        return _ejecucion->GetRepite();
    }
    return false;
}

bool Animaciones::SeCambiaEstado()
{
    return cambio;
}