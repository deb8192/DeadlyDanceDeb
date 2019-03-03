#include "Jugando.hpp"
#include "../Juego.hpp"
#include "../Enemigos/Pollo.hpp"
#include "../ConstantesComunes.hpp"
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
//singleton
Jugando* Jugando::_unicaInstancia = 0;
//fin indicador singleton

#define PALANCA "palanca"

Jugando::Jugando()
{
    
}

Jugando::~Jugando()
{
    reiniciando = false;
    jugadorInmovil = false;
    drawTime = 0;
    lastDrawTime = 0;
    atacktime = 0;
    id = 0;
    cambia = 0;
    danyo = 0;
    danyo2 = 0;
    contadorEnem = 0;
    int_cpw_aux = 0;

    //Jugador jugador;
    //CargadorNiveles cargador;
    //CargadorBehaviorTrees cargadorIA;
    //vector<Pathfinder::NodeRecord> recorrido;

    // Punteros sin new
    _enemPideAyuda = nullptr;
    _destinoPathFinding = nullptr;
    _jugador = nullptr;

    // Punteros a clases singleton
    _controladorTiempo = nullptr;
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;
    _motor = nullptr;
    _interfaz = nullptr;

    // Liberar memoria
    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        delete _enemigos.at(i);
    }
    _enemigos.clear();

    tam = _auxiliadores.size();
    for(short i=0; i < tam; i++)
    {
        delete _auxiliadores.at(i);
    }
    _auxiliadores.clear();

    tam = _interactuables.size();
    for(short i=0; i < tam; i++)
    {
        delete _interactuables.at(i);
    }
    _interactuables.clear();

    tam = _recolectables.size();
    for(short i=0; i < tam; i++)
    {
        delete _recolectables.at(i);
    }
    _recolectables.clear();

    tam = _powerup.size();
    for(short i=0; i < tam; i++)
    {
        delete _powerup.at(i);
    }
    _powerup.clear();

    tam = _zonas.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonas.at(i);
    }
    _zonas.clear();

    //delete _primeraSala;
    delete _unicaInstancia;
}

void Jugando::Iniciar()
{
    cout << "\e[42m Entrando en Estado - Jugando \e[0m" << endl;
    
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _fisicas = MotorFisicas::getInstance();
    _sense = SenseEventos::getInstance();
    _controladorTiempo = Times::GetInstance();
    _interfaz = InterfazJugador::getInstance();

    _motor->CargarInterfaz();
    
    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    CargarNivel(5, 1); //(level, player) 1 = heavy / 2 = bailaora

    reiniciando = false;
    
    ValoresPorDefecto();

    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
}

void Jugando::ValoresPorDefecto()
{
    id = 0;
    //_primeraSala = nullptr;
    //drawTime = _controladorTiempo->GetTiempo(2);
    drawTime = 0.0f;
    lastDrawTime = drawTime;
    atacktime = 0.0f;
    cambia = 0;
    _enemPideAyuda = nullptr;
    _destinoPathFinding = nullptr;
    danyo = 0;
    danyo2 = 0;
    contadorEnem = 0;
    int_cpw_aux = 0;

    // Activamos la interfaz
    _interfaz->activar();
}

void Jugando::ValoresPorDefectoJugador()
{
    float xIni = _jugador->getIniX();
    float yIni = _jugador->getIniY();
    float zIni = _jugador->getIniZ();
    
    jugadorInmovil = false;
    _jugador->setDinero(0);
    _jugador->setVida(_jugador->getVidaIni());
    _jugador->setBarraAtEs(100);
    _jugador->setAtaque(15);
    _jugador->setArma(NULL);
    _jugador->setArmaEspecial(100);
    _jugador->setTimeAtEsp(0.0f);
    _jugador->setDanyoCritico(50);
    _jugador->setProAtaCritico(10);
    _jugador->setPosiciones(xIni, yIni, zIni);
    _jugador->setNewPosiciones(xIni, yIni, zIni);
    _jugador->initPosicionesFisicas(xIni/2, yIni/2, zIni/2);
    //TO DO: revisar que lo haga bien
    //_jugador->setRotacion(0,180,0);
    //_jugador->setNewRotacion(0,180,0);
}

// TO DO: Revisar si el cuerpo fisico tambn se tiene q cambiar
void Jugando::PosicionesIniEnemigos()
{
    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        Enemigo* _ene = _enemigos.at(i);
        _ene->setPosiciones(_ene->getIniX(), 
            _ene->getIniY(), _ene->getIniZ());
        
        _ene->setVida(_ene->getVidaIni());

        _ene = nullptr;
    }
}

// Desactiva el modo debug en MotorGrafico
 void Jugando::DesactivarDebug()
 {
     if (_motor->GetDebugActivado())
     {
        _motor->activarDebugGrafico();
     }
 }

void Jugando::ManejarEventos() {
    // ESC o P para abrir menu de pausa
    if (_motor->EstaPulsado(KEY_ESC) || 
        _motor->EstaPulsado(KEY_P)) {
        
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_P);
        Juego::GetInstance()->estado.CambioEstadoPausa();
    }

    /* *********** Teclas para probar cosas *************** */

    if (_motor->EstaPulsado(KEY_K))
    {
        _motor->ResetKey(KEY_K);
        _jugador->setVida(0);
    }

    //para modo debug
    if(_motor->EstaPulsado(KEY_G_DEBUG))
    {
        _motor->activarDebugGrafico();
        _motor->ResetKey(KEY_G_DEBUG);
    }

    //para pathfinding activado
    if(_motor->EstaPulsado(KEY_C))
    {
        _motor->activarPathfinding();
        _motor->ResetKey(KEY_C);
    }
    /* **************************************************** */
    
    //cambia se utiliza porque coge y suelta el objeto sucesivamente varias veces, la causa de este error
    //era porque ocurren varias iteraciones del bucle tal vez porque la interpolacion crea mas iteraciones en el bucle
    if(_motor->EstaPulsado(KEY_E))
    {
        _motor->ResetKey(KEY_E);
        InteractuarNivel();
    }
    else{
        cambia = 0;
    }
    //cout << "cambia: " << cambia << endl; //esto es para ver cuantas iteraciones de bucle pasan cuando coge objeto
}

/************************** InteractuarNivel* ************************
* Detecta las posiciones de los objetos recolectables y de interaccion
* y si está pulsado E interactua y si no lo pinta de color para destacarlo
*/
void Jugando::InteractuarNivel()
{
    //lo siguiente es para saber que objeto colisiona con jugador
    int rec_col = _fisicas->collideColectable();
    int int_col = _fisicas->collideInteractuable();

    if(rec_col < 0 && int_col < 0)
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
    else if(int_col >= 0)
    {
        if(cambia <= 0)
        {
            cout<<"Detecta el objeto"<<endl;
            this->AccionarMecanismo(int_col);
        }
        cambia++;
    }
}

