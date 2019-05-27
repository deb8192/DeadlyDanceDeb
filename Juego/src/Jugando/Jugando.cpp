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

    // Punteros a clases singleton
    _controladorTiempo = nullptr;
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;
    _motor = nullptr;
    _interfaz = nullptr;

    int tam = _enemigos.size();
    for(int i=0; i < tam; i++)
    {
        _enemigos.at(i) = nullptr;
    }
    _enemigos.clear();

    tam = _eneCofres.size();
    for(int i=0; i < tam; i++)
    {
        _eneCofres.at(i) = nullptr;
    }
    _eneCofres.clear();

    tam = _zonasRespawn.size();
    for(int i=0; i < tam; i++)
    {
        _zonasRespawn.at(i) = nullptr;
    }
    _zonasRespawn.clear();

    tam = _zonasCofre.size();
    for(int i=0; i < tam; i++)
    {
        _zonasCofre.at(i) = nullptr;
    }
    _zonasCofre.clear();

    tam = _zonasEscondite.size();
    for(int i=0; i < tam; i++)
    {
        _zonasEscondite.at(i) = nullptr;
    }
    _zonasEscondite.clear();

    tam = _zonasOscuras.size();
    for(int i=0; i < tam; i++)
    {
        _zonasOscuras.at(i) = nullptr;
    }
    _zonasOscuras.clear();

    tam = _reco_armas.size();
    for(int i=0; i < tam; i++)
    {
        _reco_armas.at(i) = nullptr;
    }
    _reco_armas.clear();

    tam = _llaves.size();
    for(int i=0; i < tam; i++)
    {
        _llaves.at(i) = nullptr;
    }
    _llaves.clear();

    tam = _powerup.size();
    for(int i=0; i < tam; i++)
    {
        _powerup.at(i) = nullptr;
    }
    _powerup.clear();

    tam = _waypoints.size();
    for(int i=0; i < tam; i++)
    {
        _waypoints.at(i) = nullptr;
    }
    _waypoints.clear();

    tam = _palancas.size();
    for(int i=0; i < tam; i++)
    {
        _palancas.at(i) = nullptr;
    }
    _palancas.clear();

    tam = _puertas.size();
    for(int i=0; i < tam; i++)
    {
        _puertas.at(i) = nullptr;
    }
    _puertas.clear();

    tam = _cofres.size();
    for(int i=0; i < tam; i++)
    {
        _cofres.at(i) = nullptr;
    }
    _cofres.clear();

    // Liberar memoria
    tam = _auxiliadores.size();
    for(int i=0; i < tam; i++)
    {
        delete _auxiliadores.at(i);
    }
    _auxiliadores.clear();
    contadorWaypointsJugador = 0;
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
    nivelJ = 8;
    #ifdef WEMOTOR
        CargarNivel(nivelJ,tipoJugadorJ);
    #else
        CargarNivel(6, constantes.HEAVY);
    #endif
    _controladorTiempo = Times::GetInstance();

    tiempoInicioNivel = _controladorTiempo->GetTiempo(1);//se coge la marca de tiempo de iniciar el nivel para calcular la puntuacion

    _auxiliadores.reserve(_enemigos.size());
    recorrido.reserve(_enemigos.size());

    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
    _motor->BorrarCargando();

    //Crear Sprites
    CrearSprites();

    //si esta puesto el nivel 1 suena la bienvenida del nivel 1, sino del 2
    if(nivelJ == 8)
    {
        _motora->getEvent("MuerteBienvenida1")->start();
        _motora->getEvent("pasoscharcos")->start();
        _motora->getEvent("pasoscharcos")->pause();
        _motora->getEvent("pasosmadera")->start();
        _motora->getEvent("pasosmadera")->pause();
        _motora->getEvent("pasostierra")->start();
        _motora->getEvent("pasostierra")->pause();
        _motora->getEvent("pasospiedra")->start();
        _motora->getEvent("pasospiedra")->pause();
    }
    else
    {
        _motora->getEvent("MuerteBienvenida2")->start();
        _motora->getEvent("pasospiedra")->start();
        _motora->getEvent("pasospiedra")->pause();

    }
      startPlayTime = _controladorTiempo->GetTiempo(1);
}

