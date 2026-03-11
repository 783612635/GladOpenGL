#include <iostream>
#include "Input/KeyBoard.h" 
#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float vertices[] = {
    -0.5f,  -0.5f,  
    0.5f,   -0.5f,  
    0.5f,   0.5f,  
    -0.5f,  0.5f
};

unsigned int indices[] = {0,1,2,
2,3,0};

std::string vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

std::string fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

    //开始渲染之前还有一件重要的事情要做，
    //我们必须告诉OpenGL渲染窗口的尺寸大小，
    //即视口(Viewport)，这样OpenGL才只能
    //知道怎样根据窗口大小显示数据和坐标。
    //注意，处理过的OpenGL坐标范围只为-1到1，
    //因此我们事实上将(-1到1)范围内的坐标映射到(0, 800)和(0, 600)。
    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    Shader VS(GL_VERTEX_SHADER);
    VS.GetSourceAndCompile(vertexShaderSource);

    Shader FS(GL_FRAGMENT_SHADER);
    FS.GetSourceAndCompile(fragmentShaderSource);

    ShaderProgram sp;
    sp.AttachShader(VS.shaderId);
    sp.AttachShader(FS.shaderId);
    sp.LinkProgarm();

    VS.DeleteShader();
    FS.DeleteShader();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        glUseProgram(sp.id);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    sp.DeleteProgram();
    glfwTerminate();

    std::cout << "Exit..." << "\n";
    return 0;
}