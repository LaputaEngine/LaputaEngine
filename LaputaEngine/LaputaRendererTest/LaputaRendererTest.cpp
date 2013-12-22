#include <Windows.h>
#include "LptaRenderer.h"

#pragma comment(lib, "LaputaRenderer.lib")

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdArgs, int showArg)
{
	HWND hWnd;
	WNDCLASSEX windowConfig;
	ZeroMemory(&windowConfig, sizeof(WNDCLASSEX));

	windowConfig.cbSize = sizeof(WNDCLASSEX);
	windowConfig.style = (CS_HREDRAW | CS_VREDRAW);
	windowConfig.lpfnWndProc = WindowProc;
	windowConfig.hInstance = instance;
	windowConfig.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowConfig.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowConfig.lpszClassName = L"LaputaRendererTestWindowClass";
	
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

	ShowWindow(hWnd, showArg);

	LptaRenderer renderer(instance);
	renderer.CreateDevice("Direct3D");
	LPTAFXRENDERER device = renderer.GetDevice();
	std::shared_ptr<HWND> t;
	device->Init(hWnd, t, 16, 0, false);

	MSG message;
	while (true) {
		
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		if (message.message == WM_QUIT) {
			break;
		}

		device->BeginRendering(true, true, true);
		device->EndRendering();
	}
	renderer.Release();
	return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}