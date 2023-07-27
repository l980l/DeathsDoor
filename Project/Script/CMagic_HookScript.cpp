#include "pch.h"
#include "CMagic_HookScript.h"
#include "CPlyMagic_Hook.h"

CMagic_HookScript::CMagic_HookScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_HOOKSCRIPT)
	, m_pOwner(nullptr)
	, m_fTime(0.f)
{
}

CMagic_HookScript::~CMagic_HookScript()
{
}

void CMagic_HookScript::begin()
{
}

void CMagic_HookScript::tick()
{
	m_fTime += DT;
	if (m_fTime > 0.5f)
	{
		Rigidbody()->SetVelocity(-m_vThrownDir * 300000.f);

		Vec3 Diff = m_vStartPos - Transform()->GetWorldPos();
		if(abs(Diff.x) + abs(Diff.z) < 100.f )
		{
			m_pOwner->FailSnatch();
			Destroy();
			m_fTime = 0.f;
		}
	}
}

void CMagic_HookScript::BeginOverlap(CCollider3D* _Other)
{
	// 갈고리를 걸 수 있는 obj와 충돌했다면 hooking 상태로 전환
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER
		|| _Other->GetOwner()->GetLayerIndex() == (int)LAYER::ANCHOR)
	{
		m_pOwner->Snatch(_Other->Transform()->GetWorldPos());
	}
}

void CMagic_HookScript::EndOverlap(CCollider3D* _Other)
{
}

void CMagic_HookScript::SaveToLevelFile(FILE* _File)
{
}

void CMagic_HookScript::LoadFromLevelFile(FILE* _FILE)
{
}
