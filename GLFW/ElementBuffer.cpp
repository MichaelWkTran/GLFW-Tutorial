#include "ElementBuffer.h"

CElementBuffer::CElementBuffer(GLuint* _pIndicies, GLsizeiptr _Size)
{
    glGenBuffers(1, &m_GLuID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLuID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Size, _pIndicies, GL_STATIC_DRAW);
}

void CElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLuID);
}

void CElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CElementBuffer::Delete()
{
    glDeleteBuffers(1, &m_GLuID);
}
