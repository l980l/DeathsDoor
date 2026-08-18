#pragma once
#include <Engine/CScript.h>

class CHitStoneScript :
    public CScript
{
    bool  m_bHit;
    bool  m_bMove;
    float m_fMoveDistance;
    Vec3  m_vStartPos;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;
    bool         CheckStoneHit() const { return m_bHit; }

    CLONE(CHitStoneScript);
    CHitStoneScript();
    virtual ~CHitStoneScript() override;
};
