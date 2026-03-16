#include <iostream>
#include "Input/KeyBoard.h" 
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include <windows.h>
#include <filesystem>

std::string exeDir;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float vertices[] = {
    -0.5f,  -0.5f,  
    0.5f,   -0.5f,  
    0.5f,   0.5f,  
    -0.5f,  0.5f,
    0.5f,   0.5f,
    -0.2f,  -0.4f
};

unsigned int indices[] =
{0,1,2,
2,3,0};

int main()
{
    //初始化 glfw 并声明其版本，这里为3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Mac OS X系统需要额外补充
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "GladOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);//开启垂直同步

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    VertexLayout layout;
    layout.Push<float>(0, 2);

    Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices), layout);

    Shader shader("res/shader/vertex.vs", "res/shader/fragment.fs");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    KeyBoard keyBoard(window);

    int fps = 0;

    while (!glfwWindowShouldClose(window))
    {
        fps++;
        keyBoard.ProcessInput();

        //glClearColor来设置清空屏幕所用的颜色。当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。在这里，我们将屏幕设置为了类似黑板的深蓝绿色。
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清屏，glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。
        // 由于现在我们只关心颜色值，所以我们只清空颜色缓冲。
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        float timeValue = glfwGetTime();
        float redValue = sin(timeValue) / 2.0f + 0.5f;
        shader.SetUniform4f("setColor", redValue, 0.f, 0.f, 1.f);
        mesh.DrawElements();
        mesh.UnBindVAO();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.DeleteShader();
    glfwTerminate();

    std::cout << "Exit..." << "\n";
    return 0;
}