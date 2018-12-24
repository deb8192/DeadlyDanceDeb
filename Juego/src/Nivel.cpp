#include "Nivel.hpp"
#include <math.h>
#include "reactphysics3d.h"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton

#define PI 3.14159265358979323846

Nivel::Nivel()
{
    primeraSala = nullptr;
    fisicas = MotorFisicas::getInstance();//cogemos la instancia del motor de las fisicas
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
    ene->setVida(75);
    ene->definirSala(sala);//le pasamos la sala en donde esta
    ene->generarSonido(20,5);
    enemigos.push_back(ene);//guardamos el enemigo en el vector
    id++;//generamos id para la figura
    ene->setID(id);//le damos el id unico en esta partida al enemigo
    motor->CargarEnemigos(x,y,z,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    fisicas->crearCuerpo(x/2,y/2,z/2,1,1,1,2,2);
}

void Nivel::CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    jugador.setID(id++);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    jugador.setVida(100);
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarJugador(x,y,z,ruta_objeto,ruta_textura);
    motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
    fisicas->crearCuerpo(x/2,y/2,z/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
}

void Nivel::CrearObjeto(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarObjetos(x,y,z,ruta_objeto,ruta_textura);
    fisicas->crearCuerpo(x,y,z,1,10,10,10,3);
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
  MotorAudioSystem* motora = MotorAudioSystem::getInstance();
    //actualizamos los enemigos
    if(enemigos.size() > 0)//posiciones interpolacion
    {
        for(std::size_t i=0;i<enemigos.size();i++)
        {
            //cout << "Enemigo " << i << endl;
            //enemigos[i]->Atacar();
            //enemigos[i]->AtacarEspecial();
            //enemigos[i]->queEscuchas();
        }
    }

    //actualizamos el jugador
    MotorGrafico * motor = MotorGrafico::getInstance();
    //Interpolacion
    newTime = clock();
    frameTime = newTime - currentTime;
    if(frameTime>0.25f)
    {
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

       this->updateIA();

      //Posicion de escucha
        motora->setListenerPosition(jugador.getX(),jugador.getY(),jugador.getZ());

        jugador.MuereJugador(acumulator);
        jugador.MuereEnemigo(acumulator, enemigos.size());
 	    acumulator -= dt;  
    } 
}

void Nivel::updateAt(int *danyo, MotorGrafico *motor)
{
  if((motor->estaPulsado(KEY_ESPACIO)/* || motor->estaPulsado(10)*/) && atacktime == 0.0f)
    {
        *danyo = jugador.Atacar();
        motor->colorearJugador(255, 55, 0, 255);
        atacktime = 1500.0f;
    }else{
        if(atacktime > 0.0f)
        {
            atacktime--;
        }
        if(atacktime == 1000.0f) //Zona de pruebas
        {
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
}

void Nivel::updateAtEsp(int *danyo, MotorGrafico *motor)
{
    //Compureba si se realiza el ataque especial o si la animacion esta a medias
    if((/*motor->estaPulsado(9)|| */motor->estaPulsado(KEY_Q)) && atackEsptime == 0.0)
    {
        *danyo = jugador.AtacarEspecial();
        motor->colorearJugador(255, 55, 0, 255);
        if(*danyo > 0)
        {
            atackEsptime = 1500.0f;
        }
    }
    else
    {
        if(atackEsptime > 0.f)
        {
            atackEsptime--;
        }
        if(atackEsptime == 1000.0f)
        {
            motor->colorearEnemigo(255,255,255,255,0);
        }
        if(atackEsptime <= 750.0f && motor->getArmaEspecial()) //Zona de pruebas
        {
            motor->borrarArmaEspecial();
            motor->colorearJugador(255, 150, 150, 150);
        }
    }
}

void Nivel::updateIA()
{

    MotorGrafico * motor = MotorGrafico::getInstance();
    int danyo = 0;                      //Valor que indica si se ha podido realizar el ataque

    //Actualizar ataque especial
    this->updateAtEsp(&danyo, motor);
    this->updateAt(&danyo2, motor);

    //Si se realiza el ataque se comprueban las colisiones
    if(atackEsptime > 0.0)
    {
        jugador.AtacarEspecialUpdate(&danyo);
    }

    else if(atacktime > 0.0)
    {
        jugador.AtacarUpdate(danyo2);
    }

    //En caso contrario se colorean los enemigos de color gris
    else
    {
        for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            motor->colorearEnemigos(255, 150, 150, 150, i);
        }
    }
}

//Pruebas pathfinding
Sala * Nivel::getPrimeraSala()
{
    return primeraSala;
}

std::vector<Enemigo *>  Nivel::getEnemigos()
{
    return enemigos;
}

Jugador Nivel::getJugador()
{
    return jugador;
}

std::vector<Enemigo*> Nivel::getEnemies()
{
  return enemigos;
}
