#include "ZonaEscondite.hpp"

ZonaEscondite::ZonaEscondite(int anc, int lar, int alt, const char *tip, bool lastHide)
    :Zona(anc, lar, alt, tip)
{
    ultimoEscondite = lastHide;
}
ZonaEscondite::~ZonaEscondite()
{
    ultimoEscondite = false;
}

void ZonaEscondite::SetUltimoEscondite(bool esUltimo)
{
    ultimoEscondite = esUltimo;
}

bool ZonaEscondite::GetUltimoEscondite()
{
    return ultimoEscondite;
}