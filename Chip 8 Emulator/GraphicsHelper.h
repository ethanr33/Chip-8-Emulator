#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ScreenHelper.h"

class GraphicsHelper {
	private:
		//ScreenHelper object to manage screen pixels
		ScreenHelper* screen = new ScreenHelper();

		//Title of window to hold emulator in
		std::string WINDOW_TITLE = "Chip 8 Emulator";

		//Width of emulator window
		const int WINDOW_WIDTH = screen->getScreenWidthPixels() * screen->getPixelSize();
		const int WINDOW_HEIGHT = screen->getScreenHeightPixels() * screen->getPixelSize();
		
		//Object to render window
		sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	public:
		void draw();
		bool isWindowOpen();
		void pollEvent();
		ScreenHelper* getScreen();
};