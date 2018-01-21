#include "Generation.h"

Generation::Generation() :calque()
{
}

Generation::Generation(int ptaille, Carte &pcarte, bool paleatoire, int pfrequence, int poctaves, int indiceDeGeneration)
{
	taille = ptaille;
	aleatoire = paleatoire;
	frequence = pfrequence;
	octaves = poctaves;
	persistance = 0.5f;
	string text = "";

	maxHeightNoramlise = 255;
	maxHeatNoramlise = 255;
	maxMoistureNoramlise = 255;

	//Création des calques de génération
	perlin();

	//Génération de la hauteur
	CalqueGen();
	CalqueSum(pcarte,1);
	adjustBorder(pcarte);
	//Ajustement de la hauteur
	CalqueSum(pcarte, 2);
	
	//Création de l'humidité
	CalqueGen();
	CalqueSum(pcarte, 3);

	//Création de la chaleur
	CalqueGen();
	CalqueSum(pcarte, 4);

	
	pcarte.max();
	normalisation(pcarte);
	pcarte.max();

	int h = 1;
}

Generation::~Generation()
{
}

void Generation::perlin()
{
	//Generation::calque;
	int i, j;
	calque.clear();
	calque.push_back(Calque(taille, 1));

	for (i = 1; i<octaves; i++) {
		calque.push_back(Calque(taille, (float)(pow(persistance, i))));
	}
}

void Generation::CalqueGen()
{
	int i;
	for (i = 0; i<octaves; i++) {
		if (i == 0) {
			calque[i].CalqueAleatoire();
		}
		else {
			calque[i].ActionSurCalqueAleatoire(calque[0], i, frequence);
		}
		if (!aleatoire) {

		}
		else {
			frequence *= frequence;
		}
	}
}

void Generation::CalqueSum(Carte &pcarte, int indiceDeGeneration)
{
	/* indiceDeGeneration
		1 -> Hauteur 
		2 -> Ajustement hauteur
		3 -> Moisture
		4 -> Heat
	*/

	/* calcul de la somme de toutes les persistances,
	pour ramener les valeurs dans un intervalle acceptable */
	int i, j, n;
	Cases caseTemp;
	float sum_persistances = 0;

	if (indiceDeGeneration == 1) {
		for (i = 0; i < octaves; i++) {
			sum_persistances += calque[i].getPersistence();
		}
	}
	else
	{
		for (i = 3; i < octaves; i++) {
			sum_persistances += calque[i].getPersistence();
		}
	}

	int tmp;
	/* ajout des calques successifs */
	bool test = false;
	for (i = 0; i<taille; i++) {
		for (j = 0; j<taille; j++) {
			for (n = 1; n<octaves; n++) {
				tmp = (int)(calque[n].getTab(i, j)*calque[n].getPersistence());

				/* normalisation */
				caseTemp = pcarte.getCaseValue(i, j);
				if (indiceDeGeneration == 1 || indiceDeGeneration == 2) {
					caseTemp.setHigh(caseTemp.getHigh() + (int)(tmp / sum_persistances));
				}
				else if (indiceDeGeneration == 3) {
					caseTemp.setMoisture(caseTemp.getMoisture() + (int)(tmp / sum_persistances));
				}
				else if (indiceDeGeneration == 4) {
					caseTemp.setHeat(caseTemp.getHeat() + (int)(tmp / sum_persistances));
				}
				pcarte.setCaseValue(i, j, caseTemp);
			}
		}
	}
	lissage(pcarte, indiceDeGeneration);
}

void Generation::lissage(Carte &pcarte, int indiceDeGeneration) {

	/* lissage */
	vector<vector<int>> tmp = vector<vector<int> >(taille, vector<int>(taille, 0));
	int x, y, a, n, k, l;
	for (x = 0; x<taille; x++) {
		for (y = 0; y<taille; y++) {
			a = 0;
			n = 0;
			if (indiceDeGeneration == 1) {
				for (k = x - 2; k <= x + 2; k++) {
					for (l = y - 2; l <= y + 2; l++) {
						if ((k >= 0) && (k < taille) && (l >= 0) && (l < taille)) {
							n++;
							a = pcarte.getCaseValue(k, l).getHigh();
						}
					}
				}
			}
			else
			{
				for (k = x - 5; k <= x + 5; k++) {
					for (l = y - 5; l <= y + 5; l++) {
						if ((k >= 0) && (k<taille) && (l >= 0) && (l<taille)) {
							n++;
							if (indiceDeGeneration == 1 || indiceDeGeneration == 2) {
								a = pcarte.getCaseValue(k, l).getHigh();
							}
							else if (indiceDeGeneration == 3) {
								a = pcarte.getCaseValue(k, l).getMoisture();
							}
							else if (indiceDeGeneration == 4) {
								a = pcarte.getCaseValue(k, l).getHeat();
							}
						}
					}
				}
			}
			tmp[x][y] = (int)((float)(a / n));
		}
	}

	Cases caseTemp;

	for (x = 0; x<taille; x++) {
		for (y = 0; y<taille; y++) {
			caseTemp = pcarte.getCaseValue(x, y);
			if (indiceDeGeneration == 1 || indiceDeGeneration == 2) {
				caseTemp.setHigh(tmp[x][y]);
			}
			else if (indiceDeGeneration == 3) {
				caseTemp.setMoisture(tmp[x][y]);
			}
			else if (indiceDeGeneration == 4) {
				caseTemp.setHeat(tmp[x][y]);
			}
			pcarte.setCaseValue(x, y, caseTemp);
		}
	}
}

