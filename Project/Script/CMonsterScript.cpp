#include "pch.h"
#include "CMonsterScript.h"


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
}

CMonsterScript::~CMonsterScript()
{
}

void CMonsterScript::tick()
{
	if(KEY_TAP(KEY::SPACE))
	{
		CGameObject* pObj = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Bat")->Clone();
		SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);
	}
}

void CMonsterScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Parent Object" == _Other->GetOwner()->GetName())
	{
		//Destroy();	

		SetLifeSpan(2.f);
	}
}

