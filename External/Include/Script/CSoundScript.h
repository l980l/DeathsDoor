#pragma once
#include <Engine/CSound.h>
#include <Engine/CScript.h>
class CSoundScript :
    public CScript
{
private:
    Ptr<CSound> pSound;
    int idx;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;

    CLONE(CSoundScript);
public:
    CSoundScript();
    ~CSoundScript();
};

