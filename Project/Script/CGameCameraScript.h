#pragma once
#include <Engine\CScript.h>
class CGameCameraScript :
    public CScript
{
private:
    CGameObject*    m_pTarget;
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
    Vec3 GetDistance() { return m_vDistance; }
    
    void SetTarget(CGameObject* _pTarget) { m_pTarget = _pTarget; }
    void SetTargetPlayer(){ m_pTarget = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"); }


    CLONE(CGameCameraScript);

public:
    CGameCameraScript();
    ~CGameCameraScript();
};

