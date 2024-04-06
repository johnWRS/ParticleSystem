#pragma once
#include <glm/glm.hpp>
#include "helper.h"
#include "particle.h"
#include "textureLoader.h"
using namespace glm;
class particleEmitter {
public:
	particleEmitter(const std::string& name, const int numEmitsPerMinute, const int numParticlesPerEmit, const vec2& numParticlesPerEmitOffset, const vec3& position, const vec2& positionOffsetX, const vec2& positionOffsetY, const vec2& positionOffsetZ, const vec3& velocity, const vec2& velocityOffsetX
		, const vec2& velocityOffsetY, const vec2& velocityOffsetZ, const vec3& acceleration, const vec2& accelerationOffsetX, const vec2& accelerationOffsetY, const vec2& accelerationOffsetZ
		, const vec3& orientation, const vec2& orientationOffsetX, const vec2& orientationOffsetY, const vec2& orientationOffsetZ, const vec3& orientationRate, const vec2& orientationRateOffsetX
		, const vec2& orientationRateOffsetY, const vec2& orientationRateOffsetZ, const vec3& scale, const vec2& scaleOffsetX, const vec2& scaleOffsetY, const vec2& scaleOffsetZ
		, const vec3& scaleRate, const vec2& scaleRateOffsetX, const vec2& scaleRateOffsetY, const vec2& scaleRateOffsetZ, const vec4& startColour, const vec2& startColourOffsetR
		, const vec2& startColourOffsetG, const vec2& startColourOffsetB, const vec2& startColourOffsetA, const vec4& endColour, const vec2& endColourOffsetR, const vec2& endColourOffsetG
		, const vec2& endColourOffsetB, const vec2& endColourOffsetA, const float lifeSpan, const vec2& lifeSpanOffset, const std::vector<std::string>& textures);
	particle emit();
	std::vector<particle> update(const float dt);
	std::vector<particle> oneTimeEmit(int num);
	void enable() { m_enabled = true; }
	void disable() { m_enabled = false; }
	void toggleEnable() { m_enabled = !m_enabled; }
	std::string getName() const { return m_name; }

private:
	std::string m_name;
	vec3 m_position = vec3(0, 0, 0);
	vec2 m_positionOffsetX = vec2(0, 0);
	vec2 m_positionOffsetY = vec2(0, 0);
	vec2 m_positionOffsetZ = vec2(0, 0);
	vec3 m_velocity = vec3(0, 0, 0);
	vec2 m_velocityOffsetX = vec2(0, 0);
	vec2 m_velocityOffsetY = vec2(0, 0);
	vec2 m_velocityOffsetZ = vec2(0, 0);
	vec3 m_acceleration = vec3(0, 0, 0);
	vec2 m_accelerationOffsetX = vec2(0, 0);
	vec2 m_accelerationOffsetY = vec2(0, 0);
	vec2 m_accelerationOffsetZ = vec2(0, 0);
	vec3 m_orientation = vec3(0, 0, 0);
	vec2 m_orientationOffsetX = vec2(0, 0);
	vec2 m_orientationOffsetY = vec2(0, 0);
	vec2 m_orientationOffsetZ = vec2(0, 0);
	vec3 m_orientationRate = vec3(0, 0, 0);
	vec2 m_orientationRateOffsetX = vec2(0, 0);
	vec2 m_orientationRateOffsetY = vec2(0, 0);
	vec2 m_orientationRateOffsetZ = vec2(0, 0);
	vec3 m_scale = vec3(1, 1, 1);
	vec2 m_scaleOffsetX = vec2(0, 0);
	vec2 m_scaleOffsetY = vec2(0, 0);
	vec2 m_scaleOffsetZ = vec2(0, 0);
	vec3 m_scaleRate = vec3(0, 0, 0);
	vec2 m_scaleRateOffsetX = vec2(0, 0);
	vec2 m_scaleRateOffsetY = vec2(0, 0);
	vec2 m_scaleRateOffsetZ = vec2(0, 0);
	vec4 m_startColour = vec4(1, 1, 1, 1);
	vec2 m_startColourOffsetR = vec2(0, 0);
	vec2 m_startColourOffsetG = vec2(0, 0);
	vec2 m_startColourOffsetB = vec2(0, 0);
	vec2 m_startColourOffsetA = vec2(0, 0);
	vec4 m_endColour = vec4(1, 1, 1, 1);
	vec2 m_endColourOffsetR = vec2(0, 0);
	vec2 m_endColourOffsetG = vec2(0, 0);
	vec2 m_endColourOffsetB = vec2(0, 0);
	vec2 m_endColourOffsetA = vec2(0, 0);
	float m_lifeSpan = 0;
	vec2 m_lifeSpanOffset = vec2(0, 0);
	std::vector<GLuint64> m_textures;

	float m_timePerEmit = 0;
	vec2 m_numParticlesPerEmitOffset = vec2(0, 0);
	int m_numParticlesPerEmit = 1;
	float m_timeElapsed = 0;
	bool m_enabled = false;
};

