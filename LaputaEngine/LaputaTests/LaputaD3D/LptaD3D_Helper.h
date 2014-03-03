#ifndef _LPTAD3D_HELPER_H_
#define _LPTAD3D_HELPER_H_

#include <gtest/gtest.h>
#include <d3d9.h>

class D3D9Test : public ::testing::Test
{
public:
    static const unsigned int WINDOW_WIDTH = 800;
    static const unsigned int WINDOW_HEIGHT = 600;

public:
    virtual void SetUp()
    {
        D3DPRESENT_PARAMETERS d3dpp;
        ZeroMemory(&d3dpp, sizeof(d3dpp));
	    d3dpp.Windowed = TRUE;
	    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	    d3dpp.BackBufferWidth = 800;
	    d3dpp.BackBufferHeight = 600;


        d3d = Direct3DCreate9(D3D_SDK_VERSION);
        d3d->CreateDevice(D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            NULL,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &d3dpp,
            &d3ddev);
    }

    virtual void TearDown()
    {
    }

protected:
    LPDIRECT3D9 d3d;
    LPDIRECT3DDEVICE9 d3ddev;
};

#endif