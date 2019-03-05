#ifndef INEventoSonido_HPP
#define INEventoSonido_HPP

//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class EventoSonido
{
    public:
        EventoSonido(int inten,double durac,int nx,int ny,int nz,int prop,int tip);//intensidad, duracion(en segundos) 
        ~EventoSonido();
        
        int* getPropiedades();
        void restarTiempo(double tiempo);
        double getDuracion();
        float getIntensidad();
        int getTipo();

    private:
        double duracion;
        double duracionOriginal;
        float multiplicador;//este valor se encarga de medir como de grande es la onda en cada momento
        int intensidad;
        int x,y,z;
        int propietario;
        int tipo;

};

#endif