#pragma once
#include "../Core.h"
#include <functional>
#include <unordered_map>

//记录帧按键状态是为了防止重复执行某按键逻辑

enum class KeyState
{
	None,
	Pressed,   // 本帧刚按下
	Released,  // 本帧刚松开
	Held       // 持续按住
};

class KeyBoard
{
public:
	KeyBoard(GLFWwindow* window):window(window) {}
	~KeyBoard() {}

public:
	GLFWwindow* window {nullptr};
	// 当前帧状态
	std::unordered_map<int, bool> currentState;
	// 上一帧状态
	std::unordered_map<int, bool> previousState;

	std::unordered_map<int, std::unordered_map<KeyState, std::function<void()>>> keyCallbacks;

public:
	void BindKey(int key, KeyState state,std::function<void()> func)
	{
		keyCallbacks[key][state] = func;
	}

	void ProcessInput()
	{
		//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		//{
		//	glfwSetWindowShouldClose(window, true);
		//	std::cout << "Press Esc." << "\n";
		//}
		for (auto& pair : keyCallbacks)
		{
			int key = pair.first;
			bool isPressed = glfwGetKey(window, key) == GLFW_PRESS;

			currentState[key] = isPressed;

			bool wasPressed = previousState[key];

			KeyState state = KeyState::None;

			if (isPressed && !wasPressed)
				state = KeyState::Pressed;
			else if (!isPressed && wasPressed)
				state = KeyState::Released;
			else if (isPressed && wasPressed)
				state = KeyState::Held;

			// 执行回调
			if (keyCallbacks[key].count(state))
			{
				keyCallbacks[key][state]();
			}
			previousState = currentState;
		}
	}
};
