#include "pch.h"
#include "CBatScript.h"
#include "BatStates.h"
#include <Engine/components.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>

CBatScript::CBatScript()	:
	CScript((UINT)SCRIPT_TYPE::BATSCRIPT)
{
}

CBatScript::~CBatScript()
{
	if (nullptr == m_pState)
		delete m_pState;
}


void CBatScript::begin()
{
	m_pState = GetOwner()->GetScript<CStateScript>();
	m_pState->AddState(L"Idle", new CBatIdle);
	m_pState->AddState(L"Recognize", new CBatRecognize);
	m_pState->AddState(L"Trace", new CBatChase);
	m_pState->AddState(L"Attack", new CBatAttack);
	
	m_pState->ChangeState(L"Idle");
}

void CBatScript::tick()
{
	
	Vec3 batPos = GetOwner()->Transform()->GetWorldPos();
	if (KEY_PRESSED(KEY::W))
	{
		batPos.x += 
	}
	if (KEY_PRESSED(KEY::S))
	{

	}
	if (KEY_PRESSED(KEY::A))
	{

	}
	if (KEY_PRESSED(KEY::D))
	{

	}
}

void CBatScript::BeginOverlap(CCollider2D* _Other)
{
}
