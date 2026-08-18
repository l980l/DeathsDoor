#include "pch.h"
#include "LandScapeUI.h"

#include <Engine/CLandScape.h>
#include <Engine/CResMgr.h>
#include "ListUI.h"


LandScapeUI::LandScapeUI()
    : ComponentUI("##LandScape", COMPONENT_TYPE::LANDSCAPE)
{
    SetName("LandScape");
}

LandScapeUI::~LandScapeUI()
{
}

int LandScapeUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    Vec2 vFace   = GetTarget()->LandScape()->GetFace();
    int  Face[2] = {static_cast<int>(vFace.x), static_cast<int>(vFace.y)};
    ImGui::Text("Face	   ");
    ImGui::SameLine();
    if (ImGui::SliderInt2("##Face", Face, 1, 100))
        GetTarget()->LandScape()->SetFace(static_cast<UINT>(Face[0]), static_cast<UINT>(Face[1]));

    int iCurMod = static_cast<int>(GetTarget()->LandScape()->GetCurMod());
    ImGui::Text("MODE       ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##CurMode", &iCurMod, 0, static_cast<int>(LANDSCAPE_MOD::NONE)))
        GetTarget()->LandScape()->SetMod(static_cast<LANDSCAPE_MOD>(iCurMod));


    Ptr<CTexture> pTex = GetTarget()->LandScape()->GetBrushTex();
    ImGui::Text("Brush Tex  ");
    ImGui::SameLine();
    ImGui::Image(pTex->GetSRV().Get(), ImVec2(30.f, 30.f));

    ImGui::SameLine();

    if (ImGui::Button("##TextureSelectBtn", ImVec2(18.f, 18.f)))
    {
        const map<wstring, Ptr<CRes>>& AllTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

        ListUI* pListUI = static_cast<ListUI*>(ImGuiMgr::GetInst()->FindUI("##List"));
        pListUI->SetModal(false);
        pListUI->Reset("Texture List", ImVec2(300.f, 500.f));
        for (const auto& pair : AllTex)
            pListUI->AddItem(string(pair.first.begin(), pair.first.end()));
        pListUI->AddDynamic_Select(this, static_cast<UI_DELEGATE_1>(&LandScapeUI::SelectTexture));
    }


    int BrushTexArrSize = static_cast<int>(GetTarget()->LandScape()->GetBrushTex()->GetArraySize());
    int BrushIdx        = static_cast<int>(GetTarget()->LandScape()->GetBrushIdx());
    ImGui::Text("Brush Idx  ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##BrushgIdx", &BrushIdx, 0, BrushTexArrSize - 1))
        GetTarget()->LandScape()->SetBrushIdx(static_cast<UINT>(BrushIdx));

    Vec2   vScale      = GetTarget()->LandScape()->GetBrushScale();
    ImVec2 vBrushScale = ImVec2(vScale.x, vScale.y);
    ImGui::Text("Brush Scale");
    ImGui::SameLine();
    if (ImGui::SliderFloat2("##BrushScale", &vBrushScale.x, 0.01f, 1.f))
    {
        Vec2 vScale = Vec2(vBrushScale.x, vBrushScale.y);
        GetTarget()->LandScape()->SetBrushScale(vScale);
    }

    int TileArrSize = static_cast<int>(GetTarget()->LandScape()->GetTileArrTex()->GetArraySize()) / 2;
    int WeightIdx   = static_cast<int>(GetTarget()->LandScape()->GetWeightIdx());
    ImGui::Text("Weight Idx ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##WeightIdx", &WeightIdx, 0, TileArrSize - 1))
        GetTarget()->LandScape()->SetWeightIdx(static_cast<UINT>(WeightIdx));

    float Velocity = GetTarget()->LandScape()->GetVelocity();
    ImGui::Text("Velocity   ");
    ImGui::SameLine();
    if (ImGui::SliderFloat("##Velocity", &Velocity, 0.1f, 1.f))
        GetTarget()->LandScape()->SetVelocity(Velocity);

    Vec2   vTessFactorDist = GetTarget()->LandScape()->GetTessFactorDist();
    ImVec2 TessFactorDist  = ImVec2(vTessFactorDist.x, vTessFactorDist.y);
    ImGui::Text("TessDist   ");
    ImGui::SameLine();
    if (ImGui::SliderFloat2("##TessDist", &TessFactorDist.x, 1, 5000.f))
    {
        vTessFactorDist = Vec2(TessFactorDist.x, TessFactorDist.y);
        GetTarget()->LandScape()->SetTessFactorDist(vTessFactorDist);
    }

    int iMaxTessFactorLevel = GetTarget()->LandScape()->GetMaxTessFactorLevel();
    ImGui::Text("TessLevel  ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##TessLevel", &iMaxTessFactorLevel, 1, 25))
        GetTarget()->LandScape()->SetMaxTessFactorLevel(iMaxTessFactorLevel);


    return TRUE;
}

void LandScapeUI::SelectTexture(DWORD_PTR _Key)
{
    string        strKey = (char*)_Key;
    Ptr<CTexture> pTex   = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));

    GetTarget()->LandScape()->SetBrushTex(pTex);
}
