#include "Jugando.hpp"
#include "../Juego.hpp"

//singleton
Jugando* Jugando::_unicaInstancia = 0;
//fin indicador singleton

Jugando::Jugando()
{
    
}

Jugando::~Jugando()
{
    cout << "Borrando Jugando" << endl;
    reiniciando = false;
    jugadorInmovil = false;
    drawTime = 0.0f;
    lastDrawTime = 0.0f;

    // Punteros a clases singleton
    _controladorTiempo = nullptr;
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;

    // Liberar memoria
    short tam = _interactuables.size();
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



    //TO DO: borrarlas de MotorGrafico

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
    //drawTime = 0.0f;
    drawTime = _controladorTiempo->GetTiempo(2);
    lastDrawTime = drawTime;
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
    // KEY_E
    //_nivel->ManejarEventos();
}

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
    //_nivel->update();//se actualiza posiciones y interpolado

    //animacion
    _motor->cambiarAnimacionJugador(jugador.getAnimacion());

    // Adelanta posicion del bounding box al jugador, mientras pulses esa direccion si colisiona no se mueve
    _fisicas->colisionChecker(_motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W),
        jugador.getNewX(),
        jugador.getNewY(),
        jugador.getNewZ()
    );
    
    // Actualizar movimiento del jugador
    jugador.movimiento(jugadorInmovil,
        _motor->EstaPulsado(KEY_A),
        _motor->EstaPulsado(KEY_S),
        _motor->EstaPulsado(KEY_D),
        _motor->EstaPulsado(KEY_W)
    );

    _fisicas->updateJugador(jugador.getX(),
        jugador.getY(),
        jugador.getZ()
    );
    
    // Armas

    //Comprueba la activacion de un powerup
    //this->activarPowerUp();
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
    //_nivel->updateIA();
}

void Jugando::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra toda la pantalla

    //Para evitar un tran salto en el principio de la ejecucion se actualiza el valor de drawTime
    /*if (drawTime == 0.0f)
    {
        drawTime = _controladorTiempo->GetTiempo(2);
    }*/
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

    //Dibujado de las puertas

    //Dibujado del ataque especial
    //Ataque especial Heavy
    //Ataque especial bailaora

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
    /*
    _motor->BorrarScena();//borramos la scena

    //pre limpiamos todo
    _motor->LimpiarMotorGrafico();
    LimpiarNivel();
    _fisicas->limpiarFisicas();
    //limpiammos la sala
    if(_primeraSala != nullptr)
    {
       _primeraSala->~Sala();
       _primeraSala = nullptr;
    }*/

    //cargamos el nivel
    cargador.CargarNivelXml(nivel, tipoJug); //se llama al constructor vacio
    
    // Codigo de Nivel.cpp
    //Cargar objetos con el nivel completo
    /*this->cargarCofres(2); //Cargamos los cofres del nivel

    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Nivel1")->start(); //Reproducir musica juego
    _motora->getEvent("AmbienteGritos")->start(); //Reproducir ambiente

    _motor->cargarInterfaz();
    //esta ya todo ejecutamos ia y interpolado
    Ejecutar();*/
    
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
    
    cout << "jugador creado en: "<<x<<", "<<y<<", "<<z<<", "<<endl;
    //TO DO: propiedades no se usa
    //_motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
}

/*Sala* Jugando::CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura)//lo utilizamos para crear su modelo en motorgrafico y su objeto
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
}*/

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

// Desactiva el modo debug en MotorGrafico
 void Jugando::DesactivarDebug()
 {
     if (_motor->GetDebugActivado())
     {
        _motor->activarDebugGrafico();
     }
 }