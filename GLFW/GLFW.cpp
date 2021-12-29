#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

void FramebufferSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight);

GLfloat GLfVertices[] =
{
    //Coordinates                                      /**/    //Colours             /**/    
    -0.5f,  -0.5f * sqrtf(3.0f) / 3.0f,       0.0f,    /**/    0.8f, 0.3f,  0.02f,    /**/    // Lower left corner       
    0.5f,   -0.5f * sqrtf(3.0f) / 3.0f,       0.0f,    /**/    0.8f, 0.3f,  0.02f,    /**/    // Lower right corner      
    0.0f,   0.5f * sqrtf(3.0f) * 2.0f / 3.0f, 0.0f,    /**/    1.0f, 0.6f,  0.32f,    /**/    // Upper corner            
    -0.25f, 0.5f * sqrtf(3.0f) / 6.0f,        0.0f,    /**/    0.9f, 0.45f, 0.17f,    /**/    // Inner Upper left corner 
    0.25f,  0.5f * sqrtf(3.0f) / 6.0f,        0.0f,    /**/    0.9f, 0.45f, 0.17f,    /**/    // Inner Upper right corner
    0.0f,   -0.5f * sqrtf(3.0f) / 3,          0.0f,    /**/    0.8f, 0.3f,  0.02f     /**/    // Inner Lower corner      
};

GLuint GLuIndicies[]
{
    0, 3, 5, //Lower left triangle
    3, 2, 4, //Lower right triangle
    5, 4, 1  //Upper triangle
};

int main()
{
    //Initialize and Configure GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Set up Window
    GLFWwindow* pWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (pWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(pWindow, FramebufferSizeCallback);
    
    //Set up Shader
    CShader ShaderProgram("Default.vert", "Default.frag");

    CVertexArray VAO1;
    VAO1.Bind();

    CVertexBuffer VBO1(GLfVertices, sizeof(GLfVertices));
    CElementBuffer EBO1(GLuIndicies, sizeof(GLuIndicies));

    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    GLuint uniID = glGetUniformLocation(ShaderProgram.m_GLuID, "scale");

    //Render Loop
    while (!glfwWindowShouldClose(pWindow))
    {
        //Input
        if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(pWindow, true);
        }

        //Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();
        glUniform1f(uniID, 1.5f);
        VAO1.Bind();
        
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        //Check and call events and swap the buffers
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}