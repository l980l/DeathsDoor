#include "pch.h"
#include "RigidbodyUI.h"

#include <Engine\CRigidbody.h>

RigidbodyUI::RigidbodyUI()
	: ComponentUI("##Rigidbody", COMPONENT_TYPE::RIGIDBODY)
{
	SetName("Rigidbody");
}

RigidbodyUI::~RigidbodyUI()
{
}

int RigidbodyUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	float fMass = GetTarget()->Rigidbody()->GetMass();
	float fFriction = GetTarget()->Rigidbody()->GetFriction();
	float fFrictionScale = GetTarget()->Rigidbody()->GetFrictionScale();
	float fGravityAccel = GetTarget()->Rigidbody()->GetGravityAccel();
	float fVelocityLimit = GetTarget()->Rigidbody()->GetVelocityLimit();
	float fGravityLimit = GetTarget()->Rigidbody()->GetGravityLimit();

	bool bUseGround = GetTarget()->Rigidbody()->IsUseGravity();
	bool bIce = GetTarget()->Rigidbody()->IsIce();

	ImGui::Text("Mass         ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##Mass", &fMass, 1.f, 10.f))
	{
		GetTarget()->Rigidbody()->SetMass(fMass);
	}

	ImGui::Text("Friction     ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##Friction", &fFriction, 1.f, 1000.f))
	{
		GetTarget()->Rigidbody()->SetFriction(fFriction);
	}

	ImGui::Text("FrictionScale");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##FrictionScale", &fFrictionScale, 1.f, 10.f))
	{
		GetTarget()->Rigidbody()->SetFrictionScale(fFrictionScale);
	}

	ImGui::Text("GravityAccel ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##GravityAccel", &fGravityAccel, 1.f, 1000.f))
	{
		GetTarget()->Rigidbody()->SetGravityAccel(fGravityAccel);
	}

	ImGui::Text("GravityLimit ");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##GravityLimit", &fGravityLimit, 1.f, 1000.f))
	{
		GetTarget()->Rigidbody()->SetGravityVelocityLimit(fGravityLimit);
	}

	ImGui::Text("VelocityLimit");
	ImGui::SameLine();
	if (ImGui::SliderFloat("##VelocityLimit", &fVelocityLimit, 1.f, 1000.f))
	{
		GetTarget()->Rigidbody()->SetVelocityLimit(fVelocityLimit);
	}
	ImGui::Text("GravityUse   ");
	ImGui::SameLine();
	if (ImGui::Checkbox("##Ground", &bUseGround))
	{
		GetTarget()->Rigidbody()->SetGravity(bUseGround);
	}

	ImGui::Text("Ice          ");
	ImGui::SameLine();
	if (ImGui::Checkbox("##Ice", &bIce))
	{
		GetTarget()->Rigidbody()->SetIce(bIce);
	}

	return TRUE;
}
