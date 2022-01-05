#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Texture.h"

void FramebufferSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight);

GLfloat GLfVertices[] =
{
    //Coordinates          /**/    //Colours            /**/    Texture Coordinate
    -0.5f, -0.5f, 0.0f,    /**/    1.0f, 0.0f, 0.0f,    /**/    0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 0.0f,    /**/    0.0f, 1.0f, 0.0f,    /**/    0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 0.0f,    /**/    0.0f, 0.0f, 1.0f,    /**/    1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 0.0f,    /**/    1.0f, 1.0f, 1.0f,    /**/    1.0f, 0.0f  // Lower right corner
};

GLuint GLuIndicies[]
{
    0, 2, 1, // Upper triangle
    0, 3, 2  // Lower triangle
};

int main()
{
    //Initialize and Configure GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Set up Window
    GLFWwindow* pWindow = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
    if (pWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //???
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 800);
    glfwSetFramebufferSizeCallback(pWindow, FramebufferSizeCallback);
    
    //Set up Shader
    CShader ShaderProgram("Default.vert", "Default.frag");

    CVertexArray VAO1;
    VAO1.Bind();

    CVertexBuffer VBO1(GLfVertices, sizeof(GLfVertices));
    CElementBuffer EBO1(GLuIndicies, sizeof(GLuIndicies));

    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    GLuint uniScale = glGetUniformLocation(ShaderProgram.m_GLuID, "scale");

    //Texture
    CTexture Texture(std::string("TestTexture.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture.TextureUnit(ShaderProgram, "tex0", 0);

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
        glUniform1f(uniScale, 1.5f);
        Texture.Bind();
        VAO1.Bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Check and call events and swap the buffers
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    Texture.Delete();
    ShaderProgram.Delete();
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}