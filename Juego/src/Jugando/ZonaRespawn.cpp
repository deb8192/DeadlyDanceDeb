#include "ZonaRespawn.hpp"

ZonaRespawn::ZonaRespawn(int anc, int lar, int alt, const char *tip, int boss)
    :Zona(anc, lar, alt, tip)
{
    if(boss == 1)
    {
        respawnBoss = true;
    }
    else
    {
        respawnBoss = false;
    }
}
ZonaRespawn::~ZonaRespawn()
{
    respawnBoss = false;
}