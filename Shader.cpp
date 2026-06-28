#include<iostream>
#include<sstream>
#include<fstream>
#include "Shader.h"	
#include <glad/gl.h>

// helper functions
using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath){
    string vertexFilePath = ShaderSource(vertexPath);
    string fragmentFilePath = ShaderSource(fragmentPath);

    vertexID = CompileShader(GL_VERTEX_SHADER, vertexFilePath);
    fragmentID = CompileShader(GL_FRAGMENT_SHADER, fragmentFilePath);

    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    // if things go wrong...
    // for vertexID and fragmentID compileShader handles everything 
    int success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        string type = "PROGRAM"; 
        char infoLog[1024];
        glGetProgramInfoLog(programID, 1024, NULL, infoLog);
        cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);


};

Shader::~Shader() {
    // check to ensure a valid programID still exist
    if (programID != 0) {
        glDeleteProgram(programID);
    }
}

void Shader::Use() const {
    glUseProgram(programID); 
}

void Shader::Unbind() const {
    glUseProgram(0);
}


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

string Shader::ShaderSource(const string & file_name) {
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
