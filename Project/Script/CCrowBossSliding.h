#pragma once
#include "CState.h"
class CCrowBossSliding :
    public CState
{
private:
    queue<Vec3>             m_qStartPos;        // Hook을 보스에서 날리지 않는 경우 슬라이딩을 시작할 위치
    queue<Vec3>             m_qTargetPos;       // Hook을 여러 개 날렸을 때 차례대로 슬라이딩 할 위치를 받아둠
    Vec3                    m_vCurTargetPos;    // 현재 가야하는 위치
    Vec3                    m_vDirtoTarget;
    Vec3                    m_vRottoTarget;
    float                   m_fSlidiingSpeed;
    bool                    m_bThrowmany;       // 여러 개 던졌을 때
   

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void AddTargetPos(Vec3 _vTargetPos);
    void AddStartTargetPos(Vec3 _vStartPos, Vec3 _vTargetPos);
    void SlidingToTargetPos();
    void ArriveToTarget();

    CLONE(CCrowBossSliding);

public:
    CCrowBossSliding();
    ~CCrowBossSliding();
};

