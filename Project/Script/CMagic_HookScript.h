#pragma once
#include <Engine/CScript.h>

class CPlyMagic_Hook;

class CMagic_HookScript :
    public CScript
{
private:
    CPlyMagic_Hook*         m_pOwner;
    vector<CGameObject*>    m_vecChain;
    Vec3                    m_vStartPos;
    Vec3                    m_vThrownDir;
    Vec3                    m_vAttackDir;
    float                   m_fTime;
    float                   m_fDistancetoTarget;    // Hookpos���� �Ÿ�
    float                   m_fChainSpacing;        // ü�� �� �����ϴ� ����
    bool                    m_bSnatch;              // ����è ����
    bool                    m_bReturn;              // ����ä�� ���ϰ� ���ƿ��� ��
    bool                    m_bActive;
    
private:
    void SetOwner(CPlyMagic_Hook* _pOwner) { m_pOwner = _pOwner; }
    void SetChain(vector<CGameObject*>& _vecChain) { m_vecChain = _vecChain; }
public:    
    virtual void begin() override;
    virtual void tick() override;

    void SetThrowDir(Vec3 _vThrowDir) { m_vThrownDir = _vThrowDir.Normalize(); }
    void SetAttackDir(Vec3 _vDir) {m_vAttackDir = _vDir;}
    void SetStartPos(Vec3 _vStartPos) { m_vStartPos = _vStartPos; }
    void Active(bool _bActive);

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    void PaveChain();
    void Clear();

    CLONE(CMagic_HookScript);

public:
    CMagic_HookScript();
    ~CMagic_HookScript();
    
    friend class CPlyMagic_Hook;
};

