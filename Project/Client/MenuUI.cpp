#include "pch.h"
#include "MenuUI.h"

#include "CLevelSaveLoad.h"
#include <Engine/CEventMgr.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CScript.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CPhysXMgr.h>

#include <Script/CScriptMgr.h>

#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "InspectorUI.h"


MenuUI::MenuUI()
    : UI("##Menu")
{
    SetName("Menu");
}

MenuUI::~MenuUI()
{
}

void MenuUI::finaltick()
{
    if (!IsActive())
        return;

    render_update();
}

int MenuUI::render_update()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save Level"))
                // Level ����
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurLevel());
            if (ImGui::MenuItem("Load Level"))
            {
                // Level �ҷ�����
                CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(LEVEL_STATE::STOP);

                tEvent evn = {};
                evn.Type   = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam = (DWORD_PTR)pLoadedLevel;

                CEventMgr::GetInst()->AddEvent(evn);
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("GameObject"))
        {
            // ���� ������ ���ӿ�����Ʈ ����
            if (ImGui::BeginMenu("Create Empty Object"))
            {
                //CreateEmptyObject();
                if (ImGui::MenuItem("DEFAULT"))
                    CreateEmptyObject(static_cast<int>(LAYER::DEFAULT));
                else if (ImGui::MenuItem("MainCamera"))
                    CreateEmptyObject(static_cast<int>(LAYER::MAINCAMERA));
                else if (ImGui::MenuItem("SubCamera"))
                    CreateEmptyObject(static_cast<int>(LAYER::SUBCAMERA));
                else if (ImGui::MenuItem("Player"))
                    CreateEmptyObject(static_cast<int>(LAYER::PLAYER));
                else if (ImGui::MenuItem("Monster"))
                    CreateEmptyObject(static_cast<int>(LAYER::MONSTER));
                else if (ImGui::MenuItem("PlayerProjectile"))
                    CreateEmptyObject(static_cast<int>(LAYER::PLAYERPROJECTILE));
                else if (ImGui::MenuItem("MonsterProjectile"))
                    CreateEmptyObject(static_cast<int>(LAYER::MONSTERPROJECTILE));
                else if (ImGui::MenuItem("Wall"))
                    CreateEmptyObject(static_cast<int>(LAYER::WALL));
                else if (ImGui::MenuItem("Item"))
                    CreateEmptyObject(static_cast<int>(LAYER::ITEM));
                else if (ImGui::MenuItem("Ground"))
                    CreateEmptyObject(static_cast<int>(LAYER::GROUND));
                else if (ImGui::MenuItem("FallArea"))
                    CreateEmptyObject(static_cast<int>(LAYER::FALLAREA));
                else if (ImGui::MenuItem("Ladder"))
                    CreateEmptyObject(static_cast<int>(LAYER::LADDER));
                else if (ImGui::MenuItem("Anchor"))
                    CreateEmptyObject(static_cast<int>(LAYER::ANCHOR));
                else if (ImGui::MenuItem("Braizer"))
                    CreateEmptyObject(static_cast<int>(LAYER::BRAIZER));
                else if (ImGui::MenuItem("NPC"))
                    CreateEmptyObject(static_cast<int>(LAYER::NPC));
                else if (ImGui::MenuItem("ViewPortUI"))
                    CreateEmptyObject(static_cast<int>(LAYER::UI));
                ImGui::EndMenu();
            }
            ImGui::Separator();


            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < static_cast<UINT>(COMPONENT_TYPE::END); ++i)
                {
                    if (ImGui::MenuItem(ToString(static_cast<COMPONENT_TYPE>(i))))
                        AddComponent(static_cast<COMPONENT_TYPE>(i));
                }
                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Add Script"))
            {
                vector<wstring> vecScripts;
                CScriptMgr::GetScriptInfo(vecScripts);

                for (size_t i = 0; i < vecScripts.size(); ++i)
                {
                    string strScriptName = string(vecScripts[i].begin(), vecScripts[i].end());
                    if (ImGui::MenuItem(strScriptName.c_str()))
                        AddScript(vecScripts[i]);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Level"))
        {
            CLevel* CurLevel    = CLevelMgr::GetInst()->GetCurLevel();
            bool    PlayEnable  = true;
            bool    PauseEnable = true;
            bool    StopEnable  = true;

            if (CurLevel->GetState() == LEVEL_STATE::PLAY)
            {
                PlayEnable  = false;
                PauseEnable = true;
                StopEnable  = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::PAUSE)
            {
                PlayEnable  = true;
                PauseEnable = false;
                StopEnable  = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::STOP)
            {
                PlayEnable  = true;
                PauseEnable = false;
                StopEnable  = false;
            }

            if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
            {
                CLevelSaveLoad::Play(L"Level\\Temp.lv", CurLevel);
                CurLevel->ChangeState(LEVEL_STATE::PLAY);
            }
            else if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::PAUSE);
            }
            else if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
            {
                CurLevel->ChangeState(LEVEL_STATE::STOP);
                CLevel* pNewLevel = CLevelSaveLoad::Stop(L"Level\\Temp.lv", LEVEL_STATE::STOP);
                tEvent  evn       = {};
                evn.Type          = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam        = DWORD_PTR(pNewLevel);
                CEventMgr::GetInst()->AddEvent(evn);

                // InspectorUI
                InspectorUI* Inspector = static_cast<InspectorUI*>(ImGuiMgr::GetInst()->FindUI("##Inspector"));
                Inspector->SetTargetObject(nullptr);
            }

            ImGui::EndMenu();
        }


        ImGui::EndMainMenuBar();
    }

    return 0;
}

