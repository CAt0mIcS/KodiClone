#include "pch.h"
#include "Window.h"

#include "Kodi/Exceptions/WinAPIException.h"


Window::Window()
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_ClassName;
	wc.hIconSm = 0;
	
	RegisterClassEx(&wc);
	m_hWnd = CreateWindowEx(0, m_ClassName, L"Kodi", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, this);
	if (!m_hWnd)
		KODI_THROW_LAST_WINAPI_EXCEPTION();

	ShowWindow(m_hWnd, SW_MAXIMIZE);
}

std::optional<int> Window::ProcessMessage()
{
	MSG msg{};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (int)msg.wParam;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}

LRESULT Window::HandleMessageSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		Window* window = (Window*)pCreate->lpCreateParams;

		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)HandleMessagePass);

		return window->HandleMessage(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMessagePass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	return window->HandleMessage(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(35, 38, 40)));
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


