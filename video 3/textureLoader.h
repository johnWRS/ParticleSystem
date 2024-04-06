#pragma once
#include <vector>
#include <map>
#include <string>
#include "helper.h"
class textureLoader {
public:
	static std::vector<GLuint64> getTextures() { return m_textures; }
	static std::map<std::string, size_t> getTextureMap() { return m_textureMap; }
	static GLuint64 loadTexture(const std::string& filepath);
private:
	//hold the texture handles, Shouldn't have duplicates
	static std::vector<GLuint64> m_textures;
	//map file paths to already loaded texture indices
	static std::map<std::string, size_t> m_textureMap;
};

