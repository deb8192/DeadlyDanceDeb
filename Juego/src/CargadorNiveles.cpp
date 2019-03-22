#include <stdlib.h> 
#include "CargadorNiveles.hpp"

#include "Personajes/Heavy.hpp"
#include "Personajes/Bailaora.hpp"
#include "Enemigos/Pollo.hpp"
#include "Enemigos/Murcielago.hpp"
#include "Enemigos/CofreArana.hpp"
#include "Enemigos/MuerteBoss.hpp"

CargadorNiveles::CargadorNiveles()
{
    _motor = MotorGrafico::GetInstance();
    _fisicas = MotorFisicas::getInstance();
    _motora = MotorAudioSystem::getInstance();
}

CargadorNiveles::~CargadorNiveles()
{
    _motor = nullptr;
    _fisicas = nullptr;
    _motora = nullptr;

    delete _jugador;
    delete _boss;

    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        delete _enemigos.at(i);
    }
    _enemigos.clear();

    tam = _zonas.size();
    for(short i=0; i < tam; i++)
    {
        delete _zonas.at(i);
    }
    _zonas.clear();

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

    tam = _waypoints.size();
    for(short i=0; i < tam; i++)
    {
        delete _waypoints.at(i);
    }
    _waypoints.clear();
    
    delete _primeraSala;
}

