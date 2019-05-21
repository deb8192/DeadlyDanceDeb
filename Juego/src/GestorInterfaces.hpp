/*Esta clase se basa en calcular donde debe ir cada elemento perteneciente al hud, menus, puzzles, etc, se 
utiliza siempre porcentajes en las medidas*/
#ifndef GestorInterfaces_HPP
#define GestorInterfaces_HPP

#include <iostream>

class GestorInterfaces
{
        public:
                //clase singleton en public
                ~GestorInterfaces();

                static GestorInterfaces * GetInstance() //esto se utiliza para crear el objeto una sola vez
                {
                        if(!_unica_instancia)
                        {
                                _unica_instancia = new GestorInterfaces();
                        }
                                
                        return _unica_instancia;  
                }
                //fin singleton public
                
                void UpdateDimensionesVentana(int *);

                void UpdateDimensionesVentana(unsigned int w, unsigned h);

                void ActualizarParametros();

                float GetEscaladoX();//desde original
                float GetEscaladoY();//desde original

                struct menu
                {
                        float xLogo = 0.34;
                        unsigned int xLogoM;
                        float yLogo = 0.02;
                        unsigned int yLogoM;

                        float xLogo2 = 0.02;
                        unsigned int xLogo2M;
                        float yLogo2 = 0.88;
                        unsigned int yLogo2M;
                        
                        float xLogo3 = 0.90;
                        unsigned int xLogo3M;
                        float yLogo3 = 0.80;
                        unsigned int yLogo3M;
                        
                        float xEmpezar = 0.42;
                        unsigned int xEmpezarM;
                        float yEmpezar = 0.40;
                        unsigned int yEmpezarM;

                        float xContinuar = 0.42;
                        unsigned int xContinuarM;
                        float yContinuar = 0.50;
                        unsigned int yContinuarM;

                        float xConfi = 0.42;
                        unsigned int xConfiM;
                        float yConfi = 0.60;
                        unsigned int yConfiM;

                        float xCre = 0.42;
                        unsigned int xCreM;
                        float yCre = 0.70;
                        unsigned int yCreM;

                        float xSalir = 0.42;
                        unsigned int xSalirM;
                        float ySalir = 0.80;
                        unsigned int ySalirM;
                };

                menu * _menu;

                menu * GetMenu();

        private:
                //clase singleton 
                GestorInterfaces();
                static GestorInterfaces * _unica_instancia;
                //fin clase singleton private
                
                unsigned int Height;//alto de la ventana
                unsigned int Width;//ancho de la ventana
                float escaladoWidth;//escalado weigth segun dimension original 800
                float escaladoHeight;//escalado height segun dimension original 600

                //apartir de aqui definimos todos los valores (en porcentaje)
                
                struct hud
                {
                        float xVida = 0.10f;
                        float yVida = 0.10f;
                        float xEnergia = 0.10f;
                        float yEnergia = 0.14f;
                        float xDinero = 0.90f;
                        float yDinero = 0.10f;
                        float xObjeto = 0.90f;
                        float yObjeto = 0.90f;
                };


};

#endif
