#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include "Carte.h"
#include <SDL.h>

class Visualisation
{
public:
	Visualisation();
	~Visualisation();
	int launch();

private:
	SDL_Event evenements;
	bool terminer;
	SDL_Window* fenetre;

};

