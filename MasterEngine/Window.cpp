#include "Window.h"


namespace Engine{

	Window::Window()
	{
	}


	Window::~Window()
	{
	}
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE){
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN){
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS){
			flags |= SDL_WINDOW_BORDERLESS;
		}
		// Create a window 
		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

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


		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		SDL_GL_SetSwapInterval(0);
		std::cout << "OpenGL version  : " << glGetString(GL_VERSION) << std::endl;
		return 0;
	}

	void Window::swapBuffer(){
		SDL_GL_SwapWindow(_window);
	}
}