#pragma once
#include "header.h"
#include "NeuralNetwork.h"

class App
{
	const int _NO_X_SPRITES;
	const int _NO_Y_SPRITES;
	const int _TILE_SIZE;

	sf::RenderWindow _window;
	sf::Event _event;
	bool ** _spriteColors;
	sf::RectangleShape _whiteTile;
	sf::RectangleShape _blackTile;
	NeuralNetwork _network;

	void setTileColor(int x, int y, bool color);
	void paint(int x, int y, bool color);
	void mouseButtonAction();
	void clearPage();
	void drawPage();

public:
	App();
	void loop();
	~App();
};