#include "library.h"
bool antialiasing = true;
bool fullscreenMode = false;

using namespace std;
using namespace sf;

RenderWindow window;
Event event;
Color darkRed(220, 220, 50, 100);
string incode = "";
int mouseX, mouseY;
Clock mainClock;
Time mainTime;
int timeSeconds, timeMilliseconds;
int timer = 0;
Uint32 unicode = event.text.unicode;

void MAIN_MENU(), MAIN_MENU_SETTINGS(), MAIN_MENU_LOAD_GAME(), MAIN_MENU_NEW_GAME();
void CHECKBOX(int posX, int posY, bool argumanet[], wstring checkboxName, int boxesNumber, wstring box1, wstring box2, wstring box3, wstring box4, wstring box5, wstring box6);
string INPUT_TEXT(int posX, int posY, wstring inputTextName, string outputString);
void START_GAME();
void MAP_GENERATOR();
void CHEATS();
void FIELD_ZOOM(int i, int j);
void YES_NO_BOX(wstring boxContent, wstring boxExtraContent);
void RELOAD_LANGUAGE_STRINGS();
void ADD_BUILDING(int x, int y, int id, string name);
void REMOVE_BUILDING(int x, int y, int id);
void UPGRADE_BUILDING(int x, int y, string name);
void UPGRADE_BUILDING_COST(int x, int y, string name);
void NEXT_TURN();
void PLACE_BUILDING(string building);
void PLACE_BUILDING_MAIN(int spIdX, int spIdY, int priceId);
void CHECK_STATUS_1();
bool yesNoBoxActive = false;
bool difficulty[3] = { 1, 0, 0 };
bool mapSize[3] = { 0, 1, 0 };

bool textareaActive = false;
String inputText("");
random_device rd;

mt19937 rng(rd());
uniform_int_distribution<int> uni(1, 1000);
auto random_integer = uni(rng);
int tAddon = 0;

#include "myFunctions.h"
#include "fonts.h"
#include "sounds.h"
#include "textures.h"
#include "saves.h"
#include "map.h"
#include "player.h"
#include "text.h"

int main()	{
	window.create(VideoMode(1280, 720, 32), "Main Menu");		//TWORZENIE OKNA (1280x720)
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);	//Limit 30FPS
	LOAD_FONTS();
	LOAD_SOUNDS();
	MAIN_MENU();
}

void MAIN_MENU() {
	incode = "mainMenu";
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) { CHEATS(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//NOWA GRA
							MAIN_MENU_NEW_GAME();
							break;
						case 1:	//WCZYTAJ GRÊ
							MAIN_MENU_LOAD_GAME();
							break;
						case 2:	//USTWIENIA
							window.clear();
							MAIN_MENU_SETTINGS();
							break;
						case 3:	//WYJŒCIE
							window.close();
							break;
						}
					}
				}
			}
		}
		window.clear();
		
		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);
			
			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		window.display();
	}
}

void MAIN_MENU_SETTINGS() {
	incode = "mainMenuSettings";
	window.setTitle("Main Menu - Settings");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//JÊZYK
							if (lang == "english")
								lang = "polish";
							else
								lang = "english";
							SET_TEXT(incode);
							break;
						case 1:	//FULLSCREEN
							if (fullscreenMode == false) {
								window.create(VideoMode(1280, 720, 32), "life-simulator", Style::Fullscreen);
								fullscreenMode = true;
							}
							else {
								window.create(VideoMode(1280, 720, 32), "life-simulator");
								fullscreenMode = true;
							}
							SET_TEXT(incode);
							break;
						case 2:	//ANTIALIASING
							if (antialiasing == false) {
								SET_ANTIALIASING();
								antialiasing = true;
							}
							else {
								SET_ANTIALIASING();
								antialiasing = false;
							}
							SET_TEXT(incode);
							break;
						case 3:	//POWRÓT
							window.clear();
							MAIN_MENU();
							break;
						}
					}
				}
			}
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		for (int i = 4; i < 7; i++) {	//TEXT
			window.draw(txt[0][i]);
		}

		window.display();
	}
}

void MAIN_MENU_LOAD_GAME() {
	incode = "mainMenuLoadGame";
	window.setTitle("Main Menu - Load Game");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				for (int i = 0; i < 4; i++) {
					if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i)) {
						switch (i) {
						case 0:	//SAVE 1

							break;
						case 1:	//SAVE 2
							
							break;
						case 2:	//SAVE 3
							
							break;
						case 3:	//POWRÓT
							MAIN_MENU();
							break;
						}
					}
				}
			}
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 4; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= (640 - (txt[0][i].getLocalBounds().width / 2) - 10) && mouseX <= (640 + (txt[0][i].getLocalBounds().width / 2) - 10) && mouseY >= 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i) && mouseY <= 150 + (txt[0][i].getLocalBounds().height / 2) + (80 * i))
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		for (int i = 4; i < 7; i++) {	//TEXT
			window.draw(txt[0][i]);
		}

		window.display();
	}
}

