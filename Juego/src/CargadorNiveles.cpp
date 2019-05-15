#include <stdlib.h>
#include "CargadorNiveles.hpp"

#include "Personajes/Heavy.hpp"
#include "Personajes/Bailaora.hpp"
#include "Enemigos/Pollo.hpp"
#include "Enemigos/Murcielago.hpp"
#include "Enemigos/CofreArana.hpp"
#include "Enemigos/MuerteBoss.hpp"
#include "Enemigos/Guardian.hpp"

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

    tam = _eneCofres.size();
    for(short i=0; i < tam; i++)
    {
        delete _eneCofres.at(i);
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
        delete _reco_armas.at(i);
    }
    _reco_armas.clear();

    tam = _llaves.size();
    for(short i=0; i < tam; i++)
    {
        delete _llaves.at(i);
    }
    _llaves.clear();

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

    tam = _palancas.size();
    for(short i=0; i < tam; i++)
    {
        delete _palancas.at(i);
    }
    _palancas.clear();

    tam = _puertas.size();
    for(short i=0; i < tam; i++)
    {
        delete _puertas.at(i);
    }
    _puertas.clear();

    tam = _cofres.size();
    for(short i=0; i < tam; i++)
    {
        delete _cofres.at(i);
    }
    _cofres.clear();

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
    //int wallsMax = hijo.attribute("Walls").as_int();//nos devuelve un int
    //int keysMax = hijo.attribute("Keys").as_int();//nos devuelve un int
    int leversMax = hijo.attribute("Levers").as_int();//nos devuelve un int
    chestsMax = hijo.attribute("Chests").as_int();//nos devuelve un int
    int doorsMax = hijo.attribute("Doors").as_int();//nos devuelve un int
    int zonesMax = hijo.attribute("Zones").as_int();//nos devuelve un int
    int waypointsMax = hijo.attribute("Waypoints").as_int();//nos devuelve un int

    ReservarMemoriaVectores(eneMax, doorsMax, leversMax, chestsMax,
        waypointsMax, zonesMax/*, wallsMax*/);

    pugi::xml_node primera = doc.child("Level"); //partimos de nivel
    vector <pugi::xml_node> anterior;
    anterior.push_back(primera.child("Platform"));
    vector <Sala* > padre;
    Sala* sala = crearSala(anterior.back(),nullptr);//pasamos la primera parte para que busque plataformas

    for (pugi::xml_node hijo = doc.child("Level").child("Light"); hijo; hijo = hijo.next_sibling("Light"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int y = hijo.attribute("Y").as_int();//nos devuelve un int
        int z = hijo.attribute("Z").as_int();//nos devuelve un int
        int r = hijo.attribute("colorR").as_int();//nos devuelve un int
        int g = hijo.attribute("colorG").as_int();//nos devuelve un int
        int b = hijo.attribute("colorB").as_int();//nos devuelve un int
        int tipo = hijo.attribute("Tipo").as_int();
        float intensidad = (float)hijo.attribute("Intensity").as_int();
        int anim = hijo.attribute("Animacion").as_int();
        CrearLuz(x,y,z,tipo,intensidad,r,g,b,anim); //cargamos el objeto
    }

    for (pugi::xml_node hijo = doc.child("Level").child("LightSala"); hijo; hijo = hijo.next_sibling("LightSala"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int minz = hijo.attribute("minZ").as_int();//nos devuelve un int
        int maxz = hijo.attribute("maxZ").as_int();//nos devuelve un int
        int minx = hijo.attribute("minX").as_int();//nos devuelve un int
        int maxx = hijo.attribute("maxX").as_int();//nos devuelve un int
        int sala = hijo.attribute("sala").as_int();
        CrearSalaLuz(sala,minz,maxz,minx,maxx);
    }

    for (pugi::xml_node hijo = doc.child("Level").child("LightPos"); hijo; hijo = hijo.next_sibling("LightPos"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int y = hijo.attribute("Y").as_int();//nos devuelve un int
        int z = hijo.attribute("Z").as_int();//nos devuelve un int
        int sala = hijo.attribute("sala").as_int();
        CrearLuzEnSala(sala,x,y,z);
    }

    for (pugi::xml_node hijo = doc.child("Level").child("Particles"); hijo; hijo = hijo.next_sibling("Particles"))//esto nos devuelve todos los hijos que esten al nivel del anterior
    {
        int x = hijo.attribute("X").as_int();//nos devuelve un int
        int y = hijo.attribute("Y").as_int();//nos devuelve un int
        int z = hijo.attribute("Z").as_int();//nos devuelve un int
        int vx = hijo.attribute("VX").as_int();//nos devuelve un int
        int vy = hijo.attribute("VY").as_int();//nos devuelve un int
        int vz = hijo.attribute("VZ").as_int();//nos devuelve un int
        int npart = hijo.attribute("nPart").as_int();
        float size = (float)hijo.attribute("size").as_int()/10.0f;
        float localz = (float)hijo.attribute("LZ").as_int();
        float vida = (float)hijo.attribute("vida").as_int();
        const char* textura = hijo.attribute("Texture").value(); //nos da un char[] = string
        CrearSistemaDeParticulas(x,y,z,vx,vy,vz,npart,localz,vida,size,textura);
    }

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
        // El modelo y la textura estan dentro de sus clases de jugadores

        switch (tipoJug)
        {
            case 2:
                _jugador = new Bailaora(padren,tipoJug,Playerx,Playerz,Playery,ancho,largo,alto,accion, 100);
                break;

            default:
                _jugador = new Heavy(padren,tipoJug,Playerx,Playerz,Playery,ancho,largo,alto,accion, 100);
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

        if (enemigo != constantes.BOSS)
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
        short tipoObj = (short) obj.attribute("tipoObj").as_int();//nos devuelve un short
        int numFrames = obj.attribute("Frames").as_int();//numero de frames de la animacion
        const char* logicaAnimacion = obj.attribute("Animation").value();//contiene la ruta a la logica de la animacion


        if(obj.attribute("Frames") && obj.attribute("Animation"))
        {
            CrearObjeto(codigo,accion,nombre,ataque,rp,x,y,z,despX,despZ,ancho,largo,alto,modelo,textura, NULL, tipoObj, logicaAnimacion, numFrames); //cargamos el enemigo
        }
        else
        {
            CrearObjeto(codigo,accion,nombre,ataque,rp,x,y,z,despX,despZ,ancho,largo,alto,modelo,textura, NULL, tipoObj);//no tiene logica de animacion porque es un objeto con un unico estado y frame
        }

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
        int boss = zon.attribute("boss").as_int();
        short totalElementos = zon.attribute("elementos").as_int();
        const char* tipo = zon.attribute("tipo").value(); //nos da un char[] = string
        CrearZona(accion,x,y,z,ancho,largo,alto,boss,tipo,totalElementos,padren); //cargamos el enemigo
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
        char* tipoWaypoint = (char*) enem.attribute("tipoWaypoint").value();
        int compartido = enem.attribute("compartido").as_int();//nos devuelve un int
        char* conexiones = (char*) enem.attribute("conexiones").value(); //nos indica los ID de los waypoints con los que conecta este waypoint
        char* reading =  strtok(conexiones, ",");
        int* arrayConexiones = new int [5];
        unsigned short i = 0;
        while(reading != nullptr)
        {
            arrayConexiones[i] = atoi(reading);
            reading = strtok(NULL, ",");
            i++;
        }
        CrearWaypoint(padren,accion,compartido,ID,x,y,z,ancho,largo,alto,arrayConexiones,tipoWaypoint[0],i); //cargamos el waypoint
    }

    return padren;
}

void CargadorNiveles::SetVectorEnemigos(std::vector<Enemigo*>& _enemigosNuevos)
{
    _enemigos = _enemigosNuevos;
}

Jugador* CargadorNiveles::GetJugador()
{
    return _jugador;
}

std::vector<Enemigo*> CargadorNiveles::GetEnemigos()
{
    return _enemigos;
}

unsigned int CargadorNiveles::GetEnemigosCapacity()
{
    return _enemigos.capacity();
}


std::vector<Enemigo*> CargadorNiveles::GetEneCofres()
{
    return _eneCofres;
}

std::vector<ZonaOscura*> CargadorNiveles::GetZonasOscuras()
{
    return _zonasOscuras;
}

unsigned int CargadorNiveles::GetZonasOscurasCapacity()
{
    return _zonasOscuras.capacity();
}

std::vector<ZonaRespawn*> CargadorNiveles::GetZonasRespawn()
{
    return _zonasRespawn;
}

unsigned int CargadorNiveles::GetZonasRespawnCapacity()
{
    return _zonasRespawn.capacity();
}

std::vector<ZonaCofre*> CargadorNiveles::GetZonasCofre()
{
    return _zonasCofre;
}

unsigned int CargadorNiveles::GetZonasCofreCapacity()
{
    return _zonasCofre.capacity();
}

std::vector<ZonaEscondite*> CargadorNiveles::GetZonasEscondite()
{
    return _zonasEscondite;
}

unsigned int CargadorNiveles::GetZonasEsconditeCapacity()
{
    return _zonasEscondite.capacity();
}

std::vector<Recolectable*> CargadorNiveles::GetRecolectables()
{
    return _reco_armas;
}

std::vector<Recolectable*> CargadorNiveles::GetLlaves()
{
    return _llaves;
}

unsigned int CargadorNiveles::GetRecolectablesCapacity()
{
    return _reco_armas.capacity();
}

std::vector<Pared*> CargadorNiveles::GetParedes()
{
    return _paredes;
}

unsigned int CargadorNiveles::GetParedesCapacity()
{
    return _paredes.capacity();
}

std::vector<Recolectable*> CargadorNiveles::GetPowerup()
{
    return _powerup;
}

unsigned int CargadorNiveles::GetPowerupCapacity()
{
    return _powerup.capacity();
}

Enemigo* CargadorNiveles::GetBoss()
{
    return _boss;
}

std::vector<Waypoint*> CargadorNiveles::GetWaypoints()
{
    return _waypoints;
}

unsigned int CargadorNiveles::GetWaypointsCapacity()
{
    return _waypoints.capacity();
}

std::vector<Puerta*> CargadorNiveles::GetPuertas()
{
    return _puertas;
}

std::vector<Palanca*> CargadorNiveles::GetPalancas()
{
    return _palancas;
}

std::vector<Cofre*> CargadorNiveles::GetCofres()
{
    return _cofres;
}

void CargadorNiveles::ReservarMemoriaVectores(int eneMax, int doorsMax, int leversMax, int chestsMax,
    int waypointsMax, int zonesMax)
{
    _enemigos.reserve(eneMax);
    _puertas.reserve(doorsMax);
    _palancas.reserve(leversMax);
    _cofres.reserve(chestsMax);
    _zonasRespawn.reserve(zonesMax);
    _waypoints.reserve(waypointsMax);
    _eneCofres.reserve(chestsMax/4);

    // TO DO:
    /*
    _zonasEscondite.reserve();
    _zonasOscuras.reserve();
    _zonasCofre.reserve();_reco_armas.reserve(20);
    _llaves.reserve(20);
    _powerup.reserve(20);
    */
}

void CargadorNiveles::BorrarVectorEnemigosBossActivado()
{
    short tam = _enemigos.size();
    for(short i=0; i < tam; i++)
    {
        delete _enemigos.at(i);
    }
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
    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,6,0,0, false);

    if(!_primeraSala)
    {
       _primeraSala = _sala;
    }

    return _sala;
}

void CargadorNiveles::CrearLuz(int x,int y,int z,int tipo,float dist, int r, int g, int b, int anim)
{
    _motor->CargarLuces(x,y,z,r,g,b,tipo,dist,anim);
}

void CargadorNiveles::CrearSalaLuz(int sala,int minz,int maxz,int minx,int maxx)
{
    _motor->CargarSalaLuz(sala,minz,maxz,minx,maxx);
}

void CargadorNiveles::CrearLuzEnSala(int sala,int x,int y,int z)
{
    _motor->CargarLuzEnSala(sala,x,y,z);
}

void CargadorNiveles::CrearSistemaDeParticulas(int x,int y,int z,int vx,int vy,int vz,int npart,float localz,float vida,float size, const char* textura)
{
    _motor->CargarParticulas(x,y,z,vx,vy,vz,size,npart,localz,vida,textura);
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
            Pollo* _ene = new Pollo(x,y,z, 50); // Posiciones, vida
            //ia
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
            _ene->setVelocidadMaxima(1.0f);
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
            Murcielago* _ene = new Murcielago(x,y,z, 75); // Posiciones, vida
            //ia
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("MurcielagoBT"));
            _ene->setVelocidadMaxima(1.0f);
            _enemigos.push_back(_ene);//guardamos el enemigo en el vector
            _enemigos.back()->setID(++id);//le damos el id unico en esta partida al enemigo

            //Cargar sonido evento en una instancia con la id del enemigo como nombre
            std::string nameid = std::to_string(id); //pasar id a string
            _motora->LoadEvent("event:/SFX/SFX-Murcielago volando", nameid);
            _motora->getEvent(nameid)->setPosition(x,y,z);
            _motora->getEvent(nameid)->setVolume(1.0f);
            _motora->getEvent(nameid)->start();
        }
            break;

        case 3:
        {
            Guardian* _ene = new Guardian(x,y,z, 150, enemigo);
            //ia
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("GuardianBT"));
            _ene->setVelocidadMaxima(1.5f);
            _ene->setID(++id);//le damos el id unico en esta partida al enemigo
            _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
            _ene = nullptr;

            //Cargar sonido evento en una instancia con la id del enemigo como nombre
            std::string nameid = std::to_string(id); //pasar id a string
            _motora->LoadEvent("event:/SFX/SFX-Muerte Movimiento Esqueleto", nameid);
            _motora->getEvent(nameid)->setPosition(x,y,z);
            _motora->getEvent(nameid)->setVolume(0.5f);
            _motora->getEvent(nameid)->start();
        }
        break;

        case 4:
        {
            Guardian* _ene = new Guardian(x,y,z, 150, enemigo);
            //ia
            _ene->setArbol(cargadorIA.cargarBehaviorTreeXml("GuardianBT"));
            _ene->setVelocidadMaxima(1.5f);
            _ene->setID(++id);//le damos el id unico en esta partida al enemigo
            _enemigos.push_back(move(_ene));//guardamos el enemigo en el vector
            _ene = nullptr;

            //Cargar sonido evento en una instancia con la id del enemigo como nombre
            std::string nameid = std::to_string(id); //pasar id a string
            _motora->LoadEvent("event:/SFX/SFX-Muerte Movimiento Esqueleto", nameid);
            _motora->getEvent(nameid)->setPosition(x,y,z);
            _motora->getEvent(nameid)->setVolume(0.5f);
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

    _motor->CargarEnemigos(x,y,z,_enemigos.back()->GetModelo(),_enemigos.back()->GetTextura(), false,_enemigos.back()->GetAnimacion(),_enemigos.back()->GetFps());//creamos la figura

    _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,2,0,0,false);
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,7,0,0,false); //Para ataques
    _fisicas->crearCuerpo(0,x/2,y/2,z/2,2,5,5,5,8,0,0,false); //Para ataques especiales
}

