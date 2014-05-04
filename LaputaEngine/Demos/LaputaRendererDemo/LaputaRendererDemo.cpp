#define D3D_DEBUG_INFO
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#include <Windows.h>
#include "LptaRenderer.h"
#include "LptaDeviceBuilder.h"
#include "LptaVector.h"
#include "LptaNormalVector.h"
#include "LptaSkinManager.h"
#include "LptaMaterialManager.h"
#include "LptaTextureManager.h"
#include "LptaVertexCache.h"
#include "vertices/LptaVertices.h"
#include "vertices/LptaUUVertices.h"
#include "vertices/LptaIndices.h"
using namespace lpta;
using namespace lpta_3d;

#pragma comment(lib, "LaputaRenderer.lib")

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

bool g_hasFocus = false;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdArgs, int showArg)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    HWND hWnd;
    WNDCLASSEX windowConfig;
    ZeroMemory(&windowConfig, sizeof(WNDCLASSEX));

    windowConfig.cbSize = sizeof(WNDCLASSEX);
    windowConfig.style = (CS_OWNDC | CS_DBLCLKS);
    windowConfig.lpfnWndProc = WindowProc;
    windowConfig.cbClsExtra = 0;
    windowConfig.cbWndExtra = 0;
    windowConfig.hInstance = instance;
    windowConfig.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowConfig.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowConfig.hbrBackground = (HBRUSH)COLOR_WINDOW;
    windowConfig.lpszClassName = L"LaputaRendererTestWindowClass";
    windowConfig.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassEx(&windowConfig);

    hWnd = CreateWindowEx(0,
        L"LaputaRendererTestWindowClass",
        L"Laputa Renderer Test",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        nullptr,
        nullptr,
        instance,
        nullptr);
    lpta::LptaRenderer renderer(instance);
    LPTA_DEVICE_BUILDER builder;
    renderer.CreateDeviceBuilder("Direct3D", &builder);
    vector<HWND> renderWindows;
    lpta::LPTA_DEVICE device;

    renderWindows.push_back(CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"static",
        nullptr,
        WS_CHILD | SS_BLACKRECT | WS_VISIBLE, 0, 0, 800, 600, hWnd, nullptr, instance, nullptr)
    );
    builder->Make(hWnd, renderWindows, &device);
    device->SetClearColor(0.5f, 0.5f, 0.5f);
    device->UseWindow(0);
    
    ShowWindow(hWnd, showArg);
    MSG message;

    LptaVector right(1.0f, 0.0f, 0.0f);
    LptaVector up(0.0f, 1.0f, 0.0f);
    LptaVector dir(0.0f, 0.0f, 1.0f);
    LptaVector point(0.0f, 0.0f, 0.0f);

    LptaUUVertices tri;
    UU_VERTEX vertex = {
        lpta_3d::POINT(-1.0f, -1.0f, 1.0f),
        LptaNormalVector::MakeFrom(0.0f, 0.0f, 1.0f),
        0.0f, 1.0f  
    };
    tri.AddVertex(vertex);
    vertex.coordinate.SetX(0.0f);
    vertex.coordinate.SetY(1.0f);
    tri.AddVertex(vertex);
    vertex.coordinate.SetX(1.0f);
    vertex.coordinate.SetY(-1.0f);
    tri.AddVertex(vertex);
    INDICES indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    LptaResource::ID bufferId = device->GetVertexCache()->CreateStaticBuffer(&tri, indices, 0);
    device->SetCullingMode(RS_CULL_NONE);
    device->ActivateVertexShader(0, VERTEX_TYPE::VT_UU);
    device->ActivatePixelShader(0);

    LptaMatrix m = LptaMatrix::MakeIdentityMatrix();
    m.SetTranslation(0.0f, 0.0f, 0.0f);

    while (true) {
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        if (message.message == WM_QUIT) {
            break;
        }

        if (g_hasFocus) {
            device->BeginRendering(true, true, true);
            //device->SetView3D(right, up, dir, point);
            device->SetWorldTransform(m);
            device->GetVertexCache()->FlushStaticBuffer(bufferId);
            device->EndRendering();
        }
    }
    device.reset();
    return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_ACTIVATE:
        g_hasFocus = (wParam != 0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        ;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}