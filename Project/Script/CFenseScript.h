#pragma once
#include <Engine/CScript.h>
class CFenseScript :
    public CScript
{
private:

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void OnOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    CLONE(CFenseScript);
public:
    CFenseScript();
    ~CFenseScript();

};

