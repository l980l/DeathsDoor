#pragma once
#include "ComponentUI.h"
class Animator3DUI :
    public ComponentUI
{
public:
    vector<tMTAnimClip>     m_vecAnimClip;
    vector<string>          m_vecStrName;

public:
    virtual int render_update() override;

public:
    Animator3DUI();
    ~Animator3DUI();
};