void Generation::adjustBorder(Carte &pcarte) {
	int nbBorderD = 0;
	int nbIterrations = 1;

	vector<vector<int>> map2 = vector<vector<int> >(taille, vector<int>(taille,0));

	for (int i = 0; i < taille; i++) {
		for (int j = 0; j< taille; j++) {
			if (pcarte.getCaseValue(i,j).getHigh() >= 2) {
				map2[i][j] = 1;
			}
			else {
				map2[i][j] = 0;
			}
		}
	}

	for (int k = 0; k<nbIterrations; k++) {
		for (int i = 2; i < taille - 2; i++) {
			for (int j = 2; j< taille - 2; j++) {
				nbBorderD = 0;
				if (map2[i - 1][j] == 1) {
					nbBorderD++;
				}
				if (map2[i + 1][j] == 1) {
					nbBorderD++;
				}
				if (map2[i][j - 1] == 1) {
					nbBorderD++;
				}
				if (map2[i][j + 1] == 1) {
					nbBorderD++;
				}
				if (map2[i - 1][j - 1] == 1) {
					nbBorderD++;
				}
				if (map2[i + 1][j + 1] == 1) {
					nbBorderD++;
				}
				if (map2[i + 1][j - 1] == 1) {
					nbBorderD++;
				}
				if (map2[i - 1][j + 1] == 1) {
					nbBorderD++;
				}

				if (nbBorderD<4) {
					map2[i][j] = 0;
				}
				else if (nbBorderD >= 5) {
					map2[i][j] = 1;
				}
			}
		}
	}

	for (int i = 2; i < taille - 2; i++) {
		for (int j = 2; j< taille - 2; j++) {
			nbBorderD = 0;
			if (map2[i - 1][j] == 1) {
				nbBorderD++;
			}
			if (map2[i + 1][j] == 1) {
				nbBorderD++;
			}
			if (map2[i][j - 1] == 1) {
				nbBorderD++;
			}
			if (map2[i][j + 1] == 1) {
				nbBorderD++;
			}
			if (map2[i - 1][j - 1] == 1) {
				nbBorderD++;
			}
			if (map2[i + 1][j + 1] == 1) {
				nbBorderD++;
			}
			if (map2[i + 1][j - 1] == 1) {
				nbBorderD++;
			}
			if (map2[i - 1][j + 1] == 1) {
				nbBorderD++;
			}
			if (nbBorderD >= 7) {
				map2[i][j] = 1;
			}
			else if (nbBorderD <= 1) {
				map2[i][j] = 0;
			}
		}
	}

	Cases tmp; 
	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < taille; j++) {
			if (map2[i][j] != 1) {
				tmp = pcarte.getCaseValue(i, j);
				tmp.setHigh(0);
				pcarte.setCaseValue(i, j, tmp);
			}
		}
	}
}

void Generation::normalisation(Carte &pcarte) {
	Cases tmp;
	int maxHeight = pcarte.getMaxHeight();
	int maxHeat = pcarte.getMaxHeat();
	int maxMoisture = pcarte.getMaxMoisture();

	int height = 0;
	int heat = 0;
	int moisture = 0;


	for (int i = 0; i < taille; i++) {
		for (int j = 0; j < taille; j++) {
				tmp = pcarte.getCaseValue(i, j);
				height = (int)((double)tmp.getHigh() / (double)maxHeight*maxHeightNoramlise);
				heat = (int)((double)tmp.getHeat() / (double)maxHeat*maxHeatNoramlise);
				moisture = (int)((double)tmp.getMoisture() / (double)maxMoisture*maxMoistureNoramlise);

				tmp.setHigh(height);
				tmp.setHeat(heat);
				tmp.setMoisture(moisture);
				pcarte.setCaseValue(i, j, tmp);
		}
	}
}