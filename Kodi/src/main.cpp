#include "pch.h"

HWND hWndButton;
HWND hWndButton2;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR nCmdLine, _In_ int nCmdShow)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MAINWINDOW";
	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(0, L"MAINWINDOW", L"Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);

	hWndButton = CreateWindowEx(0, L"BUTTON", L"Ok", WS_CHILD | WS_BORDER | WS_VISIBLE, 10, 10, 100, 50, hWnd, (HMENU)1, hInstance, nullptr);
	hWndButton2 = CreateWindowEx(0, L"BUTTON", L"OkMove", WS_CHILD | WS_BORDER | WS_VISIBLE, 100, 200, 100, 50, hWnd, (HMENU)2, hInstance, nullptr);

	MSG msg{};
	while(GetMessage(&msg, NULL, 0, 0))
	{ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		break; 
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 2)
		{
			AnimateWindow(hWnd, 1000, AW_BLEND | AW_HIDE);
			AnimateWindow(hWnd, 1000, AW_BLEND | AW_ACTIVATE);
			
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return TRUE;
}
