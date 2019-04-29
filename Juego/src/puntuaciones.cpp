#include "puntuaciones.hpp"


///ejemplo de uso 
/*	puntuaciones puntuar;
	puntuar.setUser((char*)"jose4");
	puntuar.setPass((char*)"44445");
	puntuar.setPuntuacion(9000);
	puntuar.setTiempo(30);
	puntuar.setNivel(0);
	int retu =  puntuar.subirpuntuacion(false);
	switch(retu)
	{
		case 0:
			std::cout << "Todo correcto "<< std::endl;
			break;
		case -1:
			std::cout << "usuario no valido"<< std::endl;
			break;
		case -2:
			std::cout << "Credenciales no validos"<< std::endl;
			break;
		case -3:
			std::cout << "Servicio no disponible" << std::endl;
			break;
		case -4:
			std::cout << "No hay internet o la pagina no responde" << std::endl;
			break;
}*/

namespace
{
    std::size_t callback(const char* in,std::size_t size,std::size_t num,std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

puntuaciones::puntuaciones()
{
    //inicializamos variables
    user = "vacio";
    pass = "vacio";
    puntuacion = -1;
    tiempo = -1;
    nivel = -1;
    resulta = -4;
}

int puntuaciones::subirpuntuacion(bool registro)
{
    resulta = -4;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    //con los datos ya asignados vamos a subir la puntuacion
    //auto $url = "http://www.crzycats.com/puntuaciones/v1/deadlydance.php?";
    //auto $parametros = "tipo=1&us=&pa=&pu=&ti=&ni=&re=0";
    if(curl) 
    {
        
        int tip,reg;

        if(registro)
        {
            tip = 1;//operacion tipo 1
            reg = 1;// registro true
        }
        else
        {
            tip = 2;//operacion tipo 2
            reg = 0;//registr false
        }

        std::string us = user;
        std::string pa = pass; 
        std::string tipo = std::to_string(tip); 
        std::string pu = std::to_string(puntuacion); 
        std::string ti = std::to_string(tiempo); 
        std::string ni = std::to_string(nivel);
        std::string re = std::to_string(reg);

        //auto $parametros = "tipo=1&us=&pa=&pu=&ti=&ni=&re=0";
        
        std::string ruta_completa = "tipo="+tipo+"&us="+us+"&pa="+pa+"&pu="+pu+"&ti="+ti+"&ni="+ni+"&re="+re;
        const char * c = ruta_completa.c_str();

        //esto transforma el string std 11 a char
        //char cadena[sizeof(ruta_completa)];//le dice la longitud del char que sera igual a la longitud del string
        //strcpy(cadena,ruta_completa.c_str()); //pasa el string a char
        //fin de la transformacion
        
        curl_easy_setopt(curl, CURLOPT_URL,"http://www.crzycats.com/puntuaciones/puntuaciones/v1/deadlydance.php");
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, c);//datos enviados por post
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);//cuando se devuelve datos se llama a esta funcion
        
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);//permite las redirecciones

        std::unique_ptr<std::string> httpData(new std::string());//creamos el tipo de dato para contener el string
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());//le decimos que escriba en httpdata

        
        //
        // Execute command ( curl )
        //
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        //
        // Check Errors
        //
        if(res != CURLE_OK)
        {
            resulta = -4;//nos disponible
        }
        else
        {
            Json::CharReaderBuilder builder;
            Json::CharReader * reader = builder.newCharReader();
            Json::Value obj;
            
            builder["collectComments"] = false;
            
            JSONCPP_STRING errs;

            bool ok = reader->parse(httpData->c_str(), httpData->c_str() + httpData->size(), &obj, &errs);
            
            if(ok)
            {
                int devolucion = obj["estado"].asInt();//obtenemos el string
                resulta = devolucion;//guardamos la devolucion
                return resulta;//devolvemmos el codigo resultante de la subida de la puntuacion               
            }

        }
        
    }

    return resulta;
}

void puntuaciones::setUser(const char * us)//da valor a user por defecto "vacio"
{

    user = us;

}

void puntuaciones::setPass(const char * pa)//da valor a pass por defecto "vacio"
{

    pass = pa;

}

void puntuaciones::setPuntuacion(int pu)//da valoro a puntuacion por defecto -1
{

    puntuacion = pu;

}

void puntuaciones::setTiempo(int ti)//da valor a tiempo por defecto -1
{

    tiempo = ti;

}

void puntuaciones::setNivel(int ni)//da valor a nivel por defecto -1
{

    nivel = ni;

}

int puntuaciones::resultado()//*si es 0 es que todo a ido bien, 
{

    return resulta;

}