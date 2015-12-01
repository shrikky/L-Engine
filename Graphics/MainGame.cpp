#include "MainGame.h"
#include <iostream>

MainGame::MainGame() :_time(0),
	_screenWidth(1024),
	_screenHeight(768),
	_maxFPS(60),
	_gameState(GameState::PLAY) {
	
}


MainGame::~MainGame()
{

}

void MainGame::run(){
	initSystems();

	_sprite.push_back(new Sprite());
	_sprite.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");

	_sprite.push_back(new Sprite());
	_sprite.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/PNG/CharacterRight_Standing.png");
	

	gameLoop();
}

void MainGame::initSystems(){
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	// Tell SDL that we want double buffering enabled
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_window.create("Game Engine", _screenWidth, _screenHeight, FULLSCREEN);
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
		//frame time measuring/
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.001;
		drawGame();
		calculateFPS();

		// Print once in 10 frames
		static int framecounter = 0;
		framecounter++;
		if (framecounter == 10){
			std::cout << _fps << std::endl;
			framecounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks){
			SDL_Delay(1000.0f / _maxFPS - frameTicks);

		}
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
	GLint textureLocation = _shader.getUniformVariable("mySampler");
	glUniform1i(textureLocation, 0);

	for (int i = 0; i < _sprite.size(); i++){
		_sprite[i]->draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	_window.swapBuffer();
	_shader.unUse();
	
}

void MainGame::calculateFPS(){
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	static float currentTicks;

	// get ticks using SDL
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;
	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;

	// Store the values in this array and calculate Sum
	for (int i = 0; i < count; i++){
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;


	// print only if the average is not 0
	if (frameTimeAverage > 0){
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}

	
}