/************** Update *************
*  Bucle de actualizacion del juego
*  Entradas:
*
*  Salidas:
* */
void Jugando::Update()
{
    Constantes constantes;
    _motor->clearDebug();
    _motora->update(false); //Actualiza el motor de audio
    _sense->update(); //Se actualizan sentidos

    if (_jugador->EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        _jugador->MuereJugador(); // Animacion de muerte
        DesactivarDebug();
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }

     /*Debo actualizar puertas en vector puertas de nivel segun vector puertas de fisicas*/
        //int i = 0;
        for(unsigned int i = 0; i < puertas.size(); i++)        
        {
            cout << "PUERTA:: "<< _fisicas->GetPuertaX(i) << "-" << _fisicas->GetPuertaY(i) << "-" << _fisicas->GetPuertaZ(i) << endl;
            cout << "PUERTA:: "<< _fisicas->GetPuertaRX(i) << "-" << _fisicas->GetPuertaRY(i) << "-" << _fisicas->GetPuertaRZ(i) << endl;
             
            puertas[i]->setPosiciones(_fisicas->GetPuertaX(i)*2,_fisicas->GetPuertaY(i)*0,_fisicas->GetPuertaZ(i)*2);
            puertas[i]->setRotacion(_fisicas->GetPuertaRX(i),_fisicas->GetPuertaRY(i),_fisicas->GetPuertaRZ(i));
        }
        
    // ********** se actualiza posiciones e interpolado **********
    //animacion
    _motor->cambiarAnimacionJugador(_jugador->getAnimacion());

    if(_jugador->getArma() != nullptr)
    {
        float posArmaX = 5*  sin(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getX();
        float posArmaZ = 5*  cos(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getZ();//iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
        _jugador->getArma()->setPosiciones(posArmaX, _jugador->getY()+3, posArmaZ);
        _motor->llevarObjeto(posArmaX, _jugador->getY()+3,posArmaZ, _jugador->getRX(), _jugador->getRY(), _jugador->getRZ() );
        _fisicas->llevarBox(posArmaX, _jugador->getY()+3,posArmaZ, _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(), _jugador->getArma()->getAlto());
    }

    //Comprueba la activacion de un powerup
    this->activarPowerUp();

    // Adelanta posicion del bounding box al jugador, mientras pulses esa direccion si colisiona no se mueve
    _fisicas->colisionChecker(_motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W),
        _jugador->getNewX(),
        _jugador->getNewY(),
        _jugador->getNewZ()
    );

    //colisiones con todos los objetos y _enemigos que no se traspasan
    if(_fisicas->collideObstacle() || !_fisicas->collidePlatform())
    {
        //colisiona
        jugadorInmovil = true;
        _jugador->setNewPosiciones(_jugador->getX(), _jugador->getY(), _jugador->getZ());
    }
    else
    {
        //no colisiona
        jugadorInmovil = false;
    }
    
    // Actualizar movimiento del jugador
    _jugador->movimiento(jugadorInmovil,
        _motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W)
    );

    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        _fisicas->updateEnemigos(_enemigos.at(i)->getFisX(),
            _enemigos.at(i)->getFisY(),
            _enemigos.at(i)->getFisZ(),
            i
        );
    }

    _fisicas->updateJugador(_jugador->getX(),
        _jugador->getY(),
        _jugador->getZ()
    );

    if(_enemPideAyuda != nullptr)   //Solo llama desde aqui a pathfinding si hay un enemigo pidiendo ayuda y _enemigos buscandole.
    {
        this->updateRecorridoPathfinding(nullptr);
    }
    
    //Actualizar ataque especial
    this->updateAtEsp();
    this->updateAt(&danyo2);

    //Si se realiza el ataque se comprueban las colisiones
    if(_jugador->getTimeAtEsp() > 0.0)
    {
        _jugador->AtacarEspecialUpdate(&danyo);
    }
    else if(_jugador->getTimeAt() > 0.0)
    {
        _jugador->AtacarUpdate(danyo2);
    }
    else //En caso contrario se colorean los _enemigos de color gris
    {
        for(unsigned int i = 0; i < _enemigos.size(); i++)
        {
            _motor->colorearEnemigo(255, 150, 150, 150, i);
        }
    }

    //Posicion de escucha
    _motora->setListenerPosition(_jugador->getX(),_jugador->getY(),_jugador->getZ());

    //actualizamos los _enemigos
    if(_enemigos.size() > 0)//posiciones interpolacion
    {
        //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;
        for(short i=0;(unsigned)i<_enemigos.size();i++)
        {
            cout<< "Ejecuto nodo actual de la ia: " << i << endl;
            if(_enemigos[i] != nullptr)
            {
                _enemigos[i]->UpdateBehavior(&i);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento

                    //Este bloque se da si el enemigo esta en el proceso de merodear
                    if(_enemigos.at(i)->getTimeMerodear() > 0.0f)
                    {
                        if(_enemigos.at(i)->getTimeMerodear() == 1.5f)
                        {
                            //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                            _enemigos.at(i)->setLastTimeMerodear(_controladorTiempo->GetTiempo(2));
                        }
                        float tiempoActual = 0.0f, tiempoMerodear = 0.0f;
                        tiempoActual = _controladorTiempo->GetTiempo(2);
                        tiempoMerodear = _enemigos.at(i)->getTimeMerodear();
                        tiempoMerodear -= (tiempoActual - _enemigos.at(i)->getLastTimeMerodear());
                        if(tiempoActual > _enemigos.at(i)->getLastTimeMerodear())
                        {
                            //Si no es la primera vez que entra al bucle de merodear, tiempoActual debe ser mayor que lastTimeMerodear
                            //por lo que guardamos en lastTimeMerodear a tiempoActual
                            _enemigos.at(i)->setLastTimeMerodear(tiempoActual);
                        }
                        _enemigos.at(i)->setTimeMerodear(tiempoMerodear);
                    }
                    //FUNCIONA REGULAR
                    if(_fisicas->enemyCollideObstacle(i) || !_fisicas->enemyCollidePlatform(i))
                    {
                        //colisiona
                        struct DatosDesplazamiento
                        {   
                            float x = 0.0f;
                            float y = 0.0f;
                            float z = 0.0f;
                        }
                        velocidad, posicionesPasadas;

                        velocidad.x = (_enemigos.at(i)->getNewX() - _enemigos.at(i)->getLastX()) * constantes.DOS;
                        velocidad.y = (_enemigos.at(i)->getNewY() - _enemigos.at(i)->getLastY()) * constantes.DOS;
                        velocidad.z = (_enemigos.at(i)->getNewZ() - _enemigos.at(i)->getLastZ()) * constantes.DOS;
                        posicionesPasadas.x = _enemigos.at(i)->getLastX() - velocidad.x;
                        posicionesPasadas.y = _enemigos.at(i)->getLastY() - velocidad.y;
                        posicionesPasadas.z = _enemigos.at(i)->getLastZ() - velocidad.z;

                        _enemigos.at(i)->setPosicionesFisicas(-velocidad.x, 0.0f, -velocidad.z);//colisiona
                        //enemigos.at(i)->setPosiciones(_enemigos.at(i)->getX() - velocidad.x, _enemigos.at(i)->getLasY() - velocidad.y, _enemigos.at(i)->getLastZ() - velocidad.z);//colisiona         
                        _enemigos.at(i)->setNewPosiciones(_enemigos.at(i)->getNewX() - velocidad.x, _enemigos.at(i)->getNewY() - velocidad.y, _enemigos.at(i)->getNewZ() - velocidad.z);//colisiona                                
                        _enemigos.at(i)->setLastPosiciones(posicionesPasadas.x, posicionesPasadas.y, posicionesPasadas.z);//colisiona                                
                        if(_enemigos.at(i)->GetRotation() != 0.0f)
                        {
                            _enemigos.at(i)->setNewRotacion(_enemigos.at(i)->getRX(), _enemigos.at(i)->getRY() - constantes.PI_RADIAN, _enemigos.at(i)->getRZ());
                            _enemigos.at(i)->setRotation(0.0f); 
                        }
                    }

            }
            //_enemigos[i]->queVes();
        }
    }
        //_enemigos->MuereEnemigo(acumulator);
        //acumulator -= dt;
    //}
}

