#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Yanked from examples/exmaple_glfw_opengl3/main.cpp
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE] = { 0 };
char live_buffer[BUFFER_SIZE] = { 0 };
char live_buffer2[BUFFER_SIZE] = { 0 };
char out_buffer[BUFFER_SIZE] = { 0 };

int EncryptFilter(ImGuiInputTextCallbackData* data) {
	if ((data->EventChar > 64 && data->EventChar < 91) || (data->EventChar > 96 && data->EventChar < 123)) {
		// In other words, [A..Z] or [a..z]. Make sure it's lowercase!
		data->EventChar = tolower(data->EventChar);
		return 0;
	}
	return 1;
}

void Encrypt(char buffer[], char out[]) {
	// Encrypt characters in buffer to out.
	int i = 0;
	while (buffer[i]) {
		// Loop ends at the end of string
		char loopedchr = ("wordle")[i % 6] - 97;
		out[i] = (char) ((loopedchr + buffer[i] + i - 97) % 26 + 97);
		i++;
	}
}

void ClearBuffer(char buffer[]) {
	// Resets buffer to '\0' until a null byte is encountered.
	int c = 0;
	while (buffer[c]) buffer[c++] = '\0';
}

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) return 1;

	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	GLFWwindow *window = glfwCreateWindow(1280, 720, "Testing", NULL, NULL);

	if (window == NULL) return 1;
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	int counter = 0;

	// So we can clear the screen every frame
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Finally done with setup (I hope)
	// Time for some real code!
	while (!glfwWindowShouldClose(window)) {
		// Keyboard & Mouse events
		glfwPollEvents();
		// Initiate new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test window");

		ImGui::Text("Totally useful text!");
		if (ImGui::Button("CLICK?")) {
			counter++;
		}
		ImGui::SameLine();
		ImGui::Text("count = %i", counter);
		ImGui::ColorEdit3("Clear color", (float *) &clear_color);

		ImGui::Text("Input text to encrypt below...");
		ImGui::InputText("To Encrypt", buffer, BUFFER_SIZE, ImGuiInputTextFlags_CallbackCharFilter, EncryptFilter);

		if (ImGui::Button("Encrypt!")) {
			Encrypt(buffer, out_buffer);
		}
		ImGui::SameLine();
		ImGui::Text("Result: %s", out_buffer);

		ImGui::Text("OR input live-encrypted text here!");
		ImGui::InputText("Live Encryption", live_buffer, BUFFER_SIZE, ImGuiInputTextFlags_CallbackCharFilter, EncryptFilter);
		// Re-Encrypt text entered, live!
		ClearBuffer(live_buffer2);
		Encrypt(live_buffer, live_buffer2);
		ImGui::Text("Live Encryption result: %s", live_buffer2);

		ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
		ImGui::End();

		// Display frame
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

