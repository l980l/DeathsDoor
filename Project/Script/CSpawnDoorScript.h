#pragma once
#include <Engine/CScript.h>

// ���͸� ������Ű�� Door�� ��ũ��Ʈ

class CSpawnDoorScript :
    public CScript
{
private:
    wstring     m_strSpawnMstName;  // �ڽ��� ������ų ������ �̸�
    float       m_fDelay;           // ���͸� ������ų Ÿ�̹�
    bool        m_bSpawn;

public:
    virtual void begin() override;
    virtual void tick() override;
    void SetSpawnMst(wstring _strSpawnNum) { m_strSpawnMstName = _strSpawnNum; }

    CLONE(CSpawnDoorScript);
public:
    CSpawnDoorScript();
    ~CSpawnDoorScript();
};

