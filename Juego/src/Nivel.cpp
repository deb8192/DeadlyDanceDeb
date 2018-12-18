#include "Nivel.hpp"
#include "MotorGrafico.hpp"
#include "reactphysics3d.h"
#include "MotorFisicas.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton


Nivel::Nivel()
{
    primeraSala = nullptr;
    id = 0;
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
    MotorGrafico * motor = MotorGrafico::getInstance();//cogemos instancia del motor para crear la figura 3d
    pollo * ene = new pollo();//aqui va el tipo de enemigo que es hacer ifffffffffsssss y meter una variable nueva de tipo para saber que tipo es
    ene->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    ene->definirSala(sala);//le pasamos la sala en donde esta
    enemigos.push_back(ene);//guardamos el enemigo en el vector
    id++;//generamos id para la figura
    ene->setID(id);//le damos el id unico en esta partida al enemigo
    motor->CargarEnemigos(x,y,z,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(x/2,y/2,z/2,1,1,1,2,2);
}

void Nivel::CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarJugador(x,y,z,ruta_objeto,ruta_textura);
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(x/2,y/2,z/2,3,1,1,1,1);
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

void Nivel::setThen()
{   //variables de la interpolacion
    currentTime = clock();
	acumulator = 0.0f;
    dt =1.0f/60.0f;
}

void Nivel::update()
{
  MotorFisicas* fisicas = MotorFisicas::getInstance();
    //actualizamos los enemigos
    if(enemigos.size() > 0)//posiciones interpolacion
    {
        for(std::size_t i=0;i<enemigos.size();i++)
        {
            //cout << "Enemigo " << i << endl;
            //enemigos[i]->Atacar();
            //enemigos[i]->AtacarEspecial();
        }
    }

    //actualizamos el jugador
     MotorGrafico * motor = MotorGrafico::getInstance();
    //Interpolacion
    newTime = clock();
    frameTime = newTime - currentTime;
    if(frameTime>0.25f){
        frameTime=0.25f;
    }
    currentTime = newTime;
    acumulator += frameTime;
    while(acumulator >= dt)
    {
        //actualizamos movimiento del jugador

       jugador.movimiento(dt,
            motor->estaPulsado(1),
            motor->estaPulsado(2),
            motor->estaPulsado(3),
            motor->estaPulsado(4)
        );

       motor->mostrarJugador(jugador.getX(),
            jugador.getY(),
            jugador.getZ(),
            jugador.getRX(),
            jugador.getRY(),
            jugador.getRZ()
        );

        fisicas->updateJugador(jugador.getX(),
            jugador.getY(),
            jugador.getZ(),
            jugador.getRX(),
            jugador.getRY(),
            jugador.getRZ()
        );

      // if(fisicas->getWorld()->testOverlap(fisicas->getJugador(),fisicas->getEnemies(0)))
      // {
      //   motor->colorearEnemigo(255,255,0,0,0);
      // }else{
      //   motor->colorearEnemigo(255,255,255,255,0);
      // }

      //Actualizar ataca
      if((motor->estaPulsado(5) || motor->estaPulsado(11)) && atacktime == 0.0f)
      {
          jugador.Atacar();
          atacktime = 2000.0f;
      }else{
          if(atacktime > 0.0f)
          {
            atacktime--;
          }
          if(atacktime > 0.0f && atacktime < 999.0f)
          {
            jugador.AtacarUpdate();
          }
          if(atacktime == 1000.0f) //Zona de pruebas
          {
            motor->colorearEnemigo(255,255,255,255,0);
            motor->clearDebug2();
          }
          if(atacktime > 500.0f)
          {
            //Colorear rojo
            motor->colorearJugador(255,255,0,0);
          }else{
            //Colorear gris
            motor->colorearJugador(255,0,0,255);
          }
      }
 	   acumulator -= dt;
    }

}

void Nivel::updateIA()
{

}

//Pruebas pathfinding
Sala * Nivel::getPrimeraSala()
{
    return primeraSala;
}

Enemigo * Nivel::getPrimerEnemigo()
{
    return enemigos.at(1);
}

std::vector<Enemigo*> Nivel::getEnemies()
{
  return enemigos;
}
