#include "pch.h"
#include "CWaveScript.h"

CWaveScript::CWaveScript()
	: CScript((UINT)SCRIPT_TYPE::WAVESCRIPT)
	, m_iRoomNum(-1)
	, m_iRemainMst(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(0)
	, m_vecWave{}
	, m_bActive(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CWaveScript::CWaveScript(const CWaveScript& _Other)
	: CScript((UINT)SCRIPT_TYPE::WAVESCRIPT)
	, m_iRoomNum(_Other.m_iRoomNum)
	, m_iRemainMst(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(_Other.m_iMaxWaveNum)
	, m_vecWave()
	, m_bActive(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CWaveScript::~CWaveScript()
{
	for (size_t i = 0; i < m_vecWave->size(); ++i)
	{
		m_vecWave[i].clear();
	}
}

void CWaveScript::begin()
{
}

void CWaveScript::tick()
{
}

void CWaveScript::SpawnMst()
{
	for (size_t i = 0; i < m_vecWave[m_iCurWaveNum].size(); ++i)
	{
		CGameObject* pMst = CResMgr::GetInst()->FindRes<CPrefab>(L"Spawner")->Instantiate();
		int iPrefabNum = m_vecWave[m_iCurWaveNum][i].PrefabNum;
		Vec2 Pos = m_vecWave[m_iCurWaveNum][i].SpawnPos;
		Vec3 vPos = Vec3(Pos.x, Pos.y, 300.f);
		pMst->GetScript<CSpawnScript>()->SetSpawnMst(iPrefabNum);
		SpawnGameObject(pMst, vPos, (int)LAYER::DEFAULT);
	}
	m_iRemainMst = (int)m_vecWave[m_iCurWaveNum].size();
	++m_iCurWaveNum;
}

void CWaveScript::SetWaveInfo(int _iWaveNum, vector<SpawnInfo> _mapInfo)
{
}

void CWaveScript::MinusMstCount()
{
}

void CWaveScript::AddWaveMst(int _iWavwNum, int _iPrefNum, Vec2 _vSpawnPos)
{
}

void CWaveScript::BeginOverlap(CCollider2D* _Other)
{
}

void CWaveScript::SaveToLevelFile(FILE* _File)
{
}

void CWaveScript::LoadFromLevelFile(FILE* _File)
{
}
