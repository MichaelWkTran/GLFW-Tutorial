#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

class CElementBuffer
{
public:
	GLuint m_GLuID;
	CElementBuffer(std::vector<GLuint>& _GLuIndicies);

	void Bind();
	void Unbind();
	void Delete();
};

