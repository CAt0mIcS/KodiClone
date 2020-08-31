#pragma once

#include <optional>
#include "Kodi/Exceptions/KodiException.h"


class Window
{
public:
	/**
	* Constructor for the Window
	*/
	Window();

	/**
	* Getter for HWND
	* 
	* @returns the native HWND window
	*/
	HWND GetNativeWindow() const { return m_hWnd; }

	/**
	* Uses PeekMessage to translate and dispatch messages
	* 
	* @returns the exit code if WM_QUIT was received, an empty optional otherwise
	*/
	static std::optional<int> ProcessMessage();

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMessagePass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HWND m_hWnd;
	static constexpr const wchar_t* const m_ClassName = L"MAINWINDOWCLASS";
};

