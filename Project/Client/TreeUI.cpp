#include "pch.h"
#include "TreeUI.h"


// ========
// TreeNode
// ========
TreeNode::TreeNode()
    : m_Owner(nullptr)
    , m_ParentNode(nullptr)
    , m_ID(0)
    , m_Data(0)
    , m_CategoryNode(false)
    , m_Hilight(false)
{
}

TreeNode::~TreeNode()
{
    Safe_Del_Vec(m_vecChildNode);
}

void TreeNode::render_update()
{
    // FinalName �����
    string strFinalName = m_strName;
    strFinalName        += "##";

    char szBuff[100] = {};
    _itoa_s(m_ID, szBuff, 10);
    strFinalName += szBuff;

    // Flag üũ
    UINT flag = ImGuiTreeNodeFlags_DefaultOpen;

    // �ڽ� ��尡 ������ Lear �÷��׸� �����Ѵ�(ȭ��ǥ ����)
    if (m_vecChildNode.empty())
        flag |= ImGuiTreeNodeFlags_Leaf;

    // Ŭ�� �Ǿ��ų�, �׸� ��ǥ ����� ��� Selected �÷��׷� ���̶���Ʈ�� �ش�.
    if (m_Hilight || m_CategoryNode)
        flag |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(strFinalName.c_str(), flag))
    {
        // �ش� ��忡 ���콺 ��Ŭ���� �߻��ϸ� ���ó��� ���� �ش�.
        if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            m_Owner->m_LbtDownNode = this;
        }

        // ���콺 ��Ŭ�� �߻�
        else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
            m_Owner->SetRbtDownNode(this);
        }

        else if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            m_Owner->SetSelectedNode(this);
        }

        // �Ǵ�, Ʈ�� �籸�� ������ ���õ� ��忴�ٸ�, �ٽ� ���ó��� ó���Ѵ�.
        else if (0 != m_Owner->m_dwPrevSelected && m_Owner->m_dwPrevSelected == m_Data)
        {
            m_Owner->m_dwPrevSelected = 0;
            m_Owner->SetSelectedNode(this);
        }

        // �ش� ��� ������ �巡�� ��ŸƮ üũ
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload(m_Owner->m_strDragDropID.c_str(), this, sizeof(TreeNode));
            ImGui::Text(m_strName.c_str());

            // Tree �� �巡�� ��� ���
            m_Owner->SetDragNode(this);

            ImGui::EndDragDropSource();
        }

        // �巡�� ���� ��, ����� �ĺ��� ���
        if (ImGui::BeginDragDropTarget())
        {
            // �ش� ��忡�� ���콺 �� ���, ������ PayLoad Ű���� ��ġ�� ���
            const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload(m_Owner->m_strDragDropID.c_str());
            if (pPayLoad)
                // DropNode �� Tree �� �˸�
                m_Owner->SetDropNode(this);

            ImGui::EndDragDropTarget();
        }

        for (size_t i = 0; i < m_vecChildNode.size(); ++i)
            m_vecChildNode[i]->render_update();

        ImGui::TreePop();
    }
}


// ================
//      TreeUI
// ================
TreeUI::TreeUI()
    : UI("##Tree")
    , m_RootNode(nullptr)
    , g_NextId(0)
    , m_bShowRoot(true)
    , m_SelectedNode(nullptr)
    , m_dwPrevSelected(0)
    , m_SelectInst(nullptr)
    , m_SelectFunc(nullptr)
    , m_DragDropInst(nullptr)
    , m_DragDropFunc(nullptr)
{
    m_strDragDropID = "PayLoad";
}

TreeUI::~TreeUI()
{
    if (nullptr != m_RootNode)
        delete m_RootNode;
}

