#pragma once
#include "ComponentUI.h"

class Collider2DUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

    Collider2DUI();
    virtual ~Collider2DUI() override;
};
