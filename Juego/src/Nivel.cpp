#include "Nivel.hpp"
#include "Pathfinder.hpp"
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
    controladorTiempo = times::getInstance();//obtenemos la instancia de la clase times
}

bool Nivel::CargarNivel(int level)
{
    if(primeraSala != nullptr)
    {
        primeraSala->~Sala();
        primeraSala = nullptr;
    }
    cargador.CargarNivelXml(level);

    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->cargarInterfaz();

    return false;
}

void Nivel::CrearEnemigo(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades, Sala * sala)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    //accion indicara futuramente que tipo de enemigo sera (herencia)
    MotorGrafico * motor = MotorGrafico::getInstance();//cogemos instancia del motor para crear la figura 3d
    pollo * ene = new pollo();//aqui va el tipo de enemigo que es hacer ifffffffffsssss y meter una variable nueva de tipo para saber que tipo es
    //ia
        CargadorBehaviorTrees cargadorIA;
        ene->setArbol(cargadorIA.cargarArbol("Prueba1"));
    //fin ia
    ene->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    ene->setVida(75);
    ene->setBarraAtEs(0);
    ene->definirSala(sala);//le pasamos la sala en donde esta
    ene->setAtaque(10);
    ene->setArmaEspecial(100);
    ene->setTimeAtEsp(0.0f);
    ene->setDanyoCritico(50);
    ene->setProAtaCritico(10);
    //ene->generarSonido(20,5);
    ene->setRotation(0.0f);//le ponemos hacia donde mira cuando se carga
    enemigos.push_back(ene);//guardamos el enemigo en el vector
    id++;//generamos id para la figura
    ene->setID(id);//le damos el id unico en esta partida al enemigo

    motor->CargarEnemigos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,2);

}

void Nivel::CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{   jugador.setVida(100);
    jugador.setID(id++);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setTimeAtEsp(0.0f);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    jugador.setVida(100);
    MotorGrafico * motor = MotorGrafico::getInstance();

    motor->CargarJugador(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas

}

void Nivel::CrearObjeto(int accion, const char* nombre, int ataque, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();

    if(accion == 2)
    {
        Recolectable* rec = new Recolectable(ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura);
        rec->setID(recolectables.size());
        rec->setPosiciones(x,y,z);
        recolectables.push_back(rec);

  }
    motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,3);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba

}

Sala * Nivel::CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char *ruta_objeto, const char *ruta_textura)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    Sala * sala = new Sala(ancho,largo,alto,x,y,z,centro);
    //int * datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int id = motor->CargarPlataformas(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    sala->definirID(id);

    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,6);

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

void Nivel::EraseEnemigo(int i){
    //elimniar el objeto en memoria(la onda)
    enemigos[i]->~Enemigo();//el destructor de enemigo
    enemigos[i]=nullptr;
    enemigos.erase(enemigos.begin() + i);
}
void Nivel::EraseJugador(int i){
    //jugador.erase(jugador.begin() + i);
}



void Nivel::CogerObjeto()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();

    int rec_col = fisicas->collideColectable();

        if(jugador.getArma() == nullptr)//si no tiene arma equipada
        {
            //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)recolectables[rec_col];
            Arma* nuArma = new Arma(recolectables[rec_col]->getAtaque(),recolectables[rec_col]->getNombre(),recolectables[rec_col]->getAncho(),recolectables[rec_col]->getLargo(),recolectables[rec_col]->getAlto(),recolectables[rec_col]->getObjeto(),recolectables[rec_col]->getTextura());
            jugador.setArma(nuArma);
            //lo cargamos por primera vez en el motor de graficos
            motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), recolectables[rec_col]->getObjeto(), recolectables[rec_col]->getTextura());
            //lo cargamos por primera vez en el motor de fisicas
            fisicas->crearCuerpo(0,jugador.getX()/2,jugador.getY()/2,jugador.getZ()/2,2,recolectables[rec_col]->getAncho(), recolectables[rec_col]->getLargo(), recolectables[rec_col]->getAlto(), 6);
            //borramos el recolectable de nivel, motor grafico y motor fisicas
            recolectables.erase(recolectables.begin() + rec_col);
            motor->EraseColectable(rec_col);
            fisicas->EraseColectable(rec_col);
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
        else if(jugador.getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
            nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
            Arma* nuArma = new Arma(recolectables[rec_col]->getAtaque(),recolectables[rec_col]->getNombre(),recolectables[rec_col]->getAncho(),recolectables[rec_col]->getLargo(),recolectables[rec_col]->getAlto(),recolectables[rec_col]->getObjeto(),recolectables[rec_col]->getTextura());
            motor->EraseArma();
            jugador.setArma(nuArma);
            //lo cargamos por primera vez en el motor de graficos
            motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), recolectables[rec_col]->getObjeto(), recolectables[rec_col]->getTextura());
            //lo cargamos en el motor de fisicas
            fisicas->setFormaArma(jugador.getX()/2, jugador.getY()/2, jugador.getZ()/2, jugador.getArma()->getAncho(), jugador.getArma()->getLargo(),jugador.getArma()->getAlto());
            //borramos el recolectable anterior de nivel, motor grafico y motor fisicas
            recolectables.erase(recolectables.begin() + rec_col);
            motor->EraseColectable(rec_col);
            fisicas->EraseColectable(rec_col);
            //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
            recolectables.push_back(nuRec);
            fisicas->setFormaRecolectable(recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
            motor->CargarRecolectable(recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }

}

