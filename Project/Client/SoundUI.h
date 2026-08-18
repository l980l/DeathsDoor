#pragma once
#include "ResUI.h"
#include <Engine/CSound.h>

class SoundUI :
    public ResUI
{
    CSound*        m_sound;
    FMOD::Channel* pChannel;
    int            idx;
    float          m_volume;

public:
    virtual int render_update() override;

    SoundUI();
    virtual ~SoundUI() override;
};
