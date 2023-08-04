#include "pch.h"
#include "CGrimKnightScript.h"
#include "CPlayerScript.h"

#include <Engine/CGameObject.h>
#include<Engine/CRigidbody.h>
#include "CTrace.h"
#include "CStateScript.h"

#include "GrimKnightStates.h"



CGrimKnightScript::CGrimKnightScript()	:
	CMonsterScript((UINT)SCRIPT_TYPE::GRIMKNIGHTSCRIPT)
{
}

CGrimKnightScript::CGrimKnightScript(const CGrimKnightScript& _Other) :
	CMonsterScript((UINT)SCRIPT_TYPE::GRIMKNIGHTSCRIPT)
{
}

CGrimKnightScript::~CGrimKnightScript()
{
}

void CGrimKnightScript::begin()
{
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
		m_pStateScript->AddState(L"Idle", new CGrimKnightIdle);
		m_pStateScript->AddState(L"Trace", new CTrace);
		m_pStateScript->AddState(L"Attack", new CGrimKnightMelee);
		m_pStateScript->AddState(L"SpinDown", new CGrimKnightSpinDown);
		m_pStateScript->AddState(L"SpinUp", new CGrimKnightSpinUp);
		m_pStateScript->AddState(L"SpinLeft", new CGrimKnightLeftSpin);
		m_pStateScript->AddState(L"SpinRight", new CGrimKnightRightSpin);
		m_pStateScript->AddState(L"LongDistance", new CGrimKnightLongDistance);
		m_pStateScript->AddState(L"BackStep1", new CGrimKnightBackStep);
		m_pStateScript->AddState(L"BackStep2", new CGrimKnightBackStep2);
		m_pStateScript->AddState(L"Guard", new CGrimKnightGuard);
		m_pStateScript->AddState(L"GuardStay", new CGrimKnightGuardStay);
		m_pStateScript->AddState(L"GuardBreak", new CGrimKnightGuardBreak);
		m_pStateScript->AddState(L"Hit", new CGrimKnightHit);
		m_pStateScript->AddState(L"Death", new CGrimKnightDeath);

		m_pStateScript->ChangeState(L"Idle");
	}

	//Rigidbody ����, ����, �������, ���� �ӵ� �� ����
	GetOwner()->Rigidbody()->SetMass(1.f);
	GetOwner()->Rigidbody()->SetFriction(1.f);
	GetOwner()->Rigidbody()->SetFrictionScale(1.f);
	GetOwner()->Rigidbody()->SetVelocityLimit(300.f);

	// �ʱ� ���� ����.
	m_stat.HP = 300;
	m_stat.Attack = 1;
	m_stat.Attack_Speed = 10;
	m_stat.Speed = 300;
	m_pStateScript->SetStat(m_stat);

	recognizeCheck = false;
	onCollision = false;
	retrace = false;
}

void CGrimKnightScript::tick()
{
	//���� �÷��̾� Ž�� -> ����
	if (GetDetect() && m_pStateScript->FindState(L"Idle") == m_pStateScript->GetCurState() &&
		recognizeCheck == false)
	{
		recognizeCheck = true;
		m_pStateScript->ChangeState(L"Trace");
	}

	if (recognizeCheck)
	{
		/*m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
		float dir = GetSmoothDir(GetOwner(), m_pPlayer);
		Vec3 curDir = GetOwner()->Transform()->GetRelativeRot();
		GetOwner()->Transform()->SetRelativeRot(curDir.x, dir, 0.f);*/
	}

	else if (GetDetect() && m_pStateScript->FindState(L"LongDistance") == m_pStateScript->GetCurState())
	{
		m_pStateScript->ChangeState(L"Trace");
	}


	//2.HP�� 0 �̸� Death
	if (m_pStateScript->GetStat().HP <= 0)
	{
		if (m_pStateScript->FindState(L"Death") != m_pStateScript->GetCurState())
			m_pStateScript->ChangeState(L"Death");
		SetLifeSpan(0.5f);
	}
}

void CGrimKnightScript::BeginOverlap(CCollider3D* _Other)
{
	//4.��, ȭ��, ��, ��ź, ������ �浹�ϸ�
	if (L"Player" == _Other->GetOwner()->GetName() && onCollision == false)
	{
		m_pStateScript->ChangeState(L"Attack");
		onCollision = true;
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

void CGrimKnightScript::OnOverlap(CCollider3D* _Other)
{
}

void CGrimKnightScript::EndOverlap(CCollider3D* _Other)
{
}

void CGrimKnightScript::SaveToLevelFile(FILE* _File)
{

}

void CGrimKnightScript::LoadFromLevelFile(FILE* _File)
{
}
