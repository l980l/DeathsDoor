#pragma once
#include <Engine/CScript.h>

class CCrowBossChainThrow;

class CBossChainScript :
    public CScript
{
private:
    CCrowBossChainThrow*    m_pChainScript;
    vector<CGameObject*>    m_vecChain;
    Vec3                    m_vThrowStartPos;       // ������ ������ ��ġ
    Vec3                    m_vThrownDir;           // ������ ����(�Ÿ��� ���)
    Vec3                    m_vThrownRot;           // ������ ����(ȸ������)
    float                   m_fThrowDistance;       // ���ư��� �ϴ� �Ÿ�
    float                   m_fDistancetoTarget;    // Hookpos���� �Ÿ�
    float                   m_fChainSpacing;        // ü�� �� �����ϴ� ����
    bool                    m_bActive;

private:
    void SetChainScript(CCrowBossChainThrow* _pChainScript) { m_pChainScript = _pChainScript; }
    void SetChain(vector<CGameObject*>& _vecChain) { m_vecChain = _vecChain; }

public:
    virtual void begin() override;
    virtual void tick() override;

    void SetThrowDir(Vec3 _vThrowDir) { m_vThrownDir = _vThrowDir.Normalize(); }
    void SetThrowRot(Vec3 _vThrowRot) { m_vThrownRot = _vThrowRot; }
    void SetThrowStartPos(Vec3 _vStartPos) { m_vThrowStartPos = _vStartPos; }
    void Active(bool _bActive);

    void PaveChain();
    void Clear();

    CLONE(CBossChainScript);

public:
    CBossChainScript();
    ~CBossChainScript();

};

