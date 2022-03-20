#include "main.h"

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

void EncryptWindow(bool *open) {
	ImGuiWindowFlags flags = 0;
	flags |= ImGuiWindowFlags_MenuBar;
	flags |= ImGuiWindowFlags_NoCollapse;

	// Basically main for this subprogram.
	ImGui::Begin("Encryption", open, flags);

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

	ImGui::End();
}

