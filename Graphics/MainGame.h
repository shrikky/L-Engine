#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include "Errors.h"
#include "Sprite.h"
#include "Shaders.h"
#include "GLTexture.h"
enum class GameState{PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();

private:

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	Shaders _shader;
	SDL_Window* _window;
	GameState _gameState;
	Sprite _sprite;
	GLTexture _playerTexture;
	int _screenWidth;
	int _screenHeight;
	float _time;
};

