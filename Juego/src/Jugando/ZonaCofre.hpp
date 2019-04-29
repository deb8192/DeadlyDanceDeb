#ifndef ZonaCofre_HPP
#define ZonaCofre_HPP
#include "Zona.hpp"

using namespace std;

class ZonaCofre : public Zona 
{

    public:
        //Constructor y destructor
        ZonaCofre(int anc, int lar, int alt, const char* tip);
        ~ZonaCofre();
        
        void annadirElemento(); //Annade un elemento, ya sea un cofre que se pone, un murcielago que entra a una zona oscura...
        void quitarElemento(); //Elimina un elemento, ya sea un cofre que se pone, un murcielago que entra a una zona oscura...
        
        void SetCofreAranna(bool esAranna);
        void SetTotalElementos(unsigned short elementos);
        bool GetCofreAranna();
        unsigned short GetTotalElementos();
        unsigned short GetElementosActuales();

    private:
        bool cofreAranna;
        unsigned short totalElementos;      //Total de elementos que puede albergar la zona
        unsigned short elementosActuales;   //Elementos (cofres, murcielagos) que contienen actualmente la zona
        
};

#endif
