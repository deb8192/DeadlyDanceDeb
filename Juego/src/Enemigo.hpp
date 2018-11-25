#ifndef Enemigo_HPP
#define Enemigo_HPP

#include "INnpc.hpp"
#include "INdrawable.hpp"

class Enemigo : public INnpc , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        
    private:

};

#endif 