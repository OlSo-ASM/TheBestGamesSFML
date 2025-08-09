#include "Game.h"

Game::Game(sf::RenderWindow* win) {
	this->win = win;
}

Game::~Game() {
	while (!states.empty()) {
		popState();
	}
}

void Game::pushState(gameState* state) {
	states.push(state);
	states.top()->init(win);
}

void Game::popState() {
	states.top()->clean();
	delete states.top();
	states.pop();
}

gameState* Game::currentState() {
	return states.top();
}

void Game::handleInput(const std::optional<sf::Event>& event) {
	states.top()->handleInput(event);
}

void Game::update() {
	states.top()->update(this);
}

void Game::render() {
	states.top()->render(win);
}