#include "GraphicsHelper.h"

void GraphicsHelper::draw() {
	this->window->clear();

	for (int i = 0; i < this->screen->getScreenWidthPixels(); i++) {
		for (int j = 0; j < this->screen->getScreenHeightPixels(); j++) {
			float pixelSize = this->screen->getPixelSize();
			sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));

			if (this->screen->getPixelValue(j, i) == 0) {
				pixel.setFillColor(this->screen->getPixelOffColor());
			} else {
				pixel.setFillColor(this->screen->getPixelOnColor());
			}

			pixel.setPosition(pixelSize * i, pixelSize * j);

			this->window->draw(pixel);
		}
	}

	this->window->display();
}

bool GraphicsHelper::isWindowOpen() {
	return this->window->isOpen();
}

void GraphicsHelper::pollEvent() {
	sf::Event event;

	while (this->window->pollEvent(event)) {
		if (event.type = sf::Event::Closed) {
			this->window->close();
		}
	}
}

ScreenHelper* GraphicsHelper::getScreen() {
	return this->screen;
}