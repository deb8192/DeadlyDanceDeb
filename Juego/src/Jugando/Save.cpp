#include "Save.hpp"

Save::Save()
{
    save.tipo = 0;// rockero por defecto
    save.dinero = 100;// nada de dinero por defecto
    save.nivel = 7;// primer nivel por defecto
    strcpy(save.nombre," Vacio ");//esta vacia la partida por defecto
    strcpy(save.fechaActual,"00-00-0000");//sin fecha
}

bool Save::RecuperarPartida(const char * ruta)
{
    std::ifstream buffer;//solo escritura
    buffer.open(ruta,std::ios::binary);
    
    if(buffer.is_open())
    {
        buffer.read(reinterpret_cast<char *>(&save),sizeof(Partida));
        //unsigned int valor = reinterpret_cast<unsigned int>(recogida);
        buffer.close();
        return true;
    }


    return false;
}

void Save::GuardarPartida(const char * ruta)
{
    std::ofstream buffer;//solo escritura
    buffer.open(ruta,std::ios::binary);

    if(buffer.is_open())
    {
        buffer.write(reinterpret_cast<char *>(&save),sizeof(Partida));
        //buffer.write(reinterpret_cast<const char *>(&save),sizeof(save));
    }
    else
    {
        std::cout << "No se ha podido crear o abrir el archivo -> " << ruta << std::endl;
    }
    

    buffer.close();
}

unsigned int Save::GetTipo()
{
    return save.tipo;
}

void Save::SetTipo(unsigned int nuevoTipo)
{
    save.tipo = nuevoTipo;
}

unsigned int Save::GetDinero()
{
    return save.dinero;
}

void Save::SetDinero(unsigned int nuevoDinero)
{
    save.dinero = nuevoDinero;
}

unsigned int Save::GetNivel()
{
    return save.nivel;
}

void Save::SetNivel(unsigned int nuevoNivel)
{
    save.nivel = nuevoNivel;
}

const char * Save::GetNombre()
{
    return save.nombre;
}

void Save::SetNombre(const char * nuevoNombre)
{
    strcpy(save.nombre,nuevoNombre);
}

const char * Save::GetFecha()
{
    return save.fechaActual;
}