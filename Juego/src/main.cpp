#include <iostream>
#include "pruebaOpengl.hpp"
#include "Times.hpp"
#include "Juego.hpp"
#include <Interfaz.hpp>
int main()
{
  cout << "\e[42m Iniciando Juego \e[0m" << endl;

  Interfaz * interfaz = new Interfaz;

  unsigned short idcamara = interfaz->AddCamara();

  unsigned short idluz = interfaz->AddLuz(0); //Crea una luz direccional
  unsigned short idluz2 = interfaz->AddLuz(1); //Crear un punto de luz
  unsigned short idluz3 = interfaz->AddLuz(1); //Crear un punto de luz
  unsigned short idluz4 = interfaz->AddLuz(1); //Crear un punto de luz
  unsigned short idluz5 = interfaz->AddLuz(1); //Crear un punto de luz
  unsigned short focoluz = interfaz->AddLuz(2); //Crear un foco de luz

  unsigned short idmalla = interfaz->AddMalla("assets/animations/BreakWallLarge_000001.obj",25);
  unsigned short pollo = interfaz->AddMalla("assets/models/Pollo.obj",1);
  unsigned short murci = interfaz->AddMalla("assets/models/Murcielago.obj",1);
  unsigned short suelo = interfaz->AddMalla("assets/models/scene_example.obj",1);

  unsigned short vida = interfaz->AddImagen("assets/images/5.png",10,10,0.4); //ruta,x,y,escalado
  unsigned short energia = interfaz->AddImagen("assets/images/2.png",10,65,0.4);
  unsigned short dinero = interfaz->AddImagen("assets/images/6.png",655,10,0.4);
  unsigned short texto1 = interfaz->AddTexto("assets/fonts/arial.ttf",24); //fuente,tamanyo

  while(interfaz->VentanaEstaAbierta())
  {
	  float radius = 5.0f;                                   //Distancia desde el centro del circulo
	  float camX = sin(glfwGetTime()/2.0f) * radius;         //Calculo de X
	  float camZ = cos(glfwGetTime()/2.0f) * radius;         //Calculo de Z

      float radiuslight = 3.0f;                              //Distancia desde el centro del circulo
      float luzX = sin(glfwGetTime()*2.0) * radiuslight;     //Calculo de X
      float luzZ = cos(glfwGetTime()*2.0) * radiuslight;     //Calculo de Z

      interfaz->Trasladar(idcamara,camX,2,camZ);
      interfaz->Trasladar(idluz2,0,1,2);
      interfaz->Trasladar(idluz3,0,1,-2);
      interfaz->Trasladar(idluz4,luzX,1,luzZ);
      interfaz->Trasladar(idluz5,-2,1,0);
      interfaz->Trasladar(focoluz,0,3,0);

      interfaz->Trasladar(idmalla,-20,-7,0);
      interfaz->Escalar(idmalla,0.15,0.15,0.15);

      interfaz->Escalar(suelo,1.5,1,1.5);
      interfaz->Trasladar(suelo,0,-2.3,0);

      interfaz->Escalar(pollo,0.45,0.45,0.45);
      interfaz->Trasladar(pollo,0,-3.6,0);

      interfaz->Escalar(murci,0.35,0.35,0.35);
      interfaz->Trasladar(murci,7,3,0);

      interfaz->Draw();
  }
  return 0;

	Juego::GetInstance();
    Juego::GetInstance()->Iniciar();
	cout << "\e[42m Cierre Juego \e[0m" << endl;
	return 0; //retornamos cero de ejecucion correcta
}
