#include "pch.h"
#include "CRoomScript.h"
#include "CSpawnDoorScript.h"
#include "CSpawnMgr.h"
#include "CLevelSaveLoadInScript.h"

CRoomScript::CRoomScript()
	: CScript((UINT)SCRIPT_TYPE::ROOMSCRIPT)
	, m_iRoomNum(-1)
	, m_iRemainMst(-1)
	, m_iRemainGimmik(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(0)
	, m_vecWave{}
	, m_bActive(false)
	,m_bSpawn(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, &m_iRoomNum, "RoomNum");
}

CRoomScript::CRoomScript(const CRoomScript& _Other)
	: CScript((UINT)SCRIPT_TYPE::ROOMSCRIPT)
	, m_iRoomNum(_Other.m_iRoomNum)
	, m_iRemainMst(-1)
	, m_iRemainGimmik(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(_Other.m_iMaxWaveNum)
	, m_vecWave()
	, m_bActive(false)
	, m_bSpawn(false)
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
	vector<CGameObject*> vecMonster = CLevelMgr::GetInst()->GetCurLevel()->GetLayer((int)LAYER::MONSTER)->GetParentObject();
	m_prevMonsterNum = vecMonster.size();
}

void CRoomScript::tick()
{
	/*if(m_bActive)
	{
		if(m_iRemainGimmik == 0 && m_iRemainMst == 0)
			CSpawnMgr::GetInst()->SetFence(m_iRoomNum, true);
	}*/
	//현재 웨이브의 몬스토 수가 남은 수보다 
	vector<CGameObject*> vecMonster = CLevelMgr::GetInst()->GetCurLevel()->GetLayer((int)LAYER::MONSTER)->GetParentObject();
	if (vecMonster.size() > m_prevMonsterNum)
	{
		m_bSpawn = true;
	}
	if (m_iCurWaveNum == m_iMaxWaveNum - 1 && m_bSpawn)
	{
		CSpawnMgr::GetInst()->SetFence(m_iRoomNum, false);//내린다
		GetOwner()->SetLifeSpan(0.f);

	}
	if (vecMonster.size() == m_prevMonsterNum && m_bSpawn)
	{
		++m_iCurWaveNum;
		SpawnMst();
		m_bSpawn = false;
	}
	
}

void CRoomScript::SpawnMst()
{
	//현재 웨이브의 몬스터 수를 확인해서 스폰하고 m_iRemainMst에 수 표시
	CLevelSaveLoadInScript script;
	for (size_t i = 0; i < m_vecWave[m_iCurWaveNum].size(); ++i)
	{
		CGameObject* pdoor = script.SpawnandReturnPrefab(L"prefab\\DoorPink.prefab", 0, m_vecWave[m_iCurWaveNum][i].SpawnPos);
		pdoor->AddComponent(new CSpawnDoorScript);
		pdoor->GetScript<CSpawnDoorScript>()->SetSpawnMst(m_vecWave[m_iCurWaveNum][i].PrefabName);
		pdoor->GetScript<CSpawnDoorScript>()->SetDelay(1.f);
		int a = 1;
		pdoor->MeshRender()->GetMaterial(0)->SetScalarParam(INT_1, &a);
		pdoor->MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, Vec4(0.6f,0.1f,0.2f,0.7f));
		
	}
	m_iRemainMst = (int)m_vecWave[m_iCurWaveNum].size();
	
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
	//웨이브 vector에 몬스터 정보를 입력
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
		CSpawnMgr::GetInst()->SetFence(m_iRoomNum, false);
		m_bActive = true;
	}
}

void CRoomScript::SaveToLevelFile(FILE* _File)
{
	/*fwrite(&m_iRoomNum, sizeof(int), 1, _File);
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
	}*/
}

void CRoomScript::LoadFromLevelFile(FILE* _File)
{
	/*fread(&m_iRoomNum, sizeof(int), 1, _File);
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
	}*/
}
