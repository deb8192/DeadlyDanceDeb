#ifndef FORMAPRIMITIVA_HPP
#define FORMAPRIMITIVA_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FormaPrimitiva
{
    public:

        FormaPrimitiva(float *);//crea una forma primitiva
        void Remove();//remueve la forma primitiva
        void Draw();//Pinta el objeto primitivo

    private:
    
        unsigned int VBO,VAO;
        ~FormaPrimitiva();

};

#endif