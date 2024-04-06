#include "particle.h"

bool particle::update(const float dt) {
	if(m_acceleration != vec3(0, 0, 0)) {
		m_velocity += m_acceleration * dt;
	}
	if(m_velocity != vec3(0, 0, 0)) {
		m_position += m_velocity * dt;
		m_transformChange = true;
	}
	if(m_orientationRate != vec3(0, 0, 0)) {
		m_orientation += m_orientationRate * dt;
		m_transformChange = true;
	}
	if(m_scaleRate != vec3(0, 0, 0)) {
		m_scale += m_scaleRate * dt;
		m_transformChange = true;
	}
	m_life += dt;
	if(m_lifeSpan != 0 && m_startColour != m_endColour) {
		float norm = clamp(m_life / m_lifeSpan, 0.0f, 1.0f);
		m_colour = lerp(m_startColour, m_endColour, norm);
	}
	return updateMatrix();
}

bool particle::updateMatrix() {
	if(m_transformChange) {
		m_M = translate(mat4(1.0f), m_position) * glm::eulerAngleXYZ(m_orientation.x, m_orientation.y, m_orientation.z) * glm::scale(mat4(1.0f), m_scale);
		m_transformChange = false;
		return true;
	}
	return false;
}

particle::particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour) {
	m_position = pos;
	m_orientation = ori;
	m_scale = scale;
	m_transformChange = true;
	m_colour = colour;
}

particle::particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec3& vel, const vec3& acl, const vec3& rotRate, const vec3& scaleRate, const vec4& startColour, const vec4& endColour, const float lifespan, const GLuint64 texture) {
	m_position = pos;
	m_velocity = vel;
	m_acceleration = acl;
	m_orientation = ori;
	m_orientationRate = rotRate;
	m_scale = scale;
	m_scaleRate = scaleRate;
	m_transformChange = true;
	m_colour = startColour;
	m_startColour = startColour;
	m_endColour = endColour;
	m_lifeSpan = lifespan;
	m_texture = texture;
}

void particle::setPosition(const vec3& pos) {
	if(pos != m_position) {
		m_position = pos;
		m_transformChange = true;
	}
}

void particle::setOrientation(const vec3& ori) {
	if(ori != m_orientation) {
		m_orientation = ori;
		m_transformChange = true;
	}
}

void particle::setScale(const vec3& scale) {
	if(scale != m_scale) {
		m_scale = scale;
		m_transformChange = true;
	}
}

void particle::setColour(const vec4& colour) {
	m_colour = colour;
}