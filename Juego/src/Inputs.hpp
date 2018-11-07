#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace gui;
//using namespace idsEventos;

#ifndef Inputs_HPP
#define Inputs_CPP

    class Inputs: public IEventReceiver
    {
        public:
            virtual bool OnEvent(const SEvent& event);
            virtual bool IsKeyDown(EKEY_CODE keyCode);
            bool IsEventOn(int event);
            Inputs();
            void setDevice(IrrlichtDevice *devi);
        private:
	        bool KeyIsDown[KEY_KEY_CODES_COUNT];//almacena si esta pulsado o no de todo el array de botones normales (no entran los especiales)
	        bool *EventosActivos;
            IrrlichtDevice *device;
    };

#endif /*Inputs_HPP */