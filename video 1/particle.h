#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;
class particle {
public:
	mat4 getM()const { return m_M; };
	void update();
	particle() {};
	particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour);
	vec4 getColour()const { return m_colour; };
	vec3 getScale()const { return m_scale; };
	vec3 getOrientation()const { return m_orientation; };
	vec3 getPosition()const { return m_position; };
	void setPosition(const vec3& pos);
	void setOrientation(const vec3& ori);
	void setScale(const vec3& scale);
	void setColour(const vec4& colour);
private:
	vec3 m_position = vec3(0, 0, 0);
	vec3 m_orientation = vec3(0, 0, 0);
	vec3 m_scale = vec3(1, 1, 1);
	bool m_transformChange = false;
	mat4 m_M = mat4(1.0f);
	vec4 m_colour = vec4(1, 1, 1, 1);
};

