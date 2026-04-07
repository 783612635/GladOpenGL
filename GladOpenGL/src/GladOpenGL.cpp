#include <iostream>
#include "Input/KeyBoard.h" 
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include <windows.h>
#include <filesystem>

std::string exeDir;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

float vertices_box[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] =
{0,1,2,
0,2,3};

float texCoord[] =
{ 0.0f,0.0f,
    1.0f,0.0f,
    0.5f,1.0f
};

int main()
{
    //初始化 glfw 并声明其版本，这里为3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Mac OS X系统需要额外补充
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GladOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1);//开启垂直同步

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    VertexLayout layout;
    layout.Push<float>(0, 3);
    layout.Push<float>(1, 2);
    //layout.Push<float>(2, 2);

    Mesh mesh(vertices_box, sizeof(vertices_box), indices, sizeof(indices), layout);
    Texture tex("res/pics/container.jpg",GL_TEXTURE_2D);

    tex.Bind();

    Shader shader("res/shader/vertex.vs", "res/shader/fragment.fs");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    KeyBoard keyBoard(window);
    keyBoard.BindKey(GLFW_KEY_ESCAPE, KeyState::Pressed,[&]() {
        	glfwSetWindowShouldClose(window, true);
	        std::cout << "Press Esc." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_DOWN, KeyState::Pressed,[&]() {
        std::cout << "Press DownArrow." << "\n" ;
        });
    keyBoard.BindKey(GLFW_KEY_UP, KeyState::Pressed,[&]() {
        std::cout << "Press UpArrow." << "\n" ;
        });

    int frameCount = 0;
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        frameCount++;
        double currentTime = glfwGetTime();
        // 每秒更新一次
        if (currentTime - lastTime >= 1.0)
        {
            printf("FPS: %d\n", frameCount);

            frameCount = 0;
            lastTime += 1.0;
        }

        keyBoard.ProcessInput();

        //glClearColor来设置清空屏幕所用的颜色。当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。在这里，我们将屏幕设置为了类似黑板的深蓝绿色。
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0, 0.0));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);

        shader.Use();
        //float timeValue = glfwGetTime();
        //float redValue = sin(timeValue) / 2.0f + 0.5f;
        //shader.SetUniform4f("setColor", redValue, 0.f, 0.f, 1.f);
        //float offsetValue = sin(timeValue) / 2.0f;
        //shader.SetUniformMat4("Model", model);
        //shader.SetUniformMat4("View", view);
        //shader.SetUniformMat4("Projection", projection);
        //shader.SetUniform1i("ourTexture", 0);
        
        //mesh.DrawElements();
        //mesh.DrawArrays(0, 36);

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = i == 0 ? (20.0f * (i + 1)) : 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            if (i == 0 || i % 3 == 0)
            {
                
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            shader.SetUniformMat4("Model", model);
            shader.SetUniformMat4("View", view);
            shader.SetUniformMat4("Projection", projection);
            shader.SetUniform1i("ourTexture", 0);

            mesh.DrawArrays( 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.DeleteShader();
    glfwTerminate();

    std::cout << "Exit..." << "\n";
    return 0;
}