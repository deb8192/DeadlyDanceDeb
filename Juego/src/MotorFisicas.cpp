#include "MotorFisicas.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorFisicas* MotorFisicas::unica_instancia = 0;
//fin indicador singleton

MotorFisicas::MotorFisicas()
{
    config.defaultVelocitySolverNbIterations = 20;
    config.isSleepingEnabled = false;
    space = new CollisionWorld(config);
    jugador = nullptr;
}

void MotorFisicas::crearCuerpo(float px, float py, float pz, int type, float ancho, float alto, float largo, int typeCreator)
{

    rp3d::Vector3 posiciones(px,py,pz);
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

   if(type == 1)//circulo
   {
        SphereShape * forma = new SphereShape(ancho);
        cuerpo->addCollisionShape(forma,transformacion);
    }
    else if(type == 2)//cuadrado (boundingbox)
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
        objetos.push_back(cuerpo);
    }
    else if(typeCreator == 4)//objetos
    {
        plataformas.push_back(cuerpo);
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

bool MotorFisicas::collideObstacle()
{   
    //abra que indicar tipo de objeto de alguna manera (que sean obstaculos)
    //for(long unsigned int i = 0; i < objetos.size();i++)
    for(long unsigned int i = 0; i < 7;i++)
    {
      if(space->testOverlap(jugador,objetos[i]))
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

void MotorFisicas::colisionRayoUnCuerpo(float x,float y,float z,float longitud)
{
    //Ray * rayo = crearRayo(x,y,z,longitud);

    //RaycastInfo intersecion;

    //bool colision = true;
}
void MotorFisicas::colisionChecker(bool a, bool s, bool d, bool w, float x, float y, float z)
{    
    float px = x,
          pz = z;
    if(a)
     px -= 1;
    if(s)
     pz -= 1;
    if(d)
     px += 1;
    if(w)
     pz += 1;

    if(jugador != nullptr)
    {
        rp3d::Vector3 posiciones(px,y,pz); 
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

CollisionBody* MotorFisicas::getObjects(int n)
{
 return objetos[n];
}
