#include "Heavy.hpp"

Heavy::Heavy(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion)
: Jugador(nX,nY,nZ,ancho,largo,alto,accion)
{
    cout << "Soy Heavy!!!!!!!!" <<endl;

    playerTextura = "assets/texture/HeavyTex.png";
    playerModelo = "assets/models/rockero.b3d";
}

Heavy::~Heavy()
{

}

void Heavy::RenderAtaqueEsp(float updateTime, float drawTime)
{
    getArmaEspecial()->moverseEntidad(1 / updateTime);
    getArmaEspecial()->RotarEntidad(1 / updateTime);
    getArmaEspecial()->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        GetDatosAtEsp()[0],
        getY(),
        GetDatosAtEsp()[2],
        getRX(),
        getRY(),
        getRZ());

    _motor->dibujarObjetoTemporal(
        getArmaEspecial()->getFisX()*2,
        getY(),
        getArmaEspecial()->getFisZ()*2,
        getRX(),
        getRY(),
        getRZ(),
        8,
        1,
        8,
        2);
}