void MAIN_MENU_NEW_GAME() {
	mainClock.restart();
	incode = "mainMenuNewGame";
	window.setTitle("Main Menu - New Game");
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	textareaActive = false;
	txt[5][8].setString("");
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				cout << endl << difficulty[0] << endl;
				cout << mapSize[0] << endl;
				if (mouseX >= txt[0][0].getPosition().x && mouseX <= txt[0][0].getPosition().x + txt[0][0].getLocalBounds().width && mouseY >= txt[0][0].getPosition().y && mouseY <= txt[0][0].getPosition().y + txt[0][0].getLocalBounds().height) {
					window.clear();
					MAIN_MENU();
					break;
				}
				if (mouseX >= txt[0][1].getPosition().x && mouseX <= txt[0][1].getPosition().x + txt[0][1].getLocalBounds().width && mouseY >= txt[0][1].getPosition().y && mouseY <= txt[0][1].getPosition().y + txt[0][1].getLocalBounds().height) {
					window.clear();
					MAP_GENERATOR();	//[!] GENEROWANIE MAPY [!]
					START_GAME();
					break;
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				textareaActive = false;
		}
		window.clear();

		for (int i = 0; i < 2; i++) {	//SPRITE
			window.draw(sp[0][i]);
		}

		for (int i = 0; i < 2; i++) {	//TEXT
			window.draw(txt[0][i]);

			if (mouseX >= txt[0][i].getPosition().x && mouseX <= txt[0][i].getPosition().x + txt[0][i].getLocalBounds().width && mouseY >= txt[0][i].getPosition().y && mouseY <= txt[0][i].getPosition().y + txt[0][i].getLocalBounds().height)
				txt[0][i].setFillColor(darkRed);
			else
				txt[0][i].setFillColor(Color::Black);
		}

		
		if (lang == "english")	CHECKBOX(480, 120, difficulty, L"Difficulty", 3, L"Easy", L"Medium", L"Hard", L"", L"", L"");
		if (lang == "polish")	CHECKBOX(480, 120, difficulty, L"Trudnoœæ", 3, L"£atwy", L"Œredni", L"Trudny", L"", L"", L"");

		if (lang == "english")	CHECKBOX(640, 120, mapSize, L"Map Size", 3, L"Small", L"Medium", L"Large", L"", L"", L"");
		if (lang == "polish")	CHECKBOX(640, 120, mapSize, L"Rozmiar", 3, L"Ma³y", L"Œredni", L"Du¿y", L"", L"", L"");

		if (lang == "english")	mapName = INPUT_TEXT(470, 300, L"World Name", mapName);
		if (lang == "polish")	mapName = INPUT_TEXT(470, 300, L"Nazwa Œwiata", mapName);

		window.display();
	}
}

