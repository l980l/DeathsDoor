#include "pch.h"
#include "CRoomScript.h"
#include "CSpawnDoorScript.h"
#include "CSpawnMgr.h"
#include "CLevelSaveLoadInScript.h"
#include "CHitStoneScript.h"

CRoomScript::CRoomScript()
	: CScript((UINT)SCRIPT_TYPE::ROOMSCRIPT)
	, m_iRoomNum(-1)
	, m_iRemainMst(-1)
	, m_iRemainGimmik(-1)
	, m_iCurWaveNum(0)
	, m_iMaxWaveNum(0)
	, m_vecWave{}
	, m_bActive(false)
	, m_bSpawn(false)
	, m_bLastWave(false)
	, m_bWaveStart(false)
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
	, m_bLastWave(false)
	, m_bWaveStart(false)
	, m_bStoneHit(false)
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
	m_bWaveStart = false;
	m_iRoomNum = -1;
	m_iRemainMst = -1;
	m_iRemainGimmik = -1;
	m_iCurWaveNum = 0;
	m_iMaxWaveNum = 0;
	m_bActive = false;
	m_bSpawn = false;
	m_bLastWave = false;
	m_bWaveStart = false;
}

void CRoomScript::tick()
{
	if (m_iMaxWaveNum == 0)
		return;
	if (CLevelMgr::GetInst()->FindObjectByName(L"Gimmik"))
	{
		m_bStoneHit = CLevelMgr::GetInst()->FindObjectByName(L"Gimmik")->GetScript<CHitStoneScript>()->CheckStoneHit();
	}
	else
	{
		m_bStoneHit = true;
	}
	
	vector<CGameObject*> vecMonster = CLevelMgr::GetInst()->GetCurLevel()->GetLayer((int)LAYER::MONSTER)->GetParentObject();
	if (vecMonster.size() > m_prevMonsterNum)
	{
		m_bSpawn = true;//이전 몬스터 수 보다 많아지면 true
	}
	if (m_bSpawn)
	{
		m_bWaveStart = true;
	}
	
	if (m_iCurWaveNum == m_iMaxWaveNum - 1 && vecMonster.size() == m_prevMonsterNum && m_bLastWave&& m_bStoneHit)
	{
		CSpawnMgr::GetInst()->SetFence(m_iRoomNum, false);//내린다
		GetOwner()->SetLifeSpan(0.f);
	}

	if (vecMonster.size() == m_prevMonsterNum && m_bWaveStart && m_bLastWave == false)
	{
		++m_iCurWaveNum;
		SpawnMst();
		m_bWaveStart = false;
		m_bSpawn = false;
	}
	if (m_iCurWaveNum == m_iMaxWaveNum - 1 && (vecMonster.size() > m_prevMonsterNum))
	{
		//마지막 웨이브가 스폰이 되었다
		m_bLastWave = true;
	}

}

void CRoomScript::SpawnMst()
{
	//현재 웨이브의 몬스터 수를 확인해서 스폰하고 m_iRemainMst에 수 표시
	CLevelSaveLoadInScript script;
	for (size_t i = 0; i < m_vecWave[m_iCurWaveNum].size(); ++i)
	{
		CGameObject* pdoor = script.SpawnandReturnPrefab(L"prefab\\DoorPink.prefab", 8, m_vecWave[m_iCurWaveNum][i].SpawnPos);
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
