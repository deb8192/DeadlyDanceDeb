#include "MotorFisicas.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
#include <iostream>

using namespace std;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.14159265358979323846
#define PIRADIAN 180.0f

MotorFisicas* MotorFisicas::unica_instancia = 0;
//fin indicador singleton

MotorFisicas::MotorFisicas()
{
    config.defaultVelocitySolverNbIterations = 20;
    config.isSleepingEnabled = false;
    space = new CollisionWorld(config);
    jugador = nullptr;
}

void MotorFisicas::crearCuerpo(int accion, float px, float py, float pz, int type, float ancho, float alto, float largo, int typeCreator)
{
    rp3d::Vector3 posiciones(px,py,pz);
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

   if(type == 1)//esfera
   {
        SphereShape * forma = new SphereShape(ancho);
        cuerpo->addCollisionShape(forma,transformacion);
    }
    else if(type == 2)//cubo (boundingbox)
    {
        rp3d::Vector3 medidas(ancho,alto,largo);
        BoxShape * forma = new BoxShape(medidas);
        cuerpo->addCollisionShape(forma,transformacion);
    }
    else if(type == 3)//capsula (ideal para personajes)
    {
        CapsuleShape * forma = new CapsuleShape(ancho,alto);
        cuerpo->addCollisionShape(forma,transformacion);
    }
    if(typeCreator == 1)//jugador
    {
        jugador = cuerpo;
    }
    else if(typeCreator == 2)//enemigos
    {
        enemigos.push_back(cuerpo);
    }
    else if(typeCreator == 3)//objetos
    {
        //Objetos con los que interactuar como puertas
        if(accion == 3)
        {
            obstaculos.push_back(cuerpo);
            //Se le anade una zona de deteccion mediante colision
            rp3d::CollisionBody * deteccion;
            SphereShape * detector = new SphereShape(alto);
            deteccion = space->createCollisionBody(transformacion);
            deteccion->addCollisionShape(detector,transformacion);
            interactuables.push_back(deteccion);
        }
        //Objetos que recoger como armas y llaves
        if(accion == 2)
        {
            recolectables.push_back(cuerpo);
        }
        //Obstaculos que se interponen ante el jugador
        if(accion == 1)
        {
            obstaculos.push_back(cuerpo);
        }
    }
    else if(typeCreator == 6)//objetos
    {
        plataformas.push_back(cuerpo);
    }
    else if(typeCreator == 4)//ataque de jugador
    {
        jugadorAtack = cuerpo;
    }
    else if(typeCreator == 5)//objetos
    {
        armaAtEsp = cuerpo;
    }
    else if(typeCreator == 6)//objetos
    {
        arma = cuerpo;
    }
    else if(typeCreator == 7)//ataque enemigos
    {
        enemigosAtack.push_back(cuerpo);
    }
    else if(typeCreator == 8)//objetos
    {
        armaAtEspEne.push_back(cuerpo);
    }
    // std::cout << "px: " << posiciones.x << std::endl;
    // std::cout << "py: " << posiciones.y << std::endl;
    // std::cout << "pz: " << posiciones.z << std::endl;
}

void MotorFisicas::setFormaArma(float px, float py, float pz, int anc, int lar, int alt)
{

    rp3d::Vector3 posiciones(px,py,pz);
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

    rp3d::Vector3 medidas(anc,alt,lar);
    BoxShape * forma = new BoxShape(medidas);
    cuerpo->addCollisionShape(forma,transformacion);

    arma = cuerpo;
}

void MotorFisicas::EraseColectable(int idx)
{
    recolectables.erase(recolectables.begin() + idx);
}

void MotorFisicas::EraseEnemigo(std::size_t i)
{
    space->destroyCollisionBody(enemigos[i]);//nos cargamos el contenido
    enemigos[i]=nullptr;
    enemigos.erase(enemigos.begin() + i);

    space->destroyCollisionBody(enemigosAtack[i]);//nos cargamos el contenido
    enemigosAtack[i]=nullptr;
    enemigosAtack.erase(enemigosAtack.begin() + i);

    space->destroyCollisionBody(armaAtEspEne[i]);//nos cargamos el contenido
    armaAtEspEne[i]=nullptr;
    armaAtEspEne.erase(armaAtEspEne.begin() + i);
}

void MotorFisicas::EraseJugador(){
    jugador = NULL;
}

void MotorFisicas::EraseArma()
{
    arma = NULL;
}

void MotorFisicas::setFormaRecolectable(int id, float px, float py, float pz, int anc, int lar, int alt)
{

    rp3d::Vector3 posiciones(px,py,pz);
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

    rp3d::Vector3 medidas(anc,alt,lar);
    BoxShape * forma = new BoxShape(medidas);
    cuerpo->addCollisionShape(forma,transformacion);

    recolectables.push_back(cuerpo);
}

