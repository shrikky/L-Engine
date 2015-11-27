#include "MainGame.h"
#include "ImageLoader.h"
#include <iostream>

MainGame::MainGame() :_time(0),
	_window(nullptr),
	_screenWidth(1024),
	_screenHeight(768),
	_gameState(GameState::PLAY) {
	
}


MainGame::~MainGame()
{

}

void MainGame::run(){
	initSystems();
	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
	_playerTexture = ImageLoader::loadPNG("Textures/PNG/CharacterRight_Standing.png");
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
	_shader.addAttributes("vertexColor");
	_shader.addAttributes("vertexUV");
	_shader.linkShaders();

}
void MainGame::gameLoop(){
	while (_gameState != GameState::EXIT){
		processInput();
		_time += 0.001;
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _shader.getUniformVariable("mySampler");
	glUniform1i(textureLocation, 0);
	//GLuint timeLocation = _shader.getUniformVariable("time");
	//glUniform1f(timeLocation, _time);
	_sprite.draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	_shader.unUse();
	SDL_GL_SwapWindow(_window);
}