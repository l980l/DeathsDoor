#include "pch.h"
#include "DecalUI.h"

#include <Engine/CResMgr.h>
#include <Engine/CDecal.h>

#include "ImGuiMgr.h"
#include "ListUI.h"

#include "TreeUI.h"
#include "ParamUI.h"

DecalUI::DecalUI()
	: ComponentUI("##Decal", COMPONENT_TYPE::DECAL)
{
	SetName("Decal");
}

DecalUI::~DecalUI()
{
}

int DecalUI::render_update()
{

	if (FALSE == ComponentUI::render_update())
		return FALSE;

	//  ����� ������
	static bool bDebug = false;
	ImGui::Text("DebugMode ");
	ImGui::SameLine();
	if (ImGui::Checkbox("##DebugMode", &bDebug))
		GetTarget()->Decal()->SetShowDebug(bDebug);

	ImGui::SameLine();

	// Emissive ����
	static bool bLight = GetTarget()->Decal()->IsSetAsLight();
	ImGui::Text("LightMode ");
	ImGui::SameLine();
	if (ImGui::Checkbox("##LightMode", &bLight))
		GetTarget()->Decal()->SetAsLight(bLight);

	// Emissive�� ���� ���� ���� ���
	if(bLight)
	{
		ImGui::Text("LightAlpha");
		ImGui::SameLine();
		static float fDecalAlpha = GetTarget()->Decal()->GetAlpha();
		if (ImGui::SliderFloat("##DecalAlpha", &fDecalAlpha, 0.f, 1.f))
			GetTarget()->Decal()->SetAlpha(fDecalAlpha);
	}

	return TRUE;
}
