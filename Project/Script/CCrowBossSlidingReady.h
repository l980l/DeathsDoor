#pragma once
#include "CState.h"
class CCrowBossSlidingReady :
    public CState
{
private:
    int m_iSlidingCount;  // �̹� �罽 ���Ͽ��� �����̵��� Ƚ��. ù 1ȸ�� ȭ�� ������ �����̵� �ϰ�, �� �ڷ� 4ȸ ������ �罽�� ���� ������ �˵��� �����, ���ư���. 

public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    CLONE(CCrowBossSlidingReady);

public:
    CCrowBossSlidingReady();
    ~CCrowBossSlidingReady();
};

