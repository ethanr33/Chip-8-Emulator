#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class InputHelper {
	private:
		std::vector<sf::Keyboard::Key> keyMap = {
			sf::Keyboard::Num1,
			sf::Keyboard::Num2,
			sf::Keyboard::Num3,
			sf::Keyboard::Num4,
			sf::Keyboard::Q,
			sf::Keyboard::W,
			sf::Keyboard::E,
			sf::Keyboard::R,
			sf::Keyboard::A,
			sf::Keyboard::S,
			sf::Keyboard::D,
			sf::Keyboard::F,
			sf::Keyboard::Z,
			sf::Keyboard::X,
			sf::Keyboard::C,
			sf::Keyboard::V
		};

	public:
		bool isKeyPressed(char keyCode);
		char waitForKeyPress();
};