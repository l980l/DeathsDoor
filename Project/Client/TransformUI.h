#pragma once
#include "ComponentUI.h"

class CGameObject;

class TransformUI :
    public ComponentUI
{
    bool    m_bShowEdieWave;
    wstring m_wstrPrefabName;
    Vec3    m_vSpawnPos;

public:
    virtual int render_update() override;
    void        ShowWaveEditor();

    TransformUI();
    virtual ~TransformUI() override;
};
