#pragma once
#include "ResUI.h"

class MaterialUI :
    public ResUI
{
    TEX_PARAM m_eSelected;

public:
    virtual int render_update() override;


    void SelectTexture(DWORD_PTR _Key);

    MaterialUI();
    virtual ~MaterialUI() override;
};
