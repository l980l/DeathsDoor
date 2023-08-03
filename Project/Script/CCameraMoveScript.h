#pragma once
#include <Engine\CScript.h>

class CCameraMoveScript :
    public CScript
{
private:
    float        m_fCamSpeed;
    Vec2		 m_vOffset;
    float		 m_fAccTime;
    float		 m_fMaxTime;
    float		 m_fRange;
    float		 m_fShakeSpeed;
    float		 m_fShakeDir;
    bool		 m_bCamShake;

public:
    virtual void tick() override;
    void CameraShake(float _fRange, float _fShackSpeed, float _fTerm);
    void ShackCamera();

private:
    void Camera2DMove();
    void Camera3DMove();

    CLONE(CCameraMoveScript);
public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

