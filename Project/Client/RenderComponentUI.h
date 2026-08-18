#pragma once
#include "UI.h"

class RenderComponentUI :
    public UI
{
    CGameObject*      m_Target;
    CRenderComponent* m_Component;

public:
    virtual int render_update() override;

    void SetTarget(CGameObject* _Target);
    void SelectMesh(DWORD_PTR _Key);
    void SelectMaterial(DWORD_PTR _Key);
    void SelectTexture(DWORD_PTR _Key);

    CGameObject* GetTarget() const { return m_Target; }
    RenderComponentUI();
    virtual ~RenderComponentUI() override;
};
