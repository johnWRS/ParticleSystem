#pragma once
#include <vector>
#include <glad/glad.h>
#include <map>
#include <string>
#include "particle.h"
#include "helper.h"
class particleSystem {
public:
	particleSystem() {};
	void update(const float dt);
	void render(const unsigned int shaderID, const mat4& V, const mat4& P);
	void createParticle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour, const std::string& imagePath);
private:
	std::vector<particle> m_particles;
	std::vector<vec4> m_colours;
	std::vector<mat4> m_matrices;
	//hold the texture handles, Shouldn't have duplicates
	std::vector<unsigned int> m_textures;
	//map file paths to already loaded texture indices
	std::map<std::string, size_t> m_textureMap;
	//take GL_InstanceID and map to textures
	std::vector<int> m_instanceOrderToTexture;
};

