#pragma once
#include <glm/glm.hpp>
using namespace glm;
class helper {
public:
	template<typename T>
	static T generateRandomNumber(const T min, const T max);
	//generate number between min(inclusive) and max(exclusive)
	template<typename T>
	static T generateRandomNumber(const vec2& range);

	static vec2 generateRandom2Vector(const float range);
	static vec2 generateRandom2Vector(const vec2& range);
	static vec3 generateRandom3Vector(const float range);
	static vec3 generateRandom3Vector(const vec2& range);
	static vec4 generateRandom4Vector(const float range);
	static vec4 generateRandom4Vector(const vec2& range);
	static vec4 generateRandom4Vector(const vec4& range);
};
template<typename T>
T helper::generateRandomNumber(const T min, const T max) {
	if((min == 0 && max == 0) || (min == 0 && max == 1)) {
		return 0;
	}
	return T((max - min) * (float) rand() / (RAND_MAX + 1)) + min;
}

template<typename T>
T helper::generateRandomNumber(const vec2& range) {
	if(range == vec2(0, 0) || range == vec2(0)) {
		return 0;
	}
	return T(T(range.y - range.x) * (float) rand() / (RAND_MAX + 1)) + T(range.x);
}