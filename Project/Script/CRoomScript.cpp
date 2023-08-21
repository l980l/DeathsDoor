#include "pch.h"
#include "CRoomScript.h"
#include "CSpawnDoorScript.h"
#include "CSpawnMgr.h"
#include "CLevelSaveLoadInScript.h"
#include "CFenceScript.h"

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
	, m_iRemainGimmik(-1)
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
}

void CRoomScript::tick()
{


void CRoomScript::SpawnMst()
{
	//���� ���̺��� ���� ���� Ȯ���ؼ� �����ϰ� m_iRemainMst�� �� ǥ��
	for (size_t i = 0; i < m_vecWave[m_iCurWaveNum].size(); ++i)
	{
		CGameObject* pdoor = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\DoorPink.prefab", 8, m_vecWave[m_iCurWaveNum][i].SpawnPos);
		pdoor->AddComponent(new CSpawnDoorScript);
		pdoor->GetScript<CSpawnDoorScript>()->SetSpawnMst(m_vecWave[m_iCurWaveNum][i].PrefabName);
		pdoor->GetScript<CSpawnDoorScript>()->SetDelay(1.f);
		int a = 1;
		pdoor->MeshRender()->GetMaterial(0)->SetScalarParam(INT_1, &a);
		pdoor->MeshRender()->GetMaterial(0)->SetScalarParam(VEC4_0, Vec4(0.6f,0.1f,0.2f,0.7f));		
	}
	++m_iCurWaveNum;
	m_iRemainMst = (int)m_vecWave[m_iCurWaveNum].size();
}

void CRoomScript::ActivateFence(bool _bOpen)
{
	for (size_t i = 0; i < m_vecFence.size(); ++i)
	{
		m_vecFence[i]->ActivateFence(_bOpen);
	}
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
		if (0 <= m_iRemainMst)
		{
			if (m_iCurWaveNum < m_iMaxWaveNum)
			{
				SpawnMst();
				m_iRemainMst = 0;
			}
		}
	}
	if (m_iRemainMst <= 0 && m_iRemainGimmik <= 0
		&& m_iCurWaveNum == m_iMaxWaveNum)
	{
		for (size_t i = 0; i < m_vecFence.size(); ++i)
		{
			m_vecFence[i]->ActivateFence(false);
		}
	}
}

void CRoomScript::ReduceGimmickCount()
{
	if(m_iRemainGimmik > 0)
		--m_iRemainGimmik;
	if (m_iRemainMst <= 0 && m_iRemainGimmik <= 0
		&& m_iCurWaveNum == m_iMaxWaveNum)
	{
		for (size_t i = 0; i < m_vecFence.size(); ++i)
		{
			m_vecFence[i]->ActivateFence(false);
		}
	}
}

void CRoomScript::AddWaveMst(int _iWavwNum, wstring _wstrPrefName, Vec3 _vSpawnPos)
{
	//���̺� vector�� ���� ������ �Է�
	SpawnInfo Info;
	Info.PrefabName = _wstrPrefName;
	Info.SpawnPos = _vSpawnPos;
	m_vecWave[_iWavwNum].push_back(Info);
}

void CRoomScript::BeginOverlap(CCollider2D* _Other)
{
	GetOwner()->DeleteComponent(COMPONENT_TYPE::COLLIDER3D);
	CSpawnMgr::GetInst()->SpawnMonster(m_iRoomNum);
	CSpawnMgr::GetInst()->ActivateFence(m_iRoomNum, false);
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
