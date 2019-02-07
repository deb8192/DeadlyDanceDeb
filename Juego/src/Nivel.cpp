#include "Nivel.hpp"
#include "Pathfinder.hpp"
#include <math.h>
#include "reactphysics3d.h"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton

#define PIRADIAN 180.0f
#define PI 3.14159265358979323846
#define PALANCA "palanca"

Nivel::Nivel()
{
    primeraSala = nullptr;
    //fisicas = MotorFisicas::getInstance();//cogemos la instancia del motor de las fisicas
    id = 0;
    ejecutar = false;
    destinoPathFinding = nullptr;
    fisicas = MotorFisicas::getInstance();//cogemos la instancia del motor de las fisicas
    id = 0;
    controladorTiempo = times::getInstance();//obtenemos la instancia de la clase times
    drawTime = 0.0f;
    lastDrawTime = drawTime;
}

void Nivel::LimpiarNivel()
{

    //para ejecucion de la ia y interpolado

    id = 0;//se vuelve a cero pq la proxima vez que entre se inicializa todo a 0

    cout << "se entra en borrar enemigos" << endl;

    borrarEnemigos();

    if(recolectables.size() > 0)
    {
        for(std::size_t i=0 ; i < recolectables.size() ; i++)
        {
            int numero = (int)i;
            delete recolectables[numero];
            recolectables[i] = nullptr;
        }

        recolectables.resize(0);
    }

    if(interactuables.size() > 0)
    {
        for(std::size_t i=0 ; i < interactuables.size() ; i++)
        {
            delete interactuables[i];
            interactuables[i] = nullptr;
        }

        interactuables.resize(0);
    }

    if(zonas.size() > 0)
    {
        for(std::size_t i=0 ; i < zonas.size() ; i++)
        {
            delete zonas[i];
            zonas[i] = nullptr;
        }

        zonas.resize(0);
    }

    if(powerup.size() > 0)
    {
        for(std::size_t i=0 ; i < powerup.size() ; i++)
        {
            delete powerup[i];
            powerup[i] = nullptr;
        }

        powerup.resize(0);
    }

    //jugador.~Jugador();//limpiamos jugador
    jugador = Jugador();//volvemos a crear jugador

}

bool Nivel::CargarNivel(int level)
{
    NoEjecutar();//se impide entrar en bucles del juego

    MotorGrafico * motor = MotorGrafico::getInstance();
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();

    motor->borrarScena();//borramos la scena

    //pre limpiamos todo
    motor->LimpiarMotorGrafico();
    LimpiarNivel();
    fisicas->limpiarFisicas();
    //limpiammos la sala
    if(primeraSala != nullptr)
    {
        primeraSala->~Sala();
        primeraSala = nullptr;
    }
    //cargamos el nivel
    cargador.CargarNivelXml(level);
    //Cargar objetos con el nivel completo
    this->cargarCofres(2); //Cargamos los cofres del nivel

    motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    motora->getEvent("Nivel1")->start(); //Reproducir musica juego

    motor->cargarInterfaz();
    //esta ya todo ejecutamos ia y interpolado
    Ejecutar();
    //devolvemos true si todo a ido bien
    return true;
}

void Nivel::CrearEnemigo(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades, Sala * sala)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    //accion indicara futuramente que tipo de enemigo sera (herencia)
    MotorGrafico * motor = MotorGrafico::getInstance();//cogemos instancia del motor para crear la figura 3d
    pollo * ene = new pollo();//aqui va el tipo de enemigo que es hacer ifffffffffsssss y meter una variable nueva de tipo para saber que tipo es
    //ia
        //cargadorIA.cargarBehaviorTreeXml("PolloBT");
        ene->setArbol(cargadorIA.cargarBehaviorTreeXml("PolloBT"));
    //fin ia
    ene->setPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    ene->setNewPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    ene->setLastPosiciones(x,y,z);//le pasamos las coordenadas donde esta
    ene->Enemigo::initPosicionesFisicas(x/2,y/2,z/2);//le pasamos las coordenadas donde esta
    ene->setVida(75);
    ene->setVelocidad(2.0f);
    ene->setBarraAtEs(0);
    ene->definirSala(sala);//le pasamos la sala en donde esta
    ene->setAtaque(10);
    ene->setArmaEspecial(100);
    ene->setTimeAtEsp(0.0f);
    ene->setDanyoCritico(50);
    ene->setProAtaCritico(10);
    //ene->generarSonido(20,5);
    ene->setRotation(0.0f);//le ponemos hacia donde mira cuando se carga
    enemigos.push_back(ene);//guardamos el enemigo en el vector
    id++;//generamos id para la figura
    ene->setID(id);//le damos el id unico en esta partida al enemigo

    motor->CargarEnemigos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);//creamos la figura pasando el id
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,2);
    fisicas->crearCuerpo(0,x/2,y/2,z/2,2,1,1,1,7); //Para ataques
    fisicas->crearCuerpo(0,x/2,y/2,z/2,2,4,4,4,8); //Para ataques especiales

    //Cargar sonido evento en una instancia con la id del enemigo como nombre
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();
    std::string nameid = std::to_string(id); //pasar id a string
    motora->LoadEvent("event:/SFX/SFX-Pollo enfadado",nameid);
    motora->getEvent(nameid)->setPosition(x,y,z);
    motora->getEvent(nameid)->setVolume(0.4f);
    motora->getEvent(nameid)->start();
}

void Nivel::recargarJugador(){
    jugador.setVida(100);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setTimeAtEsp(0.0f);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    jugador.setVida(100);
    jugador.setPosiciones(getjix(),getjiy(),getjiz());
}

void Nivel::setjix(int x){
    this->jix =x ;
}
void Nivel::setjiy(int y){
    this->jiy = y;
}
void Nivel::setjiz(int z){
    this->jiz = z;
}

int Nivel::getjix(){
    return this->jix;
}
int Nivel::getjiy(){
    return this->jiy;
}
int Nivel::getjiz(){
    return this->jiz;
}

void Nivel::CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    this->setjix(x);
    this->setjiy(y);
    this->setjiz(z);
    jugador.setVida(100);
    jugador.setID(id++);
    jugador.setBarraAtEs(100);
    jugador.setAtaque(15);
    jugador.setArma(NULL);
    jugador.setArmaEspecial(100);
    jugador.setTimeAtEsp(0.0f);
    jugador.setDanyoCritico(50);
    jugador.setProAtaCritico(10);
    jugador.setVida(100);
    jugador.setPosiciones(x,y,z);
    MotorGrafico * motor = MotorGrafico::getInstance();

    motor->CargarJugador(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    cout << x << " " << y << " " << z << " " << endl;
    motor->CargarArmaEspecial(x,y,z,jugador.getRutaArmaEsp(),"");
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,3,2,2,2,1);//creamos el cuerpo y su espacio de colisiones en el mundo de las fisicas

}

