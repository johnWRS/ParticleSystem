#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glad/glad.h>
using namespace glm;
class particle {
public:
	mat4 getM()const { return m_M; };
	bool update(const float dt);
	bool updateMatrix();
	particle() {};
	particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec4& colour);
	particle(const vec3& pos, const vec3& ori, const vec3& scale, const vec3& vel, const vec3& acl, const vec3& rotRate, const vec3& scaleRate, const vec4& startColour, const vec4& endColour, const float lifespan, const GLuint64 texture);
	vec4 getColour()const { return m_colour; };
	vec3 getScale()const { return m_scale; };
	vec3 getOrientation()const { return m_orientation; };
	vec3 getPosition()const { return m_position; };
	GLuint64 getTexture()const { return m_texture; }
	void setPosition(const vec3& pos);
	void setOrientation(const vec3& ori);
	void setScale(const vec3& scale);
	void setColour(const vec4& colour);
private:
	vec3 m_position = vec3(0, 0, 0);
	vec3 m_velocity = vec3(0, 0, 0);
	vec3 m_acceleration = vec3(0, 0, 0);
	vec3 m_orientation = vec3(0, 0, 0);
	vec3 m_orientationRate = vec3(0, 0, 0);
	vec3 m_scale = vec3(1, 1, 1);
	vec3 m_scaleRate = vec3(0, 0, 0);
	bool m_transformChange = false;
	mat4 m_M = mat4(1.0f);
	vec4 m_colour = vec4(1, 1, 1, 1);
	vec4 m_startColour = vec4(1, 1, 1, 1);
	vec4 m_endColour = vec4(1, 1, 1, 1);
	float m_life = 0;
	float m_lifeSpan = 0;
	GLuint64 m_texture = -1;
};