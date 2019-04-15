#include "Inputs.hpp"

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

		//tecla E solo debe suceder una vez cuando se pulse y no en bucle mientras se mantenga pulsado
		KeyIsPressed[KEY_KEY_E] = false;
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_KEY_E)
		{
			if(!EKeyIsDown)
			{
					KeyIsPressed[KEY_KEY_E] = true;				
			}
			else
			{
				KeyIsPressed[KEY_KEY_E] = false;
			}

			EKeyIsDown = event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_E;				
		}

		/*if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    	{
			MouseClick[event.MouseInput.Event] = event.MouseInput.ButtonStates;
		}*/
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				EstadosMouse.LeftButtonDown = true;
				EstadosMouse.LeftButtonUp = false;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				EstadosMouse.LeftButtonDown = false;
				EstadosMouse.LeftButtonUp = true;
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				EstadosMouse.RightButtonDown = true;
				EstadosMouse.RightButtonUp = false;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				EstadosMouse.RightButtonDown = false;
				EstadosMouse.RightButtonUp = true;
				break;

			case EMIE_MOUSE_MOVED:
				MouseClick[event.MouseInput.Event] = event.MouseInput.ButtonStates;
				EstadosMouse.Position.X = event.MouseInput.X;
				EstadosMouse.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}
		return false;
	}

	// This is used to check whether a key is being held down
	bool Inputs::IsKeyDown(EKEY_CODE keyCode)
	{
		return KeyIsDown[keyCode];
	}

	bool Inputs::IsKeyPressed(EKEY_CODE keyCode)
	{
		return KeyIsPressed[keyCode];
	}


	Inputs::SMouseState& Inputs::GetMouseState()
	{
		return EstadosMouse;
	}

	void Inputs::ResetClicDerecho()
	{
		EstadosMouse.RightButtonDown = false;
	}

    void Inputs::ResetClicIzquierdo()
    {
    	EstadosMouse.LeftButtonDown = false;
    }

    bool Inputs::PulsadoClicIzq()
    {
    	return EstadosMouse.LeftButtonDown;
    }

    bool Inputs::PulsadoClicDer()
    {
    	return EstadosMouse.RightButtonDown;
    }

    bool Inputs::SueltoClicIzq()
    {
    	return EstadosMouse.LeftButtonUp;
    }

    bool Inputs::SueltoClicDer()
    {
    	return EstadosMouse.RightButtonUp;
    }

    void Inputs::ResetEventoRaton(int event)
    {
		MouseClick[event]=false;
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
		KeyIsPressed[keyCode]=false;
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
