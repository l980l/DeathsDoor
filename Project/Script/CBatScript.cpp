#include "pch.h"
#include "CBatScript.h"
#include "CPlayerScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"
#include <Engine/CDetourMgr.h>
#include "BatStates.h"



CBatScript::CBatScript()	:
	CMonsterScript((UINT)SCRIPT_TYPE::BATSCRIPT)
{
}

CBatScript::CBatScript(const CBatScript& _Other)	:
	CMonsterScript((UINT)SCRIPT_TYPE::BATSCRIPT)
{
}

CBatScript::~CBatScript()
{
}


void CBatScript::begin()
{
	CMonsterScript::begin();

	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// ���� ����
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"BatIdle", new CBatIdle);
		m_pStateScript->AddState(L"BatRecognize", new CBatRecognize);
		m_pStateScript->AddState(L"BatTrace", new CTrace);
		m_pStateScript->AddState(L"BatAttack", new CBatAttack);
		m_pStateScript->AddState(L"BatHit", new CBatHit);
		m_pStateScript->AddState(L"BatDeath", new CBatDeath);

		m_pStateScript->ChangeState(L"BatIdle");
	}

	//Rigidbody ����, ����, �������, ���� �ӵ� �� ����
	GetOwner()->Rigidbody()->SetVelocityLimit(100.f);

	// �ʱ� ���� ����.
	m_stat.HP = 100;
	m_stat.Max_HP = 100;
	m_stat.Attack = 1;
	m_stat.Attack_Speed = 10;
	m_stat.Speed = 200;
	m_pStateScript->SetStat(m_stat);
	recognizeCheck = false;
	onCollision = false;
	retrace = false;
}

void CBatScript::tick()
{	
	CMonsterScript::tick();
	
	// ���� ���� ����.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	if (recognizeCheck)
	{
		m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
		float dir = GetSmoothDir(GetOwner(), m_pPlayer);
		Vec3 curDir = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(curDir.x, dir, 0.f);
	}

	//1.Player�� Ž���ߴٸ� Idle->exit()���� Recognize --->Trace
	if (GetDetect()&& m_pStateScript->FindState(L"BatIdle") == m_pStateScript->GetCurState()&&
		recognizeCheck == false)
	{
		if (m_pStateScript->FindState(L"BatRecognize") != m_pStateScript->GetCurState())
		{
			m_pStateScript->ChangeState(L"BatRecognize");
			recognizeCheck = true;
		}
	}
	Vec3 PlayerPos = GetOwner()->GetScript<CMonsterScript>()->GetPlayer()->Transform()->GetWorldPos();
	float fDistance = GetDistance(PlayerPos, GetOwner()->Transform()->GetWorldPos());
	if (retrace && fDistance > 100.f)
	{
		if (m_pStateScript->FindState(L"BatTrace") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"BatTrace");
	}
	//2.HP�� 0 �̸� Death
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"BatDeath") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"BatDeath");
	}


}

void CBatScript::BeginOverlap(CCollider3D* _Other)
{
	if (CLevelMgr::GetInst()->GetCurLevel()->GetState() == LEVEL_STATE::STOP)
		return;


	//4.��, ȭ��, ��, ��ź, ������ �浹�ϸ� Hit
	if (L"Player" == _Other->GetOwner()->GetName() && onCollision == false)
	{
		m_pStateScript->ChangeState(L"BatAttack");
	}

	if (L"Sword" == _Other->GetName())
	{
		//ü��--
		//m_stat.HP -= SwordDamage
	}
	else if (L"Arrow" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Fire" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Bomb" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Hook" == _Other->GetName())
	{
		//ü��--
	}
	else if (L"Ghost" == _Other->GetName())
	{
		//ü��--
	}
}

void CBatScript::OnOverlap(CCollider3D* _Other)
{
	//if (CLevelMgr::GetInst()->GetCurLevel()->GetState() == LEVEL_STATE::STOP)
	//	return;
	//if (L"Player" == _Other->GetOwner()->GetName())
	//{
	//	//3.Player�� �浹�ߴٸ� Attack
	//	if (m_pStateScript->FindState(L"BatIdle") == m_pStateScript->GetCurState())
	//			m_pStateScript->ChangeState(L"BatAttack");
	//}
	
}

void CBatScript::EndOverlap(CCollider3D* _Other)
{
	onCollision = false;
	retrace = true;
}

void CBatScript::SaveToLevelFile(FILE* _File)
{
}

void CBatScript::LoadFromLevelFile(FILE* _File)
{
}
