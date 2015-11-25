#include "MainGame.h"

#include <iostream>

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{

}

void MainGame::run(){
	initSystems();
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	gameLoop();
}

void MainGame::initSystems(){
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
		fatalError("SDL window creation failed");
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr){
		fatalError("SDL_GLcontext creation failed !");
	}
	GLenum error = glewInit();
	if (error != GLEW_OK){
		fatalError("Glew is not Initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	initShaders();
}
void MainGame::initShaders(){
	_shader.compileShaders("Shaders/VertexShader.vert", "Shaders/FragShader.frag");
	_shader.addAttributes("vertexPosition");
	_shader.linkShaders();

}
void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT){
		processInput();
		drawGame();
	}
}

void MainGame::processInput(){
	SDL_Event _event;
	while (SDL_PollEvent(&_event)){
		switch (_event.type){
		case SDL_QUIT :
			_gameState = GameState::EXIT;
			break;


		}
	}

}

void MainGame::drawGame(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.use();
	_sprite.draw();
	_shader.unUse();
	SDL_GL_SwapWindow(_window);
}