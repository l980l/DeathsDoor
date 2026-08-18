#pragma once
#include "ComponentUI.h"

class DecalUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

    DecalUI();
    virtual ~DecalUI() override;
};
