#ifndef fonts_h
#define fonts_h

#include "library.h"

sf::Font fontAmitaRegular;

void LOAD_FONTS() {
	fontAmitaRegular.loadFromFile("data/fonts/Amita-Bold.ttf");
	// https://fonts.google.com/specimen/Amita?selection.family=Amita
}

#endif