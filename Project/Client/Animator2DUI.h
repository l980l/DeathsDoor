#pragma once
#include "ComponentUI.h"

class Animator2DUI :
    public ComponentUI
{
public:
    virtual int render_update() override;

    Animator2DUI();
    virtual ~Animator2DUI() override;
};
