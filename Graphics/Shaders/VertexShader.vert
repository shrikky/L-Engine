#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragUV;
out vec4 fragColor;

void main(){
    
	gl_Position.xy = vertexPosition;   
	gl_Position.z =0;
	gl_Position.w =1; 
	fragColor = vertexColor;
	fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}