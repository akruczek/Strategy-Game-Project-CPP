#ifndef map_h
#define map_h

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
								"lumberjack", "quarry", "mine", "farm", "fish"};
int buildingsAmount[50];
// 0 - townHall, 1 - storage, 2 - simpleHouse, 3 - WoodenHouse, 4 - StoneHouse, 
// 5 - lumberjack, 6 - quarry, 7 - mine, 8 - farm, 9 - fish

int buildingsPriceWood[50] = { 0, 50, 20, 30, 30,
							   10, 55, 50, 20, 35};

int buildingsPriceStone[50] = { 0, 25, 5, 15, 30,
								 5, 5, 15, 5, 15};

int buildingsPriceIron[50] = { 0, 10, 0, 5, 20, 
							    0, 15, 5, 0, 5};

// 1 - (w:50, s:25, i:10), 2 - (w:20, s:5, i:0), 3 - (w:30, s:15, i:5), 4 - (w:30, s:30, i:20)
// 5 - (w:10, s:5, i:0), 6 - (w:55, s:5, i:15), 7 - (w:50, s:15, i:5), 8 - (w:20, s:5, i:0), 9 - (w:35, s:15, i:5)

bool upgradeBuilding[10][10];

bool workField[10][10];

int loadGenerateMap = 0;

#endif