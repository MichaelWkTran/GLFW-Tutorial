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
#include "Camera.h"

void FramebufferSizeCallback(GLFWwindow* _pWindow, int _iWidth, int _iHeight);

GLfloat GLfVertices[] =
{
    //Coordinates          /**/    //Colours               /**/    Texture Coordinate
    -0.5f, 0.0f,  0.5f,    /**/    0.83f, 0.70f, 0.44f,    /**/    0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,    /**/    0.83f, 0.70f, 0.44f,    /**/    5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,    /**/    0.83f, 0.70f, 0.44f,    /**/    0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,    /**/    0.83f, 0.70f, 0.44f,    /**/    5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,    /**/    0.92f, 0.86f, 0.76f,    /**/    2.5f, 5.0f
};

GLuint GLuIndicies[]
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

const unsigned int uViewPortW = 800, uViewPortH = 800;

int main()
{
    //Initialize and Configure GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Set up Window
    GLFWwindow* pWindow = glfwCreateWindow(uViewPortW, uViewPortH, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, uViewPortW, uViewPortH);
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
    
    glEnable(GL_DEPTH_TEST);

    CTexture Texture(std::string("TestTextureTiles.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture.TextureUnit(ShaderProgram, "tex0", 0);

    CCamera Camera(uViewPortW, uViewPortH, glm::vec3(0.0f, 0.0f, 2.0f));

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShaderProgram.Activate();

        //Set up Camera
        Camera.Inputs(pWindow);
        Camera.Matrix(45.0f, 0.1f, 100.0f, ShaderProgram, "camMatrix");

        //Set up model
        Texture.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(GLuIndicies)/sizeof(int), GL_UNSIGNED_INT, 0);

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