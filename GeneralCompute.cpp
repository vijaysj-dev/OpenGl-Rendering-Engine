#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>   // NEEDED FOR FILES
#include <sstream>   // NEEDED FOR STRINGS
#include "Shader.h"
#include<vector>
using namespace std;



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



    Shader newShader("D:\\GeneralCompute\\GeneralCompute\\Shaders\\vertex.vert", "D:\\GeneralCompute\\GeneralCompute\\Shaders\\FragmentShader.frag");
    // Set up Vertex Data and Buffers 
     vector<float> vertices= {
        // triangle 1 (Bottom-Left half)
        -0.5f, -0.5f, 0.0f,  // Bottom-Left     0,1,2
         0.5f, -0.5f, 0.0f,  // Bottom-Right    3,4,5
        -0.5f,  0.5f, 0.0f,  // Top-Left        6,7,8

        // triangle 2 (Top-Right half)
         0.5f, -0.5f, 0.0f,  // Bottom-Right    9,10,11
         0.5f,  0.5f, 0.0f,  // Top-Right       12,13,14
        -0.5f,  0.5f, 0.0f   // Top-Left        15,16,17
    };

    //scaling
    float scale = 0.3f;
    vertices[0] = scale+vertices[0];
    vertices[9] = vertices[9] - scale;
    vertices[3] = vertices[3] - scale;

    vertices[6] = scale + vertices[6];
    vertices[15] = scale + vertices[15];

    vertices[12] = vertices[12] - scale;


    //
    vertices[1] = scale + vertices[1];
    vertices[4] = scale + vertices[4];
    vertices[10] = scale + vertices[10];

    vertices[7] = vertices[7] - scale;
    vertices[13] = vertices[13] - scale;
    vertices[16] = vertices[16] - scale;

     
    // geometry setup 
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind VAO first, then bind and set vertex buffers, then configure attributes
    glBindVertexArray(VAO);
   

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind buffers to prevent accidental modification .... good 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    float direction = 0.001f;
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        if (vertices[0] >= 1.0f) {
            direction = -0.001f;
        }
        else if (vertices[0] <= -1.0f) {
            direction = 0.001f;
        }

     
        for (int i = 0; i < 18; i += 3) {
            vertices[i] += direction;
        }


       


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw it genius!!!!......
        newShader.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}