#include <iostream>
#include "Input/KeyBoard.h" 
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include "Renderer/Camera.h"
#include <windows.h>
#include <filesystem>

unsigned int windowWidth = 1920;
unsigned int windowHeight = 1080;

// 初始化相机：位置(0,0,3)，WorldUp(0,1,0)，Yaw(-90.0)
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = windowWidth / 2;
float lastY = windowHeight / 2;

bool firstMouse = true;

std::string exeDir;

float fov = 30.f;

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float vertices[] = {
    //     ---- 位置 ---- 
-0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    -0.5f,  0.5f, -0.5f,  
    -0.5f, -0.5f, -0.5f,  
};

float vertices_box[] = {
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    // 前序列 (Positive Z)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    // 左序列 (Negative X)
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    // 右序列 (Positive X)
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     // 下序列 (Negative Y)
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

     // 上序列 (Positive Y)
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

unsigned int indices[] =
{0,1,2,
0,2,3};

float texCoord[] =
{ 0.0f,0.0f,
    1.0f,0.0f,
    0.5f,1.0f
};

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GladOpenGL", NULL, NULL);
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

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    VertexLayout layout;
    layout.Push<float>(0, 3);
    layout.Push<float>(1, 3);
    layout.Push<float>(2, 2);

    Mesh mesh(vertices_box, sizeof(vertices_box), indices, sizeof(indices), layout);
    Texture tex("res/pics/container.jpg",GL_TEXTURE_2D);
    tex.Bind();
    Shader shader("res/shader/vertex.vs", "res/shader/fragment.fs");

    VertexLayout light_layout;
    light_layout.Push<float>(0, 3);
    light_layout.Push<float>(1, 3);
    light_layout.Push<float>(2, 2);
    Mesh lightBox(vertices_box, sizeof(vertices_box), indices, sizeof(indices), light_layout);
    Shader lightShader("res/shader/lightVer.vs", "res/shader/lightFrag.fs");

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

    float cameraSpeed = 0.05f;

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
    keyBoard.BindKey(GLFW_KEY_S, KeyState::Pressed, [&]() {
        camera.Position -= cameraSpeed * camera.Front;
        std::cout << "Press s." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_W, KeyState::Pressed, [&]() {
        camera.Position += cameraSpeed * camera.Front;
        std::cout << "Press w." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_A, KeyState::Pressed, [&]() {
        camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
        std::cout << "Press a." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_D, KeyState::Pressed, [&]() {
        camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
        std::cout << "Press d." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_S, KeyState::Held, [&]() {
        camera.Position -= cameraSpeed * camera.Front;
        std::cout << "Press s." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_W, KeyState::Held, [&]() {
        camera.Position += cameraSpeed * camera.Front;
        std::cout << "Press w." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_A, KeyState::Held, [&]() {
        camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
        std::cout << "Press a." << "\n";
        });
    keyBoard.BindKey(GLFW_KEY_D, KeyState::Held, [&]() {
        camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
        std::cout << "Press d." << "\n";
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

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightShader.Use();

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        glm::mat4 view = camera.GetViewMatrix();
        //camera.zoom -> FOV
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / windowHeight, 0.1f, 100.0f);

        lightShader.SetUniformMat4("Model", lightModel);
        lightShader.SetUniformMat4("View", view);
        lightShader.SetUniformMat4("Projection", projection);
        lightShader.SetUniform3f("lightPos", lightPos);
        lightBox.DrawArrays(0,36);

        shader.Use();

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
            shader.SetUniform4f("lightColor", 1.0,1.0,1.0,1.0);

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