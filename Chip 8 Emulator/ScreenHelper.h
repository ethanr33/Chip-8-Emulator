#pragma once

#include <vector>
#include <exception>
#include <SFML/Graphics.hpp>

class ScreenHelper {
	private:
		const int SCREEN_WIDTH_PIXELS = 64;
		const int SCREEN_HEIGHT_PIXELS = 32;
		//Size of emulated pixel displayed on screen
		const int PIXEL_SIZE = 10;
		//PIXEL_ON_COLOR: Color of pixel on screen when set to be on.
		const sf::Color PIXEL_ON_COLOR = sf::Color::White;
		//PIXEL_OFF_COLOR: Color of pixel on screen when set to be off.
		const sf::Color PIXEL_OFF_COLOR = sf::Color::Black;
		/*
			if screen[i][j] is 1, then the pixel is set to PIXEL_COLOR.
			if screen[i][j] is 0, then the pixel is set to black.
		*/
		std::vector<std::vector<int>> screen = std::vector<std::vector<int>>(SCREEN_HEIGHT_PIXELS, std::vector<int>(SCREEN_WIDTH_PIXELS, 0));
	public:
		ScreenHelper();
		int getScreenWidthPixels();
		int getScreenHeightPixels();
		int getPixelSize();
		sf::Color getPixelOnColor();
		sf::Color getPixelOffColor();
		int getPixelValue(int row, int col);
		void setPixelValue(int row, int col, int newValue);
		void resetPixels();
};