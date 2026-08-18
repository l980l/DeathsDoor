#pragma once
#include "CState.h"

class CCrowBossStomp :
    public CState
{
    Vec3  m_Dir;
    float m_fDistance;
    float m_fTime;
    bool  m_bCameraShake;

public:
    void SetDir(Vec3 _vDir) { m_Dir = _vDir; }
    void SetDistance(float _fDistance) { m_fDistance = _fDistance; }

    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossStomp);

    CCrowBossStomp();
    virtual ~CCrowBossStomp() override;
};
