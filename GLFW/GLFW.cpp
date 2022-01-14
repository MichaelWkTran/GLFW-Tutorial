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
    //Coordinates          /**/    //Colours            /**/    Texture Coordinate    /**/    Normals
    -1.0f, 0.0f,  1.0f,	   /**/    1.0f, 1.0f, 1.0f,    /**/    0.0f, 0.0f,		      /**/    0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,	   /**/    1.0f, 1.0f, 1.0f,    /**/    0.0f, 1.0f,		      /**/    0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,    /**/    1.0f, 1.0f, 1.0f,    /**/    1.0f, 1.0f,		      /**/    0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,	   /**/    1.0f, 1.0f, 1.0f,    /**/    1.0f, 0.0f,		      /**/    0.0f, 1.0f, 0.0f
};

GLuint GLuIndices[]
{
    0, 1, 2,
    0, 2, 3
};

GLfloat GLfLightVertices[] =
{ 
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint GLuLightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
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
    
    //Set up Shaders
    //Set up Light Shader
    CShader ShaderLight("Light.vert", "Light.frag");
    CVertexArray VAOLight; VAOLight.Bind();
    CVertexBuffer VBOLight(GLfLightVertices, sizeof(GLfLightVertices));
    CElementBuffer EBOLight(GLuLightIndices, sizeof(GLuLightIndices));
    VAOLight.LinkAttribute(VBOLight, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    VAOLight.Unbind(); VBOLight.Unbind(); EBOLight.Unbind();

    glm::vec4 v4LightColour(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 v3LightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 mat4LightModel = glm::mat4(1.0f);
    mat4LightModel = glm::translate(mat4LightModel, v3LightPos);
    ShaderLight.Activate();
    glUniformMatrix4fv(glGetUniformLocation(ShaderLight.m_GLuID, "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(mat4LightModel));
    glUniform4f(glGetUniformLocation(ShaderLight.m_GLuID, "uni_v4LightColor"), v4LightColour.x, v4LightColour.y, v4LightColour.z, v4LightColour.w);
    
    //Set up Pyramid Shader
    CShader ShaderPyramid("Default.vert", "Default.frag");
    CVertexArray VAOPyramid; VAOPyramid.Bind();
    CVertexBuffer VBOPyramid(GLfVertices, sizeof(GLfVertices));
    CElementBuffer EBOPyramid(GLuIndices, sizeof(GLuIndices));
    VAOPyramid.LinkAttribute(VBOPyramid, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    VAOPyramid.LinkAttribute(VBOPyramid, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAOPyramid.LinkAttribute(VBOPyramid, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAOPyramid.LinkAttribute(VBOPyramid, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    VAOPyramid.Unbind(); VBOPyramid.Unbind(); EBOPyramid.Unbind();
    
    glm::vec3 v3PyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 mat4PyramidModel = glm::mat4(1.0f);
    mat4PyramidModel = glm::translate(mat4PyramidModel, v3PyramidPos);
    ShaderPyramid.Activate();
    glUniformMatrix4fv(glGetUniformLocation(ShaderPyramid.m_GLuID, "uni_mat4Model"), 1, GL_FALSE, glm::value_ptr(mat4PyramidModel));
    glUniform4f(glGetUniformLocation(ShaderPyramid.m_GLuID, "uni_v4LightColor"), v4LightColour.x, v4LightColour.y, v4LightColour.z, v4LightColour.w);
    glUniform3f(glGetUniformLocation(ShaderPyramid.m_GLuID, "uni_v3LightPosition"), v3LightPos.x, v3LightPos.y, v3LightPos.z);

    CTexture Texture("Planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture.TextureUnit(ShaderPyramid, "uni_samp2DTexture", 0);
    CTexture TextureSpecular("PlanksSpecular.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    Texture.TextureUnit(ShaderPyramid, "uni_samp2DSpecularTexture", 1);

    //Set up Textures
    glEnable(GL_DEPTH_TEST);

    //Set up camera
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

        //Set up Camera
        Camera.Inputs(pWindow);
        Camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
        
        //What shaders the program is going to use
        //Set up Pyramid
        ShaderPyramid.Activate();
        glUniform3f(glGetUniformLocation(ShaderPyramid.m_GLuID, "uni_v3CameraPosition"), Camera.m_v3Position.x, Camera.m_v3Position.y, Camera.m_v3Position.z);
        Camera.Matrix(ShaderPyramid, "uni_mat4CameraMatrix");
        Texture.Bind(); TextureSpecular.Bind(); VAOPyramid.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(GLuIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
        
        //Set up Light
        ShaderLight.Activate();
        Camera.Matrix(ShaderLight, "uni_mat4CameraMatrix");
        VAOLight.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(GLuLightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        //Check and call events and swap the buffers
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    VAOPyramid.Delete(); VBOPyramid.Delete(); EBOPyramid.Delete(); Texture.Delete(); ShaderPyramid.Delete();
    VAOLight.Delete(); VBOLight.Delete(); EBOPyramid.Delete(); ShaderLight.Delete();
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}