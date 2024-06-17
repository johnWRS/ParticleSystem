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
	const int PARTICLE_BUFFER_LIMIT = 1000;
	particleSystem() {};
	bool initialize(unsigned int arraySize);
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

	std::vector<particleEmitter> m_emitters;
	std::map < std::string, std::size_t> m_emitterMap;

	std::vector<particle> m_particles;
	std::vector<particleStripped> m_strippedParticles;

	unsigned int m_tail;
	unsigned int m_arraySize;

	GLuint m_particlesSSBO;
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	Shader m_shader;
};
