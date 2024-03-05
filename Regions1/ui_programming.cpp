// ui_programming.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "ui_programming.h"
#include "stdio.h"

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

		HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH hBrushInitial = (HBRUSH)SelectObject(hdc, hBrushBlue);

		HRGN RectRgn = CreateRectRgn(600, 200, 900, 400);

		HRGN EllipseRgn = CreateEllipticRgn(500, 150, 700, 300);
		CombineRgn(EllipseRgn, EllipseRgn, RectRgn, RGN_OR);
		DeleteObject(RectRgn);

		HRGN RectRgn2 = CreateRectRgn(400, 25, 600, 200);
		CombineRgn(EllipseRgn, EllipseRgn, RectRgn2, RGN_DIFF);
		PaintRgn(hdc, EllipseRgn);
		DeleteObject(RectRgn2);

		HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrushRed);
		DeleteObject(hBrushBlue);
		FrameRgn(hdc, EllipseRgn, hBrushRed, 5, 5);

		SetArcDirection(hdc, AD_CLOCKWISE);
		Arc(hdc, 100, 100, 200, 200, 150, 200, 200, 150);
		MoveToEx(hdc, 200, 150, nullptr);
		LineTo(hdc, 350, 150);
		LineTo(hdc, 350, 250);
		LineTo(hdc, 150, 250);
		LineTo(hdc, 150, 200);

		EndPath(hdc);
		StrokeAndFillPath(hdc);

		DeleteObject(EllipseRgn);
		SelectObject(hdc, hBrushInitial);
		DeleteObject(hBrushRed);


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