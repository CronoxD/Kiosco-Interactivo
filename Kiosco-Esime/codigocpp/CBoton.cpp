#include "../Head/CBoton.h"
#include <iostream>

bool CBoton::obtenerSprite(int xx, int yy, std::string imagen, SDL_Renderer *Rendere, int mmAncho, int mmAlto)
{
	return ingresarImagen(xx, yy, imagen, Rendere, mmAncho, mmAlto);
}

void CBoton::imprimirBoton(SDL_Renderer *Rendere)
{
	mostrarImagen(Rendere);
}

void CBoton::botonTrans(int x, int y, int mmAncho, int mmAlto)
{
	obtenerTrans(x, y, mmAncho, mmAlto);
}

bool CBoton::botonTouchDown(SDL_Event *e)
{
	if (e->type == SDL_FINGERDOWN)
	{
		float mx, my;

		mx = e->tfinger.x;
		my = e->tfinger.y;
		
		if ( mx > getx() && mx < getx() + getmAncho() && 
		     my>gety() && my < gety() + getmAlto())
			return true;
		else return false;
	}
	else return false;
}
