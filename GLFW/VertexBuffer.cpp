#include "VertexBuffer.h"

CVertexBuffer::CVertexBuffer(GLfloat* _pVerticies, GLsizeiptr _Size)
{
	glGenBuffers(1, &m_GLuID);
    glBindBuffer(GL_ARRAY_BUFFER, m_GLuID);
    glBufferData(GL_ARRAY_BUFFER, _Size, _pVerticies, GL_STATIC_DRAW);
}

void CVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_GLuID);
}

void CVertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CVertexBuffer::Delete()
{
    glDeleteBuffers(1, &m_GLuID);
}
