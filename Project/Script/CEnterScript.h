#pragma once
#include <Engine/CScript.h>

class CColiider3D;

// Coliider�� ������ ���� �Ա��� ��ġ��
// Player�� �浹�ϸ� �ڽ��� �����ϸ� ���� �ݰ� SpawnMgr�� �ڽ��� ���� ��ȣ�� ���� Ȱ��ȭ��Ű�� ��.
class CEnterScript :
    public CScript
{
private:
    int      m_iRoomNum;

public:
    virtual void begin() override;
    virtual void tick() override {};

public:
    void SetRoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }

    virtual void BeginOverlap(CCollider3D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CEnterScript);
public:
    CEnterScript();
    ~CEnterScript();

    friend class CSpawnMgr;
};

