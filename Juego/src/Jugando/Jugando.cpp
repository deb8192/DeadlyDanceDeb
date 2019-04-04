#include "Jugando.hpp"
#include "../Juego.hpp"
#include "../ConstantesComunes.hpp"
#include "../Enemigos/CofreArana.hpp"
#include "../Objetos/Puerta.hpp"

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
    _puzzle = nullptr;

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

    tam = _eneCofres.size();
    for(short i=0; i < tam; i++)
    {
        _eneCofres.at(i) = nullptr;
    }
    _eneCofres.clear();

    tam = _zonas.size();
    for(short i=0; i < tam; i++)
    {
        _zonas.at(i) = nullptr;
    }
    _zonas.clear();

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

    tam = _palancas.size();
    for(short i=0; i < tam; i++)
    {
        _palancas.at(i) = nullptr;
    }
    _palancas.clear();

    tam = _puertas.size();
    for(short i=0; i < tam; i++)
    {
        _puertas.at(i) = nullptr;
    }
    _puertas.clear();

    tam = _cofres.size();
    for(short i=0; i < tam; i++)
    {
        _cofres.at(i) = nullptr;
    }
    _cofres.clear();

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

    // Cargamos todos los puzzles en memoria
    cargPuzzles.CargarPuzzlesXml();

    Constantes constantes;
    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    #ifdef WEMOTOR
        CargarNivel(7, constantes.HEAVY);
    #else
        CargarNivel(6, constantes.HEAVY);
    #endif
    //TO DO: hacerle un reserve:
    //_auxiliadores.reserve(xx);
    //recorrido.reserve(xx);

    reiniciando = false;
    puzzleResuelto = false;

    ValoresPorDefecto();

    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
    _motor->BorrarCargando();
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
    //Valores para el centro de las bandadas en el flocking
    posicionMediaEnemigos.vX = INT_MAX;
    posicionMediaEnemigos.vY = INT_MAX;
    posicionMediaEnemigos.vZ = INT_MAX;
    proyectilFuera = true;
    // Activamos la interfaz
    _interfaz->activar();
    desactivarColisionesJugador = false;
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
    _jugador->setTimeAt(0.0f);
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
    // TO DO: comprobar si esta en array ene
    // sacarlo de ahí y del motor
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

    // Desactivar fisicas jugador
    if(_motor->EstaPulsado(KEY_U))
    {
        desactivarColisionesJugador = !desactivarColisionesJugador;
        _motor->ResetKey(KEY_U);
    }

    // Multicamara
    if(_motor->EstaPulsado(KEY_C))
    {
        _motor->ResetKey(KEY_C);
        _motor->CambiarCamara();
    }

    // Debug para probar cofres
    if(_motor->EstaPulsado(KEY_I))
    {
        cargador.TrasladarJugadorACofres();
        _motor->ResetKey(KEY_I);
    }

    if(_motor->EstaPulsado(KEY_Z))
    {
        /*_motor->DibujarCofre(_cofreP->GetPosicionArrayObjetos(), true);
        _cofreP->CrearFisica();
        _cofreP->accionar();*/
        //_cofreP=nullptr;
        _motor->ResetKey(KEY_Z);
    }

    if(_motor->EstaPulsado(KEY_B))
    {
        unsigned short desplaza = 10;
        _jugador->setPosiciones(242+desplaza, 0, 490);
        _jugador->setNewPosiciones(242+desplaza, 0, 490);
        _jugador->initPosicionesFisicas((242+desplaza)/2, 0/2, 490/2);
        enSalaBoss = true;
        CargarBossEnMemoria();
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
}

