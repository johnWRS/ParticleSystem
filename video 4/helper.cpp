#include "helper.h"

float helper::calculateRandomOffset(const float starting, const vec2& offset) {
	return starting + helper::generateRandomNumber<float>(offset);
}

vec2 helper::calculateRandomOffset(const vec2& starting, const vec2& offsetX, const vec2& offsetY) {
	return starting + vec2(helper::generateRandomNumber<float>(offsetX), helper::generateRandomNumber<float>(offsetY));
}

vec3 helper::calculateRandomOffset(const vec3& starting, const vec2& offsetX, const vec2& offsetY, const vec2& offsetZ) {
	return starting + vec3(helper::generateRandomNumber<float>(offsetX), helper::generateRandomNumber<float>(offsetY), helper::generateRandomNumber<float>(offsetZ));
}

vec4 helper::calculateRandomOffset(const vec4& starting, const vec2& offsetX, const vec2& offsetY, const vec2& offsetZ, const vec2& offsetW) {
	return starting + vec4(helper::generateRandomNumber<float>(offsetX), helper::generateRandomNumber<float>(offsetY), helper::generateRandomNumber<float>(offsetZ), helper::generateRandomNumber<float>(offsetW));
}

vec2 helper::generateRandom2Vector(const float range) {
	return { generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range) };
}

vec2 helper::generateRandom2Vector(const vec2& range) {
	return { generateRandomNumber<float>(range),generateRandomNumber<float>(range) };
}

vec3 helper::generateRandom3Vector(const float range) {
	return { generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range) };
}

vec3 helper::generateRandom3Vector(const vec2& range) {
	return { generateRandomNumber<float>(range),generateRandomNumber<float>(range),generateRandomNumber<float>(range) };
}

vec4 helper::generateRandom4Vector(const float range) {
	return { generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range),generateRandomNumber<float>(0.0f,range) };
}

vec4 helper::generateRandom4Vector(const vec2& range) {
	return { generateRandomNumber<float>(range),generateRandomNumber<float>(range) ,generateRandomNumber<float>(range) ,generateRandomNumber<float>(range) };
}

GLuint64 helper::loadTexture(const std::string& path) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width;
	int height;
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if(data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		GLuint64 handle = glGetTextureHandleARB(texture);
		glMakeTextureHandleResidentARB(handle);
		glBindTexture(GL_TEXTURE_2D, 0);
		return handle;
	}
	stbi_image_free(data);
	return -1;
}

void helper::bindTextures(const unsigned int binding, const std::vector<unsigned int>& input) {
	for(int i = 0; i < input.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, input[i]);
		glUniform1i(binding + i, i);
	}
}