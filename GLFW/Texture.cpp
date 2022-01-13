#include "Texture.h"

CTexture::CTexture(const char* _pImage, GLenum _GLeType, GLuint _GLuSlot, GLenum _GLeFormat, GLenum _GLePixelType)
{
	m_GLeType = _GLeType;

	int iImageWidth, iImageHeight, iColChanNum;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pImageData = stbi_load(_pImage, &iImageWidth, &iImageHeight, &iColChanNum, 0);

	glGenTextures(1, &m_GLuID);
	glActiveTexture(GL_TEXTURE0 + _GLuSlot);
	m_GLuUnit = _GLuSlot;
	glBindTexture(m_GLeType, m_GLuID);

	glTexParameteri(m_GLeType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(m_GLeType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(m_GLeType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_GLeType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(m_GLeType, 0, GL_RGBA, iImageWidth, iImageHeight, 0, _GLeFormat, _GLePixelType, pImageData);
	glGenerateMipmap(m_GLeType);

	stbi_image_free(pImageData);
	glBindTexture(m_GLeType, 0);
}

void CTexture::TextureUnit(CShader& _Shader, const char* _pUniform, GLuint _GLuUnit)
{
	GLuint texUni = glGetUniformLocation(_Shader.m_GLuID, _pUniform);
	_Shader.Activate();
	glUniform1i(texUni, _GLuUnit);
}

void CTexture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + m_GLuUnit);
	glBindTexture(m_GLeType, m_GLuID);
}

void CTexture::Unbind()
{
	glBindTexture(m_GLeType, 0);
}

void CTexture::Delete()
{
	glDeleteTextures(1, &m_GLeType);
}
