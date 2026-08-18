#pragma once
#include "UI.h"

class TreeUI;

class ContentUI :
    public UI
{
    TreeUI*         m_Tree;
    vector<wstring> m_vecResPath;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual int  render_update() override;

    void Reload(); // Content ������ �ִ� ���ҽ��� �ε�
    void ResetContent() const;
    void SetTargetToInspector(DWORD_PTR _SelectedNode) const;

private:
    void     FindFileName(const wstring& _FolderPath);
    RES_TYPE GetResTypeByExt(const wstring& _relativepath) const;

public:
    ContentUI();
    virtual ~ContentUI() override;
};
