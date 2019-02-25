#include "Bailaora.hpp"

Bailaora::Bailaora(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion)
: Jugador(nX,nY,nZ,ancho,largo,alto,accion)
{
    cout << "Soy Bailaora!!!!!!!!" <<endl;

    // TO DO: cambiar por las suyas
    playerTextura = "assets/texture/HeavyTex.png";
    playerModelo = "assets/models/rockero.b3d";
}

Bailaora::~Bailaora()
{

}

void Bailaora::RenderAtaqueEsp(float updateTime, float drawTime)
{
    getArmaEspecial()->moverseEntidad(1 / updateTime);
    getArmaEspecial()->RotarEntidad(1 / updateTime);
    getArmaEspecial()->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        GetDatosAtEsp()[0],
        GetDatosAtEsp()[1],
        GetDatosAtEsp()[2],
        GetDatosAtEsp()[3],
        GetDatosAtEsp()[4],
        GetDatosAtEsp()[5]);

    _motor->dibujarObjetoTemporal(
        getArmaEspecial()->getFisX()*2,
        getArmaEspecial()->getY(),
        getArmaEspecial()->getFisZ()*2,
        GetDatosAtEsp()[3],
        GetDatosAtEsp()[4],
        GetDatosAtEsp()[5],
        8,
        1,
        8,
        3);
}