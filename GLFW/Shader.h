#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* _pFileName);

class CShader
{
public:
	GLuint m_GLuID;
	CShader(const char* _pVertexFile, const char* _pFragmentFile);

	void Activate();
	void Delete();
};