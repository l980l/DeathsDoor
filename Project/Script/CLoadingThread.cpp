#include "pch.h"
#include "CLoadingThread.h"
#include "CLevelSaveLoadInScript.h"

#include <Engine\CPathMgr.h>
#include <Engine\DataStream.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CEventMgr.h>


CLoadingThread::CLoadingThread() :
	m_bLoadComplete(false)
	, m_LoadLevelThreadScript(nullptr)
{
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	// Level �ҷ�����
	CLevel* pLoadedLevel = CLevelSaveLoadInScript::Stop(m_LevelPath, LEVEL_STATE::STOP);

	m_LoadLevelThreadScript->SetLoadLevel(pLoadedLevel);

	m_bLoadComplete = true;
}
