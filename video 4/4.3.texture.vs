#version 460 core
layout (location = 0) in vec3 pos;

struct particle{
	mat4 m_M;
	vec4 m_colour;
	uvec2 m_texture;
	float m_life;
	float two;
};

layout (std430,binding=2) buffer ParticleBlock{
	particle particles[];
};

out VS_OUT{
	flat vec4 colour;
	vec2 coords;
	flat float life;
	flat uvec2 texture;
}vs_out;

uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P *V*particles[gl_InstanceID].m_M* vec4(pos, 1.0);
	vs_out.coords=(pos.xy/2.0f)+vec2(0.5,0.5);
	vs_out.life=particles[gl_InstanceID].m_life;
	vs_out.texture=particles[gl_InstanceID].m_texture;
	vs_out.colour=particles[gl_InstanceID].m_colour;
}