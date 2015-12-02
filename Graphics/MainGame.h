#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>
#include <MasterEngine\Errors.h>
#include <MasterEngine\Sprite.h>
#include <MasterEngine\Shaders.h>
#include <MasterEngine\GLTexture.h>
#include <vector>
#include <MasterEngine\Window.h>
#include <MasterEngine\Engine.h>
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
	void calculateFPS();
	Engine::Shaders _shader;
	Engine::Window _window;
	GameState _gameState;
	std::vector<Engine::Sprite*> _sprite;
	Engine::GLTexture _playerTexture;
	int _screenWidth;
	int _screenHeight;
	float _fps;		
	float _frameTime;
	float _time;
	float _maxFPS;
};

