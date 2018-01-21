#include <iostream>
#include "Main.h"
#include <thread>
#include <mutex>
#include "visualisation.h"
#include "Generation.h"

using namespace std;

void demarrage(int ptaille, Carte &pcarte, bool paleatoire, int pfrequence, int poctaves, int indiceDeGeneration) {
	Generation gen(ptaille, pcarte, paleatoire, pfrequence, poctaves, indiceDeGeneration);
}

int main(int argc, char * argv[])
{
	int taille = 50;
	bool aleatoire = true;
	int pfrequence = 5;
	int poctaves = 8;
	int indiceDeGeneration = 1;

	Carte carte(taille);

	/*thread t1([]() {*/
		
	/*});*/
	/*thread t2();*/

	demarrage(taille, carte, aleatoire, pfrequence, poctaves, indiceDeGeneration);

	Visualisation fenetre;
	int isRunning = fenetre.launch();

	/*t1.join();
	t2.join();*/
	return 0;
}



