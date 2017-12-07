#ifndef map_h
#define map_h
#include "library.h"

using namespace std;
using namespace sf;

void MAP_GENERATOR();
void ADD_BUILDING(int x, int y, int id, string name);
void ADD_BUILDING_MAIN(int x, int y, int id, string name);
void REMOVE_BUILDING(int x, int y, int id);
void UPGRADE_BUILDING(int x, int y, string name);
void UPGRADE_BUILDING_COST(int x, int y, string name);
void PLACE_BUILDING(string building);
void PLACE_BUILDING_MAIN(int spIdX, int spIdY, int priceId);
void UPGRADE_BUILDING_MAIN(int x, int y, int woodCost, int stoneCost, int ironCost);
void UPGRADE_BUILDING_COST_MAIN(int x, int y, int woodCost, int stoneCost, int ironCost);

string mapFieldsNames[10][10];
string mapFieldsNamesPol[10][10];
float mapFieldsWoodCapacity[10][10];
float mapFieldsWoodValue[10][10];
float mapFieldsStoneCapacity[10][10];
float mapFieldsStoneValue[10][10];
float mapFieldsIronCapacity[10][10];
float mapFieldsIronValue[10][10];
string mapName = "mapName";

string mapFieldsBuildings[10][10];
string buildingsStrings[50] = { "townHall", "storage", "simpleHouse", "woodenHouse", "stoneHouse", 
								"lumberjack", "quarry", "mine", "farm", "fish", 
								"hunting", "gather", "windmill", "carpenter"};
int buildingsAmount[50];
// 0 - townHall, 1 - storage, 2 - simpleHouse, 3 - WoodenHouse, 4 - StoneHouse, 
// 5 - lumberjack, 6 - quarry, 7 - mine, 8 - farm, 9 - fish, 10 - hunting
// 10 - hunting, 11 - gather, 12 - windmill, 13 - carpenter

int buildingsPriceWood[50] = { 0, 50, 20, 30, 30,
							   10, 55, 50, 20, 35,
							   35, 40, 55, 45};

int buildingsPriceStone[50] = { 0, 25, 5, 15, 30,
								5, 5, 15, 5, 15,
								15, 10, 45, 15};

int buildingsPriceIron[50] = { 0, 10, 0, 5, 20, 
							   0, 15, 5, 0, 5,
							   10, 0, 25, 40};

// 0 - (w:0, s:0, i:0) 1 - (w:50, s:25, i:10), 2 - (w:20, s:5, i:0), 3 - (w:30, s:15, i:5), 4 - (w:30, s:30, i:20)
// 5 - (w:10, s:5, i:0), 6 - (w:55, s:5, i:15), 7 - (w:50, s:15, i:5), 8 - (w:20, s:5, i:0), 9 - (w:35, s:15, i:5)
// 10 - (w:35, :15, i:10), 11 - (w:40, s:10, i:0), 12 - (w:55, s:45, i:25), 13 - (w:45, s:15, i:40)

bool upgradeBuilding[10][10];

bool workField[10][10];

int loadGenerateMap = 0;

extern int playerPopulation;
extern Time mainTime;
extern Clock mainClock;
extern float playerWoodCapacity, playerStoneCapacity, playerIronCapacity, playerFoodValue, playerFoodCapacity;

