#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
	void initSystems();

private:
	int _screenWidth;
	int _screenHeight;
	SDL_Window* _window;
};

