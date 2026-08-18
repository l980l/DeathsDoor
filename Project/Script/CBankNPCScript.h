#pragma once
#include <Engine/CScript.h>

class CBankNPCScript :
    public CScript
{
    CGameObject* m_pTalkSign;

public:
    virtual void begin() override {};
    virtual void tick() override {};

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CBankNPCScript);
    CBankNPCScript();
    virtual ~CBankNPCScript() override = default;
};