/************************** InteractuarNivel* ************************
* Detecta las posiciones de los objetos recolectables y de interaccion
* y si está pulsado E interactua y si no lo pinta de color para destacarlo
*/
void Jugando::InteractuarNivel()
{
    //lo siguiente es para saber que objeto colisiona con jugador
    int rec_col = _fisicas->collideColectable();
    short int_puerta = _fisicas->collidePuerta();
    short int_palanca = _fisicas->collidePalanca();
    short int_cofre = _fisicas->collideCofre();
    Constantes constantes;

    if (int_puerta >= 0)
    {
        AccionarMecanismo(int_puerta, constantes.PUERTA_OBJ);
    }
    else if (int_palanca >= 0)
    {
        AccionarMecanismo(int_palanca, constantes.PALANCA);
    }

    if (int_cofre >= 0)
    {
        AccionarMecanismo(int_cofre, constantes.COFRE_OBJ);
    }
    
    if(rec_col < 0 && int_cofre < 0 && 
        int_palanca < 0 && int_puerta < 0)
    {
        DejarObjeto();
    }
    else if (rec_col >= 0)
    {
        CogerObjeto();
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

    //colisiones con todos los objetos y enemigos que no se traspasan
    jugadorInmovil = _jugador->ColisionEntornoEne();

    if(desactivarColisionesJugador)
    {
        jugadorInmovil = false;
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


    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        _fisicas->updateEnemigos(_enemigos.at(i)->getFisX(),
            _enemigos.at(i)->getFisY(),
            _enemigos.at(i)->getFisZ(),
            i
        );
    }

    //Si se realiza el ataque se comprueban las colisiones
    if(_jugador->getTimeAtEsp() > 0.0)
    {
        _jugador->AtacarEspecialUpdate(&danyo, _enemigos);
    }
    else if(_jugador->getTimeAt() > 0.0)
    {
        unsigned int posicion = 0;
        std::vector<short> indiceObjetosColisionados = _fisicas->collideAttackWall();
        for(unsigned short i = 0; i < indiceObjetosColisionados.size(); i ++)
        {
            _motora->getEvent("RomperPared")->setPosition(_jugador->getX(),_jugador->getY(),_jugador->getZ());
            _motora->getEvent("RomperPared")->start();

            _fisicas->ErasePared(indiceObjetosColisionados[i]);
            posicion = _fisicas->GetRelacionParedesObstaculos(indiceObjetosColisionados[i]);
            _fisicas->EraseObstaculo(posicion);

            if(posicion != 0)
            {
                //TO DO: anyadirle tiempo de espera para la anim y luego hacerla invisible
                _motor->DibujarPared(_paredes[indiceObjetosColisionados[i]]->GetPosicionArrayObjetos(), false);
                posicion = 0;
            }
        }
        _jugador->AtacarUpdate(danyo2, _enemigos);
    }

    //actualizamos los enemigos
    if(_enemigos.size() > 0)//posiciones interpolacion
    {
        //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;
        short contadorEnemigos = 0;
        INnpc::VectorEspacial posicionTemporal;

        for(short i=0;(unsigned)i<_enemigos.size();i++)
        {
            if(_enemigos[i] != nullptr)
            {
                // Se coloca la posicionMedia de las bandadas
                if(_enemigos[i]->GetModo() == constantes.UNO)
                {
                    if(posicionMediaEnemigos.vX != INT_MAX)
                    {
                        _enemigos[i]->SetPosicionComunBandada(posicionMediaEnemigos);
                    }
                }

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
                if(_enemigos[i]->GetModo() == constantes.UNO && _enemigos[i]->getVida() > 0)
                {
                    contadorEnemigos++;
                    posicionTemporal.vX += _enemigos[i]->getX();
                    posicionTemporal.vY += _enemigos[i]->getY();
                    posicionTemporal.vZ += _enemigos[i]->getZ();
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
                //Este bloque se da si el enemigo (de momento guardian) esta en modo ocultacion
                if(_enemigos[i]->getTimeOcultarse() > 0.0f)
                {
                    if(_enemigos[i]->getTimeOcultarse() == 1.5f)
                    {
                        //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeOcultarse(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoOcultarse = 0.0f;
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoOcultarse = _enemigos[i]->getTimeOcultarse();
                    tiempoOcultarse -= (tiempoActual - _enemigos[i]->getLastTimeOcultarse());
                    if(tiempoActual > _enemigos[i]->getLastTimeOcultarse())
                    {
                        //Si no es la primera vez que entra al bucle de merodear, tiempoActual debe ser mayor que lastTimeOcultarse
                        //por lo que guardamos en lastTimeOcultarse a tiempoActual
                        _enemigos[i]->setLastTimeOcultarse(tiempoActual);
                    }
                    _enemigos[i]->setTimeOcultarse(tiempoOcultarse);
                }
            }
            //_enemigos[i]->queVes();
        }
        if(contadorEnemigos >= 1)
        {
            posicionMediaEnemigos.vX = posicionTemporal.vX / contadorEnemigos;
            posicionMediaEnemigos.vY = posicionTemporal.vY / contadorEnemigos;
            posicionMediaEnemigos.vZ = posicionTemporal.vZ / contadorEnemigos;
        }
        else
        {
            posicionMediaEnemigos.vX = INT_MAX;
            posicionMediaEnemigos.vY = INT_MAX;
            posicionMediaEnemigos.vZ = INT_MAX;
        }


    }
        //_enemigos->MuereEnemigo(acumulator);
        //acumulator -= dt;
    //}
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
    // Bajar vida
    if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        _jugador->ModificarVida(-20);
    }

    // Subir vida
    if (_motor->EstaPulsado(KEY_H))
    {
        _motor->ResetKey(KEY_H);
        _jugador->ModificarVida(20);
    }
    /* **************************************************** */

    //Aquí el jugador genera sonidos al caminar
    if(!_jugador->EstaMuerto() && (!jugadorInmovil && (_motor->EstaPulsado(KEY_A)
     || _motor->EstaPulsado(KEY_S) || _motor->EstaPulsado(KEY_D) || _motor->EstaPulsado(KEY_W))))
    {
        _jugador->generarSonido(constantes.NUEVE * constantes.SEIS, constantes.CINCO, constantes.UNO);
    }

    //En esta parte muere enemigo
    if(_enemigos.size() > 0){
        //comprobando los _enemigos para saber si estan muertos
        for(short i=0;(unsigned)i<_enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

            if(_enemigos[i]->estasMuerto() && _enemigos[i]->finalAnimMuerte())
            {
                //Datos comunes a todos
                int x = _enemigos[i]->getX();
                int y = _enemigos[i]->getY();
                int z = _enemigos[i]->getZ();
               
                if(_enemigos[i]->GetTipoEnemigo() == constantes.GUARDIAN_A || 
                    _enemigos[i]->GetTipoEnemigo() == constantes.GUARDIAN_B)
                {
                    CrearObjeto(x,y,z,2,2,2,constantes.LLAVE,0);
                }
                // TO DO: anyadir cofre aranya
                // else if (_enemigos[i]->GetTipoEnemigo() == constantes.ARANA)
                else
                {
                    unsigned short tipoObj = NumeroAleatorio(constantes.ORO,constantes.ENERGIA);
                    unsigned short cantidad = 0;
                    if (tipoObj == constantes.ORO) {
                        cantidad = NumeroAleatorio(1,5);
                    } else if (tipoObj == constantes.VIDA) {
                        cantidad = NumeroAleatorio(20,50);
                    } else { // ENERGIA
                        cantidad = NumeroAleatorio(10,60);
                    }
                    CrearPowerUp(x,y,z,tipoObj,cantidad);
                }

                if (_enemigos[i] != nullptr && _enemigos[i]->GetPedirAyuda()) {
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

    // Para cuando se mate al boss
    //Juego::GetInstance()->estado.CambioEstadoGanar();
}

void Jugando::Render()
{
    Constantes constantes;
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

    //Dibujado de las puertas, las palancas y los cofres ****************
    for(unsigned short i = 0; i < _puertas.size(); i++)
    {
        _puertas.at(i)->Render(updateTime, resta);
    }

    for(unsigned short i = 0; i < _palancas.size(); i++)
    {
        _palancas.at(i)->Render(updateTime, resta);
    }

    for(unsigned short i = 0; i < _cofres.size(); i++)
    {
        _cofres.at(i)->Render(updateTime, resta);
    }
    //*******************************************************************

    //Dibujado del personaje
    _jugador->Render(updateTime, resta);

    //Armas
    if(_jugador->getArma() != nullptr)
    {
        //Ataque Animacion
        if (_jugador->getArma()->GetTipoObjeto() == constantes.GUITARRA)
        {
            if(_jugador->getTimeAt() == 1.5f)
            {
                mov_weapon_rotX = -90;
                mov_weapon_posX = 3.5;
                mov_weapon_posZ = 3.5;
                mov_weapon_posY = 4.0;
            }
            else if(_jugador->getTimeAt() > 0.0f && _jugador->getTimeAt() < 1.5f)
            {
                if(mov_weapon_rotX < 0)mov_weapon_rotX += 4;
                if(mov_weapon_posY > 1.5)mov_weapon_posY -= 0.2;
                if(mov_weapon_posX < 5.5)mov_weapon_posX += 0.3;
                if(mov_weapon_posZ < 5.5)mov_weapon_posZ += 0.3;
            }
            else
            {
                mov_weapon_posX=-2.0;
                mov_weapon_posZ=-1.5;
                mov_weapon_posY=5.0;
                mov_weapon_rotX=90;
                mov_weapon_rotY=0;
                mov_weapon_rotZ=0;
            }
        }
        else if(_jugador->getArma()->GetTipoObjeto() == constantes.ARPA)
        {
            if(_jugador->getTimeAt() == 1.5f)
            {
                proyectilFuera = false;
                mov_weapon_rotX = 180;
                mov_weapon_posX = 2;
                mov_weapon_posZ = 2;
                mov_weapon_posY = 2.5;
            }
            else if(_jugador->getTimeAt() <= 0.0f)
            {
                if(proyectilFuera == false)
                {
                    _motor->EraseProyectil();
                    proyectilFuera = true;
                }
                mov_weapon_posX=-0.7;
                mov_weapon_posZ=-0.5;
                mov_weapon_posY=2.3;
                mov_weapon_rotX=90;
                mov_weapon_rotY=0;
                mov_weapon_rotZ=0;
            }
        }

        //METERLE LA FUNCION AL JUGADOR
        float posArmaX = mov_weapon_posX*  sin(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getX();
        float posArmaZ = mov_weapon_posZ*  cos(constantes.PI*  _jugador->getRY() / constantes.PI_RADIAN) + _jugador->getZ();//iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
        _jugador->getArma()->setPosiciones(posArmaX, _jugador->getY()+3, posArmaZ);
        //!METERLE LA FUNCION AL JUGADOR

       _motor->llevarObjeto(posArmaX, _jugador->getY()+mov_weapon_posY,posArmaZ, _jugador->getRX()+mov_weapon_rotX, _jugador->getRY()+mov_weapon_rotY, _jugador->getRZ()+mov_weapon_rotZ );
       _fisicas->llevarBox(posArmaX, _jugador->getY()+mov_weapon_posY,posArmaZ, _jugador->getArma()->getAncho()+mov_weapon_rotX, _jugador->getArma()->getLargo()+mov_weapon_rotY, _jugador->getArma()->getAlto()+mov_weapon_rotZ);
    }


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

    //Dibujado waypoints
    for(unsigned int i=0; i < _waypoints.size(); i++)
    {
        _waypoints.at(i)->Render();
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
    else if (puzzleResuelto)
    {
        if (ganarPuzzle)
        {
            // TO DO: Crear objeto chulo
            _cofreP->DesactivarCofre();
            AbrirCofre(_cofreP);
            _cofreP = nullptr;
        }
        else
        {
            _cofreP->accionar();
            CrearEnemigoArana();
        }
        ganarPuzzle = false;
        puzzleResuelto = false;
    }
}

void Jugando::Reiniciar()
{
    reiniciando = true;
}

void Jugando::EstPuzzle(bool ganar)
{
    ganarPuzzle = ganar;
    puzzleResuelto = true;
    _motor->HabilitarDinero();
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
    _paredes = cargador.GetParedes();
    _powerup = cargador.GetPowerup();
    _zonas = cargador.GetZonas();
    _enemigos = cargador.GetEnemigos();
    _waypoints = cargador.GetWaypoints();
    ConectarWaypoints();

    //Cargar objetos con el nivel completo
    cargador.CargarCofres(); //Cargamos los cofres del nivel
    probArana = _eneCofres.size();
    _puertas = cargador.GetPuertas();
    _palancas = cargador.GetPalancas();
    _cofres = cargador.GetCofres();
    _eneCofres = cargador.GetEneCofres();
    _boss = cargador.GetBoss();

    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Nivel1")->setVolume(0.1);
    _motora->getEvent("Nivel1")->start(); //Reproducir musica juego
    _motora->getEvent("AmbienteGritos")->setVolume(0.5);
    _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente
    _motora->getEvent("AmbienteLava")->setPosition(145.0f,0.0f,18.0f);
    _motora->getEvent("AmbienteLava")->setVolume(1.0);
    _motora->getEvent("AmbienteLava")->start(); //Reproducir ambiente

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
        _jugador->getZ(), _jugador->getRutaArmaEsp(),_jugador->getRutaTexturaArmaEsp());

}

unsigned short Jugando::NumeroAleatorio(unsigned short limite_inf, unsigned short limite_sup)
{
    srand(time(NULL));
    return (limite_inf + rand() % (limite_sup+1 - limite_inf));
}

void Jugando::CrearPowerUp(int x,int y,int z, unsigned short tipoObjeto,
    unsigned short cantidad)
{
    Recolectable* _rec = new Recolectable(-1,1,1,1,x,y,z,tipoObjeto,
        4,0,0);
    int posicionObjeto = _motor->CargarObjetos(4,0,x,y,z,1,1,1,
        _rec->GetModelo(),_rec->GetTextura());
    _rec->SetPosicionArrayObjetos(posicionObjeto);
    // Obtiene la vida, energia o cantidad de oro dentro de un rango
    _rec->setCantidad(cantidad);
    _powerup.push_back(move(_rec));
    _rec = nullptr;
}

void Jugando::CrearObjeto(int x,int y,int z,int ancho,int largo,int alto,
    unsigned short tipoObjeto,unsigned short ataque)
{
    Constantes constantes;
    Recolectable* _rec = new Recolectable(-1,ancho,largo,alto,x,y,z,tipoObjeto,
        2,0,0);
    int posicionObjeto = _motor->CargarObjetos(2,0,x,y,z,ancho,largo,alto,
        _rec->GetModelo(),_rec->GetTextura());
    _rec->SetPosicionArrayObjetos(posicionObjeto);

    if (tipoObjeto == constantes.LLAVE)
    {
        _rec->setCodigo(20);
    }
    else  // ARMAS
    {
        _rec->setAtaque(ataque);
    }
    _recolectables.push_back(move(_rec));
    _rec = nullptr;
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

// Para coger una llave o un arma
void Jugando::CogerObjeto()
{
    Constantes constantes;
    long unsigned int rec_col = _fisicas->collideColectable();
    _jugador->setAnimacion(4);

    // Comprobamos si es una llave
    if(_recolectables.at(rec_col)->GetTipoObjeto() == constantes.LLAVE)
    {
        Llave* llave = new Llave(_recolectables.at(rec_col)->getCodigo());
        _jugador->AnnadirLlave(llave);

        //borramos el recolectable de nivel, _motor grafico y motor fisicas
        _recolectables.erase(_recolectables.begin() + rec_col);
        _motor->EraseColectable(rec_col);
        _fisicas->EraseColectable(rec_col);
    } 
    else // En el caso contrario, es un arma
    {
        if(_jugador->getArma() == nullptr)//si no tiene arma equipada
        {
            //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)_recolectables[rec_col];
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),
                _recolectables[rec_col]->getAncho(),
                _recolectables[rec_col]->getLargo(),_recolectables[rec_col]->getAlto(),
                _recolectables[rec_col]->GetTipoObjeto());
            _jugador->setArma(nuArma);
            //PROVISIONAL
            _jugador->getArma()->setRotacion(0.0, constantes.PI_RADIAN, 0.0);//!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(_jugador->getX(), _jugador->getY(), _jugador->getZ(), _recolectables[rec_col]->GetModelo(),NULL);
            //lo cargamos por primera vez en el motor de fisicas
            _fisicas->crearCuerpo(0,_jugador->getX()/2,_jugador->getY()/2,_jugador->getZ()/2,2,_recolectables[rec_col]->getAncho(), _recolectables[rec_col]->getLargo(), _recolectables[rec_col]->getAlto(), 9,0,0);
            //borramos el recolectable de nivel, _motor grafico y motor fisicas
            _recolectables.erase(_recolectables.begin() + rec_col);
            _motor->EraseColectable(rec_col);
            _fisicas->EraseColectable(rec_col);
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
        else if(_jugador->getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(-1,
                _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(), 
                _jugador->getArma()->getAlto(),
                _jugador->getX(),_jugador->getY(), _jugador->getZ(),
                _jugador->getArma()->GetTipoObjeto(),2,0,0);
            nuRec->setAtaque(_jugador->getArma()->getAtaque());
            
            Arma* nuArma = new Arma(_recolectables[rec_col]->getAtaque(),
                _recolectables[rec_col]->getAncho(), _recolectables[rec_col]->getLargo(),
                _recolectables[rec_col]->getAlto(), _recolectables[rec_col]->GetTipoObjeto());
            _motor->EraseArma();
            _jugador->setArma(nuArma);

            //PROVISIONAL
            _jugador->getArma()->setRotacion(0.0, constantes.PI_RADIAN, 0.0);
            //!PROVISIONAL
            //lo cargamos por primera vez en el motor de graficos
            _motor->CargarArmaJugador(_jugador->getX(), _jugador->getY(), _jugador->getZ(), 
                _recolectables[rec_col]->GetModelo(), NULL);

            //lo cargamos en el motor de fisicas
            _fisicas->setFormaArma(_jugador->getX()/2, _jugador->getY()/2, _jugador->getZ()/2, 
                _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(),_jugador->getArma()->getAlto());

            //borramos el recolectable anterior de nivel, _motor grafico y motor fisicas
            _recolectables.erase(_recolectables.begin() + rec_col);
            _motor->EraseColectable(rec_col);
            _fisicas->EraseColectable(rec_col);

            //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
            _recolectables.push_back(nuRec);
            
            _motor->CargarRecolectable(_recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->GetModelo(), NULL);
            atacktime = 0.0f; //Reiniciar tiempo de ataques
        }
    }
}

void Jugando::DejarObjeto()
{
    Constantes constantes;
    if(_jugador->getArma() != nullptr)//si tiene arma equipada
    {
        //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
        Recolectable* nuRec = new Recolectable(-1,
            _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(), 
            _jugador->getArma()->getAlto(),
            _jugador->getX(),_jugador->getY(), _jugador->getZ(),
            _jugador->getArma()->GetTipoObjeto(),2,0,0);
        nuRec->setAtaque(_jugador->getArma()->getAtaque());

        _motor->EraseArma();
        _fisicas->EraseArma();
        _jugador->setArma(NULL);

        //por ultimo creamos una nueva y actualizamos informacion en motor grafico
        _motor->CargarRecolectable(_recolectables.size(),
            nuRec->getX(), nuRec->getY(),nuRec->getZ(),
            nuRec->GetModelo(), NULL);

        _recolectables.push_back(move(nuRec));
        nuRec = nullptr;
    }
}

/*********** AccionarMecanismo ***********
*  Funcion que depende del tipoObj, obtiene el interactuable
*  de la posicion pos de su propio array.
*/
void Jugando::AccionarMecanismo(int pos, const unsigned short tipoObj)
{
    Constantes constantes;
    unsigned int i = 0;
    bool coincide = false;

    if (tipoObj == constantes.COFRE_OBJ) // TO DO: repasar todo lo de los cofres al terminar la IA
    {
        _cofreP = _cofres.at(pos);
        if (_cofreP->GetEsArana())
        {
            AbrirPantallaPuzzle();
        }
        else
        {
            _cofreP->DesactivarCofre();
            AbrirCofre(_cofreP);
            _cofreP = nullptr;
        }
    }
    else if (tipoObj == constantes.PALANCA)
    {
        Palanca* _palanca = _palancas.at(pos);

        //Busca la puerta que coincide con la palanca que se esta activando
        while(i < _puertas.size() && !coincide)
        {
            if (_puertas.at(i)->getCodigo() != _palanca->getCodigo())
            {
                i++;
            }
            else
            {
                coincide = true;
            }
        }
        if (coincide)
        {
            //Se acciona o desacciona el mecanismo segun su estado actual
            bool activar = _palanca->accionar();
            Puerta* _puerta = _puertas.at(i);
            bool abrir = _puerta->accionar();
            float rot = (constantes.PI_MEDIOS + constantes.PI_CUARTOS);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                _motora->getEvent("AbrirPuerta")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                _motora->getEvent("AbrirPuerta")->start();
                _puerta->GirarPuerta(rot);
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _puerta->GirarPuerta(-rot);
            }

            if(activar)
            {
                //Se abre/acciona la puerta / el mecanismo
                #ifdef WEMOTOR
                    _palanca->setNewRotacion(_palanca->getRX(), _palanca->getRY(), _palanca->getRZ()-50);
                #else
                    _palanca->setNewRotacion(_palanca->getRX(), _palanca->getRY(), _palanca->getRZ()+50);
                #endif
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                #ifdef WEMOTOR
                    _palanca->setNewRotacion(_palanca->getRX(), _palanca->getRY(), _palanca->getRZ()+50);
                #else
                    _palanca->setNewRotacion(_palanca->getRX(), _palanca->getRY(), _palanca->getRZ()-50);
                #endif
            }
        }
    }
    else
    {
        Puerta* _puerta = _puertas.at(pos);

        // Si es una puerta sin llave o palanca asociada
        if(_puerta->getCodigo() == 0)
        {
            //Se acciona o desacciona el mecanismo segun su estado actual
            bool abrir = _puerta->accionar();
            float rot = (constantes.PI_MEDIOS + constantes.PI_CUARTOS);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                //_motora->getEvent("AbrirPuerta")->setVolume(0.8f);
                _motora->getEvent("AbrirPuerta")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                _motora->getEvent("AbrirPuerta")->start();
                _puerta->GirarPuerta(rot);
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _motora->getEvent("CerrarPuerta")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                _motora->getEvent("CerrarPuerta")->start();
                _puerta->GirarPuerta(-rot);
            }
        }
        else
        {
            //Comprueba las llaves que tiene el jugador
            while(i < _jugador->GetLlaves().size() && !coincide)
            {
                if(_jugador->GetLlaves().at(i)->GetCodigoPuerta() == _puerta->getCodigo())
                {
                    //Si el jugador tiene la llave cuyo codigo coincide con la puerta la abre
                    coincide = true;
                }
                i++;
            }
            if(coincide)
            {
                //Se acciona o desacciona el mecanismo segun su estado actual
                bool abrir = _puerta->accionar();
                if(abrir)
                {
                    if(_puerta->getCodigo() == constantes.PUERTA_BOSS && !enSalaBoss)
                    {
                        _motora->getEvent("Nivel1")->stop();
                        _motora->getEvent("Nivel2")->setVolume(0.4);
                        _motora->getEvent("Nivel2")->start(); //Reproducir musica juego
                        enSalaBoss = true;
                        this->CargarBossEnMemoria();
                    }
                    //Se abre/acciona la puerta / el mecanismo
                    _motora->getEvent("AbrirCerradura")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                    _motora->getEvent("AbrirCerradura")->setVolume(0.5);
                    _motora->getEvent("AbrirCerradura")->start();
                    _puerta->GirarPuerta(constantes.PI_MEDIOS + constantes.PI_CUARTOS);
                }
                else
                {
                    //Se cierra/desacciona la puerta / el mecanismo
                    _motora->getEvent("CerrarPuerta")->setPosition(_puerta->getX(), _puerta->getY(), _puerta->getZ());
                    _motora->getEvent("CerrarPuerta")->start();
                    _puerta->GirarPuerta(-(constantes.PI_MEDIOS + constantes.PI_CUARTOS));
                }
            }
        }
        _puerta = nullptr;
    }
}

void Jugando::activarPowerUp()
{
    Constantes constantes;
    int int_cpw = _fisicas->collideColectablePowerup();

    if(int_cpw >= 0 && int_cpw != int_cpw_aux)
    {
        bool locoges = false; //Comprobar si lo puedes coger

        //Efecto del power up (ataque) 0 = vida, 1 = energia, 2 = monedas, 3 = danyo, 4 = defensa
        if(_powerup.at(int_cpw)->GetTipoObjeto() == constantes.VIDA /*&& _jugador->getVida() < 100*/)
        {
            //cout << "PowerUP Vida! TOTAL:" << _jugador->getVida() << endl;
            _jugador->ModificarVida(_powerup.at(int_cpw)->getCantidad());
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->GetTipoObjeto() == constantes.ENERGIA /*&& _jugador->getBarraAtEs() < 100*/)
        {
            //cout << "PowerUP Energia! TOTAL:" << _jugador->getBarraAtEs() << endl;
           _jugador->ModificarBarraAtEs(_powerup.at(int_cpw)->getCantidad());
            locoges = true;
        }
        else if(_powerup.at(int_cpw)->GetTipoObjeto() == constantes.ORO)
        {
            //cout << "Recoges " << _powerup.at(int_cpw)->getCantidad() << " de oro" << endl;
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

    if((_motor->EstaPulsado(LMOUSE_PRESSED_DOWN) || _motor->EstaPulsado(KEY_ESPACIO)) && _jugador->getTimeAt() <= 0.0f)
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
        /*if(atacktime > 0.5f)
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
        }*/

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
    if((_motor->EstaPulsado(RMOUSE_PRESSED_DOWN) || _motor->EstaPulsado(KEY_Q)) && _jugador->getTimeAtEsp() <= 0.0)
    {
        danyo = _jugador->AtacarEspecial();
        _motor->ResetKey(KEY_Q);
        _motor->ResetEvento(RMOUSE_PRESSED_DOWN);
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
            //cout << "tiempo: " << _jugador->getTimeAtEsp() << endl;
            //cout << "existe: " << _motor->getArmaEspecial() << endl;
        }
        /*if(_jugador->getTimeAtEsp() > 0.f && ((int) (_jugador->getTimeAtEsp()*  100) % 10 >= 4) && ((int) (_jugador->getTimeAtEsp()*  100) % 10 <= 4))
        {
            danyo = _jugador->AtacarEspecial();
        }*/
        if(_jugador->getTimeAtEsp() == 1.0f)
        {
            _motor->colorearEnemigo(255,255,255,255,0);
        }
        #ifdef WEMOTOR
            if(_jugador->getTimeAtEsp() <= 0.5f && _motor->getArmaEspecial()) //Zona de pruebas
            {
                 //cout << "SE BORRA" << endl;
                _motor->borrarArmaEspecial();
            }
        #else
            if(_jugador->getTimeAtEsp() <= 0.5f && _motor->getArmaEspecial()) //Zona de pruebas
            {
                _motor->borrarArmaEspecial();
                _motor->colorearJugador(255, 150, 150, 150);
            }
        #endif
    }
}

void Jugando::updateRecorridoPathfinding(Enemigo* _enem)
{
    if(auxiliarPathfinding >= 20 || (contadorEnem == 0 && _enem == _enemPideAyuda))
    {
        _auxiliadores.clear();
        enemDejarDePedirAyuda();
        _destinoPathFinding = nullptr;
        contadorEnem = 0;
        auxiliarPathfinding = 0;

    }
    //Si enem no es nulo se anade a la cola de enemigos _auxiliadores
    if(_enem != nullptr && _enem != _enemPideAyuda )
    {
        _enem->SetContestar(false);
        _auxiliadores.push_back(_enem);
        contadorEnem++;
    }
    //Si no hay sala de destino guardada, se guarda en este momento
    if(_destinoPathFinding == nullptr && _enemPideAyuda != nullptr)
    {
        _destinoPathFinding = _enemPideAyuda->getSala();
    }
    //Ejecucion del pathfinding si hay una sala de destino guardada
    if(_destinoPathFinding != nullptr)
    {
        while(!_auxiliadores.empty())
        {
            if(_destinoPathFinding != _auxiliadores.front()->getSala() && _auxiliadores.front()->GetModo() != 3)
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
    auxiliarPathfinding++;
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
    if(_enemPideAyuda != nullptr)
    {
        //cout << "\e[42m Deja de pedir ayuda \e[0m" << endl;
        _enemPideAyuda->SetPedirAyuda(false);
        _enemPideAyuda = nullptr;
    }
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

void Jugando::AbrirPantallaPuzzle()
{
    ganarPuzzle = false;
    Juego::GetInstance()->estado.CambioEstadoPuzle((int*)cargPuzzles.GetPuzzle(2));
}

void Jugando::AbrirCofre(Cofre* _inter)
{
    //Se abre el cofre (Animacion)
    _inter->setNewRotacion(_inter->getRX(), _inter->getRY(),
    _inter->getRZ() + 80.0);
    _inter->accionar();

    //Crear objeto aleatorio (GUITARRA, ARPA, ORO)
    float x = _inter->getX() + 5;
    float y = _inter->getY();
    float z = _inter->getZ();

    Constantes constantes;
    switch (NumeroAleatorio(constantes.ARPA,constantes.ORO))
    {
        case 7: // ARPA
            CrearObjeto(x,y,z,2,2,2,constantes.ARPA,NumeroAleatorio(15,25));
            break;

        case 8: // GUITARRA
            CrearObjeto(x,y,z,2,2,2,constantes.GUITARRA,NumeroAleatorio(22,32));
            break;
        
        default: // ORO
            CrearPowerUp(x,y,z,constantes.ORO,NumeroAleatorio(20,30));
            break;
    }
}

void Jugando::CrearEnemigoArana()
{
    // Crear Arana
    CofreArana* _eneA = (CofreArana*)_eneCofres.at(
        _cofreP->GetPosArray());

    float x = _eneA->getX();
    float y = _eneA->getY();
    float z = _eneA->getZ();

    _motor->CargarEnemigos(x,y,z,_eneA->GetModelo(),_eneA->GetTextura());//creamos la figura
    _fisicas->crearCuerpo(1,x/2,y/2,z/2,2,_eneA->GetAncho(),
        _eneA->GetAlto(),_eneA->GetLargo(),2,0,0);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0); //Para ataques especiales

   //Cargar sonido evento en una instancia con la id del enemigo como nombre
    std::string nameid = std::to_string(_eneA->getID()); //pasar id a string
    _motora->LoadEvent("event:/SFX/SFX-Muerte Movimiento Esqueleto", nameid);
    _motora->getEvent(nameid)->setPosition(x,y,z);
    _motora->getEvent(nameid)->setVolume(0.5f);
    _motora->getEvent(nameid)->start();

    _enemigos.push_back(move(_eneA));
    _eneA = nullptr;

    // Borrar cofre
    _motor->DibujarCofre(_cofreP->GetPosicionArrayObjetos(), false);
    _cofreP->DesactivarCofre();
}

void Jugando::CargarBossEnMemoria()
{
    float x = _boss->getX();
    float y = _boss->getY();
    float z = _boss->getZ();

    _motor->CargarEnemigos(x,y,z,_boss->GetModelo(), _boss->GetTextura());//creamos la figura
    _fisicas->crearCuerpo(1,x/2,y/2,z/2,2,1,1,1,2,0,0);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0); //Para ataques especiales

    std::string nameid = std::to_string(_boss->getID()); //pasar id a string
    _motora->LoadEvent("event:/SFX/SFX-Muerte Movimiento Esqueleto", nameid);
    _motora->getEvent(nameid)->setPosition(x,y,z);
    _motora->getEvent(nameid)->setVolume(0.5f);
    _motora->getEvent(nameid)->start();

    _enemigos.push_back(move(_boss));
}
