#include "Shader.h"

using namespace std;

Shader::Shader()
{
	id = 0;
	uniform_projection = 0;
	uniform_model = 0;
}


Shader::~Shader()
{
	clearShader();
}

bool Shader::createFromString(const char * vertexCode, const char * fragmentCode)
{
	return compileShader(vertexCode, fragmentCode);
}

GLuint Shader::getProjectionLocation()
{
	return uniform_projection;
}

GLuint Shader::getModelLocation()
{
	return uniform_model;
}

void Shader::useShader()
{
	glUseProgram(id);
}

void Shader::clearShader()
{
	if (id)
	{
		glDeleteProgram(id);
		id = 0;
	}

	uniform_model = 0;
	uniform_projection = 0;
}

bool Shader::compileShader(const char *vertexCode, const char *fragmentCode)
{
	id = glCreateProgram();
	if (!id)
	{
		cout << "Failed to create shader" << endl;
		return false;
	}

	addShader(id, vertexCode, GL_VERTEX_SHADER);
	addShader(id, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(id, sizeof(eLog), nullptr, eLog);
		cout << "Error linking shader: " << eLog << endl;
		return false;
	}

	glValidateProgram(id);
	glGetProgramiv(id, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(id, sizeof(eLog), nullptr, eLog);
		cout << "Error validating shader: " << eLog << endl;
		return false;
	}

	uniform_model = glGetUniformLocation(id, "model");
	uniform_projection = glGetUniformLocation(id, "projection");

	return true;
}

bool Shader::addShader(GLuint program, const char *shader_code, GLenum shader_type)
{
	auto shader = glCreateShader(shader_type);
	const GLchar *theCode[1];
	theCode[0] = shader_code;

	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shader_code);

	glShaderSource(shader, 1, theCode, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), nullptr, eLog);
		cout << "Error compiling shader: " << eLog << endl;
		return false;
	}
	glAttachShader(program, shader);
	return true;
}

