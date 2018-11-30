#include "Nivel.hpp"
#include "MotorGrafico.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton


Nivel::Nivel()
{
    primeraSala = nullptr; 
}

bool Nivel::CargarNivel(int level)
{
    if(primeraSala != nullptr)
    {
        primeraSala->~Sala();
        primeraSala = nullptr;
    }
    cargador.CargarNivelXml(level);
    return false;
}

void Nivel::CrearEnemigo(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades, Sala * sala)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    Enemigo ene;
    ene.setPosiciones(x,y,z);
    ene.definirSala(sala);
    enemigos.push_back(ene);
    motor->CargarEnemigos(x,y,z,ruta_objeto,ruta_textura);
    ene.generarSonido(40,20.0);
}

void Nivel::CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarJugador(x,y,z,ruta_objeto,ruta_textura);
}

void Nivel::CrearObjeto(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarObjetos(x,y,z,ruta_objeto,ruta_textura);
}

Sala * Nivel::CrearPlataforma(int x,int y,int z, int ancho, int largo, int centro, const char *ruta_objeto, const char *ruta_textura)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    Sala * sala = new Sala(ancho,largo,x,y,z,centro);
    //int * datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int id = motor->CargarPlataformas(x,y,z,ruta_objeto,ruta_textura);
    sala->definirID(id);

    if(primeraSala == nullptr)
    {
        primeraSala = sala;
    }

    return sala;
}

void Nivel::CrearLuz(int x,int y,int z)
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarLuces(x,y,z);
}

void Nivel::update()
{
    //actualizamos los enemigos
    if(enemigos.size() > 0)
    {
        for(std::size_t i=0;i<enemigos.size();i++)
        {
            cout << "Enemigo " << i << endl;
            enemigos[i].queEscuchas();//esto iria mas en ia o algun proceso relacionado no debe estar aqui, lo pongo de PRUEBA
        }
    }

}

void Nivel::updateIA()
{

}