#include "helper.h"

vec2 helper::generateRandom2Vector(const float range) {
	return { generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range) };
}

vec2 helper::generateRandom2Vector(const vec2& range) {
	return { generateRandomNumber<float>(range), generateRandomNumber<float>(range) };
}

vec3 helper::generateRandom3Vector(const float range) {
	return { generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range) };
}

vec3 helper::generateRandom3Vector(const vec2& range) {
	return { generateRandomNumber<float>(range), generateRandomNumber<float>(range), generateRandomNumber<float>(range) };
}

vec4 helper::generateRandom4Vector(const float range) {
	return { generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range), generateRandomNumber<float>(0.0f, range) };
}
vec4 helper::generateRandom4Vector(const vec2& range) {
	return { generateRandomNumber<float>(range), generateRandomNumber<float>(range), generateRandomNumber<float>(range), generateRandomNumber<float>(range) };
}

vec4 helper::generateRandom4Vector(const vec4& range) {
	return { generateRandomNumber<float>(0.0f, range.x), generateRandomNumber<float>(0.0f, range.y), generateRandomNumber<float>(0.0f, range.z), generateRandomNumber<float>(0.0f, range.w) };
}