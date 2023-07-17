#include "pch.h"
#include "MenuUI.h"

#include "CLevelSaveLoad.h"
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>
#include <Engine\CScript.h>
#include <Engine/CLevelMgr.h>

#include <Script\CScriptMgr.h>



#include "ImGuiMgr.h"
#include "OutlinerUI.h"
#include "InspectorUI.h"
#include "CLevelSaveLoad.h"



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
            {
                // Level ����
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurLevel());
            }
            if (ImGui::MenuItem("Load Level"))
            {
                // Level �ҷ�����
                CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(LEVEL_STATE::STOP);

                tEvent evn = {};
                evn.Type = EVENT_TYPE::LEVEL_CHANGE;
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
                if (ImGui::MenuItem("DefaultLayer"))
                    CreateEmptyObject(0);
                else if (ImGui::MenuItem("Map"))
                    CreateEmptyObject(1);
                else if (ImGui::MenuItem("Player"))
                    CreateEmptyObject(2);
                else if (ImGui::MenuItem("Monster"))
                    CreateEmptyObject(3);
                else if (ImGui::MenuItem("PlayerProjectile"))
                    CreateEmptyObject(4);
                else if (ImGui::MenuItem("MonsterProjectile"))
                    CreateEmptyObject(5);
                else if (ImGui::MenuItem("NPC"))
                    CreateEmptyObject(6);
                else if (ImGui::MenuItem("Door"))
                    CreateEmptyObject(7);
                else if (ImGui::MenuItem("HitObject"))
                    CreateEmptyObject(8);
                else if (ImGui::MenuItem("Boundary"))
                    CreateEmptyObject(9);
                else if (ImGui::MenuItem("MainCam"))
                    CreateEmptyObject(10);
                else if (ImGui::MenuItem("UICam"))
                    CreateEmptyObject(11);
                else if (ImGui::MenuItem("ViewPortUI"))
                    CreateEmptyObject(31);
                ImGui::EndMenu();
            }
            ImGui::Separator();


            if (ImGui::BeginMenu("Add Component"))
            {
                for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
                {
                    if (ImGui::MenuItem(ToString((COMPONENT_TYPE)i)))
                    {
                        AddComponent(COMPONENT_TYPE(i));
                    }
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
                    {
                        AddScript(vecScripts[i]);
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Level"))
        {
            CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();
            bool PlayEnable = true;
            bool PauseEnable = true;
            bool StopEnable = true;

            if (CurLevel->GetState() == LEVEL_STATE::PLAY)
            {
                PlayEnable = false;
                PauseEnable = true;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::PAUSE)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = true;
            }
            else if (CurLevel->GetState() == LEVEL_STATE::STOP)
            {
                PlayEnable = true;
                PauseEnable = false;
                StopEnable = false;
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

                tEvent evn = {};
                evn.Type = EVENT_TYPE::LEVEL_CHANGE;
                evn.wParam = DWORD_PTR(pNewLevel);
                CEventMgr::GetInst()->AddEvent(evn);

                // InspectorUI
                InspectorUI* Inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
                Inspector->SetTargetObject(nullptr);
            }

            ImGui::EndMenu();
        }




        ImGui::EndMainMenuBar();
    }

    return 0;
}

void MenuUI::CreateEmptyObject(int layerindx)
{
    CGameObject* pNewObject = new CGameObject;
    pNewObject->AddComponent(new CTransform);
    pNewObject->SetName(L"NewObject");

    if (layerindx == 10)
    {
        pNewObject->SetName(L"MainCam");
        pNewObject->AddComponent(new CCamera);
        pNewObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC); // ī�޶� ������Ʈ�� ���� ��� ����(����)
        pNewObject->Camera()->SetCameraIndex(0); //MainCamera�� ����
        pNewObject->Camera()->SetLayerMaskAll(true); // ��� ���̾� üũ
        pNewObject->Camera()->SetLayerMask(31, false);// UI Layer �� ���������� �ʴ´�.
    }
    else if (layerindx == 11)
    {
        pNewObject->SetName(L"SubCam");
        pNewObject->AddComponent(new CCamera);
        pNewObject->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC); // ī�޶� ������Ʈ�� ���� ��� ����(����)
        pNewObject->Camera()->SetCameraIndex(1); //MainCamera�� ����
        pNewObject->Camera()->SetLayerMask(31, true);
    }
    SpawnGameObject(pNewObject, Vec3(0.f, 0.f, 0.f), layerindx);

    // Outliner �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");

    // �����߰��� ������Ʈ�� �����ͷ� �ϴ� ��尡 �߰��Ǹ�, ���û��·� �ΰ� �Ѵ�.
    outliner->SetSelectedNodeData(DWORD_PTR(pNewObject));
}

void MenuUI::CreatePrefabObject()
{
}

void MenuUI::AddComponent(COMPONENT_TYPE _type)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

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
    }

    // Inspector �� ���Ӱ� �߰��� ������Ʈ�� �˸��� ���ؼ� Ÿ���� �ٽ� �˷��ش�.
    inspector->SetTargetObject(pSelectedObject);

}

void MenuUI::AddScript(const wstring& _strScriptName)
{
    // Outliner �� Inspector �� �����´�.
    OutlinerUI* outliner = (OutlinerUI*)ImGuiMgr::GetInst()->FindUI("##Outliner");
    InspectorUI* inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");

    // ���õ� ������Ʈ�� �����ͼ� ComponentType �� �´� ������Ʈ�� �����ؼ� �߰��Ѵ�.
    CGameObject* pSelectedObject = outliner->GetSelectedObject();

    if (nullptr == pSelectedObject)
        return;

    CScript* pScript = CScriptMgr::GetScript(_strScriptName);

    pSelectedObject->AddComponent(pScript);

    inspector->SetTargetObject(pSelectedObject);
}
