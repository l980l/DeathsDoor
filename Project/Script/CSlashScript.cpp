#include "pch.h"
#include "CSlashScript.h"
#include "CStateScript.h"
#include "CMonsterScript.h"

CSlashScript::CSlashScript()
	: CScript((UINT)SCRIPT_TYPE::SLASHSCRIPT)
{
}

CSlashScript::~CSlashScript()
{
}

void CSlashScript::BeginOverlap(CCollider3D* _Other)
{
	if(_Other->GetOwner()->GetScript<CStateScript>())
	{
		Stat CurStat = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		CurStat.HP -= 50;
		if (CurStat.HP <= 0)
			CurStat.HP = 0;

		_Other->GetOwner()->GetScript<CStateScript>()->SetStat(CurStat);
		_Other->GetOwner()->GetScript<CMonsterScript>()->SetLastHitTime();
	}
}
