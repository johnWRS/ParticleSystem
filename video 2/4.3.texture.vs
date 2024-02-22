#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 M[100];
uniform mat4 V;
uniform mat4 P;

flat out int index;
out vec2 coords;

void main()
{
	gl_Position = P *V*M[gl_InstanceID]* vec4(pos, 1.0);
	index=gl_InstanceID;
	coords=(pos.xy/2.0f)+vec2(0.5,0.5);
}
