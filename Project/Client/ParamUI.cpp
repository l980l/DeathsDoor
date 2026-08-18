#include "pch.h"
#include "ParamUI.h"

#include "ImGuiMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include <Engine/CResMgr.h>

// �����ɹ� �ʱ�ȭ
UINT ParamUI::g_NextId = 0;


int ParamUI::Param_Int(const string& _strDesc, int* _pData, bool _bDrag)
{
    ImGui::Text(_strDesc.c_str());
    ImGui::SameLine(100);

    string strIntName = GetNextName("##Param_Int");
    ImGui::SetNextItemWidth(150);

    if (_bDrag)
    {
        if (ImGui::DragInt(strIntName.c_str(), _pData))
            return 1;
    }

    else
    {
        if (ImGui::InputInt(strIntName.c_str(), _pData))
            return 1;
    }

    return 0;
}

int ParamUI::Param_Float(const string& _strDesc, float* _pData, bool _bDrag)
{
    ImGui::Text(_strDesc.c_str());
    ImGui::SameLine(100);

    string strIntName = GetNextName("##Param_Int");
    ImGui::SetNextItemWidth(150);

    if (_bDrag)
    {
        if (ImGui::DragFloat(strIntName.c_str(), _pData, 0.05f))
            return 1;
    }

    else
    {
        if (ImGui::InputFloat(strIntName.c_str(), _pData))
            return 1;
    }

    return 0;
}

int ParamUI::Param_Vec2(const string& _strDesc, Vec2* _pData, bool _bDrag)
{
    ImGui::Text(_strDesc.c_str());
    ImGui::SameLine(100);

    string strIntName = GetNextName("##Param_Int");
    ImGui::SetNextItemWidth(150);

    float arrFloat[2] = {_pData->x, _pData->y};

    if (_bDrag)
    {
        if (ImGui::DragFloat2(strIntName.c_str(), arrFloat))
        {
            _pData->x = arrFloat[0];
            _pData->y = arrFloat[1];
            return 1;
        }
    }

    else
    {
        if (ImGui::InputFloat2(strIntName.c_str(), arrFloat))
        {
            _pData->x = arrFloat[0];
            _pData->y = arrFloat[1];
            return 1;
        }
    }

    return 0;
}

int ParamUI::Param_Vec3(const string& _strDesc, Vec3* _pData, bool _bDrag)
{
    ImGui::Text(_strDesc.c_str());
    ImGui::SameLine(100);

    string strIntName = GetNextName("##Param_Int");
    ImGui::SetNextItemWidth(150);

    float arrFloat[3] = {_pData->x, _pData->y, _pData->z};

    if (_bDrag)
    {
        if (ImGui::DragFloat3(strIntName.c_str(), arrFloat))
        {
            _pData->x = arrFloat[0];
            _pData->y = arrFloat[1];
            _pData->z = arrFloat[2];
            return 1;
        }
    }

    else
    {
        if (ImGui::InputFloat3(strIntName.c_str(), arrFloat))
        {
            _pData->x = arrFloat[0];
            _pData->y = arrFloat[1];
            _pData->z = arrFloat[2];
            return 1;
        }
    }

    return 0;
}


int ParamUI::Param_Vec4(const string& _strDesc, Vec4* _pData, bool _bDrag)
{
    ImGui::Text(_strDesc.c_str());
    ImGui::SameLine(100);

    string strIntName = GetNextName("##Param_Int");
    ImGui::SetNextItemWidth(200);


    if (_bDrag)
    {
        if (ImGui::DragFloat4(strIntName.c_str(), *_pData))
            return 1;
    }

    else
    {
        if (ImGui::InputFloat4(strIntName.c_str(), *_pData))
            return 1;
    }

    return 0;
}

int ParamUI::Param_Tex(const string& _strDesc, Ptr<CTexture>& _Tex, UI* _UI, UI_DELEGATE_1 _Func)
{
    ImGui::Text(_strDesc.c_str());

    string strIntName = GetNextName("##Param_Tex");

    ImVec2 uv_min     = ImVec2(0.0f, 0.0f);             // Top-left
    ImVec2 uv_max     = ImVec2(1.0f, 1.0f);             // Lower-right
    ImVec4 tint_col   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

    if (_Tex == nullptr)
        ImGui::Image(nullptr, ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);
    else
        ImGui::Image(_Tex->GetSRV().Get(), ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

    // ��� üũ
    if (ImGui::BeginDragDropTarget())
    {
        // �ش� ��忡�� ���콺 �� ���, ������ PayLoad Ű���� ��ġ�� ���
        const ImGuiPayload* pPayLoad = ImGui::AcceptDragDropPayload("Resource");
        if (pPayLoad)
        {
            TreeNode* pNode = static_cast<TreeNode*>(pPayLoad->Data);
            CRes*     pRes  = reinterpret_cast<CRes*>(pNode->GetData());
            if (RES_TYPE::TEXTURE == pRes->GetType())
                _Tex = static_cast<CTexture*>(pRes);
        }

        ImGui::EndDragDropTarget();

        return 0;
    }


    ImGui::SameLine();

    string strBtnName = GetNextName("##TexSelectBtn");
    if (ImGui::Button(strBtnName.c_str(), ImVec2(18, 18)))
    {
        const map<wstring, Ptr<CRes>>& mapTex = CResMgr::GetInst()->GetResources(RES_TYPE::TEXTURE);

        ListUI* pListUI = static_cast<ListUI*>(ImGuiMgr::GetInst()->FindUI("##List"));
        pListUI->Reset("Texture", ImVec2(300.f, 500.f));
        for (const auto& pair : mapTex)
            pListUI->AddItem(string(pair.first.begin(), pair.first.end()));

        // �׸� ���ý� ȣ����� ��������Ʈ ���
        pListUI->AddDynamic_Select(_UI, _Func);

        return 1;
    }

    return 0;
}


string ParamUI::GetNextName(const string& _ShowName)
{
    char szKey[255] = {};
    strcpy_s(szKey, 255, _ShowName.c_str());

    char  szID[50] = "##";
    char* dest     = szID;
    _itoa_s(g_NextId++, dest + 2, 50 - 2, 10);

    strcat_s(szKey, 50, szID);

    return szKey;
}
