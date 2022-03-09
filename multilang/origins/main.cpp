#include <stdio.h>

// Yanked from examples/exmaple_glfw_opengl3/main.cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error %d: %s", error, description);
}

int main() {
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) return 1;
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Testing", NULL, NULL);

	if (window == NULL) return 1;
}

