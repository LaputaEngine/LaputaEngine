#include <Windows.h>
#include "LptaRenderer.h"

#pragma comment(lib, "LaputaRenderer.lib")

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

bool g_hasFocus = false;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdArgs, int showArg)
{
	HWND hWnd;
	WNDCLASSEX windowConfig;
	ZeroMemory(&windowConfig, sizeof(WNDCLASSEX));

	windowConfig.cbSize = sizeof(WNDCLASSEX);
	windowConfig.style = ( CS_OWNDC | CS_DBLCLKS);
	windowConfig.lpfnWndProc = WindowProc;
	windowConfig.cbClsExtra = 0;
	windowConfig.cbWndExtra = 0;
	windowConfig.hInstance = instance;
	windowConfig.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowConfig.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowConfig.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowConfig.lpszClassName = L"LaputaRendererTestWindowClass";
	windowConfig.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	RegisterClassEx(&windowConfig);

	hWnd = CreateWindowEx(NULL,
		L"LaputaRendererTestWindowClass",
		L"Laputa Renderer Test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL,
		NULL,
		instance,
		NULL);

	LptaRenderer renderer(instance);
	renderer.CreateDevice("Direct3D");
	LPTAFXRENDERER device = renderer.GetDevice();
	vector<HWND> renderWindows;

	renderWindows.push_back(CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"static",
		NULL,
		WS_CHILD | SS_BLACKRECT | WS_VISIBLE, 10, 10, 100, 100, hWnd, NULL, instance, NULL)
		);
	device->SetClearColor(1.0f, 0.0f, 0.0f);
	device->Init(hWnd, renderWindows, 16, 0, false);
	device->UseWindow(0);
	ShowWindow(hWnd, showArg);
	MSG message;
	device->BeginRendering(true, true, true);
	device->EndRendering();
	while (true) {
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		if (message.message == WM_QUIT) {
			break;
		}

		if (g_hasFocus) {
			device->BeginRendering(true, true, true);
			device->EndRendering();
		}
	}
	renderer.Release();
	return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_ACTIVATE:
		g_hasFocus = (bool)wParam;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}