#pragma once
#include "ComponentUI.h"

#include <Engine/CScript.h>

class ScriptUI :
    public ComponentUI
{
    CScript* m_pTargetScript;
    string   m_strScriptName;

public:
    virtual int render_update() override;

    void SetScript(CScript* _Script);

    ScriptUI();
    virtual ~ScriptUI() override;
};
