#pragma once
class Cases
{
public:
	Cases();
	~Cases();

	/* mutateurs */ 

	void setHigh(int phigh);
	void setMoisture(int pmoisture);
	void setHeat(int pheat);

	void setIsTown(bool ptown);
	void setIsRiver(bool priver);
	void setIsLake(bool plake);
	void setIsRoad(bool proad);

	/* accesseurs */

	int getHigh();
	int getMoisture();
	int getHeat();

	bool getIsTown();
	bool getIsRiver();
	bool getIsLake();
	bool getIsRoad();

private:
	int hauteur;
	int moisture;
	int heat;

	bool isTown;
	bool isRiver;
	bool isLake;
	bool isRoad;

};

