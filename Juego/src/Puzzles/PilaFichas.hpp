#ifndef PilaFichas_HPP
#define PilaFichas_CPP

class PilaFichas
{
	public:
		PilaFichas();
		~PilaFichas();
		PilaFichas(short tam, short y);
		short GetTamayo();
		short GetPosY();
		void SetPosY(short y);
		
	private:
		short tamanyo;
		short posY;
};

#endif /* PilaFichas_HPP */