#pragma once
#include "ComponentUI.h"

class CParticleSystem;

class ParticleSystemUI :
    public ComponentUI
{
    CParticleSystem* m_pParticleSystem;
    tParticleModule  m_tModuleData;
    Ptr<CTexture>    pTex;
    int              m_iEmissive;

public:
    virtual int render_update() override;
    void        ModuleOnOff(string _strName, string _strID, int& _ModuleCheck) const;
    void        SetTexture();
    void        SelectTexture(DWORD_PTR _Key);
    void        SpawnModule();
    void        ScaleModule();
    void        ColorModule();
    void        AddVelocityModule();
    void        DragModule();
    void        RandomForceModule();
    void        RenderModule();
    void        VelocityScaleModule() const;
    void        AnimationModule();
    void        SaveParticle();
    void        LoadParticle();

    ParticleSystemUI();
    virtual ~ParticleSystemUI() override;
};
