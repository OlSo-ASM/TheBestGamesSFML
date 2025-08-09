#include "Game.h"

using namespace sf;
sapperPauseMenu::sapperPauseMenu(std::function<void(sf::RenderWindow*)> renderFunc, int* gameFlag) {
	this->renderFunc = renderFunc;
	this->gameFlag = gameFlag;
}
sapperPauseMenu::~sapperPauseMenu() {
	
}
void sapperPauseMenu::init(RenderWindow* win) {
	this->win = win;
	Vector2f sizeOfMenu, menuBias;
	sizeOfMenu.x = win->getSize().y * 0.6;
	sizeOfMenu.y = win->getSize().y * 0.75;
	menuBias.x = win->getSize().x/2 -sizeOfMenu.x/2;
	menuBias.y = win->getSize().y/2 - sizeOfMenu.y/2;
	menuBackGround.setSize(sizeOfMenu);
	menuBackGround.setFillColor(Color(107, 107, 107));
	menuBackGround.setPosition(menuBias);
	background.setSize((Vector2f)win->getSize());
	background.setPosition(Vector2f(0, 0));
	background.setFillColor(Color(255, 255, 255, 170));
	Font font("Fonts/sapperFont/sapperFont.ttf");
	buttonRestart = new button(Vector2f(win->getSize().x/2 - menuBackGround.getSize().x * 0.84 / 2,
		menuBackGround.getSize().y/6*1+menuBackGround.getPosition().y- menuBackGround.getSize().x * 0.75 / 3/2),
		Vector2f(menuBackGround.getSize().x*0.84, menuBackGround.getSize().x * 0.75/3), "Restart", font);
	buttonRestart->setColor(Color(137, 137, 137));
	buttonBack = new button(Vector2f(win->getSize().x / 2 - menuBackGround.getSize().x * 0.84/2, 
		menuBackGround.getSize().y / 6 * 3 + menuBackGround.getPosition().y - menuBackGround.getSize().x * 0.75 / 3/2),
		Vector2f(menuBackGround.getSize().x * 0.84, menuBackGround.getSize().x * 0.75 / 3), "Back", font);
	buttonBack->setColor(Color(137, 137, 137));
	buttonOut = new button(Vector2f(win->getSize().x / 2 - menuBackGround.getSize().x * 0.84/2, 
		menuBackGround.getSize().y / 6 * 5 + menuBackGround.getPosition().y - menuBackGround.getSize().x * 0.75 / 3/2),
		Vector2f(menuBackGround.getSize().x * 0.84, menuBackGround.getSize().x * 0.75 / 3), "Quit", font);
	buttonOut->setColor(Color(137, 137, 137));
}
void sapperPauseMenu::update(Game* game) {
	if (buttonBack->isClickedLeft())
	{
		*gameFlag = 0;
		game->popState();
	}else if (buttonRestart->isClickedLeft())
	{
		*gameFlag = 1;
		game->popState();
	}else if (buttonOut->isClickedLeft())
	{
		*gameFlag = 2;
		game->popState();
	}
}
void sapperPauseMenu::handleInput(const std::optional<Event>& event) {
	buttonRestart->clickHandle(win, event);
	buttonBack->clickHandle(win, event);
	buttonOut->clickHandle(win, event);
}
void sapperPauseMenu::render(RenderWindow* win) {
	renderFunc(win);
	win->draw(background);
	win->draw(menuBackGround);
	buttonRestart->draw(win);
	buttonBack->draw(win);
	buttonOut->draw(win);
}
void sapperPauseMenu::clean() {
	delete buttonRestart;
	delete buttonBack;
	delete buttonOut;
}