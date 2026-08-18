#include "pch.h"
#include "MaterialUI.h"

#include "ParamUI.h"

#include <Engine/CResMgr.h>
#include <Engine/CMaterial.h>

MaterialUI::MaterialUI()
    : ResUI(RES_TYPE::MATERIAL)
{
    SetName("Material");
}

MaterialUI::~MaterialUI()
{
}

int MaterialUI::render_update()
{
    ResUI::render_update();

    // Material �̸�
    ImGui::Text("Material");
    ImGui::SameLine();

    Ptr<CMaterial> pMtrl  = static_cast<CMaterial*>(GetTargetRes().Get());
    string         strKey = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());
    ImGui::InputText("##MtrlUIName", (char*)strKey.c_str(), ImGuiInputTextFlags_ReadOnly);

    // GraphicsShader �̸�
    ImGui::Text("Shader  ");
    ImGui::SameLine();

    Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
    if (nullptr != pShader)
    {
        string strKey = string(pShader->GetKey().begin(), pShader->GetKey().end());
        ImGui::InputText("##ShaderUIName", (char*)strKey.c_str(), strKey.length(), ImGuiInputTextFlags_ReadOnly);
    }
    else
    {
        char szEmtpy[10] = {};
        ImGui::InputText("##ShaderUIName", szEmtpy, 10, ImGuiInputTextFlags_ReadOnly);
    }

    ImGui::NewLine();
    ImGui::Text("Parameter");


    // Shader ���� �䱸�ϴ� ScalarParameter �� UI �� ����
    if (nullptr == pShader)
        return 0;

    const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();

    for (size_t i = 0; i < vecScalarParam.size(); ++i)
    {
        switch (vecScalarParam[i].eParam)
        {
        // Shader Parameter �� Int Ÿ���� ���
        case INT_0:
        case INT_1:
        case INT_2:
        case INT_3:
        {
            // ���� ��Ƽ���� ���õ� ���� ����   
            int data = 0;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Int(vecScalarParam[i].strDesc, &data))
                // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
        }
        break;
        case FLOAT_0:
        case FLOAT_1:
        case FLOAT_2:
        case FLOAT_3:
        {
            // ���� ��Ƽ���� ���õ� ���� ����   
            float data = 0;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Float(vecScalarParam[i].strDesc, &data))
                // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
        }
        break;
        case VEC2_0:
        case VEC2_1:
        case VEC2_2:
        case VEC2_3:
        {
            // ���� ��Ƽ���� ���õ� ���� ����   
            Vec2 data;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Vec2(vecScalarParam[i].strDesc, &data))
                // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
        }
        break;
        case VEC4_0:
        case VEC4_1:
        case VEC4_2:
        case VEC4_3:
        {
            // ���� ��Ƽ���� ���õ� ���� ����   
            Vec4 data;
            pMtrl->GetScalarParam(vecScalarParam[i].eParam, &data);
            if (ParamUI::Param_Vec4(vecScalarParam[i].strDesc, &data))
                // UI �ʿ��� ���� ����Ǿ�����, ���� ��Ƽ���� ���� ����
                pMtrl->SetScalarParam(vecScalarParam[i].eParam, &data);
        }
        break;
        case MAT_0:
        case MAT_1:
        case MAT_2:
        case MAT_3:
            break;
        }
    }

    // Shader ���� �䱸�ϴ� Texture Parameter �� UI �� ����
    const vector<tTexParam>& vecTexParam = pShader->GetTexParam();
    for (size_t i = 0; i < vecTexParam.size(); ++i)
    {
        ImGui::NewLine();
        Ptr<CTexture> pCurTex = pMtrl->GetTexParam(vecTexParam[i].eParam);
        if (ParamUI::Param_Tex(vecTexParam[i].strDesc, pCurTex, this, static_cast<UI_DELEGATE_1>(&MaterialUI::SelectTexture)))
            m_eSelected = vecTexParam[i].eParam;
        pMtrl->SetTexParam(vecTexParam[i].eParam, pCurTex);
    }

    return 0;
}


void MaterialUI::SelectTexture(DWORD_PTR _Key)
{
    string        strKey = (char*)_Key;
    Ptr<CTexture> pTex   = CResMgr::GetInst()->FindRes<CTexture>(wstring(strKey.begin(), strKey.end()));

    Ptr<CMaterial> pMtrl = static_cast<CMaterial*>(GetTargetRes().Get());
    pMtrl->SetTexParam(m_eSelected, pTex);
}
