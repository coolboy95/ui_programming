// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"

HINSTANCE hInst;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	const char className1[] = "H-instance window class1";

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

	hInst = hInstance;

	int biggerClassX = 100;
	int biggerClassY = 200;

	int biggerClassW = 1000;
	int biggerClassH = 500;

	int smallerClassW = 400;
	int smallerClassH = 100;

	HWND hWnd = CreateWindowExA(0, className1, "New Title1", WS_OVERLAPPEDWINDOW,
		biggerClassX, biggerClassY, biggerClassW, biggerClassH, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, TRUE);
	UpdateWindow(hWnd);

	HACCEL hAccelTable = NULL;

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}

	UnregisterClassA(className1, hInst);

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

void CreatePolygon(HDC hdc)
{
	tagPOINT p1;
	p1.x = 140;
	p1.y = 20;

	tagPOINT p2;
	p2.x = 200;
	p2.y = 20;

	tagPOINT p3;
	p3.x = 180;
	p3.y = 30;

	tagPOINT p4;
	p4.x = 200;
	p4.y = 50;

	tagPOINT p5;
	p5.x = 160;
	p5.y = 60;

	POINT pArray[] = { p1, p2, p3, p4, p5 };

	Polygon(hdc, pArray, sizeof(pArray) / sizeof(pArray[0]));
}

void CreateLine(HDC hdc)
{
	tagPOINT p1;
	p1.x = 300;
	p1.y = 50;

	tagPOINT p2;
	p2.x = 350;
	p2.y = 100;

	POINT pArray[] = { p1,p2 };

	HPEN hPenPurple = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
	HPEN hPenInitial = (HPEN)SelectObject(hdc, hPenPurple);
	Polyline(hdc, pArray, sizeof(pArray) / sizeof(pArray[0]));
	SelectObject(hdc, hPenInitial);
	DeleteObject(hPenPurple);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{

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
		DeleteObject(hBrushRed);

		RECT insideRect = { outsideRect.right / 2 - 50, outsideRect.bottom / 2 - 15, outsideRect.right / 2 + 50, outsideRect.bottom / 2 + 15 }; // width 100 and height 30
		HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hBrushBlue);

		HPEN hPenYellow = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		HPEN hPenInitial = (HPEN)SelectObject(hdc, hPenYellow);

		SetBkMode(hdc, TRANSPARENT);
		HFONT newFont = CreateFontA(14, 0, 0, 0, 700, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman");
		HFONT initialFont = (HFONT)SelectObject(hdc, newFont);

		Rectangle(hdc, insideRect.left, insideRect.top, insideRect.right, insideRect.bottom);

		SetTextColor(hdc, RGB(0, 0, 0)); // Setting black color
		DrawTextA(hdc, "YOLO", -1, &insideRect, DT_CENTER);

		SelectObject(hdc, initialFont);
		DeleteObject(newFont);

		SelectObject(hdc, hPenInitial);
		DeleteObject(hPenYellow);

		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushBlue);

		CreatePolygon(hdc);
		CreateLine(hdc);

		HBITMAP imageBitmap = (HBITMAP)LoadImageA(nullptr, "C:\\Users\\nikhilkhuran\\Downloads\\ImageBmp.bmp", 
			IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
		
		if (imageBitmap)
		{
			OutputDebugStringA("image bit map loaded\n");
		}
		else {
			OutputDebugStringA("image bit map not loaded\n");
		}
		
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmInitial = (HBITMAP)SelectObject(hdcMem, imageBitmap);
		
		BitBlt(hdc,insideRect.left, insideRect.top, 20, 20, hdcMem, 0,0, SRCCOPY);

		SelectObject(hdcMem, hbmInitial);
		DeleteObject(imageBitmap);
		DeleteObject(hdcMem);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		OutputDebugStringA("Win proc 1 WM_Destroy\n");
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}