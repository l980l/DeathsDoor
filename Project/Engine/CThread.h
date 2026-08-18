#pragma once

class CThread
{
    friend class CThreadMgr;

protected:
    CThread();
    virtual ~CThread() = 0;

    HANDLE           m_Thread;
    HANDLE           m_StartEvent;
    bool             m_Loop;
    bool             m_Suspend;
    CRITICAL_SECTION m_CRT;

public:
    bool IsSuspend() const
    {
        return m_Suspend;
    }

    void SetLoop(bool Loop)
    {
        m_Loop = Loop;
    }

    void Suspend();
    void Resume();
    void ReStart();
    void Stop();
    void Start() const;

    virtual bool Init();
    virtual void Run() = 0;

private:
    static unsigned int __stdcall ThreadFunction(void* Arg);
};
