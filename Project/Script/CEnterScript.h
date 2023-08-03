#pragma once
#include <Engine/CScript.h>
class CDoorScript :
    public CScript
{
private:
    int      m_iRoomNum;
    bool     m_bOpen;
    bool     m_bClose;
    Vec3     m_vStartPos;
    float    m_fMoveDistance;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    void SetRoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }
    void CloseDoor();
    void OpenDoor();

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CDoorScript);
public:
    CDoorScript();
    CDoorScript(const CDoorScript& _Other);
    ~CDoorScript();

    friend class CSpawnMgr;
};

