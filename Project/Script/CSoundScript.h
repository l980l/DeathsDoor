#pragma once
#include <Engine/CSound.h>
#include <Engine/CScript.h>
class CSoundScript :
    public CScript
{
private:
    Ptr<CSound>     pSound;
    float                    m_volume;
    int                       m_idx;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider3D* _Other) override;
    Ptr<CSound> AddSound(wstring _filename,int _repeat, float _volume = 0.5f);
    void SetIndex(int _idx) { m_idx = _idx; }
    int GetIndex() { return m_idx; }
    CLONE(CSoundScript);
public:
    CSoundScript();
    ~CSoundScript();
};

