#ifndef textures_h
#define textures_h

#include "library.h"
using namespace std;
using namespace sf;

Texture tex[51][51];	//TABLICA TEKSTUR
Sprite sp[51][51];		//TABLICA SPRITE'ÓW

void SET_ANTIALIASING() {
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			tex[i][j].setSmooth(antialiasing);
		}
	}
}

void LOAD_TEXTURES(string incode) {	//£ADOWANIE TEKSTUR
	if (incode == "mainMenu") {																//[!]MENU G£ÓWNE[!]
		tex[0][0].loadFromFile("data/graphics/backgrounds/mainMenu-background.png");		//T£O
		tex[0][1].loadFromFile("data/graphics/backgrounds/mainMenu-mainFrame.png");			//RAMKA G£ÓWNA
	}
	if (incode == "startGame") {															//[!]START GAME[!]
		tex[0][0].loadFromFile("data/graphics/backgrounds/startGame-background.png");		//T£O
		tex[0][1].loadFromFile("data/graphics/icons/iconField.png");						//T£O DLA IKON
	}

	//TEKSTURY STATYCZNE |\/|
	tex[5][0].loadFromFile("data/graphics/form/checkbox.png");								//CHECKBOX
	tex[5][1].loadFromFile("data/graphics/form/checkboxBird.png");							//CHECKBOX - PTASZEK
	tex[5][2].loadFromFile("data/graphics/form/inputText.png");								//INPUT-TEXT
	tex[5][45].loadFromFile("data/graphics/backgrounds/startGame-moreMaterials.png");		//MORE MATERIALS
	tex[5][46].loadFromFile("data/graphics/backgrounds/startGame-moreFood.png");			//MORE FOOD
	tex[5][47].loadFromFile("data/graphics/backgrounds/startGame-food.png");				//FOOD
	tex[5][48].loadFromFile("data/graphics/backgrounds/startGame-population.png");			//POPULACJA
	tex[5][49].loadFromFile("data/graphics/backgrounds/startGame-materialsFrame.png");		//MATERIALS FRAME
	tex[5][50].loadFromFile("data/graphics/form/yesNoBox.png");								//YES_NO BOX

	tex[5][3].loadFromFile("data/graphics/mapModel/mapFogField.png");						//MG£A - MAPA
	//tex[5][4].loadFromFile("data/graphics/mapModel/mapStandardField.png");				//POLE JEDNOSTKOWE - MAPA
	tex[5][5].loadFromFile("data/graphics/mapModel/mapGrassField.png");						//MAPA-POLE -GRASS
	tex[5][6].loadFromFile("data/graphics/mapModel/mapDirtField.png");						//MAPA-POLE -DIRT
	tex[5][7].loadFromFile("data/graphics/mapModel/mapWaterField.png");						//MAPA-POLE -WATER
	tex[5][8].loadFromFile("data/graphics/mapModel/mapForestField.png");					//MAPA-POLE -FOREST
	tex[5][9].loadFromFile("data/graphics/mapModel/mapMountainField.png");					//MAPA-POLE -MOUNTAIN
	tex[4][0].loadFromFile("data/graphics/textures/grassTexture.png");						//MAPA-POLE ZBLI¯ENIE -GRASS, sp[4][0] - SPRITE DYNAMICZNY (tekstura)
	tex[4][1].loadFromFile("data/graphics/textures/dirtTexture.png");						//MAPA-POLE ZBLI¯ENIE -DIRT
	tex[4][2].loadFromFile("data/graphics/textures/waterTexture.png");						//MAPA-POLE ZBLI¯ENIE -WATER
	tex[4][3].loadFromFile("data/graphics/textures/forestTexture.png");						//MAPA-POLE ZBLI¯ENIE -FOREST
	tex[4][4].loadFromFile("data/graphics/textures/mountainTexture.png");					//MAPA-POLE ZBLI¯ENIE -MOUNTAIN
	tex[4][5].loadFromFile("data/graphics/backgrounds/startGame-bar.png");					//BAR
	tex[4][6].loadFromFile("data/graphics/backgrounds/startGame-barOne.png");				//BAR - ONE						

	tex[4][20].loadFromFile("data/graphics/icons/iconNextTurn.png");						//NEXT TURN
	tex[4][21].loadFromFile("data/graphics/icons/<>.png");	
	tex[4][22].loadFromFile("data/graphics/icons/iconRemove.png");							//REMOVE
	tex[4][23].loadFromFile("data/graphics/icons/iconUpgrade.png");							//UPGRADE
	tex[4][24].loadFromFile("data/graphics/icons/iconShovel.png");							//£OPATA
	tex[4][25].loadFromFile("data/graphics/icons/iconAxe.png");								//SIEKIERA
	tex[4][26].loadFromFile("data/graphics/icons/iconHammer.png");							//M£OT
	tex[4][27].loadFromFile("data/graphics/icons/iconPickaxe.png");							//KILOF
	tex[4][28].loadFromFile("data/graphics/icons/iconInfo.png");							//INFO
	tex[4][29].loadFromFile("data/graphics/icons/iconExit.png");							//EXIT

	tex[4][30].loadFromFile("data/graphics/icons/iconSimpleHouse.png");						//PROSTY DOM
	tex[4][31].loadFromFile("data/graphics/icons/iconWoodenHouse.png");						//DREWNIANY DOM
	tex[4][32].loadFromFile("data/graphics/icons/iconStoneHouse.png");						//KAMIENNY DOM
	tex[4][33].loadFromFile("data/graphics/icons/iconLumberjack.png");						//DRWAL
	tex[4][34].loadFromFile("data/graphics/icons/iconQuarry.png");							//KAMIENIO£OM
	tex[4][35].loadFromFile("data/graphics/icons/iconMine.png");							//KOPALNIA
	tex[4][36].loadFromFile("data/graphics/icons/<>.png");
	tex[4][37].loadFromFile("data/graphics/icons/<>.png");
	tex[4][38].loadFromFile("data/graphics/icons/iconBuildingStorage.png");					//MAGAZYN
	tex[4][39].loadFromFile("data/graphics/icons/iconBuildingTownHall.png");				//RATUSZ

	tex[4][40].loadFromFile("data/graphics/icons/iconFarm.png");							//FARMA
	tex[4][41].loadFromFile("data/graphics/icons/iconFish.png");							//FISH
	tex[4][42].loadFromFile("data/graphics/icons/iconHunting.png");							//HUNTING
	tex[4][43].loadFromFile("data/graphics/icons/iconGather.png");							//GATHER
	tex[4][44].loadFromFile("data/graphics/icons/iconWindmill.png");						//M£YN
	tex[4][45].loadFromFile("data/graphics/icons/<>.png");
	tex[4][46].loadFromFile("data/graphics/icons/<>.png");
	tex[4][47].loadFromFile("data/graphics/icons/<>.png");
	tex[4][48].loadFromFile("data/graphics/icons/<>.png");
	tex[4][49].loadFromFile("data/graphics/icons/<>.png");

	tex[1][0].loadFromFile("data/graphics/icons/iconWood.png");								//IKONA - DREWNO
	tex[1][1].loadFromFile("data/graphics/icons/iconStone.png");							//IKONA - KAMIEÑ
	tex[1][2].loadFromFile("data/graphics/icons/iconIron.png");								//IKONA - METAL
	tex[1][3].loadFromFile("data/graphics/icons/iconUpgradeBuilding.png");					//UPGRADE BUILDING
	tex[1][4].loadFromFile("data/graphics/icons/iconMoreButton.png");						//MORE BUTTON

	tex[2][0].loadFromFile("data/graphics/icons/more/iconMoreWheat.png");					//iconMore WHEAT			
	tex[2][1].loadFromFile("data/graphics/icons/more/iconMoreFish.png");					//iconMore FISH			
	tex[2][2].loadFromFile("data/graphics/icons/more/iconMoreMeat.png");					//iconMore MEAT			
	tex[2][3].loadFromFile("data/graphics/icons/more/iconMoreHerb.png");					//iconMore HERB
	tex[2][4].loadFromFile("data/graphics/icons/more/iconMoreForestFruit.png");				//iconMore FOREST FRUIT	
	tex[2][5].loadFromFile("data/graphics/icons/more/iconMoreFlour.png");					//iconMore FLOUR
	tex[2][49].loadFromFile("data/graphics/icons/more/iconMoreNo.png");						//iconMore NO
	tex[2][50].loadFromFile("data/graphics/icons/more/iconMoreYes.png");					//iconMore YES


}

void LOAD_SPRITE() {
	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			sp[i][j].setTexture(tex[i][j]);
		}
	}
}

void SET_SPRITE(string incode) {
	if (incode == "mainMenu") {
		sp[0][0].setPosition(0, 0);
		sp[0][1].setPosition(440, 50);
	}
	if (incode == "startGame") {
		sp[0][0].setPosition(0, 0);
		sp[4][0].setPosition(700, 47);
		sp[0][1].setPosition(710, 650);
	}
}

#endif
