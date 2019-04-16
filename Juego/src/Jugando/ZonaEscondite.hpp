#ifndef ZonaEscondite_HPP
#define ZonaEscondite_HPP
#include "Zona.hpp"

using namespace std;

class ZonaEscondite : public Zona 
{

    public:
        //Constructor y destructor
        ZonaEscondite(int anc, int lar, int alt, const char* tip, bool lastHide);
        ~ZonaEscondite();
        bool GetUltimoEscondite();

    private:
        bool ultimoEscondite;
};

#endif
