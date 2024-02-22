#include "particleSystem.h"

void particleSystem::update(const float dt) {
	for(int i = 0; i < m_particles.size(); i++) {
		if(m_particles[i].update(dt)) {
			m_matrices[i] = m_particles[i].getM();
		}
	}
}

void particleSystem::render(const unsigned int shaderID, const mat4& V, const mat4& P) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "P"), 1, GL_FALSE, &P[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "V"), 1, GL_FALSE, &V[0][0]);
	helper::bindTextures(glGetUniformLocation(shaderID, "textures"), m_textures);

	glUniform1iv(glGetUniformLocation(shaderID, "instanceOrderToTexture"), m_instanceOrderToTexture.size(), &m_instanceOrderToTexture[0]);

	glUniform4fv(glGetUniformLocation(shaderID, "colour"), m_colours.size(), &m_colours[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "M"), m_matrices.size(), GL_FALSE, &m_matrices[0][0][0]);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_matrices.size());
}

void particleSystem::createParticle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour, const std::string& imagePath) {
	m_particles.emplace_back(pos, ori, scale, colour);
	m_matrices.emplace_back(1.0f);
	m_colours.emplace_back(colour);
	if(m_textureMap.count(imagePath) > 0) {
		m_instanceOrderToTexture.emplace_back(m_textureMap.at(imagePath));
	}
	else {
		unsigned int texture = helper::loadTexture(imagePath);
		if(texture != -1) {
			m_textures.emplace_back(texture);
			m_textureMap.insert({ imagePath,m_textures.size() - 1 });
			m_instanceOrderToTexture.emplace_back(m_textureMap.at(imagePath));
		}
	}

}
