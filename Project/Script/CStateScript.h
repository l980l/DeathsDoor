#pragma once
#include <Engine/CScript.h>

class CState;

class CStateScript :
    public CScript
{
private:
    map<wstring, CState*>   m_mapState;     // ��ü State 
    CState*                 m_pCurState;    // ���� State
    Stat                    m_tStat;


public:
    virtual void begin() override;
    virtual void tick() override;

    Stat GetStat() { return m_tStat; }
    void SetStat(Stat _tStat) { m_tStat = _tStat; }

    void AddState(const wstring& _strKey, CState* _pState);
    CState* GetCurState() { return m_pCurState; }
    CState* FindState(const wstring& _strKey)
    {
        map<wstring, CState*>::iterator iter = m_mapState.find(_strKey);
        if (iter != m_mapState.end())
            return iter->second;
        return nullptr;
    }
    void ChangeState(const wstring& _strStateName);

    virtual void BeginOverlap(CCollider2D* _Other);
    virtual void OnOverlap(CCollider2D* _Other);
    virtual void EndOverlap(CCollider2D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CStateScript);

public:
    CStateScript();
    ~CStateScript();
};

