#pragma once
#include <memory>
#include <string>
#include <windows.h>

class Screen
{
public:
	Screen();
	~Screen();

private:
	const SHORT width = 128;
	const SHORT height = 32;
	const int bufferSize = width * height;

private:
	HANDLE consoleBuffers[2];
	int bufferIndex = 0; // TODO: 타입 변경예정
	std::unique_ptr<wchar_t[]> buffer = nullptr;

public:
	void Write(const SHORT x, const SHORT y, const std::wstring& text);
	void Render();
	void Clear();

	void ShowConsoleCursor(bool bIsShow);
};