void Nivel::CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    int posicionObjeto;

    //Arma
    if(accion == 2)
    {
        posicionObjeto = motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura);
        rec->setID(recolectables.size());
        rec->setPosiciones(x,y,z);
        rec->SetPosicionArrayObjetos(posicionObjeto);
        recolectables.push_back(rec);
    }else
    //Puertas o interruptores
    if(accion == 3)
    {
        posicionObjeto = motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Interactuable * inter = new Interactuable(codigo, nombre, ancho, largo, alto, ruta_objeto, ruta_textura, posicionObjeto);
        inter->setID(id++);
        inter->setPosiciones(x,y,z);
        inter->SetPosicionArrayObjetos(posicionObjeto);
        inter->setDesplazamientos(despX,despZ);
        inter->setRotacion(0.0,0.0,0.0);
        interactuables.push_back(inter);
    }else
    //Powerups
    if(accion == 4)
    {
        posicionObjeto = motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
        Recolectable* rec = new Recolectable(codigo,ataque,nombre,ancho,largo,alto,ruta_objeto,ruta_textura);
        rec->setID(powerup.size());
        rec->setPosiciones(x,y,z);
        rec->SetPosicionArrayObjetos(posicionObjeto);
        rec->setCantidad(propiedades[0]); //cantidad
        powerup.push_back(rec);
    }else
    {
        posicionObjeto = motor->CargarObjetos(accion,x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    }

    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,3);
    //motor->debugBox(x,y,z,ancho,alto,largo);
    //fisicas->crearCuerpo(x,y,z,1,10,10,10,3); //esto lo ha tocado debora y yo arriba

}

void Nivel::CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char *tipo, int * propiedades)//lo utilizamos para crear zonas
{
   //Crear zona
   Zona* zon = new Zona(ancho,largo,alto,tipo);

   //ID propia y posicion
   int calcID = zonas.size();
   zon->setID(calcID);
   zon->setPosiciones(x,y,z);

   //guardarla en el nivel
   zonas.push_back(zon);

 }

