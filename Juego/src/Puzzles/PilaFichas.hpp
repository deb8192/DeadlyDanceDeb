#ifndef PilaFichas_HPP
#define PilaFichas_CPP

class PilaFichas
{
	public:
		PilaFichas();
		~PilaFichas();
		PilaFichas(short tam, short y);
		int GetIMG();
		short GetTamayo();
		short GetPosY();
		void SetPosY(short y);
		void SetIMG(int img);
		
	private:
		short tamanyo;
		short posY;
		int   imagenFicha;
};

#endif /* PilaFichas_HPP */