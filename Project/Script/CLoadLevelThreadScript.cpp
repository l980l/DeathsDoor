#include "pch.h"
#include "CLoadLevelThreadScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CLoadingThread.h"

#include <Engine\DataStream.h>
#include <Engine\CEventMgr.h>
#include <Engine\CThreadQueue.h>
#include <Engine\CThreadMgr.h>


CLoadLevelThreadScript::CLoadLevelThreadScript()
	: CScript((UINT)SCRIPT_TYPE::LOADLEVELTHREADSCRIPT)
{
}

CLoadLevelThreadScript::~CLoadLevelThreadScript()
{
}

void CLoadLevelThreadScript::begin()
{
	m_LoadingThread = CThreadMgr::GetInst()->Create<CLoadingThread>("Loading");

	switch (g_tNextLevel)
	{
	case LEVEL_TYPE::CASTLE_FIELD:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Castle.lv");
		break;
	case LEVEL_TYPE::CASTLE_BOSS:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Castle_Boss.lv");
		break;
	case LEVEL_TYPE::FOREST_FIELD:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Forest.lv");
		break;
	case LEVEL_TYPE::ICE_FIELD:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Ice.lv");
		break;
	case LEVEL_TYPE::ICE_BOSS:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Ice_Boss.lv");
		break;
	case LEVEL_TYPE::HALL:
		m_LoadingThread->SetLoadingLevelPath(L"Level\\Hall.lv");
		break;
	}

	m_LoadingThread->SetLoadLevelThreadScript(this);

	m_LoadingQueue = m_LoadingThread->GetQueue();

	m_LoadingThread->Start();
}

void CLoadLevelThreadScript::tick()
{
	// Queue�� �����Ͱ� ���� ��� �޾ƿͼ� ó���Ѵ�. 
	// �ϴ� �츮 ������ �ε����� �ȳ����� �����̶� �� ����?
	if (!m_LoadingQueue->empty())
	{
		/*int	Header, Size;
		unsigned char	Data[1024] = {};

		m_LoadingQueue->pop(&Header, &Size, Data);

		CDataStream	stream;
		stream.SetBuffer(Data);

		float	Rate = 0.f;

		stream.GetData<float>(&Rate, 4);*/
	}

	if (m_LoadingThread->IsLoadComplete())
	{
		tEvent evn = {};
		evn.Type = EVENT_TYPE::LEVEL_CHANGE;
		evn.wParam = (DWORD_PTR)m_LoadLevel;
		evn.lParam = (DWORD_PTR)m_LoadLevel->GetLevelType();

		CEventMgr::GetInst()->AddEvent(evn);

		CThreadMgr::GetInst()->Delete("Loading");
	}
}

void CLoadLevelThreadScript::SaveToLevelFile(FILE* _File)
{
}

void CLoadLevelThreadScript::LoadFromLevelFile(FILE* _FILE)
{
}

