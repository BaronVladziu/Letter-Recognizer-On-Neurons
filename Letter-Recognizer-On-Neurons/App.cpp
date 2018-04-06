#include "App.h"

App::App()
	: _NO_X_SPRITES(50),
	_NO_Y_SPRITES(50),
	_TILE_SIZE(15),
	_window(sf::VideoMode(_TILE_SIZE*_NO_X_SPRITES, _TILE_SIZE*_NO_Y_SPRITES), "Letter-Recognizer-On-Neurons"),
	_network(_NO_X_SPRITES, _NO_Y_SPRITES)
{
	_whiteTile.setSize(sf::Vector2f(_TILE_SIZE, _TILE_SIZE));
	_whiteTile.setFillColor(sf::Color::White);
	_blackTile.setSize(sf::Vector2f(_TILE_SIZE, _TILE_SIZE));
	_blackTile.setFillColor(sf::Color::Black);
	_spriteColors = new bool *[_NO_X_SPRITES];
	for (int i = 0; i < _NO_X_SPRITES; i++)
	{
		_spriteColors[i] = new bool[_NO_Y_SPRITES];
		for (int j = 0; j < _NO_Y_SPRITES; j++)
		{
			_spriteColors[i][j] = false;
		}
	}
	std::cout << "Hello, would you like to play with me?" << std::endl;
	std::cout << "Draw me a number and press Enter" << std::endl;
	std::cout << "then I'll do my best to recognize it" << std::endl;
}
void App::loop()
{
	while (_window.isOpen())
	{
		while (_window.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				_window.close();
			if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
				_window.close();
			if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Return)
			{
				_network.recognize(_spriteColors);
				clearPage();
			}
		}
		mouseButtonAction();
		_window.clear();
		drawPage();
		_window.display();
	}
}
void App::clearPage()
{
	for (int i = 0; i < _NO_X_SPRITES; i++)
	{
		for (int j = 0; j < _NO_Y_SPRITES; j++)
		{
			_spriteColors[i][j] = false;
		}
	}
}
void App::mouseButtonAction()
{
	sf::Vector2i pos = sf::Mouse::getPosition(_window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		paint(pos.x / _TILE_SIZE, pos.y / _TILE_SIZE, true);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		paint(pos.x / _TILE_SIZE, pos.y / _TILE_SIZE, false);
}
void App::paint(int x, int y, bool color)
{
	setTileColor(x, y, color);
	setTileColor(x+1, y, color);
	setTileColor(x, y+1, color);
	setTileColor(x-1, y, color);
	setTileColor(x, y-1, color);
	setTileColor(x + 1, y - 1, color);
	setTileColor(x + 1, y + 1, color);
	setTileColor(x - 1, y - 1, color);
	setTileColor(x - 1, y + 1, color);
	setTileColor(x + 2, y, color);
	setTileColor(x, y + 2, color);
	setTileColor(x - 2, y, color);
	setTileColor(x, y - 2, color);
	setTileColor(x + 2, y - 1, color);
	setTileColor(x + 2, y + 1, color);
	setTileColor(x - 2, y - 1, color);
	setTileColor(x - 2, y + 1, color);
	setTileColor(x + 1, y - 2, color);
	setTileColor(x + 1, y + 2, color);
	setTileColor(x - 1, y - 2, color);
	setTileColor(x - 1, y + 2, color);
}
void App::setTileColor(int x, int y, bool color)
{
	if (x >= 0 && x < _NO_X_SPRITES &&
		y >= 0 && y < _NO_Y_SPRITES)
	{
		_spriteColors[x][y] = color;
	}
}
void App::drawPage()
{
	for (int i = 0; i < _NO_X_SPRITES; i++)
	{
		for (int j = 0; j < _NO_Y_SPRITES; j++)
		{
			if (_spriteColors[i][j] == true)
			{
				_whiteTile.setPosition(double(i*_TILE_SIZE), double(j*_TILE_SIZE));
				_window.draw(_whiteTile);
			}
			else
			{
				_blackTile.setPosition(double(i*_TILE_SIZE), double(j*_TILE_SIZE));
				_window.draw(_blackTile);
			}
		}
	}
}
App::~App()
{
	for (int i = 0; i < _NO_X_SPRITES; i++)
	{
		delete[] _spriteColors[i];
	}
	delete[] _spriteColors;
}