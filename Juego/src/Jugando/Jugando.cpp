#include "Jugando.hpp"
#include "../Juego.hpp"
#include "../Enemigos/Pollo.hpp"

//singleton
Jugando* Jugando::_unicaInstancia = 0;
//fin indicador singleton

#define PIRADIAN 180.0f
#define PI 3.14159265358979323846
#define PALANCA "palanca"

Jugando::Jugando()
{
    
}

Jugando::~Jugando()
{
    cout << "Borrando Jugando" << endl;
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

    // Punteros a clases singleton
    _controladorTiempo = nullptr;
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;

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

    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    CargarNivel(5, 1); //(level, player) 1 = heavy / 2 = bailaora

    reiniciando = false;
    ValoresPorDefecto();
    ValoresPorDefectoJugador();

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
}

void Jugando::ValoresPorDefectoJugador()
{
    float xIni = jugador.getIniX();
    float yIni = jugador.getIniY();
    float zIni = jugador.getIniZ();
    
    jugadorInmovil = false;
    jugador.setVida(100);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setTimeAtEsp(0.0f);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    jugador.setPosiciones(xIni, yIni, zIni);
    jugador.setNewPosiciones(xIni, yIni, zIni);
    jugador.initPosicionesFisicas(xIni/2, yIni/2, zIni/2);
    //TO DO: revisar que lo haga bien
    //jugador.setRotacion(0,180,0);
    //jugador.setNewRotacion(0,180,0);
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
        jugador.setVida(0);
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
    _motor->clearDebug();
    _motora->update(false); //Actualiza el motor de audio
    _sense->update(); //Se actualizan sentidos

    if (jugador.EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        jugador.MuereJugador(); // Animacion de muerte
        DesactivarDebug();
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }

    // ********** se actualiza posiciones e interpolado **********
    //animacion
    _motor->cambiarAnimacionJugador(jugador.getAnimacion());

    if(jugador.getArma() != nullptr)
    {
        float posArmaX = 5 * sin(PI * jugador.getRY() / PIRADIAN) + jugador.getX();
        float posArmaZ = 5 * cos(PI * jugador.getRY() / PIRADIAN) + jugador.getZ();;
        //iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
        jugador.getArma()->setPosiciones(posArmaX, jugador.getY()+3, posArmaZ);
        _motor->llevarObjeto(posArmaX, jugador.getY()+3,posArmaZ, jugador.getRX(), jugador.getRY(), jugador.getRZ() );
        _fisicas->llevarBox(posArmaX, jugador.getY()+3,posArmaZ, jugador.getArma()->getAncho(), jugador.getArma()->getLargo(), jugador.getArma()->getAlto());
    }

    //Comprueba la activacion de un powerup
    this->activarPowerUp();

    // Adelanta posicion del bounding box al jugador, mientras pulses esa direccion si colisiona no se mueve
    _fisicas->colisionChecker(_motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W),
        jugador.getNewX(),
        jugador.getNewY(),
        jugador.getNewZ()
    );

    //colisiones con todos los objetos y enemigos que no se traspasan
    if(_fisicas->collideObstacle() || !_fisicas->collidePlatform())
    {
        //colisiona
        jugadorInmovil = true;
        jugador.setNewPosiciones(jugador.getX(), jugador.getY(), jugador.getZ());
    }
    else
    {
        //no colisiona
        jugadorInmovil = false;
    }
    
    // Actualizar movimiento del jugador
    jugador.movimiento(jugadorInmovil,
        _motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W)
    );

    _motor->clearDebug2();   //Pruebas debug
    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        _fisicas->updateEnemigos(_enemigos.at(i)->getFisX(),
            _enemigos.at(i)->getFisY(),
            _enemigos.at(i)->getFisZ(),
            i
        );
        _motor->dibujarObjetoTemporal(_enemigos.at(i)->getFisX(),
            _enemigos.at(i)->getFisX(), _enemigos.at(i)->getFisX(),
            _enemigos.at(i)->getRX(), _enemigos.at(i)->getRY(),
            _enemigos.at(i)->getRZ(),5, 5, 5, 2);
    }

    _fisicas->updateJugador(jugador.getX(),
        jugador.getY(),
        jugador.getZ()
    );

    if(_enemPideAyuda != nullptr)   //Solo llama desde aqui a pathfinding si hay un enemigo pidiendo ayuda y enemigos buscandole.
    {
        this->updateRecorridoPathfinding(nullptr);
    }
    
    //Actualizar ataque especial
    this->updateAtEsp();
    this->updateAt(&danyo2);

    //Si se realiza el ataque se comprueban las colisiones
    if(jugador.getTimeAtEsp() > 0.0)
    {
        jugador.AtacarEspecialUpdate(&danyo);
    }
    else if(jugador.getTimeAt() > 0.0)
    {
        jugador.AtacarUpdate(danyo2);
    }
    else //En caso contrario se colorean los enemigos de color gris
    {
        for(unsigned int i = 0; i < _enemigos.size(); i++)
        {
            _motor->colorearEnemigo(255, 150, 150, 150, i);
        }
    }

    //Posicion de escucha
    _motora->setListenerPosition(jugador.getX(),jugador.getY(),jugador.getZ());

    //actualizamos los enemigos
    if(_enemigos.size() > 0)//posiciones interpolacion
    {
        float tiempoActual = 0.0f, tiempoAtaqueEsp = 0.0f;
        for(std::size_t i=0;i<_enemigos.size();i++)
        {
            //ESTE BUCLE SE VA A IR TODO SEGURAMENTE DESDE AQUI
            int danyo_jug = 0;
            _enemigos[i]->setPosAtaques(i);
            tiempoActual = _controladorTiempo->GetTiempo(2);
            //si el tiempo de ataque es mayor que 0, ir restando tiempo hasta 0
            if(_enemigos[i]->getTimeAtEsp() > 0.0f)
            {
                tiempoAtaqueEsp = _enemigos[i]->getTimeAtEsp();
                tiempoAtaqueEsp -= (tiempoActual - _enemigos[i]->getLastTimeAtEsp());
                _enemigos[i]->setLastTimeAtEsp(tiempoActual);
                _enemigos[i]->setTimeAtEsp(tiempoAtaqueEsp); //restar al tiempo de ataque
            }
            if(_enemigos[i]->getTimeAtEsp() <= 0.0f)
            {
                danyo_jug = _enemigos[i]->AtacarEspecial();
                _enemigos[i]->setTimeAtEsp(10.0f); //tiempo hasta el proximo ataque
                _enemigos[i]->setLastTimeAtEsp(_controladorTiempo->GetTiempo(2));
            }
            else if(_enemigos[i]->getBarraAtEs() < 100)
            {
                _enemigos[i]->AumentarBarraAtEs(1);
            }
            if(danyo_jug == 0)
            {
                //cout << "Enemigo " << i  << " pos: " << _enemigos[i]->getPosAtaques() << endl;

                //si el tiempo de ataque es mayor que 0, ir restando tiempo hasta 0
                /*if(_enemigos[i]->getTimeAt() > 0.0f)
                {
                    tiempoAtaque = _enemigos[i]->getTimeAt();
                    tiempoAtaque -= (tiempoActual - _enemigos[i]->getLastTimeAt());
                    _enemigos[i]->setLastTimeAt(tiempoActual);
                    _enemigos[i]->setTimeAt(tiempoAtaque); //restar al tiempo de ataque
                }
                if(_enemigos[i]->getTimeAt() <= 0.0f)
                {
                    danyo_jug = _enemigos[i]->Atacar();
                    _enemigos[i]->setTimeAt(1.5f); //tiempo hasta el proximo ataque
                    _enemigos[i]->setLastTimeAt(_controladorTiempo->GetTiempo(2));
                }
                //Si el enemigo ha realizado danyo
                if(danyo_jug > 0)
                {
                    jugador.QuitarVida(danyo_jug);
                    cout<< "Vida jugador: "<< jugador.getVida() << endl;
                }*/
            }
            else //Se le quita vida con el danyo del ataque especial
            {
                if(danyo_jug > 0)
                {
                    jugador.QuitarVida(danyo_jug);
                    cout<< "Vida jugador tras ataque especial: "<< jugador.getVida() << endl;
                }
            }
            //!ESTE BUCLE SE VA A IR TODO SEGURAMENTE HASTA AQUI

            cout<< "Ejecuto nodo actual de la ia: " << i << endl;
            if(_enemigos[i]!= nullptr && _enemigos[i]->GetEnemigo() == 0)
            {
                Pollo* enemPollo = (Pollo*) _enemigos[i];
                enemPollo->UpdatePollo(i);
                //colisiones con todos los objetos y enemigos que no se traspasan
                //AUN NO FUNCIONA
                /*if(_fisicas->enemyCollideObstacle(i) || !_fisicas->enemyCollidePlatform(i))
                {
                    //colisiona
                    enemPollo->Enemigo::setNewPosiciones(enemPollo->Enemigo::getX(), enemPollo->Enemigo::getY(), enemPollo->Enemigo::getZ());
                }*/
            }
            //_enemigos[i]->queVes();
        }
    }
        //_enemigos->MuereEnemigo(acumulator);
        //acumulator -= dt;
    //}

   // TO DO:
   //actualizamos la interfaz de jugador
    jugador.updateInterfaz();
    //actualizamos la interfaz en motor grafico
    _motor->updateInterfaz();
}