void Nivel::DejarObjeto()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();

        if(jugador.getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
            nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
            motor->EraseArma();
            fisicas->EraseArma();
            jugador.setArma(NULL);

            //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
            recolectables.push_back(nuRec);
            fisicas->setFormaRecolectable(recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
            motor->CargarRecolectable(recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
        }

}

void Nivel::pulsarE()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();
    //lo siguiente es para saber que objeto colisiona con jugador
    int rec_col = fisicas->collideColectable();

    //cambia se utiliza porque coge y suelta el objeto sucesivamente varias veces, la causa de este error
    //era porque ocurren varias iteraciones del bucle tal vez porque la interpolacion crea mas iteraciones en el bucle
    if(motor->estaPulsado(KEY_E))
    {
        if(rec_col < 0)
        {
            if(cambia <= 0)
            {
                DejarObjeto();
            }
            cambia++;
        }
        else if(rec_col >= 0)
        {
            if(cambia <= 0)
            {
                CogerObjeto();
            }
            cambia++;
        }
    }
    else{
        cambia = 0;
    }
    motor->resetKey(KEY_E);
    //cout << "cambia: " << cambia << endl; //esto es para ver cuantas iteraciones de bucle pasan cuando coge objeto
}




void Nivel::update()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();

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

    if(jugador.getArma() != nullptr)
    {
        //iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
        jugador.getArma()->setPosiciones(jugador.getX(), jugador.getY(), jugador.getZ());
        motor->llevarObjeto(jugador.getX(), jugador.getY()+3,jugador.getZ(), jugador.getRX(), jugador.getRY(), jugador.getRZ() );
        fisicas->llevarBox(jugador.getX(), jugador.getY()+3,jugador.getZ(), jugador.getArma()->getAncho(), jugador.getArma()->getLargo(), jugador.getArma()->getAlto());
    }


      //adelanta posicion del bounding box al jugador, mientras pulses esa direccion si colisiona no se mueve
      fisicas->colisionChecker(motor->estaPulsado(1),
          motor->estaPulsado(2),
          motor->estaPulsado(3),
          motor->estaPulsado(4),
          jugador.getX(),
          jugador.getY(),
          jugador.getZ()
      );

      //colisiones con todos los objetos y enemigos que no se traspasan
      if(fisicas->collideObstacle())
      {
        //colisiona
      }
      else if(fisicas->collidePlatform())//solo se mueve estando sobre una plataforma
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

        /*for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            fisicas->updateEnemigos(enemigos.at(i)->getX(),
                enemigos.at(i)->getY(),
                enemigos.at(i)->getZ(),
                i
            );
        }*/

        for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            motor->mostrarEnemigos(enemigos.at(i)->getX(),
                enemigos.at(i)->getY(),
                enemigos.at(i)->getZ(),
                enemigos.at(i)->getRX(),
                enemigos.at(i)->getRY(),
                enemigos.at(i)->getRZ(),
                i
            );
        }

        fisicas->updateJugador(jugador.getX(),
            jugador.getY(),
            jugador.getZ()
        );
      }
       //this->updateIA(); esto no se fuerza desde el update normal se llama desde main 4 veces por segundo
       //Actualizar ataque especial
        this->updateAtEsp(motor);
        this->updateAt(&danyo2, motor);
        //this->updateRecorridoPathfinding();

        //Si se realiza el ataque se comprueban las colisiones
        if(jugador.getTimeAtEsp() > 0.0)
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
                motor->colorearEnemigo(255, 150, 150, 150, i);
            }
        }

      //Posicion de escucha
       motora->setListenerPosition(jugador.getX(),jugador.getY(),jugador.getZ());

       //actualizamos los enemigos
       if(enemigos.size() > 0)//posiciones interpolacion
       {
           float tiempoActual = 0.0f, tiempoAtaqueEsp = 0.0f;
           for(std::size_t i=0;i<enemigos.size();i++)
           {
                int danyo_jug = 0;
                //si el tiempo de ataque es mayor que 0, ir restando 1 hasta 0
                if(enemigos[i]->getTimeAtEsp() > 0.0f)
                {
                    tiempoActual = controladorTiempo->getTiempo(2);
                    tiempoAtaqueEsp = enemigos[i]->getTimeAtEsp();
                    tiempoAtaqueEsp -= (tiempoActual - enemigos[i]->getLastTimeAtEsp());
                    enemigos[i]->setLastTimeAtEsp(tiempoActual);
                    enemigos[i]->setTimeAtEsp(tiempoAtaqueEsp); //restar uno al tiempo de ataque
                }
                if(enemigos[i]->getTimeAtEsp() <= 0.0f)
                {
                    danyo_jug = enemigos[i]->AtacarEspecial();
                    enemigos[i]->setTimeAtEsp(10.0f); //tiempo hasta el proximo ataque
                    enemigos[i]->setLastTimeAtEsp(controladorTiempo->getTiempo(2));
            
                }
                else if(enemigos[i]->getBarraAtEs() < 100)
                {
                    enemigos[i]->AumentarBarraAtEs(1);
                }
                if(danyo_jug == 0)
                {
                    //cout << "Enemigo " << i << endl;
                    //Si el enemigo ha realizado danyo
                    danyo_jug = enemigos[i]->Atacar();
                    if(danyo_jug > 0)
                    {
                        jugador.QuitarVida(danyo_jug);
                        cout<< "Vida jugador: "<< jugador.getVida() << endl;
                        enemigos[i]->setAtackTime(1500.0f); //tiempo hasta el proximo ataque
                    }
                    //si el tiempo de ataque es mayor que 0, ir restando 1 hasta 0
                    if(enemigos[i]->getAtackTime() > 0.0f)
                    {
                        enemigos[i]->setAtackTime(enemigos[i]->getAtackTime() - 1.0f); //restar uno al tiempo de ataque
                    }
                }
                //Se le quita vida con el danyo del ataque especial
                else
                {
                    if(danyo_jug > 0)
                    {
                        jugador.QuitarVida(danyo_jug);
                        cout<< "Vida jugador tras ataque especial: "<< jugador.getVida() << endl;
                    }
                }
               //enemigos[i]->queVes();
           }
       }
        jugador.MuereJugador(acumulator);
        //enemigos->MuereEnemigo(acumulator);
 	      acumulator -= dt;
    }
    
    //actualizamos la interfaz de jugador
    jugador.updateInterfaz();
    //actualizamos la interfaz en motor grafico
    motor->updateInterfaz();
}