void CargadorNiveles::CrearBoss(int accion,int enemigo,int x,int y,int z,
    int ancho, int largo, int alto, Sala* sala)
{
    _boss = new MuerteBoss(x,y,z, 300); // Posiciones, vida
    //_boss->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
    _boss->setArbol(cargadorIA.cargarBehaviorTreeXml("BossesBT"));
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
    _boss->SetMultiplicadorAtEsp(2);
}

//lo utilizamos para crear zonas
void CargadorNiveles::CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, int boss, const char* tipo, unsigned short totalElem, Sala* sala)
{
    Constantes constantes;
    //Crear zonas
    int calcID;
    if(strcmp(tipo, constantes.ZRESPAWN) == 0)
    {
        ZonaRespawn* zonR = new ZonaRespawn(ancho,largo,alto,tipo,boss);
        calcID = _zonasRespawn.size();
        zonR->setID(calcID);
        zonR->setPosiciones(x,y,z);
        zonR->SetSala(sala);
        _zonasRespawn.push_back(zonR);
        zonR = nullptr;
    }
    else if(strcmp(tipo, constantes.ZCHEST) == 0)
    {
        ZonaCofre* zonC = new ZonaCofre(ancho,largo,alto,tipo);
        calcID = _zonasCofre.size();
        zonC->setID(calcID);
        zonC->SetTotalElementos(totalElem);
        zonC->setPosiciones(x,y,z);
        zonC->SetSala(sala);
        _zonasCofre.push_back(zonC);
        zonC = nullptr;
    }
    else if(strcmp(tipo, constantes.ZDARK) == 0)
    {
        ZonaOscura* zonO= new ZonaOscura(ancho,largo,alto,tipo);
        calcID = _zonasOscuras.size();
        zonO->setID(calcID);
        zonO->SetTotalElementos(totalElem);
        zonO->setPosiciones(x,y,z);
        zonO->SetSala(sala);
        _zonasOscuras.push_back(zonO);
        zonO = nullptr;
    }
    else if(strcmp(tipo, constantes.ZHIDE) == 0)
    {
        ZonaEscondite* zonE= new ZonaEscondite(ancho,largo,alto,tipo,false);
        calcID = _zonasEscondite.size();
        zonE->setID(calcID);
        zonE->setPosiciones(x,y,z);
        zonE->SetSala(sala);
        _zonasEscondite.push_back(move(zonE));
        zonE = nullptr;
    }

}

