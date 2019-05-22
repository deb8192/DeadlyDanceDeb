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

                struct hud
                {
                        float xVida = 0.04f;
                        unsigned int xVidaM;
                        float yVida = 0.02f;
                        unsigned int yVidaM;
                        
                        float xEnergia = 0.04f;
                        unsigned int xEnergiaM;
                        float yEnergia = 0.10f;
                        unsigned int yEnergiaM;

                        float xDinero = 0.85f;
                        unsigned int xDineroM;
                        float yDinero = 0.02f;
                        unsigned int yDineroM;

                        float xObjeto = 0.85f;
                        unsigned int xObjetoM;
                        float yObjeto = 0.88f;
                        unsigned int yObjetoM;

                        unsigned int xBarraVidaM;
                        unsigned int yBarraVidaM;

                        unsigned int xBarraEnergiaM;
                        unsigned int yBarraEnergiaM;

                        unsigned int xMarcaDineroM;
                        unsigned int yMarcaDineroM;

                        unsigned int xTipoObjetoM;
                        unsigned int yTipoObjetoM;

                };

                struct carga
                {
                        float xCarga = 0.75f;
                        unsigned int xCargaM;
                        float yCarga = 0.68f;
                        unsigned int yCargaM;
                };

                menu * _menu;

                hud * _hud;

                carga * _carga;

                menu * GetMenu();

                hud * GetHud();

                carga * GetCarga();

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
                



};

#endif
