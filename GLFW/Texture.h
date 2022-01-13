#pragma once

#include <glad/glad.h>
#include<stb/stb_image.h>
#include "Shader.h"

class CTexture
{
public:
	GLuint m_GLuID;
	GLenum m_GLeType;
	GLuint m_GLuUnit;

	CTexture(const char* _pImage, GLenum _GLeType, GLuint _GLuSlot, GLenum _GLeFormat, GLenum _GLePixelType);

	void TextureUnit(CShader& _Shader, const char* _pUniform, GLuint _GLuUnit);
	void Bind();
	void Unbind();
	void Delete();
};

