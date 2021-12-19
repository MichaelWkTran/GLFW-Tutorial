#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char* pVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* pFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
    
    //Set up Shaders
    GLuint GLuVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GLuVertexShader, 1, &pVertexShaderSource, NULL);
    glCompileShader(GLuVertexShader);

    GLuint GLuFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(GLuFragmentShader, 1, &pFragmentShaderSource, NULL);
    glCompileShader(GLuFragmentShader);

    GLuint GLuShaderProgram = glCreateProgram();

    glAttachShader(GLuShaderProgram, GLuVertexShader);
    glAttachShader(GLuShaderProgram, GLuFragmentShader);

    glLinkProgram(GLuShaderProgram);

    glDeleteShader(GLuVertexShader);
    glDeleteShader(GLuFragmentShader);

    //Set up verticies
    GLfloat GLfVertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //Set up Vertex Buffer
    GLuint GLuVertexArray, GLuVertexBuffer;

    glGenVertexArrays(1, &GLuVertexArray);
    glGenBuffers(1, &GLuVertexBuffer);
    
    glBindVertexArray(GLuVertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, GLuVertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfVertices), GLfVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
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
        glUseProgram(GLuShaderProgram);
        glBindVertexArray(GLuVertexArray);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Check and call events and swap the buffers
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &GLuVertexArray);
    glDeleteBuffers(1, &GLuVertexBuffer);
    glDeleteProgram(GLuShaderProgram);
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}