#pragma once
#include <Engine\CScript.h>

#include <Engine\Thread.h>
#include <Engine\ThreadQueue.h>

class CLoadLevelThreadScript :
    public CScript
{
protected:
	wstring			m_LevelPath;
	bool			m_bLoadComplete;
	CThreadQueue	m_Queue;

public:
	CThreadQueue* GetQueue()
	{
		return &m_Queue;
	}

	bool IsLoadComplete()	const
	{
		return m_bLoadComplete;
	}

public:
	void SetLoadingLevelPath(const wstring& LevelPath)
	{
		m_LevelPath = LevelPath;
	}

public:
	virtual void tick() override;

public:
	virtual void SaveToLevelFile(FILE* _File) override;
	virtual void LoadFromLevelFile(FILE* _FILE) override;

private:
    CLONE(CLoadLevelThreadScript);
public:
    CLoadLevelThreadScript();
    ~CLoadLevelThreadScript();
};

