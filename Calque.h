#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Calque
{
public:
	Calque();
	~Calque();

	Calque(int taille, float d);
	float getPersistence();
	int getTab(int i, int j);

	void CalqueAleatoire();

	void ActionSurCalqueAleatoire(Calque pmap, int octaves, int frequence);

	string toString();

	int valeur_interpolee(int i, int j, int frequenceCourante, int random, Calque map);

	int interpolate(int y1, int y2, int n, int delta);

private:
	vector< vector<int>> Tab;
	float persistence;
	int taille;
};