void Nivel::updateAt(int *danyo, MotorGrafico *motor)
{
  if((motor->estaPulsado(KEY_ESPACIO) || motor->estaPulsado(LMOUSE_DOWN)) && atacktime == 0.0f)
    {
        *danyo = jugador.Atacar();
        motor->resetKey(KEY_ESPACIO);
        motor->resetEvento(LMOUSE_DOWN);
        atacktime = 1500.0f;
    }else{
        if(atacktime > 0.0f)
        {
            atacktime--;
        }
        if(atacktime > 500.0f)
        {
            //Colorear rojo
            motor->colorearJugador(255,255,0,0);
        }else if(atacktime > 0.0f){
            //Colorear gris
            motor->colorearJugador(255,150,150,150);
        }
    }

    //clear
    if(atacktime == 0.0f){
      motor->clearDebug2();
    }
}

void Nivel::updateAtEsp(MotorGrafico *motor)
{
    float tiempoActual = 0.0f;
    float tiempoAtaqueEsp = 0.0f;
    //Compureba si se realiza el ataque especial o si la animacion esta a medias
    if((motor->estaPulsado(RMOUSE_DOWN)||motor->estaPulsado(KEY_Q)) && jugador.getTimeAtEsp() <= 0.0)
    {
        danyo = jugador.AtacarEspecial();
        motor->resetKey(KEY_Q);
        motor->resetEvento(RMOUSE_DOWN);
        motor->colorearJugador(255, 55, 0, 255);
        if(danyo > 0)
        {
            jugador.setTimeAtEsp(1.5f);
            jugador.setLastTimeAtEsp(controladorTiempo->getTiempo(2));
            
        }
    }
    else
    {
        if(danyo > 0)
        {
            danyo = 0;
        }
        if(jugador.getTimeAtEsp() > 0.f)
        {
            tiempoActual = controladorTiempo->getTiempo(2);
            tiempoAtaqueEsp = jugador.getTimeAtEsp();
            tiempoAtaqueEsp -= (tiempoActual - jugador.getLastTimeAtEsp());
            jugador.setLastTimeAtEsp(tiempoActual);
            jugador.setTimeAtEsp(tiempoAtaqueEsp);
        }
        if(jugador.getTimeAtEsp() > 0.f && (int) (jugador.getTimeAtEsp() * 100) % 25 == 0.f)
        {
            danyo = jugador.AtacarEspecial();
        }
        if(jugador.getTimeAtEsp() == 1.0f)
        {
            motor->colorearEnemigo(255,255,255,255,0);
        }
        if(jugador.getTimeAtEsp() <= 0.5f && motor->getArmaEspecial()) //Zona de pruebas
        {
            motor->borrarArmaEspecial();
            motor->colorearJugador(255, 150, 150, 150);
        }
    }
}

