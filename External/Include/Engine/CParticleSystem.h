#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;
class CTexture;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*          m_ParticleBuffer;
    CStructuredBuffer*          m_RWBuffer;
    CStructuredBuffer*          m_ModuleDataBuffer;
    
    tParticleModule             m_ModuleData;
    Ptr<CParticleUpdateShader>  m_UpdateCS;

    Ptr<CTexture>               m_Tex;
   
    float                       m_AccTime;


public:
    virtual void finaltick() override;
    virtual void render() override;

    void SetModuleData(tParticleModule _ModuleData) {m_ModuleData = _ModuleData;}
    tParticleModule GetModuleData() { return m_ModuleData; }

    void SetTex(Ptr<CTexture> _Tex) { m_Tex = _Tex; }
    Ptr<CTexture> GetTex() { return m_Tex; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);
public:
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _Other);
    ~CParticleSystem();
};

