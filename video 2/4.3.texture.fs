#version 330 core
out vec4 FragColor;

uniform vec4 colour[100];
uniform sampler2D textures[30];
uniform int instanceOrderToTexture[100];
flat in int index;
in vec2 coords;

void main()
{
	FragColor = texture2D(textures[instanceOrderToTexture[index]],coords)* colour[index];
	if(FragColor.a==0){
		discard;
	}
}