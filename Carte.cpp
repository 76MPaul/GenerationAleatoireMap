#include "Carte.h"



Carte::Carte()
{

}

Carte::Carte(int ptaille)
{	
	taille = ptaille;
	Cases caseBase = Cases();
	carte.resize(ptaille, vector<Cases>(ptaille, caseBase));
}


Carte::~Carte()
{

}

Cases Carte::getCaseValue(int x, int y)
{
	return Carte::carte[x][y];
}

void Carte::setCaseValue(int x, int y, Cases pcase)
{
	carte[x][y] = pcase;
}

void Carte::max() {
	maxMoisture = 0;
	maxHeat = 0;
	maxHeight = 0;
	for (int x = 0; x<taille; x++) {
		for (int y = 0; y<taille; y++) {
			if (carte[x][y].getMoisture()>maxMoisture) {
				maxMoisture = carte[x][y].getMoisture();
			}
			else if (carte[x][y].getMoisture()<minMoisture) {
				minMoisture = carte[x][y].getMoisture();
			}

			if (carte[x][y].getHigh()>maxHeight) {
				maxHeight = carte[x][y].getHigh();
			}
			else if (carte[x][y].getHigh()<minHeight) {
				minHeight = carte[x][y].getHigh();
			}

			if (carte[x][y].getHeat()>maxHeat) {
				maxHeat = carte[x][y].getHeat();
			}
			else if (carte[x][y].getHeat()<minHeat) {
				minHeat = carte[x][y].getHeat();
			}
		}
	}
}

int Carte::getMaxHeight() {
	return maxHeight;
}

int Carte::getMaxHeat() {
	return maxHeat;
}

int Carte::getMaxMoisture() {
	return maxMoisture;
}