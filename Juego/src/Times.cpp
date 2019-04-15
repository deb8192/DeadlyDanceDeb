#include "Times.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Times* Times::_unica_instancia = 0;
//fin indicador singleton

//inicialiciamos 
Times::Times()
{
    Inicializar();
}

//destructor de la clase
Times::~Times()
{
    delete _unica_instancia;
}

//modificas los valores de frames y de numero de calculas de ia por cada ciclo
void Times::SetFrames(int valor, int update, int ia)
{
    Inicializar();
    numero_frames = valor;
    tiempo_frame = milisegundos/valor;
    numero_updateia = ia;
    tiempo_ia =1000/(ia+1);
    numero_update = update;
    tiempo_update = milisegundos/update;
    //std::cout << "Numero de frames: "<< numero_frames << std::endl;
    //std::cout << "Tiempo de cada frame: "<< tiempo_frame << std::endl;
    //std::cout << "Numero de actualizaciones ia por segundo: "<< numero_updateia << std::endl;
    //std::cout << "Tiempo hasta cada update ia: "<< tiempo_ia << std::endl;
}
//dice cuando se debe ejecutar el siguiente frame
bool Times::EjecutoDraw()
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
//dice cuando se debe ejecutar update
bool Times::EjecutoUpdate()
{
    unsigned tiempo_ahora = clock();
    float tiempo_restante = (float(tiempo_ahora-tiempoInicio2)/(CLOCKS_PER_SEC/1000.0f));
    if(tiempoInicio2 != 0.0)
    {
        /*if(tiempo_restante >= tiempo_update && tiempo_restante < (tiempo_update+tiempo_frame))
        {
            //std::cout << "Ejecuto ia" << std::endl;
            tiempoInicio2 = clock();
            return true;        
        }*/
        if(tiempo_restante >= tiempo_update)
        {
           //pasamos frame
           int cuantos_sumar = (tiempo_restante/tiempo_update);
           if((update_actual+cuantos_sumar)  < numero_update)
           {
               update_actual=update_actual+cuantos_sumar;   
               //std::cout << frame_actual << std::endl;
           }
           else //si no se pasa al siguiente frame del nuevo ciclo 
           { 
               //std::cout << clock()/CLOCKS_PER_SEC << std::endl;
               tiempoInicio3 = clock();
               update_actual = 1;
           }
           tiempoInicio2 = clock();//cogemos el contador ahora de tiempo
           return true;//ya se puede ejecutar
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
//dice cuando se debe ejecutar la ia
bool Times::EjecutoIA()
{
    unsigned tiempo_ahora = clock();
    float tiempo_restante = (float(tiempo_ahora-tiempoInicio3)/(CLOCKS_PER_SEC/1000.0f));
    if(tiempoInicio3 != 0.0)
    {
        if(tiempo_restante >= tiempo_ia && tiempo_restante < (tiempo_ia+tiempo_update))
        {
            //std::cout << "Ejecuto ia" << std::endl;
            tiempoInicio3 = clock();
            return true;        
        }
        else
        {
            return false;
        }
    }

    if(tiempoInicio3 == 0.0)
    {
        tiempoInicio3 = clock();
    }

    return false;
}
//tiempo que queda en este frame
float Times::GetMaximoTiempoFrame()
{
    unsigned tiempo_ahora = clock();
    float tiempo_restante = (float(tiempo_ahora-tiempoInicio)/(CLOCKS_PER_SEC/1000.0f));
    return (tiempo_frame-tiempo_restante);
}
//sirve para recuperar el tiempo de ejecucion, si le pasas 1 te lo devolvera en milisegundos si le pasas 2 te lo devuelve en segundos
float Times::GetTiempo(int modo)
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

    return (float(tiempo_ahora/(CLOCKS_PER_SEC/1000.0f))); // se devuelve por defecto en ms el tiempo actual

}
//nos servira para devolver el tiempo pasado desde una marca de tiempo con GetTiempo(modo 1)
float Times::CalcularTiempoPasado(float antiguo)
{

   unsigned tiempo_ahora = clock();
   float ahora = (float(tiempo_ahora/(CLOCKS_PER_SEC/1000.0f)));//antiguo - ahora
   float tiempo_restante = (float(ahora-antiguo)); 
   return tiempo_restante;
}

//inicializa los valores como si fuera la primera vez
void Times::Inicializar()
{
    pasado=false;//para que no cuente como pasado
    frame_actual=1;//para que procese el primer frame
    tiempoFinal = 0.0;
    tiempoInicio = 0.0;
    tiempoInicio2 = 0.0;
    tiempo_pasado = 0.0;
}

float Times::GetUpdateIATime()
{
    return numero_updateia;   //Aquí se deberia devolver el tiempo de actualizacion, no el de dibujado
}

float Times::GetUpdateTime()
{
    return numero_update;   //Aquí se deberia devolver el tiempo de actualizacion, no el de dibujado
}

float Times::GetUpdateFrame()
{
    return numero_frames;   //Aquí se deberia devolver el tiempo de dibujado
}

/*float Times::GetDrawingTime()
{

}*/