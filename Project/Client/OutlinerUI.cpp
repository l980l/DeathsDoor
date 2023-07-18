#include "pch.h"
#include "OutlinerUI.h"

#include "ImGuiMgr.h"
#include "InspectorUI.h"
#include "ContentUI.h"

#include <Engine\CEventMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include <Engine/CResMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CEventMgr.h>

#include "TreeUI.h"

OutlinerUI::OutlinerUI()
    : UI("##Outliner")
	, m_Tree(nullptr)
	, m_dwSelectedData()
{
    SetName("Outliner");

	// OutlinerUI �ȿ� �ڽ����� Tree �� �߰��Ѵ�.
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	m_Tree->SetActive(true);
	m_Tree->ShowRoot(false);

	m_Tree->AddDynamic_Select(this, (UI_DELEGATE_1)&OutlinerUI::SetTargetToInspector);
	m_Tree->AddDynamic_DragDrop(this, (UI_DELEGATE_2)&OutlinerUI::DragDrop);
	m_Tree->SetDragDropID("GameObject");

	// ��Ŭ���� Tree �߰�
	m_Tree->AddDynamic_RightMouseButton(this, (UI_DELEGATE_1)&OutlinerUI::MouseRightClick);

	AddChildUI(m_Tree);
}

OutlinerUI::~OutlinerUI()
{
}

void OutlinerUI::tick()
{
	if (CEventMgr::GetInst()->IsLevelChanged())
	{
		ResetOutliner();

		// Ʈ�� ���� ��, ���� ���ó��� ������ DATA �� ������, ã�Ƽ� ���ó��� ����
		if (0 != m_dwSelectedData)
		{
			m_Tree->GetSelectedNode(m_dwSelectedData);
		}		
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

	// ���ҽ� �Ŵ������� ���� ��� ���ҽ� ��� �޾ƿ�
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < (UINT)MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);

		const vector<CGameObject*>& vecParentObj = pLayer->GetParentObject();

		for (size_t i = 0; i < vecParentObj.size(); ++i)
		{
			AddGameObject(vecParentObj[i], nullptr);			
		}
	}
}

void OutlinerUI::SetTargetToInspector(DWORD_PTR _SelectedNode)
{
	TreeNode* pSelectedNode = (TreeNode*)_SelectedNode;
	CGameObject* pSelectObject = (CGameObject*)pSelectedNode->GetData();

	// Inspector �� ���õ� GameObject �� �˷��ش�.	
	InspectorUI* pInspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetObject(pSelectObject);
}


void OutlinerUI::AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode)
{
	// ������Ʈ�� Ʈ���� �ְ�, ������ ��� �ּҸ� �޾Ƶд�.
	TreeNode* pNode = m_Tree->AddItem(string(_Obj->GetName().begin(), _Obj->GetName().end())
									, (DWORD_PTR)_Obj
									, _ParentNode);

	// ������Ʈ�� �ڽĿ�����Ʈ ���� ������Ʈ ��带 �θ�� �ؼ� �� ������ �ٽ� �־��ش�.
	const vector<CGameObject*>& vecChild = _Obj->GetChild();
	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(vecChild[i], pNode);
	}
}


CGameObject* OutlinerUI::GetSelectedObject()
{
	TreeNode* pSelectedNode = m_Tree->GetSelectedNode();

	if (nullptr == pSelectedNode)
		return nullptr;

	return (CGameObject*)pSelectedNode->GetData();
}






void OutlinerUI::DragDrop(DWORD_PTR _DragNode, DWORD_PTR _DropNode)
{
	TreeNode* pDragNode = (TreeNode*)_DragNode;
	TreeNode* pDropNode = (TreeNode*)_DropNode;

	CGameObject* pDragObj = (CGameObject*)pDragNode->GetData();
	CGameObject* pDropObj = nullptr;
	if (nullptr != pDropNode)
	{
		pDropObj = (CGameObject*)pDropNode->GetData();
	}

	// �ڽ����� �� ������Ʈ�� ������ ������Ʈ�� ����(�θ����) �� �ϳ����, 
	// AddChild ó������ �ʴ´�.
	if (nullptr != pDropObj)
	{
		if (pDropObj->IsAncestor(pDragObj))
			return;
	}

	// �̺�Ʈ �Ŵ����� ���ؼ� ó���Ѵ�.
	tEvent evn = {};
	evn.Type = EVENT_TYPE::ADD_CHILD;
	evn.wParam = (DWORD_PTR)pDropObj;
	evn.lParam = (DWORD_PTR)pDragObj;
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
				{
					Menu = 1;
				}

				if (ImGui::MenuItem("Prefab"))
				{
					Menu = 2;
				}

				if (ImGui::MenuItem("Delete"))
				{
					Menu = 3;
				}

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
				TreeNode* pRClickNode = (TreeNode*)_RClickNode;

				CGameObject* pRClickObj = (CGameObject*)pRClickNode->GetData();

				string strRename = string(Rename);
				wstring wstrRename = wstring(strRename.begin(), strRename.end());

				pRClickObj->SetName(wstrRename);

				m_Tree->SetRbtDownNode(nullptr);

				OutlinerUI::ResetOutliner();

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

			TreeNode* pRClickNode = (TreeNode*)_RClickNode;

			CGameObject* pRClickObj = (CGameObject*)pRClickNode->GetData();

			Ptr<CPrefab> pPrefab = nullptr;

			pPrefab = new CPrefab;

			wstring PrefabName = wstring(pRClickObj->GetName() + L"Prefab");

			pPrefab->RegisterProtoObject(pRClickObj->Clone());

			CResMgr::GetInst()->AddRes(PrefabName, pPrefab);

			ContentUI* pContent = (ContentUI*)ImGuiMgr::GetInst()->FindUI("##Content");
			pContent->ResetContent();

			m_Tree->SetRbtDownNode(nullptr);
			memset(&Menu, 0, sizeof(int));
		}

		else if (Menu == 3)
		{
			CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

			if (CurLevel->GetState() == LEVEL_STATE::STOP)
			{
				TreeNode* pRClickNode = (TreeNode*)_RClickNode;

				CGameObject* pRClickObj = (CGameObject*)pRClickNode->GetData();
								
				CurLevel->GetLayer(pRClickObj->GetLayerIndex())->RemoveFromParentList(pRClickObj);
				
				delete(pRClickObj);

				ResetOutliner();

				InspectorUI* Inspector = (InspectorUI*)ImGuiMgr::GetInst()->FindUI("##Inspector");
				Inspector->SetTargetObject(nullptr);

				m_Tree->SetRbtDownNode(nullptr);
				memset(&Menu, 0, sizeof(int));
			}
		}

		ImGui::EndPopup();
	}
}
