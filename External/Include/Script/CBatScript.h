#pragma once
class CBatScript    :
    public CScript
{
private:
    CStateScript* m_pState;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;


    CLONE(CBatScript);

public:
    CBatScript();
    ~CBatScript();

};