void Jugando::UpdateIA()
{
    /* *********** Teclas para probar cosas *************** */
    if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        jugador.QuitarVida(20);
    }
    /* **************************************************** */
    
    //En esta parte muere enemigo
    if(_enemigos.size() > 0){
        //comprobando los enemigos para saber si estan muertos
        for(std::size_t i=0;i<_enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

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
                    this->CrearObjeto(codigo,accion,nombre,ataque,x,y,z,0,0,ancho,largo,alto,modelo,textura,propiedades);
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
                    if(_enemigos[i]->GetEnemigo() == 0)
                    {
                        Pollo* enemPollo = (Pollo*) _enemigos[i];
                        enemPollo->RunIA();
                        enemPollo->UpdatePollo(i);
                        //AUN NO FUNCIONA
                        /*if(_fisicas->enemyCollideObstacle(i) || !_fisicas->enemyCollidePlatform(i))
                        {
                            //colisiona
                            enemPollo->Enemigo::setNewPosiciones(enemPollo->Enemigo::getX(), enemPollo->Enemigo::getY(), enemPollo->Enemigo::getZ());
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

    //Para evitar un tran salto en el principio de la ejecucion se actualiza el valor de drawTime
    if (drawTime == 0.0f)
    {
        drawTime = _controladorTiempo->GetTiempo(2);
    }
    lastDrawTime = drawTime;
    drawTime = _controladorTiempo->GetTiempo(2);

    //Dibujado del personaje
    jugador.moverseEntidad(1 / _controladorTiempo->GetUpdateTime());
    jugador.RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
    jugador.UpdateTimeMove(drawTime - lastDrawTime);
    _motor->mostrarJugador(jugador.getX(),
        jugador.getY(),
        jugador.getZ(),
        jugador.getRX(),
        jugador.getRY(),
        jugador.getRZ()
    );
    cout << jugador.getX() <<" Vida: "<<jugador.getVida()<< endl;
    
    //Dibujado de los enemigos
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

    //Dibujado del ataque especial
    //Ataque especial Heavy
    if(jugador.getTimeAtEsp() > 0.0f)
    {
        if(strcmp(jugador.getArmaEspecial()->getNombre(), "Heavy") == 0)
        {
            jugador.getArmaEspecial()->moverseEntidad(1 / _controladorTiempo->GetUpdateTime());
            jugador.getArmaEspecial()->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
            jugador.getArmaEspecial()->UpdateTimeMove(drawTime - lastDrawTime);

            _motor->mostrarArmaEspecial(
                jugador.GetDatosAtEsp()[0],
                jugador.getY(),
                jugador.GetDatosAtEsp()[2],
                jugador.getRX(),
                jugador.getRY(),
                jugador.getRZ());

            _motor->clearDebug2(); //Pruebas debug

            _motor->dibujarObjetoTemporal(
                jugador.getArmaEspecial()->getFisX()*2,
                jugador.getY(),
                jugador.getArmaEspecial()->getFisZ()*2,
                jugador.getRX(),
                jugador.getRY(),
                jugador.getRZ(),
                8,
                1,
                8,
                2);
        }

        //Ataque especial bailaora
        else if(strcmp(jugador.getArmaEspecial()->getNombre(), "Bailaora") == 0)
        {
            jugador.getArmaEspecial()->moverseEntidad(1 / _controladorTiempo->GetUpdateTime());
            jugador.getArmaEspecial()->RotarEntidad(1 / _controladorTiempo->GetUpdateTime());
            jugador.getArmaEspecial()->UpdateTimeMove(drawTime - lastDrawTime);

            _motor->mostrarArmaEspecial(
                jugador.GetDatosAtEsp()[0],
                jugador.GetDatosAtEsp()[1],
                jugador.GetDatosAtEsp()[2],
                jugador.GetDatosAtEsp()[3],
                jugador.GetDatosAtEsp()[4],
                jugador.GetDatosAtEsp()[5]);

            _motor->clearDebug2(); //Pruebas debug

            _motor->dibujarObjetoTemporal(
                jugador.getArmaEspecial()->getX(),
                jugador.getArmaEspecial()->getY(),
                jugador.getArmaEspecial()->getZ(),
                jugador.GetDatosAtEsp()[3],
                jugador.GetDatosAtEsp()[4],
                jugador.GetDatosAtEsp()[5],
                8,
                1,
                8,
                3);
        }
    }

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

        cout << "Cambia: "<<jugador.getX() << endl;

        // Resto de valores del juego
        ValoresPorDefecto();

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
    _motor->LimpiarMotorGrafico();
    //LimpiarNivel();
    _fisicas->limpiarFisicas();
    //limpiammos la sala
    if(_primeraSala != nullptr)
    {
       _primeraSala->~Sala();
       _primeraSala = nullptr;
    }

    //cargamos el nivel
    cargador.CargarNivelXml(nivel, tipoJug); //se llama al constructor vacio
    
    //Cargar objetos con el nivel completo
    this->cargarCofres(2); //Cargamos los cofres del nivel

    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Nivel1")->start(); //Reproducir musica juego
    _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente

    _motor->cargarInterfaz();
    //esta ya todo ejecutamos ia y interpolado
    return true;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearJugador(int accion, int x,int y,int z, int ancho, int largo, 
    int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades)
{
    cout << "Creo el jugador"<<endl;
    jugador = Jugador(x, y, z, ancho, largo, alto, ruta_objeto, ruta_textura);
    jugador.setID(++id);
    _motor->CargarJugador(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    ValoresPorDefectoJugador();
    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
    _motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");

    cout << "jugador creado en: "<<x<<", "<<y<<", "<<z<<", "<<endl;
    //TO DO: propiedades no se usa
}

void Jugando::CrearEnemigo(int accion, int enemigo, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int*  propiedades, Sala*  sala)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    //accion indicara futuramente que tipo de enemigo sera (herencia)
    switch (enemigo)
    {
        case 0:
        {
            Pollo* _ene = new Pollo();//aqui va el tipo de enemigo que es hacer ifffffffffsssss y meter una variable nueva de tipo para saber que tipo es
            //ia
            //cargadorIA.cargarBehaviorTreeXml("PolloBT");
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
            _enemigos.push_back(_ene);//guardamos el enemigo en el vector
            id++;//generamos id para la figura
            _enemigos.back()->setID(id);//le damos el id unico en esta partida al enemigo

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
    _enemigos.back()->Enemigo::initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _enemigos.back()->setVida(75);
    _enemigos.back()->setVelocidad(1.0f);
    _enemigos.back()->setBarraAtEs(0);
    _enemigos.back()->definirSala(sala);//le pasamos la sala en donde esta
    _enemigos.back()->setAtaque(10);
    _enemigos.back()->setArmaEspecial(100);
    _enemigos.back()->setTimeAtEsp(0.0f);
    _enemigos.back()->setDanyoCritico(50);
    _enemigos.back()->setProAtaCritico(10);
    //_enemigos.back()->genemigos.back()rarSonido(20,5);
    _enemigos.back()->setRotation(0.0f);//le ponemos hacia donde mira cuando se carga

    _motor->CargarEnemigos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,2);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,1,1,1,7); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,4,4,4,8); //Para ataques especiales
}

Sala* Jugando::CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    Sala* _sala = new Sala(ancho,largo,alto,x,y,z,centro);
    //int*  datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int nId = _motor->CargarPlataformas(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    _sala->definirID(nId);
    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,6);

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

void Jugando::CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int*  propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    int posicionObjeto;

    //Arma
    if(accion == 2)
    {
        posicionObjeto = _motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* _rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura);
        _rec->setID(_recolectables.size());
        _rec->setPosiciones(x,y,z);
        _rec->SetPosicionArrayObjetos(posicionObjeto);
        _recolectables.push_back(move(_rec));
        _rec = nullptr;
    }else
    //Puertas o interruptores
    if(accion == 3)
    {
        posicionObjeto = _motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Interactuable* _inter = new Interactuable(codigo, nombre, ancho, largo, alto, ruta_objeto, ruta_textura, posicionObjeto);
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
        posicionObjeto = _motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* _rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura);
        _rec->setID(_powerup.size());
        _rec->setPosiciones(x,y,z);
        _rec->SetPosicionArrayObjetos(posicionObjeto);
        _rec->setCantidad(propiedades[0]); //cantidad
        _powerup.push_back(move(_rec));
        _rec = nullptr;
    }else
    {
        posicionObjeto = _motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    }

    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,3);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba
}

void Jugando::CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, int*  propiedades)//lo utilizamos para crear zonas
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
        int posicionObjeto = _motor->CargarObjetos(3,newx,newy,newz,2,2,2,"assets/models/Cofre/ChestCartoon.obj", "assets/models/Cofre/ChestCartoon.mtl");
        Interactuable* inter = new Interactuable(-1,"Cofre",2,2,2,"assets/models/Cofre/ChestCartoon.obj","assets/models/Cofre/ChestCartoon.mtl", posicionObjeto);
        inter->setID(id++);
        inter->setPosiciones(newx,newy,newz);
        inter->SetPosicionArrayObjetos(posicionObjeto);
        inter->setRotacion(0.0,0.0,0.0);
        _interactuables.push_back(inter);

        //Fisicas del cofre
        _fisicas->crearCuerpo(3,newx/2,newy/2,newz/2,2,2,4,2,3);

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
    long unsigned int rec_col = _fisicas->collideColectable();
    jugador.setAnimacion(4);

    //En caso de no ser llaves
    if(_recolectables.at(rec_col)->getCodigo() == 0)
    {
        if(jugador.getArma() == nullptr)//si no tiene arma equipada
        {
            //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)_recolectables[rec_col];
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),_recolectables[rec_col]->getNombre(),_recolectables[rec_col]->getAncho(),_recolectables[rec_col]->getLargo(),_recolectables[rec_col]->getAlto(),_recolectables[rec_col]->getObjeto(),_recolectables[rec_col]->getTextura());
            jugador.setArma(nuArma);
            //PROVISIONAL
            jugador.getArma()->setRotacion(0.0, PIRADIAN, 0.0);
            //!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), _recolectables[rec_col]->getObjeto(), _recolectables[rec_col]->getTextura());
            //lo cargamos por primera vez en el motor de fisicas
            _fisicas->crearCuerpo(0,jugador.getX()/2,jugador.getY()/2,jugador.getZ()/2,2,_recolectables[rec_col]->getAncho(), _recolectables[rec_col]->getLargo(), _recolectables[rec_col]->getAlto(), 6);
            //borramos el recolectable de nivel, _motor grafico y motor fisicas
            _recolectables.erase(_recolectables.begin() + rec_col);
            _motor->EraseColectable(rec_col);
            _fisicas->EraseColectable(rec_col);
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
        else if(jugador.getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(0, jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
            nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),_recolectables[rec_col]->getNombre(),_recolectables[rec_col]->getAncho(),_recolectables[rec_col]->getLargo(),_recolectables[rec_col]->getAlto(),_recolectables[rec_col]->getObjeto(),_recolectables[rec_col]->getTextura());
            _motor->EraseArma();
            jugador.setArma(nuArma);
            
            //PROVISIONAL
            jugador.getArma()->setRotacion(0.0, PIRADIAN, 0.0);
            
            //!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), _recolectables[rec_col]->getObjeto(), _recolectables[rec_col]->getTextura());
            
            //lo cargamos en el motor de fisicas
            _fisicas->setFormaArma(jugador.getX()/2, jugador.getY()/2, jugador.getZ()/2, jugador.getArma()->getAncho(), jugador.getArma()->getLargo(),jugador.getArma()->getAlto());
            
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
        jugador.AnnadirLlave(llave);
        
        //borramos el recolectable de nivel, _motor grafico y motor fisicas
        _recolectables.erase(_recolectables.begin() + rec_col);
        _motor->EraseColectable(rec_col);
        _fisicas->EraseColectable(rec_col);
    }
}

void Jugando::DejarObjeto()
{
    if(jugador.getArma() != nullptr)//si tiene arma equipada
    {
        //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
        Recolectable* nuRec = new Recolectable(0, jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
        nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
        _motor->EraseArma();
        _fisicas->EraseArma();
        jugador.setArma(NULL);

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
        while(i < jugador.GetLlaves().size() && !coincide)
        {
            if(jugador.GetLlaves().at(i)->GetCodigoPuerta() == _interactuables.at(int_col)->getCodigo())
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
   this->CrearObjeto(codigo,accion,nombre,ataque,x,y,z,0,0,ancho,largo,alto,modelo,textura,propiedades);
}

void Jugando::activarPowerUp()
{
    int int_cpw = _fisicas->collideColectablePowerup();

    if(int_cpw >= 0 && int_cpw != int_cpw_aux)
    {
        bool locoges = false; //Comprobar si lo puedes coger

        //Efecto del power up (ataque) 0 = vida, 1 = energia, 2 = monedas, 3 = danyo, 4 = defensa
        if(_powerup.at(int_cpw)->getAtaque() == 0 && jugador.getVida() < 100)
        {
            cout << "PowerUP! Curado 20 de vida. TOTAL:" << jugador.getVida() << endl;
            jugador.RecuperarVida(20);
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->getAtaque() == 1 && jugador.getBarraAtEs() < 100)
        {
            cout << "PowerUP! 50 de energia. TOTAL:" << jugador.getBarraAtEs() << endl;
            jugador.AumentarBarraAtEs(50);
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->getAtaque() == 2)
        {
            cout << "Recoges " << _powerup.at(int_cpw)->getCantidad() << " de oro" << endl;
            jugador.AumentarDinero(_powerup.at(int_cpw)->getCantidad());
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
    if((_motor->EstaPulsado(KEY_ESPACIO) || _motor->EstaPulsado(LMOUSE_DOWN)) && jugador.getTimeAt() <= 0.0f)
    {
        *danyo = jugador.Atacar(0);
        _motor->ResetKey(KEY_ESPACIO);
        _motor->ResetEvento(LMOUSE_DOWN);
        //atacktime = 1.5f;
        jugador.setTimeAt(1.5f);
        jugador.setLastTimeAt(_controladorTiempo->GetTiempo(2));
    } else {
        if(jugador.getTimeAt() > 0.0f)
        {
            tiempoActual = _controladorTiempo->GetTiempo(2);
            tiempoAtaque = jugador.getTimeAt();
            tiempoAtaque -= (tiempoActual - jugador.getLastTimeAt());
            jugador.setLastTimeAt(tiempoActual);
            jugador.setTimeAt(tiempoAtaque);
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
        if(jugador.getTimeAt() <= 0.0f){
            _motor->clearDebug2();
        }
    }
}

void Jugando::updateAtEsp()
{
    float tiempoActual = 0.0f;
    float tiempoAtaqueEsp = 0.0f;
    //Compureba si se realiza el ataque especial o si la animacion esta a medias
    if((_motor->EstaPulsado(RMOUSE_DOWN)||_motor->EstaPulsado(KEY_Q)) && jugador.getTimeAtEsp() <= 0.0)
    {
        danyo = jugador.AtacarEspecial();
        _motor->ResetKey(KEY_Q);
        _motor->ResetEvento(RMOUSE_DOWN);
        _motor->colorearJugador(255, 55, 0, 255);
        if(danyo > 0)
        {
            jugador.setTimeAtEsp(1.5f);
            jugador.setLastTimeAtEsp(_controladorTiempo->GetTiempo(2));

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
            tiempoActual = _controladorTiempo->GetTiempo(2);
            tiempoAtaqueEsp = jugador.getTimeAtEsp();
            tiempoAtaqueEsp -= (tiempoActual - jugador.getLastTimeAtEsp());
            jugador.setLastTimeAtEsp(tiempoActual);
            jugador.setTimeAtEsp(tiempoAtaqueEsp);
            danyo = jugador.AtacarEspecial();
        }
        /*if(jugador.getTimeAtEsp() > 0.f && ((int) (jugador.getTimeAtEsp()*  100) % 10 >= 4) && ((int) (jugador.getTimeAtEsp()*  100) % 10 <= 4))
        {
            danyo = jugador.AtacarEspecial();
        }*/
        if(jugador.getTimeAtEsp() == 1.0f)
        {
            _motor->colorearEnemigo(255,255,255,255,0);
        }
        if(jugador.getTimeAtEsp() <= 0.5f && _motor->getArmaEspecial()) //Zona de pruebas
        {
            _motor->borrarArmaEspecial();
            _motor->colorearJugador(255, 150, 150, 150);
        }
    }
}

void Jugando::updateRecorridoPathfinding(Enemigo* _enem)
{
    //Si enem no es nulo se anade a la cola de enemigos auxiliadores
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
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidad(), 0.0, _auxiliadores.front()->getVelocidad());
                        cout<<"Posicion del enemigo: x="<<_auxiliadores.front()->getNewX()<<" z=" << _auxiliadores.front()->getNewY();
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidad()), 0.0, _auxiliadores.front()->getVelocidad());
                    }
                    else
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() + _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, _auxiliadores.front()->getVelocidad());
                    }
                }
                else if(moveArb)
                {
                    if(moveDer)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidad(), 0.0, -(_auxiliadores.front()->getVelocidad()));
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidad()), 0.0, -(_auxiliadores.front()->getVelocidad()));
                    }
                    else
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ() - _auxiliadores.front()->getVelocidad());
                        _auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, -(_auxiliadores.front()->getVelocidad()));
                    }
                }
                else
                {
                    if(moveDer)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() + _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ());
                        _auxiliadores.front()->setPosicionesFisicas(_auxiliadores.front()->getVelocidad(), 0.0, 0.0);
                    }
                    else if(moveIzq)
                    {
                        _auxiliadores.front()->setNewPosiciones(_auxiliadores.front()->getNewX() - _auxiliadores.front()->getVelocidad(), _auxiliadores.front()->getNewY(), _auxiliadores.front()->getNewZ());
                        _auxiliadores.front()->setPosicionesFisicas(- (_auxiliadores.front()->getVelocidad()), 0.0, 0.0);
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

Jugador* Jugando::GetJugador()
{
    return &jugador;
}