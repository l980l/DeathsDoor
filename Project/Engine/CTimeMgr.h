#pragma once


class CTimeMgr
    : public CSingleton<CTimeMgr>
{
    SINGLE(CTimeMgr);
    LARGE_INTEGER m_llPrevCount;
    LARGE_INTEGER m_llCurCount;
    LARGE_INTEGER m_llFrequency;

    UINT  m_iCallCount;
    float m_fDeltaTime;
    float m_fTime;

public:
    void init();
    void tick();
    void render();

    float GetDeltaTime() const { return m_fDeltaTime; }
};
