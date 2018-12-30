#include "MotorFisicas.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
#include <iostream>

using namespace std;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

MotorFisicas* MotorFisicas::unica_instancia = 0;
//fin indicador singleton

MotorFisicas::MotorFisicas()
{
    config.defaultVelocitySolverNbIterations = 20;
    config.isSleepingEnabled = false;
    space = new CollisionWorld(config);
    jugador = nullptr;
}

void MotorFisicas::crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto,int typeCreator)
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
        rp3d::Vector3 medidas(ancho,largo,alto);
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
        objetos.push_back(cuerpo);
    }
    else if(typeCreator == 4)//ataque de jugador
    {
        jugadorAtack = cuerpo;
    }
    else if(typeCreator == 5)//objetos
    {
        armaAtEsp = cuerpo;
    }
    else if(typeCreator == 6)//ataque enemigos
    {
        enemigosAtack.push_back(cuerpo);
    }

    // std::cout << "px: " << posiciones.x << std::endl;
    // std::cout << "py: " << posiciones.y << std::endl;
    // std::cout << "pz: " << posiciones.z << std::endl;
}

Ray * MotorFisicas::crearRayo(float x, float y, float z, float longitud)
{
    rp3d::Vector3 inicio(x,y,z);
    rp3d::Vector3 final(x,y,z*longitud);
    Ray * rayo = new Ray(inicio,final);
    return rayo;
}

void MotorFisicas::colisionRayoUnCuerpo(float x,float y,float z,float longitud)
{
    //Ray * rayo = crearRayo(x,y,z,longitud);

    //RaycastInfo intersecion;

    //bool colision = true;
}

void MotorFisicas::updateJugador(float x, float y, float z, float rx, float ry, float rz)
{
    if(jugador != nullptr)
    {
        rp3d::Vector3 posiciones(x,y,z);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugador->setTransform(transformacion);
        // std::cout << "jx: " << x << std::endl;
        // std::cout << "jy: " << y << std::endl;
        // std::cout << "jz: " << z << std::endl;
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
        jugadorAtack->setTransform(transformacion);
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

CollisionBody* MotorFisicas::getAtack()
{
 return jugadorAtack;
}

CollisionBody* MotorFisicas::getEnemiesAtack()
{
 return enemigosAtack.back();
}
