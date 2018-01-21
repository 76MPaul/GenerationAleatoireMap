#include "Cases.h"



Cases::Cases()
{
	hauteur = 0;
	moisture = 0;
	heat = 0;

	isTown = false;
	isRiver = false;
	isLake = false;
	isRoad = false;
}


Cases::~Cases()
{
}

void Cases::setHigh(int phigh)
{
	hauteur = phigh;
}

void Cases::setMoisture(int pmoisture)
{
	moisture = pmoisture;
}

void Cases::setHeat(int pheat)
{
	heat = pheat;
}

void Cases::setIsTown(bool ptown)
{
	isTown = ptown;
}

void Cases::setIsRiver(bool priver)
{
	isRiver = priver;
}

void Cases::setIsLake(bool plake)
{
	isLake = plake;
}

void Cases::setIsRoad(bool proad)
{
	isRoad = proad;
}

int Cases::getHigh()
{
	return hauteur;
}

int Cases::getMoisture()
{
	return moisture;
}

int Cases::getHeat()
{
	return heat;
}

bool Cases::getIsTown()
{
	return isTown;
}

bool Cases::getIsRiver()
{
	return isRiver;
}

bool Cases::getIsLake()
{
	return isLake;
}

bool Cases::getIsRoad()
{
	return isRoad;
}
