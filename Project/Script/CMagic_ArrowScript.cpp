#include "pch.h"
#include "CMagic_ArrowScript.h"

CMagic_ArrowScript::CMagic_ArrowScript()
	: CScript((UINT)SCRIPT_TYPE::MAGIC_ARROWSCRIPT)
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
	CurPos += m_vDir* m_fSpeed* DT;
	Transform()->SetRelativePos(CurPos);
}

void CMagic_ArrowScript::BeginOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::MONSTER)
		Destroy();
	// ������ ȿ�� �� ������ �� ��
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

