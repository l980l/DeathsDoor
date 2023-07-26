#include "pch.h"
#include "CBankUpgradeScript.h"
#include "CPower.h"
#include "CAttackSpeed.h"
#include "CSpeed.h"
#include "CMagic.h"
#include "CStateScript.h"
#include <Engine/CEventMgr.h>
#include "CLevelSaveLoadInScript.h"
#include "CStateScript.h"

CBankUpgradeScript::CBankUpgradeScript()	:
	CScript(SCRIPT_TYPE::BANKUPGRADESCRIPT),
	m_Power(0),
	m_ASpeed(0),
	m_Speed(0),
	m_Magic(0)
{
}

CBankUpgradeScript::~CBankUpgradeScript()
{
}

void CBankUpgradeScript::begin()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// 상태 설정
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"Power", new CPower);
		m_pStateScript->AddState(L"AttackSpeed", new CAttackSpeed);
		m_pStateScript->AddState(L"Speed", new CSpeed);
		m_pStateScript->AddState(L"Magic", new CMagic);

		m_pStateScript->ChangeState(L"Power");
	}
	GetOwner()->Transform()->SetRelativeScale(Vec3(1913, 982.f, 1.f));
	Vec3 rot = (Vec3(0, -62, 0) / 180.f) * XM_PI;
	GetOwner()->Transform()->SetRelativeRot(rot);

	//플레이어의 능력치 받아오기
	CGameObject* player = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	CStateScript* script = player->GetScript<CStateScript>();
	Stat playerStatus = script->GetStat();
	m_Power = playerStatus.Attack;
	m_ASpeed = playerStatus.Attack_Speed;
	m_Speed = playerStatus.Speed;
	m_Magic = playerStatus.Magic_Attack;
}

void CBankUpgradeScript::tick()
{

	if (KEY_TAP(KEY::ESC))
	{
		tEvent evn = {};
		evn.Type = EVENT_TYPE::DELETE_OBJECT;
		evn.wParam = (DWORD_PTR)this->GetOwner();
		CEventMgr::GetInst()->AddEvent(evn);
	}
	//if (KEY_TAP(KEY::SPACE))
	//{
	//	CLevelSaveLoadInScript script;
	//	CGameObject* Icon = new CGameObject;
	//	Icon->AddComponent(new CTransform);
	//	Icon->AddComponent(new CMeshRender);
	//	Icon->Transform()->SetRelativeScale(Vec3(0, 0, 0));
	//	Icon->Transform()->SetRelativeRot(Vec3(0, 0, 0));
	///*	CGameObject* Icon = script.SpawnandReturnPrefab(L"prefab\\UgradeIcon.prefab", 0, Vec3(0, 0, 0));
	//	Icon->Transform()->SetRelativeScale(0,0,0);
	//	Icon->Transform()->SetRelativeRot(0,0,0);*/
	//}
}

void CBankUpgradeScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBankUpgradeScript::OnOverlap(CCollider3D* _Other)
{
	
}

void CBankUpgradeScript::EndOverlap(CCollider3D* _Other)
{
}