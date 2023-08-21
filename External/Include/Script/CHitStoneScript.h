#pragma once
#include <Engine/CScript.h>
class CHitStoneScript :
    public CScript
{
private:
    bool b_hit;
    bool b_move;
    float m_fMoveDistance;
    Vec3 m_vStartPos;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;
    bool CheckStoneHit() { return b_hit; }
    CLONE(CHitStoneScript);
public:
    CHitStoneScript();
    ~CHitStoneScript();
};

