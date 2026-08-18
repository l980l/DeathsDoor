#include "pch.h"
#include "OutlinerUI.h"
#include "commdlg.h"

#include "ImGuiMgr.h"
#include "InspectorUI.h"
#include "ContentUI.h"

#include <Engine/CEventMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>

#include <Engine/CResMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CEventMgr.h>
#include <Engine/CPhysXMgr.h>
#include "CLevelSaveLoad.h"
#include "TreeUI.h"

void OutlinerUI::tick()
{
    if (CEventMgr::GetInst()->IsLevelChanged())
    {
        ResetOutliner();

        // 트리 리셋 후, 다음 선택노드로 지정된 DATA 가 있으면, 찾아서 선택노드로 변경
        if (0 != m_dwSelectedData)
            m_Tree->GetSelectedNode(m_dwSelectedData);
    }
}

int OutlinerUI::render_update()
{
    return 0;
}

void OutlinerUI::ResetOutliner()
{
    // Tree Clear
    m_Tree->Clear();
    m_Tree->AddItem("Root", 0);

    // 리소스 매니저에서 현재 모든 리소스 목록 받아옴
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

    for (UINT i = 0; i < static_cast<UINT>(MAX_LAYER); ++i)
    {
        CLayer* pLayer = pCurLevel->GetLayer(i);

        const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

        for (size_t i = 0; i < vecParentObj.size(); ++i)
            AddGameObject(vecParentObj[i], nullptr);
    }
}

void OutlinerUI::SetTargetToInspector(DWORD_PTR _SelectedNode) const
{
    TreeNode*    pSelectedNode = reinterpret_cast<TreeNode*>(_SelectedNode);
    CGameObject* pSelectObject = reinterpret_cast<CGameObject*>(pSelectedNode->GetData());

    // Inspector 에 선택된 GameObject 를 알려준다.	
    InspectorUI* pInspector = static_cast<InspectorUI*>(ImGuiMgr::GetInst()->FindUI("##Inspector"));
    pInspector->SetTargetObject(pSelectObject);
}


CGameObject* OutlinerUI::GetSelectedObject() const
{
    TreeNode* pSelectedNode = m_Tree->GetSelectedNode();

    if (nullptr == pSelectedNode)
        return nullptr;

    return reinterpret_cast<CGameObject*>(pSelectedNode->GetData());
}

void OutlinerUI::AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode)
{
    // 오브젝트를 트리에 넣고, 생성된 노드 주소를 받아둔다.
    TreeNode* pNode = m_Tree->AddItem(string(_Obj->GetName().begin(), _Obj->GetName().end())
                                    , reinterpret_cast<DWORD_PTR>(_Obj)
                                    , _ParentNode);

    // 오브젝트의 자식오브젝트 들을 오브젝트 노드를 부모로 해서 그 밑으로 다시 넣어준다.
    const vector<CGameObject*>& vecChild = _Obj->GetChild();
    for (size_t i = 0; i < vecChild.size(); ++i)
        AddGameObject(vecChild[i], pNode);
}


void OutlinerUI::DragDrop(DWORD_PTR _DragNode, DWORD_PTR _DropNode) const
{
    TreeNode* pDragNode = reinterpret_cast<TreeNode*>(_DragNode);
    TreeNode* pDropNode = reinterpret_cast<TreeNode*>(_DropNode);

    CGameObject* pDragObj = reinterpret_cast<CGameObject*>(pDragNode->GetData());
    CGameObject* pDropObj = nullptr;
    if (nullptr != pDropNode)
        pDropObj = reinterpret_cast<CGameObject*>(pDropNode->GetData());

    // 자식으로 들어갈 오브젝트가 목적지 오브젝트의 조상(부모계층) 중 하나라면, 
    // AddChild 처리하지 않는다.
    if (nullptr != pDropObj)
        if (pDropObj->IsAncestor(pDragObj))
            return;

    // 이벤트 매니저를 통해서 처리한다.
    tEvent evn = {};
    evn.Type   = EVENT_TYPE::ADD_CHILD;
    evn.wParam = reinterpret_cast<DWORD_PTR>(pDropObj);
    evn.lParam = reinterpret_cast<DWORD_PTR>(pDragObj);
    CEventMgr::GetInst()->AddEvent(evn);
}


