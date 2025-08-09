#include "Game.h"
using namespace sf;

void sapperMenuState::init(sf::RenderWindow* win){
	difficults[0] = "Easy";
	difficults[1] = "Normal";
	difficults[2] = "Hard";
	numOfDifficult = 0;
	win->setSize(Vector2u(715, 455));
	menuBackGround.setSize((Vector2f)win->getSize());
	menuBackGround.setFillColor(Color(107, 107, 107));
	menuBackGround.setPosition(Vector2f(0, 0));
	Font font("Fonts/sapperFont/sapperFont.ttf");
	buttonStart = new button(Vector2f(237.5, 62.5), Vector2f(240, 70), "Start", font);
	buttonStart->setColor(Color(137, 137, 137));
	buttonDifficult = new button(Vector2f(237.5, 192.5), Vector2f(240, 70), "Easy", font);
	buttonDifficult->setColor(Color(137, 137, 137));
	buttonBack = new button(Vector2f(237.5, 322.5), Vector2f(240, 70), "Back", font);
	buttonBack->setColor(Color(137, 137, 137));

	this->win = win;
}
void sapperMenuState::handleInput(const std::optional<sf::Event>& event){
	buttonStart->clickHandle(win,event);
	buttonDifficult->clickHandle(win, event);
	buttonBack->clickHandle(win, event);
}
void sapperMenuState::update(Game* game){
	if(win->getSize()!=Vector2u(715,455))
		win->setSize(Vector2u(715, 455));
	if (buttonStart->isClickedLeft()) {
		buttonStart->dropClick();
		game->pushState(new sapperGame(numOfDifficult));
	}
	else if (buttonDifficult->isClickedLeft()) {
		if (numOfDifficult == 2) {
			numOfDifficult = 0;
		}
		else
			++numOfDifficult;
		buttonDifficult->setText(difficults[numOfDifficult]);
		buttonDifficult->dropClick();
	}
	else if (buttonBack->isClickedLeft()) {
		game->popState();
	}
}
void sapperMenuState::render(sf::RenderWindow* win){
	win->draw(menuBackGround);
	buttonStart->draw(win);
	buttonDifficult->draw(win);
	buttonBack->draw(win);
}
void sapperMenuState::clean(){
	delete buttonStart;
	delete buttonDifficult;
	delete buttonBack;
}