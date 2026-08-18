#pragma once
#include "ComponentUI.h"

class RigidbodyUI :
    public ComponentUI
{
    bool m_IsStaticCube;
    bool m_IsSphere;

public:
    virtual int render_update() override;

    RigidbodyUI();
    virtual ~RigidbodyUI() override;
};
