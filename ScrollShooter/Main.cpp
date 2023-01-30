#include "pch.h"
#include <iostream>
#include "Game.h"

int main() {
	Arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
	auto game = std::make_shared<Game>();
	game->init();
	game->mainLoop();
}