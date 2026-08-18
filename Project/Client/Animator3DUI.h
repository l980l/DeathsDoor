#pragma once
#include "ComponentUI.h"

class Animator3DUI :
    public ComponentUI
{
public:
    int                 m_iClipCount;
    vector<tMTAnimClip> m_vecAnimClip;
    bool                m_bShowAnimInfo;
    bool                m_bMakeAnimInfo;

    virtual int render_update() override;

    Animator3DUI();
    virtual ~Animator3DUI() override;
};