void CargadorNiveles::CargarNivelXml(int level, int tipoJug)
{
    this->tipoJug = tipoJug;

    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".xml"; // extension del archivo a abrir
    std::string ruta = "assets/maps/xml/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension;

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //ahora vamos a abrir el fichero en xml y crear una instancia de pugixml(libreria)

    pugi::xml_document doc;//instanciamos el objeto de la libreria xml
    doc.load_file(cadena);//cargamos el archivo

    // Reservar memoria
    // Solo hay una etiqueta para reservar memoria
    pugi::xml_node hijo = doc.child("Level").child("MaxNumberOf");
    int eneMax = hijo.attribute("Enemies").as_int();//nos devuelve un int
    int wallsMax = hijo.attribute("Walls").as_int();//nos devuelve un int
    int doorsMax = hijo.attribute("Doors").as_int();//nos devuelve un int
    int chestsMax = hijo.attribute("Chests").as_int();//nos devuelve un int
    ReservarMemoriaVectores(eneMax, /*wallsMax, doorsMax, */chestsMax);
    
    pugi::xml_node primera = doc.child("Level"); //partimos de nivel
    vector <pugi::xml_node> anterior;
    anterior.push_back(primera.child("Platform"));
    vector <Sala* > padre;
    Sala* sala = crearSala(anterior.back(),nullptr);//pasamos la primera parte para que busque plataformas


    /*for (pugi::xml_node hijo = doc.child("Level").child("Light"); hijo; hijo = hijo.next_sibling("Light"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int z = hijo.attribute("Y").as_int();//nos devuelve un int
        int y = hijo.attribute("Z").as_int();//nos devuelve un int 
        CrearLuz(x,y,z); //cargamos el objeto
    }*/
    
    //Se crea el arbol de salas del mapa del nivel
    for (pugi::xml_node plat = anterior.back().child("Platform"); plat; plat = plat.next_sibling("Platform"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        while(plat != NULL)
        {
            padre.push_back(sala);
            sala = crearSala(plat, padre.back());
            anterior.push_back(plat);
            plat = plat.child("Platform");
        }
        while(plat.next_sibling() == NULL && !anterior.empty())
        {
            plat = anterior.back();
            anterior.pop_back();
            sala = padre.back();
            padre.pop_back();
        }
    }
}

void CargadorNiveles::GuardarNivelXml(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".xml"; // extension del archivo a abrir
    std::string ruta = "assets/maps/xml/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension;

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //vamos a llamar a los datos desde nivel para almacenarlos en formato xml

}

void CargadorNiveles::CargarNivelBin(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".bin"; // extension del archivo a abrir
    std::string ruta = "assets/maps/bin/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension; 

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //cargamos el archivo binario para cargar el nivel en la clase nivel
}

void CargadorNiveles::GuardarNivelBin(int level)
{
    //definimos los strings
    std::string nivel = ""; //donde se almacenara el nombre del nivel   
    std::string extension = ".bin"; // extension del archivo a abrir
    std::string ruta = "assets/maps/bin/"; // ruta del archivo
    std::string ruta_completa = ""; // ruta del archivo
    //ahora pasamos el nivel a texto
    nivel = std::to_string(level);
    //creamos la ruta completa
    ruta_completa = ruta+nivel+extension; 

    //esto transforma el string std 11 a char
    char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
    strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
    //fin de la transformacion

    //llamamos a las datos desde nivel para almacenarlos en formato binario 
}

Sala* CargadorNiveles::crearSala(pugi::xml_node plat,Sala* padre)
{
    Sala* padren = nullptr;//sala hijo
    
    int accion = plat.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
    int x = plat.attribute("X").as_int();//nos devuelve un int
    int y = plat.attribute("Y").as_int();//nos devuelve un int
    int z = plat.attribute("Z").as_int();//nos devuelve un int
    int rp = plat.attribute("RP").as_int();//nos devuelve un int
    int ancho = plat.attribute("ancho").as_int();//nos devuelve un int
    int largo = plat.attribute("largo").as_int();//nos devuelve un int
    int alto = plat.attribute("alto").as_int();//nos devuelve un int 
    int centro = plat.attribute("TypeCenter").as_int();//nos devuelve el tipo de centro de masas del objeto
    bool jugadorEstasAqui = plat.attribute("UserStar").as_bool();//nos devuelve true si es donde empieza el jugador 
    const char* textura = plat.attribute("Texture").value(); //nos da un char[] = string
    const char* modelo  =  plat.attribute("Model").value(); //nos da un char[] = string
    padren = CrearPlataforma(accion,rp,x,y,z,ancho,largo,alto,centro,modelo,textura); //cargamos el objeto

    if(padre != nullptr && padren != nullptr)
    {
        padre->agregarSalida(padren);
        padren->agregarEntrada(padre);
    }

    if(jugadorEstasAqui)
    {
        //cogemos las posiciones del jugador en el escenario
        int accion = plat.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
        int Playerx = plat.attribute("StarX").as_int();//nos devuelve un int
        int Playery = plat.attribute("StarY").as_int();//nos devuelve un int
        int Playerz = plat.attribute("StarZ").as_int();//nos devuelve un int 
        int ancho = 1;//nos devuelve un int
        int largo = 1;//nos devuelve un int 
        int alto = 5;//nos devuelve un int
        // El modelo esta dentro de sus clases de jugadores

        switch (tipoJug)
        {
            case 2:
                _jugador = new Bailaora(Playerx,Playerz,Playery,ancho,largo,alto,accion, 100);
                break;
        
            default:
                _jugador = new Heavy(Playerx,Playerz,Playery,ancho,largo,alto,accion, 100);
                break;
        }
        _jugador->setID(++id);
    }

    for (pugi::xml_node enem = plat.child("Enemy"); enem; enem = enem.next_sibling("Enemy"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        //aqui va la carga de enemigos
        int accion = enem.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
        int x = enem.attribute("X").as_int();//nos devuelve un int
        int y = enem.attribute("Y").as_int();//nos devuelve un int
        int z = enem.attribute("Z").as_int();//nos devuelve un int 
        int ancho = enem.attribute("ancho").as_int();//nos devuelve un int
        int largo = enem.attribute("largo").as_int();//nos devuelve un int 
        int alto = enem.attribute("ancho").as_int();//nos devuelve un int
        int enemigo = enem.attribute("enemigo").as_int(); //nos da un char[] = string
        
        if (enemigo >= 0)
        {
            CrearEnemigo(accion,enemigo,x,y,z,ancho,largo,alto,padren); //cargamos el enemigo
        } else {
            CrearBoss(accion,enemigo,x,y,z,ancho,largo,alto,padren);
        }
    }
    for (pugi::xml_node obj = plat.child("Object"); obj; obj = obj.next_sibling("Object"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        //aqui va la carga de objetos
        int codigo = obj.attribute("codigo").as_int(); //se utiliza para asociar palancas y/o llaves a puertas
        int accion = obj.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
        int x = obj.attribute("X").as_int();//nos devuelve un int
        int y = obj.attribute("Y").as_int();//nos devuelve un int
        int z = obj.attribute("Z").as_int();//nos devuelve un int
        int rp = obj.attribute("RP").as_int();//nos devuelve un int
        int despX = obj.attribute("despX").as_int();//nos devuelve un int
        int despZ = obj.attribute("despZ").as_int();//nos devuelve un int
        int ancho = obj.attribute("ancho").as_int();//nos devuelve un int
        int largo = obj.attribute("largo").as_int();//nos devuelve un int
        int alto = obj.attribute("alto").as_int();//nos devuelve un int
        int ataque = obj.attribute("ataque").as_int();//nos devuelve un int
        const char* nombre = obj.attribute("nombre").value(); //nos da un char[] = string
        const char* textura = obj.attribute("Texture").value(); //nos da un char[] = string
        const char* modelo  =  obj.attribute("Model").value(); //nos da un char[] = string
        CrearObjeto(codigo,accion,nombre,ataque,rp,x,y,z,despX,despZ,ancho,largo,alto,modelo,textura, NULL); //cargamos el enemigo
    }
    for (pugi::xml_node zon = plat.child("Zone"); zon; zon = zon.next_sibling("Zone"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        //carga de las zonas
        int accion = zon.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
        int x = zon.attribute("X").as_int();//nos devuelve un int
        int y = zon.attribute("Y").as_int();//nos devuelve un int
        int z = zon.attribute("Z").as_int();//nos devuelve un int
        int ancho = zon.attribute("ancho").as_int();//nos devuelve un int
        int largo = zon.attribute("largo").as_int();//nos devuelve un int
        int alto = zon.attribute("ancho").as_int();//nos devuelve un int
        short totalElementos = zon.attribute("elementos").as_int();
        const char* tipo = zon.attribute("tipo").value(); //nos da un char[] = string
        CrearZona(accion,x,y,z,ancho,largo,alto,tipo,totalElementos); //cargamos el enemigo
    }

    for (pugi::xml_node enem = plat.child("Waypoint"); enem; enem = enem.next_sibling("Waypoint"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        //aqui va la carga de waypoints para los enemigos
        int accion = enem.attribute("accion").as_int(); //lo vamos a usar para decidir herencia y fisicas
        int ID = enem.attribute("id").as_int(); //lo vamos a usar para indentificar los waypoints de distintas salas
        int x = enem.attribute("X").as_int();//nos devuelve un int
        int y = enem.attribute("Y").as_int();//nos devuelve un int
        int z = enem.attribute("Z").as_int();//nos devuelve un int 
        int ancho = enem.attribute("ancho").as_int();//nos devuelve un int
        int largo = enem.attribute("largo").as_int();//nos devuelve un int 
        int alto = enem.attribute("alto").as_int();//nos devuelve un int 
        int compartido = enem.attribute("compartido").as_int();//nos devuelve un int
        char* conexiones = (char *) enem.attribute("conexiones").value(); //nos indica los ID de los waypoints con los que conecta este waypoint
        char* reading =  strtok(conexiones, ",");
        int* arrayConexiones = new int [5];
        unsigned short i = 0;
        while(reading != nullptr)
        {
            arrayConexiones[i] = atoi(reading);
            reading = strtok(NULL, ",");
            i++;
        }
        CrearWaypoint(padren,accion,compartido,ID,x,y,z,ancho,largo,alto,arrayConexiones,i); //cargamos el waypoint
    }

    return padren;
}

Jugador* CargadorNiveles::GetJugador()
{
    return _jugador;
}

std::vector<Enemigo*> CargadorNiveles::GetEnemigos()
{
    return _enemigos;
}

std::vector<Enemigo*> CargadorNiveles::GetEneCofres()
{
    return _eneCofres;
}

std::vector<Zona*> CargadorNiveles::GetZonas()
{
    return _zonas;
}

std::vector<Recolectable*> CargadorNiveles::GetRecolectables()
{
    return _recolectables;
}

std::vector<Interactuable*> CargadorNiveles::GetInteractuables()
{
    return _interactuables;
}

std::vector<Recolectable*> CargadorNiveles::GetPowerup()
{
    return _powerup;
}

Enemigo* CargadorNiveles::GetBoss()
{
    return _boss;
}

std::vector<Waypoint*> CargadorNiveles::GetWaypoints()
{
    return _waypoints;
}

void CargadorNiveles::ReservarMemoriaVectores(int eneMax, int chestsMax)
{
    //TO DO: meter a mano o cargar del XML
    _enemigos.reserve(eneMax);
    _eneCofres.reserve(chestsMax);

    unsigned short eneAranas = chestsMax/4; // 1/4 de los cofres son enemigos
    for (unsigned short i= 0; i<eneAranas; ++i)
    {
        CrearCofreArana();
    }
    
    /*_recolectables.reserve(20);
    _interactuables.reserve(20);
    _powerup.reserve(20);
    _zonas.reserve(20);
    _waypoints.reserve(20);*/
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
Sala* CargadorNiveles::CrearPlataforma(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto, int centro,
    const char* ruta_objeto, const char* ruta_textura)
{
    Sala* _sala = new Sala(ancho,largo,alto,x,y,z,centro);
    //int*  datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int nId = _motor->CargarPlataformas(rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    _sala->definirID(nId);
    _fisicas->crearCuerpo(accion,rp,x/2,y/2,z/2,2,ancho,alto,largo,6,0,0);

    if(!_primeraSala)
    {
       _primeraSala = _sala;
    }

    return _sala;
}

void CargadorNiveles::CrearLuz(int x,int y,int z)
{
    _motor->CargarLuces(x,y,z);
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void CargadorNiveles::CrearEnemigo(int accion, int enemigo, int x,int y,int z, 
    int ancho, int largo, int alto, Sala* sala)
{
    //accion indicara futuramente que tipo de enemigo sera (herencia)
    switch (enemigo)
    {
        case 0:
        {
            Pollo* _ene = new Pollo(x,y,z, 75); // Posiciones, vida
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
        case 1:
        {
            Murcielago* ene = new Murcielago(x,y,z, 125); // Posiciones, vida
            //ia
            ene->setArbol(cargadorIA.cargarBehaviorTreeXml("MurcielagoBT"));
            _enemigos.push_back(ene);//guardamos el enemigo en el vector
            _enemigos.back()->setID(++id);//le damos el id unico en esta partida al enemigo

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
    _enemigos.back()->setPosicionesAtaque(x,y,z);
    _enemigos.back()->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _enemigos.back()->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _enemigos.back()->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _enemigos.back()->initPosicionesFisicasAtaque(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _enemigos.back()->setVelocidadMaxima(1.0f);
    _enemigos.back()->setBarraAtEs(0);
    _enemigos.back()->definirSala(sala);//le pasamos la sala en donde esta
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
    
    _motor->CargarEnemigos(x,y,z,_enemigos.back()->GetModelo());//creamos la figura

    _fisicas->crearCuerpo(accion,0,x/2,y/2,z/2,2,ancho,alto,largo,2,0,0);
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,7,0,0); //Para ataques
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,8,0,0); //Para ataques especiales
}

void CargadorNiveles::CrearBoss(int accion,int enemigo,int x,int y,int z, 
    int ancho, int largo, int alto, Sala* sala)
{
    _boss = new MuerteBoss(x,y,z, 2000); // Posiciones, vida
    _boss->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
    //_boss->setArbol(cargadorIA.cargarBehaviorTreeXml("BossesBT"));
    _boss->setID(++id);//le damos el id unico en esta partida al enemigo

    _boss->SetEnemigo(enemigo); // Se utiliza en UpdateBehavior()
    _boss->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _boss->setPosicionesAtaque(x, y, z);
    _boss->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _boss->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _boss->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _boss->initPosicionesFisicasAtaque(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _boss->setVelocidadMaxima(1.0f);
    _boss->setBarraAtEs(0);
    _boss->definirSala(sala);//le pasamos la sala en donde esta
    _boss->setAtaque(20);
    _boss->setArmaEspecial(100);
    _boss->setTimeAtEsp(0.0f);
    _boss->setDanyoCritico(80);
    _boss->setProAtaCritico(20);
    _boss->setRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _boss->setVectorOrientacion();
    _boss->setNewRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _boss->setLastRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta

    _motor->CargarBoss(x,y,z,_boss->GetModelo());//creamos la figura

    _fisicas->crearCuerpo(accion,0,x/2,y/2,z/2,2,ancho,alto,largo,-1,0,0);
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,10,0,0); //Para ataque
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,11,0,0); //Para ataque especial
}

//lo utilizamos para crear zonas
void CargadorNiveles::CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, unsigned short totalElem)
{
   //Crear zona
   Zona* zon = new Zona(ancho,largo,alto,tipo);

   //ID propia y posicion
   int calcID = _zonas.size();
   zon->setID(calcID);
   zon->setPosiciones(x,y,z);
   zon->setTotalElementos(totalElem);

   //guardarla en el nivel
   _zonas.push_back(move(zon));
   zon = nullptr;
}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void CargadorNiveles::CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z,
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
        _inter->setID(++id);
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

    _fisicas->crearCuerpo(accion,rp,x/2,y/2,z/2,2,ancho,alto,largo,3,despX,despZ);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba
}

void CargadorNiveles::CrearWaypoint(Sala* sala, int accion, int compartido, int ID, int x, int y, int z, int ancho, int largo, int alto, int* arrayConexiones, int sizeConexiones)
{
    Waypoint* waypoint = new Waypoint(ID, x, y, z, compartido, arrayConexiones, sizeConexiones);
    bool coincide = false;
    unsigned short i = 0;
    while(i < _waypoints.size() && !coincide)
    {
        if(_waypoints[i]->GetID() == waypoint->GetID())
        {
            coincide = true;
            sala->AgregarWaypoint(_waypoints[i]);
            delete waypoint; // TO DO: revisar
        }
        else {i++;}
    }
    if(!coincide)
    {
        _waypoints.push_back(waypoint);
        sala->AgregarWaypoint(_waypoints.back());
    }
    waypoint = nullptr;
}

void CargadorNiveles::CrearCofreArana()
{
    /*int accion, int enemigo, int x,int y,int z, 
    int ancho, int largo, int alto, Sala* sala*/

    CofreArana* _eneA = new CofreArana(0,0,0, 150); // Posiciones, vida
    
    _eneA->setArbol(cargadorIA.cargarBehaviorTreeXml("CofreAranyaBT"));
    _eneA->setID(++id);//le damos el id unico en esta partida al enemigo
    _eneA->SetEnemigo(2);

    _eneA->setVelocidadMaxima(1.5f);
    _eneA->setBarraAtEs(0);
    _eneA->setAtaque(10);
    _eneA->setArmaEspecial(100);
    _eneA->setTimeAtEsp(0.0f);
    _eneA->setDanyoCritico(50);
    _eneA->setProAtaCritico(10);
    _eneA->setRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _eneA->setVectorOrientacion();
    _eneA->setNewRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _eneA->setLastRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta

    //_motor->CargarEnemigos(0,0,0,_eneA->GetModelo());//creamos la figura
    _eneCofres.push_back(move(_eneA));//guardamos el enemigo en el vector
    _eneA = nullptr;

    /*_eneA->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->setPosicionesAtaque(x,y,z);
    _eneA->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _eneA->initPosicionesFisicasAtaque(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _eneA->definirSala(sala);//le pasamos la sala en donde esta
    _fisicas->crearCuerpo(accion,0,x/2,y/2,z/2,2,ancho,alto,largo,2);
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,7); //Para ataques
    _fisicas->crearCuerpo(0,0,x/2,y/2,z/2,2,5,5,5,8); //Para ataques especiales
    */
    
    //Cargar sonido evento en una instancia con la id del enemigo como nombre
    /* std::string nameid = std::to_string(id); //pasar id a string
    _motora->LoadEvent("event:/SFX/SFX-Pollo enfadado", nameid);
    _motora->getEvent(nameid)->setPosition(x,y,z);
    _motora->getEvent(nameid)->setVolume(0.4f);
    _motora->getEvent(nameid)->start();*/
}

int* CargadorNiveles::GetID()
{
    return &id;
}