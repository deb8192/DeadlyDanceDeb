#include "MotorFisicas.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorFisicas* MotorFisicas::unica_instancia = 0;
//fin indicador singleton

MotorFisicas::MotorFisicas()
{
    config.defaultVelocitySolverNbIterations = 20;
    config.isSleepingEnabled = false;
    space = new CollisionWorld(config);
}

void MotorFisicas::crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto)
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
            cuerpos.push_back(cuerpo);
    }
    else if(type == 2)//cuadrado (boundingbox)
    {
            rp3d::Vector3 medidas(ancho,largo,alto);
            BoxShape * forma = new BoxShape(medidas);
            cuerpo->addCollisionShape(forma,transformacion);
            cuerpos.push_back(cuerpo);
    }
    else if(type == 3)//capsula (ideal para personajes)
    {
            CapsuleShape * forma = new CapsuleShape(ancho,alto);
            cuerpo->addCollisionShape(forma,transformacion);
            cuerpos.push_back(cuerpo);
    }
}