#ifndef ZonaRespawn_HPP
#define ZonaRespawn_HPP
#include "Zona.hpp"

using namespace std;

class ZonaRespawn : public Zona 
{

    public:
        //Constructor y destructor
        ZonaRespawn(int anc, int lar, int alt, const char* tip, int boss);
        ~ZonaRespawn();

    private:
        bool respawnBoss;
};

#endif
