#ifndef Times_HPP
#define Times_HPP

#include <ctime>//nos sirve para saber los tiempos de ejecucion
//#include <iostream>

    class Times
    {
        public:
            
            //clase singleton en public
            ~Times(void);
            static Times* GetInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(_unica_instancia == 0)
                _unica_instancia = new Times();
                return _unica_instancia;  
            }
            //fin singleton public
            void Inicializar();//inicializa los valores por defecto
            bool EjecutoDraw();//indica si se debe ejecutar el dibujado
            bool EjecutoUpdate();//indica si se debe ejecutar el update
            bool EjecutoIA();//indica si se debe ejecutar la logica del juego
            float GetMaximoTiempoFrame();//devuelve el tiempo que queda en el frame actual
            float GetTiempo(int modo);//te devuelve el tiempo actual (modo = 1 -> milisegundos, modo = 2 -> segundos)
            float CalcularTiempoPasado(float antiguo);//te devuelve el tiempo que ha pasado desde el valor antiguo (recogido con getTiempo modo 1)

            //getters & setters
            float GetUpdateTime();          //devuelve el tiempo de actualizacion de la IA por segundo
            float GetUpdateIATime();        //devuelve el tiempo de actualizacion del juego por segundo
            float GetUpdateFrame();         //devuelve el tiempo de dibujado del frame
            //float getDrawingTime();   devuelve la cantidad de frames/seg
            void SetFrames(int,int,int);//primer valor frames maximos, segundo  valor ejecucios de la ia por frame maximo numero de frames
            
        private:
            //clase singleton 
            Times();
            static Times* _unica_instancia;
            //fin clase singleton private
            float tiempo_actual;
            float tiempo_frame;
            float frame_actual;
            float update_actual;
            float numero_frames;
            float numero_update;
            float numero_updateia;
            float tiempo_ia;
            float tiempo_update;
            const float milisegundos = 1000;
            bool pasado;
            float tiempo_pasado;//tiempo pasado desde la ultima comprobacion
            unsigned tiempoInicio, tiempoInicio2, tiempoInicio3, tiempoFinal;
    };

#endif