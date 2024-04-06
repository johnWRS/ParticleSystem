#include "particleEmitter.h"

particleEmitter::particleEmitter(const std::string& name, const int numEmitsPerMinute, const int numParticlesPerEmit, const vec2& numParticlesPerEmitOffset, const vec3& position, const vec2& positionOffsetX, const vec2& positionOffsetY, const vec2& positionOffsetZ, const vec3& velocity, const vec2& velocityOffsetX, const vec2& velocityOffsetY, const vec2& velocityOffsetZ, const vec3& acceleration, const vec2& accelerationOffsetX, const vec2& accelerationOffsetY, const vec2& accelerationOffsetZ, const vec3& orientation, const vec2& orientationOffsetX, const vec2& orientationOffsetY, const vec2& orientationOffsetZ, const vec3& orientationRate, const vec2& orientationRateOffsetX, const vec2& orientationRateOffsetY, const vec2& orientationRateOffsetZ, const vec3& scale, const vec2& scaleOffsetX, const vec2& scaleOffsetY, const vec2& scaleOffsetZ, const vec3& scaleRate, const vec2& scaleRateOffsetX, const vec2& scaleRateOffsetY, const vec2& scaleRateOffsetZ, const vec4& startColour, const vec2& startColourOffsetR, const vec2& startColourOffsetG, const vec2& startColourOffsetB, const vec2& startColourOffsetA, const vec4& endColour, const vec2& endColourOffsetR, const vec2& endColourOffsetG, const vec2& endColourOffsetB, const vec2& endColourOffsetA, const float lifeSpan, const vec2& lifeSpanOffset, const std::vector<std::string>& textures) {
	m_name = name;
	m_position = position;
	m_positionOffsetX = positionOffsetX;
	m_positionOffsetY = positionOffsetY;
	m_positionOffsetZ = positionOffsetZ;
	m_velocity = velocity;
	m_velocityOffsetX = velocityOffsetX;
	m_velocityOffsetY = velocityOffsetY;
	m_velocityOffsetZ = velocityOffsetZ;
	m_acceleration = acceleration;
	m_accelerationOffsetX = accelerationOffsetX;
	m_accelerationOffsetY = accelerationOffsetY;
	m_accelerationOffsetZ = accelerationOffsetZ;
	m_orientation = orientation;
	m_orientationOffsetX = orientationOffsetX;
	m_orientationOffsetY = orientationOffsetY;
	m_orientationOffsetZ = orientationOffsetZ;
	m_orientationRate = orientationRate;
	m_orientationRateOffsetX = orientationRateOffsetX;
	m_orientationRateOffsetY = orientationRateOffsetY;
	m_orientationRateOffsetZ = orientationRateOffsetZ;
	m_scale = scale;
	m_scaleOffsetX = scaleOffsetX;
	m_scaleOffsetY = scaleOffsetY;
	m_scaleOffsetZ = scaleOffsetZ;
	m_scaleRate = scaleRate;
	m_scaleRateOffsetX = scaleRateOffsetX;
	m_scaleRateOffsetY = scaleRateOffsetY;
	m_scaleRateOffsetZ = scaleRateOffsetZ;
	m_startColour = startColour;
	m_startColourOffsetR = m_startColourOffsetR;
	m_startColourOffsetG = m_startColourOffsetG;
	m_startColourOffsetB = m_startColourOffsetB;
	m_startColourOffsetA = m_startColourOffsetA;
	m_endColour = endColour;
	m_endColourOffsetR = m_endColourOffsetR;
	m_endColourOffsetG = m_endColourOffsetG;
	m_endColourOffsetB = m_endColourOffsetB;
	m_endColourOffsetA = m_endColourOffsetA;
	m_lifeSpan = lifeSpan;
	m_lifeSpanOffset = lifeSpanOffset;
	m_timePerEmit = 60.0f / float(numEmitsPerMinute);
	m_numParticlesPerEmitOffset = numParticlesPerEmitOffset;
	m_numParticlesPerEmit = numParticlesPerEmit;
	for(const auto& texture : textures) {
		m_textures.emplace_back(textureLoader::loadTexture(texture));
	}
}

particle particleEmitter::emit() {
	vec3 pos = helper::calculateRandomOffset(m_position, m_positionOffsetX, m_positionOffsetY, m_positionOffsetZ);
	vec3 vel = helper::calculateRandomOffset(m_velocity, m_velocityOffsetX, m_velocityOffsetY, m_velocityOffsetZ);
	vec3 acl = helper::calculateRandomOffset(m_acceleration, m_accelerationOffsetX, m_accelerationOffsetY, m_accelerationOffsetZ);
	vec3 orientation = helper::calculateRandomOffset(m_orientation, m_orientationOffsetX, m_orientationOffsetY, m_orientationOffsetZ);
	vec3 orientationRate = helper::calculateRandomOffset(m_orientationRate, m_orientationRateOffsetX, m_orientationRateOffsetY, m_orientationRateOffsetZ);
	vec3 scale = helper::calculateRandomOffset(m_scale, m_scaleOffsetX, m_scaleOffsetY, m_scaleOffsetZ);
	vec3 scaleRate = helper::calculateRandomOffset(m_scaleRate, m_scaleRateOffsetX, m_scaleRateOffsetY, m_scaleRateOffsetZ);
	vec4 startColour = helper::calculateRandomOffset(m_startColour, m_startColourOffsetR, m_startColourOffsetG, m_startColourOffsetB, m_startColourOffsetA);
	vec4 endColour = helper::calculateRandomOffset(m_endColour, m_endColourOffsetR, m_endColourOffsetG, m_endColourOffsetB, m_endColourOffsetA);
	float life = helper::calculateRandomOffset(m_lifeSpan, m_lifeSpanOffset);
	GLuint64 texture = -1;
	if(!m_textures.empty()) {
		texture = m_textures[helper::generateRandomNumber(size_t(0), m_textures.size())];
	}
	return{ pos, orientation, scale, vel, acl, orientationRate, scaleRate, startColour, endColour, life, texture };
}

std::vector<particle> particleEmitter::update(const float dt) {
	if(m_enabled) {
		std::vector<particle> emittedParticles;
		m_timeElapsed += dt;
		int numEmits = int(m_timeElapsed / m_timePerEmit);
		m_timeElapsed = fmodf(m_timeElapsed, m_timePerEmit);
		if(numEmits > 0) {
			int numParticlesPerEmit = helper::calculateRandomOffset(m_numParticlesPerEmit, m_numParticlesPerEmitOffset);
			for(int i = 0; i < numEmits * numParticlesPerEmit; i++) {
				emittedParticles.emplace_back(emit());
			}
		}
		return emittedParticles;
	}
	return {};
}

std::vector<particle> particleEmitter::oneTimeEmit(int num) {
	std::vector<particle> emittedParticles;
	for(int i = 0; i < num; i++) {
		emittedParticles.emplace_back(emit());
	}
	return emittedParticles;
}
