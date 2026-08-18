#pragma once
#include <Engine/CSingleton.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


// ========
// Delegate
// ========
class UI;

using UI_DELEGATE   = void(UI::*)(void);
using UI_DELEGATE_1 = void(UI::*)(DWORD_PTR);
using UI_DELEGATE_2 = void(UI::*)(DWORD_PTR, DWORD_PTR);

class ImGuiMgr :
    public CSingleton<ImGuiMgr>
{
    SINGLE(ImGuiMgr);
    HWND             m_hMainHwnd;
    map<string, UI*> m_mapUI;

    HANDLE m_hObserver;

public:
    void init(HWND _hWnd);
    void progress();

    UI*  FindUI(const string& _UIName);
    HWND GetMainHwnd() const { return m_hMainHwnd; }

private:
    void CreateUI();
    void ObserveContent();
    void LayoutDesign() const;
    void begin() const;
    void tick() const;
    void finaltick() const;
    void render() const;
};
