#pragma once
#include "ComponentUI.h"

class Light3DUI :
    public ComponentUI
{
    tLightInfo m_LightInfo;

public:
    virtual int render_update() override;

    Light3DUI();
    virtual ~Light3DUI() override;
};
