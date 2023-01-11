
#include "ScreenHelper.h"

ScreenHelper::ScreenHelper() {

}

int ScreenHelper::getScreenWidthPixels() {
	return this->SCREEN_WIDTH_PIXELS;
}

int ScreenHelper::getScreenHeightPixels() {
	return this->SCREEN_HEIGHT_PIXELS;
}

sf::Color ScreenHelper::getPixelOnColor() {
	return this->PIXEL_ON_COLOR;
}

sf::Color ScreenHelper::getPixelOffColor() {
	return this->PIXEL_OFF_COLOR;
}

int ScreenHelper::getPixelSize() {
	return this->PIXEL_SIZE;
}


int ScreenHelper::getPixelValue(int row, int col) {
	return screen.at(row).at(col);
}

void ScreenHelper::setPixelValue(int row, int col, int newValue) {
	this->screen.at(row).at(col) = newValue;
}

void ScreenHelper::resetPixels() {
	for (int i = 0; i < this->SCREEN_HEIGHT_PIXELS; i++) {
		for (int j = 0; j < this->SCREEN_WIDTH_PIXELS; j++) {
			this->screen.at(i).at(j) = 0;
		}
	}
}