//Cargar los cofres del nivel
void Nivel::cargarCofres(int num)
{
  long unsigned int num_cofres = num;
  MotorGrafico * motor = MotorGrafico::getInstance();

  if(!zonas.empty())
  {
    if(zonas.size() >= num_cofres)
    {
      //Buscar zonas sin proposito y guardar posicion en vector
      std::vector<int> Zsinprop;
      for(int i = zonas.size(); i > 0; i--)
      {
        std::string name_tipo(zonas.at(i-1)->getTipo());
        char * cadena_tipo = new char[sizeof(name_tipo)];
        strcpy(cadena_tipo, name_tipo.c_str());

        if(strcmp(cadena_tipo,"zChest") == 0) //Si es zona de cofre
        {
          if(zonas.at(i-1)->getProposito() == false) //Y no ha cumplido su proposito
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
        zonas[Zsinprop[numAlt]]->setProposito(true);

        //Buscar zona donde colocar
        float newx = zonas[Zsinprop[numAlt]]->getX();
        float newy = zonas[Zsinprop[numAlt]]->getY();
        float newz = zonas[Zsinprop[numAlt]]->getZ();

        //Colocar cofre
        int posicionObjeto = motor->CargarObjetos(3,newx,newy,newz,2,2,2,"assets/models/Cofre/ChestCartoon.obj", "assets/models/Cofre/ChestCartoon.mtl");
        Interactuable * inter = new Interactuable(-1,"Cofre",2,2,2,"assets/models/Cofre/ChestCartoon.obj","assets/models/Cofre/ChestCartoon.mtl", posicionObjeto);
        inter->setID(id++);
        inter->setPosiciones(newx,newy,newz);
        inter->SetPosicionArrayObjetos(posicionObjeto);
        inter->setRotacion(0.0,0.0,0.0);
        interactuables.push_back(inter);

        //Fisicas del cofre
        MotorFisicas* fisicas = MotorFisicas::getInstance();
        fisicas->crearCuerpo(3,newx/2,newy/2,newz/2,2,2,4,2,3);

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

Sala * Nivel::CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char *ruta_objeto, const char *ruta_textura)//lo utilizamos para crear su modelo en motorgrafico y su objeto
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    Sala * sala = new Sala(ancho,largo,alto,x,y,z,centro);
    //int * datos = sala->getSizes(); //para comprobar la informacion de la sala
    //cout << "\e[36m datos de la sala: \e[0m" << datos[0] << " " << datos[1]  << " " << datos[2] << " " << datos[3] << " " << datos[4] << endl;
    int id = motor->CargarPlataformas(x,y,z,ancho,largo,alto,ruta_objeto,ruta_textura);
    sala->definirID(id);

    MotorFisicas* fisicas = MotorFisicas::getInstance();
    fisicas->crearCuerpo(accion,x/2,y/2,z/2,2,ancho,alto,largo,6);

    if(primeraSala == nullptr)
    {
        primeraSala = sala;
    }

    return sala;
}

void Nivel::CrearLuz(int x,int y,int z)
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    motor->CargarLuces(x,y,z);
}

void Nivel::setThen()
{   //variables de la interpolacion
    currentTime = clock();
	acumulator = 0.0f;
    dt =1.0f/60.0f;
}

void Nivel::EraseEnemigo(std::size_t i){
    //Eliminar sonido
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();
    std::string nameid = std::to_string(enemigos[i]->getID()); //pasar id a string
    motora->getEvent(nameid)->stop();

    //elimniar el objeto en memoria(la onda)
    enemigos[i]->~Enemigo();//el destructor de enemigo
    enemigos[i]=nullptr;
    enemigos.erase(enemigos.begin() + i);//begin le suma las posiciones

    //cout <<"que eres?" << i <<endl;
}
void Nivel::EraseJugador(){
    jugador.~Jugador();//el destructor de jugador
    //jugador=NULL;
}



void Nivel::CogerObjeto()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();

    long unsigned int rec_col = fisicas->collideColectable();
        jugador.setAnimacion(4);

        //En caso de no ser llaves
        if(recolectables.at(rec_col)->getCodigo() == 0)
        {
            if(jugador.getArma() == nullptr)//si no tiene arma equipada
            {
                //creamos una nueva arma a partir del recolectable con el que colisionamos //Arma* nuArma = (Arma)recolectables[rec_col];
                Arma* nuArma = new Arma(recolectables[rec_col]->getAtaque(),recolectables[rec_col]->getNombre(),recolectables[rec_col]->getAncho(),recolectables[rec_col]->getLargo(),recolectables[rec_col]->getAlto(),recolectables[rec_col]->getObjeto(),recolectables[rec_col]->getTextura());
                jugador.setArma(nuArma);
                //PROVISIONAL
                jugador.getArma()->setRotacion(0.0, PIRADIAN, 0.0);
                //!PROVISIONAL
                //lo cargamos por primera vez en el motor de graficos
                motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), recolectables[rec_col]->getObjeto(), recolectables[rec_col]->getTextura());
                //lo cargamos por primera vez en el motor de fisicas
                fisicas->crearCuerpo(0,jugador.getX()/2,jugador.getY()/2,jugador.getZ()/2,2,recolectables[rec_col]->getAncho(), recolectables[rec_col]->getLargo(), recolectables[rec_col]->getAlto(), 6);
                //borramos el recolectable de nivel, motor grafico y motor fisicas
                recolectables.erase(recolectables.begin() + rec_col);
                motor->EraseColectable(rec_col);
                fisicas->EraseColectable(rec_col);
                atacktime = 0.0f; //Reiniciar tiempo de ataques
            }
            else if(jugador.getArma() != nullptr)//si tiene arma equipada
            {
                //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
                Recolectable* nuRec = new Recolectable(0, jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
                nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
                Arma* nuArma = new Arma(recolectables[rec_col]->getAtaque(),recolectables[rec_col]->getNombre(),recolectables[rec_col]->getAncho(),recolectables[rec_col]->getLargo(),recolectables[rec_col]->getAlto(),recolectables[rec_col]->getObjeto(),recolectables[rec_col]->getTextura());
                motor->EraseArma();
                jugador.setArma(nuArma);
                //PROVISIONAL
                jugador.getArma()->setRotacion(0.0, PIRADIAN, 0.0);
                //!PROVISIONAL
                //lo cargamos por primera vez en el motor de graficos
                motor->CargarArmaJugador(jugador.getX(), jugador.getY(), jugador.getZ(), recolectables[rec_col]->getObjeto(), recolectables[rec_col]->getTextura());
                //lo cargamos en el motor de fisicas
                fisicas->setFormaArma(jugador.getX()/2, jugador.getY()/2, jugador.getZ()/2, jugador.getArma()->getAncho(), jugador.getArma()->getLargo(),jugador.getArma()->getAlto());
                //borramos el recolectable anterior de nivel, motor grafico y motor fisicas
                recolectables.erase(recolectables.begin() + rec_col);
                motor->EraseColectable(rec_col);
                fisicas->EraseColectable(rec_col);
                //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
                recolectables.push_back(nuRec);
                fisicas->setFormaRecolectable(recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
                motor->CargarRecolectable(recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
                atacktime = 0.0f; //Reiniciar tiempo de ataques
            }
        }
        else if(recolectables.at(rec_col)->getCodigo() > 0)
        {
            Llave *llave = new Llave(recolectables.at(rec_col)->getCodigo());
            jugador.AnnadirLlave(llave);
            //borramos el recolectable de nivel, motor grafico y motor fisicas
                recolectables.erase(recolectables.begin() + rec_col);
                motor->EraseColectable(rec_col);
                fisicas->EraseColectable(rec_col);
        }

}

void Nivel::DejarObjeto()
{
    MotorFisicas * fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();

        if(jugador.getArma() != nullptr)//si tiene arma equipada
        {
            //si ya llevaba un arma equipada, intercambiamos arma por el recolectable
            Recolectable* nuRec = new Recolectable(0, jugador.getArma()->getAtaque(),jugador.getArma()->getNombre(),jugador.getArma()->getAncho(),jugador.getArma()->getLargo(), jugador.getArma()->getAlto(),jugador.getArma()->getObjeto(),jugador.getArma()->getTextura());
            nuRec->setPosiciones(jugador.getX(),jugador.getY(), jugador.getZ());
            motor->EraseArma();
            fisicas->EraseArma();
            jugador.setArma(NULL);

            //por ultimo creamos un nuevo y actualizamos informacion en motores grafico y fisicas
            recolectables.push_back(nuRec);
            fisicas->setFormaRecolectable(recolectables.size(),nuRec->getX()/2, nuRec->getY()/2,nuRec->getZ()/2,nuRec->getAncho(), nuRec->getLargo(),nuRec->getAlto());
            motor->CargarRecolectable(recolectables.size(),nuRec->getX(), nuRec->getY(),nuRec->getZ(),nuRec->getObjeto(), nuRec->getTextura() );
        }

}

/*********** AccionarMecanismo ***********
 * Funcion que, en funcion del valor codigo
 * del interactuable al que apunte int_col,
 * si es -1 abre un cofre, si es 0 abre una puerta
 * sin llave y si es mayor que 0 abrira la puerta
 * indicada si el jugador tiene su llave.
 *      Entradas:
 *                  int_col: indicador del elemento en el vector de interactuables
 *      Salidas:
*/
void Nivel::crearObjetoCofre(Interactuable* newobjeto)
{
  //Aleaotrio
  srand(time(NULL));
  int ntipos = 3;
  int tipobj = 1 + rand() % ntipos; //aleatorio entre 1 y n tipos de objetos

  int accion;
  int x = newobjeto->getX() + 5;
  int y = newobjeto->getY();
  int z = newobjeto->getZ();
  int ancho = 2 ,largo = 2,alto = 2;
  int codigo,ataque;
  const char *nombre, *modelo, *textura;
  int * propiedades = new int [6];

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

void Nivel::AccionarMecanismo(int int_col)
{
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();
    unsigned int i = 0;
    bool coincide = false;
    //Si es una puerta sin llave o palanca asociada
    if(interactuables.at(int_col)->getCodigo() == 0)
    {
        //Se acciona o desacciona el mecanismo segun su estado actual
        bool abrir = interactuables.at(int_col)->accionar();
        unsigned int posicion = fisicas->GetRelacionInteractuablesObstaculos(int_col);
        if(abrir)
        {
            //Se abre/acciona la puerta / el mecanismo
            //sonido
            //motora->getEvent("AbrirPuerta")->setVolume(0.8f);
            motora->getEvent("AbrirPuerta")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
            motora->getEvent("AbrirPuerta")->start();
            interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() + 135.0, interactuables.at(int_col)->getRZ());
            fisicas->updatePuerta(interactuables.at(int_col)->getX(), interactuables.at(int_col)->getY(), interactuables.at(int_col)->getZ(), interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() +135.0, interactuables.at(int_col)->getRZ(), interactuables.at(int_col)->GetDesplazamientos() , posicion);
            cout<<"Abre la puerta"<<endl;
        }
        else
        {
            //Se cierra/desacciona la puerta / el mecanismo
            motora->getEvent("CerrarPuerta")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
            motora->getEvent("CerrarPuerta")->start();
            interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() - 135.0, interactuables.at(int_col)->getRZ());
            fisicas->updatePuerta(interactuables.at(int_col)->getX(), interactuables.at(int_col)->getY(), interactuables.at(int_col)->getZ(), interactuables.at(int_col)->getRX(), - interactuables.at(int_col)->getRY(), interactuables.at(int_col)->getRZ(), interactuables.at(int_col)->GetDesplazamientos(), posicion);
            cout<<"Cierra la puerta"<<endl;
        }
    }
    else if(interactuables.at(int_col)->getCodigo() == -1)
    {
       //Cofre no abierto
        if(!interactuables.at(int_col)->getAccionado())
        {
          //Se abre el cofre (Animacion)
          interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY(), interactuables.at(int_col)->getRZ() + 80.0);
          cout << "Abres el cofre" << endl;
          interactuables.at(int_col)->accionar();

          //Crear objeto aleatorio
          this->crearObjetoCofre(interactuables.at(int_col));

        }
        else
        {
          cout << "Cofre ya abierto" << endl;
        }

    }
    else if(std::strcmp(interactuables.at(int_col)->getNombre(), PALANCA) == 0)
    {
        i = 0;
        coincide = false;
        //PRUEBAS CON PALANCAS
        while(i < interactuables.size() && !coincide)
        {
            if(interactuables.at(i)->getCodigo() == interactuables.at(int_col)->getCodigo())
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
            bool activar = interactuables.at(int_col)->accionar();
            bool abrir = interactuables.at(i)->accionar();
            unsigned int posicion = fisicas->GetRelacionInteractuablesObstaculos(i);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                motora->getEvent("AbrirPuerta")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
                motora->getEvent("AbrirPuerta")->start();
                interactuables.at(i)->setNewRotacion(interactuables.at(i)->getRX(), interactuables.at(i)->getRY() + 135.0, interactuables.at(i)->getRZ());
                fisicas->updatePuerta(interactuables.at(i)->getX(), interactuables.at(i)->getY(), interactuables.at(i)->getZ(), interactuables.at(i)->getRX() + 100.0, interactuables.at(i)->getRY(), interactuables.at(i)->getRZ(), interactuables.at(i)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                motora->getEvent("CerrarPuerta")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
                motora->getEvent("CerrarPuerta")->start();
                interactuables.at(i)->setNewRotacion(interactuables.at(i)->getRX(), interactuables.at(i)->getRY() - 135.0, interactuables.at(i)->getRZ());
                fisicas->updatePuerta(interactuables.at(i)->getX(), interactuables.at(i)->getY(), interactuables.at(i)->getZ(), interactuables.at(i)->getRX(), - interactuables.at(i)->getRY(), interactuables.at(i)->getRZ(), interactuables.at(i)->GetDesplazamientos(), posicion);
                cout<<"Cierra la puerta"<<endl;
            }

            if(activar)
            {
                //Se abre/acciona la puerta / el mecanismo
                interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY(), interactuables.at(int_col)->getRZ()+50);
                cout<<"Acciona la palanca"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY(), interactuables.at(int_col)->getRZ()-50);
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
            if(jugador.GetLlaves().at(i)->GetCodigoPuerta() == interactuables.at(int_col)->getCodigo())
            {
                coincide = true;
            }
            i++;
        }
        if(coincide)
        {
            cout<<"Tiene la llave para abrir la puerta"<<endl;
            //Se acciona o desacciona el mecanismo segun su estado actual
            bool abrir = interactuables.at(int_col)->accionar();
            unsigned int posicion = fisicas->GetRelacionInteractuablesObstaculos(int_col);
            if(abrir)
            {
                //Se abre/acciona la puerta / el mecanismo
                motora->getEvent("AbrirCerradura")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
                motora->getEvent("AbrirCerradura")->start();
                interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() + 135.0, interactuables.at(int_col)->getRZ());
                fisicas->updatePuerta(interactuables.at(int_col)->getX(), interactuables.at(int_col)->getY(), interactuables.at(int_col)->getZ(), interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() +135.0, interactuables.at(int_col)->getRZ(), interactuables.at(int_col)->GetDesplazamientos(), posicion);
                cout<<"Abre la puerta"<<endl;
            }
            else
            {
                //Se cierra/desacciona la puerta / el mecanismo
                motora->getEvent("CerrarPuerta")->setPosition(interactuables.at(int_col)->getX(),interactuables.at(int_col)->getY(),interactuables.at(int_col)->getZ());
                motora->getEvent("CerrarPuerta")->start();
                interactuables.at(int_col)->setNewRotacion(interactuables.at(int_col)->getRX(), interactuables.at(int_col)->getRY() - 135.0, interactuables.at(int_col)->getRZ());
                fisicas->updatePuerta(interactuables.at(int_col)->getX(), interactuables.at(int_col)->getY(), interactuables.at(int_col)->getZ(), interactuables.at(int_col)->getRX(), - interactuables.at(int_col)->getRY(), interactuables.at(int_col)->getRZ(), interactuables.at(int_col)->GetDesplazamientos(), posicion);
                cout<<"Cierra la puerta"<<endl;
            }
        }
    }

}
/************************** InteractualNivel *************************
* Detecta las posiciones de los objetos recolectables y de interaccion
* y si está pulsado E interactua y si no lo pinta de color para destacarlo
*/
void Nivel::InteractuarNivel()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();
    //lo siguiente es para saber que objeto colisiona con jugador
    int rec_col = fisicas->collideColectable();
    int int_col = fisicas->collideInteractuable();

    //cambia se utiliza porque coge y suelta el objeto sucesivamente varias veces, la causa de este error
    //era porque ocurren varias iteraciones del bucle tal vez porque la interpolacion crea mas iteraciones en el bucle
    if(motor->estaPulsado(KEY_E))
    {
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
        motor->resetKey(KEY_E);
    }
    else{
        cambia = 0;
    }
    //cout << "cambia: " << cambia << endl; //esto es para ver cuantas iteraciones de bucle pasan cuando coge objeto
}
/************** Update *************
 * Bucle de actualizacion del juego
 * Entradas:
 *
 * Salidas:
 */
