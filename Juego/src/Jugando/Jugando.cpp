#include "Jugando.hpp"
#include "../Juego.hpp"
#include "../ConstantesComunes.hpp"

#define PALANCA "palanca"

Jugando::Jugando()
{
}

Jugando::~Jugando()
{
    // Punteros sin new
    _enemPideAyuda = nullptr;
    _destinoPathFinding = nullptr;
    _jugador = nullptr;
    _boss = nullptr;

    // Punteros a clases singleton
    _controladorTiempo = nullptr;
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;
    _motor = nullptr;
    _interfaz = nullptr;

    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        _enemigos.at(i) = nullptr;
    }
    _enemigos.clear();

    tam = _zonas.size();
    for(short i=0; i < tam; i++)
    {
        _zonas.at(i) = nullptr;
    }
    _zonas.clear();

    tam = _interactuables.size();
    for(short i=0; i < tam; i++)
    {
        _interactuables.at(i) = nullptr;
    }
    _interactuables.clear();

    tam = _recolectables.size();
    for(short i=0; i < tam; i++)
    {
        _recolectables.at(i) = nullptr;
    }
    _recolectables.clear();

    tam = _powerup.size();
    for(short i=0; i < tam; i++)
    {
        _powerup.at(i) = nullptr;
    }
    _powerup.clear();

    tam = _waypoints.size();
    for(short i=0; i < tam; i++)
    {
        _waypoints.at(i) = nullptr;
    }
    _waypoints.clear();

    // Liberar memoria
    tam = _auxiliadores.size();
    for(short i=0; i < tam; i++)
    {
        delete _auxiliadores.at(i);
    }
    _auxiliadores.clear();
}

void Jugando::Iniciar()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _fisicas = MotorFisicas::getInstance();
    _sense = SenseEventos::getInstance();
    _controladorTiempo = Times::GetInstance();
    _interfaz = InterfazJugador::getInstance();

    _motor->CargarInterfaz();
    
    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    CargarNivel(6, 1); //(level, player) 1 = heavy / 2 = bailaora
    
    //TO DO: hacerle un reserve:
    //_auxiliadores.reserve(xx);
    //recorrido.reserve(xx);

    reiniciando = false;
    
    ValoresPorDefecto();

    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
}

void Jugando::ValoresPorDefecto()
{
    //id = 0;
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
    enSalaBoss = false;

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
    _jugador->setPosicionesAtaque(xIni, yIni, zIni);
    _jugador->setNewPosiciones(xIni, yIni, zIni);
    _jugador->initPosicionesFisicas(xIni/2, yIni/2, zIni/2);
    //TO DO: revisar que lo haga bien
    //_jugador->setRotacion(0,180,0);
    //_jugador->setNewRotacion(0,180,0);
}

