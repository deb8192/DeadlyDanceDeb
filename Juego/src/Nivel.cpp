#include "Nivel.hpp"

#include <math.h>

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton


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
    ene->setVida(50);
    ene->definirSala(sala);//le pasamos la sala en donde esta
    enemigos.push_back(ene);//guardamos el enemigo en el vector
    id++;//generamos id para la figura
    ene->setID(id);//le damos el id unico en esta partida al enemigo
    motor->CargarEnemigos(x,y,z,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    fisicas->crearCuerpo(x/4,y/4,z/4,2,1,1,1,2);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
}

void Nivel::CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    jugador.setID(id++);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarJugador(x,y,z,ruta_objeto,ruta_textura);
    motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
    fisicas->crearCuerpo(x/2,y/2,z/2,3,1,1,1,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
    fisicas->crearCuerpo(x/2,y/2,z/2,2,5,5,0.5,4);
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
    int danyo = 0;
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
        this->updateAtEsp(&danyo, motor);

        fisicas->updateJugador(jugador.getX(),jugador.getY(),jugador.getZ(),jugador.getRX(),jugador.getRY(),jugador.getRZ());
        
        vector <unsigned int> atacados;

        if(danyo >0)
        {
            atacados = fisicas->updateArmaEspecial(jugador.getX(),jugador.getY(),jugador.getZ(),jugador.getRX(),jugador.getRY(),jugador.getRZ());
            
            if(!atacados.empty())
            {
                for(unsigned int i = 0; i < atacados.size(); i++)
                {
                    float variacion = rand() % 21 - 10;
                    variacion = variacion / 100;
                    variacion = roundf(variacion * 10) / 10;
                    danyo += (int) variacion;
                    enemigos.at(i)->QuitarVida(danyo);
                    cout<<"Daño "<<danyo<<endl;
                    cout<<"Vida enemigo "<<enemigos.at(i)->getID()<<" "<<enemigos.at(i)->getVida()<<endl;
                    motor->colorearEnemigos(255, 0, 255, 55, atacados.at(i));
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < enemigos.size(); i++)
            {
                motor->colorearEnemigos(255, 150, 150, 150, i);
            }
        }

 	   acumulator -= dt;  
    } 

}

void Nivel::updateAtEsp(int *danyo, MotorGrafico *motor)
{
//Compureba si se realiza el ataque especial o si la animacion esta a medias
    bool dibujado = false;
    if((motor->estaPulsado(9) || motor->estaPulsado(11)) || (jugador.getTimeAtEsp() > 0.0 && jugador.getTimeAtEsp() < 500.0))
    {
        if(motor->estaPulsado(9))
            cout<<"Raton"<<endl;
        else
            cout<<"Q"<<endl;
        
        if(*danyo == 0)
        {
            *danyo = jugador.AtacareEspecial();
        }
        else
        {
            cout << "PINTA" << *danyo <<endl;
            motor->colorearJugador(255, 55, 0, 255);
        }
        
        if(jugador.getTimeAtEsp() < 250)
        {
            
            motor->mostrarArmaEspecial(
            jugador.getX(), 
            jugador.getY(), 
            jugador.getZ(), 
            jugador.getRX(), 
            jugador.getRY(), 
            jugador.getRZ());

            dibujado = true;
        }
        jugador.setTimeAtEsp(jugador.getTimeAtEsp() + frameTime);
        
        

    }
    else
    {
            //cout << "NO PINTA" << *danyo <<endl;
        motor->colorearJugador(255, 150, 150, 150);
        jugador.setTimeAtEsp(0);
        *danyo = 0;
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

std::vector<Enemigo *>  Nivel::getEnemigos()
{
    return enemigos;
}

Jugador Nivel::getJugador()
{
    return jugador;
}