void Nivel::updateIA()
{
    //cout<< "Ejecuto ia " << endl;
    MotorGrafico * motor = MotorGrafico::getInstance();

    //Actualizar ataque especial
    /*this->updateAtEsp(motor);
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
            motor->colorearEnemigo(255, 150, 150, 150, i);
        }
    }*/

    //En esta parte mueren
    if(jugador.estasMuerto()){
        //motor->EraseJugador(jugador);
    }
    if(enemigos.size() > 0){
        //comprobando los enemigos para saber si estan muertos
        for(std::size_t i=0;i<enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

            if(enemigos[i]->estasMuerto() && enemigos[i]->finalAnimMuerte()){

                motor->EraseEnemigo(i);
                fisicas->EraseEnemigo(i);
                EraseEnemigo(i);
            }else{
                if(enemigos[i]->estasMuerto()){
                    enemigos[i]->MuereEnemigo(i);
                }
            }
        }
    }
    //En esta parte mueren
    if(jugador.estasMuerto()){
        //motor->EraseJugador(jugador);
    }
    if(enemigos.size() > 0){
        //comprobando los enemigos para saber si estan muertos
        for(std::size_t i=0;i<enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

            if(enemigos[i]->estasMuerto() && enemigos[i]->finalAnimMuerte()){

                motor->EraseEnemigo(i);
                fisicas->EraseEnemigo(i);
                EraseEnemigo(i);
            }else
            {
                if(enemigos[i]->estasMuerto()){
                    enemigos[i]->MuereEnemigo(i);
                }
                else
                {
                    //si no esta muerto ni piensa morirse XD ejecutamos ia
                    //cout<< "Ejecuto ia: " << i << endl;
                    enemigos[i]->runIA();
                }
            }
        }
    }
}


