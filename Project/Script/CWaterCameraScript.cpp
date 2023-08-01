#include "pch.h"
#include "CWaterCameraScript.h"

#include <Engine\CRenderMgr.h>
#include <Engine\CDevice.h>

void CWaterCameraScript::begin()
{
	// MainCamera 참조.
	m_pMainCamera = CRenderMgr::GetInst()->GetMainCam()->GetOwner();
}

void CWaterCameraScript::tick()
{
	Vec3 CamPos = m_pMainCamera->Transform()->GetRelativePos();
	Vec3 CamRot = m_pMainCamera->Transform()->GetRelativeRot();

	// WaterCamera의 Pos와 Rot 적용.
	CamPos.y = m_fWaterHeight - CamPos.y;
	GetOwner()->Transform()->SetRelativePos(CamPos);

	CamRot.x = XM_2PI - CamRot.x;
	GetOwner()->Transform()->SetRelativeRot(CamRot);

	float Scale = m_pMainCamera->Camera()->GetScale();
	GetOwner()->Camera()->SetScale(Scale);
}

void CWaterCameraScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fWaterHeight, sizeof(float), 1, _File);
}

void CWaterCameraScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_fWaterHeight, sizeof(float), 1, _FILE);
}

CWaterCameraScript::CWaterCameraScript()
	: CScript((UINT)SCRIPT_TYPE::WATERCAMERASCRIPT)
	, m_pMainCamera(nullptr)
	, m_fWaterHeight(0.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fWaterHeight, "WaterHeight");
}

CWaterCameraScript::~CWaterCameraScript()
{
}