Ray * MotorFisicas::crearRayo(float x, float y, float z, float rotation, float longitud)
{
    rp3d::Vector3 inicio(x,y,z);//posicion inicial desde donde sale el rayo(desde el centro de la entidad o objeto)

    //calculamos segun la magnitud y la direccion donde debe apuntar el rayo

    float nx,ny,nz;
    float rad = PI/180*(rotation);

    ny = y;
    nx = (cos(rad)*longitud)+x;//calculamos cuanto hay que sumarle a la posicion x
    nz = (sin(rad)*longitud)+z;//calculamos cuanto hay que sumarle a la posicion z
    rp3d::Vector3 final(nx,ny,nz);

    Ray * rayo = new Ray(inicio,final);

    return rayo;
}

bool MotorFisicas::collidePlatform()
{
    for(long unsigned int i = 0; i < plataformas.size();i++)
    {
      if(space->testOverlap(jugador,plataformas[i]))
      {
        return true;
      }
    }

    return false;

}

int MotorFisicas::collideColectable()
{
    for(long unsigned int i = 0; i < recolectables.size();i++)
    {
      if(space->testOverlap(jugador,recolectables[i]))
      {
        return (int)i;
      }
    }

    return -1;
}

int MotorFisicas::collideInteractuable()
{
    for(long unsigned int i = 0; i < interactuables.size();i++)
    {
      if(space->testOverlap(jugador,interactuables[i]))
      {
        return (int)i;
      }
    }

    return -1;
}

bool MotorFisicas::collideObstacle()
{
    //abra que indicar tipo de objeto de alguna manera (que sean obstaculos)
    for(long unsigned int i = 0; i < obstaculos.size();i++)
    {
      if(space->testOverlap(jugador,obstaculos[i]))
      {
        return true;
      }
    }

    //tampoco debe intersectar en el espacio con los enemigos
    for(long unsigned int i = 0; i < enemigos.size();i++)
    {
      if(space->testOverlap(jugador,enemigos[i]))
      {
        return true;
      }
    }

    return false;
}

int * MotorFisicas::colisionRayoUnCuerpo(float x,float y,float z,float rotation,float longitud,int modo)
{

    //se recomiendan usar modos especificos para ahorrar costes.
    Ray * rayo = crearRayo(x,y,z,rotation,longitud);

    RaycastInfo intersection;

    int * jug;
    int * ene;
    int * obj;

    //creamos un puntero para saber si colisiona con el jugador (si es el jugador devolvera que no colisiona con el)
    if(modo == 1)
    {
        jug = new int[1];
        jug[0] = 0;//false - no lo ve
    }

    //creamos un puntero que devuelve solamente los objetos con los que colisiona
    if(modo == 2)
    {
        obj = new int[objetos.size()+1];
        obj[0] = (objetos.size()+1);//dimension
        for(std::size_t a = 0; a < (objetos.size()+1);a++)
        {
            if(a != 0)
            {
                obj[a] = 0;
            }
        }
    }

    //creamos un puntero que devuelve solo los enemigos con los que colisiona por defecto si este rayo sale de un enemigo no lo detecta como colision
    if(modo == 3)
    {
        ene = new int[enemigos.size()+1];
        ene[0] = (enemigos.size()+1);//dimension

        for(std::size_t a = 0; a < (enemigos.size()+1);a++)
        {
            if(a != 0)
            {
                ene[a] = 0;
            }
        }
    }

    if(modo == 0 || modo == 1)
    {
        bool colision = jugador->raycast(*rayo,intersection);

        if(colision)
        {
            if(jugador == intersection.body)
            {
                //cout << "colisiona" << endl;
                jug[0] = 1;
            }
        }
    }
    //if(intersection.body != jugador)
    //   std::cout << "CuerpoColisionado: " << " Jugador" << std::endl;
    if(modo == 0 || modo == 3)
    {
        if(enemigos.size() > 0)//posiciones interpolacion
        {
            for(std::size_t i=0;i<enemigos.size();i++)
            {
                bool colision = enemigos[i]->raycast(*rayo,intersection);

                if(intersection.body != enemigos[i])
                    if(colision)
                        ene[i+1] = 1;
            }
        }
    }

    if(modo == 0 || modo == 2)
    {
        if(objetos.size() > 0)//posiciones interpolacion
        {
            for(std::size_t i=0;i<objetos.size();i++)
            {
                bool colision = objetos[i]->raycast(*rayo,intersection);

                if(intersection.body != objetos[i])
                    if(colision)
                        obj[i+1] = 1;
            }
        }
    }

    //por ultimo destruimos el objeto
    delete rayo;

    //devolvemos colisiones
    switch(modo)
    {
        case 1:
            return jug;
        case 2:
            return obj;
        case 3:
            return ene;
    }

    return nullptr;

}
void MotorFisicas::colisionChecker(bool a, bool s, bool d, bool w, float x, float y, float z)
{
    //cout << "arma: " << arma << endl;

    float px = x,
          pz = z;
    if(a)
     px -= 2;
    if(s)
     pz -= 2;
    if(d)
     px += 2;
    if(w)
     pz += 2;

    if(jugador != nullptr)
    {
        rp3d::Vector3 posiciones(px,y,pz);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugador->setTransform(transformacion);
    }

}

