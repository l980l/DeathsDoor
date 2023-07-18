#pragma once
#include <Engine/CScript.h>

class CState;

class CStateScript :
    public CScript
{
private:
    map<wstring, CState*>   m_mapState;     // 전체 State 
    CState*                 m_pCurState;    // 현재 State

public:
    virtual void begin() override;
    virtual void tick() override;

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

    CLONE(CStateScript);

public:
    CStateScript();
    ~CStateScript();
};

