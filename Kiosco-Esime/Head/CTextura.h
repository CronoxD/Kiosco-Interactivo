#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class CTextura
{
	SDL_Texture *mTextura;
	int mAncho;
	int mAlto;
	int x;
	int y;
	void liberar();
	
public:
	CTextura();
	~CTextura();

	bool ingresarImagen( int xx, int yy, std::string imagen, SDL_Renderer *Rendere, int mmAncho=0, int mmAlto=0);
	void obtenerTrans(int xx, int yy, int mmAncho, int mmAlto);
	void mostrarImagen(SDL_Renderer *Rendere);
	void mostrarImagenCentro(SDL_Renderer *Rendere);
	int getmAncho();
	int getmAlto();
	int getx();
	int gety();
};
