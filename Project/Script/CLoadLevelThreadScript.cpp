#include "pch.h"
#include "CLoadLevelThreadScript.h"

#include <Engine\LoadingThread.h>
#include <Engine\CPathMgr.h>
#include <Engine\DataStream.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CEventMgr.h>

#include "CLevelSaveLoadInScript.h"

CLoadLevelThreadScript::CLoadLevelThreadScript()
	: CScript((UINT)SCRIPT_TYPE::LOADLEVELTHREADSCRIPT)
	, m_bLoadComplete(false)
{
}

CLoadLevelThreadScript::~CLoadLevelThreadScript()
{
}

void CLoadLevelThreadScript::tick()
{
	wstring strPath = L"Level\\TestLevel.lv";

	// Level 불러오기
	CLevel* pLoadedLevel = CLevelSaveLoadInScript::LoadLevel(strPath);

	tEvent evn = {};
	evn.Type = EVENT_TYPE::LEVEL_CHANGE;
	evn.wParam = (DWORD_PTR)pLoadedLevel;

	CEventMgr::GetInst()->AddEvent(evn);

	m_bLoadComplete = true;
}

void CLoadLevelThreadScript::SaveToLevelFile(FILE* _File)
{
}

void CLoadLevelThreadScript::LoadFromLevelFile(FILE* _FILE)
{
}
