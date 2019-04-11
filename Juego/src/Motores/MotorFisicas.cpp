#include "MotorFisicas.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
#include <iostream>
//#include <Matrix3x3.h>

using namespace std;

MotorFisicas* MotorFisicas::_unica_instancia = 0;
//fin indicador singleton

MotorFisicas::MotorFisicas()
{
    armaAtEsp = nullptr;
    jugadorAtack = nullptr;
    arma = nullptr;

    config.defaultVelocitySolverNbIterations = 20;
    config.isSleepingEnabled = false;
    space = new CollisionWorld(config);
    // Gravity vector
    rp3d::Vector3 gravity(0.0, -9.81, 0.0);
    // Create the dynamics world
    world = new DynamicsWorld(gravity);
    jugador = nullptr;
        jugadorBody  = nullptr;
}

MotorFisicas::~MotorFisicas()
{
    //TO DO: revisar
    //WorldSettings config;
    //std::vector<unsigned int> relacionInteractuablesObstaculos

    jugador = nullptr;
    jugadorBody  = nullptr;
    armaAtEsp = nullptr;
    jugadorAtack = nullptr;
    arma = nullptr;

    short tam = enemigos.size();
    for(short i=0; i < tam; i++)
    {
        enemigos.at(i) = nullptr;
    }
    enemigos.clear();

    tam = enemigosAtack.size();
    for(short i=0; i < tam; i++)
    {
        enemigosAtack.at(i) = nullptr;
    }
    enemigosAtack.clear();

    tam = armaAtEspEne.size();
    for(short i=0; i < tam; i++)
    {
        armaAtEspEne.at(i) = nullptr;
    }
    armaAtEspEne.clear();

    tam = recolectables.size();
    for(short i=0; i < tam; i++)
    {
        recolectables.at(i) = nullptr;
    }
    recolectables.clear();

    tam = _puertas.size();
    for(short i=0; i < tam; i++)
    {
        _puertas.at(i) = nullptr;
    }
    _puertas.clear();

    tam = _palancas.size();
    for(short i=0; i < tam; i++)
    {
        _palancas.at(i) = nullptr;
    }
    _palancas.clear();

    tam = _cofres.size();
    for(short i=0; i < tam; i++)
    {
        _cofres.at(i) = nullptr;
    }
    _cofres.clear();

    tam = recolectables_powerup.size();
    for(short i=0; i < tam; i++)
    {
        recolectables_powerup.at(i) = nullptr;
    }
    recolectables_powerup.clear();

    tam = obstaculos.size();
    for(short i=0; i < tam; i++)
    {
        obstaculos.at(i) = nullptr;
    }
    obstaculos.clear();

    tam = plataformas.size();
    for(short i=0; i < tam; i++)
    {
        plataformas.at(i) = nullptr;
    }
    plataformas.clear();

    // Liberar memoria
    delete world;
    delete space;
    delete _unica_instancia;
}

