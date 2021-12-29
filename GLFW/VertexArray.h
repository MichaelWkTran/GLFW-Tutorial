#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"

class CVertexArray
{
public:
	GLuint m_GLuID;
	CVertexArray();

	void LinkVertexBuffer(CVertexBuffer VertexBuffer, GLuint GluLayout);
	void Bind();
	void Unbind();
	void Delete();
};

