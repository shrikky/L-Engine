#version 130

in vec4 fragColor;
in vec2 fragUV;
out vec4 color;
uniform sampler2D mySampler;
uniform float time;

void main()  {
	vec4 textureColor = texture(mySampler,fragUV);
	color = textureColor * fragColor;
}