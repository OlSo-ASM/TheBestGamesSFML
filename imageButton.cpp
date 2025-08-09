#include "Game.h"

imageButton::imageButton(sf::Vector2f position, sf::Vector2f size, const sf::Texture& tex): buttonSprite(tex){
	clickFlagLeft = false;
	clickFlagRight = false;
	float scaleX, scaleY;
	buttonSprite.setTexture(tex);
	scaleX = size.x / tex.getSize().x;
	scaleY = size.y / tex.getSize().y;
	buttonSprite.setScale(sf::Vector2f(scaleX, scaleY));
	buttonSprite.setPosition(position);
}
void imageButton::setTexture(const sf::Texture& newTex) {
	buttonSprite.setTexture(newTex);
}
void imageButton::draw(sf::RenderWindow* win) {
	win->draw(buttonSprite);
}

bool imageButton::isMouseOver(sf::RenderWindow* win) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
	sf::Vector2f mouseWorldPos = win->mapPixelToCoords(mousePos);
	return buttonSprite.getGlobalBounds().contains(mouseWorldPos);
}

void imageButton::clickHandle(sf::RenderWindow* win, const std::optional<sf::Event>& event) {
	if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseButtonPressed->button == sf::Mouse::Button::Left)
		{
			clickFlagLeft = isMouseOver(win);
		}
		if (mouseButtonPressed->button == sf::Mouse::Button::Right)
		{
			clickFlagRight = isMouseOver(win);
		}
	}
	if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
	{
		if (mouseButtonReleased->button == sf::Mouse::Button::Left)
		{
			clickFlagLeft = 0;
		}
		if (mouseButtonReleased->button == sf::Mouse::Button::Right)
		{
			clickFlagRight = 0;
		}
	}
}
bool imageButton::isClickedLeft() {
	return clickFlagLeft;
}
bool imageButton::isClickedRight() {
	return clickFlagRight;
}
void imageButton::dropClick() {
	clickFlagLeft = 0;
	clickFlagRight = 0;
}
imageButton::~imageButton() {};