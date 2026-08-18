#pragma once
#include <Engine/CScript.h>

class CHUDScript :
    public CScript
{
    UINT m_iMagicType;
    int  m_iMaxHP;
    int  m_iHP;
    int  m_iMaxEnergy;
    int  m_iEnergy;
    int  m_iMoney;

public:
    virtual void begin() override;
    virtual void tick() override;

    CLONE(CHUDScript);
    CHUDScript();
    virtual ~CHUDScript() override;
};
