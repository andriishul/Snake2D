#pragma once
#include <Graphics/Shader.hpp>


class glShader : public Shader 
{
private:
	std::string ReadShader(const std::string& filename) const;
	void CheckProgramLinkStatus() const;
	void CheckShaderCompileStatus(unsigned shader) const;
	void Compile(const std::string& vs_code, const std::string& fs_code);
public:
	// Loads shaders from the specified files located in the 'assets/shader' directory.
	// Parameters:
	// vertexFile: The filename of the vertex shader to be loaded.
	// fragmentFile: The filename of the fragment shader to be loaded.	
	glShader(const std::string& vertexFile, const std::string& fragmentFile);
	virtual ~glShader();

	virtual void Use() const override;

	virtual void SetInt(const char* name, int val) const override;
	virtual void SetFloat(const char* name, float val) const override;

	virtual void SetMat3(const char* name, glm::mat3 const&) const override;
	virtual void SetMat4(const char* name, glm::mat4 const&) const override;

	virtual void SetVec2(const char* name, glm::vec2 const&) const override;
	virtual void SetVec3(const char* name, glm::vec3 const&) const override;
	virtual void SetVec4(const char* name, glm::vec4 const&) const override;
private:
	unsigned m_ProgramID;
};