#pragma once
#include "CState.h"
class CPlyMagic_Arrow :
    public CState
{
    float           m_fMagicChargeTime;
    CGameObject*    m_pBow;
    CGameObject*    m_pArrow;
public:
    virtual void Enter() override;
    virtual void tick() override;
    virtual void Exit() override;

    void CalcDir(CGameObject* _pArrow);

    CLONE(CPlyMagic_Arrow);

public:
    CPlyMagic_Arrow();
    ~CPlyMagic_Arrow();
};

