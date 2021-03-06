#include "visualisation.h"



Visualisation::Visualisation()
{
}


Visualisation::~Visualisation()
{
}

int Visualisation::launch()
{

		// Notre fen�tre

		fenetre = NULL;
		SDL_Event evenements;
		bool terminer = false;


		// Initialisation de la SDL

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
			SDL_Quit();

			return -1;
		}


		// Cr�ation de la fen�tre

		fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

		if (!fenetre)
		{
			std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
			SDL_Quit();

			return -1;
		}


		// Boucle principale

		while (!terminer)
		{
			SDL_WaitEvent(&evenements);

			if (evenements.window.event == SDL_WINDOWEVENT_CLOSE)
				terminer = true;
		}


		// On quitte la SDL

		SDL_DestroyWindow(fenetre);
		SDL_Quit();

		return 0;
}