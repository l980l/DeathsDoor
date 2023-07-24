#pragma once
#include <Engine\CScript.h>
#include "CStateScript.h"

class CBankerScript :
	public CScript
{
private:
    CStateScript* m_pStateScript;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CBankerScript);
public:
    CBankerScript();
    ~CBankerScript();
};
