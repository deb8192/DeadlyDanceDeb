#ifndef ZonaOscura_HPP
#define ZonaOscura_HPP
#include "Zona.hpp"

using namespace std;

class ZonaOscura : public Zona 
{

    public:
        //Constructor y destructor
        ZonaOscura(int anc, int lar, int alt, const char* tip);
        ~ZonaOscura();

        void annadirElemento(); //Annade un elemento, ya sea un cofre que se pone, un murcielago que entra a una zona oscura...
        void quitarElemento(); //Elimina un elemento, ya sea un cofre que se pone, un murcielago que entra a una zona oscura...        

        void SetHayMurcielagos(bool hayMurcielago);
        void SetTotalElementos(unsigned short elementos);
        bool GetHayMurcielagos();
        unsigned short GetTotalElementos();
        unsigned short GetElementosActuales();

    private:
        bool hayMurcielagos;
        unsigned short totalElementos;      //Total de elementos que puede albergar la zona
        unsigned short elementosActuales;   //Elementos (cofres, murcielagos) que contienen actualmente la zona
        
};

#endif