void START_GAME() {
	incode = "startGame";
	window.setTitle("Start Game");
	yesNoBoxActive = false;
	playerWoodValue = 100;
	playerStoneValue = 75;
	playerIronValue = 50;
	turn = 1;
	LOAD_TEXTURES(incode);
	LOAD_SPRITE();
	SET_SPRITE(incode);
	SET_TEXT(incode);
	int fieldActiveByMouseX = 0;
	int fieldActiveByMouseY = 0;
	bool placeBuilding = false;
	bool pickingMaterialsWood = false;
	bool pickingMaterialsStone = false;
	bool pickingMaterialsIron = false;
	bool pickingMaterialsFood = false;
	bool removingBuildings = false;
	bool upgradingBuildings = false;
	int placeBuildingId = 0;
	string placeBuildingName = "";
	CHECK_STATUS_1();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			KLICK(event);
			if (event.type == Event::MouseMoved) { INFO(event); mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::MouseButtonPressed) {
				if (mouseX > 700 || mouseX < 50 || mouseY < 50 || mouseY > 700) {
					placeBuilding = false;			pickingMaterialsWood = false;	pickingMaterialsStone = false; pickingMaterialsIron = false;
					pickingMaterialsFood = false;	removingBuildings = false;		upgradingBuildings = false;
				}
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 3; j++) {
						if (mouseX >= 720 + (55 * i) && mouseX <= 770 + (55 * i) && mouseY >= 660 - (55 * j) && mouseY <= 710 - (55 * j)) {
							switch (j) {
							case 0:	//PIERWSZY WIERSZ OD DO£U
								switch (i) {
								case 0: NEXT_TURN(); break;
								case 1: break;
								case 2: removingBuildings = true; break;
								case 3: upgradingBuildings = true; break;
								case 4: pickingMaterialsFood = true; break;
								case 5: pickingMaterialsWood = true; break;
								case 6: pickingMaterialsStone = true; break;
								case 7: pickingMaterialsIron = true; break;
								case 8: CHEATS(); break;	//INFO
								case 9: yesNoBoxActive = true; break;
								}
								break;
							case 1:	//DRUGI WIERSZ OD DO£U
								switch (i) {
								case 0: placeBuilding = true; placeBuildingName = "simpleHouse"; placeBuildingId = 2; break;
								case 1: placeBuilding = true; placeBuildingName = "woodenHouse"; placeBuildingId = 3; break;
								case 2: placeBuilding = true; placeBuildingName = "stoneHouse"; placeBuildingId = 4; break;
								case 3: placeBuilding = true; placeBuildingName = "lumberjack"; placeBuildingId = 5; break;
								case 4: placeBuilding = true; placeBuildingName = "quarry"; placeBuildingId = 6; break;
								case 5: placeBuilding = true; placeBuildingName = "mine"; placeBuildingId = 7; break;
								case 6: break;
								case 7: break;
								case 8: placeBuilding = true; placeBuildingName = "storage"; placeBuildingId = 1; break;
								case 9: /*TOWN HALL*/break;
								}
								break;
							case 2:	//TRZECI WIERSZ OD DO£U
								switch (i) {
								case 0: placeBuilding = true; placeBuildingName = "farm"; placeBuildingId = 8; break;
								case 1: placeBuilding = true; placeBuildingName = "fish"; placeBuildingId = 9; break;
								case 2: break;
								case 3: break;
								case 4: break;
								case 5: break;
								case 6: break;
								case 7: break;
								case 8: break;
								case 9: break;
								}
								break;
							}
						}
					}
				}

				//YES_NO BOX
				if (yesNoBoxActive == true) {
					if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						window.clear();
						MAIN_MENU();
					}
					if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						yesNoBoxActive = false;
					}
				}

				//PLACE BUILDING
				if (placeBuilding == true) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								ADD_BUILDING(i, j, placeBuildingId, placeBuildingName);
								placeBuilding = false;
							}
						}
					}
				}

				//PICKING MATERIALS \/
				if (pickingMaterialsWood || pickingMaterialsStone || pickingMaterialsIron || pickingMaterialsFood) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (pickingMaterialsWood && mapFieldsWoodValue[i][j]>=1) {
									if (mapFieldsWoodValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerWoodValue++;
											mapFieldsWoodValue[i][j]--;
										}
										else {
											playerWoodValue += 0.1;
											mapFieldsWoodValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsStone && mapFieldsStoneValue[i][j] >= 1) {
									if (mapFieldsStoneValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerStoneValue++;
											mapFieldsStoneValue[i][j]--;
										}
										else {
											playerStoneValue += 0.1;
											mapFieldsStoneValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsIron && mapFieldsIronValue[i][j] >= 1) {
									if (mapFieldsIronValue[i][j] > 1) {
										if (mapFieldsNames[i][j] != "water") {
											playerIronValue++;
											mapFieldsIronValue[i][j]--;
										}
										else {
											playerIronValue += 0.1;
											mapFieldsIronValue[i][j] -= 0.1;
										}
										NEXT_TURN();
									}
								}
								else if (pickingMaterialsFood) {
									playerFoodValue += 10;
									mapFieldsWoodValue[i][j] -= 0.1;
									NEXT_TURN();
								}
							}
						}
					}
				}

				//REMOVE 
				if (removingBuildings) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (mapFieldsBuildings[i][j] == "")
									removingBuildings = false;
								else {
									if (mapFieldsBuildings[i][j] != "townHall") {
										for (int k = 0; k < 50; k++) {
											if (mapFieldsBuildings[i][j] == buildingsStrings[k]) {
												removingBuildings = false;
												REMOVE_BUILDING(i, j, k); break; 
											}
										}
									}
									else
										removingBuildings = false;
								}
							}
						}
					}
				}

				//UPGRADE
				if (upgradingBuildings) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								if (mapFieldsBuildings[i][j] != "" && !upgradeBuilding[i][j]) {
									UPGRADE_BUILDING(i, j, mapFieldsBuildings[i][j]);
									upgradingBuildings = false;
								}
								else
									upgradingBuildings = false;
							}
						}
					}
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) { CHEATS(); }
			}
			window.clear(Color::White);

			window.draw(sp[0][0]);	//T£O

			//WYŒWIETLANIE T£A PRZYCISKÓW U DO£U EKRANU
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					sp[0][1].setPosition(720 + (55 * i), 660 - (55 * j));
					window.draw(sp[0][1]);
				}
			}

			//PODŒWIETLENIE IKON \/
			if (!yesNoBoxActive) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 3; j++) {
						if (mouseY >= 660 - (j * 55) && mouseY <= 706 - (j * 55) && mouseX >= 720 + (55 * i) && mouseX <= 720 + (55 * i) + 50 - 4) {	//2-4px cieñ [!]
							sp[4][20 + i + (j * 10)].setColor(darkRed);
						}
						else {
							sp[4][20 + i + (j * 10)].setColor(Color::Black);
							if (i == 9 && j == 1)	sp[4][20 + i + (j * 10)].setColor(darkRed);		//RATUSZ
						}
					}
				}
			}

			//WYŒWIETLANIE IKON PRZYCISKÓW U DO£U EKRANU \/?
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 3; j++) {
					sp[4][20 + i + (j * 10)].setPosition(727 + (55 * i), 666 - (55 * j));
					if (i == 9 && j == 0)	sp[4][20 + i + (j * 10)].move(-2, 2);			//EXIT
					if (i == 9 && j == 1)	sp[4][20 + i + (j * 10)].setColor(darkRed);		//RATUSZ
					window.draw(sp[4][20 + i + (j * 10)]);
				}
			}

			//WYŒWIETLANIE PÓL
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 1; k++) {
						if (mapFieldsNames[i][j] == "grass") {
							sp[5][5].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][5]);
							break;
						}
						if (mapFieldsNames[i][j] == "dirt") {
							sp[5][6].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][6]);
							break;
						}
						if (mapFieldsNames[i][j] == "water") {
							sp[5][7].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][7]);
							break;
						}
						if (mapFieldsNames[i][j] == "forest") {
							sp[5][8].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][8]);
							break;
						}
						if (mapFieldsNames[i][j] == "mountain") {
							sp[5][9].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][9]);
							break;
						}
					}
				}
			}

			//YWŒWIETLANIE ZBLI¯ENIA POLA
			if (!yesNoBoxActive) {
				if (mouseX >= 50 && mouseX <= 700 && mouseY >= 50 && mouseY <= 700) {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 10; j++) {
							if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
								fieldActiveByMouseX = i;
								fieldActiveByMouseY = j;
								for (int k = 0; k < 1; k++) {
									if (mapFieldsNames[i][j] == "grass") {
										sp[4][0].setTexture(tex[4][0]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "dirt") {
										sp[4][0].setTexture(tex[4][1]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "water") {
										sp[4][0].setTexture(tex[4][2]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "forest") {
										sp[4][0].setTexture(tex[4][3]);
										FIELD_ZOOM(i, j);
										break;
									}
									if (mapFieldsNames[i][j] == "mountain") {
										sp[4][0].setTexture(tex[4][4]);
										FIELD_ZOOM(i, j);
										break;
									}
								}
							}
						}
					}
					window.draw(sp[4][0]);
					for (int i = 0; i < 5; i++)
						window.draw(txt[0][i]);
					window.draw(txt[0][12]);
				}
			}
			window.draw(txt[5][10]);

			//IKONY BUDYNKÓW \/
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 1; k++) {
						if (mapFieldsBuildings[i][j] == "townHall") {
							sp[4][39].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][39].setColor(Color::Black);	window.draw(sp[4][39]);  break;
						}
						if (mapFieldsBuildings[i][j] == "storage") {
							sp[4][38].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][38].setColor(Color::Black);	window.draw(sp[4][38]); break;
						}
						if (mapFieldsBuildings[i][j] == "simpleHouse") {
							sp[4][30].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][30].setColor(Color::Black);	window.draw(sp[4][30]); break;
						}
						if (mapFieldsBuildings[i][j] == "woodenHouse") {
							sp[4][31].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][31].setColor(Color::Black);	window.draw(sp[4][31]); break;
						}
						if (mapFieldsBuildings[i][j] == "stoneHouse") {
							sp[4][32].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][32].setColor(Color::Black);	window.draw(sp[4][32]); break;
						}
						if (mapFieldsBuildings[i][j] == "lumberjack") {
							sp[4][33].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][33].setColor(Color::Black);
							if (mapFieldsWoodValue[i][j] < 1) sp[4][33].setColor(darkRed);
							window.draw(sp[4][33]); break;
						}
						if (mapFieldsBuildings[i][j] == "quarry") {
							sp[4][34].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][34].setColor(Color::Black);
							if (mapFieldsStoneValue[i][j] < 1) sp[4][34].setColor(darkRed);
							window.draw(sp[4][34]); break;
						}
						if (mapFieldsBuildings[i][j] == "mine") {
							sp[4][35].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][35].setColor(Color::Black);
							if (mapFieldsIronValue[i][j] < 1) sp[4][35].setColor(darkRed);
							window.draw(sp[4][35]); break;
						}
						if (mapFieldsBuildings[i][j] == "farm") {
							sp[4][40].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][40].setColor(Color::Black);	window.draw(sp[4][40]); break;
						}
						if (mapFieldsBuildings[i][j] == "fish") {
							sp[4][41].setPosition(52 + (65 * i), 57 + (65 * j));	sp[4][41].setColor(Color::Black);	window.draw(sp[4][41]); break;
						}
					}
					if (upgradeBuilding[i][j] == true) { sp[1][3].setPosition(72 + (65 * i), 54 + (65 * j)); window.draw(sp[1][3]); }
				}
			}

			sp[5][47].setPosition(645, 3);
			window.draw(sp[5][47]);
			txt[0][17].setString(TO_STRINGSTREAM(playerFoodValue));
			txt[0][17].setFillColor(Color::White);
			window.draw(txt[0][17]);

			sp[4][5].setPosition(450, 10);
			window.draw(sp[4][5]);
			sp[4][6].setPosition(451, 11);
			window.draw(sp[4][6]);
			for (int i = 0; i < (((playerFoodValue / playerFoodCapacity)) * 100) - 13; i++) {
				sp[4][6].move(2, 0);
				window.draw(sp[4][6]);
			}
			txt[0][16].setString(TO_STRINGSTREAM(((playerFoodValue / playerFoodCapacity)) * 100) + "%");
			txt[0][16].setPosition(540 - txt[0][16].getLocalBounds().width / 2, 18);
			window.draw(txt[0][16]);
			window.draw(txt[0][15]);

			//WYŒWIETLANIE IKON SUROWCÓW (JEŒLI WIÊKSZE NI¯ 100) \/
			for (int i = 0; i < 3; i++)
				sp[1][i].setScale(0.35, 0.35);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					tAddon = 0;
					if (mapFieldsWoodValue[i][j] >= 100) {
						sp[1][0].setPosition(52 + (65 * i), 95 + (65 * j));
						window.draw(sp[1][0]);
						tAddon++;
					}
					if (mapFieldsStoneValue[i][j] >= 100) {
						sp[1][1].setPosition(52 + (20 * tAddon) + (65 * i), 95 + (65 * j));
						window.draw(sp[1][1]);
						tAddon++;
					}
					if (mapFieldsIronValue[i][j] >= 100) {
						sp[1][2].setPosition(52 + (20 * tAddon) + (65 * i), 95 + (65 * j));
						window.draw(sp[1][2]);
					}
				}
			}

			//WYŒWIETLANIE ILOŒCI SUROWCÓW ETC.
			sp[5][49].setPosition(1175, 50);
			sp[5][48].setPosition(1216, 200);
			window.draw(sp[5][49]);
			window.draw(sp[5][48]);
			for (int i = 0; i < 3; i++) {
				sp[1][i].setScale(0.65, 0.65);
				sp[1][i].setPosition(1180, 60 + (45 * i));
				window.draw(sp[1][i]);
			}
			for (int i = 5; i < 8; i++)
				window.draw(txt[0][i]);
			for (int i = 0; i < 3; i++) {
				txt[0][8].setPosition(1220, 65 + (45 * i));
				window.draw(txt[0][8]);
			}
			for (int i = 9; i < 12; i++)
				window.draw(txt[0][i]);

			if (yesNoBoxActive == true) {
				if (lang == "english")
					YES_NO_BOX(L"Are you sure you want to Exit?", L"Unsaved progress will be lost!");
				if (lang == "polish")
					YES_NO_BOX(L"Na pewno chcesz opuœciæ grê?", L"Nie zapisane dane zostan¹ utracone!");
			}

			//PLACE BUILDINGS 
			if (placeBuilding == true) { PLACE_BUILDING(placeBuildingName); window.draw(txt[0][13]); }

			//NEXT TURN
			if (mouseX >= 720 && mouseX <= 765 && mouseY >= 660 && mouseY <= 705 && !placeBuilding) {
				txt[0][13].setFillColor(Color::Color(0, 100, 0, 255));
				txt[0][13].setPosition(1125, 60);			txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.09) * 1) * buildingsAmount[5])));	window.draw(txt[0][13]);
				txt[0][13].setPosition(1125, 60 + 50);		txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.06) * 1) * buildingsAmount[6])));	window.draw(txt[0][13]);
				txt[0][13].setPosition(1125, 60 + 100);		txt[0][13].setString("+" + TO_STRINGSTREAM_DOUBLE(ROUND(((playerPopulation * 0.04) * 1) * buildingsAmount[7])));	window.draw(txt[0][13]);
			}

			//NARZÊDZIA MANUALNEGO ZBIERANIA SUROWCÓW/JEDZENIA
			if (pickingMaterialsWood || pickingMaterialsStone || pickingMaterialsIron || pickingMaterialsFood) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
							sp[5][3].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][3]);
							if (pickingMaterialsFood) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(700, 15); txt[0][13].setString("+10"); window.draw(txt[0][13]);
							}
							if (pickingMaterialsWood && mapFieldsWoodValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
							if (pickingMaterialsStone && mapFieldsStoneValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60 + 50); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
							if (pickingMaterialsIron && mapFieldsIronValue[i][j] >= 1) {
								txt[0][13].setFillColor(Color::Color(0, 100, 0, 255)); txt[0][13].setPosition(1125, 60 + 100); txt[0][13].setString("+1");
								if (mapFieldsNames[i][j] == "water") txt[0][13].setString("+0.1");
								window.draw(txt[0][13]);
							}
						}
					}
				}
				if (pickingMaterialsFood) { sp[4][24].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][24]); }
				if (pickingMaterialsWood) { sp[4][25].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][25]); }
				if (pickingMaterialsStone) { sp[4][26].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][26]); }
				if (pickingMaterialsIron) { sp[4][27].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][27]); }
			}
			window.draw(txt[0][14]);

			//REMOVE, UPGRADE
			if (removingBuildings || upgradingBuildings) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
							sp[5][3].setPosition(50 + (65 * i), 50 + (65 * j));
							window.draw(sp[5][3]);
							if (upgradingBuildings) 
								if (mapFieldsBuildings[i][j] != "") 
									UPGRADE_BUILDING_COST(i, j, mapFieldsBuildings[i][j]);
						}
					}
				}
				if (removingBuildings) { sp[4][22].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][22]); }
				if (upgradingBuildings) { sp[4][23].setPosition(mouseX + 10, mouseY - 10); window.draw(sp[4][23]); }
			}

			window.display();
		}
	}
}

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
					mapFieldsStoneCapacity[i][j] = ((rand() % 50) + 75)*4;
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
					playerPopulation += 10;
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
						playerPopulation += 10;
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
						playerPopulation += 10;
						isTownHall = true;
						if (i < 9) {
							mapFieldsBuildings[i+1][j] = "storage";
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


void ADD_BUILDING(int x, int y, int id, string name) {
	if (name == "storage") {	//MAGAZYN NIE MO¯E BYC NA WODZIE LUB NA INNYM BUDYNKU \/
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodCapacity = 200 * buildingsAmount[id];
			playerStoneCapacity = 175 * buildingsAmount[id];
			playerIronCapacity = 150 * buildingsAmount[id];
			playerFoodCapacity = (1000 * buildingsAmount[id]) + 200;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "townHall") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "simpleHouse") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerPopulation += 4;
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "woodenHouse") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerPopulation += 7;
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "stoneHouse") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerPopulation += 12;
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "lumberjack") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerWoodPerTurn += ((playerPopulation * 0.09) * 1);
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "quarry") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerStonePerTurn += ((playerPopulation * 0.06) * 1);
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "mine") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerIronPerTurn += ((playerPopulation * 0.04) * 1);
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "farm") {
		if (mapFieldsNames[x][y] != "water" && mapFieldsNames[x][y] != "mountain" && mapFieldsNames[x][y] != "forest" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerFoodPerTurn += (1 * (playerPopulation * 0.1));
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
	else if (name == "fish") {
		if (mapFieldsNames[x][y] == "water" && mapFieldsBuildings[x][y] == "" && playerWoodValue >= buildingsPriceWood[id] && playerStoneValue >= buildingsPriceStone[id] && playerIronValue >= buildingsPriceIron[id]) {
			mapFieldsBuildings[x][y] = name;
			buildingsAmount[id]++;
			playerWoodValue -= buildingsPriceWood[id];
			playerStoneValue -= buildingsPriceStone[id];
			playerIronValue -= buildingsPriceIron[id];
			playerFoodPerTurn += (1.2 * (playerPopulation * 0.1));
			workField[x][y] = true;
			SET_TEXT(incode);
			NEXT_TURN();
		}
	}
}

void REMOVE_BUILDING(int x, int y, int id) {
	buildingsAmount[id]--;
	mapFieldsBuildings[x][y] = "";
	upgradeBuilding[x][y] = false;
	CHECK_STATUS_1();
	SET_TEXT(incode);
	NEXT_TURN();
}

void UPGRADE_BUILDING(int x, int y, string name) {
	if (name == "storage") {

		if (playerWoodValue >= 200 && playerStoneValue >= 200 && playerIronValue >= 125) {
			upgradeBuilding[x][y] = true;
			playerWoodValue -= 200;	playerStoneValue -= 200; playerIronValue -= 125;
		}

		NEXT_TURN();
	}
}

void UPGRADE_BUILDING_COST(int x, int y, string name) {
	if (name == "storage" && !upgradeBuilding[x][y]) {
		txt[0][13].setFillColor(Color::Red);
		txt[0][13].setPosition(1135, 60);		txt[0][13].setString("-200");		window.draw(txt[0][13]);
		txt[0][13].setPosition(1135, 60 + 50);	txt[0][13].setString("-200");		window.draw(txt[0][13]);
		txt[0][13].setPosition(1135, 60 + 100);	txt[0][13].setString("-125");		window.draw(txt[0][13]);
	}
}

void CHECK_STATUS_1() {
	playerWoodCapacity = 200 * buildingsAmount[1];
	playerStoneCapacity = 175 * buildingsAmount[1];
	playerIronCapacity = 150 * buildingsAmount[1];
	playerFoodCapacity = (1000 * buildingsAmount[1]) + 200;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (upgradeBuilding[i][j] == true) {
				if (mapFieldsBuildings[i][j] == "storage") {
					playerWoodCapacity += 500;
					playerStoneCapacity += 350;
					playerIronCapacity += 200;
					playerFoodCapacity += 800;
				}
			}
		}
	}

	if (playerWoodValue > playerWoodCapacity)	playerWoodValue = playerWoodCapacity;
	if (playerStoneValue > playerStoneCapacity)	playerStoneValue = playerStoneCapacity;
	if (playerIronValue > playerIronCapacity)	playerIronValue = playerIronCapacity;
	if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
}

