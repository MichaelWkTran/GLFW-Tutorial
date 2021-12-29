#pragma once

#include <glad/glad.h>

class CVertexBuffer
{
public:
	GLuint m_GLuID;
	CVertexBuffer(GLfloat* _pVerticies, GLsizeiptr _Size);

	void Bind();
	void Unbind();
	void Delete();
};