// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"
#include "stdio.h"
#include "time.h"
#include "thread"

#define UPDATEPROGRESSID 202
#define UPDATEPROGRESSNC 302
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
HWND hWnd2;
HWND hWnd;
double rightPercentageChildWindow;

LRESULT CALLBACK    WndProcMainWindow(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcChildWindow(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	const char className1[] = "H-instance window class1";
	const char className2[] = "H-instance window class2";

	rightPercentageChildWindow = 0.1;

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

	hWnd = CreateWindowExA(0, className1, "New Title1", WS_OVERLAPPEDWINDOW,
		biggerClassX, biggerClassY, biggerClassW, biggerClassH, nullptr, nullptr, hInstance, nullptr);

	POINT biggerWindowBegin = { 0,0 };
	ClientToScreen(hWnd, &biggerWindowBegin);
	int NonClientAreaHeight = biggerWindowBegin.y - biggerClassY;
	int NonClientAreaWidthOffset = biggerWindowBegin.x - biggerClassX;

	hWnd2 = CreateWindowExA(0, className2, "New Title2", WS_CHILD,
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

	std::thread t([]() {
		
		while (1)
		{
			if (rightPercentageChildWindow >= 1.0)
			{
				break;
			}
			rightPercentageChildWindow += 0.1;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			WPARAM wParam = MAKEWPARAM(UPDATEPROGRESSID, UPDATEPROGRESSNC);
			SendMessageA(hWnd, WM_COMMAND, wParam, NULL);
		}
		
	});
	
	

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}

	t.join();

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

LRESULT CALLBACK WndProcMainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		WORD id = loword(wParam);
		WORD notificationCode = hiword(wParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM COMMAND id: %d notificationCode %d ", id, notificationCode);
		log(str);
		if (notificationCode == UPDATEPROGRESSNC)
		{
			log("MainWindow1 Update progress NC received");
			//UpdateWindow(hWnd2);
			InvalidateRect(hWnd2, NULL, true);
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
		RECT originalRect = {40,20,250,40};
		RECT progressRect = { 40,20,250,40 };
		//GetClientRect(hWnd, &outsideRect); // get the client area rectangle

		HBRUSH hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushGreen);
		Rectangle(hdc, originalRect.left, originalRect.top, originalRect.right, originalRect.bottom);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushGreen);

		HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
		hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushBlue);
		Rectangle(hdc, progressRect.left, progressRect.top, progressRect.left + (progressRect.right-progressRect.left)*rightPercentageChildWindow, progressRect.bottom);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushBlue);

		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}