// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"
#include "stdio.h"
#include <thread>

#define UPDATEPROGRESSID 203
#define UPDATEPROGRESSNC 303
#define button1ID 1001
#define LBUTTONCLICKID 202
#define LBUTTONCLICKNC 302
#define biggerClassX 100
#define biggerClassY 200
#define biggerClassW 1000
#define biggerClassH 500
#define smallerClassW 400
#define smallerClassH 200
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

	size_t y = RegisterClassExA(&wcex2);

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
	size_t NonClientAreaHeight = biggerWindowBegin.y - biggerClassY;
	size_t NonClientAreaWidthOffset = biggerWindowBegin.x - biggerClassX;

	hWnd2 = CreateWindowExA(0, className2, "New Title2", WS_CHILD,
		(biggerClassW - NonClientAreaWidthOffset) - smallerClassW, (biggerClassH - NonClientAreaHeight) - smallerClassH, smallerClassW, smallerClassH, hWnd, nullptr, hInstance, nullptr);

	HWND hWnd3 = CreateWindowExA(0, "BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		0, (biggerClassH - NonClientAreaHeight) - smallerClassH, smallerClassW, smallerClassH, hWnd, HMENU(button1ID), (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), nullptr);

	if (!hWnd || !hWnd2 || !hWnd3)
	{
		return FALSE;
	}

	ShowWindow(hWnd, TRUE);
	UpdateWindow(hWnd);

	ShowWindow(hWnd2, TRUE);
	UpdateWindow(hWnd2);

	ShowWindow(hWnd3, TRUE);
	UpdateWindow(hWnd3);

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
			SendMessageA(hWnd2, WM_COMMAND, wParam, NULL);
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

void AddText(HDC hdc, size_t x, size_t y, size_t xText, size_t yText)
{
	SetBkMode(hdc, TRANSPARENT);
	HFONT newFont = CreateFontA(14, 0, 0, 0, 700, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman");
	HFONT initialFont = (HFONT)SelectObject(hdc, newFont);

	RECT rect = { x - 50, y - 10, x + 50, y + 10 };

	SetTextColor(hdc, RGB(0, 0, 0)); // Setting black color
	char str[256];
	sprintf_s(str, "x: %zu y: %zu", xText, yText);
	DrawTextA(hdc, str, -1, &rect, DT_CENTER);

	SelectObject(hdc, initialFont);
	DeleteObject(newFont);
}

void DrawRect(HDC hdc, RECT rect, bool isInsideRect, size_t xText, size_t yText)
{
	if (isInsideRect)
	{
		HBRUSH hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushGreen);
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushGreen);
		size_t xCenter = (rect.right - rect.left) / 2;
		size_t yCenter = (rect.bottom - rect.top) / 2;
		AddText(hdc, rect.left + xCenter, rect.top + yCenter, xText, yText);
	}
	else
	{
		HBRUSH hBrushYellow = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushYellow);
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushYellow);
	}

	RECT originalRect = { rect.left + 40, rect.top + 20, rect.left + 250, rect.top + 40 };
	RECT progressRect = { rect.left + 40, rect.top + 20, rect.left + 250, rect.top + 40 };
	//GetClientRect(hWnd, &outsideRect); // get the client area rectangle

	HBRUSH hBrushGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushGreen);
	Rectangle(hdc, originalRect.left, originalRect.top, originalRect.right, originalRect.bottom);
	SelectObject(hdc, hBrushInitial);
	DeleteObject(hBrushGreen);

	HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
	hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushBlue);
	Rectangle(hdc, progressRect.left, progressRect.top, progressRect.left + (progressRect.right - progressRect.left) * rightPercentageChildWindow, progressRect.bottom);
	SelectObject(hdc, hBrushInitial);
	DeleteObject(hBrushBlue);

}

bool isInsideChildwindow = false;
bool isInsideTopRightRect = false;
int topRectTop;
int topRectLeft;
int topRectRight;
int topRectBottom;
size_t xPosMainWindow;
size_t yPosMainWindow;

bool IsInsideMainWindowTopRect(int x, int y)
{
	return ((x > topRectLeft) && (x < topRectRight) && (y > topRectTop) && (y < topRectBottom));
}

