#pragma once
#include "ComponentUI.h"

class CParticleSystem;

class ParticleSystemUI :
    public ComponentUI
{
private:
    CParticleSystem* m_pParticleSystem;
    tParticleModule      m_tModuleData;
    Ptr<CTexture>         pTex;
public:
    virtual int render_update() override;
    void ModuleOnOff(string _strName, string _strID, int& _ModuleCheck);
    void SetTexture();
    void SelectTexture(DWORD_PTR _Key);
    void SpawnModule();
    void ScaleModule();
    void ColorModule();
    void AddVelocityModule();
    void DragModule();
    void RandomForceModule();
    void VelocityScaleModule();
    void AnimationModule();
    void SaveParticle();
    void LoadParticle();

public:
    ParticleSystemUI();
    ~ParticleSystemUI();

};

