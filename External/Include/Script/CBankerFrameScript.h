#pragma once
#include <Engine/CScript.h>

class CBankerFrameScript :
    public CScript
{
private:
    int m_count;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CBankerFrameScript);
public:
    CBankerFrameScript();
    ~CBankerFrameScript();
};