void MAP_GENERATOR() {
	loadGenerateMap = 1;	//infoline
	cout << "Map Generation..." << endl;	//infoline
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			mapFieldsBuildings[i][j] = "";
	for (int i = 0; i < 20; i++) {
		buildingsAmount[i] = 0;
	}
	bool isTownHall = false;
	playerPopulation = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			mainTime = mainClock.getElapsedTime();
			srand((int)mainTime.asMilliseconds());
			cout << loadGenerateMap << "%, " << "Seed: " << rand() % 1000 + 1 << ", ";	//infoline
			for (int k = 0; k < 1; k++) {
				/*500 - 50%*/	if (((rand() % 1000) + 1) % 2 == 0) {
					mapFieldsNames[i][j] = "grass";
					cout << "Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
				/*167 - 16.7%*/	if (((rand() % 1000) + 1) % 3 == 0) {
					mapFieldsNames[i][j] = "dirt";
					cout << "Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = ((rand() % 50) + 75)*0.8;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = ((rand() % 50) + 75)*0.8;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
				/*95 - 9.5%*/	if (((rand() % 1000) + 1) % 5 == 0 || ((rand() % 1000) + 1) % 17 == 0 || ((rand() % 1000) + 1) % 19 == 0) {
					mapFieldsNames[i][j] = "grass";	//WOLNE 9.5%
					cout << "?Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = (rand() % 50) + 75;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
				/*55 - 5.5%*/	if (((rand() % 1000) + 1) % 7 == 0 || ((rand() % 1000) + 1) % 23 == 0 || ((rand() % 1000) + 1) % 29 == 0 || ((rand() % 1000) + 1) % 31 == 0 || ((rand() % 1000) + 1) % 37 == 0) {
					mapFieldsNames[i][j] = "mountain";
					cout << "Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = ((rand() % 50) + 75)*0.65;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = ((rand() % 50) + 75) * 4;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = ((rand() % 50) + 75)*3.2;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
				/*36 - 3.6%*/	if (((rand() % 1000) + 1) % 11 == 0 || ((rand() % 1000) + 1) % 13 == 0 || ((rand() % 1000) + 1) % 41 == 0 || ((rand() % 1000) + 1) % 43 == 0 || ((rand() % 1000) + 1) % 47 == 0 || ((rand() % 1000) + 1) % 53 == 0 || ((rand() % 1000) + 1) % 59 == 0 || ((rand() % 1000) + 1) % 61 == 0 || ((rand() % 1000) + 1) % 67 == 0 || ((rand() % 1000) + 1) % 71 == 0 || ((rand() % 1000) + 1) % 73 == 0 || ((rand() % 1000) + 1) % 79 == 0) {
					mapFieldsNames[i][j] = "water";
					cout << "Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = ((rand() % 50) + 75)*0.1;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = ((rand() % 50) + 75)*0.1;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = ((rand() % 50) + 75)*0.05;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
				/*147 - 14.7%*/	else {
					mapFieldsNames[i][j] = "forest";
					cout << "Field " << "[" << i << "]" << "[" << j << "]" << ": " << mapFieldsNames[i][j] << ", "; //infoline

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMilliseconds());
					mapFieldsWoodCapacity[i][j] = ((rand() % 50) + 75)*2.4;
					mapFieldsWoodValue[i][j] = mapFieldsWoodCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "wood: " << mapFieldsWoodCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsStoneCapacity[i][j] = ((rand() % 50) + 75)*1.1;
					mapFieldsStoneValue[i][j] = mapFieldsStoneCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "stone: " << mapFieldsStoneCapacity[i][j] << ", ";

					mainTime = mainClock.getElapsedTime();
					srand((int)mainTime.asMicroseconds());
					mapFieldsIronCapacity[i][j] = ((rand() % 50) + 75)*1.5;
					mapFieldsIronValue[i][j] = mapFieldsIronCapacity[i][j];
					cout << "(s:" << (rand() % 125) + 75 << ")" << "iron: " << mapFieldsIronCapacity[i][j] << ", " << endl;
					break;
				}
			}
			//RATUSZ I MAGAZYN \/
			mainTime = mainClock.getElapsedTime();
			srand((int)mainTime.asMilliseconds());
			if (isTownHall == false) {
				if (((rand() % 100) + 1) % 29 == 0 && mapFieldsNames[i][j] != "water") {
					ADD_BUILDING(i, j, 0, "townHall");
					cout << "[!] Generated Town Hall on field " << "[" << i << "] [" << j << "]" << endl;
					//					playerPopulation += 10;
					isTownHall = true;
					if (i < 9) {
						mapFieldsBuildings[i + 1][j] = "storage";
						buildingsAmount[1]++;
						playerWoodCapacity = 200 * buildingsAmount[1];
						playerStoneCapacity = 175 * buildingsAmount[1];
						playerIronCapacity = 150 * buildingsAmount[1];
						cout << "[!] Generated Storage on field " << "[" << i + 1 << "] [" << j << "]" << endl;
						if (mapFieldsNames[i + 1][j] == "water")	mapFieldsNames[i + 1][j] = "grass";
					}
					else if (i > 0) {
						mapFieldsBuildings[i - 1][j] = "storage";
						buildingsAmount[1]++;
						playerWoodCapacity = 200 * buildingsAmount[1];
						playerStoneCapacity = 175 * buildingsAmount[1];
						playerIronCapacity = 150 * buildingsAmount[1];
						cout << "[!] Generated Storage on field " << "[" << i - 1 << "] [" << j << "]" << endl;
						if (mapFieldsNames[i - 1][j] == "water")	mapFieldsNames[i - 1][j] = "grass";
					}
				}
				if (isTownHall == false && i > 8) {
					if (((rand() % 100) + 1) % 3 == 0 && mapFieldsNames[i][j] != "water") {
						ADD_BUILDING(i, j, 0, "townHall");
						cout << "[!] Generated Town Hall on field " << "[" << i << "] [" << j << "]" << endl;
						//						playerPopulation += 10;
						isTownHall = true;
						if (i < 9) {
							mapFieldsBuildings[i + 1][j] = "storage";
							buildingsAmount[1]++;
							playerWoodCapacity = 200 * buildingsAmount[1];
							playerStoneCapacity = 175 * buildingsAmount[1];
							playerIronCapacity = 150 * buildingsAmount[1];
							cout << "[!] Generated Storage on field " << "[" << i + 1 << "] [" << j << "]" << endl;
							if (mapFieldsNames[i + 1][j] == "water")	mapFieldsNames[i + 1][j] = "grass";
						}
						else if (i > 0) {
							mapFieldsBuildings[i - 1][j] = "storage";
							buildingsAmount[1]++;
							playerWoodCapacity = 200 * buildingsAmount[1];
							playerStoneCapacity = 175 * buildingsAmount[1];
							playerIronCapacity = 150 * buildingsAmount[1];
							cout << "[!] Generated Storage on field " << "[" << i - 1 << "] [" << j << "]" << endl;
							if (mapFieldsNames[i - 1][j] == "water")	mapFieldsNames[i - 1][j] = "grass";
						}
					}
					if (isTownHall == false && i == 9 && j == 9) {
						ADD_BUILDING(i, j, 0, "townHall");
						cout << "[!] Generated Town Hall on field " << "[" << i << "] [" << j << "]" << endl;
						//						playerPopulation += 10;
						isTownHall = true;
						if (i < 9) {
							mapFieldsBuildings[i + 1][j] = "storage";
							buildingsAmount[1]++;
							playerWoodCapacity = 200 * buildingsAmount[1];
							playerStoneCapacity = 175 * buildingsAmount[1];
							playerIronCapacity = 150 * buildingsAmount[1];
							cout << "[!] Generated Storage on field " << "[" << i + 1 << "] [" << j << "]" << endl;
							if (mapFieldsNames[i + 1][j] == "water")	mapFieldsNames[i + 1][j] = "grass";
						}
						else if (i > 0) {
							mapFieldsBuildings[i - 1][j] = "storage";
							buildingsAmount[1]++;
							playerWoodCapacity = 200 * buildingsAmount[1];
							playerStoneCapacity = 175 * buildingsAmount[1];
							playerIronCapacity = 150 * buildingsAmount[1];
							cout << "[!] Generated Storage on field " << "[" << i - 1 << "] [" << j << "]" << endl;
							if (mapFieldsNames[i - 1][j] == "water")	mapFieldsNames[i - 1][j] = "grass";
						}
					}
				}
			}
			if (mapFieldsBuildings[i][j] == "townHall" && mapFieldsNames[i][j] == "water") {
				mapFieldsNames[i][j] = "grass";
				cout << "[!] Changed field [" << i << "] [" << j << "] from water to grass (!townHall)" << endl;
			}
			if (mapFieldsBuildings[i][j] == "storage" && mapFieldsNames[i][j] == "water") {
				mapFieldsNames[i][j] = "grass";
				cout << "[!] Changed field [" << i << "] [" << j << "] from water to grass (!storage)" << endl;
			}
			playerFoodCapacity = 1200;
			playerFoodValue = 770;
			Sleep(1);
			loadGenerateMap++;	//infoline
		}
	}
}

#endif