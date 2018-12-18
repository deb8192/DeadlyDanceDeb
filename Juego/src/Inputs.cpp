#include "Inputs.hpp"
#include "eventos.hpp"
//se llama a su cabezera para cargar las dependencias
//#include "eventos.hpp"

	bool Inputs::OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			//IGUIEnvironment* env = device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{
				case EGET_BUTTON_CLICKED:
				//aqui entra cuando es un evento de pulsar un boton
					EventosActivos[id] = true;
				break;
				default: //esto es basicamente para quitar los warning por el enumeration
  				break;
			}
		}

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		}
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
			MouseClick[event.MouseInput.Event] = event.MouseInput.ButtonStates;
		}
		return false;
	}

	// This is used to check whether a key is being held down
	bool Inputs::IsKeyDown(EKEY_CODE keyCode)
	{
		return KeyIsDown[keyCode];
	}
	
	// This is used to check whether a mouse key is being held down
	bool Inputs::IsMouseClick(EMOUSE_INPUT_EVENT mouseEvent)
	{
		return MouseClick[mouseEvent];			
	}

	// This is used to check whether a key is being held down
	bool Inputs::IsEventOn(int event)
	{
		return EventosActivos[event];
	}

	// This is used to check whether a key is being held down
	void Inputs::ResetEvento(int event)
	{
		EventosActivos[event]=false;
	}

	// This is used to check whether a key is being held down
	void Inputs::ResetKey(int keyCode)
	{
		KeyIsDown[keyCode]=false;
	}

	Inputs::Inputs()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		{
			KeyIsDown[i] = false;
		}

		EventosActivos = new bool[idsEventos::UltimoEvento];

		for (int i=0; i<idsEventos::UltimoEvento; ++i)
		{
			EventosActivos[i] = false;
		}
	}

	void Inputs::setDevice(IrrlichtDevice *devi)
	{
		device = devi;
	}
