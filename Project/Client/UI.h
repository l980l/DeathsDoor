#pragma once


#include "ImGuiMgr.h"

class UI
{
    string m_strName; // Ÿ��Ʋ �̸�, 
    string m_strID;   // ID �̸�

    ImVec2 m_vSize;     // UI ũ��
    ImVec2 m_vPopupPos; // UI ��ġ

    UI*         m_ParentUI;   // �θ� UI
    vector<UI*> m_vecChildUI; // �ڽ� UI ���

    bool m_Modal;  // ��� or ��޸���
    bool m_Active; // UI Ȱ��ȭ üũ

public:
    virtual void init()
    {
    }

    virtual void tick()
    {
    }

    virtual void finaltick();
    virtual int  render_update() = 0;


    void SetActive(bool _Active) { m_Active = _Active; }
    bool IsActive() const { return m_Active; }

    void SetModal(bool _Modal) { m_Modal = _Modal; }
    bool IsModal() const { return m_Modal; }

    ImVec2 GetPopupPos() const { return m_vPopupPos; }
    void   SetPopupPos(ImVec2 _vPos) { m_vPopupPos = _vPos; }

    const string& GetName() { return m_strName; }
    void          SetName(const string& _Name) { m_strName = _Name; }

    const string& GetID() { return m_strID; }

    void SetSize(float _width, float _height) { m_vSize = ImVec2(_width, _height); }

    void AddChildUI(UI* _UI)
    {
        _UI->m_ParentUI = this;
        m_vecChildUI.push_back(_UI);
    }


    UI(const string& _Name);
    virtual ~UI();
};
