#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

out vec4 FragColor;

in VS_OUT{
	flat vec4 colour;
	vec2 coords;
	flat float life;
	flat uvec2 texture;
}fs_in;

void main()
{
	if(fs_in.life<=0){
		discard;
	}
	FragColor = texture(sampler2D(fs_in.texture),fs_in.coords)*fs_in.colour;
	//FragColor = vec4(1,1,1,1);
	if(FragColor.a==0){
		discard;
	}
}