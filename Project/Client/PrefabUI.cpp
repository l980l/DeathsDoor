#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CGameObject.h>
#include <Engine/CTransform.h>
#include <Engine/CMeshRender.h>
#include <Engine/CPathMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include "CLevelSaveLoad.h"
#include <Engine/CResMgr.h>

PrefabUI::PrefabUI()
    :ResUI(RES_TYPE::PREFAB)
{
    SetName("Prefab");
}

PrefabUI::~PrefabUI()
{

}

int PrefabUI::render_update()
{
    ResUI::render_update();
    //if (ImGui::Button("Add", ImVec2(100, 18)))
    //{
    //    wstring strFolderpath = CPathMgr::GetInst()->GetContentPath();
    //    wstring relativepath = GetTargetRes()->GetRelativePath();
    //    strFolderpath += relativepath;
    //    FILE* pFile = nullptr;
    //    errno_t iErrNum = _wfopen_s(&pFile, strFolderpath.c_str(), L"rb");
    //    int ind = 0;
    //    fread(&ind, sizeof(int), 1, pFile);
    //    CGameObject* newPrefab = CLevelSaveLoad::LoadGameObject(pFile);
    //    int num = 0;
    //    wstring prefname = newPrefab->GetName();
    //    wstring orgprefname = prefname;
    //    CLevel* curlevel = CLevelMgr::GetInst()->GetCurLevel();
    //    CLayer* curlayer = curlevel->GetLayer(ind);
    //    Vec3 prefpos = newPrefab->Transform()->GetWorldPos();
    //    vector<CGameObject*> vecObj = curlayer->GetParentObject();
    //    for (size_t i = 0; i < vecObj.size(); i++)
    //    {
    //        //if (vecObj[i]->GetName() == prefname)//���� �̸��� �ִٸ� ���� ī��Ʈ
    //        //{
    //        //    num++;//1
    //        //    wstring idx = std::to_wstring(num);
    //        //    prefname = orgprefname;
    //        //    prefname += idx;
    //        //    if (vecObj[i]->GetName() != prefname)
    //        //    {
    //        //        
    //        //        newPrefab->SetName(prefname);
    //        //    }
    //        //}
    //    }
    //    SpawnGameObject(newPrefab, prefpos, ind);
    //    fclose(pFile);
    //}
    // Prefab �̸�
    ImGui::Text("Prefab          ");
    ImGui::SameLine();

    Ptr<CPrefab> pPrefab = (CPrefab*)GetTargetRes().Get();
    string strKey = string(pPrefab->GetKey().begin(), pPrefab->GetKey().end());
    ImGui::InputText("##PrefabUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

    // Save ��ư
    ImGui::Text("Save            ");
    ImGui::SameLine();
    static char szEmtpy[30] = {};
    ImGui::InputText("##PrefabNewName", szEmtpy, 30);
    ImGui::SameLine();

    if (ImGui::Button("##PrefabSaveButton", ImVec2(18.f, 18.f)))
    {
        string strTemp = szEmtpy;
        wstring wstrTemp = wstring(strTemp.begin(), strTemp.end());

        CLevelSaveLoad::SavePrefab(L"prefab\\" + wstrTemp + L".prefab", (CPrefab*)GetTargetRes().Get());
    }

    // Spawn
    static int iSpawnLayer = 0;
    ImGui::Text("SpawnLayerIndex ");
    ImGui::SameLine();
    ImGui::SliderInt("##SpawnLayerIndex", &iSpawnLayer, 0, MAX_LAYER);

    static float SpawnPos[3] = { 0.f,0.f,0.f };
    ImGui::Text("SpawnPos        ");
    ImGui::SameLine();
    ImGui::DragFloat3("##SpawnPos", SpawnPos);
    ImGui::SameLine();

    if (ImGui::Button("##SpawnGameObjectButton", ImVec2(18.f, 18.f)))
    {
        SpawnGameObject(pPrefab->Instantiate(), Vec3(SpawnPos[0], SpawnPos[1], SpawnPos[2]), iSpawnLayer);
    }

    return 0;
}