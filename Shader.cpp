#include<iostream>
#include<sstream>
#include<fstream>
#include "Shader.h"	
#include <glad/gl.h>

// helper functions
using namespace std;

//Shader::Shader(const char* vertexPath, const char* fragmentPath){
//    string vertexFilePath = ShaderSource(vertexPath);
//    string fragmentFilePath = ShaderSource(fragmentPath);
//
//    
//
//};
unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int ID = glCreateShader(type);
	const char* src= source.c_str();

	glShaderSource(ID, 1, &src, nullptr);
	glCompileShader(ID);

	int success;
	char infoLog[1024];
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ID, 1024, nullptr, infoLog); // logs info
		std::cerr << "COMPILATION_FAILED of type: "
			<< (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "\n"
			<< infoLog << std::endl;
		glDeleteShader(ID);  // log and delete
		return 0;

	}

	return ID;

}

string ShaderSource(const string& file_name) {
    ifstream ShaderFile;
    stringstream ShaderStream;

    ShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        ShaderFile.open(file_name);
        ShaderStream << ShaderFile.rdbuf();
        ShaderFile.close();


    }
    catch (const exception& e) { // FIX: Catch by const reference
        cerr << "ERROR: Something went wrong while reading the shader: " << file_name << "\n";
        cerr << "Details: " << e.what() << "\n"; // Optional: Prints the exact OS error
        return "";
    }

    string shaderCode = ShaderStream.str();
    // Safety check: Did we actually get code?
    if (shaderCode.empty()) {
        cerr << "ERROR: Shader file was empty: " << file_name << "\n";
    }

    return shaderCode;
}
