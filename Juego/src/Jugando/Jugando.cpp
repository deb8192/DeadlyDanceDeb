#include "Jugando.hpp"
#include "../Juego.hpp"
#include "../Enemigos/CofreArana.hpp"
#include "../Enemigos/Pollo.hpp"
#include "../Enemigos/Murcielago.hpp"
#include "../Objetos/Puerta.hpp"

Jugando::Jugando(unsigned int nivel,unsigned int tipoJugador,unsigned int dinero, unsigned int slot)
{
    nivelJ = nivel;
    tipoJugadorJ = tipoJugador;
    dineroJ = dinero;
    slotJ = slot;
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

    tam = _zonasRespawn.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonasRespawn.at(i);
    }
    _zonasRespawn.clear();

    tam = _zonasCofre.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonasCofre.at(i);
    }
    _zonasCofre.clear();

    tam = _zonasEscondite.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonasEscondite.at(i);
    }
    _zonasEscondite.clear();

    tam = _zonasOscuras.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonasOscuras.at(i);
    }
    _zonasOscuras.clear();

    tam = _reco_armas.size();
    for(short i=0; i < tam; i++)
    {
        _reco_armas.at(i) = nullptr;
    }
    _reco_armas.clear();

    tam = _llaves.size();
    for(short i=0; i < tam; i++)
    {
        _llaves.at(i) = nullptr;
    }
    _llaves.clear();

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

    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    #ifdef WEMOTOR
        CargarNivel(nivelJ,tipoJugadorJ);
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
    respawnTime = 0.0f;
    lastRespawnTime = respawnTime;
    atacktime = 0.0f;
    // TO DO: Cambia comentado porque ya se ha arreglado la entrada de inputs, quitar al asegurarnos
    //cambia = 0;
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
    _jugador->setDinero(dineroJ);
    _jugador->setVida(_jugador->getVidaIni());
    _jugador->setBarraAtEs(100);
    _jugador->setAtaque(15);
    _jugador->setArma(nullptr);
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
        _motor->girarCamara();
        _fisicas->girarCamara();
        _jugador->girarCamara();
        _motor->ResetKey(KEY_1);
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
    // (Actualizacion: era cosa de los inputs de OpenGL) TO DO: borrar este mega comentario despues de asegurarnos
    if(_motor->EstaPulsado(KEY_E))
    {
        _motor->ResetKey(KEY_E);
        InteractuarNivel();
    }
    // TO DO: Cambia comentado porque ya se ha arreglado la entrada de inputs, quitar al asegurarnos
    /*else
    {
        cambia = 0;
    }*/

}

/************************** InteractuarNivel* ************************
* Detecta las posiciones de los objetos recolectables y de interaccion
* y si está pulsado E interactua y si no lo pinta de color para destacarlo
*/
void Jugando::InteractuarNivel()
{
    //lo siguiente es para saber que objeto colisiona con jugador
    // TO DO: optimizar estas comprobaciones
    int rec_llave = _fisicas->collideLlave();
    int rec_col = _fisicas->collideColectableArma();
    int int_puerta = _fisicas->collidePuerta();
    int int_palanca = _fisicas->collidePalanca();
    int int_cofre = _fisicas->collideAbrirCofre();

    // TO DO: Cambia comentado porque ya se ha arreglado la entrada de inputs, quitar al asegurarnos
    /*if(cambia <= 0)
    {*/
        if (int_puerta >= 0)
        {
            AccionarMecanismo(int_puerta, constantes.PUERTA_OBJ);
            //cambia++;
        }
        else if (int_palanca >= 0)
        {
            AccionarMecanismo(int_palanca, constantes.PALANCA);
            //cambia++;
        }
        else if (int_cofre >= 0)
        {
            AccionarMecanismo(int_cofre, constantes.COFRE_OBJ);
            //cambia++;
        }
        else if (rec_llave >= 0)
        {
            _jugador->setAnimacion(4);
            RecogerLlave(rec_llave);
        }
        else if (rec_col >= 0)
        {
            _jugador->setAnimacion(4);
            RecogerArma(rec_col);
            //cambia++;
        }
        else
        {
            DejarObjeto();
            //cambia++;
        }
   // }
}

