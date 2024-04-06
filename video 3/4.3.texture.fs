#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

out vec4 FragColor;

layout (std430,binding=1) buffer TextureHandleBlock{
	uvec2 texture_handles[];
};


uniform vec4 colour[200];
uniform int instanceOrderToTexture[200];
flat in int index;
in vec2 coords;

void main()
{
	FragColor = texture(sampler2D(texture_handles[instanceOrderToTexture[index]]),coords)*colour[index];
	if(FragColor.a==0){
		discard;
	}
}