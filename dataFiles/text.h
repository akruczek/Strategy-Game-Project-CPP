#ifndef text_h
#define text_h

#include "library.h"
using namespace std;
using namespace sf;

Text txt[51][51];
string lang = "english";

void SET_TEXT(string incode) {	//USTAWIANIE STRINGÓW DLA TEKSTU
	for (int i = 0; i < 51; i++) {	//STANDARDOWE USTAWIENIA TEKSTU
		for (int j = 0; j < 51; j++) {
			txt[i][j].setFont(fontAmitaRegular);
			txt[i][j].setFillColor(Color::Black);
			txt[i][j].setCharacterSize(16);
			txt[i][j].setPosition(640 - (txt[i][j].getLocalBounds().width / 2), (320) - (txt[i][j].getLocalBounds().height / 2));
			txt[i][j].setOutlineThickness(0);
			txt[i][j].setStyle(Text::Regular);
		}
	}

	if (incode == "mainMenu") {	//MENU G£ÓWNE
		if (lang == "english") {
			txt[0][0].setString("New Game");
			txt[0][1].setString("Load Game");
			txt[0][2].setString("Settings");
			txt[0][3].setString("Exit");
		}
		if (lang == "polish") {
			txt[0][0].setString("Nowa Gra");
			txt[0][1].setString(L"Wczytaj Grê");
			txt[0][2].setString("Ustawienia");
			txt[0][3].setString(L"Wyjœcie");
		}
		for (int i = 0; i < 4; i++) {
			txt[0][i].setCharacterSize(48);
			txt[0][i].setPosition((640 - (txt[0][i].getLocalBounds().width / 2) - 10), 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i));
		}
	}
	
	if (incode == "mainMenuSettings") {	//MENU G£ÓWNE - USTAWIENIA
		if (lang == "english") {
			txt[0][0].setString("Language");
			txt[0][1].setString("FullScreen");
			txt[0][2].setString("Antialiasing");
			txt[0][3].setString("Return");
			txt[0][4].setString("English");
			if (fullscreenMode == false)
				txt[0][5].setString("Off");
			else
				txt[0][5].setString("On");
			if (antialiasing == false)
				txt[0][6].setString("Off");
			else
				txt[0][6].setString("On");
		}
		if (lang == "polish") {
			txt[0][0].setString(L"Jêzyk: Polski");
			txt[0][1].setString(L"Pe³ny Ekran");
			txt[0][2].setString("Antyaliasing");
			txt[0][3].setString(L"Powrót");
			txt[0][4].setString("Polski");
			if (fullscreenMode == false)
				txt[0][5].setString(L"Wy³.");
			else
				txt[0][5].setString(L"W³.");
			if (antialiasing == false)
				txt[0][6].setString(L"Wy³.");
			else
				txt[0][6].setString(L"W³.");
		}
		for (int i = 0; i < 4; i++) {
			txt[0][i].setCharacterSize(40);
			txt[0][i].setPosition((640 - (txt[0][i].getLocalBounds().width / 2) - 10), 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i));
		}
		for (int i = 4; i < 7; i++) {
			txt[0][i].setCharacterSize(24);
			txt[0][i].setPosition((640 - (txt[0][i].getLocalBounds().width / 2) - 10), 190 - (txt[0][i].getLocalBounds().height / 2) + (80 * (i-4)));
		}
	}

	if (incode == "mainMenuLoadGame") {	//MENU G£ÓWNE - USTAWIENIA
		if (lang == "english") {
			txt[0][0].setString("Slot 1");
			txt[0][1].setString("Slot 2");
			txt[0][2].setString("Slot 3");
			txt[0][3].setString("Return");
			if (save1 == false)
				txt[0][4].setString("Empty");
			else
				txt[0][4].setString("Saved");	//dalsze instrukcje
			if (save2 == false)
				txt[0][5].setString("Empty");
			else
				txt[0][5].setString("Saved");	//dalsze instrukcje
			if (save3 == false)
				txt[0][6].setString("Empty");
			else
				txt[0][6].setString("Saved");	//dalsze instrukcje
		}
		if (lang == "polish") {
			txt[0][0].setString("Slot 1");
			txt[0][1].setString("Slot 2");
			txt[0][2].setString("Slot 3");
			txt[0][3].setString("Return");
			if (save1 == false)
				txt[0][4].setString("Pusty");
			else
				txt[0][4].setString("Zapisany");	//dalsze instrukcje
			if (save2 == false)
				txt[0][5].setString("Pusty");
			else
				txt[0][5].setString("Zapisany");	//dalsze instrukcje
			if (save3 == false)
				txt[0][6].setString("Pusty");
			else
				txt[0][6].setString("Zapisany");	//dalsze instrukcje
		}
		for (int i = 0; i < 4; i++) {
			txt[0][i].setCharacterSize(40);
			txt[0][i].setPosition((640 - (txt[0][i].getLocalBounds().width / 2) - 10), 150 - (txt[0][i].getLocalBounds().height / 2) + (80 * i));
		}
		for (int i = 4; i < 7; i++) {
			txt[0][i].setCharacterSize(24);
			txt[0][i].setPosition((640 - (txt[0][i].getLocalBounds().width / 2) - 10), 190 - (txt[0][i].getLocalBounds().height / 2) + (80 * (i - 4)));
		}
	}

	if (incode == "mainMenuNewGame") {	//MENU G£ÓWNE - NOWA GRA
		if (lang == "english") {
			txt[0][0].setString("Return");
			txt[0][1].setString("Start");
		}
		if (lang == "polish") {
			txt[0][0].setString(L"Powrót");
			txt[0][1].setString("Rozpocznij");
		}
		for (int i = 0; i < 2; i++) {
			txt[0][i].setCharacterSize(32);
			txt[0][i].setPosition((633 - (txt[0][i].getLocalBounds().width / 2) - 10), 450 - (txt[0][i].getLocalBounds().height / 2) - (i*50));
		}
	}
	if (incode == "startGame") {	//START GAME
		if (lang == "english") {
			txt[0][1].setString("Field Type: ");
			txt[0][2].setString("Wood: ");
			txt[0][3].setString("Stone: ");
			txt[0][4].setString("Iron: ");
			txt[0][12].setString("Building: ");
			txt[0][15].setString("Food:");
		}
		if (lang == "polish") {
			txt[0][1].setString("Rodzaj Pola: ");
			txt[0][2].setString("Drewno: ");
			txt[0][3].setString(L"Kamieñ: ");
			txt[0][4].setString(L"¯elazo: ");
			txt[0][12].setString(L"Budynek: ");
			txt[0][15].setString("Jedzenie:");
		}
		txt[0][0].setString(mapName);
		txt[0][0].setPosition(710, 52);
		txt[0][0].setCharacterSize(32);
		txt[0][0].setOutlineThickness(1);
		txt[0][0].setOutlineColor(Color::White);
		for (int i = 1; i < 5; i++) {
			txt[0][i].setCharacterSize(16);
			txt[0][i].setStyle(Text::Bold);
			txt[0][i].setPosition(760, 100 + ((i - 1) * 20));
		}
		txt[0][5].setString(TO_STRINGSTREAM(ROUND(playerWoodValue)));
		txt[0][6].setString(TO_STRINGSTREAM(ROUND(playerStoneValue)));
		txt[0][7].setString(TO_STRINGSTREAM(ROUND(playerIronValue)));
		for (int i = 5; i < 8; i++)
			txt[0][i].setPosition(1240 - (txt[0][i].getLocalBounds().width / 2), 55 + (45 * (i-5)));
		txt[0][8].setString("-----");
		txt[0][9].setString(TO_STRINGSTREAM(ROUND(playerWoodCapacity)));
		txt[0][10].setString(TO_STRINGSTREAM(ROUND(playerStoneCapacity)));
		txt[0][11].setString(TO_STRINGSTREAM(ROUND(playerIronCapacity)));
		for (int i = 9; i < 12; i++) {
			txt[0][i].setPosition(1240 - (txt[0][i].getLocalBounds().width / 2), 75 + (45 * (i - 9)));
			txt[0][i].setFillColor(Color::Color(153, 0, 0, 100));
		}
		txt[0][12].setPosition(760, 180);
		txt[0][12].setCharacterSize(16);
		txt[0][12].setStyle(Text::Bold);
		txt[0][13].setString("Price Building");
		txt[0][14].setString("Population");	txt[0][14].setString(TO_STRINGSTREAM(playerPopulation));
		txt[0][14].setPosition(1244 - (txt[0][14].getLocalBounds().width/2), 205);
		txt[0][15].setCharacterSize(28);
		txt[0][15].setFillColor(Color::White);
		txt[0][15].setPosition(445 - txt[0][15].getLocalBounds().width, 10);
		txt[0][16].setString("FoodValuePercent");
		txt[0][16].setFillColor(Color::Black);
		txt[0][16].setOutlineColor(Color::White);
		txt[0][16].setOutlineThickness(2);
		txt[0][17].setString(TO_STRINGSTREAM(playerFoodValue));
		txt[0][17].setPosition(669 - txt[0][17].getLocalBounds().width / 2, 7);
		txt[0][17].setCharacterSize(14);
	}

	//TEKST STATYCZNY |\/|
	txt[5][0].setString("checkboxName");										txt[5][0].setCharacterSize(28);	//CHECKBOX NAME
	txt[5][1].setString("box1");												txt[5][1].setCharacterSize(20);	//CHECHBOX VALUES |\/|
	txt[5][2].setString("box2");												txt[5][2].setCharacterSize(20);
	txt[5][3].setString("box3");												txt[5][3].setCharacterSize(20);
	txt[5][4].setString("box4");												txt[5][4].setCharacterSize(20);
	txt[5][5].setString("box5");												txt[5][5].setCharacterSize(20);
	txt[5][6].setString("box6");												txt[5][6].setCharacterSize(20);	//CHECHBOX VALUES |/\|
	txt[5][7].setString("inputTextName");										txt[5][7].setCharacterSize(28);	//INPUT-TEXT NAME
	txt[5][8].setString("");													txt[5][8].setCharacterSize(24);	//INPUT-TEXT VALUE
	txt[5][9].setString("|");													txt[5][9].setCharacterSize(24);	//MRUGAJ¥CY PIPE
	txt[5][50].setString("Yes");												txt[5][50].setCharacterSize(32);
	txt[5][49].setString("No");													txt[5][49].setCharacterSize(32);
	txt[5][48].setString("yesNoContent");										txt[5][48].setCharacterSize(24);
	txt[5][47].setString("yesNoContent2");										txt[5][47].setCharacterSize(20);
	txt[5][10].setString(TO_STRINGSTREAM(turn));								txt[5][10].setCharacterSize(24);	//TURA
	txt[5][10].setPosition(1225 - (txt[5][10].getLocalBounds().width / 2), 20);	txt[5][10].setOutlineThickness(3);
	txt[5][10].setFillColor(Color::Black);										txt[5][10].setOutlineColor(darkRed);
}

#endif