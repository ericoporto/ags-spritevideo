#ifndef SPRITEVIDEO_RENDERFACTORY_H
#define SPRITEVIDEO_RENDERFACTORY_H

#include <memory>
#include "RenderObject.h"

struct Screen;

class RenderFactory
{
public:
    virtual void InitGfxDevice(void* data) = 0;
    virtual bool InitGfxMode(Screen* screen, void* data) = 0;
    virtual void SetScreenMatrixes(Screen* screen, float(*world)[16], float(*view)[16], float(*proj)[16]) = 0;
    virtual std::unique_ptr<RenderObject> CreateRenderObject() = 0;
};

#endif // SPRITEVIDEO_RENDERFACTORY_H
