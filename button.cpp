#include "Game.h"
#include <iostream>

using namespace sf;

button::button(sf::Vector2f position, sf::Vector2f size, std::string titleText, sf::Font font):title(font) {
	buttonFont = font;
	title.setFont(buttonFont);
	clickFlagLeft = false;
	clickFlagRight = false;
	buttonShape.setPosition(position);
	buttonShape.setSize(size);
	this->title.setString(titleText);
	
	sf::FloatRect textRect = this->title.getLocalBounds();
	this->title.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f));

	sf::Vector2f buttonCenter = buttonShape.getPosition() + buttonShape.getSize() / 2.0f;
	this->title.setPosition(buttonCenter);

}
button::~button() {};
bool button::isMouseOver(sf::RenderWindow* win) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
	sf::Vector2f mouseWorldPos = win->mapPixelToCoords(mousePos);
	return buttonShape.getGlobalBounds().contains(mouseWorldPos);
}

void button::clickHandle(sf::RenderWindow* win, const std::optional<sf::Event>& event) {
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

void button::setColor(sf::Color color) {
	buttonShape.setFillColor(color);
}
void button::setPosition(sf::Vector2f newPos) {
	buttonShape.setPosition(newPos);
	sf::FloatRect textRect = this->title.getLocalBounds();
	this->title.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f));

	sf::Vector2f buttonCenter = buttonShape.getPosition() + buttonShape.getSize() / 2.0f;
	this->title.setPosition(buttonCenter);

}
void button::setSize(sf::Vector2f newSize) {
	buttonShape.setSize(newSize);
	sf::FloatRect textRect = this->title.getLocalBounds();
	this->title.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f));

	sf::Vector2f buttonCenter = buttonShape.getPosition() + buttonShape.getSize() / 2.0f;
	this->title.setPosition(buttonCenter);
}
void button::draw(sf::RenderWindow* win) {
	win->draw(buttonShape);
	win->draw(title);
}
bool button::isClickedLeft() {
	return clickFlagLeft;
}
bool button::isClickedRight() {
	return clickFlagRight;
}
void button::dropClick() {
	clickFlagLeft = 0;
	clickFlagRight = 0;
}

void button::setText(std::string text) {
	title.setString(text);
	sf::FloatRect textRect = this->title.getLocalBounds();
	this->title.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f));

	sf::Vector2f buttonCenter = buttonShape.getPosition() + buttonShape.getSize() / 2.0f;
	this->title.setPosition(buttonCenter);
}