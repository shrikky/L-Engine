#pragma once
#include <GL/glew.h>
struct Position{
	float x;
	float y;
};
struct UV{
	float u;
	float v;
};
struct Color{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
	
};
struct vertex{
	Position position;
	Color color;
	UV uv;
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
	void setUV(float u, float v){
		uv.u = u;
		uv.v = v;
	}
	void setPosition(float x, float y){
		position.x = x;
		position.y = y;
	}
};