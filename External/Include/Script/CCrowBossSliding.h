#pragma once
#include "CState.h"
class CCrowBossSliding :
    public CState
{
private:
    vector<CGameObject*>    m_vecHook;
    queue<Vec3>             m_qStartPos;        // Hook�� �������� ������ �ʴ� ��� �����̵��� ������ ��ġ
    queue<Vec3>             m_qTargetPos;       // Hook�� ���� �� ������ �� ���ʴ�� �����̵� �� ��ġ�� �޾Ƶ�
    Vec3                    m_vCurTargetPos;    // ���� �����ϴ� ��ġ
    Vec3                    m_vDirtoTarget;
    Vec3                    m_vRottoTarget;
    float                   m_fSlidiingSpeed;
    bool                    m_bThrowmany;       // ���� �� ������ ��
    int                     m_iSliderCount;
   
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void SetHook(vector<CGameObject*> _vecHook) { if (m_vecHook.empty()) m_vecHook = _vecHook; }
    void AddTargetPos(Vec3 _vTargetPos, Vec3 _vStartPos = {});
    void SlidingToTargetPos();
    void ArriveToTarget();

    CLONE(CCrowBossSliding);

public:
    CCrowBossSliding();
    ~CCrowBossSliding();

};