void Nivel::update()
{
    MotorGrafico * motor = MotorGrafico::getInstance();

    if(motor->estaPulsado(KEY_J))
    {
        jugador.QuitarVida(20);
        motor->resetKey(KEY_J);
    }

    if(ejecutar)
    {
        MotorFisicas* fisicas = MotorFisicas::getInstance();
        MotorAudioSystem* motora = MotorAudioSystem::getInstance();


        //animacion
        motor->cambiarAnimacionJugador(jugador.getAnimacion());

        //valores nuevos de interpolacion


        //Interpolacion SE SUSTITUIRA
        /*newTime = clock();
        frameTime = newTime - currentTime;
        if(frameTime>0.25f)
        {
            frameTime=0.25f;
        }
        currentTime = newTime;
        acumulator += frameTime;*/
        //while(acumulator >= dt)
        //{

        if(jugador.getArma() != nullptr)
        {
            float posArmaX = 5 * sin(PI * jugador.getRY() / PIRADIAN) + jugador.getX();
            float posArmaZ = 5 * cos(PI * jugador.getRY() / PIRADIAN) + jugador.getZ();;
            //iguala la posicion del arma a la del jugador y pasa a los motores las posiciones
            jugador.getArma()->setPosiciones(posArmaX, jugador.getY()+3, posArmaZ);
            motor->llevarObjeto(posArmaX, jugador.getY()+3,posArmaZ, jugador.getRX(), jugador.getRY(), jugador.getRZ() );
            fisicas->llevarBox(posArmaX, jugador.getY()+3,posArmaZ, jugador.getArma()->getAncho(), jugador.getArma()->getLargo(), jugador.getArma()->getAlto());
        }

        //Comprueba la activacion de un powerup
        this->activarPowerUp();

        //adelanta posicion del bounding box al jugador, mientras pulses esa direccion si colisiona no se mueve
        fisicas->colisionChecker(motor->estaPulsado(1),
            motor->estaPulsado(2),
            motor->estaPulsado(3),
            motor->estaPulsado(4),
            jugador.getNewX(),
            jugador.getNewY(),
            jugador.getNewZ()
        );

        //colisiones con todos los objetos y enemigos que no se traspasan
        if(fisicas->collideObstacle() || !fisicas->collidePlatform())
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

        //actualizamos movimiento del jugador

            jugador.movimiento(jugadorInmovil,
                motor->estaPulsado(1),
                motor->estaPulsado(2),
                motor->estaPulsado(3),
                motor->estaPulsado(4)
            );

            motor->clearDebug2();   //Pruebas debug
            for(unsigned int i = 0; i < enemigos.size(); i++)
            {
                fisicas->updateEnemigos(enemigos.at(i)->getFisX(),
                    enemigos.at(i)->getFisY(),
                    enemigos.at(i)->getFisZ(),
                    i
                );
                motor->dibujarObjetoTemporal(enemigos.at(i)->getFisX(), enemigos.at(i)->getFisX(), enemigos.at(i)->getFisX(), enemigos.at(i)->getRX(), enemigos.at(i)->getRY(), enemigos.at(i)->getRZ(),5, 5, 5, 2);

            }

            fisicas->updateJugador(jugador.getX(),
                jugador.getY(),
                jugador.getZ()
            );

            if(enemPideAyuda != nullptr)   //Solo llama desde aqui a pathfinding si hay un enemigo pidiendo ayuda y enemigos buscandole.
            {
                this->updateRecorridoPathfinding(nullptr);
            }

        //this->updateIA(); esto no se fuerza desde el update normal se llama desde main 4 veces por segundo
        //Actualizar ataque especial
            this->updateAtEsp(motor);
            this->updateAt(&danyo2, motor);

            //Si se realiza el ataque se comprueban las colisiones
            if(jugador.getTimeAtEsp() > 0.0)
            {
                jugador.AtacarEspecialUpdate(&danyo);
            }

            else if(jugador.getTimeAt() > 0.0)
            {
                jugador.AtacarUpdate(danyo2);
            }
            //En caso contrario se colorean los enemigos de color gris
            else
            {
                for(unsigned int i = 0; i < enemigos.size(); i++)
                {
                    motor->colorearEnemigo(255, 150, 150, 150, i);
                }
            }

        //Posicion de escucha
        motora->setListenerPosition(jugador.getX(),jugador.getY(),jugador.getZ());

        //actualizamos los enemigos
        if(enemigos.size() > 0)//posiciones interpolacion
        {
            float tiempoActual = 0.0f, tiempoAtaque = 0.0f, tiempoAtaqueEsp = 0.0f;
            for(std::size_t i=0;i<enemigos.size();i++)
            {
                    int danyo_jug = 0;
                    enemigos[i]->setPosAtaques(i);
                    tiempoActual = controladorTiempo->getTiempo(2);
                    //si el tiempo de ataque es mayor que 0, ir restando tiempo hasta 0
                    if(enemigos[i]->getTimeAtEsp() > 0.0f)
                    {
                        tiempoAtaqueEsp = enemigos[i]->getTimeAtEsp();
                        tiempoAtaqueEsp -= (tiempoActual - enemigos[i]->getLastTimeAtEsp());
                        enemigos[i]->setLastTimeAtEsp(tiempoActual);
                        enemigos[i]->setTimeAtEsp(tiempoAtaqueEsp); //restar al tiempo de ataque
                    }
                    if(enemigos[i]->getTimeAtEsp() <= 0.0f)
                    {
                        danyo_jug = enemigos[i]->AtacarEspecial();
                        enemigos[i]->setTimeAtEsp(10.0f); //tiempo hasta el proximo ataque
                        enemigos[i]->setLastTimeAtEsp(controladorTiempo->getTiempo(2));
                    }
                    else if(enemigos[i]->getBarraAtEs() < 100)
                    {
                        enemigos[i]->AumentarBarraAtEs(1);
                    }
                    if(danyo_jug == 0)
                    {
                        //cout << "Enemigo " << i  << " pos: " << enemigos[i]->getPosAtaques() << endl;

                        //si el tiempo de ataque es mayor que 0, ir restando tiempo hasta 0
                        if(enemigos[i]->getTimeAt() > 0.0f)
                        {
                            tiempoAtaque = enemigos[i]->getTimeAt();
                            tiempoAtaque -= (tiempoActual - enemigos[i]->getLastTimeAt());
                            enemigos[i]->setLastTimeAt(tiempoActual);
                            enemigos[i]->setTimeAt(tiempoAtaque); //restar al tiempo de ataque
                        }
                        if(enemigos[i]->getTimeAt() <= 0.0f)
                        {
                            danyo_jug = enemigos[i]->Atacar();
                            enemigos[i]->setTimeAt(1.5f); //tiempo hasta el proximo ataque
                            enemigos[i]->setLastTimeAt(controladorTiempo->getTiempo(2));
                        }
                        //Si el enemigo ha realizado danyo
                        if(danyo_jug > 0)
                        {
                            jugador.QuitarVida(danyo_jug);
                            cout<< "Vida jugador: "<< jugador.getVida() << endl;
                        }
                    }
                    //Se le quita vida con el danyo del ataque especial
                    else
                    {
                        if(danyo_jug > 0)
                        {
                            jugador.QuitarVida(danyo_jug);
                            cout<< "Vida jugador tras ataque especial: "<< jugador.getVida() << endl;
                        }
                    }
                //enemigos[i]->queVes();
            }
        }
            //jugador.MuereJugador(acumulator);
            //enemigos->MuereEnemigo(acumulator);
            //acumulator -= dt;
        //}

        //actualizamos la interfaz de jugador
        jugador.updateInterfaz();
        //actualizamos la interfaz en motor grafico
        motor->updateInterfaz();
    }
}

