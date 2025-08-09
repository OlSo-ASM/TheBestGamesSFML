#include "Game.h"

gameState::~gameState() {

}
void gameState::init(sf::RenderWindow* win) {
	this->win = win;
}
void gameState::clean() {

}