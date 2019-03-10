#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	virtual ~Shader();

	bool createFromString(const char *vertexCode, const char *fragmentCode);
	bool createFromFiles(const char *vertexFilename, const char *fragmentFilename);
	GLuint getProjectionLocation();
	GLuint getModelLocation();
	void useShader();
	void clearShader();

private:
	GLuint id, uniform_projection, uniform_model;

	bool compileShader(const char *vertexCode, const char *fragmentCode);
	bool addShader(GLuint program, const char *shader_code, GLenum shader_type);
	std::string readFile(const char *filename);
};