void Jugando::UpdateIA()
{
    Constantes constantes;
    /* *********** Teclas para probar cosas *************** */
    if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        _jugador->ModificarVida(-20);
    }
    /* **************************************************** */
    
    //En esta parte muere enemigo
    if(_enemigos.size() > 0){
        //comprobando los _enemigos para saber si estan muertos
        for(short i=0;(unsigned)i<_enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

            if(_enemigos[i]->estasMuerto() && _enemigos[i]->finalAnimMuerte()){

                //Crear un power-up/dinero
                //Se crea un power-up?
                srand(time(NULL));
                int secreapower = rand() % 101; //Entre 0 y 100
                cout << "secreapower:" << secreapower << endl;

                if(secreapower <= 100){ //20% de posibilidades
                    //Cual power-up? (ataque) 0 = vida, 1 = energia, 2 = monedas
                    srand(time(NULL));
                    int numpow = 3;
                    int cualpower = rand() % numpow;
                    cout << "POWER: " << cualpower << endl;
                    int ataque;
                    const char* nombre,*modelo,*textura;

                    //DAtos comunes a todos
                    int x = _enemigos[i]->getX();
                    int y = _enemigos[i]->getY();
                    int z = _enemigos[i]->getZ();
                    int accion = 4;
                    int ancho = 0.5 ,largo = 0.5,alto = 0.5;
                    int codigo = -2;
                    int*  propiedades = new int [6];

                    if(cualpower == 0)
                    {
                    ataque = 0;
                    nombre = "vida_up";
                    modelo = "assets/models/powerup0.obj";
                    textura = "assets/models/powerup0.mtl";
                    }
                    else if(cualpower == 1)
                    {
                    ataque = 1;
                    nombre = "energy_up";
                    modelo = "assets/models/powerup1.obj";
                    textura = "assets/models/powerup1.mtl";
                    }
                    else if(cualpower == 2)
                    {
                    ataque = 2;
                    nombre = "gold_up";
                    modelo = "assets/models/gold.obj";
                    textura = "assets/models/gold.mtl";
                    //oro entre 1 y 5 monedas
                    srand(time(NULL));
                    int orocant = 1 + rand() % 5; //variable = limite_inf + rand() % (limite_sup + 1 - limite_inf)
                    propiedades[0] = orocant; //para pasarlo a crear objeto
                    }

                    //Crear objeto
                    this->CrearObjeto(codigo,accion,nombre,ataque,0,x,y,z,0,0,ancho,largo,alto,modelo,textura,propiedades);
                }

                //Borrar enemigo
                _motor->EraseEnemigo(i);
                _fisicas->EraseEnemigo(i);
                EraseEnemigo(i);

            }else{
                if(_enemigos[i]->estasMuerto()){
                    _enemigos[i]->MuereEnemigo(i);
                }
                else
                {
                    //si no esta muerto ni piensa morirse XD ejecutamos ia
                    cout<< "Ejecuto ia: " << i << endl;
                    if(_enemigos[i] != nullptr)
                    {
                        _enemigos[i]->UpdateIA();    //Ejecuta la llamada al arbol de comportamiento para realizar la siguiente accion
                        /*enemigos[i]->UpdateBehavior(&i);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                        
                        //Este bloque se da si el enemigo esta en el proceso de merodear
                        if(_enemigos.at(i)->getTimeMerodear() > 0.0f)
                        {
                            if(_enemigos.at(i)->getTimeMerodear() == 1.5f)
                            {
                                //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                                _enemigos.at(i)->setLastTimeMerodear(_controladorTiempo->GetTiempo(2));
                            }
                            float tiempoActual = 0.0f, tiempoMerodear = 0.0f;
                            tiempoActual = _controladorTiempo->GetTiempo(2);
                            tiempoMerodear = _enemigos.at(i)->getTimeMerodear();
                            tiempoMerodear -= (tiempoActual - _enemigos.at(i)->getLastTimeMerodear());
                            if(tiempoActual > _enemigos.at(i)->getLastTimeMerodear())
                            {
                                //Si no es la primera vez que entra al bucle de merodear, tiempoActual debe ser mayor que lastTimeMerodear
                                //por lo que guardamos en lastTimeMerodear a tiempoActual
                                _enemigos.at(i)->setLastTimeMerodear(tiempoActual);
                            }
                            _enemigos.at(i)->setTimeMerodear(tiempoMerodear);
                        }
                        //AUN NO FUNCIONA
                        if(_fisicas->enemyCollideObstacle(i) || !_fisicas->enemyCollidePlatform(i))
                        {
                            //colisiona
                            _enemigos.at(i)->initPosicionesFisicas(_enemigos.at(i)->getLastX()/2, _enemigos.at(i)->getLastY()/2, _enemigos.at(i)->getLastZ()/2);//colisiona
                            _enemigos.at(i)->setPosiciones(_enemigos.at(i)->getLastX(), _enemigos.at(i)->getLastY(), _enemigos.at(i)->getLastZ());//colisiona        
                            _enemigos.at(i)->setNewPosiciones(_enemigos.at(i)->getLastX(), _enemigos.at(i)->getLastY(), _enemigos.at(i)->getLastZ());//colisiona                                
                            _enemigos.at(i)->setNewRotacion(_enemigos.at(i)->getRX(), _enemigos.at(i)->getRY() - constantes.PI_MEDIOS, _enemigos.at(i)->getRZ());
                            _enemigos.at(i)->setRotation(_enemigos.at(i)->GetRotation() / constantes.DOS);
                        }*/
                    }
                    else
                        _enemigos[i]->RunIA(true);
                }
            }
        }
    }
}

