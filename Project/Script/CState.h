#pragma once
#include <Engine/CEntity.h>
#include "CStateScript.h"

class CState :
    public CEntity
{
    CStateScript* m_pOwnerScript;

public:
    virtual void tick() = 0;
    virtual void Enter() = 0; // 새로운 state로 변경될때 호출 됨.
    virtual void Exit() = 0;  // 다른 state로 변경되기 직전에 호출 됨.

    void ChangeState(wstring _strStateName) const;

    CStateScript* GetOwnerScript() const { return m_pOwnerScript; }
    CGameObject*  GetOwner() const { return m_pOwnerScript->GetOwner(); }

    virtual void BeginOverlap(CCollider3D* _Other)
    {
    };

    virtual void OnOverlap(CCollider3D* _Other)
    {
    };

    virtual void EndOverlap(CCollider3D* _Other)
    {
    };

    virtual CState* Clone() override = 0;

    CState();
    virtual ~CState() override;

    friend class CStateScript;
};
