#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CStateScript.h"
#include "PlayerStates.h"

#include <Engine\CRenderMgr.h>

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pState(nullptr)
	, m_fSpeed(0.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Speed");
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr == m_pState)
		delete m_pState;
}

void CPlayerScript::begin()
{
	m_pState = GetOwner()->GetScript<CStateScript>();
	m_pState->AddState(L"Idle", new CPlyIdle);
	m_pState->AddState(L"Walk", new CPlyWalk);
	m_pState->ChangeState(L"Idle");
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	
}

void CPlayerScript::Shoot()
{
}



void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	
}


void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}