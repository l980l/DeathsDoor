#pragma once
#include "ResUI.h"

class MeshUI :
    public ResUI
{
public:
    virtual int render_update() override;

    MeshUI();
    virtual ~MeshUI() override;
};
