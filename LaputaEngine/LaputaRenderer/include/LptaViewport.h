#ifndef _LPTAVIEWPORT_H_
#define _LPTAVIEWPORT_H_

namespace lpta
{

typedef struct VIEWPORT_DIM_TYPE
{
    unsigned int width;
    unsigned int height;
} VIEWPORT_DIM;

typedef struct VIEWPORT_POINT_TYPE
{
    unsigned int x;
    unsigned int y;
} VIEWPORT_POINT;

class LptaViewport
{
public:
    static const unsigned int DEFAULT_X = 0;
    static const unsigned int DEFAULT_Y = 0;
    static const unsigned int DEFAULT_WIDTH = 800;
    static const unsigned int DEFAULT_HEIGHT = 600;

public:
    LptaViewport(void);
    LptaViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    ~LptaViewport(void);

    const VIEWPORT_POINT &GetPoint(void) const;
    const VIEWPORT_DIM &GetDimension(void) const;

private:
    VIEWPORT_POINT point;
    VIEWPORT_DIM dimension;
};

}

#endif