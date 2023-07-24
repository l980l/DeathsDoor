#pragma once
#include "CState.h"
class CGrimKnightGuardStay :
    public CState
{
private:
    int     m_hitCount;
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

private:
    Vec3 vector_cross(Vec3 a, Vec3 b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    CLONE(CGrimKnightGuardStay);

public:
    CGrimKnightGuardStay();
    ~CGrimKnightGuardStay();
};

