#pragma once
#include <Engine\CScript.h>
class CGameCameraScript :
    public CScript
{
private:
    CGameObject*    m_pPlayer;
    float           m_fMoveTime;
    float           m_fPrevMoveTime;
    float           m_fDiffer;
    float           m_fTargetScale;
    float           m_fPrevScale;
    Vec3            m_vDistance;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;
    void SetInvincible(float _fMoveTime) { m_fMoveTime = _fMoveTime; }
    void SetMoveCamera(float _vTargetScale, float _fTime);


    CLONE(CGameCameraScript);

public:
    CGameCameraScript();
    ~CGameCameraScript();
};