void OutlinerUI::MouseRightClick(DWORD_PTR _RClickNode)
{
    ImGui::OpenPopup("##OutlinerPopup");

    if (ImGui::BeginPopupContextItem("##OutlinerPopup"))
    {
        static int Menu = 0;

        if (Menu == 0)
        {
            if (ImGui::BeginMenu("##OutlinerMenu"))
            {
                if (ImGui::MenuItem("Rename"))
                    Menu = 1;

                if (ImGui::MenuItem("Prefab"))
                    Menu = 2;

                if (ImGui::MenuItem("Delete"))
                    Menu = 3;

                ImGui::EndMenu();
            }

            if (ImGui::IsKeyPressed(ImGuiKey_Escape))
                m_Tree->SetRbtDownNode(nullptr);
        }

        else if (Menu == 1)
        {
            static char Rename[256] = {};

            ImGui::InputText("##Rename", Rename, sizeof(Rename));

            if (ImGui::IsKeyPressed(ImGuiKey_Enter))
            {
                TreeNode* pRClickNode = reinterpret_cast<TreeNode*>(_RClickNode);

                CGameObject* pRClickObj = reinterpret_cast<CGameObject*>(pRClickNode->GetData());

                string  strRename  = string(Rename);
                wstring wstrRename = wstring(strRename.begin(), strRename.end());

                pRClickObj->SetName(wstrRename);

                m_Tree->SetRbtDownNode(nullptr);

                ResetOutliner();

                memset(Rename, 0, sizeof(Rename));
                memset(&Menu, 0, sizeof(int));
            }

            else if (ImGui::IsKeyPressed(ImGuiKey_Escape))
            {
                m_Tree->SetRbtDownNode(nullptr);

                memset(Rename, 0, sizeof(Rename));
                memset(&Menu, 0, sizeof(int));
            }
        }

        else if (Menu == 2)
        {
            static int ID = 0;

            TreeNode* pRClickNode = reinterpret_cast<TreeNode*>(_RClickNode);

            CGameObject* pRClickObj = reinterpret_cast<CGameObject*>(pRClickNode->GetData());

            Ptr<CPrefab> pPrefab = nullptr;

            pPrefab = new CPrefab;

            const wstring PrefabName = wstring(pRClickObj->GetName() + L"Prefab");

            pPrefab->RegisterProtoObject(pRClickObj->Clone());

            CResMgr::GetInst()->AddRes(PrefabName, pPrefab);

            ContentUI* pContent = static_cast<ContentUI*>(ImGuiMgr::GetInst()->FindUI("##Content"));
            pContent->ResetContent();


            m_Tree->SetRbtDownNode(nullptr);
            memset(&Menu, 0, sizeof(int));
        }

        else if (Menu == 3)
        {
            CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

            if (CurLevel->GetState() == LEVEL_STATE::STOP)
            {
                TreeNode* pRClickNode = reinterpret_cast<TreeNode*>(_RClickNode);

                CGameObject* pRClickObj = reinterpret_cast<CGameObject*>(pRClickNode->GetData());

                CurLevel->GetLayer(pRClickObj->GetLayerIndex())->RemoveFromParentList(pRClickObj);
                //CPhysXMgr::
                //delete(pRClickObj);
                tEvent evn = {};
                evn.Type   = EVENT_TYPE::DELETE_OBJECT;
                evn.wParam = reinterpret_cast<DWORD_PTR>(pRClickObj);
                CEventMgr::GetInst()->AddEvent(evn);

                ResetOutliner();

                InspectorUI* inspector = static_cast<InspectorUI*>(ImGuiMgr::GetInst()->FindUI("##Inspector"));
                inspector->SetTargetObject(nullptr);

                m_Tree->SetRbtDownNode(nullptr);
                memset(&Menu, 0, sizeof(int));
            }
        }

        ImGui::EndPopup();
    }
}


OutlinerUI::OutlinerUI()
    : UI("##Outliner")
    , m_Tree(nullptr)
    , m_dwSelectedData()
{
    SetName("Outliner");

    // OutlinerUI 안에 자식으로 Tree 를 추가한다.
    m_Tree = new TreeUI;
    m_Tree->SetName("OutlinerTree");
    m_Tree->SetActive(true);
    m_Tree->ShowRoot(false);

    m_Tree->AddDynamic_Select(this, reinterpret_cast<UI_DELEGATE_1>(&OutlinerUI::SetTargetToInspector));
    m_Tree->AddDynamic_DragDrop(this, reinterpret_cast<UI_DELEGATE_2>(&OutlinerUI::DragDrop));
    m_Tree->SetDragDropID("GameObject");

    // 우클릭용 Tree 추가
    m_Tree->AddDynamic_RightMouseButton(this, static_cast<UI_DELEGATE_1>(&OutlinerUI::MouseRightClick));

    AddChildUI(m_Tree);
}

OutlinerUI::~OutlinerUI()
{
}
