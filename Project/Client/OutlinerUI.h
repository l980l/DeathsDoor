#pragma once
#include "UI.h"

class TreeUI;
class TreeNode;

class OutlinerUI :
    public UI
{
    TreeUI*   m_Tree;
    DWORD_PTR m_dwSelectedData;

public:
    virtual void tick() override;
    virtual int  render_update() override;

    void         ResetOutliner();
    void         SetTargetToInspector(DWORD_PTR _SelectedNode) const;
    CGameObject* GetSelectedObject() const;

    // Ʈ���� ���µ� ���, �Է����� ���� �����Ϳ� ������ ��带  ���û��·� �д�.
    void SetSelectedNodeData(DWORD_PTR _data)
    {
        m_dwSelectedData = _data;
    }

private:
    void AddGameObject(CGameObject* _Obj, TreeNode* _ParentNode);
    void DragDrop(DWORD_PTR _DragNode, DWORD_PTR _DropNode) const;
    void MouseRightClick(DWORD_PTR _RClickNode);

public:
    OutlinerUI();
    virtual ~OutlinerUI() override;
};
