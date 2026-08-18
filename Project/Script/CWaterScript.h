#pragma once
#include <Engine/CScript.h>

class CWaterScript :
    public CScript
{
    CGameObject* m_pPlayer;
    float        m_fWaterHeight;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CWaterScript);

    CWaterScript();
    virtual ~CWaterScript() override;
};
