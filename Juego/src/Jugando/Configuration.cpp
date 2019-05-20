#include "Configuration.hpp"

Configuration::Configuration()
{
    configuracion.volAmbiente = 50;
    configuracion.volEfectos = 50;
    configuracion.volVoces = 50;
    configuracion.heightScreen = 576;
    configuracion.widthScreen = 1024;
    configuracion.muteAll = false;
    configuracion.vsync = false;
    configuracion.suavizadoMsax1 = true;
    configuracion.AllScreen = false;
}

bool Configuration::CargarConfiguracion(const char * ruta)
{
    std::ifstream buffer;//solo escritura
    buffer.open(ruta,std::ios::binary);
    
    if(buffer.is_open())
    {
        buffer.read(reinterpret_cast<char *>(&configuracion),sizeof(Configuracion));
        //unsigned int valor = reinterpret_cast<unsigned int>(recogida);
        buffer.close();
        return true;
    }


    return false;
}

void Configuration::GuardarConfiguracion(const char * ruta)
{
    std::ofstream buffer;//solo escritura
    buffer.open(ruta,std::ios::binary);

    if(buffer.is_open())
    {
        buffer.write(reinterpret_cast<char *>(&configuracion),sizeof(Configuracion));
        //buffer.write(reinterpret_cast<const char *>(&save),sizeof(save));
    }
    else
    {
        std::cout << "No se ha podido crear o abrir el archivo -> " << ruta << std::endl;
    }
    

    buffer.close();
}

void Configuration::SetConfiguracion(unsigned int vambiente,unsigned int vefecto,unsigned int vvoces,unsigned int height,unsigned int ancho,bool muteall,bool vsync,bool msax1,bool allscreen)
{
    configuracion.volAmbiente = vambiente;
    configuracion.volEfectos = vefecto;
    configuracion.volVoces = vvoces;
    configuracion.heightScreen = height;
    configuracion.widthScreen = ancho;
    configuracion.muteAll = muteall;
    configuracion.vsync = vsync;
    configuracion.suavizadoMsax1 = msax1;
    configuracion.AllScreen = allscreen;
}

unsigned int Configuration::GetVolAmbiente()
{
    return configuracion.volAmbiente;
}

unsigned int Configuration::GetVolEfectos()
{
    return configuracion.volEfectos;
}

unsigned int Configuration::GetVolVoces()
{
    return configuracion.volVoces;
}

unsigned int Configuration::GetHeight()
{
    return configuracion.heightScreen;
}

unsigned int Configuration::GetWidth()
{
    return configuracion.widthScreen;
}

bool Configuration::GetMuteAll()
{
    return configuracion.muteAll;
}

bool Configuration::GetVsync()
{
    return configuracion.vsync;
}

bool Configuration::GetSuavizadoMsaX1()
{
    return configuracion.suavizadoMsax1;
}

bool Configuration::GetAllScreen()
{
    return configuracion.AllScreen;
}