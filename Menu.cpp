#include "Menu.h"

#include "Game.h"

Menu::Menu(Game* game) {
	this->game = game;
}

Menu::~Menu() {

}

void Menu::render() {
	game->switchGameState(GameState::PLAYING);
}

void Menu::update(float delta) {

}

bool Menu::handleEvent(SDL_Event* event) {

	return true;
}

void Menu::changeFrom() {

}

void Menu::changeTo() {

}

void Menu::resize(int width, int height) {

}
