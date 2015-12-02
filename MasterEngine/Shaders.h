#pragma once
#include <string>
#include <GL\\glew.h>

namespace Engine{

	class Shaders
	{
	public:
		Shaders();
		~Shaders();

		void compileShaders(const std::string& vertexshaderLoc, const std::string& fragmentshaderLoc);
		void linkShaders();
		GLint getUniformVariable(const std::string& abc);
		void addAttributes(const std::string& attribName);
		void use();
		void unUse();

	private:
		int _numOfAttrib;
		void compileShader(const std::string & shaderPath, GLuint id);
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragShaderID;
	};

}