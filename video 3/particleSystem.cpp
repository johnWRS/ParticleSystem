#include "particleSystem.h"

bool particleSystem::initialize() {
	// build and compile our shader zprogram
	// ------------------------------------
	m_shader = Shader("C://Users//John//Documents//particleSystem//4.3.texture.vs", "C://Users//John//Documents//particleSystem//4.3.texture.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords (note that we changed them to 2.0f!)
		 1.0f,  1.0f, -0.0f,//   1.0f, 0.0f, 0.0f,  // 2.0f, 2.0f, // top right
		 1.0f, -1.0f, -0.0f,//   0.0f, 1.0f, 0.0f,  // 2.0f, 0.0f, // bottom right
		-1.0f, -1.0f, -0.0f,//   0.0f, 0.0f, 1.0f,  // 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, -0.0f,//   1.0f, 1.0f, 0.0f,  // 0.0f, 2.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);

	m_particleTexturesSSBO = 0;
	glGenBuffers(1, &m_particleTexturesSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_particleTexturesSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 100 * sizeof(GLuint64), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, m_particleTexturesSSBO, 0, 100 * sizeof(GLuint64));
	glEnableVertexAttribArray(0);

	return true;
}

void particleSystem::cleanup() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void particleSystem::update(const float dt) {
	for(auto& emitter : m_emitters) {
		addParticles(emitter.update(dt));
	}
	for(int i = 0; i < m_particles.size(); i++) {
		if(m_particles[i].update(dt)) {
			m_matrices[i] = m_particles[i].getM();
			m_colours[i] = m_particles[i].getColour();
		}
	}
}

void particleSystem::render(const mat4& V, const mat4& P) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);*/
	//glCullFace(GL_BACK);
	if(!m_particles.empty()) {
		glBindVertexArray(m_VAO);

		// render container
		m_shader.use();

		glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "P"), 1, GL_FALSE, &P[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "V"), 1, GL_FALSE, &V[0][0]);
		if(!m_textures.empty()) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_particleTexturesSSBO);
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, (int) m_textures.size() * sizeof(GLuint64), &m_textures[0]);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

			glUniform1iv(glGetUniformLocation(m_shader.ID, "instanceOrderToTexture"), m_instanceOrderToTexture.size(), &m_instanceOrderToTexture[0]);
		}


		glUniform4fv(glGetUniformLocation(m_shader.ID, "colour"), m_colours.size(), &m_colours[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_shader.ID, "M"), m_matrices.size(), GL_FALSE, &m_matrices[0][0][0]);

		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_matrices.size());
	}
}

void particleSystem::addEmitter(const particleEmitter& emitter) {
	m_emitters.emplace_back(emitter);
	m_emitterMap.insert({ emitter.getName(),m_emitters.size() - 1 });
}

void particleSystem::oneTimeEmit(const std::string& name, int numParticles) {
	if(m_emitterMap.count(name) > 0) {
		addParticles(m_emitters[m_emitterMap.at(name)].oneTimeEmit(numParticles));
	}
}

void particleSystem::enableEmitter(const std::string& name) {
	if(m_emitterMap.count(name) > 0) {
		m_emitters[m_emitterMap.at(name)].enable();
	}
}

void particleSystem::disableEmitter(const std::string& name) {
	if(m_emitterMap.count(name) > 0) {
		m_emitters[m_emitterMap.at(name)].disable();
	}
}

void particleSystem::toggleEmitter(const std::string& name) {
	if(m_emitterMap.count(name) > 0) {
		m_emitters[m_emitterMap.at(name)].toggleEnable();
	}
}

void particleSystem::addParticles(const std::vector<particle>& particles) {
	for(const auto& particle : particles) {
		m_particles.emplace_back(particle);
		m_matrices.emplace_back(1.0f);
		m_colours.emplace_back(particle.getColour());
		addTexture(particle.getTexture());
	}
}

void particleSystem::addTexture(const GLuint64 text) {
	if(m_textureHandleMap.count(text) > 0) {
		m_instanceOrderToTexture.emplace_back(m_textureHandleMap.at(text));
	}
	else {
		m_textures.emplace_back(text);
		m_textureHandleMap.insert({ text,m_textures.size() - 1 });
		m_instanceOrderToTexture.emplace_back(m_textureHandleMap[text]);
	}
}
