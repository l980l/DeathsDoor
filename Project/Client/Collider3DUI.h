#pragma once
#include "ComponentUI.h"

class Collider3DUI :
    public ComponentUI
{
    Vec3  pPos;
    float pRadius;
    bool  createSphere;
    bool  setRenderRigidbody;

public:
    virtual int render_update() override;

    Collider3DUI();
    virtual ~Collider3DUI() override;
};
