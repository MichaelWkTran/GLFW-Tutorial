#pragma once

#include <glad/glad.h>

class CElementBuffer
{
public:
	GLuint m_GLuID;
	CElementBuffer(GLuint* _pIndicies, GLsizeiptr _Size);

	void Bind();
	void Unbind();
	void Delete();
};

