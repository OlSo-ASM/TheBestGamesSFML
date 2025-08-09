#include "Game.h"
#include <string>
using namespace sf;

void mainMenuState::init(sf::RenderWindow* win) {

	menuBackGround.setSize((Vector2f)win->getSize());
	menuBackGround.setFillColor(Color(107, 107, 107));
	menuBackGround.setPosition(Vector2f(0, 0));
	
	this->win = win;

	int bias = 0;
	for (size_t i = 0; i < NUM_GAMES; ++i) {
		if ((i>0)&&!(i % 11))
			bias += 200;
		icons.push_back(new Texture(("icons/icon"+std::to_string(i)+".png")));
		buttons.push_back(new imageButton(Vector2f(7.5+37.5 + 100 * (int)i - (int)(i / 4) * 400, 2.5 + 25 + 100 * (int)(i / 4) - bias), Vector2f(100, 100), *icons[i]));
	}
	numOfSlide = 0;
}

void mainMenuState::update(Game* game) {
	if (win->getSize() != Vector2u(715, 455))
		win->setSize(Vector2u(715, 455));
	if (buttons[0]->isClickedLeft())
	{
		buttons[0]->dropClick();
		game->pushState(new sapperMenuState());
	}
}

void mainMenuState::render(sf::RenderWindow* win) {
	win->draw(menuBackGround);
	for (size_t i = numOfSlide*12; i < numOfSlide*12+12; ++i) {
		if (i >= buttons.size())
			break;
		buttons[i]->draw(win);
	}
}

void mainMenuState::handleInput(const std::optional<sf::Event>& event) {
	for (size_t i = numOfSlide * 12; i < numOfSlide * 12 + 12; ++i) {
		if (i >= buttons.size())
			break;
		buttons[i]->clickHandle(win, event);
		
	}
}

void mainMenuState::clean() {

}