int TreeUI::render_update()
{
    if (nullptr != m_RootNode)
    {
        if (m_bShowRoot)
            m_RootNode->render_update();
        else
            for (size_t i = 0; i < m_RootNode->m_vecChildNode.size(); ++i)
                m_RootNode->m_vecChildNode[i]->render_update();
    }

    // Drag Drop ��� �Ѵ� �ִ� ���
    if ((m_DragNode && m_DropNode) || (m_DragNode && ImGui::IsMouseReleased(ImGuiMouseButton_Left)))
    {
        if (m_DragDropInst && m_DragDropFunc)
            (m_DragDropInst->*m_DragDropFunc)((DWORD_PTR)m_DragNode, (DWORD_PTR)m_DropNode);

        m_DragNode = nullptr;
        m_DropNode = nullptr;
    }

    if (m_RbtDownNode)
        if (m_MouseRClickInst && m_MouseRClickFunc)
            (m_MouseRClickInst->*m_MouseRClickFunc)((DWORD_PTR)m_RbtDownNode);
    return 0;
}

void TreeUI::Clear()
{
    // ������ ���õ� ��尡 ������
    if (nullptr != m_SelectedNode)
        // �̸��� ����صд�.
        m_dwPrevSelected = m_SelectedNode->GetData();

    if (nullptr != m_RootNode)
    {
        delete m_RootNode;
        m_RootNode = nullptr;
    }
}

TreeNode* TreeUI::AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent)
{
    TreeNode* pNewNode = new TreeNode;

    pNewNode->m_Owner   = this;
    pNewNode->m_strName = _strNodeName;
    pNewNode->m_Data    = _Data;
    pNewNode->m_ID      = g_NextId++;

    // ��Ʈ�� NULL �̴� ==> Ʈ���� ���� ������ ������
    if (nullptr == m_RootNode)
    {
        // ���� ������ �Է��ε�, �θ� ������ ���
        assert(!_pParent);

        m_RootNode = pNewNode;
    }

    // Ʈ���� ���� �����Ͱ� ���ʰ� �ƴϴ�.
    else
    {
        if (_pParent)
        {
            // ����� �θ�� ������ ��尡 �ش� Ʈ�� �Ҽ��� �ƴϴ�.
            if (_pParent->m_Owner != this)
                assert(nullptr);

            // ������ �θ��� �ڽ����� ����
            _pParent->m_vecChildNode.push_back(pNewNode);
            pNewNode->m_ParentNode = _pParent;
        }

        // �θ�� ������ ��尡 ���°��, ��Ʈ ������ �ִ´�
        else
        {
            // ���� ������ ��带 ��Ʈ����� �ڽ����� ����
            m_RootNode->m_vecChildNode.push_back(pNewNode);
            pNewNode->m_ParentNode = m_RootNode;
        }
    }

    return pNewNode;
}


void TreeUI::SetSelectedNode(TreeNode* _Node)
{
    // ���콺�� ���� ���� �� ��尡 ��ġ�ؾ� ��
    if (m_LbtDownNode != _Node)
    {
        m_LbtDownNode = nullptr;
        return;
    }

    if (m_SelectedNode)
        m_SelectedNode->m_Hilight = false;

    m_SelectedNode = _Node;
    m_LbtDownNode  = nullptr;

    if (m_SelectedNode)
    {
        m_SelectedNode->m_Hilight = true;

        if (m_SelectInst && m_SelectFunc)
            (m_SelectInst->*m_SelectFunc)((DWORD_PTR)m_SelectedNode);
    }
}

void TreeUI::SetDragNode(TreeNode* _Node)
{
    m_DragNode = _Node;
    m_DropNode = nullptr;
}

void TreeUI::SetDropNode(TreeNode* _Node)
{
    m_DropNode = _Node;
}

void TreeUI::SetRbtDownNode(TreeNode* _Node)
{
    m_RbtDownNode = _Node;
}

bool TreeUI::GetSelectedNode(DWORD_PTR _Data)
{
    static list<TreeNode*> queue;
    queue.clear();

    queue.push_back(m_RootNode);

    TreeNode* pCurNode = nullptr;
    while (!queue.empty())
    {
        pCurNode = queue.front();
        queue.pop_front();

        for (size_t i = 0; i < pCurNode->m_vecChildNode.size(); ++i)
            queue.push_back(pCurNode->m_vecChildNode[i]);

        if (pCurNode->GetData() == _Data)
        {
            SetSelectedNode(pCurNode);
            return true;
        }
    }

    return false;
}