/************** Update *************
*  Bucle de actualizacion del juego
*  Entradas:
*
*  Salidas:
* */
void Jugando::Update()
{
    bool colisionaWaypoint = false, waypointComun = false;
    _motor->clearDebug();
    short contadorWaypoints = 0, contadorEnemigos = 0, i = 0;
    INnpc::VectorEspacial posicionTemporal;
    if(lastRespawnTime == 0.0f)
    {
        lastRespawnTime = _controladorTiempo->GetTiempo(2);
    }
    respawnTime = _controladorTiempo->GetTiempo(2) - lastRespawnTime;
    _motora->update(false); //Actualiza el motor de audio
    _sense->update(); //Se actualizan sentidos

    if (_jugador != nullptr && _jugador->EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        _jugador->MuereJugador(); // Animacion de muerte
        DesactivarDebug();
        _motor->cambiarAnimacionJugador(5);//la muerte del jugador tiene este id
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }

    // **********  Se actualiza el respawn si procede  **********
    if(respawnTime - lastRespawnTime >= constantes.TIEMPO_RESPAWN && !enSalaBoss)
    {
        this->RespawnEnemigos();
        lastRespawnTime = respawnTime;
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

    //ESTO ES DE DEBUG PARA ATRAVESAR PAREDES
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

    //Aqui se comprueba si el jugador cambia de sala
    if(!_waypoints.empty() && _waypoints.size() > 0)
    {
        while(!colisionaWaypoint && (unsigned) i < _waypoints.size())
        {
            colisionaWaypoint = _fisicas->CollidePlayerWaypoint(i);
            if(!colisionaWaypoint)
            {
                i++;
            }
        }
    }
    //Ha colisionado con un waypoint
    if(colisionaWaypoint)
    {
        //Se compara si es tipo B (de acceso horizontal)
        if(_waypoints[i]->GetTipo() == constantes.WAYP_B)
        {
            //Si la x del jugador es mayor que la x del waypoint y la x de la sala
            //actual del jugador es menor que la del waypoint, cambia de sala
            if(_jugador->getX() > _waypoints[i]->GetPosicionWaypoint().x)
            {
                if(_jugador->GetSala()->getSizes()[constantes.DOS] < _waypoints[i]->GetPosicionWaypoint().x)
                {
                    //Se busca la nueva sala a la que se accede
                    this->CambiarSalaJugador(i);
                }
            }
            //Si la x del jugador es menor que la x del waypoint y la x de la sala
            //actual del jugador es mayor que la del waypoint, cambia de sala
            else if(_jugador->getX() < _waypoints[i]->GetPosicionWaypoint().x)
            {
                if(_jugador->GetSala()->getSizes()[constantes.DOS] > _waypoints[i]->GetPosicionWaypoint().x)
                {
                    //Se busca la nueva sala a la que se accede
                    this->CambiarSalaJugador(i);
                }
            }
        }
        else if(_waypoints[i]->GetTipo() == constantes.WAYP_C)
        {
            //Si la z del jugador es mayor que la z del waypoint y la z de la sala
            //actual del jugador es menor que la del waypoint, cambia de sala
            if(_jugador->getZ() > _waypoints[i]->GetPosicionWaypoint().z)
            {
                if(_jugador->GetSala()->getSizes()[constantes.CUATRO] < _waypoints[i]->GetPosicionWaypoint().z)
                {
                    //Se busca la nueva sala a la que se accede
                    this->CambiarSalaJugador(i);
                }
            }
            //Si la z del jugador es menor que la z del waypoint y la z de la sala
            //actual del jugador es mayor que la del waypoint, cambia de sala
            else if(_jugador->getZ() < _waypoints[i]->GetPosicionWaypoint().z)
            {
                if(_jugador->GetSala()->getSizes()[constantes.CUATRO] > _waypoints[i]->GetPosicionWaypoint().z)
                {
                    //Se busca la nueva sala a la que se accede
                    this->CambiarSalaJugador(i);
                }
            }
        }
    }

    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        if(_enemigos[i] != nullptr)
        {
            _fisicas->updateEnemigos(_enemigos.at(i)->getFisX(),
                _enemigos.at(i)->getFisY(),
                _enemigos.at(i)->getFisZ(),
                i
            );
        }
    }

    //Si se realiza el ataque se comprueban las colisiones
    if(_jugador->getTimeAtEsp() > 0.0)
    {
        _jugador->AtacarEspecialUpdate(&danyo, _enemigos);
    }
    else if(_jugador->getTimeAt() > 0.0)
    {
        _jugador->CrearCuerpoAtaque();

        // Comprobamos si ataca a la pared
        short paredCol = _fisicas->collideAttackWall();
        if (paredCol >= 0)
        {
            _paredes.at(paredCol)->Borrar(paredCol);
            _paredes.erase(_paredes.begin() + paredCol);
        }
        else // en caso contrario, es a un enemigo
        {
            _jugador->AtacarUpdate(danyo2, _enemigos);
        }
        //_jugador->setTimeAt(0);
    }

    //actualizamos los enemigos
    if(_enemigos.size() > 0)//posiciones interpolacion
    {
        //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;

        for(short i=0;(unsigned)i<_enemigos.size();i++)
        {
            if(_enemigos[i] != nullptr && _enemigos[i]->getVida() > 0)
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
                // TO DO: optimizar
                if (_enemPideAyuda) {
                    _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, true);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                } else {
                    _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, false);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
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
                colisionaWaypoint = false;
                //Aqui se comprueba si el jugador cambia de sala
                while(!colisionaWaypoint && (unsigned) contadorWaypoints < _waypoints.size())
                {
                    colisionaWaypoint = _fisicas->CollideEnemiWaypoint(contadorWaypoints,i);
                    if(!colisionaWaypoint)
                    {
                        contadorWaypoints++;
                    }
                }
                //Ha colisionado con un waypoint
                if(colisionaWaypoint)
                {
                    //Se compara si es tipo B (de acceso horizontal)
                    if(_waypoints[contadorWaypoints]->GetTipo() == constantes.WAYP_B)
                    {
                        //Si la x del jugador es mayor que la x del waypoint y la x de la sala
                        //actual del jugador es menor que la del waypoint, cambia de sala
                        if(_enemigos[i]->getX() > _waypoints[contadorWaypoints]->GetPosicionWaypoint().x)
                        {
                            if(_enemigos[i]->GetSala()->getSizes()[constantes.DOS] < _waypoints[contadorWaypoints]->GetPosicionWaypoint().x)
                            {
                                //Se busca la nueva sala a la que se accede
                                this->CambiarSalaEnemigo(contadorWaypoints,i);
                            }
                        }
                        //Si la x del jugador es menor que la x del waypoint y la x de la sala
                        //actual del jugador es mayor que la del waypoint, cambia de sala
                        else if(_enemigos[i]->getX() < _waypoints[contadorWaypoints]->GetPosicionWaypoint().x)
                        {
                            if(_enemigos[i]->GetSala()->getSizes()[constantes.DOS] > _waypoints[contadorWaypoints]->GetPosicionWaypoint().x)
                            {
                                //Se busca la nueva sala a la que se accede
                                this->CambiarSalaEnemigo(contadorWaypoints,i);
                            }
                        }
                    }
                    else if(_waypoints[contadorWaypoints]->GetTipo() == constantes.WAYP_C)
                    {
                        //Si la z del jugador es mayor que la z del waypoint y la z de la sala
                        //actual del jugador es menor que la del waypoint, cambia de sala
                        if(_enemigos[i]->getZ() > _waypoints[contadorWaypoints]->GetPosicionWaypoint().z)
                        {
                            if(_enemigos[i]->GetSala()->getSizes()[constantes.CUATRO] < _waypoints[contadorWaypoints]->GetPosicionWaypoint().z)
                            {
                                //Se busca la nueva sala a la que se accede
                                this->CambiarSalaEnemigo(contadorWaypoints,i);
                            }
                        }
                        //Si la z del jugador es menor que la z del waypoint y la z de la sala
                        //actual del jugador es mayor que la del waypoint, cambia de sala
                        else if(_enemigos[i]->getZ() < _waypoints[contadorWaypoints]->GetPosicionWaypoint().z)
                        {
                            if(_enemigos[i]->GetSala()->getSizes()[constantes.CUATRO] > _waypoints[contadorWaypoints]->GetPosicionWaypoint().z)
                            {
                                //Se busca la nueva sala a la que se accede
                                this->CambiarSalaEnemigo(contadorWaypoints,i);
                            }
                        }
                    }
                }
                //Se tiene en cuenta al enemigo si esta en modo ataque para situar al nuevo centro del flocking
                if(_enemigos[i]->GetModo() == Enemigo::modosEnemigo::MODO_ATAQUE)
                {
                    contadorEnemigos++;
                    posicionTemporal.vX += _enemigos[i]->getX();
                    posicionTemporal.vY += _enemigos[i]->getY();
                    posicionTemporal.vZ += _enemigos[i]->getZ();

                    //Ya que comprobamos el modo ataque, comprobamos aqui si esta en una sala distinta a la del jugador
                    if(_enemigos[i]->GetSala() != _jugador->GetSala())
                    {
                        short contadorWaypointsJugador = 0;
                        contadorWaypoints = 0;
                        while((unsigned) contadorWaypoints < _enemigos[i]->GetSala()->GetWaypoints().size() && !waypointComun)
                        {
                            while((unsigned) contadorWaypointsJugador < _jugador->GetSala()->GetWaypoints().size() && !waypointComun)
                            {
                                //Si hay un waypoint en comun entre la sala del jugador y la del enemigo, estan en salas contiguas
                                if(_jugador->GetSala()->GetWaypoints()[contadorWaypointsJugador] == _enemigos[i]->GetSala()->GetWaypoints()[contadorWaypoints])
                                {
                                    //Se hace al enemigo ir hacia el waypoint comun y cuando llegue se hace que persiga al jugador
                                    waypointComun = true;
                                    vector <INdrawable::Posiciones> posicionWaypoint;
                                    posicionWaypoint.reserve(constantes.UNO);
                                    posicionWaypoint.push_back(_jugador->GetSala()->GetWaypoints()[contadorWaypointsJugador]->GetPosicionWaypoint());
                                    _enemigos[i]->AnnadirRecorridoAyuda(posicionWaypoint);
                                    _enemigos[i]->SetSala(_jugador->GetSala());
                                }
                                else{contadorWaypointsJugador++;}
                            }
                            contadorWaypointsJugador = 0;
                            contadorWaypoints++;
                        }
                        //Si el jugador no esta en la sala contigua, el enemigo pasa a su estado normal
                        if(!waypointComun)
                        {
                            _enemigos[i]->SetModo(Enemigo::modosEnemigo::MODO_DEFAULT);
                        }
                    }
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

    //Aqui el jugador genera sonidos al caminar
    if(!_jugador->EstaMuerto())
    {
        if((!jugadorInmovil && (_motor->EstaPulsado(KEY_A)
        || _motor->EstaPulsado(KEY_S) || _motor->EstaPulsado(KEY_D) || _motor->EstaPulsado(KEY_W))))
        {
            _jugador->generarSonido(constantes.NUEVE * constantes.SEIS, constantes.CINCO, constantes.UNO);
        }
    }

    //En esta parte muere enemigo
    if(_enemigos.size() > 0)
    {
        //comprobando los _enemigos para saber si estan muertos
        for(short i=0;(unsigned)i<_enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor
            if(_enemigos[i] != nullptr)
            {
                if(_enemigos[i]->estasMuerto() && _enemigos[i]->finalAnimMuerte())
                {
                    //Datos comunes a todos
                    int x = _enemigos[i]->getX();
                    int y = _enemigos[i]->getY();
                    int z = _enemigos[i]->getZ();
                    unsigned short tipoEnemigo = _enemigos[i]->GetTipoEnemigo();

                    if( tipoEnemigo == constantes.GUARDIAN_A ||
                        tipoEnemigo == constantes.GUARDIAN_B)
                    {
                        CrearObjeto(x,y,z,2,2,2,constantes.LLAVE,0);
                    }
                    else if (tipoEnemigo == constantes.ARANA)
                    {
                        AbrirCofre(x,y,z,true);
                    }
                    else if (tipoEnemigo == constantes.BOSS)
                    {
                        Juego::GetInstance()->estado.CambioEstadoGanar();
                    }
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

                    if (_enemigos[i]->GetPedirAyuda()) {
                        enemDejarDePedirAyuda();
                    }

                    //Borrar enemigo
                    _enemigos[i]->BorrarEnemigos(i);
                    EraseEnemigo(i);

                }else{
                    if(_enemigos[i]->estasMuerto()){
                        _enemigos[i]->MuereEnemigo(i);
                    }
                    else
                    {
                        //si no esta muerto ni piensa morirse XD ejecutamos ia
                        _enemigos[i]->UpdateIA();    //Ejecuta la llamada al arbol de comportamiento para realizar la siguiente accion
                    }
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

    for(unsigned int i = 0; i < _cofres.size(); i++)
    {
        _cofres.at(i)->Render(updateTime, resta);
    }
    //*******************************************************************
    //BILLBOARD RECOGER ARMAS
    if(_reco_armas.size() >= 0)
    {
        for(unsigned short i = 0; i < _reco_armas.size(); i++)
        {
            if(_jugador->getArma() != nullptr)
            {
                _motor->mostrarBoardArma(_jugador->getArma()->getAtaque(),_reco_armas[i]->getAtaque(),_jugador->getArma()->GetTipoObjeto(),_reco_armas[i]->GetTipoObjeto(), i);
            }
            else{
                _motor->mostrarBoardArma(10,_reco_armas[i]->getAtaque(),-1,0, i);
            }
        }
    }
    //********************************************************************
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
        else if(_jugador->getArma()->GetTipoObjeto() == constantes.FLAUTA)
        {
            if(_jugador->getTimeAt() == 1.5f)
            {
                proyectilFuera = false;
                mov_weapon_rotX = 180;
                mov_weapon_posX = 2;
                mov_weapon_posZ = 2;
                mov_weapon_posY = 5.5;
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
        if(_enemigos[i])
        {
            _enemigos.at(i)->Render(i, updateTime, resta);
        }
    }

    //Dibujado de ataques enemigos
    for(unsigned int i = 0; i < _enemigos.size(); i++)
    {
        if(_enemigos[i])
        {
            _enemigos.at(i)->RenderAtaque();
        }
    }

    //Dibujado del ataque especial del jugador
    if(_jugador->getTimeAtEsp() > 0.0f)
    {
        _jugador->RenderAtaqueEsp(updateTime, resta);
    }

    //Dibujado zonas
    for(unsigned int i=0; i < _zonasOscuras.size(); i++)
    {
        if(_zonasOscuras[i])
        {
            _zonasOscuras.at(i)->Render();
        }
    }

    for(unsigned int i=0; i < _zonasCofre.size(); i++)
    {
        if(_zonasCofre[i])
        {
            _zonasCofre.at(i)->Render();
        }
    }

    for(unsigned int i=0; i < _zonasEscondite.size(); i++)
    {
        if(_zonasEscondite[i])
        {
            _zonasEscondite.at(i)->Render();
        }
    }

    for(unsigned int i=0; i < _zonasRespawn.size(); i++)
    {
        if(_zonasRespawn[i])
        {
            _zonasRespawn.at(i)->Render();
        }
    }

    //Dibujado waypoints
    for(unsigned int i=0; i < _waypoints.size(); i++)
    {
        if(_waypoints[i])
        {
            _waypoints.at(i)->Render();
        }
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
            //_cofreP->DesactivarCofre();
            AbrirCofre(_cofreP->getX(),_cofreP->getY(),_cofreP->getZ(),true);
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
    _reco_armas = cargador.GetRecolectables();
    _reco_armas.reserve(cargador.GetRecolectablesCapacity());
    _paredes = cargador.GetParedes();
    _paredes.reserve(cargador.GetParedesCapacity());
    _powerup = cargador.GetPowerup();
    _powerup.reserve(cargador.GetPowerupCapacity());
    _zonasOscuras = cargador.GetZonasOscuras();
    _zonasOscuras.reserve(cargador.GetZonasOscurasCapacity());
    _zonasEscondite = cargador.GetZonasEscondite();
    _zonasEscondite.reserve(cargador.GetZonasEsconditeCapacity());
    _zonasCofre = cargador.GetZonasCofre();
    _zonasCofre.reserve(cargador.GetZonasCofreCapacity());
    _zonasRespawn = cargador.GetZonasRespawn();
    _zonasRespawn.reserve(cargador.GetZonasRespawnCapacity());
    _enemigos = cargador.GetEnemigos();
    _enemigos.reserve(cargador.GetEnemigosCapacity());
    _waypoints = cargador.GetWaypoints();
    _waypoints.reserve(cargador.GetWaypointsCapacity());
    ConectarWaypoints();

    //Cargar objetos con el nivel completo
    cargador.CargarCofres(); //Cargamos los cofres del nivel
    probArana = _eneCofres.size();
    _puertas = cargador.GetPuertas();
    _palancas = cargador.GetPalancas();
    _cofres = cargador.GetCofres();
    _eneCofres = cargador.GetEneCofres();
    _boss = cargador.GetBoss();
    _llaves = cargador.GetLlaves();

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
    Recolectable* _rec = new Recolectable(-1,1,1,1,x,y,z,tipoObjeto,0,0);
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
    Recolectable* _rec = new Recolectable(-1,ancho,largo,alto,x,y,z,tipoObjeto,0,0);
    unsigned short accion = 0;
    if (tipoObjeto == constantes.LLAVE)
    {
        _rec->setCodigo(20);
        _llaves.push_back(move(_rec));
        accion = 8;
    }
    else  // ARMAS
    {
        _rec->setAtaque(ataque);
        _reco_armas.push_back(move(_rec));
        accion = 2;
    }
    int posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,ancho,largo,alto,
        _rec->GetModelo(),_rec->GetTextura());
    _rec->SetPosicionArrayObjetos(posicionObjeto);
    _rec = nullptr;
}

/************* RespawnEnemigos **************
 * Funcion que hace aparecer enemigos en las
 * zonas de respawn aleatoriamente o en una
 * sala concreta en funcion del nivel de 
 * dificultad actual del juego
 *                    
*/
void Jugando::RespawnEnemigos()
{
    Constantes constantes;
    int x = 0.0f;
    int y = 0.0f;
    int z = 0.0f; 
    int* zonasSeleccionadas = new int[4];
    int ancho, alto, largo;
    short enemigosRestantes = _enemigos.capacity() - _enemigos.size();
    short i = 0;
    short zonaElegida;
    CargadorBehaviorTrees cargadorIA;

    //Mientras haya hueco en el array de enemigos se crean los cuatro nuevos enemigos
    if(enemigosRestantes > constantes.CERO && !_zonasRespawn.empty())
    {
        while(i < constantes.CUATRO && enemigosRestantes > constantes.CERO)
        {
            enemigosRestantes--;
            short enemigo = this->NumeroAleatorio(0,1);
            /*if(lvDificil)
            {

            }
            else
            {*/
            //Se selecciona una zona de respawn que no haya generado ningun enemigo en el ultimo bucle
            zonaElegida = this->NumeroAleatorio(0, _zonasRespawn.size() -1);
            while(_zonasRespawn[zonaElegida] && (_zonasRespawn[zonaElegida]->getProposito() || _zonasRespawn[zonaElegida]->GetRespawnBoss()))
            {
                zonaElegida++;
                if((unsigned) zonaElegida >= _zonasRespawn.size() || _zonasRespawn[zonaElegida]->GetRespawnBoss())
                {
                    zonaElegida = 0;
                }
            }
            zonasSeleccionadas[i] = zonaElegida;
            i++;
            //}
            
            //Se pone el proposito de la zona como cumplido y se crea el nuevo enemigo
            x = _zonasRespawn[zonaElegida]->getX();
            y = _zonasRespawn[zonaElegida]->getY();
            z = _zonasRespawn[zonaElegida]->getZ(); 
            _zonasRespawn[zonaElegida]->setProposito(true);
            switch(enemigo)
            {
                case 0:
                {
                    ancho = largo = 2;
                    alto = 3;
                    Pollo* _ene = new Pollo(x,y,z, 50); // Posiciones, vida
                    //ia
                    //cargadorIA.cargarBehaviorTreeXml("PolloBT");
                    _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos.back()->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
                    _ene = nullptr;

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Pollo enfadado", nameid);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
                    _motora->getEvent(nameid)->setVolume(0.4f);
                    _motora->getEvent(nameid)->start();
                }
                    break;
                case 1:
                {
                    ancho = largo = 2;
                    alto = 3;
                    Murcielago* _ene = new Murcielago(x,y,z, 75); // Posiciones, vida
                    //ia
                    _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("MurcielagoBT"));
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos.back()->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(_ene);//guardamos el enemigo en el vector

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Murcielago volando", nameid);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
                    _motora->getEvent(nameid)->setVolume(1.0f);
                    _motora->getEvent(nameid)->start();
                }
                break;
            }
            _enemigos.back()->SetEnemigo(enemigo);
            _enemigos.back()->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
            _enemigos.back()->setPosicionesAtaque(x,y,z);
            _enemigos.back()->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
            _enemigos.back()->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
            _enemigos.back()->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
            _enemigos.back()->initPosicionesFisicasAtaque(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
            _enemigos.back()->setBarraAtEs(0);
            _enemigos.back()->definirSala(_zonasRespawn[zonaElegida]->GetSala());//le pasamos la sala en donde esta
            _enemigos.back()->setAtaque(5);
            _enemigos.back()->setArmaEspecial(100);
            _enemigos.back()->setTimeAtEsp(0.0f);
            _enemigos.back()->setDanyoCritico(50);
            _enemigos.back()->setProAtaCritico(10);
            //_enemigos.back()->genemigos.back()rarSonido(20,5);
            _enemigos.back()->setRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
            _enemigos.back()->setVectorOrientacion();
            _enemigos.back()->setNewRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
            _enemigos.back()->setLastRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta

            _motor->CargarEnemigos(x,y,z,_enemigos.back()->GetModelo(),_enemigos.back()->GetTextura());//creamos la figura

            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,ancho,alto,largo,2,0,0);
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0); //Para ataques
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0); //Para ataques especiales
        }
        while(i > constantes.CERO)
        {
            i--;
            _zonasRespawn[zonasSeleccionadas[i]]->setProposito(false);
        }
        delete[] zonasSeleccionadas;
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

void Jugando::CambiarSalaJugador(unsigned short i)
{
    unsigned short j = 0;
    unsigned short k = 0;
    bool cambioRealizado = false;
    //Se comprueban las salidas
    while(!cambioRealizado && j < _jugador->GetSala()->getSalidas().size())
    {
        while(!cambioRealizado && k < _jugador->GetSala()->getSalidas()[j]->GetWaypoints().size())
        {
            if(_waypoints[i] == _jugador->GetSala()->getSalidas()[j]->GetWaypoints()[k])
            {
                _jugador->SetSala(_jugador->GetSala()->getSalidas()[j]);
                cambioRealizado = true;
            }
            else if(!cambioRealizado)
            {
                k++;
            }
        }
        if(!cambioRealizado)
        {
            k = 0;
            j++;
        }
    }
    j=0;
    //Si en las salidas no se haya la nueva sala se comprueban las entradas
    while(!cambioRealizado && j < _jugador->GetSala()->getEntradas().size())
    {
        while(!cambioRealizado && k < _jugador->GetSala()->getEntradas()[j]->GetWaypoints().size())
        {
            if(_waypoints[i] == _jugador->GetSala()->getEntradas()[j]->GetWaypoints()[k])
            {
                _jugador->SetSala(_jugador->GetSala()->getEntradas()[j]);
                cambioRealizado = true;
            }
            else if(!cambioRealizado)
            {
                k++;
            }
        }
        if(!cambioRealizado)
        {
            k = 0;
            j++;
        }
    }
}

void Jugando::CambiarSalaEnemigo(unsigned short n, unsigned short m)
{
    unsigned short j = 0;
    unsigned short k = 0;
    bool cambioRealizado = false;
    //Se comprueban las salidas
    while(!cambioRealizado && j < _enemigos[m]->GetSala()->getSalidas().size())
    {
        while(!cambioRealizado && k < _enemigos[m]->GetSala()->getSalidas()[j]->GetWaypoints().size())
        {
            if(_waypoints[n] == _enemigos[m]->GetSala()->getSalidas()[j]->GetWaypoints()[k])
            {
                _enemigos[m]->SetSala(_enemigos[m]->GetSala()->getSalidas()[j]);
                cambioRealizado = true;
            }
            else if(!cambioRealizado)
            {
                k++;
            }
        }
        if(!cambioRealizado)
        {
            k = 0;
            j++;
        }
    }
    j=0;
    //Si en las salidas no se haya la nueva sala se comprueban las entradas
    while(!cambioRealizado && j < _enemigos[m]->GetSala()->getEntradas().size())
    {
        while(!cambioRealizado && k < _enemigos[m]->GetSala()->getEntradas()[j]->GetWaypoints().size())
        {
            if(_waypoints[n] == _enemigos[m]->GetSala()->getEntradas()[j]->GetWaypoints()[k])
            {
                _enemigos[m]->SetSala(_enemigos[m]->GetSala()->getEntradas()[j]);
                cambioRealizado = true;
            }
            else if(!cambioRealizado)
            {
                k++;
            }
        }
        if(!cambioRealizado)
        {
            k = 0;
            j++;
        }
    }
}

// Para recoger una llave
void Jugando::RecogerLlave(int rec_llave)
{
    Llave* llave = new Llave(_llaves.at(rec_llave)->getCodigo());
    _jugador->AnnadirLlave(llave);
    llave = nullptr;

    //borramos el recolectable de nivel, _motor grafico y motor fisicas
    _llaves.erase(_llaves.begin() + rec_llave);
    _motor->EraseLlave(rec_llave);
    _fisicas->EraseLlave(rec_llave);
}

// Para coger un arma
void Jugando::RecogerArma(int rec_col)
{
    if(_jugador->getArma() == nullptr)//si no tiene arma equipada
    {
        //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)_reco_armas[rec_col];
        _jugador->setArma(_reco_armas[rec_col]);

        //borramos el recolectable de nivel, _motor grafico y motor fisicas
        _reco_armas.erase(_reco_armas.begin() + rec_col);
        _motor->EraseRecoArma(rec_col);
        _fisicas->EraseRecoArma(rec_col);
    }
    else if(_jugador->getArma() != nullptr)//si tiene arma equipada
    {
        //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
        Recolectable* nuRec = new Recolectable(-1,
            _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(),
            _jugador->getArma()->getAlto(),
            _jugador->getX(),_jugador->getY(), _jugador->getZ(),
            _jugador->getArma()->GetTipoObjeto(),0,0);
        nuRec->setAtaque(_jugador->getArma()->getAtaque());

        _jugador->setArma(_reco_armas[rec_col]);

        //borramos el recolectable anterior de nivel, _motor grafico y motor fisicas
        _reco_armas.erase(_reco_armas.begin() + rec_col);
        _motor->EraseRecoArma(rec_col);
        _fisicas->EraseRecoArma(rec_col);

        //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
        int posicionObjeto = _motor->CargarObjetos(2,0,nuRec->getX(), nuRec->getY(),nuRec->getZ(),
            nuRec->getAncho(),nuRec->getLargo(),nuRec->getAlto(),
            nuRec->GetModelo(),nuRec->GetTextura());
        nuRec->SetPosicionArrayObjetos(posicionObjeto);
        _reco_armas.push_back(nuRec);
        nuRec = nullptr;
    }
    atacktime = 0.0f; //Reiniciar tiempo de ataques
}

void Jugando::DejarObjeto()
{
    if(_jugador->getArma() != nullptr)//si tiene arma equipada
    {
        //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
        Recolectable* nuRec = new Recolectable(-1,
            _jugador->getArma()->getAncho(), _jugador->getArma()->getLargo(),
            _jugador->getArma()->getAlto(),
            _jugador->getX(),_jugador->getY(), _jugador->getZ(),
            _jugador->getArma()->GetTipoObjeto(),0,0);
        nuRec->setAtaque(_jugador->getArma()->getAtaque());

        if ((_jugador->getArma()->GetTipoObjeto() == constantes.ARPA) ||
            (_jugador->getArma()->GetTipoObjeto() == constantes.FLAUTA))
        {
            if(proyectilFuera == false)
            {
                _motor->EraseProyectil();
                proyectilFuera = true;
                _motora->getEvent("Flauta")->stop();
                _motora->getEvent("Arpa")->stop();
            }
        }
        _jugador->setArma(nullptr);

        //por ultimo creamos una nueva y actualizamos informacion en motor grafico
        int posicionObjeto = _motor->CargarObjetos(2,0,nuRec->getX(), nuRec->getY(),nuRec->getZ(),
            nuRec->getAncho(),nuRec->getLargo(),nuRec->getAlto(),
            nuRec->GetModelo(),nuRec->GetTextura());
        nuRec->SetPosicionArrayObjetos(posicionObjeto);
        _reco_armas.push_back(nuRec);
        nuRec = nullptr;
    }
}

/*********** AccionarMecanismo ***********
*  Funcion que depende del tipoObj, obtiene el interactuable
*  de la posicion pos de su propio array.
*/
void Jugando::AccionarMecanismo(int pos, const unsigned short tipoObj)
{
    unsigned int i = 0;
    bool coincide = false;

    if (tipoObj == constantes.COFRE_OBJ) // TO DO: repasar todo lo de los cofres al terminar la IA
    {
        _cofreP = _cofres.at(pos);
        if (_cofreP->GetEsArana())
        {
            AbrirPantallaPuzzle();
            // TO DO: guardar pos
        }
        else
        {
            _cofreP->DesactivarCofre(pos);
            AbrirCofre(_cofreP->getX(),_cofreP->getY(),_cofreP->getZ(),false);
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
            {   //Se abre/acciona la puerta / el mecanismo
                _puerta->GirarPuerta(rot, true);
            }
            else
            {   //Se cierra/desacciona la puerta / el mecanismo
                _puerta->GirarPuerta(-rot, true);
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
                _puerta->GirarPuerta(rot, false);
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                _puerta->GirarPuerta(-rot, false);
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
                    _puerta->GirarPuerta((constantes.PI_MEDIOS + constantes.PI_CUARTOS), false);
                }
                else
                {   //Se cierra/desacciona la puerta / el mecanismo
                    _puerta->GirarPuerta(-(constantes.PI_MEDIOS + constantes.PI_CUARTOS), false);
                }
            }
        }
        _puerta = nullptr;
    }
}

void Jugando::activarPowerUp()
{
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
        // TO DO: revisar porque pilla arma especial del motor en vez del jugador
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
    //Si enem no es nulo y es distinto al que pide ayuda se annade a la cola de enemigos _auxiliadores
    if(_enem != nullptr && _enem != _enemPideAyuda )
    {
        _enem->SetContestar(false);
        _auxiliadores.push_back(_enem);
        contadorEnem++;
    }
    //Si no hay sala de destino guardada y si hay enemigo que pide ayuda, se guarda en este momento
    if(_destinoPathFinding == nullptr && _enemPideAyuda != nullptr)
    {
        _destinoPathFinding = _enemPideAyuda->GetSala();
    }
    //Ejecucion del pathfinding si hay una sala de destino guardada
    if(_destinoPathFinding != nullptr)
    {
        while(!_auxiliadores.empty())
        {
            if(_destinoPathFinding != _auxiliadores.front()->GetSala() && _auxiliadores.front()->GetModo() != Enemigo::modosEnemigo::MODO_AUXILIAR_ALIADO)
            {
                Pathfinder* path = Pathfinder::getInstance();
                recorrido = path->encontrarCamino(_auxiliadores.front()->GetSala(), _destinoPathFinding);
                vector<INdrawable::Posiciones> posicionesWaypoints;
                posicionesWaypoints.clear();
                for(unsigned short i = 0; i < recorrido.size(); i++)
                {
                    posicionesWaypoints.push_back(recorrido[i]->GetPosicionWaypoint());
                    _auxiliadores.front()->SetSala(_destinoPathFinding);
                }
                _auxiliadores.front()->AnnadirRecorridoAyuda(posicionesWaypoints);
            }
            else if(_destinoPathFinding == _auxiliadores.front()->GetSala() && _auxiliadores.front()->GetModo() != Enemigo::modosEnemigo::MODO_ATAQUE)
            {
                _auxiliadores.front()->SetModo(Enemigo::modosEnemigo::MODO_ATAQUE);
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

void Jugando::AbrirCofre(float x, float y, float z, bool esArana)
{
    unsigned short objeto = 0;
    unsigned short minArpa = 15;
    unsigned short minGuitar = 22;
    unsigned short minFlauta = 13;

    // El cofre suelta armas normales y oro, la arana suelta armas mas fuertes
    if (esArana)
    {
        objeto = NumeroAleatorio(constantes.ARPA,constantes.ULTIMA_ARMA);
        minArpa = 22;
        minGuitar = 31;
        minFlauta = 25;
    }
    else
    {
        objeto = NumeroAleatorio(constantes.ARPA,constantes.ORO);
        x = x + 5;
    }

    switch (objeto)
    {
        case 7: // ARPA
            CrearObjeto(x,y,z,2,2,2,constantes.ARPA,NumeroAleatorio(minArpa,25));
            break;

        case 8: // GUITARRA
            CrearObjeto(x,y,z,2,2,2,constantes.GUITARRA,NumeroAleatorio(minGuitar,32));
            break;

        case 9: // FLAUTA
            CrearObjeto(x,y,z,2,2,2,constantes.FLAUTA,NumeroAleatorio(minFlauta,23));
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

    _eneA->SetIdCofre(_cofreP->getID());

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
    //_motor->DibujarCofre(_cofreP->GetPosicionArrayObjetos(), false);
    // TO DO: pasar pos correcta
    _cofreP->BorrarCofre(0);
}

void Jugando::CargarBossEnMemoria()
{
    float x = _boss->getX();
    float y = _boss->getY();
    float z = _boss->getZ();

    short tam = _enemigos.size();
    cargador.SetVectorEnemigos(_enemigos);
    for(short i=0; i < tam; i++)
    {
        _enemigos.at(i) = nullptr;
        _motor->EraseTodosEnemigos(i);
        _fisicas->EraseTodosEnemigos(i);
    }
    cargador.BorrarVectorEnemigosBossActivado();

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

void Jugando::CambiarAranyaPorCofre(int idC, float x,float y, float z, 
    unsigned int posArrayArana, Sala* sala)
{
    unsigned int pos = 0;
    bool posNula = false;
    while (!posNula)
    {
        if (_cofres.at(pos) != nullptr)
        {
            pos++;
        }
        else
        {
            posNula = true;
        }
    }

    Cofre* _cofre = new Cofre(idC, pos,
        x, y, z,
        constantes.COFRE_OBJ, posArrayArana,
        sala);

    _cofres.at(pos) = move(_cofre);
    _cofre = nullptr;
}