void Nivel::updateRecorridoPathfinding()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    //Ejecucion del pathfinding de momento al pulsar P
    if(motor->estaPulsado(KEY_P) || !recorrido.empty())
    {
        bool colorear = false;
        motor->resetKey(KEY_P);
        Pathfinder path;
        int tipoCentro;
        if(!colorear)
        {
            motor->colorearEnemigo(255, 127, 0, 127, 1);
            colorear = true;
        }
        //Se inicia el recorrido hacia la primera sala del arbol de salas
        //Se cambiara para buscar al enemigo que pide ayuda.
        if(recorrido.empty() && !enemigos.empty())
        {
            enemigoSeleccionado++;
            if(enemigoSeleccionado == enemigos.size())
            {
                enemigoSeleccionado = 0;
            }
            recorrido = path.encontrarCamino(enemigos.at(enemigoSeleccionado)->getSala(), primeraSala);
        }
        //Desplazamiento del enemigo hacia su destino
        if(!recorrido.empty())
        {
            //Se comprueban las coordenadas del enemigo y si ha llegado a la siguiente
            //sala del camino a la que debe ir o no. Se tienen en cuenta los tipos de centros
            //para realizar las comprobaciones de coordenadas adecuadas con el ancho y alto de las salas
            if(enemigos.at(enemigoSeleccionado)->getSala() != recorrido.front().nodo)
            {
                bool cambia = false, moveDer = false, moveIzq = false, moveArb = false, moveAbj = false;
                tipoCentro = recorrido.front().nodo->getType();
                //Centro arriba a la izquierda
                if(tipoCentro == 4)
                {
                    if(enemigos.at(enemigoSeleccionado)->getX() >= recorrido.front().nodo->getSizes()[2] && enemigos.at(enemigoSeleccionado)->getX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() < recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }
                    if(cambia && (enemigos.at(enemigoSeleccionado)->getZ() >= recorrido.front().nodo->getSizes()[4] && enemigos.at(enemigoSeleccionado)->getZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        enemigos.at(enemigoSeleccionado)->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la izquierda
                else if(tipoCentro == 3)
                {
                    if(enemigos.at(enemigoSeleccionado)->getX() >= recorrido.front().nodo->getSizes()[2] && enemigos.at(enemigoSeleccionado)->getX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() < recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }

                    if(cambia && (enemigos.at(enemigoSeleccionado)->getZ() >= recorrido.front().nodo->getSizes()[4] && enemigos.at(enemigoSeleccionado)->getZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        enemigos.at(enemigoSeleccionado)->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() > recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro arriba a la derecha
                else if(tipoCentro == 2)
                {
                    if(enemigos.at(enemigoSeleccionado)->getX() <= recorrido.front().nodo->getSizes()[2] && enemigos.at(enemigoSeleccionado)->getX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (enemigos.at(enemigoSeleccionado)->getZ() >= recorrido.front().nodo->getSizes()[4] && enemigos.at(enemigoSeleccionado)->getZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        enemigos.at(enemigoSeleccionado)->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la derecha
                else if(tipoCentro == 1)
                {
                    if(enemigos.at(enemigoSeleccionado)->getX() <= recorrido.front().nodo->getSizes()[2] && enemigos.at(enemigoSeleccionado)->getX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (enemigos.at(enemigoSeleccionado)->getZ() <= recorrido.front().nodo->getSizes()[4] && enemigos.at(enemigoSeleccionado)->getZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] )))
                    {
                        enemigos.at(enemigoSeleccionado)->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() > recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro en el centro
                else if(tipoCentro == 0)
                {
                    if(enemigos.at(enemigoSeleccionado)->getX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2) && enemigos.at(enemigoSeleccionado)->getX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        cambia = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveIzq = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveDer = true;
                    }

                    if(cambia && (enemigos.at(enemigoSeleccionado)->getZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2) && enemigos.at(enemigoSeleccionado)->getZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2)))
                    {
                        enemigos.at(enemigoSeleccionado)->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveArb = true;
                    }
                    else if(enemigos.at(enemigoSeleccionado)->getZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveAbj = true;
                    }
                }
                if(moveAbj)
                {
                    if(moveDer)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() + 1.0 * 0.25, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() + frameTime);
                        cout<<"Posicion del enemigo: x="<<enemigos.at(enemigoSeleccionado)->getX()<<" z=" << enemigos.at(enemigoSeleccionado)->getY();
                    }
                    else if(moveIzq)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() - 1.0 * 0.25, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() + frameTime);
                    }
                    else
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX(), enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() + frameTime);
                    }
                }
                else if(moveArb)
                {
                    if(moveDer)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() + frameTime, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() - frameTime);
                    }
                    else if(moveIzq)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() - frameTime, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() - frameTime);
                    }
                    else
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX(), enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ() - frameTime);
                    }
                }
                else
                {
                    if(moveDer)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() + frameTime, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ());
                    }
                    else if(moveIzq)
                    {
                        enemigos.at(enemigoSeleccionado)->setPosiciones(enemigos.at(enemigoSeleccionado)->getX() - frameTime, enemigos.at(enemigoSeleccionado)->getY(), enemigos.at(enemigoSeleccionado)->getZ());
                    }
                }
            }
            else
            {
                cout<<"nodo actual: "<<enemigos.at(enemigoSeleccionado)->getSala()->getPosicionEnGrafica()<<endl;

                recorrido.erase(recorrido.begin());
            }
        }
    }
}

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
