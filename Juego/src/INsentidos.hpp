#ifndef INsentidos_HPP
#define INsentidos_HPP


//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class INsentidos
{

public:
     virtual ~INsentidos(){};
     
     virtual void generarSonido(int intensidad,int duracion)=0;
    
/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    //de momento nada
};

#endif /* INsentidos_HPP */