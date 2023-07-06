#pragma once

#include "Thread.h"
#include "ThreadQueue.h"

enum class ELoadingHeader
{
	LoadingRate
};

class CLoadingThread :
    public CThread
{
	friend class CThreadMgr;

protected:
	CLoadingThread();
	virtual ~CLoadingThread();

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
	virtual void Run();

private:
	void LoadingCallback(float Rate);
};

