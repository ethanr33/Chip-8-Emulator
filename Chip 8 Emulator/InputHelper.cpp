#include "InputHelper.h"

bool InputHelper::isKeyPressed(char keyCode) {
	return sf::Keyboard::isKeyPressed(this->keyMap.at(keyCode));
}