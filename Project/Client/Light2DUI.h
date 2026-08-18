#pragma once
#include "ComponentUI.h"

class Light2DUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

    Light2DUI();
    virtual ~Light2DUI() override;
};
