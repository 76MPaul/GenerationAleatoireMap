#pragma once
#include <iostream>
#include "Calque.h"
#include "Carte.h"
#include <string>

class Generation
{
public:
	Generation();
	Generation(int ptaille, Carte &pcarte, bool paleatoire, int pfrequence, int poctaves, int indiceDeGeneration);
	~Generation();

private:
	/* variables */
	vector<Calque> calque;
	int frequence; 
	float persistance; 
	bool aleatoire;
	int octaves;
	int taille;

	int maxHeightNoramlise;
	int maxHeatNoramlise;
	int maxMoistureNoramlise;

	/* Functions */
	void perlin();
	void CalqueGen();
	void CalqueSum(Carte &pcarte, int indiceDeGeneration);
	void lissage(Carte &pcarte, int indiceDeGeneration);
	void adjustBorder(Carte &pcarte);

	void normalisation(Carte & pcarte);


};

