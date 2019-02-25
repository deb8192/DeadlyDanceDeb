#ifndef Recurso_HPP
#define Recurso_HPP

class Recurso
{
    public:

        virtual void Remove()=0;//destruye el recurso de memoria
        virtual bool CargarRecurso(const char *)=0;//carga el recurso que hay en la ruta que se le facilita

    protected:

        char tipo;

};

#endif