void MotorFisicas::crearCuerpo(int accion, float px, float py, float pz, int type, float ancho, float alto, float largo, int typeCreator, float despX, float despZ)
{
    rp3d::Vector3 posiciones(px+despX,py,pz+despZ); //el desplazamiento es necesario para colocar el eje de giro en las fisicas de la puertas
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody * cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

    switch(type)
    {
        case 1: //esfera
        {
            SphereShape * forma = new SphereShape(ancho);
            cuerpo->addCollisionShape(forma,transformacion);
        }
            break;
        case 2: //cubo (boundingbox)
        {
            rp3d::Vector3 medidas(ancho,alto,largo);
            BoxShape * forma = new BoxShape(medidas);
            cuerpo->addCollisionShape(forma,transformacion);
        }
            break;
        default: //type == 3, capsula (ideal para personajes)
        {
            CapsuleShape * forma = new CapsuleShape(ancho,alto);
            cuerpo->addCollisionShape(forma,transformacion);
        }
            break;
    }

    switch(typeCreator)
    {
        case 1: //jugador
        {
            rp3d::RigidBody* rigido;
            rigido = world->createRigidBody(transformacion);
            rp3d::Vector3 medicion(2,alto,2);
            BoxShape * ocupamiento = new BoxShape(medicion);
            rigido->addCollisionShape(ocupamiento,transformacion,rp3d::decimal(10));
            rigido->enableGravity(false);

            jugadorBody = rigido;
            jugadorBody->setType(BodyType::KINEMATIC);
            jugador = cuerpo;
        }
            break;
        case 2: //enemigos
        {
            enemigos.push_back(cuerpo);
        }
            break;
        case 3: //objetos
        {
            //paredes invisibles
            if(accion == 6)
            {
                obstaculos.push_back(cuerpo);
                //Para la camara
                rp3d::Vector3 posiciones(px+despX,py,pz+despZ+2.5f); //el desplazamiento es necesario para colocar el eje de giro en las fisicas de la puertas
                rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
                Transform transformacion(posiciones,orientacion);
                rp3d::CollisionBody * cuerpo;
                cuerpo = space->createCollisionBody(transformacion);
                rp3d::Vector3 medicion(ancho,alto,largo+3.5f);
                BoxShape * formapared = new BoxShape(medicion);
                cuerpo->addCollisionShape(formapared,transformacion);
                paredeInvisiblesCamara.push_back(cuerpo);
            }
            //paredes rompibles que se interponen ante el jugador
            else if(accion == 5)
            {
                relacionParedesObstaculos.push_back(obstaculos.size());
                paredes.push_back(cuerpo);
                obstaculos.push_back(cuerpo);
            }
            //Recolectable power ups
            else if(accion == 4)
            {
                recolectables_powerup.push_back(cuerpo);
            }
            //Objetos que recoger como armas y llaves
            else if(accion == 2)
            {
                recolectables.push_back(cuerpo);
            }
            //Obstaculos que se interponen ante el jugador
            else if(accion == 1)
            {
                obstaculos.push_back(cuerpo);
            }
        }
            break;
        case 4: //ataque de jugador
        {
            jugadorAtack = cuerpo;
        }
            break;
        case 5:
        {
            armaAtEsp = cuerpo;
        }
            break;
        case 6:
        {
            plataformas.push_back(cuerpo);
        }
            break;
        case 7: //ataque enemigos
        {
            enemigosAtack.push_back(cuerpo);
        }
            break;
        case 8:
        {
            armaAtEspEne.push_back(cuerpo);
        }
            break;
        case 9:
        {
            arma = cuerpo;
        }
            break;

        default:
        {
            // Nada por ahora
        }
            break;
    }
    // std::cout << "px: " << posiciones.x << std::endl;
    // std::cout << "py: " << posiciones.y << std::endl;
    // std::cout << "pz: " << posiciones.z << std::endl;
}