void PLACE_BUILDING(string building) {
	txt[0][13].setFillColor(Color::Red);
	for (int k = 0; k < 1; k++) {
		if (building == "storage")		{ PLACE_BUILDING_MAIN(4, 38, 1); break; }
		if (building == "simpleHouse")	{ PLACE_BUILDING_MAIN(4, 30, 2); break; }
		if (building == "woodenHouse")	{ PLACE_BUILDING_MAIN(4, 31, 3); break; }
		if (building == "stoneHouse")   { PLACE_BUILDING_MAIN(4, 32, 4); break; }
		if (building == "lumberjack")	{ PLACE_BUILDING_MAIN(4, 33, 5); break; }
		if (building == "quarry")		{ PLACE_BUILDING_MAIN(4, 34, 6); break; }
		if (building == "mine")			{ PLACE_BUILDING_MAIN(4, 35, 7); break; }
		if (building == "farm")			{ PLACE_BUILDING_MAIN(4, 40, 8); break; }
		if (building == "fish")			{ PLACE_BUILDING_MAIN(4, 41, 9); break; }
	}
	/* DODAÆ DO mouseButtonPressed
	if (placeBuilding == true) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
					ADD_BUILDING(i, j, placeBuildingId, placeBuildingName);
					placeBuilding = false;
				}
			}
		}
	}
	*/
}

