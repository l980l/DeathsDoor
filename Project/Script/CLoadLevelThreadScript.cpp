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

	m_LoadingThread->SetLoadingLevelPath(L"Level\\TestLevel.lv");

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

