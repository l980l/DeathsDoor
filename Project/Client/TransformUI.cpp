#include "pch.h"
#include "TransformUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Script/CRoomScript.h>
#include <Engine/CRenderMgr.h>

TransformUI::TransformUI()
	: ComponentUI("##Transform", COMPONENT_TYPE::TRANSFORM)	
	, m_bShowEdieWave(false)
	, m_wstrPrefabName{}
	, m_vSpawnPos{}
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
	if (ImGui::DragFloat3("##Relative Rotation",vRotation))
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

	static bool bShow;
	if(GetTarget()->GetScript<CRoomScript>())
	{
		ImGui::Text("WaveEditor");
		ImGui::SameLine();
		ImGui::Checkbox("##WaveEditor", &m_bShowEdieWave);
		if (m_bShowEdieWave)
		{
			SetSize(0.f, 500.f);
			ShowWaveEditor();
		}
		else
			SetSize(0.f, 150.f);

	}

	return TRUE;
}

void TransformUI::ShowWaveEditor()
{

	CRoomScript* pWave = GetTarget()->GetScript<CRoomScript>();

	if (ImGui::Button("Bat       "))
		m_wstrPrefabName = L"prefab\\Bat.prefab";
	ImGui::SameLine();
	if (ImGui::Button("Lurker    "))
		m_wstrPrefabName = L"prefab\\Lurker.prefab";
	ImGui::SameLine();
	if (ImGui::Button("Grunt     "))
		m_wstrPrefabName = L"prefab\\Grunt.prefab";
	if (ImGui::Button("Bazooka   "))
		m_wstrPrefabName = L"prefab\\Bazooka.prefab";
	ImGui::SameLine();
	if (ImGui::Button("GrimKnight"))
		m_wstrPrefabName = L"prefab\\GrimKnight.prefab";
	ImGui::SameLine();
	if (ImGui::Button("Knight    "))
		m_wstrPrefabName = L"prefab\\Knight.prefab";
	if (ImGui::Button("CrowBoss  "))
		m_wstrPrefabName = L"prefab\\CrowBoss.prefab";

	ImGui::Text("SpawnPos");
	ImGui::InputFloat3("##SpawnPos", m_vSpawnPos);

	ImGui::Text("Wave Num");
	ImGui::SameLine();
	static int WaveNum = 0;
	ImGui::InputInt("##WaveNum", &WaveNum);

	ImGui::Text("Max  Num");
	ImGui::SameLine();
	static int MaxWaveNum = 0;
	ImGui::InputInt("##MaxWaveNum", &MaxWaveNum);

	if (ImGui::Button("ADD Mst", ImVec2(60.f, 20.f)))
		pWave->AddWaveMst(WaveNum, m_wstrPrefabName, m_vSpawnPos);

	vector<SpawnInfo> Wave = pWave->GetWaveInfo(WaveNum);

	for (size_t i = 0; i < Wave.size(); ++i)
	{
		wstring wstrPrefName = Wave[i].PrefabName;
		string strPrefName = string(wstrPrefName.begin(), wstrPrefName.end());

		string Count;
		Count = std::to_string(i);
		ImGui::Text(strPrefName.c_str());
		string label = "##";
		label += Count;
		if (ImGui::InputFloat3(label.c_str(), &Wave[i].SpawnPos.x))
			pWave->SetWaveInfo(WaveNum, Wave);
	}

}
