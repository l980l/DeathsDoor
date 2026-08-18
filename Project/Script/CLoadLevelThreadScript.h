#pragma once

#include <Engine/CScript.h>
#include <Engine/CLevel.h>

class CLoadLevelThreadScript :
    public CScript
{
    class CLoadingThread* m_LoadingThread;
    class CThreadQueue*   m_LoadingQueue;
    CLevel*               m_LoadLevel;

public:
    void SetLoadLevel(CLevel* _LoadLevel)
    {
        m_LoadLevel = _LoadLevel;
    }

    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CLoadLevelThreadScript);
    CLoadLevelThreadScript();
    virtual ~CLoadLevelThreadScript() override;
};
