#pragma once
#include <Engine/CScript.h>
class CFenseScript :
    public CScript
{
    int     m_iRoomNum;
    Vec3     m_vStartPos;
    bool    m_bOpen;
    bool    m_bClose;
    float    m_fMoveDistance;

public:
    void SetRoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }
    virtual void begin() override;
    virtual void tick() override;

    void CloseFence();
    void OpenFence();

    CLONE(CFenseScript);
public:
    CFenseScript();
    ~CFenseScript();
    friend class CSpawnMgr;
};

