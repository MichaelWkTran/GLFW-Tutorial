#include "Texture.h"

CTexture::CTexture(const char* _pImage, GLenum _Type, GLenum _Slot, GLenum _Format, GLenum _PixelType)
{
	m_Type = _Type;

	int iImageWidth, iImageHeight, iColChanNum;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pImageData = stbi_load(_pImage, &iImageWidth, &iImageHeight, &iColChanNum, 0);

	glGenTextures(1, &m_GLuID);
	glActiveTexture(_Slot);
	glBindTexture(m_Type, m_GLuID);

	glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(m_Type, 0, GL_RGBA, iImageWidth, iImageHeight, 0, _Format, _PixelType, pImageData);
	glGenerateMipmap(m_Type);

	stbi_image_free(pImageData);
	glBindTexture(m_Type, 0);
}

void CTexture::TextureUnit(CShader& _Shader, const char* _pUniform, GLuint _GLuUnit)
{
	GLuint texUni = glGetUniformLocation(_Shader.m_GLuID, _pUniform);
	_Shader.Activate();
	glUniform1i(texUni, _GLuUnit);
}

void CTexture::Bind()
{
	glBindTexture(m_Type, m_GLuID);
}

void CTexture::Unbind()
{
	glBindTexture(m_Type, 0);
}

void CTexture::Delete()
{
	glDeleteTextures(1, &m_Type);
}