void Jugando::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra toda la pantalla

    _motor->clearDebug2();
    //Para evitar un tran salto en el principio de la ejecucion se actualiza el valor de drawTime
    if (drawTime == 0.0f)
    {
        drawTime = _controladorTiempo->GetTiempo(2);
    }
    lastDrawTime = drawTime;
    drawTime = _controladorTiempo->GetTiempo(2);

    _fisicas->updateJoints(drawTime);

    //Dibujado del personaje
    _jugador->moverseEntidad(1 / _controladorTiempo->GetUpdateTime());
    _jugador->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
    _jugador->UpdateTimeMove(drawTime - lastDrawTime);
    _motor->mostrarJugador(_jugador->getX(),
        _jugador->getY(),
        _jugador->getZ(),
        _jugador->getRX(),
        _jugador->getRY(),
        _jugador->getRZ()
    );
    
    //Dibujado de los _enemigos
    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        _enemigos.at(i)->moverseEntidad(1 / _controladorTiempo->GetUpdateTime());
        _enemigos.at(i)->UpdateTimeMove(drawTime - lastDrawTime);
        _enemigos.at(i)->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
        _enemigos.at(i)->UpdateTimeRotate(drawTime - lastDrawTime);
        _motor->mostrarEnemigos(_enemigos.at(i)->getX(),
            _enemigos.at(i)->getY(),
            _enemigos.at(i)->getZ(),
            _enemigos.at(i)->getRX(),
            _enemigos.at(i)->getRY(),
            _enemigos.at(i)->getRZ(),
            i
        );
        _motor->dibujarObjetoTemporal(_enemigos.at(i)->getFisX()*2,
            _enemigos.at(i)->getFisY()*2,
            _enemigos.at(i)->getFisZ()*2,
            _enemigos.at(i)->getRX(),
            _enemigos.at(i)->getRY(),
            _enemigos.at(i)->getRZ(),3 , 3, 3, 2);
    }

    //Dibujado de las puertas
    for(unsigned int i = 0; i < _interactuables.size(); i++)
    {
        _interactuables.at(i)->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
        _interactuables.at(i)->UpdateTimeRotate(drawTime - lastDrawTime);
        _motor->mostrarObjetos(_interactuables.at(i)->getX(),
            _interactuables.at(i)->getY(),
            _interactuables.at(i)->getZ(),
            _interactuables.at(i)->getRX(),
            _interactuables.at(i)->getRY(),
            _interactuables.at(i)->getRZ(),
            _interactuables.at(i)->GetPosicionObjetos()
        );
    }

    //Dibujado de las puertas version joints
    for(unsigned int i = 0; i < puertas.size(); i++)
    {
        puertas.at(i)->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
        puertas.at(i)->UpdateTimeRotate(drawTime - lastDrawTime);
        _motor->mostrarObjetos(puertas.at(i)->getX(),
            puertas.at(i)->getY(),
            puertas.at(i)->getZ(),
            puertas.at(i)->getRX(),
            puertas.at(i)->getRY(),
            puertas.at(i)->getRZ(),
            puertas.at(i)->GetPosicionObjetos()
        );
    }


    //Dibujado del ataque especial del jugador
    if(_jugador->getTimeAtEsp() > 0.0f)
    {
        _jugador->RenderAtaqueEsp(_controladorTiempo->GetUpdateTime(),
            (drawTime - lastDrawTime));
        ////Ataque especial heavy
        //if(strcmp(_jugador->getArmaEspecial()->getNombre(), "Heavy") == 0)
        //Ataque especial bailaora
        //else if(strcmp(_jugador->getArmaEspecial()->getNombre(), "Bailaora") == 0)
    }

    //Dibujado de ataques
    /*for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        _motor->dibujarObjetoTemporal(
            _enemigos.at(i)->getAtX(),
            _enemigos.at(i)->getAtY(),
            _enemigos.at(i)->getAtZ(),
            _enemigos.at(i)->getRX(),
            _enemigos.at(i)->getRY(),
            _enemigos.at(i)->getRZ(),
            4,
            4,
            4,
            2);
    }*/

    //Dibujado zonas
    for(unsigned int i=0; i < _zonas.size(); i++)
    {
        _motor->dibujarZona(_zonas.at(i)->getX(),
            _zonas.at(i)->getY(),
            _zonas.at(i)->getZ(),
            _zonas.at(i)->getAncho(),
            _zonas.at(i)->getAlto(),
            _zonas.at(i)->getLargo()
        );
    }
    //_motor->clearDebug2(); //Pruebas debug

    _motor->RenderInterfaz(_interfaz->getEstado());

    _motor->RenderEscena();  // Vuelve a pintar
}

void Jugando::Pausar()
{ 
    cout << "Pausando el juego" << endl;
    DesactivarDebug();
}

void Jugando::Reanudar()
{ 
    if (reiniciando) {
        cout << "REINICIAR JUEGO" << endl;

        DesactivarDebug();
        // valores por defecto del jugador
        ValoresPorDefectoJugador();

        cout << "Cambia: "<<_jugador->getX() << endl;

        // Resto de valores del juego
        ValoresPorDefecto();
        PosicionesIniEnemigos();

        reiniciando = false;
    } else {
        cout << "Reanudando el juego" << endl;
    }
}

// Elimina los datos en memoria
void Jugando::Vaciar()
{
    cout << "Vaciando el juego" << endl;
}

void Jugando::Reiniciar()
{
    reiniciando = true;
}






bool Jugando::CargarNivel(int nivel, int tipoJug)
{
    // Codigo de Nivel.cpp
    
    _motor->BorrarScena();//borramos la scena

    //pre limpiamos todo
   // _motor->LimpiarMotorGrafico();
    //LimpiarNivel();
    _fisicas->limpiarFisicas();
    //limpiammos la sala
    /*if(_primeraSala != nullptr)
    {
       _primeraSala->~Sala();
       _primeraSala = nullptr;
    }*/

    //cargamos el nivel
    cargador.CargarNivelXml(nivel, tipoJug); //se llama al constructor vacio
    
    CrearJugador();
    

    //Cargar objetos con el nivel completo
    this->cargarCofres(2); //Cargamos los cofres del nivel

    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Nivel1")->start(); //Reproducir musica juego
    _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente

    //esta ya todo ejecutamos ia y interpolado
    return true;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearJugador()
{
    cout << "Creo el jugador"<<endl;
    _jugador = cargador.GetJugador();
    _jugador->setID(++id);
    ValoresPorDefectoJugador();

    _motor->CargarJugador(_jugador->getX(),_jugador->getY(), _jugador->getZ(),
        _jugador->GetAncho(), _jugador->GetLargo(), _jugador->GetAlto(),
        _jugador->GetModelo(), _jugador->GetTextura());

    _motor->CargarArmaEspecial(_jugador->getX(),_jugador->getY(),
        _jugador->getZ(), _jugador->getRutaArmaEsp(),"");

    //cout << "jugador creado en: "<<x<<", "<<y<<", "<<z<<", "<<endl;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearEnemigo(int accion, int enemigo, int x,int y,int z, int ancho, int largo, int alto,
    const char* ruta_objeto, const char* ruta_textura, Sala* sala)
{
    //accion indicara futuramente que tipo de enemigo sera (herencia)
    switch (enemigo)
    {
        case 0:
        {
            //TO DO: revisar creacion de tipos de enemigos
            //75 = vida
            Pollo* _ene = new Pollo(x,y,z, 75);//aqui va el tipo de enemigo que es hacer ifs y meter una variable nueva de tipo para saber que tipo es
            //ia
            //cargadorIA.cargarBehaviorTreeXml("PolloBT");
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
            _ene->setID(++id);//le damos el id unico en esta partida al enemigo
            _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
            _ene = nullptr;

            //Cargar sonido evento en una instancia con la id del enemigo como nombre
            std::string nameid = std::to_string(id); //pasar id a string
            _motora->LoadEvent("event:/SFX/SFX-Pollo enfadado", nameid);
            _motora->getEvent(nameid)->setPosition(x,y,z);
            _motora->getEvent(nameid)->setVolume(0.4f);
            _motora->getEvent(nameid)->start();
        }
            break;
        default:
            break;
    }
        //fin ia
    _enemigos.back()->SetEnemigo(enemigo);
    _enemigos.back()->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _enemigos.back()->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _enemigos.back()->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _enemigos.back()->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _enemigos.back()->setVelocidadMaxima(1.0f);
    _enemigos.back()->setBarraAtEs(0);
    _enemigos.back()->definirSala(sala);//le pasamos la sala en donde esta
    _enemigos.back()->setAtaque(10);
    _enemigos.back()->setArmaEspecial(100);
    _enemigos.back()->setTimeAtEsp(0.0f);
    _enemigos.back()->setDanyoCritico(50);
    _enemigos.back()->setProAtaCritico(10);
    //_enemigos.back()->genemigos.back()rarSonido(20,5);
    _enemigos.back()->setRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _enemigos.back()->setVectorOrientacion();
    _enemigos.back()->setNewRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _enemigos.back()->setLastRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    
    _motor->CargarEnemigos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    _fisicas->crearCuerpo(accion,0,x/2,y/2,z/2,2,ancho,alto,largo,2);
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,7); //Para ataques
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,8); //Para ataques especiales
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
Sala* Jugando::CrearPlataforma(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto, int centro,
    const char* ruta_objeto, const char* ruta_textura)
{
    Sala* _sala = new Sala(ancho,largo,alto,x,y,z,centro);
    //int*  datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int nId = _motor->CargarPlataformas(rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    _sala->definirID(nId);
    _fisicas->crearCuerpo(accion,rp,x/2,y/2,z/2,2,ancho,alto,largo,6);

    if(!_primeraSala)
    {
       _primeraSala = _sala;
    }

    return _sala;
}

