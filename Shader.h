#pragma once
#ifndef SHADER_H
#define SHADER_H


#include<string>
using namespace std;

unsigned int CompileShader(unsigned int type, const std::string& source);
//unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

class Shader {
public:
	unsigned int programID;
	unsigned int vertexID;
	unsigned int fragmentID;
	Shader(const char* vertexPath, const char* fragmentPath);
	string ShaderSource(const string& file_name);
	~Shader();

	void Use() const;

	void Unbind() const;


	// Utilities
	/*void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetMat4(const std::string& name, const float* matrixData) const;*/


};

#endif // SHADER_H
