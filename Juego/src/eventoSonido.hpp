#ifndef INeventoSonido_HPP
#define INeventoSonido_HPP

//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class eventoSonido
{
    public:
        
        ~eventoSonido();
        eventoSonido(int inten,double durac,int nx,int ny,int nz,int prop,int tip);//intensidad, duracion(en segundos) 
        int * getPropiedades();
        void restarTiempo(double tiempo);
        double getDuracion();

    private:
        double duracion;
        int intensidad;
        int x,y,z;
        int propietario;
        int tipo;
};

#endif
