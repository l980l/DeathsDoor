#include "pch.h"
#include "CMagic_HookScript.h"

CMagic_HookScript::CMagic_HookScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_HOOKSCRIPT)
{
}

CMagic_HookScript::~CMagic_HookScript()
{
}

void CMagic_HookScript::begin()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HOOK, false);
	// 훅 프리팹을 클릭한 방향으로 날리기
}

void CMagic_HookScript::tick()
{
}

void CMagic_HookScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER
		|| _Other->GetOwner()->GetLayerIndex() == (int)LAYER::ANCHOR)
	{
		m_bHook = true;
		m_vHookPos = _Other->Transform()->GetWorldPos();
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