void PLACE_BUILDING_MAIN(int spIdX, int spIdY, int priceId) {
	sp[spIdX][spIdY].setPosition(mouseX + 10, mouseY - 10);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mouseX >= 50 + (65 * i) && mouseX <= 50 + (65 * i) + 65 && mouseY >= 50 + (65 * j) && mouseY <= 50 + (65 * j) + 65) {
				sp[5][3].setPosition(50 + (65 * i), 50 + (65 * j));
				window.draw(sp[5][3]);
			}
		}
	}
	txt[0][13].setPosition(1135, 60);		txt[0][13].setString("-" + TO_STRINGSTREAM(buildingsPriceWood[priceId]));		window.draw(txt[0][13]);
	txt[0][13].setPosition(1135, 60 + 50);	txt[0][13].setString("-" + TO_STRINGSTREAM(buildingsPriceStone[priceId]));		window.draw(txt[0][13]);
	txt[0][13].setPosition(1135, 60 + 100);	txt[0][13].setString("-" + TO_STRINGSTREAM(buildingsPriceIron[priceId]));		window.draw(txt[0][13]);
	window.draw(sp[spIdX][spIdY]);
}

void NEXT_TURN() {
	turn++;
	txt[5][10].setString(TO_STRINGSTREAM(turn));
	txt[5][10].setPosition(1225 - (txt[5][10].getLocalBounds().width / 2), 20);
//	playerWoodValue += playerWoodPerTurn;
//	playerStoneValue += playerStonePerTurn;
//	playerIronValue += playerIronPerTurn;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapFieldsBuildings[i][j] == "lumberjack") {
				if (mapFieldsWoodValue[i][j] > ((playerPopulation * 0.09) * 1)) {
					mapFieldsWoodValue[i][j] -= ((playerPopulation * 0.09) * 1);
					playerWoodValue += ((playerPopulation * 0.09) * 1);
				}
				else if (mapFieldsWoodValue[i][j] < ((playerPopulation * 0.09) * 1) && mapFieldsWoodValue > 0) {
					playerWoodValue += mapFieldsWoodValue[i][j];
					mapFieldsWoodValue[i][j] -= mapFieldsWoodValue[i][j];
				}
				if (mapFieldsWoodValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "quarry") {
				if (mapFieldsStoneValue[i][j] > ((playerPopulation * 0.06) * 1)) {
					mapFieldsStoneValue[i][j] -= ((playerPopulation * 0.06) * 1);
					playerStoneValue += ((playerPopulation * 0.06) * 1);
				}
				else if (mapFieldsWoodValue[i][j] < ((playerPopulation * 0.06) * 1) && mapFieldsWoodValue > 0) {
					playerStoneValue += mapFieldsStoneValue[i][j];
					mapFieldsStoneValue[i][j] -= mapFieldsStoneValue[i][j];
				}
				if (mapFieldsWoodValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "mine") {
				if (mapFieldsIronValue[i][j] > ((playerPopulation * 0.04) * 1)) {
					mapFieldsIronValue[i][j] -= ((playerPopulation * 0.04) * 1);
					playerIronValue += ((playerPopulation * 0.04) * 1);
				}
				else if (mapFieldsIronValue[i][j] < ((playerPopulation * 0.04) * 1) && mapFieldsIronValue > 0) {
					playerIronValue += mapFieldsIronValue[i][j];
					mapFieldsIronValue[i][j] -= mapFieldsIronValue[i][j];
				}
				if (mapFieldsWoodValue[i][j] == 0) workField[i][j] = false;
			}
			else if (mapFieldsBuildings[i][j] == "farm") {
				playerFoodValue += (1 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
			}
			else if (mapFieldsBuildings[i][j] == "fish") {
				playerFoodValue += (1.2 * (playerPopulation * 0.2));
				if (playerFoodValue > playerFoodCapacity)	playerFoodValue = playerFoodCapacity;
			}
			
		}
	}
	playerFoodValue -= (((playerPopulation * 0.1) * 10) + 1);
	for (int f = 30; f < playerPopulation; f += 30)
		playerFoodValue -= (((playerPopulation * 0.1) * 5) + 1);

	CHECK_STATUS_1();
	SET_TEXT(incode);
}

