#pragma once
#include <Engine\CScript.h>

class CWaterCameraScript :
    public CScript
{
private:
    CGameObject*                m_pMainCamera;      // MainCamera 포인터.
    float                       m_fWaterHeight;     // 물 높이.
    Ptr<CTexture>               m_WaterCamTex;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CWaterCameraScript);

public:
    CWaterCameraScript();
    ~CWaterCameraScript();
};