void Jugando::ValoresPorDefectoBoss()
{
    float xIni = _boss->getIniX();
    float yIni = _boss->getIniY();
    float zIni = _boss->getIniZ();

    _boss->setVida(_boss->getVidaIni());
    _boss->setPosiciones(xIni, yIni, zIni);
    _boss->setPosicionesAtaque(xIni, yIni, zIni);
    _boss->setNewPosiciones(xIni, yIni, zIni);
    _boss->initPosicionesFisicas(xIni/2, yIni/2, zIni/2);
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

     //para modo camara
    if(_motor->EstaPulsado(KEY_1))
    {
        _motor->cambiarCamara();
        _fisicas->cambiarCamara();
        _jugador->cambiarCamara();
        _motor->ResetKey(KEY_1);
    }
    
    /* *********** Teclas para probar cosas *************** */
    // Camara libre
    /*if (_motor->EstaPulsado(KEY_H))
    {
        _motor->ResetKey(KEY_H);
        camLibre = !camLibre;

        if (camLibre)
            _motor->IniCamLibre(_jugador->getX(), 
                _jugador->getY(), _jugador->getZ());
    }*/

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

    // Debug para probar cofres
    if(_motor->EstaPulsado(KEY_C))
    {
        unsigned short desplaza = 10;
        _jugador->setPosiciones(posCofre[0]+desplaza, posCofre[1], posCofre[2]);
        _jugador->setNewPosiciones(posCofre[0]+desplaza, posCofre[1], posCofre[2]);
        _jugador->initPosicionesFisicas((posCofre[0]+desplaza)/2, posCofre[1]/2, posCofre[2]/2);
        _motor->ResetKey(KEY_C);
    }

    if(_motor->EstaPulsado(KEY_B))
    {
        unsigned short desplaza = 10;
        _jugador->setPosiciones(_boss->getIniX()+desplaza, _boss->getIniY(), _boss->getIniZ());
        _jugador->setNewPosiciones(_boss->getIniX()+desplaza, _boss->getIniY(), _boss->getIniZ());
        _jugador->initPosicionesFisicas((_boss->getIniX()+desplaza)/2, _boss->getIniY()/2, _boss->getIniZ()/2);
        enSalaBoss = true;
        _motor->ResetKey(KEY_B);
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
    
        
    // ********** se actualiza posiciones e interpolado **********
    //animacion
    _motor->cambiarAnimacionJugador(_jugador->getAnimacion());

    if(_jugador->getArma() != nullptr)
    {
        //METERLE LA FUNCION AL JUGADOR
        float posArmaX = 5*  sin(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getX();
        float posArmaZ = 5*  cos(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getZ();//iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
        _jugador->getArma()->setPosiciones(posArmaX, _jugador->getY()+3, posArmaZ);
        //!METERLE LA FUNCION AL JUGADOR
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
    
    if (enSalaBoss) {
        //colisiones con todos los objetos y el boss
        jugadorInmovil = _jugador->ColisionEntornoBoss();
    } else {
        //colisiones con todos los objetos y enemigos que no se traspasan
        jugadorInmovil = _jugador->ColisionEntornoEne();
    }
    
    // Actualizar movimiento del jugador
    _jugador->movimiento(jugadorInmovil,
        _motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W)
    );

    _fisicas->updateJugador(_jugador->getX(),
        _jugador->getY(),
        _jugador->getZ()
    );

    //Posicion de escucha
    _motora->setListenerPosition(_jugador->getX(),_jugador->getY(),_jugador->getZ());
    
    //Actualizar ataque especial
    this->updateAtEsp();
    this->updateAt(&danyo2);
    
    if (!enSalaBoss)
    {
        for(unsigned int i = 0; i < _enemigos.size(); i++)
        {
            _fisicas->updateEnemigos(_enemigos.at(i)->getFisX(),
                _enemigos.at(i)->getFisY(),
                _enemigos.at(i)->getFisZ(),
                i
            );
        }

        /*if(_enemPideAyuda != nullptr)   //Solo llama desde aqui a pathfinding si hay un enemigo pidiendo ayuda y enemigos buscandole.
        {
            this->updateRecorridoPathfinding(nullptr);
        }*/
    
        //Si se realiza el ataque se comprueban las colisiones
        if(_jugador->getTimeAtEsp() > 0.0)
        {
            _jugador->AtacarEspecialUpdate(&danyo, _enemigos);
        }
        else if(_jugador->getTimeAt() > 0.0)
        {
            _jugador->AtacarUpdate(danyo2, _enemigos);
        }

        //actualizamos los enemigos
        if(_enemigos.size() > 0)//posiciones interpolacion
        {
            //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;
            for(short i=0;(unsigned)i<_enemigos.size();i++)
            {
                if(_enemigos[i] != nullptr)
                {
                    // Comprobamos si alguno pide ayuda para el pathfinding
                    if (_enemigos[i]->GetPedirAyuda())
                    {
                        _enemPideAyuda = _enemigos[i];
                    }
                    // Si alguno pide ayuda, se mira a ver si este contesta
                    else if(_enemPideAyuda != nullptr) 
                    {
                        if (_enemigos[i]->GetContestar())
                            updateRecorridoPathfinding(_enemigos[i]);
                    }
                    
                    // TO DO: optimizar
                    if (_enemPideAyuda) {
                        _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonas, true);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                    } else {
                        _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonas, false);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                    }
                    //Este bloque se da si el enemigo esta en el proceso de merodear
                    if(_enemigos[i]->getTimeMerodear() > 0.0f)
                    {
                        if(_enemigos[i]->getTimeMerodear() == 1.5f)
                        {
                            //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                            _enemigos[i]->setLastTimeMerodear(_controladorTiempo->GetTiempo(2));
                        }
                        float tiempoActual = 0.0f, tiempoMerodear = 0.0f;
                        tiempoActual = _controladorTiempo->GetTiempo(2);
                        tiempoMerodear = _enemigos[i]->getTimeMerodear();
                        tiempoMerodear -= (tiempoActual - _enemigos[i]->getLastTimeMerodear());
                        if(tiempoActual > _enemigos[i]->getLastTimeMerodear())
                        {
                            //Si no es la primera vez que entra al bucle de merodear, tiempoActual debe ser mayor que lastTimeMerodear
                            //por lo que guardamos en lastTimeMerodear a tiempoActual
                            _enemigos[i]->setLastTimeMerodear(tiempoActual);
                        }
                        _enemigos[i]->setTimeMerodear(tiempoMerodear);
                    }
                    //FUNCIONA REGULAR
                    if((_fisicas->enemyCollideObstacle(i) || !_fisicas->enemyCollidePlatform(i)) && (_enemigos[i]->GetModo() != 1 || _enemigos[i]->GetModo() != 3))
                    {
                        //colisiona
                        struct DatosDesplazamiento
                        {   
                            float x = 0.0f;
                            float y = 0.0f;
                            float z = 0.0f;
                        }
                        velocidad, posicionesPasadas;

                        velocidad.x = (_enemigos[i]->getNewX() - _enemigos[i]->getX());
                        velocidad.y = (_enemigos[i]->getNewY() - _enemigos[i]->getY());
                        velocidad.z = (_enemigos[i]->getNewZ() - _enemigos[i]->getZ());

                        _enemigos[i]->setPosicionesFisicas(-velocidad.x, 0.0f, -velocidad.z);//colisiona
                        //enemigos.at(i)->setPosiciones(_enemigos[i]->getX() - velocidad.x, _enemigos[i]->getLasY() - velocidad.y, _enemigos[i]->getLastZ() - velocidad.z);//colisiona         
                        _enemigos[i]->setNewPosiciones(_enemigos[i]->getX(), _enemigos[i]->getY(), _enemigos[i]->getZ());//colisiona                                
                        if(_enemigos[i]->GetRotation() != 0.0f)
                        {
                            _enemigos[i]->setNewRotacion(_enemigos[i]->getRX(), _enemigos[i]->getRY() - constantes.PI_RADIAN, _enemigos[i]->getRZ());
                            _enemigos[i]->setVectorOrientacion(); 
                            _enemigos[i]->setRotation(0.0f);
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
    else // Actualiza el BOSS
    {
        _fisicas->updateBoss(_boss->getFisX(), _boss->getFisY(),
            _boss->getFisZ()
        );
        
        //Si se realiza el ataque se comprueban las colisiones
        if(_jugador->getTimeAtEsp() > 0.0)
        {
            _jugador->AtacarEspecialUpdate(&danyo, _boss);
        }
        else if(_jugador->getTimeAt() > 0.0)
        {
            _jugador->AtacarUpdate(danyo2, _boss);
        }

        //actualizamos el boss, posiciones interpolacion
        //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;
        if(_boss != nullptr)
        {
            _boss->UpdateBehavior(0, (int*)_jugador, _zonas, false); //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
            
            //Este bloque se da si el boss esta en el proceso de merodear
            if(_boss->getTimeMerodear() > 0.0f)
            {
                if(_boss->getTimeMerodear() == 1.5f)
                {
                    //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                    _boss->setLastTimeMerodear(_controladorTiempo->GetTiempo(2));
                }
                float tiempoActual = 0.0f, tiempoMerodear = 0.0f;
                tiempoActual = _controladorTiempo->GetTiempo(2);
                tiempoMerodear = _boss->getTimeMerodear();
                tiempoMerodear -= (tiempoActual - _boss->getLastTimeMerodear());
                if(tiempoActual > _boss->getLastTimeMerodear())
                {
                    //Si no es la primera vez que entra al bucle de merodear, tiempoActual debe ser mayor que lastTimeMerodear
                    //por lo que guardamos en lastTimeMerodear a tiempoActual
                    _boss->setLastTimeMerodear(tiempoActual);
                }
                _boss->setTimeMerodear(tiempoMerodear);
            }
        }
    }
}

/**************** updateIA ***************
 * Funcion en la que se actualiza la IA y todos
 * aquellos eventos que deben ocurrir 4 veces por
 * segundo
 *      
 *      Entradas:
 *      
 *      Salidas:
*/
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
    
    //Aquí el jugador genera sonidos al caminar
    if(!_jugador->EstaMuerto() && (!jugadorInmovil && (_motor->EstaPulsado(KEY_A)
     || _motor->EstaPulsado(KEY_S) || _motor->EstaPulsado(KEY_D) || _motor->EstaPulsado(KEY_W))))
    {
        _jugador->generarSonido(constantes.CINCO * constantes.SEIS, constantes.DOS, constantes.UNO);
    }

    if (!enSalaBoss)
    {
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

                    if (_enemigos[i]->GetPedirAyuda()) {
                        enemDejarDePedirAyuda();
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
                        if(_enemigos[i] != nullptr)
                        {
                            _enemigos[i]->UpdateIA();    //Ejecuta la llamada al arbol de comportamiento para realizar la siguiente accion
                        }
                    }
                }
            }
        }
    }
    else
    {
        //En esta parte muere el BOSS
        if (!_boss->estasMuerto())
        {
            _boss->UpdateIA();
        }
        else
        {
            //TO DO: borrar fisicas y cosas
            Juego::GetInstance()->estado.CambioEstadoGanar();
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

    float resta = drawTime - lastDrawTime;
    float updateTime = _controladorTiempo->GetUpdateTime();

    //Dibujado de las puertas, las palancas, los objetos y los cofres
    for(unsigned short i = 0; i < _interactuables.size(); i++)
    {
        _interactuables.at(i)->Render(updateTime, resta);
    }
    
    //Dibujado del personaje
    _jugador->Render(updateTime, resta);
    
    if (!enSalaBoss)
    {
        //Dibujado de los enemigos
        for(unsigned short i = 0; i < _enemigos.size(); i++)
        {
            _enemigos.at(i)->Render(i, updateTime, resta);
        }

        //Dibujado de ataques enemigos
        for(unsigned int i = 0; i < _enemigos.size(); i++)
        {
            _enemigos.at(i)->RenderAtaque();
        }
    }
    else // Dibujado Boss
    {
        _boss->Render(-1, updateTime, resta);

        //Dibujado de ataque boss
        _boss->RenderAtaque();
    }

    //Dibujado del ataque especial del jugador
    if(_jugador->getTimeAtEsp() > 0.0f)
    {
        _jugador->RenderAtaqueEsp(updateTime, resta);
    }

    //Dibujado zonas
    for(unsigned int i=0; i < _zonas.size(); i++)
    {
        _zonas.at(i)->Render();
    }
    //_motor->clearDebug2(); //Pruebas debug

    _motor->RenderInterfaz(_interfaz->getEstado());

    _motor->RenderEscena();  // Vuelve a pintar
}

void Jugando::Pausar()
{ 
    DesactivarDebug();
}

void Jugando::Reanudar()
{ 
    if (reiniciando) {

        DesactivarDebug();
        // valores por defecto del jugador
        ValoresPorDefectoJugador();
        //ValoresPorDefectoBoss();


        // Resto de valores del juego
        ValoresPorDefecto();
        PosicionesIniEnemigos();

        reiniciando = false;
    }
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

    //cargamos el nivel
    cargador.CargarNivelXml(nivel, tipoJug); //se llama al constructor vacio
    
    CrearJugador();
    _recolectables = cargador.GetRecolectables();
    _interactuables = cargador.GetInteractuables();
    _powerup = cargador.GetPowerup();
    _zonas = cargador.GetZonas();
    _enemigos = cargador.GetEnemigos();
    _boss = cargador.GetBoss();
    _waypoints = cargador.GetWaypoints();
    ConectarWaypoints();

    //Cargar objetos con el nivel completo
    this->cargarCofres(16); //Cargamos los cofres del nivel

    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Nivel1")->start(); //Reproducir musica juego
    _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente

    //esta ya todo ejecutamos ia y interpolado
    return true;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearJugador()
{
    _jugador = cargador.GetJugador();
    ValoresPorDefectoJugador();

    _motor->CargarJugador(_jugador->getX(),_jugador->getY(), _jugador->getZ(),
        _jugador->GetAncho(), _jugador->GetLargo(), _jugador->GetAlto(),
        _jugador->GetModelo());

    _motor->CargarArmaEspecial(_jugador->getX(),_jugador->getY(),
        _jugador->getZ(), _jugador->getRutaArmaEsp(),"");

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
        int* id = cargador.GetID();
        _inter->setID(*(++id));
        id = nullptr;
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
    }
    else
    {
         posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    }

    _fisicas->crearCuerpo(accion,rp,x/2,y/2,z/2,2,ancho,alto,largo,3);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba
}

//Cargar los cofres del nivel
void Jugando::cargarCofres(int num)
{
  Constantes constantes;
    long unsigned int num_cofres = num;
    unsigned short  totalCofresPonible = 0;
    vector<short> zonasDisponibles;
    zonasDisponibles.reserve(num);

    //Se comprueba si hay zonas de cofres disponibles
    if(!_zonas.empty())
    {
        //se contabilizan las zonas donde se pueden colocar cofres
        for(unsigned short i = 0; i < _zonas.size(); i++)
        {
            //Se comprueba que es una zona de cofres y que le caben mas cofres
            if((_zonas.at(i)->getTipo() == constantes.CERO) && (!_zonas.at(i)->getProposito()))
            {
                totalCofresPonible += (_zonas[i]->getTotalElementos() - _zonas[i]->getElementosActuales());
                zonasDisponibles.push_back(i);
            }
        }
        //En caso de haber mas o el mismo numero de huecos para cofres que cofres se accede
        if(totalCofresPonible >= num_cofres)
        {
            float newx = 0;
            float newy = 0;
            float newz = 0;

            //Mientra hay cofres sin colocar, colocar en una zona aleatoria
            while(num_cofres > 0)
            {
                srand(time(NULL));
                int numAlt = rand() % zonasDisponibles.size();
                cout << "colocar en: " << zonasDisponibles[numAlt] << endl;

                //Buscar zona donde colocar
                newx = _zonas[zonasDisponibles[numAlt]]->getX();
                newy = _zonas[zonasDisponibles[numAlt]]->getY();
                newz = _zonas[zonasDisponibles[numAlt]]->getZ();

                //Se annade el nuevo elemento al vector de zonas
                _zonas[zonasDisponibles[numAlt]]->annadirElemento();

                //Colocar cofre
                int posicionObjeto = _motor->CargarObjetos(3,constantes.CERO,newx,newy,newz,2,2,2,"assets/models/Cofre/ChestCartoon.obj", "assets/models/Cofre/ChestCartoon.mtl");
                Interactuable*  inter = new Interactuable(-1,"Cofre",2,2,2,"assets/models/Cofre/ChestCartoon.obj","assets/models/Cofre/ChestCartoon.mtl", posicionObjeto, newx, newy, newz);
                int* id = cargador.GetID();
                inter->setID(*(++id));
                id = nullptr;
                inter->setPosiciones(newx,newy,newz);
                inter->SetPosicionArrayObjetos(posicionObjeto);
                inter->setRotacion(0.0,0.0,0.0);
                _interactuables.push_back(inter);
                inter = nullptr;

                //Fisicas del cofre
                _fisicas->crearCuerpo(3,constantes.CERO,newx/2,newy/2,newz/2,2,2,4,2,3);

                //borrar del Array por que el proposito esta cumplido
                if(_zonas[zonasDisponibles[numAlt]]->getTotalElementos() == _zonas[zonasDisponibles[numAlt]]->getElementosActuales())
                {
                    _zonas[zonasDisponibles[numAlt]]->setProposito(true);
                    zonasDisponibles.erase(zonasDisponibles.begin() + numAlt);
                }

                num_cofres--; //un cofre menos
            }
            zonasDisponibles.resize(0);

            // Debug: para cambiar la posicion del jugador al lado de un cofre
            posCofre[0] = newx;
            posCofre[1] = newy;
            posCofre[2] = newz;
        }
        else
        {
            cout << "No hay zonas de cofres suficientes en el nivel" << endl;
        }
    }
}

/************ ConectarWaypoints ************
 * Funcion establece por cada waypoint sus
 * conexiones con el resto de waypoints del nivel
 *      Entradas:
 * 
 *      Salidas:
*/
void Jugando::ConectarWaypoints()
{
    for(unsigned short i = 0; i < _waypoints.size(); i++)
    {
        for(unsigned short j = 0; j < _waypoints.size(); j++)
        {
            if(_waypoints[i]->ContainsConection(_waypoints[j]->GetID()) > -1)
            {
                _waypoints[i]->AnnadirConexionesWaypoints(_waypoints[j]);
            }
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
            _fisicas->crearCuerpo(0,0,_jugador->getX()/2,_jugador->getY()/2,_jugador->getZ()/2,2,_recolectables[rec_col]->getAncho(), _recolectables[rec_col]->getLargo(), _recolectables[rec_col]->getAlto(), 9);
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
    Constantes constantes;
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
            _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ());
            _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos() , posicion);
            cout<<"Abre la puerta"<<endl;
        }
        else
        {
            //Se cierra/desacciona la puerta / el mecanismo
            _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
            _motora->getEvent("CerrarPuerta")->start();
            _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() - (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ());
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
        //Busca la puerta que coincide con la palanca que se esta activando
        while(i < _interactuables.size() && !coincide)
        {
            if((_interactuables.at(i)->getCodigo() != _interactuables.at(int_col)->getCodigo()) ||
                strcmp(_interactuables.at(i)->getNombre(), PALANCA) == 0 ||
                strcmp(_interactuables.at(i)->getNombre(), "llave") == 0)
            {
                i++;
            }
            else
            {
                coincide = true;
            }
            
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
                _interactuables.at(i)->setNewRotacion(_interactuables.at(i)->getRX(), _interactuables.at(i)->getRY() + (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(i)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(i)->getX(), _interactuables.at(i)->getY(), _interactuables.at(i)->getZ(), _interactuables.at(i)->getRX() + 100.0, _interactuables.at(i)->getRY(), _interactuables.at(i)->getRZ(), _interactuables.at(i)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _interactuables.at(i)->setNewRotacion(_interactuables.at(i)->getRX(), _interactuables.at(i)->getRY() - (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(i)->getRZ());
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
        //Comprueba las llaves que tiene el jugador
        while(i < _jugador->GetLlaves().size() && !coincide)
        {
            if(_jugador->GetLlaves().at(i)->GetCodigoPuerta() == _interactuables.at(int_col)->getCodigo())
            {
                //Si el jugador tiene la llave cuyo codigo coincide con la puerta la abre
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
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ());
                _fisicas->updatePuerta(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ(), _interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() + (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ(), _interactuables.at(int_col)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_interactuables.at(int_col)->getX(), _interactuables.at(int_col)->getY(), _interactuables.at(int_col)->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _interactuables.at(int_col)->setNewRotacion(_interactuables.at(int_col)->getRX(), _interactuables.at(int_col)->getRY() - (constantes.PI_MEDIOS + constantes.PI_CUARTOS), _interactuables.at(int_col)->getRZ());
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
        if(danyo > 0)
        {
            _motor->colorearJugador(255, 55, 0, 255);
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
    if(auxiliarPathfinding >= 20 || (contadorEnem > 0 && _enem == _enemPideAyuda))
    {
        _auxiliadores.clear();
        enemDejarDePedirAyuda();
        _destinoPathFinding = nullptr;
        contadorEnem = 0;

    }
    //Si enem no es nulo se anade a la cola de enemigos _auxiliadores
    if(_enem != nullptr && _enem != _enemPideAyuda )
    {
        _enem->SetContestar(false);
        _auxiliadores.push_back(_enem);
        contadorEnem++;
    }
    //Si no hay sala de destino guardada, se guarda en este momento
    else if(_destinoPathFinding == nullptr)
    {
        _destinoPathFinding = _enemPideAyuda->getSala();
    }
    //Ejecucion del pathfinding si hay una sala de destino guardada
    if(_destinoPathFinding != nullptr)
    {
        while(!_auxiliadores.empty())
        {
            if(_destinoPathFinding != _auxiliadores.front()->getSala() && _auxiliadores.front()->GetModo() != 8)
            {
                Pathfinder* path = Pathfinder::getInstance();
                recorrido = path->encontrarCamino(_auxiliadores.front()->getSala(), _destinoPathFinding);
                vector<INdrawable::Posiciones> posicionesWaypoints;
                posicionesWaypoints.clear();
                for(unsigned short i = 0; i < recorrido.size(); i++)
                {
                    posicionesWaypoints.push_back(recorrido[i]->GetPosicionWaypoint());
                    _auxiliadores.front()->setSala(_destinoPathFinding);
                }
                _auxiliadores.front()->AnnadirRecorridoAyuda(posicionesWaypoints);
            }
            else if(_destinoPathFinding == _auxiliadores.front()->getSala() && _auxiliadores.front()->GetModo() != 1 && _auxiliadores.front()->GetModo() != 3)
            {
                _auxiliadores.front()->SetModo(1);
            }
            contadorEnem--;
            _auxiliadores.erase(_auxiliadores.begin());
        }
    }
    /*{
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
                    enemDejarDePedirAyuda();
                    contadorEnem = 0;
                }
            }
        }
    }*/
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

void Jugando::enemDejarDePedirAyuda()
{
    cout << "\e[42m Deja de pedir ayuda \e[0m" << endl;
    _enemPideAyuda->SetPedirAyuda(false);
    _enemPideAyuda = nullptr;
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