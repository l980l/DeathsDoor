#pragma once
#include "ComponentUI.h"

class LandScapeUI :
    public ComponentUI
{
public:
    virtual int render_update() override;
    void        SelectTexture(DWORD_PTR _Key);
    LandScapeUI();
    virtual ~LandScapeUI() override;
};
