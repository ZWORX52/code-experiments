#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#define BUFFER_SIZE 1024

// Function prototypes
namespace WordleEncryption {
	int EncryptFilter(ImGuiInputTextCallbackData* data);
	void Encrypt(char in[], char out[]);
	void UpdateWindow(bool *open);
}

#endif//MAIN_H_INCLUDED

