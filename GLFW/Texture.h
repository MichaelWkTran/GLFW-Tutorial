#pragma once

#include <glad/glad.h>
#include<stb/stb_image.h>
#include "Shader.h"

class CTexture
{
public:
	GLuint m_GLuID;
	GLenum m_Type;

	CTexture(const char* _pImage, GLenum _Type, GLenum _Slot, GLenum _Format, GLenum _PixelType);

	void TextureUnit(CShader& _Shader, const char* _pUniform, GLuint _GLuUnit);
	void Bind();
	void Unbind();
	void Delete();
};