void Nivel::activarPowerUp()
{
    int int_cpw = fisicas->collideColectablePowerup();
    if(int_cpw >= 0)
    {
        MotorGrafico * motor = MotorGrafico::getInstance();
        bool locoges = false; //Comprobar si lo puedes coger

        //Efecto del power up (ataque) 0 = vida, 1 = energia, 2 = monedas, 3 = danyo, 4 = defensa
        if(powerup.at(int_cpw)->getAtaque() == 0 && jugador.getVida() < 100)
        {
            cout << "PowerUP! Curado 20 de vida. TOTAL:" << jugador.getVida() << endl;
            jugador.RecuperarVida(20);
            locoges = true;
        }
        else if(powerup.at(int_cpw)->getAtaque() == 1 && jugador.getBarraAtEs() < 100)
        {
            cout << "PowerUP! 50 de energia. TOTAL:" << jugador.getBarraAtEs() << endl;
            jugador.AumentarBarraAtEs(50);
            locoges = true;
        }
        else if(powerup.at(int_cpw)->getAtaque() == 2)
        {
            cout << "Recoges " << powerup.at(int_cpw)->getCantidad() << " de oro" << endl;
            jugador.AumentarDinero(powerup.at(int_cpw)->getCantidad());
            locoges = true;
        }

        if(locoges == true)
        {
            //Borrar objeto en todos los sitios
            powerup.erase(powerup.begin() + int_cpw);
            motor->ErasePowerUP(int_cpw);
            fisicas->EraseColectablePowerup(int_cpw);
        }
    }
}

