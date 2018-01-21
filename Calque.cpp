#include "Calque.h"



Calque::Calque()
{
}


Calque::~Calque()
{
}

Calque::Calque(int pTaille, float d) {

	persistence = d;
	taille = pTaille;
	Tab = vector<vector<int> >(taille, vector<int>(taille,0));
	//int i, j;
	/*for (i = 0; i<taille; i++) {
		for (j = 0; j<taille; j++) {
			Tab[i][j] = 0;
		}
	}*/
}

/* accesseurs */
float Calque::getPersistence() {
	return persistence;
}

int Calque::getTab(int i, int j) {
	return Tab[i][j];
}

/* main function */
void Calque::CalqueAleatoire() {
	int i, j;
	for (i = 0; i<taille; i++) {
		for (j = 0; j<taille; j++) {
			Tab[i][j] = (int)(rand() * 256);
		}
	}

	for (i = 0; i<taille*0.05; i++) {
		for (j = 0; j<taille; j++) {
			Tab[i][j] = 0;
		}
	}
	for (j = 0; j<taille*0.05; j++) {
		for (i = 0; i<taille; i++) {
			Tab[i][j] = 0;
		}
	}
	for (i = (int)(taille - taille*0.05); i<taille; i++) {
		for (j = 0; j<taille; j++) {
			Tab[i][j] = 0;
		}
	}
	for (j = (int)(taille - taille*0.05); j<taille; j++) {
		for (i = 0; i<taille; i++) {
			Tab[i][j] = 0;
		}
	}
}

void Calque::ActionSurCalqueAleatoire(Calque pmap, int octaves, int frequence) {
	int n, i, j, a;
	Calque map = pmap;
	int frequenceCourante = frequence;
	for (i = 0; i<taille; i++) {
		for (j = 0; j<taille; j++) {
			a = valeur_interpolee(i, j, frequenceCourante, (int)(rand() * 150), map);
			//System.out.println(a);
			Tab[i][j] = a;
		}
		n = 1;
	}
}

string Calque::toString() {
	string test = "";
	int i, j;
	for (j = 0; j<taille; j++) {
		for (i = 0; i<taille; i++) {
			test += " " + Tab[i][j];
		}

	}
	return test;
}

/*************************
Private methode
****************************/


int Calque::valeur_interpolee(int i, int j, int frequenceCourante, int random, Calque map) {


	/* déterminations des bornes */
	int borne1x, borne1y, borne2x, borne2y, q;
	float pas;
	pas = (float)taille / frequenceCourante;

	q = (int)((float)i / pas);

	borne1x = (int)(q*pas);
	borne2x = (int)((q + 1)*pas);

	if (borne2x >= taille)
		borne2x = taille - 1;

	q = (int)((float)j / pas);
	borne1y = (int)(q*pas);
	borne2y = (int)((q + 1)*pas);

	if (borne2y >= taille)
		borne2y = taille - 1;

	/* récupérations des valeurs aléatoires aux bornes */
	int b00, b01, b10, b11;
	b00 = map.getTab(borne1x, borne1y);
	b01 = map.getTab(borne1x, borne2y);
	b10 = map.getTab(borne2x, borne1y);
	b11 = map.getTab(borne2x, borne2y);

	int v1 = interpolate(b00, b01, borne2y - borne1y, j - borne1y);
	int v2 = interpolate(b10, b11, borne2y - borne1y, j - borne1y);
	int fin = interpolate(v1, v2, borne2x - borne1x, i - borne1x);

	return fin;
}

int Calque::interpolate(int y1, int y2, int n, int delta) {
	if (n == 0)
		return y1;
	if (n == 1)
		return y2;

	float a = (float)delta / n;

	float v1 = (float)(3 * pow(1 - a, 2) - 2 * pow(1 - a, 3));
	float v2 = (float)(3 * pow(a, 2) - 2 * pow(a, 3));

	return (int)(y1*v1 + y2*v2);
}