void Jugando::CrearLuz(int x,int y,int z)
{
    _motor->CargarLuces(x,y,z);
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z,
    int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades)
{
    int posicionObjeto;

    //Arma
    if(accion == 2)
    {
        posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* _rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura,x,y,z);
        _rec->setID(_recolectables.size());
        _rec->setPosiciones(x,y,z);
        _rec->SetPosicionArrayObjetos(posicionObjeto);
        _recolectables.push_back(move(_rec));
        _rec = nullptr;
    }else
    //Puertas o interruptores
    if(accion == 3)
    {
        posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Interactuable* _inter = new Interactuable(codigo, nombre, ancho, largo, alto, ruta_objeto, ruta_textura, posicionObjeto,x,y,z);
        _inter->setID(id++);
        _inter->setPosiciones(x,y,z);
        _inter->SetPosicionArrayObjetos(posicionObjeto);
        _inter->setDesplazamientos(despX,despZ);
        _inter->setRotacion(0.0,0.0,0.0);
        _interactuables.push_back(move(_inter));
        _inter = nullptr;
    }else
    //Powerups
    if(accion == 4)
    {
        posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* _rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura,x,y,z);
        _rec->setID(_powerup.size());
        _rec->setPosiciones(x,y,z);
        _rec->SetPosicionArrayObjetos(posicionObjeto);
        _rec->setCantidad(propiedades[0]); //cantidad
        _powerup.push_back(move(_rec));
        _rec = nullptr;
    }else
    //puertas version joints
    if(accion == 5)
    {
        posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Interactuable*  inter = new Interactuable(codigo, nombre, ancho, largo, alto, ruta_objeto, ruta_textura, posicionObjeto,x,y,z);
        inter->setID(id++);
        inter->setPosiciones(x,y,z);
        inter->SetPosicionArrayObjetos(posicionObjeto);
        inter->setDesplazamientos(despX,despZ);
        inter->setRotacion(0.0,0.0,0.0);
        puertas.push_back(inter); 
    }
    else
    {
         posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    }

    _fisicas->crearCuerpo(accion,rp,x/2,y/2,z/2,2,ancho,alto,largo,3);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba
}

//lo utilizamos para crear zonas
void Jugando::CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo)
{
   //Crear zona
   Zona* zon = new Zona(ancho,largo,alto,tipo);

   //ID propia y posicion
   int calcID = _zonas.size();
   zon->setID(calcID);
   zon->setPosiciones(x,y,z);

   //guardarla en el nivel
   // con move, zon se queda vacio
   _zonas.push_back(move(zon));
   zon = nullptr;
}

//Cargar los cofres del nivel
void Jugando::cargarCofres(int num)
{
  long unsigned int num_cofres = num;

  if(!_zonas.empty())
  {
    if(_zonas.size() >= num_cofres)
    {
      //Buscar zonas sin proposito y guardar posicion en vector
      std::vector<int> Zsinprop;
      for(int i = _zonas.size(); i > 0; i--)
      {
        std::string name_tipo(_zonas.at(i-1)->getTipo());
        char* cadena_tipo = new char[sizeof(name_tipo)];
        strcpy(cadena_tipo, name_tipo.c_str());

        if(strcmp(cadena_tipo,"zChest") == 0) //Si es zona de cofre
        {
          if(_zonas.at(i-1)->getProposito() == false) //Y no ha cumplido su proposito
          {
            cout << "entra:" << i-1 << endl;
            Zsinprop.push_back(i-1);
          }
        }
      }

      //Mientra hay cofres sin colocar, colocar en una zona aleatoria
      while(num_cofres > 0)
      {
        srand(time(NULL));
        int numAlt = rand() % Zsinprop.size();
        cout << "colocar en: " << Zsinprop[numAlt] << endl;

        //proposito cumplido
        _zonas[Zsinprop[numAlt]]->setProposito(true);

        //Buscar zona donde colocar
        float newx = _zonas[Zsinprop[numAlt]]->getX();
        float newy = _zonas[Zsinprop[numAlt]]->getY();
        float newz = _zonas[Zsinprop[numAlt]]->getZ();

        //Colocar cofre
        int posicionObjeto = _motor->CargarObjetos(3,0,newx,newy,newz,2,2,2,"assets/models/Cofre/ChestCartoon.obj", "assets/models/Cofre/ChestCartoon.mtl");
        Interactuable* inter = new Interactuable(-1,"Cofre",2,2,2,"assets/models/Cofre/ChestCartoon.obj","assets/models/Cofre/ChestCartoon.mtl", posicionObjeto,newx,newy,newz);
        inter->setID(id++);
        inter->setPosiciones(newx,newy,newz);
        inter->SetPosicionArrayObjetos(posicionObjeto);
        inter->setRotacion(0.0,0.0,0.0);
        _interactuables.push_back(inter);

        //Fisicas del cofre
        _fisicas->crearCuerpo(3,0,newx/2,newy/2,newz/2,2,2,4,2,3);

        //borrar del Array
        Zsinprop.erase(Zsinprop.begin() + numAlt);

        num_cofres--; //un cofre menos
      }
      Zsinprop.resize(0);
    }
    else
    {
      cout << "No hay zonas de cofres suficientes en el nivel" << endl;
    }
  }
}

 void Jugando::CogerObjeto()
{
    Constantes constantes;
    long unsigned int rec_col = _fisicas->collideColectable();
    _jugador->setAnimacion(4);

    //En caso de no ser llaves
    if(_recolectables.at(rec_col)->getCodigo() == 0)
    {
        if(_jugador->getArma() == nullptr)//si no tiene arma equipada
        {
            //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)_recolectables[rec_col];
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),_recolectables[rec_col]->getNombre(),_recolectables[rec_col]->getAncho(),_recolectables[rec_col]->getLargo(),_recolectables[rec_col]->getAlto(),_recolectables[rec_col]->getObjeto(),_recolectables[rec_col]->getTextura());
            _jugador->setArma(nuArma);
            //PROVISIONAL
            _jugador->getArma()->setRotacion(0.0, constantes.PI_RADIAN, 0.0);//!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(_jugador->getX(), _jugador->getY(), _jugador->getZ(), _recolectables[rec_col]->getObjeto(), _recolectables[rec_col]->getTextura());
            //lo cargamos por primera vez en el motor de fisicas
            _fisicas->crearCuerpo(0,0,_jugador->getX()/2,_jugador->getY()/2,_jugador->getZ()/2,2,_recolectables[rec_col]->getAncho(), _recolectables[rec_col]->getLargo(), _recolectables[rec_col]->getAlto(), 6);
            //borramos el recolectable de nivel, _motor grafico y motor fisicas
            _recolectables.erase(_recolectables.begin() + rec_col);
            _motor->EraseColectable(rec_col);
            _fisicas->EraseColectable(rec_col);
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
        else if(_jugador->getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(0, _jugador->getArma()->getAtaque(),_jugador->getArma()->getNombre(),_jugador->getArma()->getAncho(),_jugador->getArma()->getLargo(), _jugador->getArma()->getAlto(),_jugador->getArma()->getObjeto(),_jugador->getArma()->getTextura(),_jugador->getX(),_jugador->getY(), _jugador->getZ());
            nuRec->setPosiciones(_jugador->getX(),_jugador->getY(), _jugador->getZ());
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),_recolectables[rec_col]->getNombre(),_recolectables[rec_col]->getAncho(),_recolectables[rec_col]->getLargo(),_recolectables[rec_col]->getAlto(),_recolectables[rec_col]->getObjeto(),_recolectables[rec_col]->getTextura());
            _motor->EraseArma();
            _jugador->setArma(nuArma);
            
            //PROVISIONAL
            _jugador->getArma()->setRotacion(0.0, constantes.PI_RADIAN, 0.0);
            //!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(_jugador->getX(), _jugador->getY(), _jugador->getZ(), _recolectables[rec_col]->getObjeto(), _recolectables[rec_col]->getTextura());
            
            //lo cargamos en el motor de fisicas
            _fisicas->setFormaArma(_jugador->getX()/2, _jugador->getY()/2, _jugador->getZ()/2, _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(),_jugador->getArma()->getAlto());
            
            //borramos el recolectable anterior de nivel, _motor grafico y motor fisicas
            _recolectables.erase(_recolectables.begin() + rec_col);
            _motor->EraseColectable(rec_col);
            _fisicas->EraseColectable(rec_col);
            
            //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
            _recolectables.push_back(nuRec);
            _fisicas->setFormaRecolectable(_recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
            _motor->CargarRecolectable(_recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
    }
    else if(_recolectables.at(rec_col)->getCodigo() > 0)
    {
        Llave* llave = new Llave(_recolectables.at(rec_col)->getCodigo());
        _jugador->AnnadirLlave(llave);
        
        //borramos el recolectable de nivel, _motor grafico y motor fisicas
        _recolectables.erase(_recolectables.begin() + rec_col);
        _motor->EraseColectable(rec_col);
        _fisicas->EraseColectable(rec_col);
    }
}

