#include "pch.h"
#include "CEnterScript.h"
#include "CSpawnMgr.h"

CEnterScript::CEnterScript()
	: CScript((UINT)SCRIPT_TYPE::ENTERSCRIPT)
	, m_iRoomNum(-1)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CEnterScript::~CEnterScript()
{
}

void CEnterScript::begin()
{
	CSpawnMgr::GetInst()->RegisterDoor(m_iRoomNum, GetOwner());
}

void CEnterScript::tick()
{
}

void CEnterScript::BeginOverlap(CColiider3D* _Other)
{
	CSpawnMgr::GetInst()->SetFence(m_iRoomNum, false);
	SetLifeSpan(0.f);
}

void CEnterScript::SaveToLevelFile(FILE* _File)
{
}

void CEnterScript::LoadFromLevelFile(FILE* _File)
{
}
