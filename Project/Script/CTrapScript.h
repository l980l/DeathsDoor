#pragma once
#include <Engine/CScript.h>
class CTrapScript :
    public CScript
{
private:


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CTrapScript);
public:
    CTrapScript();
    ~CTrapScript();

};
