#include "../Head/CInterfaz.h"


CInterfaz::CInterfaz()
{
	int i;
	for(i=0; i<50; i++)
		texturas[i]=NULL;
	for(i=0; i<50; i++)
		botones[i]=NULL;
	iBotones=0;
	iTexturas=0;
	render=NULL;
}

CInterfaz::~CInterfaz()
{
	int i;
	for(i=0; i<50; i++)
		if(botones[i]!=NULL)
			delete botones[i];
	for(i=0; i<50; i++)
		if(texturas[i]!=NULL)
			delete texturas[i];
}
bool CInterfaz::asociarVentana(SDL_Renderer *Render)
{
	render=Render;
	if(render!=NULL)	return true;
	else				return false;
}

bool CInterfaz::cargarTextura(int x, int y, std::string img, int xx, int yy)
{
	CTextura *nuevaTextura = new CTextura;
	if(nuevaTextura -> ingresarImagen(x, y, img, render, xx, yy) == false) 
	{
		cout<<"Error al cargar textura: "<< img<< endl;
		delete nuevaTextura;
		return false;
	}
	texturas[iTexturas] = nuevaTextura;
	iTexturas++;
	return true;
}

void CInterfaz::actualizarTextura(int ID, std::string img)
{
	texturas[ID]->ingresarImagen(
		texturas[ID] -> getx(), 
		texturas[ID] -> gety(), 
		img, render,
		texturas[ID] -> getmAncho(),
		texturas[ID] -> getmAlto());	
}

bool CInterfaz::cargarBoton(int x, int y, std::string img, int xx, int yy)
{
	CBoton *nuevoBoton = new CBoton;
	if(nuevoBoton -> obtenerSprite(x, y, img, render, xx, yy) == false)
	{
		cout<< "Error al cargar boton: "<< img;
		delete nuevoBoton;
		return false;
	}
	botones[iBotones] = nuevoBoton;
	iBotones++;
	
	return true;
}

void CInterfaz::cargarBotonTransparente(int x, int y,  int xx, int yy)
{
	CBoton *nuevoBoton = new CBoton;
	nuevoBoton -> botonTrans(x, y, xx, yy);

	botones[iBotones] = nuevoBoton;
	iBotones++;
}

void CInterfaz::mostrar(int j, std::string cad)
{	
	
	if(j==1000)
	{	
		int i=0;
		//mostrar Texturas
		for(i=0; i<iTexturas; i++)
			texturas[i]->mostrarImagen(render);
		
		//mostrar Botones
		for(i=0; i<iBotones; i++)
			botones[i]->imprimirBoton(render);
	}
	else
	{
		if(cad=="textura")
			texturas[j] -> mostrarImagen(render);
		else if(cad=="boton")
			botones[j] -> imprimirBoton(render);
		else 
			cout<<"No se reconoce " << cad << "como un comando de la funcion"<< endl;
	}
}

int CInterfaz::touchBoton(SDL_Event *e)
{
	int i, touch=0;
	for(i=0; i<iBotones; i++)
		if(botones[i]->botonTouchDown(e))
			touch=i+1;
	
	return touch;
}