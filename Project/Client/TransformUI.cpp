#include "pch.h"
#include "TransformUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>

TransformUI::TransformUI()
	: ComponentUI("##Transform", COMPONENT_TYPE::TRANSFORM)	
{
	SetName("Transform");
}

TransformUI::~TransformUI()
{
}

int TransformUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	Vec3 vPos = GetTarget()->Transform()->GetRelativePos();
	Vec3 vScale = GetTarget()->Transform()->GetRelativeScale();
	Vec3 vRotation = GetTarget()->Transform()->GetRelativeRot();
	vRotation = (vRotation / XM_PI) * 180.f;

	// Position
	ImGui::Text("Position ");
	ImGui::SameLine();
	if (ImGui::DragFloat3("##Relative Position", vPos))
	{
		GetTarget()->Transform()->SetRelativePos(vPos);
	}

	// Scale
	ImGui::Text("Scale");
	ImGui::SameLine();
	static bool bSameRatio = false;
	ImGui::Checkbox("##SameRatio", &bSameRatio);
	ImGui::SameLine();
	if (ImGui::DragFloat3("##Relative Scale", vScale))
	{
		// 비율 유지 기능.
		if (bSameRatio)
		{
			vScale.y = vScale.x;
			vScale.z = vScale.x;
		}

		GetTarget()->Transform()->SetRelativeScale(vScale);
	}

	// Rotation
	ImGui::Text("Rotation ");
	ImGui::SameLine();
	if (ImGui::DragFloat3("##Relative Rotation", vRotation))
	{
		vRotation = (vRotation / 180.f) * XM_PI;
		GetTarget()->Transform()->SetRelativeRot(vRotation);
	}

	if (nullptr != GetTarget()->GetParent())
	{
		bool bAbsolute = GetTarget()->Transform()->IsAbsolute();
		string statename[2] = { "TRUE", "FALSE" };
		static int istate = bAbsolute ? 0 : 1;
		string curstate = statename[istate];
		ImGui::Text("Absolute");
		ImGui::SameLine();
		ImGui::SliderInt("##Absolute", &istate, 0, 1, curstate.c_str());
	}

	return TRUE;
}
