#pragma once
#include "CState.h"
class CGrimKnightGuardStay :
    public CState
{
private:
    int     m_hitCount;
    int     m_remainHP;
    int     m_remainMaxHP;
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:
    Vec3 vector_cross(Vec3 a, Vec3 b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    float GetDir(Vec3 _vStart, Vec3 _vTarget, bool _degree = false);

    CLONE(CGrimKnightGuardStay);

public:
    CGrimKnightGuardStay();
    ~CGrimKnightGuardStay();
};

