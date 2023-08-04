#pragma once
#include <Engine/CScript.h>
class CWallScript :
    public CScript
{
private:
    int     m_iRoomNum;
    Vec3     m_vStartPos;
    bool    m_bOpen;
    bool    m_bClose;
    float    m_fMoveDistance;

public:
    virtual void tick() override;

    void SetRoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }
    void CloseDoor();
    void OpenDoor();

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CWallScript);

public:
    CWallScript();
    ~CWallScript();

    friend class CSpawnMgr;
};

