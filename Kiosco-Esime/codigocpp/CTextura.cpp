#include "../Head/CTextura.h"

CTextura::CTextura()
{
	mTextura = NULL;

	mAncho = 0;
	mAlto = 0;
	x=0;
	y=0;
}

CTextura::~CTextura()
{
	liberar();
}

void CTextura::liberar()
{
	if (mTextura != NULL)
	{
		SDL_DestroyTexture(mTextura);
		mTextura = NULL;
		mAncho = 0;
		mAlto = 0;
		x=0;
		y=0;
	}
}

bool CTextura::ingresarImagen(int xx, int yy, std::string imagen, SDL_Renderer *Rendere, int mmAncho, int mmAlto) 
{
	liberar();

	SDL_Surface *imagenCargada = IMG_Load(imagen.c_str());

	if (!imagenCargada) {cout<<"No se cargo correctamente la imagen"<< imagen<< "en CTextura \n"; return false;}

	SDL_SetColorKey(imagenCargada, SDL_TRUE, SDL_MapRGB(imagenCargada->format, 0, 0xFF, 0xFF));

	SDL_Texture *newTextura = NULL;
	newTextura = SDL_CreateTextureFromSurface(Rendere, imagenCargada);

	if (!newTextura) { cout<< "La nueva Textura no se creo correctamente\n"; return false; }

	//Se definen posicion y medidas de la Textura, la posicion es obligatoria
	x=xx;
	y=yy;
	mTextura = newTextura;
	if(mmAncho == 0)	mAncho = imagenCargada->w; //Si es 0 recibe su medida natural
	else				mAncho = mmAncho;			//De lo contrario toma la medida que el programador establecio

	if(mmAlto == 0)		mAlto = imagenCargada->h;
	else				mAlto = mmAlto;
	////////////////////////////////////////////////////////////////////
	SDL_FreeSurface(imagenCargada);
	return true;
}

void CTextura::obtenerTrans(int xx, int yy, int mmAncho, int mmAlto)
{
	x=xx;
	y=yy;
	mAlto=mmAlto;
	mAncho=mmAncho;
}

void CTextura::mostrarImagen(SDL_Renderer *Rendere)
{
	SDL_Rect renderQuad = { x, y, mAncho, mAlto };
	SDL_RenderCopy(Rendere, mTextura, NULL, &renderQuad);	
}

void CTextura::mostrarImagenCentro(SDL_Renderer *Rendere)
{
	int xx = 1366 / 2 - mAncho / 2;
	int yy = 768 / 2 - mAlto / 2;

	SDL_Rect renderQuad = { xx, yy, mAncho, mAlto };
	SDL_RenderCopy(Rendere, mTextura, NULL, &renderQuad);
}

int CTextura::getmAlto()
{
	return mAlto;
}

int CTextura::getmAncho()
{
	return mAncho;
}

int CTextura::getx()
{
	return x;
}

int CTextura::gety()
{
	return y;
}