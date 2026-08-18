#pragma once
#include <Engine/CScript.h>

class CCameraMoveScript :
    public CScript
{
    float m_fCamSpeed;

public:
    virtual void tick() override;

private:
    void Camera2DMove();
    void Camera3DMove();

    CLONE(CCameraMoveScript);
    CCameraMoveScript();
    virtual ~CCameraMoveScript() override;
};
