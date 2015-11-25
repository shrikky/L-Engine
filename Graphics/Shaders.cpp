#include "Shaders.h"
#include "Errors.h"
#include <vector>
#include<fstream>

Shaders::Shaders() : _programID(0), _vertexShaderID(0), _fragShaderID(0)
{

}


Shaders::~Shaders()
{

}

void Shaders::compileShaders(const std::string & vertexShader, const std::string& fragmentShader)
{

	// Create ShaderIDs
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatalError("VertexShader not created");

	_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragShaderID == 0)
		fatalError("Fragment Shader not created");

	compileShader(vertexShader, _vertexShaderID);
	compileShader(fragmentShader, _fragShaderID);

}

void Shaders::compileShader(const std::string & shaderPath, GLuint shaderID){

	// Load Shaders
	std::ifstream shaderFile(shaderPath);
	if (shaderFile.fail()){
		perror(shaderPath.c_str);
		fatalError("Failed to open" + shaderPath);
	}
	std::string fileContents;
	std::string line;
	while (std::getline(shaderFile, line)){
		fileContents += line + "\n";
	}
	shaderFile.close();

	// Create a pointer for file contents 
	const char* contentsptr = fileContents.c_str();
	glShaderSource(shaderID, 1, &contentsptr, nullptr);

	// Compile Shader
	glCompileShader(shaderID);

	// Error Handling
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(_vertexShaderID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the shader anymore.
		glDeleteShader(shaderID);
		std::printf("%s\n", &infoLog[0]);
		fatalError("Shader failed to compile" + shaderPath);
		
	}

}
void Shaders::linkShaders(){
	_programID = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragShaderID);

		//Use the infoLog as you see fit.

		std::printf("%s\n", &infoLog[0]);
		fatalError("Shader failed to compile");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragShaderID);
}