void CHECKBOX(int posX, int posY, bool argument[], wstring checkboxName, int boxesNumber, wstring box1, wstring box2, wstring box3, wstring box4, wstring box5, wstring box6) {
	txt[5][0].setString(checkboxName + ":");
	txt[5][0].setPosition(posX, posY);
	window.draw(txt[5][0]);
	for (int i = 0; i < boxesNumber; i++) {
		sp[5][0].setPosition(posX, (posY + 50) + (40 * i));
		switch (i) {
		case 0:	txt[5][i + 1].setString(box1); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 1:	txt[5][i + 1].setString(box2); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 2:	txt[5][i + 1].setString(box3); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 3:	txt[5][i + 1].setString(box4); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 4:	txt[5][i + 1].setString(box5); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		case 5:	txt[5][i + 1].setString(box6); txt[5][i + 1].setPosition(posX + 30, (posY + 47) + (40 * i)); window.draw(txt[5][i + 1]); break;
		}
		window.draw(sp[5][0]);
	}

	if (event.type == Event::MouseButtonPressed) {
		for (int i = 0; i < boxesNumber; i++) {
			if (mouseX >= posX && mouseX <= posX + 25) {
				if (mouseY >= (posY + 50) + (40 * i) && mouseY <= (posY + 50) + (40 * i) + 25) {
					if (argument[i] == false) {
						argument[i] = true;
						for (int j = 0; j < boxesNumber; j++) {
							if (j !=  i)	argument[j] = false;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < boxesNumber; i++) {
		if (argument[i] == true) {
			sp[5][1].setPosition(posX, (posY + 50) + (40 * i));
			window.draw(sp[5][1]);
			break;
		}
	}
}

string INPUT_TEXT(int posX, int posY, wstring inputTextName, string outputString) {
	txt[5][7].setString(inputTextName + ":");
	txt[5][7].setPosition(posX + 10, posY);
	window.draw(txt[5][7]);
	sp[5][2].setPosition(posX, posY + 35);
	window.draw(sp[5][2]);
	txt[5][8].setPosition(posX + 13, posY + 38);
	txt[5][8].setString(inputText);
	window.draw(txt[5][8]);
	if (event.type == Event::MouseButtonPressed) {
		if (mouseX >= posX && mouseX <= posX + 300 && mouseY >= posY + 35 && mouseY <= posY + 35 + 39) {
			if (textareaActive == false)
				textareaActive = true;
		}
		else {
			if (textareaActive == true)
				textareaActive = false;
		}
	}

	if (textareaActive == true) {
		txt[5][9].setPosition(posX + 13 + txt[5][8].getLocalBounds().width, posY + 38);
		mainTime = mainClock.getElapsedTime();
		timeSeconds = mainTime.asSeconds();
		if (timeSeconds % 2 == 0)
			window.draw(txt[5][9]);
	}

	if (event.type == Event::TextEntered && timer == 0 && textareaActive == true) {
		if (event.text.unicode == '\b' && inputText.getSize() > 0) {
			inputText.erase(inputText.getSize() - 1, 1);
			timer = 4;
		}
		else if (txt[5][8].getLocalBounds().width < 250) {
			inputText += static_cast<char>(event.text.unicode);
			timer = 4;
		}
	}
	outputString = inputText;
	if (timer > 0)
		timer--;
	else
		timer = 0;
	return outputString;
	/* DODAÆ DO window.pollEvent(event) [!] [!] [!] [!] [!] [!] [!] [!] [!] [!] [!]
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				textareaActive = false;
	*/
}

void YES_NO_BOX(wstring boxContent, wstring boxExtraContent) {
	sp[5][50].setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 100);
	window.draw(sp[5][50]);
	txt[5][50].setPosition(window.getSize().x / 2 - 120, window.getSize().y / 2 + 25);
	window.draw(txt[5][50]);
	txt[5][49].setPosition(window.getSize().x / 2 + 70, window.getSize().y / 2 + 25);
	window.draw(txt[5][49]);

	txt[5][48].setString(boxContent);
	txt[5][48].setPosition(window.getSize().x / 2 - txt[5][48].getLocalBounds().width/2, window.getSize().y / 2 - txt[5][48].getLocalBounds().height/2 - 60);
	txt[5][47].setString(boxExtraContent);
	txt[5][47].setPosition(window.getSize().x / 2 - txt[5][47].getLocalBounds().width / 2, window.getSize().y / 2 - txt[5][47].getLocalBounds().height / 2 - 10);
	window.draw(txt[5][48]);
	window.draw(txt[5][47]);

	if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169)
		txt[5][50].setFillColor(darkRed);
	else
		txt[5][50].setFillColor(Color::Black);

	if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169)
		txt[5][49].setFillColor(darkRed);
	else
		txt[5][49].setFillColor(Color::Black);

	/*	DODAÆ DO MouseButtonPressed [!] [!] [!] [!] [!] [!] [!]
	if (yesNoBoxActive == true) {
					if (mouseX >= window.getSize().x / 2 - 200 + 60 && mouseX <= window.getSize().x / 2 - 200 + 150 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						//yes...
					}
					if (mouseX >= window.getSize().x / 2 - 200 + 245 && mouseX <= window.getSize().x / 2 - 200 + 337 && mouseY >= window.getSize().y / 2 - 100 + 122 && mouseY <= window.getSize().y / 2 - 100 + 169) {
						//no...
					}
				}
	*/
}

void FIELD_ZOOM(int i, int j) {
	if (lang == "english") {
		txt[0][1].setString("Field Type: " + mapFieldsNames[i][j]);
		txt[0][2].setString("Wood: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodCapacity[i][j])));
		txt[0][3].setString("Stone: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneCapacity[i][j])));
		txt[0][4].setString("Iron: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronCapacity[i][j])));
		//Budynki \/
		if (mapFieldsBuildings[i][j] == "townHall")	txt[0][12].setString("Building: Town Hall");
		else if (mapFieldsBuildings[i][j] == "storage") txt[0][12].setString("Building: Storage");
		else if (mapFieldsBuildings[i][j] == "simpleHouse") txt[0][12].setString("Building: Simple House (4 res.)");
		else if (mapFieldsBuildings[i][j] == "woodenHouse") txt[0][12].setString("Building: Wooden House (7 res.)");
		else if (mapFieldsBuildings[i][j] == "stoneHouse") txt[0][12].setString("Building: Stone House (12 res.)");
		else if (mapFieldsBuildings[i][j] == "lumberjack") {
			if (workField[i][j]==true) txt[0][12].setString("Building: Lumberjack (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 1)) + "/t.)");
			else txt[0][12].setString("Building: Lumberjack -empty"); }
		else if (mapFieldsBuildings[i][j] == "quarry") {
			if (workField[i][j] == true) txt[0][12].setString("Building: Quarry (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 1)) + "/t.)");
			else txt[0][12].setString("Building: Quarry -empty"); }
		else if (mapFieldsBuildings[i][j] == "mine") {
			if (workField[i][j] == true) txt[0][12].setString("Building: Mine (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 1)) + "/t.)");
			else txt[0][12].setString("Building: Mine -empty"); }
		else if (mapFieldsBuildings[i][j] == "farm") txt[0][12].setString("Building: Farm (" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + "/t.)");
		else if (mapFieldsBuildings[i][j] == "fish") txt[0][12].setString("Building: Fish (" + TO_STRINGSTREAM_DOUBLE(1.2 * (playerPopulation * 0.1)) + "/t.)");
		else txt[0][12].setString("Building: None");

		if (upgradeBuilding[i][j])	txt[0][12].setString(txt[0][12].getString() + " -upgraded");
	}
	else if (lang == "polish") {
		RELOAD_LANGUAGE_STRINGS();
		txt[0][1].setString("Rodzaj Pola: " + mapFieldsNamesPol[i][j]);
		txt[0][2].setString("Drewno: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsWoodCapacity[i][j])));
		txt[0][3].setString(L"Kamieñ: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsStoneCapacity[i][j])));
		txt[0][4].setString(L"¯elazo: " + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronValue[i][j])) + "/" + TO_STRINGSTREAM_DOUBLE(ROUND(mapFieldsIronCapacity[i][j])));
		//Budynki \/
		if (mapFieldsBuildings[i][j] == "townHall")	txt[0][12].setString("Budynek: Ratusz");
		else if (mapFieldsBuildings[i][j] == "storage") txt[0][12].setString("Budynek: Magazyn");
		else if (mapFieldsBuildings[i][j] == "simpleHouse") txt[0][12].setString("Budynek: Prosty Dom (4 miesz.)");
		else if (mapFieldsBuildings[i][j] == "woodenHouse") txt[0][12].setString("Budynek: Drewniany Dom (7 miesz.)");
		else if (mapFieldsBuildings[i][j] == "stoneHouse") txt[0][12].setString("Budynek: Kamienny Dom (12 miesz.)");
		else if (mapFieldsBuildings[i][j] == "lumberjack") {
			if (workField[i][j] == true) txt[0][12].setString("Budynek: Drwal (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.09) * 1)) + "/t.)");
			else txt[0][12].setString("Bdynek: Drwal -pusty");
		}
		else if (mapFieldsBuildings[i][j] == "quarry") {
			if (workField[i][j] == true) txt[0][12].setString(L"Budynek: Kamienio³om (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.06) * 1)) + "/t.)");
			else txt[0][12].setString(L"Budynek: Kamienio³om -pusty");
		}
		else if (mapFieldsBuildings[i][j] == "mine") {
			if (workField[i][j] == true) txt[0][12].setString("Budynek: Kopalnia (" + TO_STRINGSTREAM_DOUBLE(((playerPopulation * 0.04) * 1)) + "/t.)");
			else txt[0][12].setString("Budynek: Kopalnia -pusty");
		}
		else if (mapFieldsBuildings[i][j] == "farm") txt[0][12].setString("Budynek: Farma (" + TO_STRINGSTREAM_DOUBLE(1 * (playerPopulation * 0.1)) + "/t.)");
		else if (mapFieldsBuildings[i][j] == "fish") txt[0][12].setString("Budynek: Chata Rybaka (" + TO_STRINGSTREAM_DOUBLE(1.2 * (playerPopulation * 0.1)) + "/t.)");
		else txt[0][12].setString("Budynek: Brak");

		if (upgradeBuilding[i][j])	txt[0][12].setString(txt[0][12].getString() + " -ulepszony");
	}
}

void RELOAD_LANGUAGE_STRINGS() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mapFieldsNames[i][j] == "grass") {
				mapFieldsNamesPol[i][j] = "trawa";
			}
			else if (mapFieldsNames[i][j] == "dirt") {
				mapFieldsNamesPol[i][j] = "ziemia";
			}
			else if (mapFieldsNames[i][j] == "water") {
				mapFieldsNamesPol[i][j] = "woda";
			}
			else if (mapFieldsNames[i][j] == "forest") {
				mapFieldsNamesPol[i][j] = "las";
			}
			else if (mapFieldsNames[i][j] == "mountain") {
				mapFieldsNamesPol[i][j] = "góra";
			}
		}
	}
}

void CHEATS() {
	string code = "";
	int codeInt1 = 0;
	int codeInt2 = 0;
	int codeInt3 = 0;
	cin >> code;
	if (code.find("map") != string::npos) {
		if (code.find("Generate") != string::npos)
			MAP_GENERATOR();
		else if (code.find("SetField") != string::npos) {
			cin >> code >> codeInt1 >> codeInt2;
			mapFieldsNames[codeInt1][codeInt2] = code;
		}
		else if (code.find("SetMaterials") != string::npos) {
			cin >> code >> codeInt1 >> codeInt2 >> codeInt3;
			if (code.find("Wood") != string::npos) {
				mapFieldsWoodValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsWoodCapacity[codeInt1][codeInt2] < mapFieldsWoodValue[codeInt1][codeInt2])
					mapFieldsWoodCapacity[codeInt1][codeInt2] = codeInt3;
			}
			if (code.find("Stone") != string::npos) {
				mapFieldsStoneValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsStoneCapacity[codeInt1][codeInt2] < mapFieldsStoneValue[codeInt1][codeInt2])
					mapFieldsStoneCapacity[codeInt1][codeInt2] = codeInt3;
			}
			if (code.find("Iron") != string::npos) {
				mapFieldsIronValue[codeInt1][codeInt2] = codeInt3;
				if (mapFieldsIronCapacity[codeInt1][codeInt2] < mapFieldsIronValue[codeInt1][codeInt2])
					mapFieldsIronCapacity[codeInt1][codeInt2] = codeInt3;
			}
		}
	}

	else if (code.find("return") != string::npos) {
		if (code.find("MainMenu") != string::npos)
			MAIN_MENU();
		else if (code.find("Settings") != string::npos)
			MAIN_MENU_SETTINGS();
		else if (code.find("StartGame") != string::npos)
			START_GAME();
	}

	else if (code.find("open") != string::npos) {
		if (code.find("YesNoBox") != string::npos)
			yesNoBoxActive = true;
	}

	else if (code.find("add") != string::npos) {
		cin >> code >> codeInt1;
		if (code.find("someMaterials") != string::npos) {
			playerWoodValue += codeInt1;
			playerStoneValue += codeInt1;
			playerIronValue += codeInt1;
		}
		else if (code.find("material") != string::npos) {
			if (code.find("Wood") != string::npos)
				playerWoodValue += codeInt1;
			else if (code.find("Stone") != string::npos)
				playerStoneValue += codeInt1;
			else if (code.find("Iron") != string::npos)
				playerIronValue += codeInt1;
		}
	}

	SET_TEXT(incode);

	/*	[!]
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::B) {	CHEATS();	}
	*/
}