#include "curl/curl.h"
#include <iostream>
#include "json/json.h"
#include <string>
#include <memory>
#include <cstring>

#ifndef puntuaciones_HPP
#define puntuaciones_HPP

class puntuaciones
{
    public:
        
        puntuaciones();//inicializa los valores
        int subirpuntuacion(bool registro = true);//true es que se va a registrar si es false es que no se va a registrar
        void setUser(const char *);//da valor a user por defecto "vacio"
        void setPass(const char *);//da valor a pass por defecto "vacio"
        void setPuntuacion(int);//da valoro a puntuacion por defecto -1
        void setTiempo(int);//da valor a tiempo por defecto -1
        void setNivel(int);//da valor a nivel por defecto -1
        int resultado();/*si es 0 es que todo a ido bien, 
        si es -1 es que ya existia el usuario y no se puede registrar, 
        -2 que el password o usuario no son correctos, -3 no esta disponible el servicio*/

    private:
        const char * user;//string usuario, longitud maxima 10
        const char * pass;//string password
        int puntuacion;//hasta 99999
        int nivel;//hasta 999
        int tiempo;//en minutos 
        int resulta;// -1 usuario ya registrado, -2 credenciales no validos, -3 no esta disponible, 0 todo correcto
};

#endif