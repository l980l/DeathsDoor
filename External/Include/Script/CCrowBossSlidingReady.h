#pragma once
#include "CState.h"
class CCrowBossSlidingReady :
    public CState
{
private:
    int m_iSlidingCount;  // 이번 사슬 패턴에서 슬라이딩한 횟수. 첫 1회는 화면 내에서 슬라이딩 하고, 그 뒤로 4회 동안은 사슬을 먼저 정해진 궤도로 만들고, 날아간다. 

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossSlidingReady);

public:
    CCrowBossSlidingReady();
    ~CCrowBossSlidingReady();
};

