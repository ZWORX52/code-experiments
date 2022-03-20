#include "main.h"

void ClearBuffer(char buffer[]) {
	// Resets buffer to '\0' until a null byte is encountered.
	int c = 0;
	while (buffer[c]) buffer[c++] = '\0';
}

char WordleEncryptionIn[BUFFER_SIZE] = { 0 };
char WordleEncryptionOut[BUFFER_SIZE] = { 0 };
char WordleDecryptionIn[BUFFER_SIZE] = { 0 };
char WordleDecryptionOut[BUFFER_SIZE] = { 0 };

int WordleEncryption::EncryptFilter(ImGuiInputTextCallbackData* data) {
	if ((data->EventChar > 64 && data->EventChar < 91) || (data->EventChar > 96 && data->EventChar < 123)) {
		// In other words, [A..Z] or [a..z]. Make sure it's lowercase!
		data->EventChar = tolower(data->EventChar);
		return 0;
	}
	return 1;
}

void WordleEncryption::Encrypt(char in[], char out[]) {
	// Encrypt characters in buffer to out.
	int i = 0;
	while (in[i]) {
		// Loop ends at the end of string
		char loopedchr = ("wordle")[i % 6] - 97;
		out[i] = (char) ((loopedchr + in[i] + i - 97) % 26 + 97);
		i++;
	}
}

void WordleEncryption::Decrypt(char in[], char out[]) {
	// Decrypt 'in' buffer to 'out' buffer.
	int i = 0;
	while (in[i]) {
		char loopedchr = ("wordle")[i % 6] - 97;
		out[i] = (char) (std::abs(in[i] - loopedchr - i - 97) % 26 + 97);
		i++;
	}
}

void WordleEncryption::UpdateWindow(bool *open) {
	ImGuiWindowFlags flags = 0;
	flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("Encryption", open, flags);

	// Redo
	ImGui::InputText("Encryption input", WordleEncryptionIn, BUFFER_SIZE, ImGuiInputTextFlags_CallbackCharFilter, EncryptFilter);
	ClearBuffer(WordleEncryptionOut);
	Encrypt(WordleEncryptionIn, WordleEncryptionOut);
	ImGui::Text("Encryption result: %s", WordleEncryptionOut);

	ImGui::InputText("Decryption input", WordleDecryptionIn, BUFFER_SIZE, ImGuiInputTextFlags_CallbackCharFilter, EncryptFilter);
	ClearBuffer(WordleDecryptionOut);
	Decrypt(WordleDecryptionIn, WordleDecryptionOut);
	ImGui::Text("Decryption result: %s", WordleDecryptionOut);

	ImGui::End();
}

