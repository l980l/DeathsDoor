#pragma once
#include <Engine/CScript.h>

class CCrowBossChainThrow;

class CBossChainScript :
    public CScript
{
private:
    CCrowBossChainThrow*    m_pChainScript;
    vector<CGameObject*>    m_vecChain;
    Vec3                    m_vThrowStartPos;
    Vec3                    m_vThrownDir;
    Vec3                    m_vAttackDir;
    float                   m_fTime;
    float                   m_fDistancetoTarget;    // Hookpos���� �Ÿ�
    float                   m_fChainSpacing;        // ü�� �� �����ϴ� ����
    bool                    m_bSnatch;              // ����è ����
    bool                    m_bReturn;              // ����ä�� ���ϰ� ���ƿ��� ��
    bool                    m_bActive;

private:
    void SetChainScript(CCrowBossChainThrow* _pChainScript) { m_pChainScript = _pChainScript; }
    void SetChain(vector<CGameObject*>& _vecChain) { m_vecChain = _vecChain; }
public:
    virtual void begin() override;
    virtual void tick() override;

    void SetThrowDir(Vec3 _vThrowDir) { m_vThrownDir = _vThrowDir.Normalize(); }
    void SetAttackDir(Vec3 _vDir) { m_vAttackDir = _vDir; }
    void SetThrowStartPos(Vec3 _vStartPos) { m_vThrowStartPos = _vStartPos; }
    void Active(bool _bActive);

    virtual void BeginOverlap(CCollider3D* _Other) override;
    virtual void EndOverlap(CCollider3D* _Other) override;

    void PaveChain();
    void Clear();

    CLONE(CBossChainScript);

public:
    CBossChainScript();
    ~CBossChainScript();

};

