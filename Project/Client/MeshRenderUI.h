#pragma once
#include "ComponentUI.h"

class MeshRenderUI :
    public ComponentUI
{
public:
    virtual int render_update() override;


    void SelectMesh(DWORD_PTR _Key);
    void SelectMaterial(DWORD_PTR _Key);


    MeshRenderUI();
    virtual ~MeshRenderUI() override;
};
