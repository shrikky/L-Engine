#include "Engine.h"
#include <SDL\SDL.h>
#include<GL\glew.h>

namespace Engine{
	int init(){

		// initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// Tell SDL that we want double buffering enabled
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}

}