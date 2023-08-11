#include "pch.h"
#include "CWaterScript.h"

CWaterScript::CWaterScript()
	: CScript((UINT)SCRIPT_TYPE::WATERSCRIPT)
	, m_pPlayer(nullptr)
	, m_fWaterHeight(300.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fWaterHeight, "WaterHeight");
}

CWaterScript::~CWaterScript()
{
}

void CWaterScript::begin()
{
	if (nullptr == m_pPlayer)
		m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	Transform()->SetRelativeRot(XM_PI * 1.5f, 0.f, 0.f);
	Transform()->SetRelativeScale(2666.f, 2113.f, 0.f);
}

void CWaterScript::tick()
{
	Vec3 CurPlayerPos = m_pPlayer->Transform()->GetWorldPos();
	CurPlayerPos.z += (CurPlayerPos.y - m_fWaterHeight);		// maincamera�� 45����. ������ z ��ǥ�� ���� �÷��̾� ��ġ��ŭ �ڷ� ������.
	CurPlayerPos.y = m_fWaterHeight;	// y ��ǥ�� �� ���̷�. 

	Transform()->SetRelativePos(CurPlayerPos);
}

void CWaterScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fWaterHeight, sizeof(float), 1, _File);
}

void CWaterScript::LoadFromLevelFile(FILE* _FILE)
{
	fread(&m_fWaterHeight, sizeof(float), 1, _FILE);
}
