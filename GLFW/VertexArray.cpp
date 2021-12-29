#include "VertexArray.h"

CVertexArray::CVertexArray()
{
    glGenVertexArrays(1, &m_GLuID);
}

void CVertexArray::LinkVertexBuffer(CVertexBuffer VertexBuffer, GLuint GluLayout)
{
    VertexBuffer.Bind();

    glVertexAttribPointer(GluLayout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(GluLayout);

    VertexBuffer.Unbind();
}

void CVertexArray::Bind()
{
    glBindVertexArray(m_GLuID);
}

void CVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void CVertexArray::Delete()
{
    glDeleteVertexArrays(1, &m_GLuID);
}
