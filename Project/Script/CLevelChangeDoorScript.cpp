#include "pch.h"
#include "CLevelChangeDoorScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CEventMgr.h>

CLevelChangeDoorScript::CLevelChangeDoorScript()
	: CScript((UINT)SCRIPT_TYPE::LEVELCHANGEDOORSCRIPT)
	, m_tChangeLevel()
{
}

CLevelChangeDoorScript::~CLevelChangeDoorScript()
{
}

void CLevelChangeDoorScript::OnOverlap(CCollider3D* _Other)
{
	if (_Other->GetOwner()->GetLayerIndex() == (int)LAYER::PLAYER)
	{
		if (KEY_TAP(KEY::E))
		{
			wstring wstrChangeLevelFilePath;
			wstring wstrLevelName;
			switch (m_tChangeLevel)
			{
			case LEVEL_TYPE::HALL:
				wstrChangeLevelFilePath = L"Level\\Hall.lv";
				wstrLevelName = L"HALL";
				break;
			case LEVEL_TYPE::CASTLE_FIELD:
				wstrChangeLevelFilePath = L"Level\\Castle.lv";
				wstrLevelName = L"CASTLE";
				break;
			case LEVEL_TYPE::CASTLE_BOSS:
				wstrChangeLevelFilePath = L"Level\\Castle_Boss.lv";
				wstrLevelName = L"CASTLE_BOSS";
				break;
			case LEVEL_TYPE::FOREST_FIELD:
				wstrChangeLevelFilePath = L"Level\\Forest.lv";
				wstrLevelName = L"FOREST";
				break;
			case LEVEL_TYPE::ICE_FIELD:
				wstrChangeLevelFilePath = L"Level\\Ice.lv";
				wstrLevelName = L"ICE";
				break;
			case LEVEL_TYPE::ICE_BOSS:
				wstrChangeLevelFilePath = L"Level\\Ice_Boss.lv";
				wstrLevelName = L"ICE_BOSS";
				break;
			}
			CLevel* NewLevel = CLevelSaveLoadInScript::Stop(wstrChangeLevelFilePath, LEVEL_STATE::STOP);
			NewLevel->SetName(wstrLevelName);
			NewLevel->SetLevelType((int)m_tChangeLevel);
			tEvent evn = {};
			evn.Type = EVENT_TYPE::LEVEL_CHANGE;
			evn.wParam = (DWORD_PTR)NewLevel;
			evn.lParam = (DWORD_PTR)NewLevel->GetLevelType();
			CEventMgr::GetInst()->AddEvent(evn);
		}
	}
}