void Nivel::updateAt(int *danyo, MotorGrafico *motor)
{
    if(ejecutar)
    {
        float tiempoActual = 0.0f;
        float tiempoAtaque = 0.0f;
        if((motor->estaPulsado(KEY_ESPACIO) || motor->estaPulsado(LMOUSE_DOWN)) && jugador.getTimeAt() <= 0.0f)
        {
            *danyo = jugador.Atacar();
            motor->resetKey(KEY_ESPACIO);
            motor->resetEvento(LMOUSE_DOWN);
            //atacktime = 1.5f;
            jugador.setTimeAt(1.5f);
            jugador.setLastTimeAt(controladorTiempo->getTiempo(2));
        }else{
            if(jugador.getTimeAt() > 0.0f)
            {
                tiempoActual = controladorTiempo->getTiempo(2);
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
                    motor->colorearJugador(255,255,0,0);
                }else if(atacktime > 0.0f){
                    //Colorear gris
                    motor->colorearJugador(255,150,150,150);
                }
            }

        //clear
        if(jugador.getTimeAt() <= 0.0f){
        motor->clearDebug2();
        }

    }
    }
}
void Nivel::updateAtEsp(MotorGrafico *motor)
{
    float tiempoActual = 0.0f;
    float tiempoAtaqueEsp = 0.0f;
    //Compureba si se realiza el ataque especial o si la animacion esta a medias
    if((motor->estaPulsado(RMOUSE_DOWN)||motor->estaPulsado(KEY_Q)) && jugador.getTimeAtEsp() <= 0.0)
    {
        danyo = jugador.AtacarEspecial();
        motor->resetKey(KEY_Q);
        motor->resetEvento(RMOUSE_DOWN);
        motor->colorearJugador(255, 55, 0, 255);
        if(danyo > 0)
        {
            jugador.setTimeAtEsp(1.5f);
            jugador.setLastTimeAtEsp(controladorTiempo->getTiempo(2));

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
            tiempoActual = controladorTiempo->getTiempo(2);
            tiempoAtaqueEsp = jugador.getTimeAtEsp();
            tiempoAtaqueEsp -= (tiempoActual - jugador.getLastTimeAtEsp());
            jugador.setLastTimeAtEsp(tiempoActual);
            jugador.setTimeAtEsp(tiempoAtaqueEsp);
            danyo = jugador.AtacarEspecial();
        }
        /*if(jugador.getTimeAtEsp() > 0.f && ((int) (jugador.getTimeAtEsp() * 100) % 10 >= 4) && ((int) (jugador.getTimeAtEsp() * 100) % 10 <= 4))
        {
            danyo = jugador.AtacarEspecial();
        }*/
        if(jugador.getTimeAtEsp() == 1.0f)
        {
            motor->colorearEnemigo(255,255,255,255,0);
        }
        if(jugador.getTimeAtEsp() <= 0.5f && motor->getArmaEspecial()) //Zona de pruebas
        {
            motor->borrarArmaEspecial();
            motor->colorearJugador(255, 150, 150, 150);
        }
    }
}

