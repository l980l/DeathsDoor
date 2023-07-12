#include "pch.h"
#include "Animator3DUI.h"

#include <Engine/CAnimator3D.h>


Animator3DUI::Animator3DUI()
    : ComponentUI("##Animator3D", COMPONENT_TYPE::ANIMATOR3D)
{
    SetName("Animator3D");
}

Animator3DUI::~Animator3DUI()
{
}


int Animator3DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    //ImGui::Text("CurClip");
    //ImGui::SameLine();
    //int CurClip = GetTarget()->Animator3D()->GetCurClip();
    //int ClipSize = GetTarget()->Animator3D()->GetClipSize();

    //ImGui::SliderInt("##AnimClip", &CurClip, 0, ClipSize - 1);

    //GetTarget()->Animator3D()->SetCurClip(CurClip);

    //// AnimClip 세팅
    //ImGui::Text("<<<SetAnimClip>>>");

    //ImGui::Text("ClipCount");
    //ImGui::SameLine();
    //static int ClipCount = 0;
    //ImGui::DragInt("##ClipCount", &ClipCount);

    //m_vecAnimClip.resize(ClipCount);    // 애니메이션 클립 임시 저장하기 위한 vector.
    //m_vecStrName.resize(ClipCount);    // 애니메이션 이름을 임시 저장하기 위한 vector. 

    //for (int i = 0; i < ClipCount; ++i)
    //{
    //    ImGui::Text("#%d ", i);
    //    ImGui::SameLine();
    //    ImGui::SetNextItemWidth(64.f);
    //    ImGui::InputText("##AnimName", (char*)m_vecStrName[i].c_str(), m_vecStrName[i].length());

    //}

    //if (ImGui::Button("Apply AnimClip", ImVec2(64, 18)))
    //{
    //    GetTarget()->Animator3D()->SetAnimClip(&vecAnimClip);
    //}

    return TRUE;
}