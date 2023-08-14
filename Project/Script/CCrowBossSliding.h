#pragma once
#include "CState.h"
class CCrowBossSliding :
    public CState
{
private:
    vector<CGameObject*>    m_vecHook;
    queue<Vec3>             m_qStartPos;        // Hook�� �������� ������ �ʴ� ��� �����̵��� ������ ��ġ
    queue<Vec3>             m_qTargetPos;       // Hook�� ���� �� ������ �� ���ʴ�� �����̵� �� ��ġ�� �޾Ƶ�
    Vec3                    m_vDirtoTarget;     
    int                     m_iSliderCount;     // �����̵� Ƚ��
    CHAINPATERN             m_tChainPatern;
   
public:
    virtual void tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

    void SetHook(vector<CGameObject*> _vecHook) { if (m_vecHook.empty()) m_vecHook = _vecHook; }
    void AddTargetPos(Vec3 _vTargetPos, Vec3 _vStartPos = {});
    void SetPatern(CHAINPATERN _tPatern) { m_tChainPatern = _tPatern; }
    void SlidingToTargetPos();
    void ArriveToTarget();

    CLONE(CCrowBossSliding);

public:
    CCrowBossSliding();
    ~CCrowBossSliding();

};