void Nivel::updateIA()
{
    //bool quehay = ejecutar;
    if(ejecutar)
    {
        //cout<< "Ejecuto ia " << endl;
        MotorGrafico * motor = MotorGrafico::getInstance();

        //En esta parte muere jugador
        if(motor->estaPulsado(KEY_J)){//SI PULSO 'J' MUERE JUGADOR
            jugador.MuereJugador();
        }
        if(jugador.estasMuerto()){
            if(jugador.estasMuerto() && jugador.finalAnimMuerte())
            {
                NoEjecutar();//se dehsabilita ejecucion de updates
                return;
            }else{
                if(jugador.estasMuerto()){
                    jugador.MuereJugador();
                }
            }
        }

        //En esta parte muere enemigo
        if(enemigos.size() > 0){
            //comprobando los enemigos para saber si estan muertos
            for(std::size_t i=0;i<enemigos.size();i++){// el std::size_t es como un int encubierto, es mejor

                if(enemigos[i]->estasMuerto() && enemigos[i]->finalAnimMuerte()){

                    //Crear un power-up/dinero
                    //Se crea un power-up?
                    srand(time(NULL));
                    int secreapower = rand() % 101; //Entre 0 y 100

                    if(secreapower <= 100){ //20% de posibilidades
                      //Cual power-up? (ataque) 0 = vida, 1 = energia, 2 = monedas
                      srand(time(NULL));
                      int numpow = 3;
                      int cualpower = rand() % numpow;
                      cout << "POWER: " << cualpower << endl;
                      int ataque;
                      const char *nombre,*modelo,*textura;

                      //DAtos comunes a todos
                      int x = enemigos[i]->getX();
                      int y = enemigos[i]->getY();
                      int z = enemigos[i]->getZ();
                      int accion = 4;
                      int ancho = 0.5 ,largo = 0.5,alto = 0.5;
                      int codigo = -2;
                      int * propiedades = new int [6];

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
                    motor->EraseEnemigo(i);
                    fisicas->EraseEnemigo(i);
                    EraseEnemigo(i);

                }else{
                    if(enemigos[i]->estasMuerto()){
                        enemigos[i]->MuereEnemigo(i);
                    }
                    else
                    {
                        //si no esta muerto ni piensa morirse XD ejecutamos ia
                        //cout<< "Ejecuto ia: " << i << endl;
                        //enemigos[i]->runIA();
                    }
                }
            }
        }
    }
}


void Nivel::updateRecorridoPathfinding(Enemigo * enem)
{
    //Si enem no es nulo se anade a la cola de enemigos auxiliadores
    if(enem != nullptr && enem != enemPideAyuda )
    {
        auxiliadores.push_back(enem);
        contadorEnem--;
    }
    else if(contadorEnem > 0 && enem == enemPideAyuda)
    {
        this->setEnemigoPideAyuda(nullptr);
        destinoPathFinding = nullptr;
        contadorEnem = 0;
    }
    //Si no hay sala de destino guardada, se guarda en este momento
    else if(destinoPathFinding == nullptr)
    {
        destinoPathFinding = enemPideAyuda->getSala();
    }
    //Ejecucion del pathfinding si hay una sala de destino guardada
    if(destinoPathFinding != nullptr)
    {
        Pathfinder *path = Pathfinder::getInstance();
        int tipoCentro;

        //Se inicia el recorrido hacia la primera sala del enemigo que pide ayuda.
        if(recorrido.empty() && !auxiliadores.empty() && !path->encontrarCamino(auxiliadores.front()->getSala(), destinoPathFinding).empty())
        {
            recorrido = path->encontrarCamino(auxiliadores.front()->getSala(), destinoPathFinding);
            auxiliadores.erase(auxiliadores.begin());
        }
        //Desplazamiento del enemigo hacia su destino
        if(!recorrido.empty())
        {
            //Se comprueban las coordenadas del enemigo y si ha llegado a la siguiente
            //sala del camino a la que debe ir o no. Se tienen en cuenta los tipos de centros
            //para realizar las comprobaciones de coordenadas adecuadas con el ancho y alto de las salas
            if(auxiliadores.front()!= nullptr && auxiliadores.front()->getSala() != recorrido.front().nodo)
            {
                bool cambia = false, moveDer = false, moveIzq = false, moveArb = false, moveAbj = false;
                tipoCentro = recorrido.front().nodo->getType();
                //Centro arriba a la izquierda
                if(tipoCentro == 4)
                {
                    if(auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] && auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }
                    if(cambia && (auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] && auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la izquierda
                else if(tipoCentro == 3)
                {
                    if(auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] && auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2])
                    {
                        moveDer = true;
                    }
                    else if(auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveIzq = true;
                    }

                    if(cambia && (auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] && auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] )))
                    {
                        auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro arriba a la derecha
                else if(tipoCentro == 2)
                {
                    if(auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] && auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] && auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] )))
                    {
                        auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4])
                    {
                        moveAbj = true;
                    }
                    else if(auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveArb = true;
                    }
                }
                //Centro abajo a la derecha
                else if(tipoCentro == 1)
                {
                    if(auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] && auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        cambia = true;
                    }
                    else if(auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2])
                    {
                        moveIzq = true;
                    }
                    else if(auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0]))
                    {
                        moveDer = true;
                    }

                    if(cambia && (auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] && auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] )))
                    {
                        auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4])
                    {
                        moveArb = true;
                    }
                    else if(auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1]))
                    {
                        moveAbj = true;
                    }
                }
                //Centro en el centro
                else if(tipoCentro == 0)
                {
                    if(auxiliadores.front()->getNewX() <= recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2) && auxiliadores.front()->getNewX() >= recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        cambia = true;
                    }
                    else if(auxiliadores.front()->getNewX() > recorrido.front().nodo->getSizes()[2] + (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveIzq = true;
                    }
                    else if(auxiliadores.front()->getNewX() < recorrido.front().nodo->getSizes()[2] - (recorrido.front().nodo->getSizes()[0] / 2))
                    {
                        moveDer = true;
                    }

                    if(cambia && (auxiliadores.front()->getNewZ() <= recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2) && auxiliadores.front()->getNewZ() >= recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2)))
                    {
                        auxiliadores.front()->setSala(recorrido.front().nodo);
                        cout<<"nodo actual: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                        recorrido.erase(recorrido.begin());
                    }
                    else if(auxiliadores.front()->getNewZ() > recorrido.front().nodo->getSizes()[4] + (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveArb = true;
                    }
                    else if(auxiliadores.front()->getNewZ() < recorrido.front().nodo->getSizes()[4] - (recorrido.front().nodo->getSizes()[1] / 2))
                    {
                        moveAbj = true;
                    }
                }
                if(moveAbj)
                {
                    if(moveDer)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() + auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() + auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(auxiliadores.front()->getVelocidad(), 0.0, auxiliadores.front()->getVelocidad());
                        cout<<"Posicion del enemigo: x="<<auxiliadores.front()->getNewX()<<" z=" << auxiliadores.front()->getNewY();
                    }
                    else if(moveIzq)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() - auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() + auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(- (auxiliadores.front()->getVelocidad()), 0.0, auxiliadores.front()->getVelocidad());
                    }
                    else
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() + auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, auxiliadores.front()->getVelocidad());
                    }
                }
                else if(moveArb)
                {
                    if(moveDer)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() + auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() - auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(auxiliadores.front()->getVelocidad(), 0.0, -(auxiliadores.front()->getVelocidad()));
                    }
                    else if(moveIzq)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() - auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() - auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(- (auxiliadores.front()->getVelocidad()), 0.0, -(auxiliadores.front()->getVelocidad()));
                    }
                    else
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ() - auxiliadores.front()->getVelocidad());
                        auxiliadores.front()->setPosicionesFisicas(0.0, 0.0, -(auxiliadores.front()->getVelocidad()));
                    }
                }
                else
                {
                    if(moveDer)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() + auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ());
                        auxiliadores.front()->setPosicionesFisicas(auxiliadores.front()->getVelocidad(), 0.0, 0.0);
                    }
                    else if(moveIzq)
                    {
                        auxiliadores.front()->setNewPosiciones(auxiliadores.front()->getNewX() - auxiliadores.front()->getVelocidad(), auxiliadores.front()->getNewY(), auxiliadores.front()->getNewZ());
                        auxiliadores.front()->setPosicionesFisicas(- (auxiliadores.front()->getVelocidad()), 0.0, 0.0);
                    }
                }
            }
            else
            {
                cout<<"nodo actual donde puede que se atasque: "<<auxiliadores.front()->getSala()->getPosicionEnGrafica()<<endl;
                recorrido.erase(recorrido.begin());
                if(recorrido.empty() && auxiliadores.empty())
                {
                    destinoPathFinding = nullptr;
                    this->setEnemigoPideAyuda(nullptr);
                    contadorEnem = 0;
                }
            }
        }
    }
    contadorEnem++;
}

