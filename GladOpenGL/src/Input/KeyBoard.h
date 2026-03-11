#pragma once
#include "../Core.h"

class KeyBoard
{
public:
	KeyBoard(GLFWwindow* window):window(window) {}
	~KeyBoard() {}

public:
	GLFWwindow* window {nullptr};

public:
	void ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
			std::cout << "Press Esc." << "\n";
		}
	}
};
