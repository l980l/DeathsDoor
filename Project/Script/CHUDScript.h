#pragma once
#include <Engine/CScript.h>
class CHUDScript :
    public CScript
{
private:
    UINT     m_pMagicType;
    int         m_pMaxHP;
    int         m_pHP;
    int         m_pMaxEnergy;
    int         m_pEnergy;
    int         m_pMoney;
public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CHUDScript);
public:
    CHUDScript();
    ~CHUDScript();
};