void Jugando::DejarObjeto()
{
    if(_jugador->getArma() != nullptr)//si tiene arma equipada
    {
        //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
        Recolectable* nuRec = new Recolectable(0, _jugador->getArma()->getAtaque(),_jugador->getArma()->getNombre(),_jugador->getArma()->getAncho(),_jugador->getArma()->getLargo(), _jugador->getArma()->getAlto(),_jugador->getArma()->getObjeto(),_jugador->getArma()->getTextura(),_jugador->getX(),_jugador->getY(), _jugador->getZ());
        nuRec->setPosiciones(_jugador->getX(),_jugador->getY(), _jugador->getZ());
        _motor->EraseArma();
        _fisicas->EraseArma();
        _jugador->setArma(NULL);

        //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
        _recolectables.push_back(nuRec);
        _fisicas->setFormaRecolectable(_recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
        _motor->CargarRecolectable(_recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
    }
}

/*********** AccionarMecanismo ***********
*  Funcion que, en funcion del valor codigo
*  del interactuable al que apunte int_col,
*  si es -1 abre un cofre, si es 0 abre una puerta
*  sin llave y si es mayor que 0 abrira la puerta
*  indicada si el jugador tiene su llave.
*       Entradas:
*                int_col: indicador del elemento en el vector de interactuables
*       Salidas:
*/
void Jugando::AccionarMecanismo(int int_col)
{
    unsigned int i = 0;
    bool coincide = false;
    //Si es una puerta sin llave o palanca asociada
    if(_interactuables.at(int_col)->getCodigo() == 0)
    {
        //Se acciona o desacciona el mecanismo segun su estado actual
        bool abrir = _interactuables.at(int_col)->accionar();
        unsigned int posicion = _fisicas->GetRelacionInteractuablesObstaculos(int_col);
        if(abrir)
        {
            //Se abre/acciona la puerta / el mecanismo
            //sonido
            //_motora->getEvent("AbrirPuerta")->setVolume(0.8f);
            _motora->getEvent("AbrirPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
            _motora->getEvent("AbrirPuerta")->start();
            _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + 135.0, _interactuables.at(int_col)->getRZ());
            _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() +135.0, _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos() , posicion);
            cout<<"Abre la puerta"<<endl;
        }
        else
        {
            //Se cierra/desacciona la puerta / el mecanismo
            _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
            _motora->getEvent("CerrarPuerta")->start();
            _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() - 135.0, _interactuables.at(int_col)->getRZ());
            _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), - _interactuables.at(int_col)->getRY(), _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos(), posicion);
            cout<<"Cierra la puerta"<<endl;
        }
    }
    else if(_interactuables.at(int_col)->getCodigo() == -1)
    {
       //Cofre no abierto
        if(!_interactuables.at(int_col)->getAccionado())
        {
          //Se abre el cofre (Animacion)
          _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY(), _interactuables.at(int_col)->getRZ() + 80.0);
          cout << "Abres el cofre" << endl;
          _interactuables.at(int_col)->accionar();

          //Crear objeto aleatorio
          this->crearObjetoCofre(_interactuables.at(int_col));
        }
        else
        {
          cout << "Cofre ya abierto" << endl;
        }
    }
    else if(std::strcmp(_interactuables.at(int_col)->getNombre(), PALANCA) == 0)
    {
        i = 0;
        coincide = false;
        //PRUEBAS CON PALANCAS
        while(i < _interactuables.size() && !coincide)
        {
            if(_interactuables.at(i)->getCodigo() == _interactuables.at(int_col)->getCodigo())
            {
                coincide = true;
                i--;
            }
            i++;
        }
        if(coincide)
        {
            cout<<"La palanca acciona una puerta"<<endl;
            //Se acciona o desacciona el mecanismo segun su estado actual
            bool activar = _interactuables.at(int_col)->accionar();
            bool abrir = _interactuables.at(i)->accionar();
            unsigned int posicion = _fisicas->GetRelacionInteractuablesObstaculos(i);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                _motora->getEvent("AbrirPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("AbrirPuerta")->start();
                _interactuables.at(i)->setNewRotacion(_interactuables.at(i)->getRX(), _interactuables.at(i)->getRY() + 135.0, _interactuables.at(i)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(i)->getX(), _interactuables.at(i)->getY(), _interactuables.at(i)->getZ(), _interactuables.at(i)->getRX() + 100.0, _interactuables.at(i)->getRY(), _interactuables.at(i)->getRZ(), _interactuables.at(i)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _interactuables.at(i)->setNewRotacion(_interactuables.at(i)->getRX(), _interactuables.at(i)->getRY() - 135.0, _interactuables.at(i)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(i)->getX(), _interactuables.at(i)->getY(), _interactuables.at(i)->getZ(), _interactuables.at(i)->getRX(), - _interactuables.at(i)->getRY(), _interactuables.at(i)->getRZ(), _interactuables.at(i)->GetDesplazamientos(), posicion);
                cout<<"Cierra la puerta"<<endl;
            }

            if(activar)
            {
                //Se abre/acciona la puerta / el mecanismo
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY(), _interactuables.at(int_col)->getRZ()+50);
                cout<<"Acciona la palanca"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY(), _interactuables.at(int_col)->getRZ()-50);
                cout<<"Desacciona la palanca"<<endl;
            }
        }
    }
    else
    {
        i = 0;
        coincide = false;
        //PRUEBAS CON LLAVES
        while(i < _jugador->GetLlaves().size() && !coincide)
        {
            if(_jugador->GetLlaves().at(i)->GetCodigoPuerta() == _interactuables.at(int_col)->getCodigo())
            {
                coincide = true;
            }
            i++;
        }
        if(coincide)
        {
            cout<<"Tiene la llave para abrir la puerta"<<endl;
            //Se acciona o desacciona el mecanismo segun su estado actual
            bool abrir = _interactuables.at(int_col)->accionar();
            unsigned int posicion = _fisicas->GetRelacionInteractuablesObstaculos(int_col);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                _motora->getEvent("AbrirCerradura")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("AbrirCerradura")->start();
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + 135.0, _interactuables.at(int_col)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() +135.0, _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() - 135.0, _interactuables.at(int_col)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), - _interactuables.at(int_col)->getRY(), _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos(), posicion);
                cout<<"Cierra la puerta"<<endl;
            }
        }
    }
}

