#include "Shader.h"

std::string GetFileContents(const char* _pFileName)
{
	std::ifstream In(_pFileName, std::ios::binary);
	if (In)
	{
		std::string strContents;
		In.seekg(0, std::ios::end);
		strContents.resize(In.tellg());
		In.seekg(0, std::ios::beg);
		In.read(&strContents[0], strContents.size());
		In.close();
		return strContents;
	}
	throw errno;
}

CShader::CShader(const char* _pVertexFile, const char* _pFragmentFile)
{
	std::string strVertexCode = GetFileContents(_pVertexFile);
	std::string strFragmentCode = GetFileContents(_pFragmentFile);

	const char* pVertexSource = strVertexCode.c_str();
	const char* pFragmentSource = strFragmentCode.c_str();

	//Set up Shaders
	GLuint GLuVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(GLuVertexShader, 1, &pVertexSource, NULL);
	glCompileShader(GLuVertexShader);

	GLuint GLuFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(GLuFragmentShader, 1, &pFragmentSource, NULL);
	glCompileShader(GLuFragmentShader);

	m_GLuID = glCreateProgram();

	glAttachShader(m_GLuID, GLuVertexShader);
	glAttachShader(m_GLuID, GLuFragmentShader);

	glLinkProgram(m_GLuID);

	glDeleteShader(GLuVertexShader);
	glDeleteShader(GLuFragmentShader);
}

void CShader::Activate()
{
	glUseProgram(m_GLuID);
}

void CShader::Delete()
{
	glDeleteProgram(m_GLuID);
}
