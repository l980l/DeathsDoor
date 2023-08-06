#include "pch.h"
#include "CRoomScript.h"
#include "CSpawnDoorScript.h"
#include "CSpawnMgr.h"

CRoomScript::CRoomScript()
	: CScript((UINT)SCRIPT_TYPE::ROOMSCRIPT)
	, m_iRoomNum(-1)
	, m_iRemainMst(-1)
	, m_iRemainGimmik(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(0)
	, m_vecWave{}
	, m_bActive(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CRoomScript::CRoomScript(const CRoomScript& _Other)
	: CScript((UINT)SCRIPT_TYPE::ROOMSCRIPT)
	, m_iRoomNum(_Other.m_iRoomNum)
	, m_iRemainMst(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(_Other.m_iMaxWaveNum)
	, m_vecWave()
	, m_bActive(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CRoomScript::~CRoomScript()
{
	for (size_t i = 0; i < m_vecWave->size(); ++i)
	{
		m_vecWave[i].clear();
	}
}

void CRoomScript::begin()
{
	CSpawnMgr::GetInst()->RegisterWave(m_iRoomNum, this);
}

void CRoomScript::tick()
{
	if(m_bActive)
	{
		if(m_iRemainGimmik == 0 && m_iRemainMst == 0)
			CSpawnMgr::GetInst()->ModifyDoor(m_iRoomNum, true);
	}
}

void CRoomScript::SpawnMst()
{
	for (size_t i = 0; i < m_vecWave[m_iCurWaveNum].size(); ++i)
	{
		CGameObject* pMst = CResMgr::GetInst()->FindRes<CPrefab>(L"SpawnDoor")->Instantiate();
		wstring  wstrPrefabName = m_vecWave[m_iCurWaveNum][i].PrefabName;
		Vec3 SpawnPos = m_vecWave[m_iCurWaveNum][i].SpawnPos;
		pMst->GetScript<CSpawnDoorScript>()->SetSpawnMst(wstrPrefabName);
		SpawnGameObject(pMst, SpawnPos, (int)LAYER::DEFAULT);
	}
	m_iRemainMst = (int)m_vecWave[m_iCurWaveNum].size();
	++m_iCurWaveNum;
}

void CRoomScript::SetWaveInfo(int _iWaveNum, vector<SpawnInfo> _mapInfo)
{
	m_vecWave[_iWaveNum] = _mapInfo;
}

void CRoomScript::ReduceMonsterCount()
{
	if(m_iRemainMst > 0)
	{
		--m_iRemainMst;
		if (0 == m_iRemainMst)
		{
			if (m_iCurWaveNum < m_iMaxWaveNum)
				SpawnMst();
		}
	}
}

void CRoomScript::ReduceGimmickCount()
{
	if(m_iRemainGimmik > 0)
		--m_iRemainGimmik;
}

void CRoomScript::AddWaveMst(int _iWavwNum, wstring _wstrPrefName, Vec3 _vSpawnPos)
{
	SpawnInfo Info;
	Info.PrefabName = _wstrPrefName;
	Info.SpawnPos = _vSpawnPos;
	m_vecWave[_iWavwNum].push_back(Info);
}

void CRoomScript::BeginOverlap(CCollider2D* _Other)
{
	if (!m_bActive)
	{
		CSpawnMgr::GetInst()->SpawnMonster(m_iRoomNum);
		CSpawnMgr::GetInst()->ModifyDoor(m_iRoomNum, false);
		m_bActive = true;
	}
}

void CRoomScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iRoomNum, sizeof(int), 1, _File);
	fwrite(&m_iMaxWaveNum, sizeof(int), 1, _File);
	for (size_t i = 0; i < 3; ++i)
	{
		size_t size = m_vecWave[i].size();
		fwrite(&size, sizeof(size_t), 1, _File);

		for (size_t j = 0; j < size; ++j)
		{
			size_t NameLength = m_vecWave[i][j].PrefabName.length();
			fwrite(&NameLength, sizeof(size_t), 1, _File);
			fwrite(&m_vecWave[i][j].PrefabName, sizeof(wstring) * NameLength, 1, _File);
			fwrite(&m_vecWave[i][j].SpawnPos, sizeof(Vec3), 1, _File);
		}
	}
}

void CRoomScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iRoomNum, sizeof(int), 1, _File);
	fread(&m_iMaxWaveNum, sizeof(int), 1, _File);
	for (size_t i = 0; i < 3; ++i)
	{
		size_t  size = 0;
		fread(&size, sizeof(size_t), 1, _File);
		m_vecWave[i].resize(size);
		for (size_t j = 0; j < size; ++j)
		{
			size_t NameLength = 0;
			fread(&NameLength, sizeof(size_t), 1, _File);
			fread(&m_vecWave[i][j].PrefabName, sizeof(wstring) * NameLength, 1, _File);
			fread(&m_vecWave[i][j].SpawnPos, sizeof(Vec3), 1, _File);
		}
	}
}
