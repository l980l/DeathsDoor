#include "pch.h"
#include "CLevelMgr.h"
#include "CPhysXMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CPhysXMgr.h"
#include "CDetourMgr.h"

CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
		delete m_pCurLevel;
}

void CLevelMgr::init()
{
	m_pCurLevel = new CLevel;
	m_pCurLevel->ChangeState(LEVEL_STATE::STOP);
}

void CLevelMgr::tick()
{
	m_pCurLevel->clear();

	if (LEVEL_STATE::PLAY == m_pCurLevel->GetState())
	{
		m_pCurLevel->tick();		
	}

	m_pCurLevel->finaltick();
}


CGameObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_pCurLevel->FindObjectByName(_strName);	
}

void CLevelMgr::FindObjectByName(const wstring& _strName, vector<CGameObject*>& _vec)
{
	m_pCurLevel->FindObjectByName(_strName, _vec);
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel)
{
	if (nullptr != m_pCurLevel)
	{
		CPhysXMgr::GetInst()->Clear();
		delete m_pCurLevel;
		m_pCurLevel = nullptr;
	}
	
	m_pCurLevel = _NextLevel;
	CPhysXMgr::GetInst()->ChangeLevel((LEVEL_TYPE)_NextLevel->GetLevelType());
	CDetourMgr::GetInst()->ChangeLevel((LEVEL_TYPE)_NextLevel->GetLevelType());
}
