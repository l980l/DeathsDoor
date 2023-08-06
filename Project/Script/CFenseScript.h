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
    virtual void begin() override;
    virtual void tick() override;

    void CloseDoor();
    void OpenDoor();

    CLONE(CFenseScript);
public:
    CFenseScript();
    ~CFenseScript();

};

