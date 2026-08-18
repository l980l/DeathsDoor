#include "pch.h"
#include "SkyBoxUI.h"

#include <Engine/CResMgr.h>

#include "ImGuiMgr.h"
#include "ListUI.h"

#include "TreeUI.h"
#include "ParamUI.h"

SkyBoxUI::SkyBoxUI()
    : ComponentUI("##SkyBox", COMPONENT_TYPE::SKYBOX)
    , m_iType(0)
{
    SetName("SkyBox");
}

SkyBoxUI::~SkyBoxUI()
{
}

int SkyBoxUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    m_iType = static_cast<int>(GetTarget()->SkyBox()->GetType());

    string strType[2]  = {"Sphere", "Cube"};
    string strTypeName = strType[m_iType];
    ImGui::Text("Type  ");
    ImGui::SameLine();
    ImGui::SliderInt("##Type", &m_iType, 0, 1, strTypeName.c_str());


    // TEX_Param Texture ��� 
    Ptr<CTexture> pTEX = GetTarget()->SkyBox()->GetSkyTex();

    ImGui::Spacing();
    ImGui::Text("SkyTex");
    ImGui::SameLine();

    // Sphere�� Tex�� ���
    // Cube�� ��� dds�� ����� �����Ƿ� �̸��� ���
    if (SKYBOX_TYPE::SPHERE == static_cast<SKYBOX_TYPE>(m_iType))
    {
        ImGui::Image(pTEX->GetSRV().Get(), ImVec2(75.f, 75.f));
    }
    else
    {
        wstring wstrTexName   = pTEX->GetKey();
        string  strSkyTexName = string(wstrTexName.begin(), wstrTexName.end());
        ImGui::Text(strSkyTexName.c_str());
    }

    ImGui::SameLine();

    if (ImGui::Button("##TextureSelectBtn", ImVec2(18.f, 18.f)))
    {
        const map<wstring, Ptr<CRes>>& AllTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

        ListUI* pListUI = static_cast<ListUI*>(ImGuiMgr::GetInst()->FindUI("##List"));
        pListUI->SetModal(false);
        pListUI->Reset("Texture List", ImVec2(300.f, 500.f));
        for (const auto& pair : AllTex)
            pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
        pListUI->AddDynamic_Select(this, static_cast<UI_DELEGATE_1>(&SkyBoxUI::SelectTexture));
    }

    GetTarget()->SkyBox()->SetType(static_cast<SKYBOX_TYPE>(m_iType));

    return TRUE;
}

void SkyBoxUI::SelectTexture(DWORD_PTR _Key)
{
    string        strKey = (char*)_Key;
    Ptr<CTexture> pTex   = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));

    GetTarget()->SkyBox()->SetSkyTexture(pTex);
}
