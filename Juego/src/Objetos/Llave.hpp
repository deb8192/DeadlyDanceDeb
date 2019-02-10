#ifndef Llave_HPP
#define Llave_HPP

using namespace std;

//aqui definimos la clase
class Llave
{
    public:
        Llave();         //esto le deja a la entidad el constructor por defecto
        Llave(int codigo);
        ~Llave();
        
        int GetCodigoPuerta();

    private: 

        int codigoPuerta;   //Es el numero de la puerta que abre
        
};

#endif /* Recolectable_HPP */