//lo utilizamos para crear su modelo en motorgrafico y su objeto
void CargadorNiveles::CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z,
    int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades, unsigned short tipoObj, const char * anima , int frame)
{
    int posicionObjeto;
    switch (tipoObj)
    {
        case 1: // LLAVE
        {
            ancho = 2;
            largo = 2;
            alto = 2;
            Recolectable* _rec = new Recolectable(++id,ancho,largo,alto,x,y,z,tipoObj,despX, despZ);
            posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,ancho,largo,alto,_rec->GetModelo(),_rec->GetTextura());
            _rec->SetPosicionArrayObjetos(posicionObjeto);
            _rec->setCodigo(codigo);
            _llaves.push_back(move(_rec));
            _rec = nullptr;
        }
        break;

        case 0: // PALANCAS
        {
            Palanca* _palanca = new Palanca(++id, codigo,
                ancho,largo,alto,x,y,z,tipoObj,despX,despZ,accion);

            posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,
                ancho,largo,alto,_palanca->GetModelo(),_palanca->GetTextura());
            _palanca->SetPosicionArrayObjetos(posicionObjeto);
            _palancas.push_back(move(_palanca));
            _palanca = nullptr;
        }
        break;

        case 2: // PUERTA2
        case 3: // PUERTA
        {
            Puerta* _puerta = new Puerta(++id, codigo,
                ancho,largo,alto,x,y,z,tipoObj,despX,despZ,accion);

            posicionObjeto = _motor->CargarObjetos(accion,0,x,y,z,
                ancho,largo,alto,_puerta->GetModelo(),_puerta->GetTextura());
            _puerta->SetPosicionArrayObjetos(posicionObjeto);
            _puertas.push_back(move(_puerta));
            _puerta = nullptr;
        }
        break;

        case 14: // PARED_ROMPIBLE
        {
            Pared* _par = new Pared(_paredes.size(), codigo,
                ancho,largo,alto,x,y,z,tipoObj,despX,despZ,accion);

            posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura,anima,frame);
            _par->SetPosicionArrayObjetos(posicionObjeto);
            _paredes.push_back(move(_par));
            _par = nullptr;
        }
        break;

        case 18: // OBJETOS QUE NO LE AFECTA LA LUZ
        {
            posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura,nullptr,1,false);
            _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,3,despX,despZ,false);
        }
        break;

        default:
        {
            posicionObjeto = _motor->CargarObjetos(accion,rp,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
            _fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,3,despX,despZ,false);
        }
        break;
    }

    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3,false); //esto lo ha tocado debora y yo arriba
}

