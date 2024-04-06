#include "textureLoader.h"

//hold the texture handles, Shouldn't have duplicates
std::vector<GLuint64> textureLoader::m_textures;
//map file paths to already loaded texture indices
std::map < std::string, size_t> textureLoader::m_textureMap;

GLuint64 textureLoader::loadTexture(const std::string& filepath) {
	if(m_textureMap.count(filepath) > 0) {
		return m_textures.at(m_textureMap.at(filepath));
	}
	else {
		GLuint64 texture = helper::loadTexture(filepath);
		if(texture != -1) {
			m_textures.emplace_back(texture);
			m_textureMap.insert({ filepath,m_textures.size() - 1 });
			return texture;
		}
	}
	return -1;
}
