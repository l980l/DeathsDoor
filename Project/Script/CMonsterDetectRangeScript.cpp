#include "pch.h"
#include "CMonsterDetectRangeScript.h"
#include "CMonsterScript.h"

void CMonsterDetectRangeScript::begin()
{
}

void CMonsterDetectRangeScript::tick()
{
}

void CMonsterDetectRangeScript::BeginOverlap(CCollider3D* _Other)
{
	// Player�� �ε��� ��쿡��.
	if (_Other->GetOwner() == CLevelMgr::GetInst()->FindObjectByName(L"Player"))
	{
		m_bDetect = true;
		
		GetOwner()->GetParent()->GetScript<CMonsterScript>()->SetDetect(true);

		Destroy();
	}
}

void CMonsterDetectRangeScript::OnOverlap(CCollider3D* _Other)
{
	int a = 0;
}


CMonsterDetectRangeScript::CMonsterDetectRangeScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERDETECTRANGESCRIPT)
	, m_bDetect(false)
{
}

CMonsterDetectRangeScript::~CMonsterDetectRangeScript()
{
}
