#pragma once
#include "CTextura.h"

class CBoton :protected CTextura
{

public:
	bool obtenerSprite(int xx, int yy, std::string imagen, SDL_Renderer *Rendere, int mmAncho=0, int mmAlto=0);
	void imprimirBoton(SDL_Renderer *Rendere);
	void botonTrans(int x, int y, int mmAncho, int mmAlto);
	bool botonTouchDown(SDL_Event *e);
};
