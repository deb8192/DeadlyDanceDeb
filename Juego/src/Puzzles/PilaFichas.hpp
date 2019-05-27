#ifndef PilaFichas_HPP
#define PilaFichas_CPP

class PilaFichas
{
	public:
		PilaFichas();
		~PilaFichas();
		PilaFichas(short tam, short x, short y);
		int GetIMG();
		short GetTamayo();
		short GetPosX();
		short GetPosY();
		int   GetInc();
		void SetPosX(short x);
		void SetPosY(short y);
		void SetIMG(int img);
		
	private:
		short tamanyo;
		short posX;
		short posY;
		int   imagenFicha;
		int   incremento;
};

#endif /* PilaFichas_HPP */