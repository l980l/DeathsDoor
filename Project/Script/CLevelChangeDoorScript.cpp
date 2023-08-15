#include "pch.h"
#include "CLevelChangeDoorScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CEventMgr.h>

CLevelChangeDoorScript::CLevelChangeDoorScript()
	: CScript((UINT)SCRIPT_TYPE::LEVELCHANGEDOORSCRIPT)
	, m_iChangeLevel(-1)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iChangeLevel, "Type");
}

CLevelChangeDoorScript::~CLevelChangeDoorScript()
{
}

void CLevelChangeDoorScript::begin()
{
	Vec4 Color = Vec4(0.f);
	switch ((LEVEL_TYPE)m_iChangeLevel)
	{
	case LEVEL_TYPE::CASTLE_FIELD:
		Color = Vec4(0.1f, 0.1f, 0.1f, 0.05f);
		break;
	case LEVEL_TYPE::CASTLE_BOSS:
		Color = Vec4(0.2f, 0.2f, 0.2f, 0.2f);
		break;
	case LEVEL_TYPE::FOREST_FIELD:
		Color = Vec4(0.4f, 1.f, 0.4f, 1.f);
		break;
	case LEVEL_TYPE::ICE_FIELD:
		Color = Vec4(0.2f, 1.f, 0.2f, 1.f);
		break;
	case LEVEL_TYPE::ICE_BOSS:
		Color = Vec4(0.4f, 0.4f, 1.f, 1.f);
		break;
	case LEVEL_TYPE::HALL:
		Color = Vec4(0.2f, 0.2f, 1.f, 1.f);
		break;
	}

	int a = 1;
	float pow = 0.1;
	GetOwner()->GetRenderComponent()->GetMaterial(0)->SetScalarParam(INT_0, &a);
	GetOwner()->GetRenderComponent()->GetMaterial(0)->SetScalarParam(VEC4_0, &Color);
}

void CLevelChangeDoorScript::OnOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::PLAYER)
	{
		if (KEY_TAP(KEY::E))
		{
			g_tNextLevel = (LEVEL_TYPE)m_iChangeLevel;

			CLevel* NewLevel = CLevelSaveLoadInScript::Stop(L"Level\\LLL.lv", LEVEL_STATE::STOP);
			NewLevel->SetName(L"LevelLoading");
			NewLevel->SetLevelType(m_iChangeLevel);
			tEvent evn = {};
			evn.Type = EVENT_TYPE::LEVEL_CHANGE;
			evn.wParam = (DWORD_PTR)NewLevel;
			evn.lParam = (DWORD_PTR)NewLevel->GetLevelType();
			CEventMgr::GetInst()->AddEvent(evn);
		}
	}
}

void CLevelChangeDoorScript::SaveToLevelFile(FILE* _FILE)
{
	fwrite(&m_iChangeLevel, sizeof(int), 1, _FILE);
}

void CLevelChangeDoorScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_iChangeLevel, sizeof(int), 1, _FILE);
}