void MotorFisicas::llevarBox(float x, float y, float z, float anc, float lar, float alt)
{
    rp3d::Vector3 posiciones(x,y,z);
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    //arma->setTransform(transformacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

    rp3d::Vector3 medidas(anc,alt,lar);
    BoxShape * forma = new BoxShape(medidas);
    cuerpo->addCollisionShape(forma,transformacion);

    arma = cuerpo;

}

void MotorFisicas::updateJugador(float x, float y, float z)
{
    if(jugador != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugador->setTransform(transformacion);

        /*
        rp3d::Vector3 posiciones(ix,y,iz);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        rp3d::Vector3 medidas(ancho,alto,largo);
        BoxShape * forma = new BoxShape(medidas);
        jugador->addCollisionShape(forma,transformacion);
        */
    }
}

void MotorFisicas::updateEnemigos(float x, float y, float z, unsigned int i)
{
    if(enemigos.at(i) != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        enemigos.at(i)->setTransform(transformacion);
    }
}

void MotorFisicas::updateAtaqueEnemigos(float x, float y, float z, unsigned int i)
{
    if(enemigos.at(i) != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        enemigosAtack.at(i)->setTransform(transformacion);
    }
}

void MotorFisicas::updateAtaquEspecEnemigos(float x, float y, float z, unsigned int i)
{
    if(enemigos.at(i) != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        armaAtEspEne.at(i)->setTransform(transformacion);
    }
}



vector<unsigned int> MotorFisicas::updateArmaEspecial(float x, float y, float z)
{
    vector<unsigned int> atacados;
    if(armaAtEsp != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        armaAtEsp->setTransform(transformacion);
        for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            if(space->testOverlap(armaAtEsp, enemigos.at(i)))
            {
                atacados.push_back(i);
            }
        }
    }
    return atacados;
}

vector<unsigned int> MotorFisicas::updateArma(float x, float y, float z)
{
    vector<unsigned int> atacados;
    if(jugadorAtack != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugadorAtack->setTransform(transformacion);
        for(unsigned int i = 0; i < enemigos.size(); i++)
        {
            if(space->testOverlap(jugadorAtack, enemigos.at(i)))
            {
                atacados.push_back(i);
            }
        }
    }
    return atacados;
}


void MotorFisicas::updateAtaque(float x, float y, float z, float rx, float ry, float rz)
{
    if(jugadorAtack != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugadorAtack->setTransform(transformacion);
        // std::cout << "jx: " << x << std::endl;
        // std::cout << "jy: " << y << std::endl;
        // std::cout << "jz: " << z << std::endl;

    }
}

void MotorFisicas::updateAtaqueEspecial(float x, float y, float z, float rx, float ry, float rz)
{
    if(armaAtEsp != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        armaAtEsp->setTransform(transformacion);
        // std::cout << "jx: " << x << std::endl;
        // std::cout << "jy: " << y << std::endl;
        // std::cout << "jz: " << z << std::endl;

    }
}

bool MotorFisicas::IfCollision(CollisionBody * body1, CollisionBody * body2)
{
  if(space->testOverlap(body1,body2))
  {
    return true;
  }
  return false;
}

CollisionWorld* MotorFisicas::getWorld()
{
  return space;
}

CollisionBody* MotorFisicas::getJugador()
{
  return jugador;
}

CollisionBody* MotorFisicas::getEnemies(int n)
{
 return enemigos[n];
}

CollisionBody* MotorFisicas::getColectables(int n)
{
 return recolectables[n];
}

CollisionBody* MotorFisicas::getObstacles(int n)
{
 return obstaculos[n];
}

CollisionBody* MotorFisicas::getAtack()
{
 return jugadorAtack;
}

CollisionBody* MotorFisicas::getEnemiesAtack(int n)
{
 return enemigosAtack[n];
}

CollisionBody* MotorFisicas::getEnemiesAtEsp(int n)
{
 return armaAtEspEne[n];
}
