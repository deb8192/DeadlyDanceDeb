#ifndef times_HPP
#define times_HPP

#include <ctime>//nos sirve para saber los tiempos de ejecucion
//#include <iostream>

    class times
    {
        public:
            
            //clase singleton en public
            ~times(void);
            static times *getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(unica_instancia == 0)
                unica_instancia = new times();
                return unica_instancia;  
            }
            //fin singleton public
            void inicializar();//inicializa los valores por defecto
            void setFrames(int,int);//primer valor frames maximos, segundo  valor ejecucios de la ia por frame maximo numero de frames
            bool EjecutoUpdate();//indica si se debe ejecutar las interpolaciones
            bool EjecutoIA();//indica si se debe ejecutar la logica del juego
            float getMaximoTiempoFrame();//devuelve el tiempo que queda en el frame actual
            float getTiempo(int modo);//te devuelve el tiempo actual (modo = 1 -> milisegundos, modo = 2 -> segundos)
            float calcularTiempoPasado(float antiguo);//te devuelve el tiempo que ha pasado desde el valor antiguo (recogido con getTiempo modo 1)

        private:
            //clase singleton 
            times();
            static times* unica_instancia;
            //fin clase singleton private
            float tiempo_actual;
            float tiempo_frame;
            float frame_actual;
            float numero_frames;
            float numero_updateia;
            float tiempo_ia;
            const float milisegundos = 1000;
            bool pasado;
            float tiempo_pasado;//tiempo pasado desde la ultima comprobacion
            unsigned tiempoInicio, tiempoInicio2, tiempoFinal;
    };

#endif