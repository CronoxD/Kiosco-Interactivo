#pragma once
#include "CBoton.h"

class CInterfaz
{
	CBoton *botones[50];
	CTextura *texturas[50];
	int iBotones;
	int iTexturas;
	SDL_Renderer *render;

public:
	CInterfaz();
	~CInterfaz(); 
	bool cargarTextura(int x, int y, std::string img, int xx=0, int yy=0);
	void actualizarTextura(int ID, std::string img);
	bool cargarBoton(int x, int y, std::string img,  int xx=0, int yy=0);
	void cargarBotonTransparente(int x, int y,  int xx, int yy);
	bool asociarVentana(SDL_Renderer *Render);
	void mostrar(int j=1000, std::string cad="");
	int touchBoton(SDL_Event *e);

};