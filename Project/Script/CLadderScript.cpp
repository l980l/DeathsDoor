#include "pch.h"
#include "CLadderScript.h"
#include "CStateScript.h"
#include "CLevelSaveLoadInScript.h"

CLadderScript::CLadderScript()
	: CScript((UINT)SCRIPT_TYPE::LADDERSCRIPT)
	, m_pInterectionImage(nullptr)
	, m_fHeight(0.f)
{
	//if (nullptr == m_pInterectionImage)
	//	m_pInterectionImage = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\LadderImage.prefab", (int)LAYER::DEFAULT, Vec3(0.f));
}

CLadderScript::~CLadderScript()
{
}

void CLadderScript::BeginOverlap(CCollider3D* _Other)
{
}

void CLadderScript::OnOverlap(CCollider3D* _Other)
{
	//if ((int)LAYER::PLAYER == _Other->GetOwner()->GetLayerIndex())
	//{
	//	if(_Other->GetOwner()->GetScript<CStateScript>()->GetCurState()
	//		!= _Other->GetOwner()->GetScript<CStateScript>()->FindState(L"Ladder"))
	//		m_pInterectionImage->Transform()->SetRelativeScale(Vec3(20.f));
	//	else
	//		m_pInterectionImage->Transform()->SetRelativeScale(Vec3(0.f));
	//}
}

void CLadderScript::EndOverlap(CCollider3D* _Other)
{
	//if ((int)LAYER::PLAYER == _Other->GetOwner()->GetLayerIndex())
	//{
	//	m_pInterectionImage->Transform()->SetRelativeScale(Vec3(0.f));
	//}
}
