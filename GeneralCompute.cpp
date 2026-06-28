#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>   // NEEDED FOR FILES
#include <sstream>   // NEEDED FOR STRINGS
#include "Shader.h"

using namespace std;

//string ShaderSource(const string& file_name) {
//    ifstream ShaderFile;
//    stringstream ShaderStream;
//
//    ShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
//    try {
//        ShaderFile.open(file_name);
//        ShaderStream << ShaderFile.rdbuf();
//        ShaderFile.close();
//
//            
//    }
//    catch (const exception& e) { // FIX: Catch by const reference
//        cerr << "ERROR: Something went wrong while reading the shader: " << file_name << "\n";
//        cerr << "Details: " << e.what() << "\n"; // Optional: Prints the exact OS error
//        return "";
//    }
//
//    string shaderCode = ShaderStream.str();
//    // Safety check: Did we actually get code?
//    if (shaderCode.empty()) {
//        cerr << "ERROR: Shader file was empty: " << file_name << "\n";
//    }
//
//    return shaderCode;  
//}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "GeneralCompute_1.0.0", NULL, NULL);
    if (window == NULL) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD" << endl;
        return -1;
    }



   

    //  fragment Shader 
   /* const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange color\n"
        "}\0";*/

    Shader newShader("D:\\GeneralCompute\\GeneralCompute\\Shaders\\vertex.vert", "D:\\GeneralCompute\\GeneralCompute\\Shaders\\FragmentShader.frag");
    // Set up Vertex Data and Buffers 
    float vertices[] = {
        // Triangle 1 (Bottom-Left half)
        -0.5f, -0.3f, 0.0f,  // Bottom-Left
         0.5f, -0.5f, 0.0f,  // Bottom-Right
        -0.5f,  0.5f, 0.0f,  // Top-Left

        // Triangle 2 (Top-Right half)
         0.5f, -0.5f, 0.0f,  // Bottom-Right
         0.5f,  0.5f, 0.0f,  // Top-Right
        -0.5f,  0.5f, 0.0f   // Top-Left
    };


    // geometry setup 
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind VAO first, then bind and set vertex buffers, then configure attributes
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffers to prevent accidental modification 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        newShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}