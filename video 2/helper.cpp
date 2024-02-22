#include "helper.h"

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

unsigned int helper::loadTexture(const std::string& path) {
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
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
		return texture;
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