void Nivel::Draw()
{
    if(ejecutar)
    {
        MotorGrafico * motor = MotorGrafico::getInstance();
        //Para evitar un tran salto en el principio de la ejecucion se actualiza el valor de drawTime
        if(drawTime == 0.0)
        {
            drawTime = controladorTiempo->getTiempo(2);
        }
        lastDrawTime = drawTime;
        drawTime = controladorTiempo->getTiempo(2);

        //Dibujado del personaje
        jugador.moverseEntidad(1 / controladorTiempo->getUpdateTime());
        jugador.RotarEntidad(1 / controladorTiempo->getUpdateTime());
        jugador.UpdateTimeMove(drawTime - lastDrawTime);
        motor->mostrarJugador(jugador.getX(),
            jugador.getY(),
            jugador.getZ(),
            jugador.getRX(),
            jugador.getRY(),
            jugador.getRZ()
        );

        //Dibujado de los enemigos
        for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            enemigos.at(i)->moverseEntidad(1 / controladorTiempo->getUpdateTime());
            enemigos.at(i)->UpdateTimeMove(drawTime - lastDrawTime);
            motor->mostrarEnemigos(enemigos.at(i)->getX(),
                enemigos.at(i)->getY(),
                enemigos.at(i)->getZ(),
                enemigos.at(i)->getRX(),
                enemigos.at(i)->getRY(),
                enemigos.at(i)->getRZ(),
                i
            );
        }
        //Dibujado de las puertas
        for(unsigned int i = 0; i < interactuables.size(); i++)
        {
            interactuables.at(i)->RotarEntidad(1 / controladorTiempo->getUpdateTime());
            interactuables.at(i)->UpdateTimeRotate(drawTime - lastDrawTime);
            motor->mostrarObjetos(interactuables.at(i)->getX(),
                interactuables.at(i)->getY(),
                interactuables.at(i)->getZ(),
                interactuables.at(i)->getRX(),
                interactuables.at(i)->getRY(),
                interactuables.at(i)->getRZ(),
                interactuables.at(i)->GetPosicionObjetos()
            );
        }

        //Dibujado del ataque especial
        //Ataque especial Heavy
        if(jugador.getTimeAtEsp() > 0.0f)
        {
            if(strcmp(jugador.getArmaEspecial()->getNombre(), "Heavy") == 0)
            {
                jugador.getArmaEspecial()->moverseEntidad(1 / controladorTiempo->getUpdateTime());
                jugador.getArmaEspecial()->RotarEntidad(1 / controladorTiempo->getUpdateTime());
                jugador.getArmaEspecial()->UpdateTimeMove(drawTime - lastDrawTime);

                motor->mostrarArmaEspecial(
                    jugador.GetDatosAtEsp()[0],
                    jugador.getY(),
                    jugador.GetDatosAtEsp()[2],
                    jugador.getRX(),
                    jugador.getRY(),
                    jugador.getRZ());

                motor->clearDebug2(); //Pruebas debug

                motor->dibujarObjetoTemporal(
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
                jugador.getArmaEspecial()->moverseEntidad(1 / controladorTiempo->getUpdateTime());
                jugador.getArmaEspecial()->RotarEntidad(1 / controladorTiempo->getUpdateTime());
                jugador.getArmaEspecial()->UpdateTimeMove(drawTime - lastDrawTime);

                motor->mostrarArmaEspecial(
                    jugador.GetDatosAtEsp()[0],
                    jugador.GetDatosAtEsp()[1],
                    jugador.GetDatosAtEsp()[2],
                    jugador.GetDatosAtEsp()[3],
                    jugador.GetDatosAtEsp()[4],
                    jugador.GetDatosAtEsp()[5]);

                motor->clearDebug2(); //Pruebas debug

                motor->dibujarObjetoTemporal(
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
        for(unsigned int i = 0; i < zonas.size(); i++)
        {
            motor->dibujarZona(zonas.at(i)->getX(),
                zonas.at(i)->getY(),
                zonas.at(i)->getZ(),
                zonas.at(i)->getAncho(),
                zonas.at(i)->getAlto(),
                zonas.at(i)->getLargo()
            );
        }
    }
}

void Nivel::setEnemigoPideAyuda(Enemigo *ene)
{
    enemPideAyuda = ene;
}

Enemigo * Nivel::getEnemigoPideAyuda()
{
    return enemPideAyuda;
}

Sala * Nivel::getPrimeraSala()
{
    return primeraSala;
}

std::vector<Enemigo *>  Nivel::getEnemigos()
{
    return enemigos;
}

Jugador Nivel::getJugador()
{
    return jugador;
}


void Nivel::Ejecutar()
{
    ejecutar = true;
}

void Nivel::NoEjecutar()
{
    ejecutar = false;
}

void Nivel::borrarEnemigos()
{
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    //actualizamos el jugador
    if(enemigos.size() > 0)
    {
        for(std::size_t i=0;i<enemigos.size();i++)
        {
                fisicas->EraseEnemigo(i);
                EraseEnemigo(i);
        }
        enemigos.resize(0);//redimensionamos el vector a 0
    }
}

void Nivel::ActivarLimpieza()
{
    limpiar = true;
}

bool Nivel::EstaLimpio()
{
    return limpio;
}