void Jugando::crearObjetoCofre(Interactuable* _newObjeto)
{
  //Aleaotrio
  srand(time(NULL));
  int ntipos = 3;
  int tipobj = 1 + rand() % ntipos; //aleatorio entre 1 y n tipos de objetos

  int accion;
  int x = _newObjeto->getX() + 5;
  int y = _newObjeto->getY();
  int z = _newObjeto->getZ();
  int ancho = 2 ,largo = 2,alto = 2;
  int codigo,ataque;
  const char* nombre,* modelo,* textura;
  int*  propiedades = new int [6];

  if(tipobj == 1)
  {
    //crear guitarra
    accion = 2;
    codigo = 0; //0:arma
    ataque = 25;
    nombre = "guitarra";
    modelo = "assets/models/Arma.obj";
    textura = "assets/texture/platform1.jpg";
    cout << "Hay una guitarra!" << endl;
  }
  else if(tipobj == 2)
  {
    //crear arpa
    accion = 2;
    codigo = 0; //0:arma
    ataque = 10;
    nombre = "arpa";
    modelo = "assets/models/objeto2.obj";
    textura = "assets/texture/platform1.png";
    cout << "Hay una arpa!" << endl;
  }
  else if(tipobj == 3)
  {
    //Oro
    accion = 4;
    codigo = -2;
    ataque = 2;
    nombre = "gold_up";
    modelo = "assets/models/gold.obj";
    textura = "assets/models/gold.mtl";
    //Cantidad de oro entre 20 y 30
    srand(time(NULL));
    int orocant = 20 + rand() % (31 - 20); //variable = limite_inf + rand() % (limite_sup + 1 - limite_inf)
    cout << "Hay " << orocant << " de Oro!" << endl;
    propiedades[0] = orocant; //para pasarlo a crear objeto
  }
   this->CrearObjeto(codigo,accion,nombre,ataque,0,x,y,z,0,0,ancho,largo,alto,modelo,textura,propiedades);
}

void Jugando::activarPowerUp()
{
    int int_cpw = _fisicas->collideColectablePowerup();

    if(int_cpw >= 0 && int_cpw != int_cpw_aux)
    {
        bool locoges = false; //Comprobar si lo puedes coger

        //Efecto del power up (ataque) 0 = vida, 1 = energia, 2 = monedas, 3 = danyo, 4 = defensa
        if(_powerup.at(int_cpw)->getAtaque() == 0 && _jugador->getVida() < 100)
        {
            cout << "PowerUP! Curado 20 de vida. TOTAL:" << _jugador->getVida() << endl;
            _jugador->ModificarVida(20);
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->getAtaque() == 1 && _jugador->getBarraAtEs() < 100)
        {
            cout << "PowerUP! 50 de energia. TOTAL:" << _jugador->getBarraAtEs() << endl;
            _jugador->ModificarBarraAtEs(50);
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->getAtaque() == 2)
        {
            cout << "Recoges " << _powerup.at(int_cpw)->getCantidad() << " de oro" << endl;
            _jugador->ModificarDinero(_powerup.at(int_cpw)->getCantidad());
            locoges = true;
        }

        if(locoges == true)
        {
            //Borrar objeto en todos los sitios
            _powerup.erase(_powerup.begin() + int_cpw);
            _motor->ErasePowerUP(int_cpw);
            _fisicas->EraseColectablePowerup(int_cpw);
        }
    }
    int_cpw_aux = int_cpw;
}

void Jugando::updateAt(int* danyo)
{
    float tiempoActual = 0.0f;
    float tiempoAtaque = 0.0f;
    if((_motor->EstaPulsado(KEY_ESPACIO) || _motor->EstaPulsado(LMOUSE_DOWN)) && _jugador->getTimeAt() <= 0.0f)
    {
        *danyo = _jugador->Atacar(0);
        _motor->ResetKey(KEY_ESPACIO);
        _motor->ResetEvento(LMOUSE_DOWN);
        //atacktime = 1.5f;
        _jugador->setTimeAt(1.5f);
        _jugador->setLastTimeAt(_controladorTiempo->GetTiempo(2));
    } else {
        if(_jugador->getTimeAt() > 0.0f)
        {
            tiempoActual = _controladorTiempo->GetTiempo(2);
            tiempoAtaque = _jugador->getTimeAt();
            tiempoAtaque -= (tiempoActual - _jugador->getLastTimeAt());
            _jugador->setLastTimeAt(tiempoActual);
            _jugador->setTimeAt(tiempoAtaque);
        }
        if(atacktime > 0.5f)
        {
            if(atacktime > 0.0f)
            {
                atacktime--;
            }
            if(atacktime > 500.0f)
            {
                //Colorear rojo
                _motor->colorearJugador(255,255,0,0);
            }else if(atacktime > 0.0f){
                //Colorear gris
                _motor->colorearJugador(255,150,150,150);
            }
        }

        //clear
        if(_jugador->getTimeAt() <= 0.0f){
           // _motor->clearDebug2();
        }
    }
}

