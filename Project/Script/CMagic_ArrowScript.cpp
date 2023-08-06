#include "pch.h"
#include "CMagic_ArrowScript.h"
#include "CStateScript.h"

CMagic_ArrowScript::CMagic_ArrowScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_ARROWSCRIPT)
	, m_vDir{}
	, m_fDamage(0.f)
{
}

CMagic_ArrowScript::~CMagic_ArrowScript()
{
}
void CMagic_ArrowScript::begin()
{
}

void CMagic_ArrowScript::tick()
{
	Vec3 CurPos = Transform()->GetWorldPos();
	CurPos += m_vDir * m_fSpeed * DT;
	Transform()->SetRelativePos(CurPos);
}

void CMagic_ArrowScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
	{
		Stat CurStat = _Other->GetOwner()->GetScript<CStateScript>()->GetStat();
		CurStat.HP -= m_fDamage;
		_Other->GetOwner()->GetScript<CStateScript>()->SetStat(CurStat);
		Destroy();
	}
	// 터지는 효과 등 나오게 할 것
}

void CMagic_ArrowScript::EndOverlap(CCollider3D* _Other)
{
}


void CMagic_ArrowScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_ArrowScript::LoadFromLevelFile(FILE* _FILE)
{
}

