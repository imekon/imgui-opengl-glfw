#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	void createMesh(GLfloat *vertices, GLuint *indices, GLuint numVertices, GLuint numIndices);
	void renderMesh();
	void clearMesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};