void Jugando::ValoresPorDefecto()
{
    //id = 0;
    reiniciando = false;
    puzzleResuelto = false;
    estarDebil = false;
    salaPenultima = false;
    meAtacan = false;
    poderEmpezar = false;
    enCentroSalaBoss = false;
    bocadillo = false;
    respawnMO = false;
    oirMuerteOmni = 0.0f;
    startPlayTime = 0.0f;
    // lvDificil = false; TO DO: no esta implementado
    estarAtacado = 0;
    estarFuerte = false;

    drawTime = 0.0f;
    lastDrawTime = drawTime;
    respawnTime = 0.0f;
    lastRespawnTime = respawnTime;
    atacktime = 0.0f;
    _enemPideAyuda = nullptr;
    _destinoPathFinding = nullptr;
    danyo = 0;
    danyo2 = 0;
    contadorEnem = 0;
    int_cpw_aux = 0;
    enSalaBoss = false;
    auxiliarPathfinding = 0;

    //Valores para el centro de las bandadas en el flocking
    posicionMediaEnemigos.vX = INT_MAX;
    posicionMediaEnemigos.vY = INT_MAX;
    posicionMediaEnemigos.vZ = INT_MAX;

    // Activamos la interfaz
    _interfaz->activar();
    desactivarColisionesJugador = false;
    contadorWaypointsJugador = 0;
    proyectilFuera = true;
    algunboardActivo = false;
    esconderArana = false;
    ganarPuzzle = false;
    _cofreP = nullptr;

    mov_weapon_posX = 0;
    mov_weapon_posY = 0;
    mov_weapon_posZ = 0;
    mov_weapon_rotX = 0;
    mov_weapon_rotY = 0;
    mov_weapon_rotZ = 0;
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
    /*if(_motor->EstaPulsado(KEY_1))
    {
        _motor->girarCamara();
        _fisicas->girarCamara();
        _jugador->girarCamara();
        _motor->ResetKey(KEY_1);
    }*/

    /* *********** Teclas para probar cosas *************** */

    /*if (_motor->EstaPulsado(KEY_K))
    {
        _motor->ResetKey(KEY_K);
        //_jugador->setVida(0);
        Juego::GetInstance()->estado.CambioEstadoGanar(GetTiempoPasadoNivel());

    }*/

    //para modo debug
    /*if(_motor->EstaPulsado(KEY_G_DEBUG))
    {
        _motor->activarDebugGrafico();
        _motor->ResetKey(KEY_G_DEBUG);
    }*/

    // Desactivar fisicas jugador
    if(_motor->EstaPulsado(KEY_U))
    {
        desactivarColisionesJugador = !desactivarColisionesJugador;
        _motor->ResetKey(KEY_U);
        poderEmpezar = true;
       if(nivelJ==8){_motora->getEvent("MuerteBienvenida1")->stop();}
    }

    // Multicamara
    if(_motor->EstaPulsado(KEY_C))
    {
        _motor->ResetKey(KEY_C);
        _motor->CambiarCamara();
    }


    // Debug para probar cofres
    /*if(_motor->EstaPulsado(KEY_I))
    {
        cargador.TrasladarJugadorACofres();
        _motor->ResetKey(KEY_I);
    }*/

    // Debug para probar esconder arana cofre
    /*if(_motor->EstaPulsado(KEY_Z))
    {
        esconderArana = !esconderArana;
        _motor->ResetKey(KEY_Z);
    }*/

    if(_motor->EstaPulsado(KEY_B))
    {
        unsigned short desplaza = 170;
        _jugador->setPosiciones(242+desplaza, 0, 490);
        _jugador->setNewPosiciones(242+desplaza, 0, 490);
        _jugador->initPosicionesFisicas((242+desplaza)/2, 0/2, 490/2);
        enSalaBoss = true;
        enCentroSalaBoss = true;
        poderEmpezar = true;

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
    int int_puerta = _fisicas->collidePuerta();
    if (int_puerta >= 0)
    {
        AccionarMecanismo(int_puerta, constantes.PUERTA_OBJ);
    }
    else
    {
        int int_palanca = _fisicas->collidePalanca();
        if (int_palanca >= 0)
        {
            AccionarMecanismo(int_palanca, constantes.PALANCA);
        }
        else
        {
            int int_cofre = _fisicas->collideAbrirCofre();
            if (int_cofre >= 0)
            {
                AccionarMecanismo(int_cofre, constantes.COFRE_OBJ);
            }
            else
            {
                int rec_llave = _fisicas->collideLlave();
                if (rec_llave >= 0)
                {
                    _jugador->setAnimacion(4);
                    RecogerLlave(rec_llave);
                }
                else
                {
                    int rec_col = _fisicas->collideColectableArma();
                    if (rec_col >= 0)
                    {
                        _jugador->setAnimacion(4);
                        RecogerArma(rec_col);
                    }
                    else
                    {
                        DejarObjeto();
                    }
                }
            }
        }
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
    //esto es para que espere 5 segundos antes de reanudar/cortar sonidos al cambiar de sala
   if(oirMuerteOmni!= 0.0f && _controladorTiempo->CalcularTiempoPasado(oirMuerteOmni)/1000 > 5.0f)
   {
        meAtacan = false;
        estarAtacado = 0;
        estarDebil = false;
        estarFuerte = false;
        oirMuerteOmni = 0.0f;
   }

    if(_jugador->GetSala()->getPosicionEnGrafica() == 0 ||
     _jugador->GetSala()->getPosicionEnGrafica() == 1 ||
     _jugador->GetSala()->getPosicionEnGrafica() == 5 ||
     _jugador->GetSala()->getPosicionEnGrafica() == 8||
     _jugador->GetSala()->getPosicionEnGrafica() == 9)
    {
        _motora->getEvent("AmbienteViento")->resume();
    }
    else
    {
        _motora->getEvent("AmbienteViento")->pause();
    }


   if(_controladorTiempo->CalcularTiempoPasado(startPlayTime)/1000 > 20.0f && nivelJ == 8)
   {
       //para que pueda moverse al decir el mensaje de bienvenida del nivel nuevo
       if((enSalaBoss && enCentroSalaBoss) || !enSalaBoss)
        {
            poderEmpezar = true;
        }
   }
   else if(nivelJ == 7)
   {
       //para que pueda moverse en el nivel antiguo
        poderEmpezar = true;
   }
   if(enSalaBoss && !poderEmpezar)
   {
       enCentroSalaBoss = _jugador->moverseAlCentroDeLaSala(&coordenadasCentroSalaBoss);
       if(enCentroSalaBoss)
       {
            int i = _puertas.size() - constantes.UNO;
            bool puertaBossCerrada = false;
            bool abrir = false;
            float rot = 0.0f;
            while(i >= constantes.CERO && !puertaBossCerrada)
            {
                if(_puertas[i]->getCodigo() == constantes.PUERTA_BOSS)
                {
                    Puerta* _puerta = _puertas.at(i);
                    abrir = _puerta->accionar();
                    _puerta->accionar();
                    abrir = _puerta->accionar();
                    rot = (constantes.PI_MEDIOS + constantes.PI_CUARTOS);
                    if(abrir)
                    {   //Se abre/acciona la puerta / el mecanismo
                        _puerta->GirarPuerta(rot, true);
                    }
                    else
                    {   //Se cierra/desacciona la puerta / el mecanismo
                        _puerta->GirarPuerta(-rot, true);
                    }
                    _puerta = nullptr;
                    puertaBossCerrada = true;
                }
                else
                {
                    i--;
                }
            }
            poderEmpezar = true;
       }
   }

    bool colisionaWaypoint = false, waypointComun = false, cercaJugador = false;
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
        ComprobarBorrarProyectil();
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
    if(poderEmpezar)
    {
        _jugador->movimiento(jugadorInmovil,
        _motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W)
        );
    }

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
    //cout << "UPD: 1"<<endl;

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

    //Este bloque se da si el enemigo esta en el proceso de invulnerabilidad
    if(_jugador->getTimeInvulnerable() > 0.0f)
    {
        if(_jugador->getTimeInvulnerable() == 1.0f)
        {
            //Si es la primera vez que entra al bucle de invulnerabilidad debe guardar el tiempo actual desde el reloj
            _jugador->setLastTimeInvulnerable(_controladorTiempo->GetTiempo(2));
        }
        float tiempoActual = 0.0f, tiempoInvulnerable = 0.0f;
        tiempoActual = _controladorTiempo->GetTiempo(2);
        tiempoInvulnerable = _jugador->getTimeInvulnerable();
        tiempoInvulnerable -= (tiempoActual - _jugador->getLastTimeInvulnerable());
        if(tiempoActual > _jugador->getLastTimeInvulnerable())
        {
            //Si no es la primera vez que entra al bucle de invulnerabilidad, tiempoActual debe ser mayor que lastTimeInvulnerable
            //por lo que guardamos en lastTimeInvulnerable a tiempoActual
            _jugador->setLastTimeInvulnerable(tiempoActual);
        }
        _jugador->setTimeInvulnerable(tiempoInvulnerable);
    }
    else
    {
        if(_jugador->GetInvulnerabilidad())
        {
            _jugador->SetInvulnerabilidad(constantes.FALSE);
        }
    }


    //actualizamos los enemigos
    if(_enemigos.size() > 0)//posiciones interpolacion
    {
        //float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;

        for(short i=0;(unsigned)i<_enemigos.size();i++)
        {
            cercaJugador = false;
            INnpc::VectorEspacial posicionMediaNula;
            posicionMediaNula.vX = INT_MAX;
            posicionMediaNula.vY = INT_MAX;
            posicionMediaNula.vZ = INT_MAX;
            if(_enemigos[i] != nullptr && _enemigos[i]->getVida() > 0)
            {
                // Se coloca la posicionMedia de las bandadas
                if(_enemigos[i]->GetModo() == Enemigo::modosEnemigo::MODO_ATAQUE)
                {
                    /*if(_enemigos[i]->GetSala() == _jugador->GetSala())
                    {
                    _enemigos[i]->SetPosicionComunBandada(posicionMediaEnemigos);
                    }
                    else
                    {*/
                        _enemigos[i]->SetPosicionComunBandada(posicionMediaNula);
                    //}
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
                // TO DO: optimizar beha
                if(_enemigos[i]->GetSala() == _jugador->GetSala() || _enemigos[i]->GetTipoEnemigo() >= constantes.BOSS || _enemigos[i]->GetTipoEnemigo() >= constantes.GUARDIAN_A  || _enemigos[i]->GetTipoEnemigo() >= constantes.GUARDIAN_B)
                {
                    if(_enemigos[i]->GetTipoEnemigo() >= constantes.BOSS && _enemigos[i]->GetRespawnBoss())
                    {
                        this->RespawnEnemigosBoss();
                    }
                    if((enSalaBoss && poderEmpezar && enCentroSalaBoss) || !enSalaBoss)
                    {
                        if (_enemPideAyuda) {
                        _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, true);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                        } else {
                            _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, false);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                        }
                    }
                    short paredCol = _enemigos[i]->GetParedRota();
                    if(paredCol >= 0)
                    {
                        _paredes[paredCol]->Borrar(paredCol);
                        _paredes.erase(_paredes.begin() + paredCol);
                        _enemigos[i]->SetParedRota(constantes.MENOS_UNO);
                    }

                    if(estarAtacado >= 2)
                    {
                        meAtacan = true;
                    }

                    if(_enemigos[i]->GetModo() == Enemigo::modosEnemigo::MODO_ATAQUE)
                    {
                        estarAtacado++;
                        if(!meAtacan)
                        {
                            if(_enemigos[i]->GetTipoEnemigo() == 0)
                            {
                                _motora->getEvent("MuertePaseas")->stop();
                                _motora->getEvent("MuerteEstasDebil")->stop();
                                _motora->getEvent("MuerteRespawn1")->stop();
                                _motora->getEvent("MuerteRespawn2")->stop();
                                _motora->getEvent("MuertePerseguido2")->start();
                            }
                            else
                            {
                                _motora->getEvent("MuertePaseas")->stop();
                                _motora->getEvent("MuerteEstasDebil")->stop();
                                _motora->getEvent("MuerteRespawn1")->stop();
                                _motora->getEvent("MuerteRespawn2")->stop();
                                _motora->getEvent("MuertePerseguido1")->start();
                            }
                        }
                        meAtacan = true;
                    }

                }
                else
                {
                    if(!enSalaBoss)
                    {
                        cercaJugador = this->ComprobarEnemigoSalaContiguaJugador(i);
                        if(cercaJugador)
                        {
                            if (_enemPideAyuda) {
                            _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, true);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                            } else {
                                _enemigos[i]->UpdateBehavior(&i, (int*)_jugador, _zonasOscuras, _zonasEscondite, false);     //Actualiza el comportamiento segun el nodo actual del arbol de comportamiento
                            }
                        }
                    }
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
                //Este bloque se da si el Boss esta en el proceso de moverse
                if(_enemigos[i]->getTimeMoverse() > 0.0f)
                {
                    if(_enemigos[i]->getTimeMoverse() == 1.5f)
                    {
                        //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeMoverse(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoMoverse = 0.0f;
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoMoverse = _enemigos[i]->getTimeMoverse();
                    tiempoMoverse -= (tiempoActual - _enemigos[i]->getLastTimeMoverse());
                    if(tiempoActual > _enemigos[i]->getLastTimeMoverse())
                    {
                        //Si no es la primera vez que entra al bucle de moverse, tiempoActual debe ser mayor que lastTimeMoverse
                        //por lo que guardamos en lastTimeMoverse a tiempoActual
                        _enemigos[i]->setLastTimeMoverse(tiempoActual);
                    }
                    _enemigos[i]->setTimeMoverse(tiempoMoverse);
                }
                //Este bloque se da si el Boss esta en el proceso de atacar
                if(_enemigos[i]->getTimeAt() > constantes.CERO)
                {
                    if(_enemigos[i]->GetEnemigo() == constantes.TRAVORNIO && _enemigos[i]->getTimeAt() == constantes.TIEMPO_EMBESTIR)
                    {
                        //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeAt(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoAtacar = 0.0f, tiempoAntiguo = _enemigos[i]->getLastTimeAt();
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoAtacar = _enemigos[i]->getTimeAt();
                    tiempoAtacar -= (tiempoActual - tiempoAntiguo);
                    if(tiempoActual > tiempoAntiguo)
                    {
                        //Si no es la primera vez que entra al bucle de atacar, tiempoActual debe ser mayor que lastTimeMoverse
                        //por lo que guardamos en lastTimeAt a tiempoActual
                        _enemigos[i]->setLastTimeAt(tiempoActual);
                    }
                    _enemigos[i]->setTimeAt(tiempoAtacar);
                }
                //Este bloque se da si el Boss esta en el proceso de ataque especial
                if(_enemigos[i]->getTimeAtEsp() > constantes.CERO)
                {
                    if(_enemigos[i]->GetEnemigo() == constantes.TRAVORNIO && _enemigos[i]->getTimeAtEsp() >= constantes.TIEMPO_ATESP_TRAVORNIO)
                    {
                        //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeAtEsp(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoAtaqueEspecial = 0.0f, tiempoAntiguo = _enemigos[i]->getLastTimeAtEsp();
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoAtaqueEspecial = _enemigos[i]->getTimeAtEsp();
                    tiempoAtaqueEspecial -= (tiempoActual - tiempoAntiguo);
                    if(tiempoActual > tiempoAntiguo)
                    {
                        //Si no es la primera vez que entra al bucle de atacar, tiempoActual debe ser mayor que lastTimeMoverse
                        //por lo que guardamos en lastTimeAtEsp a tiempoActual
                        _enemigos[i]->setLastTimeAtEsp(tiempoActual);
                    }
                    _enemigos[i]->setTimeAtEsp(tiempoAtaqueEspecial);
                }
                //Este bloque se da si el Boss esta en el proceso de defenderse
                if(_enemigos[i]->getTimeDefenderse() > constantes.CERO)
                {
                    if(_enemigos[i]->getTimeDefenderse() == constantes.TIEMPO_DEFENSA)
                    {
                        //Si es la primera vez que entra al bucle de merodear debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeDefenderse(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoDefenderse = 0.0f, tiempoAntiguo = _enemigos[i]->getLastTimeDefenderse();
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoDefenderse = _enemigos[i]->getTimeDefenderse();
                    tiempoDefenderse -= (tiempoActual - tiempoAntiguo);
                    if(tiempoActual > tiempoAntiguo)
                    {
                        //Si no es la primera vez que entra al bucle de atacar, tiempoActual debe ser mayor que lastTimeDefenderse
                        //por lo que guardamos en lastTimeDefenderse a tiempoActual
                        _enemigos[i]->setLastTimeDefenderse(tiempoActual);
                    }
                    _enemigos[i]->setTimeDefenderse(tiempoDefenderse);
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
                //Este bloque se da si el enemigo esta en el proceso de invulnerabilidad
                if(_enemigos[i]->getTimeInvulnerable() > 0.0f)
                {
                    if(_enemigos[i]->getTimeInvulnerable() == 1.5f)
                    {
                        //Si es la primera vez que entra al bucle de invulnerabilidad debe guardar el tiempo actual desde el reloj
                        _enemigos[i]->setLastTimeInvulnerable(_controladorTiempo->GetTiempo(2));
                    }
                    float tiempoActual = 0.0f, tiempoInvulnerable = 0.0f;
                    tiempoActual = _controladorTiempo->GetTiempo(2);
                    tiempoInvulnerable = _enemigos[i]->getTimeInvulnerable();
                    tiempoInvulnerable -= (tiempoActual - _enemigos[i]->getLastTimeInvulnerable());
                    if(tiempoActual > _enemigos[i]->getLastTimeInvulnerable())
                    {
                        //Si no es la primera vez que entra al bucle de invulnerabilidad, tiempoActual debe ser mayor que lastTimeInvulnerable
                        //por lo que guardamos en lastTimeInvulnerable a tiempoActual
                        _enemigos[i]->setLastTimeInvulnerable(tiempoActual);
                    }
                    _enemigos[i]->setTimeInvulnerable(tiempoInvulnerable);
                }
                else
                {
                    if(_enemigos[i]->GetInvulnerabilidad())
                    {
                        _enemigos[i]->SetInvulnerabilidad(constantes.FALSE);
                    }
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
                    //Solo tiene en cuenta el flocking para los enemigos que estan en la sala del jugador
                    if(_enemigos[i]->GetSala() == _jugador->GetSala())
                    {
                        contadorEnemigos++;
                        posicionTemporal.vX += _enemigos[i]->getX();
                        posicionTemporal.vY += _enemigos[i]->getY();
                        posicionTemporal.vZ += _enemigos[i]->getZ();
                    }
                    //Ya que comprobamos el modo ataque, comprobamos aqui si esta en una sala distinta a la del jugador
                    if(_enemigos[i]->GetSala() != _jugador->GetSala())
                    {
                        waypointComun = this->ComprobarEnemigoSalaContiguaJugador(i);
                        if(waypointComun)
                        {
                            //Se hace al enemigo ir hacia el waypoint comun y cuando llegue se hace que persiga al jugador
                            vector <INdrawable::Posiciones> posicionWaypoint;
                            posicionWaypoint.reserve(constantes.UNO);
                            posicionWaypoint.push_back(_jugador->GetSala()->GetWaypoints()[contadorWaypointsJugador]->GetPosicionWaypoint());
                            _enemigos[i]->AnnadirRecorridoAyuda(posicionWaypoint);
                            _enemigos[i]->SetSala(_jugador->GetSala());
                        }
                        else
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
    //cout << "UPD: 13"<<endl;
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
    if(_jugador->getVida() <= 30)
    {
        if(!estarDebil)
        {
            _motora->getEvent("MuerteEstasDebil")->start();

            if(_jugador->GetSala()->getPosicionEnGrafica() == 14)
            {
                _enemigos[0]->ventajaSound(_jugador->GetTipoJug());
                _enemigos[0]->stopPasearSound(_jugador->GetTipoJug());
            }
        }

        estarDebil = true;
        estarFuerte = false;
        _motora->getEvent("MuertePaseas")->stop();
    }
    else
    {
        if(_jugador->GetSala()->getPosicionEnGrafica() != 0 &&
           _jugador->GetSala()->getPosicionEnGrafica() != 14 &&
           _jugador->GetSala()->getPosicionEnGrafica() != 22)
        {
            if(!estarFuerte)
            {
                _motora->getEvent("MuertePaseas")->start();
            }
            estarFuerte = true;
        }
        else if(_jugador->GetSala()->getPosicionEnGrafica() == 14)
        {
            if(!estarFuerte)
            {
                _enemigos[0]->pasearSound(_jugador->GetTipoJug());
            }
            estarFuerte = true;
        }

        estarDebil = false;
        _motora->getEvent("MuerteEstasDebil")->stop();
        _enemigos[0]->stopVentajaSound(_jugador->GetTipoJug());

    }


    if((nivelJ == 8 && _jugador->GetSala()->getPosicionEnGrafica() == 13) ||
       (nivelJ == 7 && _jugador->GetSala()->getPosicionEnGrafica() == 21))
    {
        if(!salaPenultima)
        {
            //frases muerte omnipresente antes de la batalla final
            _motora->getEvent("MuertePenultima")->start();
            //para que no se escuchen el resto de frases
        }
        salaPenultima = true;
        estarDebil = true;
        estarFuerte = true;
        meAtacan = true;
        respawnMO = true;
        _motora->getEvent("MuerteEstasDebil")->stop();
        _motora->getEvent("MuertePaseas")->stop();
    }

    if((nivelJ == 8 && _jugador->GetSala()->getPosicionEnGrafica() == 14) ||
       (nivelJ == 7 && _jugador->GetSala()->getPosicionEnGrafica() == 22))
    {
        _motora->getEvent("MuerteEstasDebil")->stop();
        _motora->getEvent("MuertePaseas")->stop();
        _motora->getEvent("MuertePenultima")->stop();
        _motora->getEvent("MuerteRespawn1")->stop();
        _motora->getEvent("MuerteRespawn2")->stop();
        _motora->getEvent("MuertePerseguido1")->stop();
        _motora->getEvent("MuertePerseguido2")->stop();
    }

    bool cercaJugador = false;
    /* *********** Teclas para probar cosas *************** */
    // Bajar vida
    /*if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        _jugador->ModificarVida(-20);
    }*/

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
            _jugador->generarSonido(constantes.TAMANYO_ONDA, constantes.CINCO, constantes.UNO);

            if(nivelJ == 8)
            {
                if(_jugador->GetSala()->getPosicionEnGrafica() ==0)
                {
                    _motora->getEvent("pasospiedra")->resume();
                }
                if(_jugador->GetSala()->getPosicionEnGrafica() ==1)
                {
                    _motora->getEvent("pasospiedra")->resume();
                }
                if(_jugador->GetSala()->getPosicionEnGrafica() ==14)
                {
                    _motora->getEvent("pasospiedra")->resume();
                }
                else if(_jugador->GetSala()->getPosicionEnGrafica() == 3)
                {
                    _motora->getEvent("pasoscharcos")->resume();
                }
                else if(_jugador->GetSala()->getPosicionEnGrafica() == 9)
                {
                    _motora->getEvent("pasosmadera")->resume();
                }
                else
                {
                    _motora->getEvent("pasostierra")->resume();
                }

            }
            else if(nivelJ == 7)
            {
                _motora->getEvent("pasospiedra")->resume();
            }

        }
        else
        {
            if(nivelJ == 8)
            {
                _motora->getEvent("pasospiedra")->pause();
                _motora->getEvent("pasoscharcos")->pause();
                _motora->getEvent("pasosmadera")->pause();
                _motora->getEvent("pasostierra")->pause();

            }
            else if(nivelJ == 7)
            {
                _motora->getEvent("pasospiedra")->pause();
            }

        }
    }

    //En esta parte muere enemigo
    if(_enemigos.size() > 0)
    {
        //comprobando los _enemigos para saber si estan muertos
        for(short i=0;(unsigned)i<_enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor
            cercaJugador = false;
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
                        CrearObjeto(x,y,z,4,4,2,constantes.LLAVE_BOSS,0);
                        _motor->borrarBoardGuardian();
                    }
                    else if (tipoEnemigo == constantes.ARANA)
                    {
                        CofreArana* _cofA = (CofreArana*)_enemigos[i];
                        delete _cofres.at(_cofA->GetPosMotorCofre());
                        _cofres.at(_cofA->GetPosMotorCofre())=nullptr;

                        AbrirCofre(x,y,z,true);
                    }
                    else if (tipoEnemigo >= constantes.BOSS)
                    {

                        Juego::GetInstance()->estado.CambioEstadoGanar(GetTiempoPasadoNivel());
                    }
                    else
                    {
                        unsigned short tipoObj = NumeroAleatorio(constantes.VIDA,constantes.ORO);
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
                        _motor->cambiarAnimacion(5,i,_enemigos[i]->GetEstadoMuerte());
                    }
                    //si no esta muerto ni piensa morirse XD ejecutamos ia
                    else
                    {
                        if(_enemigos[i]->GetSala() == _jugador->GetSala())
                        {
                            _enemigos[i]->UpdateIA();    //Ejecuta la llamada al arbol de comportamiento para realizar la siguiente accion
                        }
                        else
                        {
                            if(!enSalaBoss)
                            {
                                cercaJugador = this->ComprobarEnemigoSalaContiguaJugador(i);
                                if(cercaJugador)
                                {
                                    _enemigos[i]->UpdateIA();    //Ejecuta la llamada al arbol de comportamiento para realizar la siguiente accion
                                }
                            }
                        }
                    }
                }

                // Si hay una arana activada y tiene que esconderse
                if (esconderArana)
                {
                    if (_enemigos.at(i)->GetTipoEnemigo() == constantes.ARANA)
                    {
                        CofreArana* _eneA = (CofreArana*)_enemigos.at(i);

                        if (_eneA->GetActivada())
                        {
                            _eneA->SetActivada(false);

                            if (_enemigos.at(i)->GetPedirAyuda())
                                enemDejarDePedirAyuda();

                            Cofre* _cofre = new Cofre(_eneA->GetIdCofre(), _eneA->GetPosMotorCofre(),
                                _eneA->GetPosObsCofre(),
                                _eneA->getX(), _eneA->getY(), _eneA->getZ(),
                                constantes.COFRE_OBJ, _eneA->GetPosArana(), _eneA->GetSala());

                            _cofres.at(_eneA->GetPosMotorCofre()) = move(_cofre);
                            _cofre = nullptr;

                            //Eliminar sonido
                            std::string nameid = std::to_string(_eneA->getID()); //pasar id a string
                            _motora->getEvent(nameid)->stop();

                            // Borrar grafico y fisicas de la arana
                            _motor->EraseEnemigo(i);
                            _fisicas->EraseEnemigo(i);

                            CofreArana* _eneNew = new CofreArana(*_eneA);

                            // La arana vuelve al array de cofres aranas
                            _eneCofres.at(_eneNew->GetPosArana()) = _eneNew;
                            _eneA = nullptr;
                            _enemigos.erase(_enemigos.begin() + i);//begin le suma las posiciones
                            esconderArana = false;
                        }
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
        if (_cofres.at(i) != nullptr)
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

    //Update animaciones sprites
    _motor->updateAnimaSprite();

    //Armas
    if(_jugador->getArma() != nullptr)
    {
        unsigned short tipoArma = _jugador->getArma()->GetTipoObjeto();
        //Ataque Animacion
        if ((tipoArma == constantes.GUITARRA1) || (tipoArma == constantes.GUITARRA2) ||
            (tipoArma == constantes.GUITARRA3))
        {
            if(_jugador->getTimeAt() == 2.0f)
            {
                //actualizar posicion de animaciones
                unsigned short tipoArma = _jugador->getArma()->GetTipoObjeto();

                switch (tipoArma)
                {
                    case 10:
                    armaSeleccionada=0;
                    break;
                    case 11:
                    armaSeleccionada=1;
                    break;
                    case 12:
                    armaSeleccionada=2;
                    break;
                }

                _motor->cambiarAnimacion(7,armaSeleccionada,1);
            }
            else if(_jugador->getTimeAt() > 0.0f && _jugador->getTimeAt() <= 2.0f)
            {
                _motor->desactivarObjeto(_motor->getArmaenEscena());
                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
            }
            else
            {
                _motor->activarObjeto(_motor->getArmaenEscena());
                mov_weapon_posX=-2.0;
                mov_weapon_posZ=-1.5;
                if(_jugador->GetTipoJug() == constantes.BAILAORA)mov_weapon_posZ=-2.6;
                mov_weapon_posY=5.0;
                mov_weapon_rotX=90;
                mov_weapon_rotY=0;
                mov_weapon_rotZ=0;
                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
            }
        }
        else if ((tipoArma == constantes.ARPA1) || (tipoArma == constantes.ARPA2) ||
            (tipoArma == constantes.ARPA3))
        {
            if(_jugador->getTimeAt() == 2.0f)
            {
                _motor->desactivarObjeto(_motor->getArmaenEscena());
                proyectilFuera = false;

                switch (tipoArma)
                {
                   case 7:
                    armaSeleccionada=6;
                   break;
                   case 8:
                    armaSeleccionada=7;
                   break;
                   case 9:
                    armaSeleccionada=8;
                   break;
                }

                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
                _motor->cambiarAnimacion(7,armaSeleccionada,1);
            }
            else if(_jugador->getTimeAt() > 0.0f && _jugador->getTimeAt() <= 2.0f)
            {
                _motor->desactivarObjeto(_motor->getArmaenEscena());
                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
            }
            else if(_jugador->getTimeAt() <= 0.0f)
            {
                if(proyectilFuera == false)
                {
                    _motor->EraseProyectil();
                    proyectilFuera = true;
                }
                _motor->activarObjeto(_motor->getArmaenEscena());
                mov_weapon_posX=-2.0;
                mov_weapon_posZ=-0.5;
                if(_jugador->GetTipoJug() == constantes.BAILAORA)mov_weapon_posZ=-1.8;
                mov_weapon_posY=4.5;
                mov_weapon_rotX=90;
                mov_weapon_rotY=0;
                mov_weapon_rotZ=0;
            }
        }
        else if ((tipoArma == constantes.FLAUTA1) || (tipoArma == constantes.FLAUTA2) ||
            (tipoArma == constantes.FLAUTA3))
        {
            if(_jugador->getTimeAt() == 2.0f)
            {
                _motor->desactivarObjeto(_motor->getArmaenEscena());
                proyectilFuera = false;

                switch (tipoArma)
                {
                   case 13:
                    armaSeleccionada=3;
                   break;
                   case 14:
                    armaSeleccionada=4;
                   break;
                   case 15:
                    armaSeleccionada=5;
                   break;
                }

                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
                _motor->cambiarAnimacion(7,armaSeleccionada,1);
            }
            else if(_jugador->getTimeAt() > 0.0f && _jugador->getTimeAt() <= 2.0f)
            {
                _motor->desactivarObjeto(_motor->getArmaenEscena());
                _motor->MoverArma(armaSeleccionada,_jugador->getX(),_jugador->getY(),_jugador->getZ());
                _motor->RotarArma(armaSeleccionada,_jugador->getRX(),_jugador->getRY()-180,_jugador->getRZ());
            }
            else if(_jugador->getTimeAt() <= 0.0f)
            {
                if(proyectilFuera == false)
                {
                    _motor->EraseProyectil();
                    proyectilFuera = true;
                }
                _motor->activarObjeto(_motor->getArmaenEscena());
                mov_weapon_posX=-0.7;
                if(_jugador->GetTipoJug() == constantes.BAILAORA)mov_weapon_posX=-1.8;
                mov_weapon_posZ=-0.5;
                if(_jugador->GetTipoJug() == constantes.BAILAORA)mov_weapon_posZ=-1.6;
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

    //Dibujado boards puertas
    algunboardActivo = false;
    for(unsigned int i=0; i<_puertas.size(); i++)
    {
        float distx = _jugador->getX() - _puertas[i]->getX();
        float disty = _jugador->getY() - _puertas[i]->getY();
        float distz = _jugador->getZ() - _puertas[i]->getZ();
        if(distx > -15.0f && distx < 15.0f && disty > -15.0f && disty < 15.0f && distz > -15.0f && distz < 15.0f)
        {
            if(!_puertas[i]->getAccionado()) //puerta no esta abierta
            {
                if(_puertas[i]->getCodigo() == 20) //puerta del boss
                {
                    if(!bocadillo)
                    {
                        _motora->getEvent("Dialogo1")->start();
                        bocadillo = true;
                    }
                    _motor->mostrarBoardPuerta(2);
                }
                else if(_puertas[i]->getCodigo() > 0 && _puertas[i]->getCodigo() < 10 )//puerta de llave
                {
                    if(!bocadillo)
                    {
                        _motora->getEvent("Dialogo1")->start();
                        bocadillo = true;
                    }
                    _motor->mostrarBoardPuerta(0);
                }
                else if(_puertas[i]->getCodigo() >= 10 && _puertas[i]->getCodigo() < 20 )//puerta de palanca
                {
                    if(!bocadillo)
                    {
                        _motora->getEvent("Dialogo1")->start();
                        bocadillo = true;
                    }
                    _motor->mostrarBoardPuerta(1);
                }
                else if(_puertas[i]->getCodigo() == 0)
                {
                    if(!bocadillo)
                    {
                        _motora->getEvent("Dialogo1")->start();
                        bocadillo = true;
                    }
                    _motor->mostrarBoardPuerta(3);
                }

                algunboardActivo = true;
            }
        }
    }
    if(!algunboardActivo)
    {
        _motor->desactivarBoardPuertas();
        bocadillo = false;
    }

    //Dibujado de los enemigos
    for(unsigned short i = 0; i < _enemigos.size(); i++)
    {
        if(_enemigos[i])
        {
            if(_enemigos.at(i)->GetTipoEnemigo() == constantes.GUARDIAN_A || _enemigos.at(i)->GetTipoEnemigo() == constantes.GUARDIAN_B)
            {
                _motor->mostrarBoardGuardian(_enemigos.at(i)->getX()+1.5f,_enemigos.at(i)->getY()+13.0f,_enemigos.at(i)->getZ());
            }
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

        // Limpiamos todos los vectores y punteros de Jugando
        LimpiarJuego();
        CargarNivel(nivelJ,tipoJugadorJ);

        reiniciando = false;
    }
    else if (puzzleResuelto)
    {
        if (ganarPuzzle)
        {
            _motora->getEvent("VictoriaPuzzle")->start();

            _cofreP->DesactivarCofre();
            AbrirCofre(_cofreP->getX(),_cofreP->getY(),_cofreP->getZ(),true);
            _cofreP = nullptr;
        }
        else
        {
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
    _motor->BorrarScena();//borramos la scena

    //pre limpiamos
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
    if(nivelJ == 7)
    {
        _motora->getEvent("Nivel11")->start(); //Reproducir musica juego
        _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente
        _motora->getEvent("AmbienteLava")->setPosition(145.0f,0.0f,18.0f);
        _motora->getEvent("AmbienteLava")->start(); //Reproducir ambiente
    }
    else if(nivelJ == 8)
    {
        _motora->getEvent("Nivel21")->start(); //Reproducir musica juego

        _motora->LoadEvent("event:/Ambientes/Ambiente-Gota de agua","AmbienteGota",0);
        _motora->getEvent("AmbienteGota")->setPosition(335.0,0.0,69.0);
        _motora->getEvent("AmbienteGota")->start();
        _motora->LoadEvent("event:/Ambientes/Ambiente-sonido de rio","AmbienteRio",0);
        _motora->getEvent("AmbienteRio")->setPosition(335.0,0.0,69.0);
        _motora->getEvent("AmbienteRio")->start();
        _motora->LoadEvent("event:/Ambientes/Ambiente-sonido de cascada","AmbienteCascada",0);
        _motora->getEvent("AmbienteCascada")->setPosition(140.0,0.0,329.0);
        _motora->getEvent("AmbienteCascada")->start();

        _motora->getEvent("AmbienteViento")->start();
        _motora->getEvent("AmbienteViento")->pause();
    }

    ValoresPorDefecto();

    //esta ya todo ejecutamos ia y interpolado
    return true;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearJugador()
{
    _jugador = cargador.GetJugador();
    ValoresPorDefectoJugador();

    _motor->CargarJugador(_jugador->getX(),_jugador->getY(), _jugador->getZ(),
        _jugador->GetEscalado(), _jugador->GetEscalado(), _jugador->GetEscalado(),
        _jugador->GetModelo(),_jugador->GetTextura(),_jugador->GetFps(),_jugador->GetAnimacion());

    if(_jugador->GetTipoJug() == constantes.BAILAORA)
    {
        _motor->CargarArma(0,_jugador->GetModeloArma(0),_jugador->GetFpsArma(0),_jugador->GetAnimacionArma(0),_jugador->GetEscaladoArma(0),_jugador->GetTexturaArma(0));
        _motor->CargarArma(1,_jugador->GetModeloArma(1),_jugador->GetFpsArma(1),_jugador->GetAnimacionArma(1),_jugador->GetEscaladoArma(1),_jugador->GetTexturaArma(1));
        _motor->CargarArma(2,_jugador->GetModeloArma(2),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(2),_jugador->GetEscaladoArma(2),_jugador->GetTexturaArma(2));
        _motor->CargarArma(3,_jugador->GetModeloArma(3),_jugador->GetFpsArma(3),_jugador->GetAnimacionArma(3),_jugador->GetEscaladoArma(3),_jugador->GetTexturaArma(3));
        _motor->CargarArma(4,_jugador->GetModeloArma(4),_jugador->GetFpsArma(4),_jugador->GetAnimacionArma(4),_jugador->GetEscaladoArma(4),_jugador->GetTexturaArma(4));
        _motor->CargarArma(5,_jugador->GetModeloArma(5),_jugador->GetFpsArma(5),_jugador->GetAnimacionArma(5),_jugador->GetEscaladoArma(5),_jugador->GetTexturaArma(5));
        _motor->CargarArma(6,_jugador->GetModeloArma(6),_jugador->GetFpsArma(6),_jugador->GetAnimacionArma(6),_jugador->GetEscaladoArma(6),_jugador->GetTexturaArma(6));
        _motor->CargarArma(7,_jugador->GetModeloArma(7),_jugador->GetFpsArma(7),_jugador->GetAnimacionArma(7),_jugador->GetEscaladoArma(7),_jugador->GetTexturaArma(7));
        _motor->CargarArma(8,_jugador->GetModeloArma(8),_jugador->GetFpsArma(8),_jugador->GetAnimacionArma(8),_jugador->GetEscaladoArma(8),_jugador->GetTexturaArma(8));
    }

    /*_motor->CargarArma(_jugador->GetModeloArma(2),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(2),_jugador->GetEscaladoArma(1));//carga arma 1 Guitarra-2
    _motor->CargarArma(_jugador->GetModeloArma(3),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(3),_jugador->GetEscaladoArma(1));//carga arma 2 Guitarra-3
    _motor->CargarArma(_jugador->GetModeloArma(4),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(4),_jugador->GetEscaladoArma(1));//carga arma 3 Flauta-1
    _motor->CargarArma(_jugador->GetModeloArma(5),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(5),_jugador->GetEscaladoArma(1));//carga arma 4 Flauta-2
    _motor->CargarArma(_jugador->GetModeloArma(6),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(6),_jugador->GetEscaladoArma(1));//carga arma 5 Flauta-3
    _motor->CargarArma(_jugador->GetModeloArma(7),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(7),_jugador->GetEscaladoArma(1));//carga arma 6 Arpa-1
    _motor->CargarArma(_jugador->GetModeloArma(8),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(8),_jugador->GetEscaladoArma(1));//carga arma 7 Arpa-2
    _motor->CargarArma(_jugador->GetModeloArma(9),_jugador->GetFpsArma(2),_jugador->GetAnimacionArma(9),_jugador->GetEscaladoArma(1));//carga arma 8 Arpa-3*/


    _motor->CargarArmaEspecial(_jugador->getX(),_jugador->getY(),
        _jugador->getZ(), _jugador->getRutaArmaEsp(),_jugador->getRutaTexturaArmaEsp());

    //Cargar sistema de particulas para el jugador
    _motor->CargarParticulasAccion(_jugador->getX(),_jugador->getY(),_jugador->getZ(),0,10,0, 1.0f, 30, 5.0f, 1.0f, "assets/images/CuraVidaParticle.png");
    _motor->CargarParticulasAccion(_jugador->getX(),_jugador->getY(),_jugador->getZ(),0,10,0, 1.0f, 30, 5.0f, 1.0f, "assets/images/CuraEnergParticle.png");
    _motor->CargarParticulasAccion(_jugador->getX(),_jugador->getY(),_jugador->getZ(),0,10,0, 1.0f, 30, 5.0f, 1.0f, "assets/images/DineroParticle.png");

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
    if (tipoObjeto == constantes.LLAVE_BOSS)
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

/************* RespawnEnemigosBoss **************
 * Funcion que hace aparecer enemigos en las
 * zonas de respawn de la sala del boss cuando
 * este invoca a los enemigos.
 *
*/
void Jugando::RespawnEnemigosBoss()
{
    int x = 0.0f;
    int y = 0.0f;
    int z = 0.0f;
    int ancho, alto, largo;
    int enemigosRestantes = this->NumeroAleatorio(constantes.TRES, constantes.SEIS);
    int numeroEnemigos = enemigosRestantes;
    int* zonasSeleccionadas = new int[enemigosRestantes];
    short i = 0;
    short zonaElegida;

    //Mientras haya hueco en el array de enemigos se crean los cuatro nuevos enemigos
    if(enemigosRestantes > constantes.CERO && !_zonasRespawn.empty())
    {
        while(i < numeroEnemigos && enemigosRestantes > constantes.CERO)
        {
            enemigosRestantes--;
            short enemigo = this->NumeroAleatorio(0,1);
            //Se selecciona una zona de respawn que no haya generado ningun enemigo en el ultimo bucle
            zonaElegida = this->NumeroAleatorio(_zonasRespawn.size() - constantes.SEIS, _zonasRespawn.size() - constantes.UNO);
            while(_zonasRespawn[zonaElegida] && (_zonasRespawn[zonaElegida]->getProposito() || !_zonasRespawn[zonaElegida]->GetRespawnBoss()))
            {
                zonaElegida++;
                if((unsigned) zonaElegida >= _zonasRespawn.size() || !_zonasRespawn[zonaElegida]->GetRespawnBoss())
                {
                    zonaElegida = _zonasRespawn.size() - constantes.SEIS;
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
                    _ene->setArbol(cargador.GetArbolPollo());
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos[_enemigos.size() - constantes.UNO]->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
                    _ene = nullptr;

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Pollo enfadado", nameid, 1);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
                    _motora->getEvent(nameid)->start();
                }
                    break;
                case 1:
                {
                    ancho = largo = 2;
                    alto = 3;
                    Murcielago* _ene = new Murcielago(x,y,z, 75); // Posiciones, vida
                    //ia
                    _ene->setArbol(cargador.GetArbolMurcielago());
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos.back()->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
                    _ene = nullptr;

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Murcielago volando", nameid, 1);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
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
            _enemigos.back()->SetModo(Enemigo::modosEnemigo::MODO_ATAQUE);
            _enemigos.back()->RespawnNoise();
            _motor->CargarEnemigos(x,y,z,_enemigos.back()->GetModelo(),_enemigos.back()->GetTextura(), false,_enemigos.back()->GetAnimacion(),_enemigos.back()->GetFps());//creamos la figura

            _enemigos[0]->invocaSound();
            _enemigos[0]->stopPasearSound(_jugador->GetTipoJug());
            _enemigos[0]->stopVentajaSound(_jugador->GetTipoJug());

            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,ancho,alto,largo,2,0,0,false);
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0,false); //Para ataques
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0,false); //Para ataques especiales
        }
        while(i > constantes.CERO)
        {
            i--;
            _zonasRespawn[zonasSeleccionadas[i]]->setProposito(false);
        }
        delete[] zonasSeleccionadas;
        zonasSeleccionadas = nullptr;
        _enemigos.front()->SetRespawnBoss(false);
    }
    else
    {
        _enemigos.front()->SetRespawnBoss(false);
    }
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
    int x = 0.0f;
    int y = 0.0f;
    int z = 0.0f;
    int* zonasSeleccionadas = new int[4];
    int ancho, alto, largo;
    short enemigosRestantes = _enemigos.capacity() - _enemigos.size();
    short i = 0;
    short zonaElegida;

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

            int tipoEne = 0;

            switch(enemigo)
            {
                case 0:
                {
                    tipoEne = 1;
                    ancho = largo = 2;
                    alto = 3;
                    Pollo* _ene = new Pollo(x,y,z, 50); // Posiciones, vida
                    //ia
                    _ene->setArbol(cargador.GetArbolPollo());
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos.back()->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
                    _ene = nullptr;

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Pollo enfadado", nameid, 1);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
                    _motora->getEvent(nameid)->start();
                }
                    break;
                case 1:
                {
                    tipoEne = 2;
                    ancho = largo = 2;
                    alto = 3;
                    Murcielago* _ene = new Murcielago(x,y,z, 75); // Posiciones, vida
                    //ia
                    _ene->setArbol(cargador.GetArbolMurcielago());
                    _ene->setVelocidadMaxima(1.0f);
                    _ene->setID(_enemigos.back()->getID() + 1);//le damos el id unico en esta partida al enemigo
                    _enemigos.push_back(_ene);//guardamos el enemigo en el vector

                    //Cargar sonido evento en una instancia con la id del enemigo como nombre
                    std::string nameid = std::to_string(_enemigos.back()->getID()); //pasar id a string
                    _motora->LoadEvent("event:/SFX/SFX-Murcielago volando", nameid, 1);
                    _motora->getEvent(nameid)->setPosition(x,y,z);
                    _motora->getEvent(nameid)->start();
                }
                break;
            }

            if(tipoEne == 2)
            {
                if(!respawnMO && _zonasRespawn[zonaElegida]->GetSala()->getPosicionEnGrafica() == _jugador->GetSala()->getPosicionEnGrafica())
                {
                    _motora->getEvent("MuerteEstasDebil")->stop();
                    _motora->getEvent("MuertePaseas")->stop();
                    _motora->getEvent("MuerteRespawn2")->start();
                }
            }
            else if(tipoEne != 0)
            {
                if(!respawnMO && _zonasRespawn[zonaElegida]->GetSala()->getPosicionEnGrafica() == _jugador->GetSala()->getPosicionEnGrafica())
                {
                    _motora->getEvent("MuerteEstasDebil")->stop();
                    _motora->getEvent("MuertePaseas")->stop();
                    _motora->getEvent("MuerteRespawn1")->start();
                }
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
            _enemigos.back()->RespawnNoise();

            _motor->CargarEnemigos(x,y,z,_enemigos.back()->GetModelo(),_enemigos.back()->GetTextura(), false,_enemigos.back()->GetAnimacion(),_enemigos.back()->GetFps());//creamos la figura

            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,ancho,alto,largo,2,0,0,false);
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0,false); //Para ataques
            _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0,false); //Para ataques especiales
        }
        while(i > constantes.CERO)
        {
            i--;
            _zonasRespawn[zonasSeleccionadas[i]]->setProposito(false);
        }
        delete[] zonasSeleccionadas;
        zonasSeleccionadas = nullptr;
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
                //tiempo de espera para que no se corten frases de la muerte al cambiar sala
                oirMuerteOmni = _controladorTiempo->GetTiempo(1);
                //para poder cambiar de sonido de pasos segun que sala estamos hay que pausarlos
                _motora->getEvent("pasospiedra")->pause();
                _motora->getEvent("pasoscharcos")->pause();
                _motora->getEvent("pasosmadera")->pause();
                _motora->getEvent("pasostierra")->pause();

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
               //tiempo de espera para que no se corten frases de la muerte al cambiar sala
                oirMuerteOmni = _controladorTiempo->GetTiempo(1);
                //para poder cambiar de sonido de pasos segun que sala estamos hay que pausarlos
                _motora->getEvent("pasospiedra")->pause();
                _motora->getEvent("pasoscharcos")->pause();
                _motora->getEvent("pasosmadera")->pause();
                _motora->getEvent("pasostierra")->pause();
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

//Comprueba si el enemigo esta en la sala contigua
bool Jugando::ComprobarEnemigoSalaContiguaJugador(unsigned int n)
{
    bool waypointComun = false;
    int contadorWaypoints = 0;
    contadorWaypointsJugador = 0;
    while((unsigned) contadorWaypoints < _enemigos[n]->GetSala()->GetWaypoints().size() && !waypointComun)
    {
        while((unsigned) contadorWaypointsJugador < _jugador->GetSala()->GetWaypoints().size() && !waypointComun)
        {
            //Si hay un waypoint en comun entre la sala del jugador y la del enemigo, estan en salas contiguas
            if(_jugador->GetSala()->GetWaypoints()[contadorWaypointsJugador] == _enemigos[n]->GetSala()->GetWaypoints()[contadorWaypoints])
            {
                //Se hace al enemigo ir hacia el waypoint comun y cuando llegue se hace que persiga al jugador
                waypointComun = true;
                return waypointComun;
            }
            else{contadorWaypointsJugador++;}
        }
        contadorWaypointsJugador = 0;
        contadorWaypoints++;
    }
    //Si llega aqui, el jugador no esta en la sala contigua
    return false;
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
    _motora->getEvent("getkey")->start();
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
        ComprobarBorrarProyectil();

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
    _motora->getEvent("Recoger")->start();
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

        ComprobarBorrarProyectil();
        _jugador->setArma(nullptr);

        //por ultimo creamos una nueva y actualizamos informacion en motor grafico
        int posicionObjeto = _motor->CargarObjetos(2,0,nuRec->getX(), nuRec->getY(),nuRec->getZ(),
            nuRec->getAncho(),nuRec->getLargo(),nuRec->getAlto(),
            nuRec->GetModelo(),nuRec->GetTextura());
        nuRec->SetPosicionArrayObjetos(posicionObjeto);
        _reco_armas.push_back(nuRec);
        nuRec = nullptr;
        _motora->getEvent("Soltar")->start();
    }
}

// Se llama al dejar el objeto, intercambiarlo por otro y cuando muere el jugador
void Jugando::ComprobarBorrarProyectil()
{
    if (_jugador->getArma() != nullptr)
    {
        unsigned short tipoArma = _jugador->getArma()->GetTipoObjeto();
        if ((tipoArma == constantes.ARPA1) || (tipoArma == constantes.FLAUTA1) ||
            (tipoArma == constantes.ARPA2) || (tipoArma == constantes.FLAUTA2) ||
            (tipoArma == constantes.ARPA3) || (tipoArma == constantes.FLAUTA3))
        {
            if(proyectilFuera == false)
            {
                _motor->EraseProyectil();
                proyectilFuera = true;
                _motora->getEvent("Flauta")->stop();
                _motora->getEvent("Arpa")->stop();
            }
        }
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
        }
        else
        {
            _cofreP->DesactivarCofre();

            //_motor->cambiarAnimacion(6,pos,1);
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
            _motora->getEvent("PalancaUse")->start();
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
                if(_jugador->GetLlaves().at(i) && _jugador->GetLlaves().at(i)->GetCodigoPuerta() == _puerta->getCodigo())
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
                        if(nivelJ == 7)
                        {
                            _motora->getEvent("Nivel11")->stop();
                            _motora->getEvent("Nivel12")->start(); //Reproducir musica juego
                        }
                        else if(nivelJ == 8)
                        {
                            _motora->getEvent("Nivel21")->stop();
                            _motora->getEvent("Nivel22")->start(); //Reproducir musica juego
                        }

                        enSalaBoss = true;
                        poderEmpezar = false;
                        _jugador->SetSala(_jugador->GetSala()->getSalidas()[0]);
                        coordenadasCentroSalaBoss.vX = _jugador->GetSala()->getSizes()[2];
                        coordenadasCentroSalaBoss.vY = _jugador->GetSala()->getSizes()[3];
                        coordenadasCentroSalaBoss.vZ = _jugador->GetSala()->getSizes()[4];
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
            _motor->IniciarParticulasAccion(0,_jugador->getX()+1.0f,_jugador->getY()+2.0f,_jugador->getZ(),0.5f);
            locoges = true;
            _motora->getEvent("getvida")->start();
        }
        else if(_powerup.at(int_cpw)->GetTipoObjeto() == constantes.ENERGIA /*&& _jugador->getBarraAtEs() < 100*/)
        {
            //cout << "PowerUP Energia! TOTAL:" << _jugador->getBarraAtEs() << endl;
           _jugador->ModificarBarraAtEs(_powerup.at(int_cpw)->getCantidad());
           _motor->IniciarParticulasAccion(1,_jugador->getX()+1.0f,_jugador->getY()+2.0f,_jugador->getZ(),0.5f);
            locoges = true;
            _motora->getEvent("getmana")->start();
        }
        else if(_powerup.at(int_cpw)->GetTipoObjeto() == constantes.ORO)
        {
            //cout << "Recoges " << _powerup.at(int_cpw)->getCantidad() << " de oro" << endl;
            _jugador->ModificarDinero(_powerup.at(int_cpw)->getCantidad());
            _motor->IniciarParticulasAccion(2,_jugador->getX()+1.0f,_jugador->getY()+2.0f,_jugador->getZ(),0.5f);
            locoges = true;
            _motora->getEvent("getgold")->start();
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

    if((_motor->EstaPulsado(LMOUSE_PRESSED_DOWN) || _motor->EstaPulsado(KEY_ESPACIO)) && _jugador->getTimeAt() <= 0.0f && poderEmpezar)
    {
        *danyo = _jugador->Atacar(0);
        _motor->ResetKey(KEY_ESPACIO);
        _motor->ResetEvento(LMOUSE_DOWN);
        //atacktime = 1.5f;
        _jugador->setTimeAt(2.0f);
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
    if((_motor->EstaPulsado(RMOUSE_PRESSED_DOWN) || _motor->EstaPulsado(KEY_Q)) && _jugador->getTimeAtEsp() <= 0.0 && poderEmpezar)
    {
        _jugador->setAnimacion(3);
        _jugador->resetContador();
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
    if(_destinoPathFinding != nullptr && _jugador->GetSala() == _destinoPathFinding)
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
                //delete path;
            }
            else if(_destinoPathFinding == _auxiliadores.front()->GetSala() && _auxiliadores.front()->GetModo() != Enemigo::modosEnemigo::MODO_ATAQUE)
            {
                _auxiliadores.front()->SetModo(Enemigo::modosEnemigo::MODO_ATAQUE);
            }
            contadorEnem--;
            _auxiliadores.erase(_auxiliadores.begin());
        }
    }
    else if(_destinoPathFinding != nullptr)
    {
        auxiliarPathfinding = 19;
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
    _motora->getEvent("AparecePuzzle")->start();
    ganarPuzzle = false;
    _motor->DeshabilitarDinero();
    Juego::GetInstance()->estado.CambioEstadoPuzle((int*)cargPuzzles.GetPuzzle(4));
}

void Jugando::AbrirCofre(float x, float y, float z, bool esArana)
{

    _motora->getEvent("AbrirCerradura")->start();
    unsigned short objeto = 0;
    unsigned short minArpa = 15;
    unsigned short minGuitar = 22;
    unsigned short minFlauta = 13;
    x = x + 5;

    //PRESENTACION
    switch (objetopresentacion) {
        case 0:
            CrearObjeto(x,y,z,3,4,2,constantes.FLAUTA3,NumeroAleatorio(23,23));
            break;
        case 2:
            CrearObjeto(x,y,z,3,4,2,constantes.ARPA1,NumeroAleatorio(26,26));
            break;
        case 4:
            CrearObjeto(x,y,z,3,4,2,constantes.GUITARRA1,NumeroAleatorio(31,31));
            break;
        default:
            CrearPowerUp(x,y,z,constantes.ORO,NumeroAleatorio(20,30));
            break;
    }
    objetopresentacion++;

    // if(objetopresentacion > 5)
    // {
    //     //***********
    //
    //     // El cofre suelta armas normales y oro, la arana suelta armas mas fuertes
    //     if (esArana)
    //     {
    //         objeto = NumeroAleatorio(constantes.ARPA1,constantes.ULTIMA_ARMA);
    //         minArpa = 22;
    //         minGuitar = 31;
    //         minFlauta = 25;
    //     }
    //     else
    //     {
    //         objeto = NumeroAleatorio(constantes.ORO,constantes.ULTIMA_ARMA+2);
    //     }
    //
    //     switch (objeto)
    //     {
    //         case 7: // ARPA
    //             CrearObjeto(x,y,z,3,4,2,constantes.ARPA1,NumeroAleatorio(minArpa,25));
    //             break;
    //         case 8:
    //             CrearObjeto(x,y,z,3,4,2,constantes.ARPA2,NumeroAleatorio(minArpa,25));
    //             break;
    //         case 9:
    //             CrearObjeto(x,y,z,3,4,2,constantes.ARPA3,NumeroAleatorio(minArpa,25));
    //             break;
    //
    //         case 10: // GUITARRA
    //             CrearObjeto(x,y,z,3,4,2,constantes.GUITARRA1,NumeroAleatorio(minGuitar,32));
    //             break;
    //         case 11:
    //             CrearObjeto(x,y,z,3,4,2,constantes.GUITARRA2,NumeroAleatorio(minGuitar,32));
    //             break;
    //         case 12:
    //             CrearObjeto(x,y,z,3,4,2,constantes.GUITARRA3,NumeroAleatorio(minGuitar,32));
    //             break;
    //
    //         case 13: // FLAUTA
    //             CrearObjeto(x,y,z,3,4,2,constantes.FLAUTA1,NumeroAleatorio(minFlauta,23));
    //             break;
    //         case 14:
    //             CrearObjeto(x,y,z,3,4,2,constantes.FLAUTA2,NumeroAleatorio(minFlauta,23));
    //             break;
    //         case 15:
    //             CrearObjeto(x,y,z,3,4,2,constantes.FLAUTA3,NumeroAleatorio(minFlauta,23));
    //             break;
    //
    //         default: // ORO
    //             CrearPowerUp(x,y,z,constantes.ORO,NumeroAleatorio(20,30));
    //             break;
    //     }
    // }
}

void Jugando::CrearEnemigoArana()
{
    _motora->getEvent("DerrotaPuzzle")->start();

    // Crear Arana
    CofreArana* _eneA = (CofreArana*)_eneCofres.at(
        _cofreP->GetPosArrayArana());

    //cout << "ID: "<<_eneA->getID()<<endl;

    _eneA->SetIdCofre(_cofreP->getID());
    _eneA->SetPosObsCofre(_cofreP->GetPosObs());
    _eneA->SetPosArana(_cofreP->GetPosArrayArana());
    _eneA->SetPosMotorCofre(_cofreP->GetPosicionArrayObjetos());
    _eneA->SetActivada(true);

    float x = _cofreP->getX();
    float y = _cofreP->getY();
    float z = _cofreP->getZ();

    int id = _motor->CargarEnemigos(x,y,z,_eneA->GetModelo(),_eneA->GetTextura(), false ,_eneA->GetAnimacion(), _eneA->GetFps());//creamos la figura
    _motor->cambiarAnimacion(5,id,2);
    _fisicas->crearCuerpo(1,x/2,y/2,z/2,2,_eneA->GetAncho(),
        _eneA->GetAlto(),_eneA->GetLargo(),2,0,0,false);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0,false); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0,false); //Para ataques especiales

   //Cargar sonido evento en una instancia con la id del enemigo como nombre
    std::string nameid = std::to_string(_eneA->getID()); //pasar id a string
    _motora->LoadEvent("event:/SFX/SFX-Arana grito enemigo", nameid, 1);
    _motora->getEvent(nameid)->setPosition(x,y,z);
    _motora->getEvent(nameid)->start();

    _enemigos.push_back(_eneA);
    _eneA = nullptr;

    _cofreP->BorrarCofre();
    _cofreP = nullptr;
}

void Jugando::CargarBossEnMemoria()
{
    int boss = _boss->GetEnemigo();
    float x = _boss->getX();
    float y = _boss->getY();
    float z = _boss->getZ();
    unsigned int did = 0;

    //cargador.SetVectorEnemigos(_enemigos);
    //BorrarTodosLosEnemigos();

    if(_jugador->GetSala() != _boss->GetSala())
    {
        _jugador->SetSala(_boss->GetSala());
    }
    if(boss == constantes.BOSS)
    {
        did = _motor->CargarEnemigos(x,y,z,_boss->GetModelo(), _boss->GetTextura(), true, _boss->GetAnimacion(), _boss->GetFps());//creamos la figura
    }
    else if(boss == constantes.TRAVORNIO)
    {
        did = _motor->CargarEnemigos(x,y,z,_boss->GetModelo(), _boss->GetTextura(), true, _boss->GetAnimacion(), _boss->GetFps(), constantes.DIEZ);//creamos la figura
    }

    _fisicas->crearCuerpo(1,x/2,y/2,z/2,2,1,1,1,2,0,0,true);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0,true); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0,true); //Para ataques especiales

    if(_boss->GetEscalado() != 1.0f)
    {
        _motor->EscalarMalla(_motor->ObtenerIDOpengl(5,did),_boss->GetEscalado());
    }

    std::string nameid = std::to_string(_boss->getID()); //pasar id a string

   if(nivelJ == 8)
   {
        _motora->LoadEvent("event:/SFX/SFX-Unicornio Caminando", nameid, 1);
        _motora->getEvent(nameid)->setPosition(x,y,z);
        _motora->getEvent(nameid)->start();
   }
   else if(nivelJ == 7)
   {
        _motora->LoadEvent("event:/SFX/SFX-Muerte Movimiento Esqueleto", nameid, 1);
        _motora->getEvent(nameid)->setPosition(x,y,z);
        _motora->getEvent(nameid)->start();
   }



    _enemigos.insert(_enemigos.begin(), _boss);
}

void Jugando::BorrarTodosLosEnemigos()
{
    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        EraseEnemigo(0);
        _motor->EraseTodosEnemigos();
        _fisicas->EraseTodosEnemigos();
    }
}

void Jugando::LimpiarJuego()
{
    BorrarTodosLosEnemigos();

    delete _jugador;
    delete _boss;

    int tam = _eneCofres.size();
    for(int i=0; i < tam; i++)
    {
        delete _eneCofres.at(i);
    }
    _eneCofres.clear();

    tam = _zonasRespawn.size();
    for(int i=0; i < tam; i++)
    {
        delete _zonasRespawn.at(i);
    }
    _zonasRespawn.clear();

    tam = _zonasCofre.size();
    for(int i=0; i < tam; i++)
    {
        delete _zonasCofre.at(i);
    }
    _zonasCofre.clear();

    tam = _zonasEscondite.size();
    for(int i=0; i < tam; i++)
    {
        delete _zonasEscondite.at(i);
    }
    _zonasEscondite.clear();

    tam = _zonasOscuras.size();
    for(int i=0; i < tam; i++)
    {
        delete _zonasOscuras.at(i);
    }
    _zonasOscuras.clear();

    tam = _reco_armas.size();
    for(int i=0; i < tam; i++)
    {
        delete _reco_armas.at(i);
    }
    _reco_armas.clear();

    tam = _llaves.size();
    for(int i=0; i < tam; i++)
    {
        delete _llaves.at(i);
    }
    _llaves.clear();

    tam = _powerup.size();
    for(int i=0; i < tam; i++)
    {
        delete _powerup.at(i);
    }
    _powerup.clear();

    cout << "Borro powerup" <<endl;
    //_waypoints.size()
    // Waypoints se borran con la sala

    tam = _palancas.size();
    for(int i=0; i < tam; i++)
    {
        delete _palancas.at(i);
    }
    _palancas.clear();

    cout << "Borro _palancas" <<endl;

    tam = _puertas.size();
    for(int i=0; i < tam; i++)
    {
        delete _puertas.at(i);
    }
    _puertas.clear();

    cout << "Borro _puertas" <<endl;

    tam = _cofres.size();
    for(int i=0; i < tam; i++)
    {
        delete _cofres.at(i);
    }
    _cofres.clear();

    cout << "Borro _cofres" <<endl;

    tam = _paredes.size();
    for(int i=0; i < tam; i++)
    {
        delete _paredes.at(i);
    }
    _paredes.clear();

    cout << "Borro _paredes" <<endl;


    // Vectores de Jugando
    tam = _auxiliadores.size();
    for(int i=0; i < tam; i++)
    {
        delete _auxiliadores.at(i);
    }
    _auxiliadores.clear();

    cout << "Borro _auxiliadores" <<endl;

    tam = recorrido.size();
    for(int i=0; i < tam; i++)
    {
        delete recorrido.at(i);
    }
    recorrido.clear();

    cout << "Borro recorrido" <<endl;
}

//Crear sprites del juego
void Jugando::CrearSprites()
{
    std::vector<const char *> sprites;
    sprites.push_back("assets/Sprites/Sprites-Ataque-Enemigo/Sprites-ataque-Enemigos_1.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Enemigo/Sprites-ataque-Enemigos_2.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Enemigo/Sprites-ataque-Enemigos_3.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Enemigo/Sprites-ataque-Enemigos_4.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Enemigo/Sprites-ataque-Enemigos_5.png");
    _motor->CargarSprite(0, sprites, 2.0f);
    sprites.clear();
    sprites.push_back("assets/Sprites/Sprites-Ataque-Epsecial-Muerte/Sprites-ataque-especial-boss-muerte_1.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Epsecial-Muerte/Sprites-ataque-especial-boss-muerte_2.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Epsecial-Muerte/Sprites-ataque-especial-boss-muerte_3.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Epsecial-Muerte/Sprites-ataque-especial-boss-muerte_4.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Epsecial-Muerte/Sprites-ataque-especial-boss-muerte_5.png");
    _motor->CargarSprite(1, sprites, 2.0f);
    sprites.clear();
    sprites.push_back("assets/Sprites/Sprites-Ataque-Jugador/Sprites-ataque-jugador_1.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Jugador/Sprites-ataque-jugador_2.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Jugador/Sprites-ataque-jugador_3.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Jugador/Sprites-ataque-jugador_4.png");
    sprites.push_back("assets/Sprites/Sprites-Ataque-Jugador/Sprites-ataque-jugador_5.png");
    _motor->CargarSprite(2, sprites, 2.0f);
    sprites.clear();
    sprites.push_back("assets/Sprites/Sprites-Respawn/Sprites-respawn_1.png");
    sprites.push_back("assets/Sprites/Sprites-Respawn/Sprites-respawn_2.png");
    sprites.push_back("assets/Sprites/Sprites-Respawn/Sprites-respawn_3.png");
    sprites.push_back("assets/Sprites/Sprites-Respawn/Sprites-respawn_4.png");
    sprites.push_back("assets/Sprites/Sprites-Respawn/Sprites-respawn_5.png");
    _motor->CargarSprite(3, sprites, 4.0f);
    sprites.clear();
}

unsigned int Jugando::GetTiempoPasadoNivel()
{
    if(_controladorTiempo)
    {
        return (unsigned int)_controladorTiempo->CalcularTiempoPasado(tiempoInicioNivel);
    }

    return 0;
}
