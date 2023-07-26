#pragma once
#include <Engine\CScript.h>
#include "CStateScript.h"

class CBankUpgradeScript :
	public CScript
{
private:
    CStateScript* m_pStateScript;
    int m_Power;
    int m_ASpeed;
    int m_Speed;
    int m_Magic;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CBankUpgradeScript);
public:
    CBankUpgradeScript();
    ~CBankUpgradeScript();
};
