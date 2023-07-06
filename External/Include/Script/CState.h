#pragma once
#include <Engine/CEntity.h>
#include "CStateScript.h"

class CState :
    public CEntity
{
private:
    CStateScript* m_pOwnerScript;

public:
    virtual void tick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    void ChangeState(wstring _strStateName);

    CStateScript* GetOwnerScript() { return m_pOwnerScript; }
    CGameObject* GetOwner() { return m_pOwnerScript->GetOwner(); }

    virtual void BeginOverlap(CCollider2D* _Other) {};
    virtual void OnOverlap(CCollider2D* _Other) {};
    virtual void EndOverlap(CCollider2D* _Other) {};

public:
    CState* Clone() = 0;

    CState();
    ~CState();

    friend class CStateScript;
};

