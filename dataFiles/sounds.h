#ifndef sounds_h
#define sounds_h

#include "library.h"

sf::SoundBuffer bufferKlick;
sf::Sound soundKlick;

void LOAD_SOUNDS() {
	bufferKlick.loadFromFile("data/sounds/klick.wav");	//nowy dŸwiêk, œcie¿ka, link
	soundKlick.setBuffer(bufferKlick);
}

void KLICK(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		soundKlick.play();
	}
}

#endif