void Jugando::updateAtEsp()
{
    float tiempoActual = 0.0f;
    float tiempoAtaqueEsp = 0.0f;
    //Compureba si se realiza el ataque especial o si la animacion esta a medias
    if((_motor->EstaPulsado(RMOUSE_DOWN)||_motor->EstaPulsado(KEY_Q)) && _jugador->getTimeAtEsp() <= 0.0)
    {
        danyo = _jugador->AtacarEspecial();
        _motor->ResetKey(KEY_Q);
        _motor->ResetEvento(RMOUSE_DOWN);
        _motor->colorearJugador(255, 55, 0, 255);
        if(danyo > 0)
        {
            _jugador->setTimeAtEsp(1.5f);
            _jugador->setLastTimeAtEsp(_controladorTiempo->GetTiempo(2));
        }
    }
    else
    {
        if(danyo > 0)
        {
            danyo = 0;
        }
        if(_jugador->getTimeAtEsp() > 0.f)
        {
            tiempoActual = _controladorTiempo->GetTiempo(2);
            tiempoAtaqueEsp = _jugador->getTimeAtEsp();
            tiempoAtaqueEsp -= (tiempoActual - _jugador->getLastTimeAtEsp());
            _jugador->setLastTimeAtEsp(tiempoActual);
            _jugador->setTimeAtEsp(tiempoAtaqueEsp);
            danyo = _jugador->AtacarEspecial();
        }
        /*if(_jugador->getTimeAtEsp() > 0.f && ((int) (_jugador->getTimeAtEsp()*  100) % 10 >= 4) && ((int) (_jugador->getTimeAtEsp()*  100) % 10 <= 4))
        {
            danyo = _jugador->AtacarEspecial();
        }*/
        if(_jugador->getTimeAtEsp() == 1.0f)
        {
            _motor->colorearEnemigo(255,255,255,255,0);
        }
        if(_jugador->getTimeAtEsp() <= 0.5f && _motor->getArmaEspecial()) //Zona de pruebas
        {
            _motor->borrarArmaEspecial();
            _motor->colorearJugador(255, 150, 150, 150);
        }
    }
}

void Jugando::updateRecorridoPathfinding(Enemigo* _enem)
{
    //Si enem no es nulo se anade a la cola de _enemigos _auxiliadores
    if(_enem != nullptr && _enem != _enemPideAyuda )
    {
        _auxiliadores.push_back(_enem);
        contadorEnem--;
    }
    else if(contadorEnem > 0 && _enem == _enemPideAyuda)
    {
        this->setEnemigoPideAyuda(nullptr);
        _destinoPathFinding = nullptr;
        contadorEnem = 0;
    }
    //Si no hay sala de destino guardada, se guarda en este momento
    else if(_destinoPathFinding == nullptr)
    {
        _destinoPathFinding = _enemPideAyuda->getSala();
    }
    //Ejecucion del pathfinding si hay una sala de destino guardada
    if(_destinoPathFinding != nullptr)
    {
        Pathfinder* path = Pathfinder::getInstance();
        int tipoCentro;

        //Se inicia el recorrido hacia la primera sala del enemigo que pide ayuda.
        if(recorrido.empty() && !_auxiliadores.empty() && !path->encontrarCamino(_auxiliadores.front()->getSala(), _destinoPathFinding).empty())
        {
            recorrido = path->encontrarCamino(_auxiliadores.front()->getSala(), _destinoPathFinding);
            _auxiliadores.erase(_auxiliadores.begin());
        }
        //Desplazamiento del enemigo hacia su destino
        if(!recorrido.empty())
        {
            //Se comprueban las coordenadas del enemigo y si ha llegado a la siguiente
            //sala del camino a la que debe ir o no. Se tienen en cuenta los tipos de centros
            //para realizar las comprobaciones de coordenadas adecuadas con el ancho y alto de las salas
            if(_auxiliadores.front()!= nullptr && _auxiliadores.front()->getSala() != recorrido.front().nodo)
            {
                bool cambia = false, moveDer = false, moveIzq = false, moveArb = false, moveAbj = false;
                tipoCentro = recorrido.front().nodo->getType();
                //Centro arriba a la izquierda
                if(tipoCentro == 4)
                {
                    if(_auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] && _auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(_auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(_auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }
                    if(cambia && (_auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] && _auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        _auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(_auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(_auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la izquierda
                else if(tipoCentro == 3)
                {
                    if(_auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] && _auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(_auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(_auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }

                    if(cambia && (_auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] && _auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] )))
                    {
                        _auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(_auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(_auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro arriba a la derecha
                else if(tipoCentro == 2)
                {
                    if(_auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] && _auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(_auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(_auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (_auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] && _auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        _auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(_auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(_auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la derecha
                else if(tipoCentro == 1)
                {
                    if(_auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] && _auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(_auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(_auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (_auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] && _auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] )))
                    {
                        _auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(_auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(_auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro en el centro
                else if(tipoCentro == 0)
                {
                    if(_auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2) && _auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        cambia = true;
                    }
                    else if(_auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveIzq = true;
                    }
                    else if(_auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveDer = true;
                    }

                    if(cambia && (_auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2) && _auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2)))
                    {
                        _auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(_auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveArb = true;
                    }
                    else if(_auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveAbj = true;
                    }
                }
                if(moveAbj)
                {
                    if(moveDer)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidadMaxima(), 0.0, _auxiliadores.front()->getVelocidadMaxima());
                        cout<<"Posicion del enemigo: x="<<_auxiliadores.front()->getNewX()<<" z=" << _auxiliadores.front()->getNewY();
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidadMaxima()), 0.0, _auxiliadores.front()->getVelocidadMaxima());
                    }
                    else
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, _auxiliadores.front()->getVelocidadMaxima());
                    }
                }
                else if(moveArb)
                {
                    if(moveDer)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidadMaxima(), 0.0, -(_auxiliadores.front()->getVelocidadMaxima()));
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidadMaxima()), 0.0, -(_auxiliadores.front()->getVelocidadMaxima()));
                    }
                    else
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidadMaxima());
                        _auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, -(_auxiliadores.front()->getVelocidadMaxima()));
                    }
                }
                else
                {
                    if(moveDer)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidadMaxima(), 0.0, 0.0);
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidadMaxima(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidadMaxima()), 0.0, 0.0);
                    }
                }
            }
            else
            {
                cout<<"nodo actual donde puede que se atasque: "<<_auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                recorrido.erase(recorrido.begin());
                if(recorrido.empty() && _auxiliadores.empty())
                {
                    _destinoPathFinding = nullptr;
                    this->setEnemigoPideAyuda(nullptr);
                    contadorEnem = 0;
                }
            }
        }
    }
    contadorEnem++;
}

void Jugando::EraseEnemigo(std::size_t i)
{
    //Eliminar sonido
    std::string nameid = std::to_string(_enemigos[i]->getID()); //pasar id a string
    _motora->getEvent(nameid)->stop();

    //elimniar el objeto en memoria(la onda)
    _enemigos[i]->~Enemigo();//el destructor de enemigo
    _enemigos[i]=nullptr;
    _enemigos.erase(_enemigos.begin() + i);//begin le suma las posiciones
    //cout <<"que eres?" << i <<endl;
}

void Jugando::setEnemigoPideAyuda(Enemigo* ene)
{
    _enemPideAyuda = ene;
}

Enemigo* Jugando::getEnemigoPideAyuda()
{
    return _enemPideAyuda;
}

std::vector<Enemigo*>  Jugando::getEnemigos()
{
    return _enemigos;
}

// Por ahora solo se llama desde Pollo.cpp
Jugador* Jugando::GetJugador()
{
    return _jugador;
}