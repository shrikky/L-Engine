#pragma once
#include <string>
#include <GL\\glew.h>
class Shaders
{
public:
	Shaders();
	~Shaders();

	void compileShaders(const std::string& vertexshaderLoc, const std::string& fragmentshaderLoc);
	void linkShaders();

private:
	void compileShader(const std::string & shaderPath, GLuint id);
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragShaderID;
};

