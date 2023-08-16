#include "pch.h"
#include "CHitStoneScript.h"

CHitStoneScript::CHitStoneScript() :
	CScript(SCRIPT_TYPE::HITSTONESCRIPT),
	b_hit(false),
	b_move(false)
{
}

CHitStoneScript::~CHitStoneScript()
{
}

void CHitStoneScript::begin()
{
}

void CHitStoneScript::tick()
{
	Vec3 vCurPos = Transform()->GetWorldPos();
	if (b_hit && !b_move)
	{
		Transform()->SetRelativePos(vCurPos.x, vCurPos.y - 100.f * DT, vCurPos.z);
	}
	m_fMoveDistance = (m_vStartPos - Transform()->GetWorldPos()).Length();
	if (m_fMoveDistance > 100.f && b_hit)
	{
		b_move = true;
	}
}

void CHitStoneScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetName() == L"Arrow")
	{
		b_hit = true;
		m_vStartPos = Transform()->GetWorldPos();
	}
}

void CHitStoneScript::OnOverlap(CCollider3D* _Other)
{
}

void CHitStoneScript::EndOverlap(CCollider3D* _Other)
{
}
