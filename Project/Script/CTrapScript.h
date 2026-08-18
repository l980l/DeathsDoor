#pragma once
#include <Engine/CScript.h>

class CTrapScript :
    public CScript
{
    int m_iTrapNum;

    void SetTrapNum(int _trapNum) { m_iTrapNum = _trapNum; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CTrapScript);
    CTrapScript();
    virtual ~CTrapScript() override;
};
