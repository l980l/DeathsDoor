#pragma once
#include "UI.h"

#include <Engine/ptr.h>
#include <Engine/CRes.h>
#include <Engine/CGameObject.h>

class CGameObject;

class ComponentUI :
    public UI
{
    CGameObject*         m_Target;
    const COMPONENT_TYPE m_Type;

public:
    void SetTarget(CGameObject* _Target);

    CGameObject* GetTarget() const { return m_Target; }

    COMPONENT_TYPE GetComponentType() const { return m_Type; }

    void GetResKey(Ptr<CRes> _Res, char* _Buff, size_t _BufferSize) const;

    virtual int render_update() override;


    ComponentUI(const string& _Name, COMPONENT_TYPE _Type);
    virtual ~ComponentUI() override;
};
