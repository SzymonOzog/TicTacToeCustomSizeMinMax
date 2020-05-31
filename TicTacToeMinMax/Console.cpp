#include "Console.h"
#include <string>

Console::Console(int width, int height) : nScreenWidth(width), nScreenHeight(height) 
{
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	setConsoleProperties();
}

void Console::setConsoleProperties()
{
	setWindowSize();
	disableWindowResizablility();
	disableCursorVisibility();
	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

void Console::setWindowSize()
{
	std::string sConsoleProps = "MODE CON COLS=" + std::to_string(nScreenWidth) + " LINES=" + std::to_string(nScreenHeight);
	system(sConsoleProps.c_str());
}

void Console::disableWindowResizablility()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void Console::disableCursorVisibility()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOut, &cursorInfo);
}