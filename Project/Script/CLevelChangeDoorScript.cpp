#include "pch.h"
#include "CLevelChangeDoorScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CEventMgr.h>

CLevelChangeDoorScript::CLevelChangeDoorScript()
    : CScript(static_cast<UINT>(SCRIPT_TYPE::LEVELCHANGEDOORSCRIPT))
    , m_iChangeLevel(-1)
{
    AddScriptParam(SCRIPT_PARAM::INT, &m_iChangeLevel, "Type");
}

CLevelChangeDoorScript::~CLevelChangeDoorScript()
{
}

void CLevelChangeDoorScript::OnOverlap(CCollider3D* _Other)
{
    if (_Other->GetOwner()->GetLayerIndex() == static_cast<int>(LAYER::PLAYER))
        if (KEY_TAP(KEY::E))
        {
            if (m_iChangeLevel == -1)
                return;
            g_tNextLevel = static_cast<LEVEL_TYPE>(m_iChangeLevel);

            CLevel* pNewLevel = CLevelSaveLoadInScript::Stop(L"Level\\LLL.lv", LEVEL_STATE::STOP);
            pNewLevel->SetName(L"Level\\LLL.lv");
            pNewLevel->SetLevelType(m_iChangeLevel);
            tEvent evn = {};
            evn.Type   = EVENT_TYPE::LEVEL_CHANGE_PLAY;
            evn.wParam = (DWORD_PTR)pNewLevel;
            evn.lParam = static_cast<DWORD_PTR>(pNewLevel->GetLevelType());
            CEventMgr::GetInst()->AddEvent(evn);
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
