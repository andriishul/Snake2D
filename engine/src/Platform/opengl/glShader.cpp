#include "glShader.h"
#include "glad/glad.h"
#include <fstream>
std::string glShader::ReadShader(const std::string& filename) const
{
	std::fstream fs{filename};

	if (fs.fail() || !fs.good())
		throw std::runtime_error("Shader " + filename + " not found.");
	std::string text, line;
	while (std::getline(fs, line))
		text += line + "\n";
	return text;
}
void glShader::CheckProgramLinkStatus() const
{
	GLint success = 1;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		GLint length = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
		GLchar* logMsg = new char[length];

		glGetProgramInfoLog(m_ProgramID, length, nullptr, logMsg);
		std::string errorMsg(logMsg);
		delete[] logMsg;
		throw std::runtime_error(errorMsg);
	}
}

void glShader::CheckShaderCompileStatus(unsigned shader) const
{
	GLint success = 1;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
	if (!success) {
		GLint length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar* logMsg = new char[length];

		glGetShaderInfoLog(shader, length, nullptr, logMsg);
		std::string errorMsg(logMsg);
		delete[] logMsg;
		throw std::runtime_error(errorMsg);
	}
}

glShader::glShader(const std::string& vertexFile, const std::string& fragmentFile): m_ProgramID(glCreateProgram())
{
	std::string vertSrc = ReadShader(ASSETS_SHADERS_DIR + vertexFile);
	std::string fragSrc = ReadShader(ASSETS_SHADERS_DIR + fragmentFile);
	Compile(vertSrc, fragSrc);
}

glShader::~glShader()
{
	if(glIsProgram(m_ProgramID))
		glDeleteProgram(m_ProgramID);
}
void glShader::Compile(const std::string& vs_code, const std::string& fs_code)
{
	const char* vsCode = vs_code.c_str(), *fsCode = fs_code.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER),
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vsCode, nullptr);
	glShaderSource(fragmentShader, 1, &fsCode, nullptr);

	glCompileShader(vertexShader);
	CheckShaderCompileStatus(vertexShader);
	glCompileShader(fragmentShader);
	CheckShaderCompileStatus(fragmentShader);

	glAttachShader(m_ProgramID, vertexShader);
	glAttachShader(m_ProgramID, fragmentShader);

	glLinkProgram(m_ProgramID);
	CheckProgramLinkStatus();

	glDetachShader(m_ProgramID, vertexShader);
	glDetachShader(m_ProgramID, fragmentShader);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void glShader::Use() const
{
	glUseProgram(m_ProgramID);
}

void glShader::SetInt(const char* name, int val) const
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name), val);
}

void glShader::SetFloat(const char* name, float val) const
{
	glUniform1f(glGetUniformLocation(m_ProgramID, name), val);
}

void glShader::SetMat3(const char* name, glm::mat3 const& val) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name), 1, false, &val[0][0]);
}

void glShader::SetMat4(const char* name, glm::mat4 const& val) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name), 1, false, &val[0][0]);
}

void glShader::SetVec2(const char* name, glm::vec2 const& val) const
{
	glUniform2f(glGetUniformLocation(m_ProgramID, name), val.x,val.y);
}

void glShader::SetVec3(const char* name, glm::vec3 const& val) const
{
	glUniform3f(glGetUniformLocation(m_ProgramID, name), val.x, val.y, val.z);
}

void glShader::SetVec4(const char* name, glm::vec4 const& val) const
{
	glUniform4f(glGetUniformLocation(m_ProgramID, name), val.x, val.y, val.z, val.w);
}
