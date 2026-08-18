#pragma once
#include "UI.h"

// =========
// TreeNode
// =========
class TreeUI;

class TreeNode
{
    TreeUI*           m_Owner;        // ��带 �����ϰ� �ִ� Ʈ��
    TreeNode*         m_ParentNode;   // �θ���
    vector<TreeNode*> m_vecChildNode; // ����� �ڽ� ���

    string m_strName; // ����� ��� �̸�
    UINT   m_ID;      // ����� ���� ID

    DWORD_PTR m_Data; // ��忡 ����� ������


    bool m_CategoryNode; // �׸� ��ǥ ���
    bool m_Hilight;      // ��� ���̶���Ʈ ó��


public:
    void SetCategoryNode(bool _category)
    {
        m_CategoryNode = _category;
    }

    const string& GetName() { return m_strName; }
    DWORD_PTR     GetData() const { return m_Data; }

private:
    void render_update();

public:
    TreeNode();
    ~TreeNode();

    friend class TreeUI;
};


// ======
// TreeUI
// ======
class TreeUI :
    public UI
{
    TreeNode* m_RootNode; // Ʈ���� �����ϰ� �ִ� ��� �� ��Ʈ ���
    UINT      g_NextId;   // �����Ǵ� ���ڿ� �ٿ��� ���� ����
    bool      m_bShowRoot;

    TreeNode* m_SelectedNode;
    TreeNode* m_LbtDownNode;

    TreeNode* m_DragNode;
    TreeNode* m_DropNode;

    DWORD_PTR m_dwPrevSelected;

    UI*           m_SelectInst;
    UI_DELEGATE_1 m_SelectFunc;

    UI*           m_DragDropInst;
    UI_DELEGATE_2 m_DragDropFunc;

    // ���콺 ��Ŭ����
    UI*           m_MouseRClickInst;
    UI_DELEGATE_1 m_MouseRClickFunc;
    TreeNode*     m_RbtDownNode;

    string m_strDragDropID;

public:
    virtual int render_update() override;

    void      Clear();
    TreeNode* AddItem(const string& _strNodeName, DWORD_PTR _Data, TreeNode* _pParent = nullptr);
    void      ShowRoot(bool _Show) { m_bShowRoot = _Show; }

    void AddDynamic_Select(UI* _UI, UI_DELEGATE_1 _MemFunc)
    {
        m_SelectInst = _UI;
        m_SelectFunc = _MemFunc;
    }

    void AddDynamic_DragDrop(UI* _UI, UI_DELEGATE_2 _MemFunc)
    {
        m_DragDropInst = _UI;
        m_DragDropFunc = _MemFunc;
    }

    void AddDynamic_RightMouseButton(UI* _UI, UI_DELEGATE_1 _MemFunc)
    {
        m_MouseRClickInst = _UI;
        m_MouseRClickFunc = _MemFunc;
    }

    void SetDragDropID(const string& _strID) { m_strDragDropID = _strID; }

private:
    void SetSelectedNode(TreeNode* _Node);
    void SetDragNode(TreeNode* _Node);
    void SetDropNode(TreeNode* _Node);

public:
    void SetRbtDownNode(TreeNode* _Node);

    TreeNode* GetSelectedNode() const { return m_SelectedNode; }
    bool      GetSelectedNode(DWORD_PTR _Data); // �Էµ� �����Ϳ� ������ �����͸� �����ϰ� �ִ� ��带 ���û��·� ����

    TreeUI();
    virtual ~TreeUI() override;

    friend class TreeNode;
};
