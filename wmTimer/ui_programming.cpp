// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"
#include "stdio.h"
#include "time.h"

#define biggerClassX 100
#define biggerClassY 200
#define biggerClassW 1000
#define biggerClassH 500
#define smallerClassW 400
#define smallerClassH 100

#define logPrefix "UiProgramming "
#define loword(a) ((WORD)(a))
#define hiword(a) ((WORD)(((DWORD)(a) >> 16) & 0xFFFF))

void log(const char* str)
{
	char data[256];
	strcpy(data, logPrefix);
	strcat(data, str);
	OutputDebugStringA(data);
}


HINSTANCE hInst;
const UINT timer_id = 10;

LRESULT CALLBACK    WndProcMainWindow(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcChildWindow(HWND, UINT, WPARAM, LPARAM);

VOID __stdcall MyTimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	if (WM_TIMER == uMsg) {
		if (idEvent == timer_id) {
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer, 80, "Now time is %I:%M:%S%p.", timeinfo);
			SetWindowTextA(hWnd, buffer);
		}
	}
}


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
	wcex.lpfnWndProc = WndProcMainWindow;
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
		log("class 1 registered\n");
	}
	else {
		log("class 1 not registered\n");
	}

	WNDCLASSEXA wcex2 = {};

	wcex2.cbSize = sizeof(wcex2);
	wcex2.style = CS_HREDRAW | CS_VREDRAW;
	wcex2.lpfnWndProc = WndProcChildWindow;
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
		log("class 2 registered\n");
	}
	else {
		log("class 2 not registered\n");
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

	SetTimer(hWnd, timer_id, 1000, (TIMERPROC)MyTimerProc);

	HACCEL hAccelTable = NULL;

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}

	UnregisterClassA(className1, hInst);
	UnregisterClassA(className2, hInst);
	KillTimer(hWnd, timer_id);

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

LRESULT CALLBACK WndProcMainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{

	}
	break;
	case WM_TIMER:
	{
		case timer_id:
		{
			log("timmer event received");
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM LBUTTON DOWN x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_LBUTTONUP:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM LBUTTON UP x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM RBUTTON DOWN x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_RBUTTONUP:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM RBUTTON UP x: %d y: %d", xPos, yPos);
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

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		log("MainWindow1 Win proc WM_Destroy\n");
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcChildWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{

	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "ChildWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_MOUSELEAVE:
	{

	}
	break;
	case WM_LBUTTONDOWN:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "ChildWindow1 WM LBUTTON DOWN x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_LBUTTONUP:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "ChildWindow1 WM LBUTTON UP x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[256];
		sprintf_s(str, "ChidWindow1 WM RBUTTON DOWN x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_RBUTTONUP:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		char str[100];
		sprintf_s(str, "ChidWindow1 WM RBUTTON UP x: %d y: %d", xPos, yPos);
		log(str);
	}
	break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT outsideRect = {};
		GetClientRect(hWnd, &outsideRect); // get the client area rectangle

		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}