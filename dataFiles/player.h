#ifndef player_h
#define player_h

float playerWoodCapacity = 0;
float playerWoodValue = 100;
float playerStoneCapacity = 0;
float playerStoneValue = 100;
float playerIronCapacity = 0;
float playerIronValue = 100;
int playerPopulation = 0;
float playerWoodPerTurn = ((playerPopulation/11) * 3) * buildingsAmount[5];
float playerStonePerTurn = ((playerPopulation / 17) * 3) * buildingsAmount[6];
float playerIronPerTurn = ((playerPopulation / 21) * 3) * buildingsAmount[7];
float playerFoodValue = 1000;
float playerFoodCapacity = 1000;
float playerFoodPerTurn = 0;
int turn = 1;

//g³ód, chata rybaka only on water

#endif