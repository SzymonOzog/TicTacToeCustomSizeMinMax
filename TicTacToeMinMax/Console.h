#pragma once
#define NOMINMAX //no windows.h I don`t want to use your terrible min and max macros
#include <Windows.h>
class Console
{
public:
	Console() = delete;
	Console(int width, int height);
private:
	const int screenWidth;
	const int screenHeight;
	HANDLE hConsoleOut = nullptr;
	HANDLE hConsoleIn = nullptr;
	DWORD dwEvents = 0;
	DWORD dwBytesWritten = 0;
	INPUT_RECORD Input;
public:
	inline void listen() { ReadConsoleInput(hConsoleIn, &Input, 1, &dwEvents); }
	inline bool isMouseEvent() { return Input.EventType == MOUSE_EVENT; }
	inline bool isLMBEvent() {	return Input.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED; }
	inline bool isKeyEvent() { return Input.EventType == KEY_EVENT; }
	inline bool isEscEvent() { return Input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE; }
	inline COORD getMousePosition() { return Input.Event.MouseEvent.dwMousePosition; }
	inline void outputScreen(wchar_t* screen) { WriteConsoleOutputCharacter(hConsoleOut, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten); }
	inline void setCursorPosition(short x, short y) { SetConsoleCursorPosition(hConsoleOut, { x, y }); }
private:
	void setConsoleProperties();
	void setWindowSize();
	void disableWindowResizablility();
	void disableCursorVisibility();
};

