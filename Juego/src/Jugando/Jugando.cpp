#include "Jugando.hpp"
#include "../Juego.hpp"

//singleton
Jugando* Jugando::_unica_instancia = 0;
//fin indicador singleton

Jugando::Jugando()
{
    
}

Jugando::~Jugando()
{
    cout << "Borrando Jugando" << endl;
    reiniciando = false;

    // Punteros a clases singleton
    _sense = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;
    _motor = nullptr;

    // Liberar memoria
    delete _primeraSala;
    delete _unica_instancia;
}

void Jugando::Iniciar()
{
    cout << "\e[42m Entrando en Estado - Jugando \e[0m" << endl;
    
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    _fisicas = MotorFisicas::getInstance();
    _sense = SenseEventos::getInstance();

    reiniciando = false;
    id = 0;
    _primeraSala = nullptr;

    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    CargarNivel(5);

    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
}

void Jugando::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra

    //_nivel->Render();

    _motor->RenderEscena();               // Vuelve a pintar
}

void Jugando::Update()
{
    _motor->clearDebug();

    //Actualiza el motor de audio
    _motora->update(false);

    _sense->update();//se actualizan sentidos

    /*if (_nivel->GetJugador()->EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        _nivel->GetJugador()->MuereJugador(); // Animacion de muerte
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }
    _nivel->update();//se actualiza posiciones y interpolado*/
}

void Jugando::UpdateIA()
{
    /* *********** Teclas para probar cosas *************** */
    if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        //_nivel->GetJugador()->QuitarVida(20);
    }
    /* **************************************************** */
    //_nivel->updateIA();
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
        //_nivel->GetJugador()->setVida(0);
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

void Jugando::Pausar()
{ 
    cout << "Pausando el juego" << endl;
}

void Jugando::Reanudar()
{ 
    if (reiniciando) {
        cout << "REINICIAR JUEGO" << endl;
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









bool Jugando::CargarNivel(int level)
{
    //cargamos el nivel
    cargador.CargarNivelXml(level); //se llama al constructor vacio

    return true;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void Jugando::CrearJugador(int accion, int x,int y,int z, int ancho, int largo, 
    int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades)
{
    cout << "Creo el jugador"<<endl;
    // 100 es vida
    jugador = Jugador(100, x, y, z, ancho, largo, alto, ruta_objeto, ruta_textura);
    jugador.setID(++id);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setTimeAtEsp(0.0f);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);

    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas
cout << "jugador creado"<<endl;
    //TO DO: propiedades no se usa
    /*
    this->setjix(x);
    this->setjiy(y);
    this->setjiz(z);
    _motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
    */
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