void MenuUI::CreateEmptyObject(int layerindx) const
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(L"NewObject");

    if (layerindx == static_cast<int>(LAYER::MAINCAMERA))
    {
        pNewObject->SetName(L"MainCamera");
        pNewObject->AddComponent(new CCamera);
        pNewObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC); // ī�޶� ������Ʈ�� ���� ��� ����(����)
        pNewObject->Camera()->SetCameraIndex(0);                    //MainCamera�� ����
        pNewObject->Camera()->SetLayerMaskAll(true);                // ��� ���̾� üũ
        pNewObject->Camera()->SetLayerMask(31, false);              // UI Layer �� ���������� �ʴ´�.
    }
    else if (layerindx == static_cast<int>(LAYER::SUBCAMERA))
    {
        pNewObject->SetName(L"SubCamera");
        pNewObject->AddComponent(new CCamera);
        pNewObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC); // ī�޶� ������Ʈ�� ���� ��� ����(����)
        pNewObject->Camera()->SetCameraIndex(2);                    //SubCamera�� ����
        pNewObject->Camera()->SetLayerMaskAll(false);
        pNewObject->Camera()->SetLayerMask(31, true);
    }
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), layerindx);

    // Outliner �� �����´�.
    OutlinerUI* outliner = static_cast<OutlinerUI*>(ImGuiMgr::GetInst()->FindUI("##Outliner"));

    // �����߰��� ������Ʈ�� �����ͷ� �ϴ� ��尡 �߰��Ǹ�, ���û��·� �ΰ� �Ѵ�.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));
}

void MenuUI::CreatePrefabObject() const
{
}

void MenuUI::AddComponent(COMPONENT_TYPE _type) const
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI*  outliner  = static_cast<OutlinerUI*>(ImGuiMgr::GetInst()->FindUI("##Outliner"));
    InspectorUI* inspector = static_cast<InspectorUI*>(ImGuiMgr::GetInst()->FindUI("##Inspector"));

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    switch (_type)
    {
    case COMPONENT_TYPE::TRANSFORM:
        pSelectedObject->AddComponent(new CTransform);
        break;
    case COMPONENT_TYPE::COLLIDER2D:
        pSelectedObject->AddComponent(new CCollider2D);
        break;
    case COMPONENT_TYPE::COLLIDER3D:
        pSelectedObject->AddComponent(new CCollider3D);
        break;
    case COMPONENT_TYPE::ANIMATOR2D:
        pSelectedObject->AddComponent(new CAnimator2D);
        break;
    case COMPONENT_TYPE::ANIMATOR3D:
        pSelectedObject->AddComponent(new CAnimator3D);
        break;
    case COMPONENT_TYPE::LIGHT2D:
        pSelectedObject->AddComponent(new CLight2D);
        break;
    case COMPONENT_TYPE::LIGHT3D:
        pSelectedObject->AddComponent(new CLight3D);
        break;
    case COMPONENT_TYPE::CAMERA:
        pSelectedObject->AddComponent(new CCamera);
        break;
    case COMPONENT_TYPE::MESHRENDER:
        pSelectedObject->AddComponent(new CMeshRender);
        break;
    case COMPONENT_TYPE::PARTICLESYSTEM:
        pSelectedObject->AddComponent(new CParticleSystem);
        break;
    case COMPONENT_TYPE::TILEMAP:
        pSelectedObject->AddComponent(new CTileMap);
        break;
    case COMPONENT_TYPE::LANDSCAPE:
        pSelectedObject->AddComponent(new CLandScape);
        break;
    case COMPONENT_TYPE::DECAL:
        pSelectedObject->AddComponent(new CDecal);
        break;
    case COMPONENT_TYPE::RIGIDBODY:
        pSelectedObject->AddComponent(new CRigidbody);
        break;
    }

    // Inspector �� ���Ӱ� �߰��� ������Ʈ�� �˸��� ���ؼ� Ÿ���� �ٽ� �˷��ش�.
    inspector->SetTargetObject(pSelectedObject);
}

void MenuUI::AddScript(const wstring& _strScriptName) const
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI*  outliner  = static_cast<OutlinerUI*>(ImGuiMgr::GetInst()->FindUI("##Outliner"));
    InspectorUI* inspector = static_cast<InspectorUI*>(ImGuiMgr::GetInst()->FindUI("##Inspector"));

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    CScript* pScript = CScriptMgr::GetScript(_strScriptName);

    pSelectedObject->AddComponent(pScript);

    inspector->SetTargetObject(pSelectedObject);
}
