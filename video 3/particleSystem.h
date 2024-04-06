#pragma once
#include <vector>
#include <glad/glad.h>
#include <map>
#include <string>
#include <learnopengl/shader_s.h>
#include "particle.h"
#include "textureLoader.h"
#include "particleEmitter.h"
class particleSystem {
public:
	particleSystem() {};
	bool initialize();
	void cleanup();
	void update(const float dt);
	void render(const mat4& V, const mat4& P);
	void addEmitter(const particleEmitter& emitter);
	void oneTimeEmit(const std::string& name, int numParticles);
	void enableEmitter(const std::string& name);
	void disableEmitter(const std::string& name);
	void toggleEmitter(const std::string& name);
private:
	void addParticles(const std::vector<particle>& particles);
	void addTexture(const GLuint64 text);

	std::vector<particleEmitter> m_emitters;
	std::map < std::string, std::size_t> m_emitterMap;

	std::vector<particle> m_particles;
	std::vector<vec4> m_colours;
	std::vector<mat4> m_matrices;

	//hold the texture handles, Shouldn't have duplicates
	std::vector<GLuint64> m_textures;
	//map file paths to already loaded texture indices
	std::map<GLuint64, size_t> m_textureHandleMap;
	//take GL_InstanceID and map to textures
	std::vector<int> m_instanceOrderToTexture;

	GLuint m_particleTexturesSSBO;
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	Shader m_shader;
};
