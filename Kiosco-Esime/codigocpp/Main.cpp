#include "../Head/CBoton.h"
#include "../Head/CTextura.h"
#include "../Head/CInterfaz.h"

using namespace std;

const int PANTALLA_ANCHO = 1366;
const int PANTALLA_ALTO = 768;

bool iniciar();
bool cargarMultimedia();
void actualizar(string rut);
void finalizar();

SDL_Renderer *gRenderer = NULL;
SDL_Window *gVentana = NULL;
Mix_Music *mamboP = NULL;
CInterfaz InterfazPrincipal;
CInterfaz ProtectorPantalla;

string eventos[100];
int numEventos;	


int main(int argc, char* args[])
{	
	if(!iniciar())
	{
		cout<<"error al iniciar SDL..."; return 0;
	}
	InterfazPrincipal.asociarVentana(gRenderer);
	ProtectorPantalla.asociarVentana(gRenderer);

	
	if (!cargarMultimedia()) return 0;

	SDL_Event e;
	bool quit = false;
	int ievents = 0;
	int x=0, CincoSeg=15000;
	int unsigned startTimePrincipal = SDL_GetTicks();
	string SEventos="academica";

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	InterfazPrincipal.mostrar();

	//Actualizar pantalla
	SDL_RenderPresent(gRenderer);
	
	while (!quit) //Ciclo principal mientras quit==false
	{
		while (SDL_PollEvent(&e) != 0) //Permanece en el ciclo mientras haya señales en cola
		{	
			if (e.type == SDL_QUIT) quit = true; //Si la señal fue de salir del programa

			if (e.type == SDL_FINGERDOWN) //Si la señal fue que el usuario toco la pantalla
			{
				/*if(InterfazPrincipal.touchBoton(&e)==1)
				{
					ProtectorPantalla.actualizarTextura(0,eventos[ievents]);
					ProtectorPantalla.mostrar();
				}*/
				if(InterfazPrincipal.touchBoton(&e)==2)
				{
					
					ievents++;
					if(ievents > numEventos)	ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}
				if(InterfazPrincipal.touchBoton(&e)==3)
				{
					ievents--;
					if(ievents < 0)	ievents=numEventos;
					ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}
				if(InterfazPrincipal.touchBoton(&e)==4)
				{
					SEventos = "academica";
					actualizar(SEventos);
					ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}
				if(InterfazPrincipal.touchBoton(&e)==5)
				{
					SEventos = "cultural";
					actualizar(SEventos);
					ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}
				if(InterfazPrincipal.touchBoton(&e)==6)
				{
					SEventos = "deportivo";
					actualizar(SEventos);
					ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}
				if(InterfazPrincipal.touchBoton(&e)==7)
				{
					SEventos = "importante";
					actualizar(SEventos);
					ievents=0;
					InterfazPrincipal.actualizarTextura(1,eventos[ievents]);
				}


				//Limpiar pantalla
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				InterfazPrincipal.mostrar();
				Mix_HaltMusic();

				//Actualizar pantalla
				SDL_RenderPresent(gRenderer);
				actualizar(SEventos);
				startTimePrincipal = SDL_GetTicks(); //Se "reinicia el tiempo a "0"
				CincoSeg = 15000;
			}
		}

		

		if(SDL_GetTicks() - startTimePrincipal > 10000)
		{	

			if(SDL_GetTicks() - startTimePrincipal > CincoSeg) 
			{
				x++;
				if(x >= numEventos) x=0; 
				CincoSeg=CincoSeg+5000;
			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			actualizar(SEventos);
			ProtectorPantalla.actualizarTextura(0,eventos[x]);
			ProtectorPantalla.mostrar();
			if( Mix_PlayingMusic() == 0 )
			{
				//Play the music
				Mix_PlayMusic( mamboP, -1 );
			}
			SDL_RenderPresent(gRenderer);
		}
		actualizar(SEventos);
	
	}

	finalizar();
	return 0;
}

bool iniciar()
{

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { printf("1");  return false; }

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) { printf("2");  return false; }

	//gVentana = SDL_CreateWindow("K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PANTALLA_ANCHO-300, PANTALLA_ALTO-200, 			SDL_WINDOW_SHOWN);
	gVentana = SDL_CreateWindow("K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PANTALLA_ANCHO, PANTALLA_ALTO,
					SDL_WINDOW_FULLSCREEN);
	if (!gVentana) { printf("3");  return false; }

	gRenderer = SDL_CreateRenderer(gVentana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!gRenderer) { printf("4");  return false; }

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) { printf("6");  return false; }

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError()<< endl;
		return false;
	}

	return true;
}

