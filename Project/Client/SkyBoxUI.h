#pragma once
#include "ComponentUI.h"

class SkyBoxUI :
    public ComponentUI
{
    int m_iType;

public:
    virtual int render_update() override;

    void SelectTexture(DWORD_PTR _Key);

    SkyBoxUI();
    virtual ~SkyBoxUI() override;
};
