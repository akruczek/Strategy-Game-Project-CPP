#include "myFunctions.h"

std::string TO_STRINGSTREAM(int value) {
	std::ostringstream oss;
	std::string return_value;
	oss << value;
	return oss.str();
}

std::string TO_STRINGSTREAM_DOUBLE(double value) {
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << std::setprecision(std::numeric_limits<double>::digits10) << value;
	return ss.str();
}

void INFO(sf::Event event) {
	if (event.type == sf::Event::MouseMoved) {
		std::cout << "mouse-X: " << event.mouseMove.x << std::endl;
		std::cout << "mouse-Y: " << event.mouseMove.y << std::endl;
	}
}

double ROUND(double value) {
	return round(value * 100) / 100;
}
