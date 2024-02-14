#include "particle.h"

void particle::update() {
	if(m_transformChange) {
		m_M = translate(mat4(1.0f), m_position) * glm::eulerAngleXYZ(m_orientation.x, m_orientation.y, m_orientation.z) * glm::scale(mat4(1.0f), m_scale);
	}
}

particle::particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour) {
	m_position = pos;
	m_orientation = ori;
	m_scale = scale;
	m_transformChange = true;
	m_colour = colour;
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