void CargadorNiveles::CrearWaypoint(Sala* sala, int accion, int compartido, int ID, int x, int y, int z, int ancho, int largo, int alto, int* arrayConexiones, const char& tipoWaypoint, int sizeConexiones)
{
    Waypoint* waypoint = new Waypoint(ID, x, y, z, compartido, arrayConexiones, tipoWaypoint, sizeConexiones, alto);
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

unsigned short CargadorNiveles::CrearCofreArana(float x, float y, float z,
    float ancho, float alto, float largo, Sala* sala)
{
    CofreArana* _eneA = new CofreArana(x,y,z, 150, ancho, alto, largo, sala); // Posiciones, vida

    //_eneA->setArbol(cargadorIA.cargarBehaviorTreeXml("CofreAranyaBT"));
    _eneA->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
    _eneA->setID(++id);//le damos el id unico en esta partida al enemigo
    _eneA->SetEnemigo(constantes.ARANA);

    _eneA->setVelocidadMaxima(1.5f);
    _eneA->setBarraAtEs(0);
    _eneA->setAtaque(10);
    _eneA->setArmaEspecial(0);
    _eneA->setTimeAtEsp(0.0f);
    _eneA->setDanyoCritico(50);
    _eneA->setProAtaCritico(10);
    _eneA->setRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _eneA->setVectorOrientacion();
    _eneA->setNewRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta
    _eneA->setLastRotacion(0.0f,0.0f,0.0f);//le pasamos las coordenadas donde esta

    _eneA->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->setPosicionesAtaque(x,y,z);
    _eneA->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    _eneA->initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _eneA->initPosicionesFisicasAtaque(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    _eneA->definirSala(sala);//le pasamos la sala en donde esta
    
    //_motor->CargarEnemigos(0,0,0,_eneA->GetModelo());//creamos la figura
    _eneCofres.push_back(move(_eneA));//guardamos el enemigo en el vector
    _eneA = nullptr;

    return _eneCofres.size()-1;
}

//Cargar los cofres del nivel
void CargadorNiveles::CargarCofres()
{
    unsigned short eneAranas = chestsMax/4; // 1/4 de los cofres son enemigos
    unsigned short aranasCreadas = 0;
    unsigned short totalCofresPonible = 0;
    vector<short> zonasDisponibles;
    zonasDisponibles.reserve(chestsMax);

    //Se comprueba si hay zonas de cofres disponibles
    if(!_zonasCofre.empty())
    {
        //se contabilizan las zonas donde se pueden colocar cofres
        for(unsigned short i = 0; i < _zonasCofre.size(); i++)
        {
            //Se comprueba que es una zona de cofres y que le caben mas cofres
            if(!_zonasCofre.at(i)->getProposito())
            {
                totalCofresPonible += (_zonasCofre[i]->GetTotalElementos() - _zonasCofre[i]->GetElementosActuales());
                zonasDisponibles.push_back(i);
            }
        }
        //En caso de haber mas o el mismo numero de huecos para cofres que cofres se accede
        if(totalCofresPonible >= chestsMax)
        {
            float newx = 0;
            float newy = 0;
            float newz = 0;

            //Mientra hay cofres sin colocar, colocar en una zona aleatoria
            while(chestsMax > 0)
            {
                srand(time(NULL));
                int numAlt = rand() % zonasDisponibles.size();

                //Buscar zona donde colocar
                newx = _zonasCofre[zonasDisponibles[numAlt]]->getX();
                newy = _zonasCofre[zonasDisponibles[numAlt]]->getY();
                newz = _zonasCofre[zonasDisponibles[numAlt]]->getZ();

                //Se annade el nuevo elemento al vector de zonas
                _zonasCofre[zonasDisponibles[numAlt]]->annadirElemento();

                //Colocar cofre
                unsigned short posArrayArana = 0;
                bool esArana = false;
                if (aranasCreadas < eneAranas)
                {
                    posArrayArana = CrearCofreArana(newx,newy,newz, 2,4,2, _zonasCofre[zonasDisponibles[numAlt]]->GetSala());
                    ++aranasCreadas;
                    esArana = true;

                    // Debug: para cambiar la posicion del jugador al lado de un cofre
                    posCofre[0] = newx;
                    posCofre[1] = newy;
                    posCofre[2] = newz;
                }

                Cofre* _cofre = new Cofre(esArana, ++id,
                    newx, newy, newz,
                    constantes.COFRE_OBJ, posArrayArana,
                    _zonasCofre[zonasDisponibles[numAlt]]->GetSala(),
                    _cofres.size());

                _cofres.push_back(move(_cofre));
                _cofre = nullptr;

                //borrar del Array por que el proposito esta cumplido
                if(_zonasCofre[zonasDisponibles[numAlt]]->GetTotalElementos() == _zonasCofre[zonasDisponibles[numAlt]]->GetElementosActuales())
                {
                    _zonasCofre[zonasDisponibles[numAlt]]->setProposito(true);
                    zonasDisponibles.erase(zonasDisponibles.begin() + numAlt);
                }

                chestsMax--; //un cofre menos
            }
            zonasDisponibles.resize(0);
        }
        /*else
        {
            cout << "No hay zonas de cofres suficientes en el nivel" << endl;
        }*/
    }
}

int* CargadorNiveles::GetID()
{
    return &id;
}

void CargadorNiveles::TrasladarJugadorACofres()
{
    unsigned short desplaza = 10;
    _jugador->setPosiciones(posCofre[0]+desplaza, posCofre[1], posCofre[2]);
    _jugador->setNewPosiciones(posCofre[0]+desplaza, posCofre[1], posCofre[2]);
    _jugador->initPosicionesFisicas((posCofre[0]+desplaza)/2, posCofre[1]/2, posCofre[2]/2);
}
