// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"
#include "stdio.h"

#define biggerClassX 100
#define biggerClassY 200
#define biggerClassW 1000
#define biggerClassH 500
#define smallerClassW 400
#define smallerClassH 100

HINSTANCE hInst;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc2(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	const char className1[] = "H-instance window class1";
	const char className2[] = "H-instance window class2";

	WNDCLASSEXA wcex = {};

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = className1;
	wcex.hIconSm = nullptr;

	int x = RegisterClassExA(&wcex);

	if (x)
	{
		OutputDebugStringA("class 1 registered\n");
	}
	else {
		OutputDebugStringA("class 1 not registered\n");
	}

	WNDCLASSEXA wcex2 = {};

	wcex2.cbSize = sizeof(wcex2);
	wcex2.style = CS_HREDRAW | CS_VREDRAW;
	wcex2.lpfnWndProc = WndProc2;
	wcex2.cbClsExtra = 0;
	wcex2.cbWndExtra = 0;
	wcex2.hInstance = hInstance;
	wcex2.hIcon = nullptr;
	wcex2.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex2.lpszMenuName = nullptr;
	wcex2.lpszClassName = className2;
	wcex2.hIconSm = nullptr;

	int y = RegisterClassExA(&wcex2);

	if (y)
	{
		OutputDebugStringA("class 2 registered\n");
	}
	else {
		OutputDebugStringA("class 2 not registered\n");
	}

	hInst = hInstance;

	HWND hWnd = CreateWindowExA(0, className1, "New Title1", WS_OVERLAPPEDWINDOW,
		biggerClassX, biggerClassY, biggerClassW, biggerClassH, nullptr, nullptr, hInstance, nullptr);

	POINT biggerWindowBegin = { 0,0 };
	ClientToScreen(hWnd, &biggerWindowBegin);
	int NonClientAreaHeight = biggerWindowBegin.y - biggerClassY;
	int NonClientAreaWidthOffset = biggerWindowBegin.x - biggerClassX;

	HWND hWnd2 = CreateWindowExA(0, className2, "New Title2", WS_CHILD,
		(biggerClassW - NonClientAreaWidthOffset) - smallerClassW, (biggerClassH - NonClientAreaHeight) - smallerClassH, smallerClassW, smallerClassH, hWnd, nullptr, hInstance, nullptr);

	if (!hWnd || !hWnd2)
	{
		return FALSE;
	}

	ShowWindow(hWnd, TRUE);
	UpdateWindow(hWnd);

	ShowWindow(hWnd2, TRUE);
	UpdateWindow(hWnd2);

	HACCEL hAccelTable = NULL;

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}

	UnregisterClassA(className1, hInst);
	UnregisterClassA(className2, hInst);

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

void DrawRect(HDC hdc, RECT rect)
{
	HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushYellow);

	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hdc, hBrushInitial);
	DeleteObject(hBrushYellow);


	SetBkMode(hdc, TRANSPARENT);
	HFONT newFont = CreateFontA(14, 0, 0, 0, 700, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman");
	HFONT initialFont = (HFONT)SelectObject(hdc, newFont);

	SetTextColor(hdc, RGB(0, 0, 0)); // Setting black color
	
	DrawTextA(hdc, "YOLO", -1, &rect, DT_CENTER);

	SelectObject(hdc, initialFont);
	DeleteObject(newFont);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		
	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming MainWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming MainWindow1 WM LBUTTON DOWN x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_LBUTTONUP:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming MainWindow1 WM LBUTTON UP x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming MainWindow1 WM RBUTTON DOWN x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_RBUTTONUP:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming MainWindow1 WM RBUTTON UP x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT outsideRect = {};
		GetClientRect(hWnd, &outsideRect); // get the client area rectangle

		HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushRed);
		Rectangle(hdc, outsideRect.left, outsideRect.top, outsideRect.right, outsideRect.bottom);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushRed);
		
		RECT topRightRect = { biggerClassW - smallerClassW, 0 , outsideRect.right, smallerClassH};
		DrawRect(hdc, topRightRect);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		OutputDebugStringA("UiProgramming MainWindow1 Win proc 1 WM_Destroy\n");
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{

	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming ChildWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_MOUSELEAVE:
	{
		
	}
	break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming ChildWindow1 WM LBUTTON DOWN x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_LBUTTONUP:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming ChildWindow1 WM LBUTTON UP x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[256];
		sprintf_s(str, "UiProgramming ChidWindow1 WM RBUTTON DOWN x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_RBUTTONUP:
	{
		WORD xPos = LOWORD(lParam);
		WORD yPos = HIWORD(lParam);
		char str[100];
		sprintf_s(str, "UiProgramming ChidWindow1 WM RBUTTON UP x: %d y: %d", xPos, yPos);
		OutputDebugStringA(str);
	}
	break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT outsideRect = {};
		GetClientRect(hWnd, &outsideRect); // get the client area rectangle

		DrawRect(hdc, outsideRect);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		OutputDebugStringA("UiProgramming Win proc 2 WM_Destroy\n");
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}