unsigned short MotorFisicas::CrearCuerpoInter(unsigned short tipoObj, float px, float py, float pz, 
    float ancho, float alto, float largo, float despX, float despZ)
{
    rp3d::Vector3 posiciones(px+despX,py,pz+despZ); //el desplazamiento es necesario para colocar el eje de giro en las fisicas de la puertas
    rp3d::Quaternion orientacion = rp3d::Quaternion::identity();

    Transform transformacion(posiciones,orientacion);

    rp3d::CollisionBody* cuerpo;
    cuerpo = space->createCollisionBody(transformacion);

    rp3d::Vector3 medidas(ancho,alto,largo);
    BoxShape* forma = new BoxShape(medidas);
    cuerpo->addCollisionShape(forma,transformacion);

    relacionInteractuablesObstaculos.push_back(obstaculos.size());
    obstaculos.push_back(cuerpo);

    //Se le anade una zona de deteccion mediante colision
    rp3d::CollisionBody* deteccion;
    SphereShape* detector = new SphereShape(alto);
    deteccion = space->createCollisionBody(transformacion);
    deteccion->addCollisionShape(detector,transformacion);

    switch(tipoObj)
    {
        case 0: // PALANCA
            _palancas.push_back(move(deteccion));
        break;

        case 4: // COFRE
            _cofres.push_back(move(deteccion));
        break;

        default: // PUERTA2 y PUERTA
            _puertas.push_back(move(deteccion));
            break;
    }
    return obstaculos.size()-1;
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

void MotorFisicas::EraseObstaculo(int idx)
{
    obstaculos.at(idx) = nullptr;
}

void MotorFisicas::EraseColectable(int idx)
{
    recolectables.erase(recolectables.begin() + idx);
}

void MotorFisicas::ErasePared(int idx)
{
    paredes.at(idx) = nullptr;
}

void MotorFisicas::EraseColectablePowerup(int idx)
{
    recolectables_powerup.erase(recolectables_powerup.begin() + idx);
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

void MotorFisicas::DesactivarCofre(unsigned short pos)
{
    _cofres.at(pos) = nullptr;
}

void MotorFisicas::EraseJugador(){
    jugador = NULL;
     jugadorBody  = NULL;
}

void MotorFisicas::EraseArma()
{
    arma = NULL;
}

Ray * MotorFisicas::crearRayo(float x, float y, float z, float rotation, float longitud)
{
    rp3d::Vector3 inicio(x,y,z);//posicion inicial desde donde sale el rayo(desde el centro de la entidad o objeto)

    //calculamos segun la magnitud y la direccion donde debe apuntar el rayo

    float nx,ny,nz;
    float rad = constantes.PI/constantes.PI_RADIAN*(rotation);

    ny = y;
    nx = (cos(rad)*longitud)+x;//calculamos cuanto hay que sumarle a la posicion x
    nz = (sin(rad)*longitud)+z;//calculamos cuanto hay que sumarle a la posicion z
    rp3d::Vector3 final(nx,ny,nz);

    Ray * rayo = new Ray(inicio,final);

    return rayo;
}

int MotorFisicas::collideColectable()
{
    for(long unsigned int i = 0; i < recolectables.size();i++)
    {
        if(space->testOverlap(jugador,recolectables[i]))
        {
            return i;
        }
    }

    return -1;
}

int MotorFisicas::collideColectablePowerup()
{
  for(long unsigned int i = 0; i < recolectables_powerup.size();i++)
  {
      if(space->testOverlap(jugador,recolectables_powerup[i]))
      {
          return i; //posicion mas recolectables
      }
  }
  return -1;
}

short MotorFisicas::collidePuerta()
{
    for (long unsigned int i = 0; i < _puertas.size(); i++)
    {
        if (space->testOverlap(jugador,_puertas[i]))
        {
            return (int)i;
        }
    }
    return -1;
}

short MotorFisicas::collidePalanca()
{
    for (long unsigned int i = 0; i < _palancas.size(); i++)
    {
        if (space->testOverlap(jugador,_palancas[i]))
        {
            return (int)i;
        }
    }
    return -1;
}

short MotorFisicas::collideCofre()
{
    for (long unsigned int i = 0; i < _cofres.size(); i++)
    {
        if (_cofres[i] != nullptr)
            if (space->testOverlap(jugador,_cofres[i]))
            {
                return (int)i;
            }
    }
    return -1;
}

bool MotorFisicas::collideObstaculos()
{
    //abra que indicar tipo de objeto de alguna manera (que sean obstaculos)
    for(long unsigned int i = 0; i < obstaculos.size();i++)
    {
        if(obstaculos[i])
        {
            if(space->testOverlap(jugador,obstaculos[i]))
            {
                return true;
            }
        }
    }
    return false;
}

bool MotorFisicas::collideObstacle()
{
    if (collideObstaculos())
        return true;

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

bool MotorFisicas::collideAtackObstacle()
{

    for(long unsigned int i = 0; i < obstaculos.size();i++)
    {
        if(obstaculos[i])
        {
            if(space->testOverlap(jugadorAtack,obstaculos[i]))
            {
                return true;
            }
        }
    }

    return false;
}

std::vector<short> MotorFisicas::collideAttackWall()
{
    std::vector<short> indicesParedes;
    indicesParedes.reserve(10);
    for(unsigned short i = 0; i < paredes.size();i++)
    {
        if(paredes[i] && jugadorAtack)
        {
            if(space->testOverlap(jugadorAtack,paredes[i]))
            {
                indicesParedes.push_back(i);
            }
        }
    }

    return indicesParedes;
}

bool MotorFisicas::enemyCollideObstacle(unsigned int enemigo)
{
    //abra que indicar tipo de objeto de alguna manera (que sean obstaculos)
    for(long unsigned int i = 0; i < obstaculos.size();i++)
    {
        if(obstaculos[i])
        {
            if(space->testOverlap(enemigos[enemigo],obstaculos[i]))
            {
                return true;
            }
        }
    }

    //tampoco debe intersectar en el espacio con los enemigos
    for(long unsigned int i = 0; i < enemigos.size();i++)
    {
        if(enemigo != i && enemigos[i])
        {
            if(space->testOverlap(enemigos[enemigo],enemigos[i]))
            {
                return true;
            }
        }
    }

    return false;
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

bool MotorFisicas::enemyCollidePlatform(unsigned int enemigo)
{
    for(long unsigned int i = 0; i < plataformas.size();i++)
    {
      if(space->testOverlap(enemigos[enemigo],plataformas[i]))
      {
        return true;
      }
    }

    return false;

}

// TO DO revisar
int * MotorFisicas::colisionRayoUnCuerpo(float x,float y,float z,float rotation,float longitud,int modo)
{
    //se recomiendan usar modos especificos para ahorrar costes.

    Ray * rayo = crearRayo(x/*-(2*(sin(constantes.PI * rotation / constantes.PI_RADIAN)))*/,y,z/*-(2*(cos(constantes.PI * rotation / constantes.PI_RADIAN)))*/,(-1*(rotation-180)),longitud);
    RaycastInfo intersection;

    int * jug;
    int * ene;
    int * obj;

    //creamos un puntero para saber si colisiona con el jugador (si es el jugador devolvera que no colisiona con el)
    if(modo == 1)
    {
        jug = new int[7];
        jug[0] = 0;//false - no lo ve
    }

    //creamos un puntero que devuelve solamente los objetos con los que colisiona
    // Ya no utilizar - MI
    if(modo == 2)
    {
        obj = new int[7];
        obj[0] = 0;//false - no lo ve
    }

    //creamos un puntero que devuelve solo los enemigos con los que colisiona por defecto si este rayo sale de un enemigo no lo detecta como colision
    if(modo == 3)
    {
        ene = new int[7];
        ene[0] = 0;//false - no lo ve
    }
    //Colisiona la vision con el jugador
    if(modo == 0 || modo == 1)
    {
        bool colision = jugador->raycast(*rayo,intersection);

        if(colision)
        {
            if(jugador == intersection.body)
            {
                //cout << "colisiona" << endl;
                jug[0] = 1;
                jug[1] = intersection.worldPoint.x;
                jug[2] = intersection.worldPoint.y;
                jug[3] = intersection.worldPoint.z;
                jug[4] = intersection.worldNormal.x;
                jug[5] = intersection.worldNormal.y;
                jug[6] = intersection.worldNormal.z;
            }
        }
    }
    //Colisiona la vision con los enemigos
    if(modo == 0 || modo == 3)
    {
        bool colision = false;
        if(enemigos.size() > 0)//posiciones interpolacion
        {
            unsigned int i = 0;
            while(i<enemigos.size() && !colision)
            {
                colision = enemigos[i]->raycast(*rayo,intersection);

                if(colision)
                {

                    ene[0] = 1;
                    ene[1] = intersection.worldPoint.x;
                    ene[2] = intersection.worldPoint.y;
                    ene[3] = intersection.worldPoint.z;
                    ene[4] = intersection.worldNormal.x;
                    ene[5] = intersection.worldNormal.y;
                    ene[6] = intersection.worldNormal.z;
                }
                else i++;
            }
        }
    }

    // Colisiona la vision con los obstaculos
    if(modo == 0 || modo == 2)
    {
        bool colision = false;
        if(obstaculos.size() > 0)//posiciones interpolacion
        {
            unsigned int i = 0;
            while(i<obstaculos.size() && !colision)
            {
                if(obstaculos[i])
                    colision = obstaculos[i]->raycast(*rayo,intersection);

                if(colision)
                {
                    //cout << "colisiona" << endl;
                    obj[0] = 1;
                    obj[1] = intersection.worldPoint.x;
                    obj[2] = intersection.worldPoint.y;
                    obj[3] = intersection.worldPoint.z;
                    obj[4] = intersection.worldNormal.x;
                    obj[5] = intersection.worldNormal.y;
                    obj[6] = intersection.worldNormal.z;
                }
                else i++;
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

    return jug;

}

void MotorFisicas::girarCamara()
{
    gcam >= 270 ? gcam = 0 : gcam += 90;
}

void MotorFisicas::colisionChecker(bool a, bool s, bool d, bool w, float x, float y, float z)
{
    float px = x,
          pz = z;

    if(w)
     az = 50;
    if(s)
     az = -50;
    if(a)
     ax = -50;
    if(d)
     ax = 50;

    //Para giro: obtienes el maximo comun divisor y lo divides entre x, z
    //asi tambien evitas que ambas variables aumenten excesivamente de valor
    float div = (float)__gcd((int)abs(ax),(int)abs(az));

    if(div != 1.0 && div != 0.0)
    {
        ax /= div;
        az /= div;
    }

    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
    az < 0 ?
     deg = constantes.PI_RADIAN + (constantes.RAD_TO_DEG * atan(ax/az)) :
     deg =  constantes.RAD_TO_DEG * atan(ax/az) ;
    //has obtenido la arcotangente que te da el angulo de giro en grados

      deg -= gcam;
      px += (int)(2.9*sin(deg*constantes.DEG_TO_RAD));
      pz += (int)(2.9*cos(deg*constantes.DEG_TO_RAD));


    if(jugador != nullptr)
    {
        rp3d::Vector3 posiciones(px,y,pz);
        rp3d::Quaternion orientacion = rp3d::Quaternion::identity();
        Transform transformacion(posiciones,orientacion);
        jugador->setTransform(transformacion);
        jugadorBody->setTransform(transformacion);
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
        //jugadorBody->getTransform(transformacion);

        //cout << jugadorBody->getTransform().getPosition().x << endl;
        //cout << jugadorBody->getTransform().getPosition().y << endl;
        //cout << jugadorBody->getTransform().getPosition().z << endl;

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

void MotorFisicas::updatePuerta(float x, float y, float z, 
    float rx, float ry, float rz, float despX, float despZ,
    unsigned int pos)
{
    if(obstaculos.at(pos) != nullptr)
    {
        float rotacion = (ry * constantes.DEG_TO_RAD) / 2;
        rp3d::Vector3 posiciones((x+despX)/2,y,(z+despZ)/2);
        rp3d::Quaternion orientacion = rp3d::Quaternion(
            cos(rotacion),
            posiciones*(sin(rotacion)));

        Transform transformacion(posiciones,orientacion);
        obstaculos.at(pos)->setTransform(transformacion);
    }
}

void MotorFisicas::updateAtaqueEnemigos(float x, float y, float z, unsigned int i)
{
    if(i < enemigos.size() && enemigos.at(i) != nullptr)
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
    atacados.reserve(enemigos.size());
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

CollisionBody* MotorFisicas::getColectablesPowerup(int n)
{
 return recolectables_powerup[n];
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

void MotorFisicas::limpiarFisicas()
{
    if(enemigos.size() > 0)
    {
        for(std::size_t i=0 ; i < enemigos.size() ; i++)
        {
            if(enemigos[i])
            {
                space->destroyCollisionBody(enemigos[i]);
            }
            enemigos[i] = nullptr;
            enemigos.erase(enemigos.begin() + i);
        }
        enemigos.resize(0);
    }

    if(enemigosAtack.size() > 0)
    {
        for(std::size_t i=0 ; i < enemigosAtack.size() ; i++)
        {
            if(enemigosAtack[i])
            {
                space->destroyCollisionBody(enemigosAtack[i]);
            }
            enemigosAtack[i] = nullptr;
            enemigosAtack.erase(enemigosAtack.begin() + i);
        }
        enemigosAtack.resize(0);
    }

    if(armaAtEspEne.size() > 0)
    {
        for(std::size_t i=0 ; i < armaAtEspEne.size() ; i++)
        {
            if(armaAtEspEne[i])
            {
                space->destroyCollisionBody(armaAtEspEne[i]);
            }
            armaAtEspEne[i] = nullptr;
            armaAtEspEne.erase(armaAtEspEne.begin() + i);
        }
        armaAtEspEne.resize(0);
    }

    if(jugador)
    {
        if(jugador)
        {
            space->destroyCollisionBody(jugador);
        }
        jugador = NULL;

        jugadorBody = NULL;
    }

    if(recolectables.size() > 0)
    {
        for(std::size_t i=0 ; i < recolectables.size() ; i++)
        {
            if(recolectables[i])
            {
                space->destroyCollisionBody(recolectables[i]);
            }
            recolectables[i] = nullptr;
            recolectables.erase(recolectables.begin() + i);
        }
        recolectables.resize(0);
    }

    if(recolectables_powerup.size() > 0)
    {
        for(std::size_t i=0 ; i < recolectables_powerup.size() ; i++)
        {
            if(recolectables_powerup[i])
            {
                space->destroyCollisionBody(recolectables_powerup[i]);
            }
            recolectables_powerup[i] = nullptr;
            recolectables_powerup.erase(recolectables_powerup.begin() + i);
        }
        recolectables_powerup.resize(0);
    }

    if(obstaculos.size() > 0)
    {
        for(std::size_t i=0 ; i < obstaculos.size() ; i++)
        {
            if(obstaculos[i])
            {
                space->destroyCollisionBody(obstaculos[i]);
            }
            obstaculos[i] = nullptr;
            obstaculos.erase(obstaculos.begin() + i);
        }
        obstaculos.resize(0);
    }

    if(plataformas.size() > 0)
    {
        for(std::size_t i=0 ; i < plataformas.size() ; i++)
        {
            if(plataformas[i])
            {
                space->destroyCollisionBody(plataformas[i]);
            }
            plataformas[i] = nullptr;
            plataformas.erase(plataformas.begin() + i);
        }

        plataformas.resize(0);
    }

    if(_puertas.size() > 0)
    {
        for(std::size_t i=0 ; i < _puertas.size() ; i++)
        {
            if(_puertas[i])
            {
                space->destroyCollisionBody(_puertas[i]);
            }
            _puertas[i] = nullptr;
            _puertas.erase(_puertas.begin() + i);
        }
        _puertas.resize(0);
    }

    if(_palancas.size() > 0)
    {
        for(std::size_t i=0 ; i < _palancas.size() ; i++)
        {
            if(_palancas[i])
            {
                space->destroyCollisionBody(_palancas[i]);
            }
            _palancas[i] = nullptr;
            _palancas.erase(_palancas.begin() + i);
        }
        _palancas.resize(0);
    }

    if(_cofres.size() > 0)
    {
        for(std::size_t i=0 ; i < _cofres.size() ; i++)
        {
            if(_cofres[i])
            {
                space->destroyCollisionBody(_cofres[i]);
            }
            _cofres[i] = nullptr;
            _cofres.erase(_cofres.begin() + i);
        }
        _cofres.resize(0);
    }
}

unsigned int MotorFisicas::GetRelacionInteractuablesObstaculos(int n)
{
    unsigned int m = n;
    return relacionInteractuablesObstaculos.at(m);
}

unsigned int MotorFisicas::GetRelacionParedesObstaculos(int n)
{
    unsigned int m = n;
    return relacionParedesObstaculos.at(m);
}

bool MotorFisicas::CamaraRotara()
{
    for(long unsigned int i = 0; i < paredeInvisiblesCamara.size();i++)
    {
        if(space->testOverlap(jugador,paredeInvisiblesCamara[i]))
        {
            return true;
        }
    }
    return false;
}