void actualizar(string rut)
{
	string rutscript= "../scripts/"+rut+".sh";
	system(rutscript.c_str()); //crea una lista del numero de eventos;

	ifstream ifeventos("../Recursos/otros/eventos.txt");
	numEventos=0;

	string ruta="../Recursos/eventos/"+rut+"/";
	string aux;

	while(!ifeventos.eof()) 
	{
    	ifeventos >> aux;
    	eventos[numEventos]=ruta+aux;
      	numEventos++;
   	}
   	numEventos--;

   	ifeventos.close();	
}

bool cargarMultimedia()
{
    /*----------------------Multimedia Interfaz Principal--------------------*/
	//Texturas
	actualizar("academica");

	if (!InterfazPrincipal.cargarTextura(0, 0, "../Recursos/fondos/fondo1.jpg"))
	{
		cout<< "no se pudo cargar fondo1.jpg";  return false;
	}
	if(!InterfazPrincipal.cargarTextura(45, 35, eventos[0], 600, 700))
	{
		cout<< "no se pudo cargar evento1.jpg"; return false;
	}

	//Botones

	InterfazPrincipal.cargarBotonTransparente(45, 35, 600, 700);

	if (!InterfazPrincipal.cargarBoton(570, 334, "../Recursos/botones/boton-sigue.png",100, 100))
	{
		cout<< "no se pudo cargar boton-sigue.png"; return false;
	}
	
	if (!InterfazPrincipal.cargarBoton(20, 334, "../Recursos/botones/boton-antes.png", 100, 100 ))
	{
		cout<< "no se pudo cargar boton-antes.png"; return false;
	}

	if (!InterfazPrincipal.cargarBoton(900,100, "../Recursos/botones/academicos.png",200,70))
	{
		cout<< "no se pudo cargar boton academicos"; return false;
	}

	if (!InterfazPrincipal.cargarBoton(900,250, "../Recursos/botones/culturales.png",200,70))
	{
		cout<< "no se pudo cargar boton culturales"; return false;
	}

	if (!InterfazPrincipal.cargarBoton(900,400, "../Recursos/botones/deportivos.png",200,70))
	{
		cout<< "no se pudo cargar boton deportivos"; return false;
	}

	if (!InterfazPrincipal.cargarBoton(900,550, "../Recursos/botones/importante.png",200,70))
	{
		cout<< "no se pudo cargar boton importante"; return false;
	}
	////MAPA///
	if (!InterfazPrincipal.cargarBoton(1150,400, "../Recursos/botones/boton_cale.png",200,70))
	{
		cout<< "no se pudo cargar boton importante"; return false;
	}
	///CALENDARIO///
	if (!InterfazPrincipal.cargarBoton(1150,550, "../Recursos/botones/boton_mapa.png",200,70))
	{
		cout<< "no se pudo cargar boton importante"; return false;
	}


	/*---------------------Multimedia Interfaz Protector de pantalla---------------------*/

	ProtectorPantalla.cargarTextura(100,0, eventos[0], 1166, 768);

	/*---------------------Cargar Musica------------------------------------------*/

	mamboP = Mix_LoadMUS( "../Recursos/otros/mambo.mp3" );
	if( mamboP == NULL )
	{
		cout<< "Failed to load beat music! SDL_mixer Error: "<< Mix_GetError()<< endl;
		return false;
	}
	
	return true;
}

void finalizar()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gVentana);
	Mix_FreeMusic( mamboP );
	mamboP = NULL;
	gVentana = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
