#pragma once
#include "CState.h"
class CCrowBossSliding :
    public CState
{
private:
    queue<Vec3>             m_qStartPos;        // Hook�� �������� ������ �ʴ� ��� �����̵��� ������ ��ġ
    queue<Vec3>             m_qTargetPos;       // Hook�� ���� �� ������ �� ���ʴ�� �����̵� �� ��ġ�� �޾Ƶ�
    Vec3                    m_vCurTargetPos;    // ���� �����ϴ� ��ġ
    Vec3                    m_vDirtoTarget;
    Vec3                    m_vRottoTarget;
    float                   m_fSlidiingSpeed;
    bool                    m_bThrowmany;       // ���� �� ������ ��
   

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

