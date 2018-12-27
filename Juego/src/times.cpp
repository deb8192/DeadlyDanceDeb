#include "times.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
times* times::unica_instancia = 0;
//fin indicador singleton

times::times()
{
    pasado=false;//para que no cuente como pasado
    frame_actual=1;//para que procese el primer frame
    tiempoFinal = 0.0;
    tiempoInicio = 0.0;
    tiempoInicio2 = 0.0;
    tiempo_pasado = 0.0;
}

times::~times(void)
{

}

void times::setFrames(int valor, int ia)
{
    numero_frames = valor;
    tiempo_frame = milisegundos/valor;
    numero_updateia = ia;
    tiempo_ia =1000/(ia+1);
    //std::cout << "Numero de frames: "<< numero_frames << std::endl;
    //std::cout << "Tiempo de cada frame: "<< tiempo_frame << std::endl;
    //std::cout << "Numero de actualizaciones ia por segundo: "<< numero_updateia << std::endl;
    //std::cout << "Tiempo hasta cada update ia: "<< tiempo_ia << std::endl;
}

bool times::EjecutoUpdate()
{
    if(tiempoInicio != 0.0)
    {
        tiempoFinal = clock();
        tiempo_pasado = (float(tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC/1000.0f));
        if(tiempo_pasado >= tiempo_frame)
        {
           //pasamos frame
           int cuantos_sumar = (tiempo_pasado/tiempo_frame);
           if((frame_actual+cuantos_sumar)  < numero_frames)
           {
               frame_actual=frame_actual+cuantos_sumar;   
               //std::cout << frame_actual << std::endl;
           }
           else //si no se pasa al siguiente frame del nuevo ciclo 
           { 
               //std::cout << clock()/CLOCKS_PER_SEC << std::endl;
               tiempoInicio2 = clock();
               frame_actual = 1;
           }
           tiempoInicio = clock();//cogemos el contador ahora de tiempo
           return true;//ya se puede ejecutar
       }
       else
       {
           return false;
       }
    }

    if(tiempoInicio == 0.0)
    {
        tiempoInicio = clock();        
        pasado = true;
        return true;
    }

    //std::cout << "no se ejecuta" << std::endl;
    return false;
}

bool times::EjecutoIA()
{
    unsigned tiempo_ahora = clock();
    float tiempo_restante = (float(tiempo_ahora-tiempoInicio2)/(CLOCKS_PER_SEC/1000.0f));
    if(tiempoInicio2 != 0.0)
    {
        if(tiempo_restante >= tiempo_ia && tiempo_restante < (tiempo_ia+tiempo_frame))
        {
            //std::cout << "Ejecuto ia" << std::endl;
            tiempoInicio2 = clock();
            return true;        
        }
        else
        {
            return false;
        }
    }

    if(tiempoInicio2 == 0.0)
    {
        tiempoInicio2 = clock();
    }

    return false;
}

float times::getMaximoTiempoFrame()
{
    unsigned tiempo_ahora = clock();
    float tiempo_restante = (float(tiempo_ahora-tiempoInicio)/(CLOCKS_PER_SEC/1000.0f));
    return (tiempo_frame-tiempo_restante);
}

float times::getTiempo(int modo)
{
    unsigned tiempo_ahora = clock();

    if(modo == 1)
    {
            return (float(tiempo_ahora/(CLOCKS_PER_SEC/1000.0f)));
    }

    if(modo == 2)
    {
            return (float(tiempo_ahora/(float(CLOCKS_PER_SEC))));
    }

}

float times::calcularTiempoPasado(float antiguo)
{

   unsigned tiempo_ahora = clock();
   float ahora = (float(tiempo_ahora/(CLOCKS_PER_SEC/1000.0f)));//antiguo - ahora
   float tiempo_restante = (float(ahora-antiguo)); 
   return tiempo_restante;
}
/*
    get tiempo el 1 lo da en milisegundos, con ese tiempo utilizar la funcion de calcular tiempo
    pasado, le paso el tiempo que he conseguido antes, para saber cuanto tiempo ha pasado
    , y ese tiempo se lo resto al tiempo de la animacion, 

*/