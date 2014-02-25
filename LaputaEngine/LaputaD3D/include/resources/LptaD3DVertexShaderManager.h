#ifndef _LPTAD3DSHADERMANAGER_H_
#define _LPTAD3DSHADERMANAGER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "LptaD3DVertexShader.h"
#include "LptaResourceManager.h"

namespace lpta_d3d
{

class LptaD3DVertexShaderManager : public lpta::LptaResourceManager<LptaD3DVertexShader>
{
public:
    LptaD3DVertexShaderManager(LPDIRECT3DDEVICE9 d3ddev);
    ~LptaD3DVertexShaderManager(void);

    // todo refine these function definitions
    LPDIRECT3DVERTEXSHADER9 LoadShader(void *data);
    LPDIRECT3DVERTEXSHADER9 LoadShaderFromFile(const std::string &filename);
    LPDIRECT3DVERTEXSHADER9 LoadAndCompileShader(std::string shader);
    LPDIRECT3DVERTEXSHADER9 LoadAndCompileShaderFromFile(const std::string &filename);

private:
    static const std::string defaultShaderProgram;
    
    LPDIRECT3DDEVICE9 d3ddev;
};

}

#endif