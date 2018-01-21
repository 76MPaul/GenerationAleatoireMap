#pragma once
#include "Cases.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Carte
{
public:
	/* functions */
	Carte();
	Carte(int ptaille);
	~Carte();

	Cases getCaseValue(int x, int y);
	void setCaseValue(int x, int y, Cases pcase);
	void max();

	int getMaxHeight();
	int getMaxHeat();
	int getMaxMoisture();

private:
	/* var */
	vector<vector<Cases>> carte;

	int taille;

	int maxHeight;
	int maxMoisture;
	int maxHeat;

	int minHeight;
	int minMoisture;
	int minHeat;

};