LRESULT CALLBACK WndProcMainWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		WORD id = loword(wParam);
		WORD notificationCode = HIWORD(wParam);
		char str[256];
		sprintf_s(str, "MainWindow1 WM COMMAND id: %d notificationCode %d ", id, notificationCode);
		log(str);
		if (notificationCode == BN_CLICKED)
		{
			log("MainWindow1 Button is clicked");
		}
		else if (notificationCode == LBUTTONCLICKNC)
		{
			log("MainWindow1 L button clicked");
		}
		else if (notificationCode == UPDATEPROGRESSNC)
		{
			log("MainWindow1 Update progress NC received");
			InvalidateRect(hWnd, NULL, true);
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		xPosMainWindow = xPos;
		yPosMainWindow = yPos;
		char str[256];
		sprintf_s(str, "MainWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		log(str);
		if (!isInsideTopRightRect && IsInsideMainWindowTopRect(xPos, yPos))
		{
			TRACKMOUSEEVENT me{};
			me.cbSize = sizeof(TRACKMOUSEEVENT);
			me.dwFlags = TME_HOVER | TME_LEAVE;
			me.hwndTrack = hWnd;
			me.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&me);
			isInsideTopRightRect = true;
			InvalidateRect(hWnd, NULL, NULL);
		}
		else if (!IsInsideMainWindowTopRect(xPos, yPos) && isInsideTopRightRect)
		{
			isInsideTopRightRect = false;
			InvalidateRect(hWnd, NULL, NULL);
		}
		else if (IsInsideMainWindowTopRect(xPos, yPos))
		{
			InvalidateRect(hWnd, NULL, NULL);
		}
	}
	break;
	case WM_MOUSELEAVE:
	{
		char str[256];
		sprintf_s(str, "MainWindow1 WM Mouse leave");
		log(str);
		isInsideTopRightRect = false;
		InvalidateRect(hWnd, NULL, NULL);
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
		log(str);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		log("MainWindow WM paint called");
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT outsideRect = {};
		GetClientRect(hWnd, &outsideRect); // get the client area rectangle

		HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushRed);
		Rectangle(hdc, outsideRect.left, outsideRect.top, outsideRect.right, outsideRect.bottom);


		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushRed);

		RECT topRightRect = { biggerClassW - smallerClassW, 0 , outsideRect.right, smallerClassH };

		topRectTop = 0;
		topRectLeft = biggerClassW - smallerClassW;
		topRectRight = outsideRect.right;
		topRectBottom = smallerClassH;

		DrawRect(hdc, topRightRect, isInsideTopRightRect, xPosMainWindow, yPosMainWindow);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		log("MainWindow1 Win proc 1 WM_Destroy\n");
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}

size_t xPosChild;
size_t yPosChild;

LRESULT CALLBACK WndProcChildWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		WORD id = loword(wParam);
		WORD notificationCode = HIWORD(wParam);
		char str[256];
		sprintf_s(str, "ChildWindow WM COMMAND id: %d notificationCode %d ", id, notificationCode);
		log(str);
		if (notificationCode == UPDATEPROGRESSNC)
		{
			log("Child window Update progress NC received");
			//UpdateWindow(hWnd2);
			InvalidateRect(hWnd, NULL, true);
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		WORD xPos = loword(lParam);
		WORD yPos = hiword(lParam);
		xPosChild = xPos;
		yPosChild = yPos;
		char str[256];
		sprintf_s(str, "ChildWindow1 WM Mouse MOVE x: %d y: %d", xPos, yPos);
		log(str);
		if (!isInsideChildwindow)
		{
			TRACKMOUSEEVENT me{};
			me.cbSize = sizeof(TRACKMOUSEEVENT);
			me.dwFlags = TME_HOVER | TME_LEAVE;
			me.hwndTrack = hWnd;
			me.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&me);
			isInsideChildwindow = true;
			InvalidateRect(hWnd, NULL, NULL);
		}
		else {
			InvalidateRect(hWnd, NULL, NULL);
		}
	}
	break;
	case WM_MOUSELEAVE:
	{
		char str[256];
		sprintf_s(str, "ChildWindow1 WM Mouse leave");
		log(str);
		isInsideChildwindow = false;
		InvalidateRect(hWnd, NULL, NULL);
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
		WPARAM wParam = MAKEWPARAM(LBUTTONCLICKID, LBUTTONCLICKNC);
		SendMessageA(GetParent(hWnd), WM_COMMAND, wParam, NULL);
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
		log("ChildWindow WM paint called");
		RECT rect = {};
		GetClientRect(hWnd, &rect); // get the client area rectangle
		DrawRect(hdc, rect, isInsideChildwindow, xPosChild, yPosChild);

		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}