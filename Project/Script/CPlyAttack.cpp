#include "pch.h"
#include "CPlyAttack.h"
#include "CPlayerScript.h"
#include "CPlyWpAttack.h"
#include "CLevelSaveLoadInScript.h"

#include <Engine/CDevice.h>

CPlyAttack::CPlyAttack()
	: m_iAttackCount(0)
	, m_fAfterAttack(0.f)
	, m_fAttackDelay(0.f)
	, m_fLimitTimeNextAttack(0.15f)
	, m_fAttackDir(0.f)
{
}

CPlyAttack::~CPlyAttack()
{
}

void CPlyAttack::Enter()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
	CalcDir();
	Slash();
}

void CPlyAttack::tick()
{
	// ���ݸ���� �����ٸ� ���� ���ѽð� �ȿ� �����ϸ� �������� �ƴ϶�� Idle�� ��ȯ
	m_fAttackDelay += DT;
	if (GetOwner()->Animator3D()->IsFinish() || m_fAttackDelay >= 0.35f)
	{
		if (0.f == m_fAfterAttack)
			++m_iAttackCount;
		// ���� ����� ������ ù ��° tick���� ���� ����Ƚ���� �����ϰ� ��
		// Idle������ �ð� ����
		m_fAfterAttack += DT;

		// ���� 3ȸ�� �����ų�, ���ݸ���� ������ �߰� ������ �Է����� ���� ��� Idle�� ��ȯ
		if (m_iAttackCount >= 3 || m_fAfterAttack >= m_fLimitTimeNextAttack)
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
		else if (KEY_PRESSED(KEY::LBTN))
		{
			CalcDir();

			// ���⿡�� ����Ƚ���� �˷���.
			CPlyWpAttack* pWpAttackState = (CPlyWpAttack*)GetOwner()->GetChild()[0]->GetScript<CStateScript>()->FindState(L"Attack");
			pWpAttackState->SetAttackCount(m_iAttackCount);

			// �¿� ������ ������
			Slash();

			m_fAfterAttack = 0.f;
			m_fAttackDelay = 0.f;
		}
	}
	else if (m_fAttackDelay > 0.3f)
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));//-m_vAttackDir * 500.f * (m_fAttackDelay / 0.35f) * DT);

}

void CPlyAttack::Exit()
{
	m_iAttackCount = 0;
	m_fAttackDelay = 0.f;
	m_fAfterAttack = 0.f;

	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
}

void CPlyAttack::CalcDir()
{	
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	m_fAttackDir = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, m_fAttackDir, 0.f);
	
	m_vAttackDir = Vec3(0.f, 0.f, 0.f);
	m_vAttackDir = Vec3(0.f, 0.f, 0.f) - vMousePos;
	m_vAttackDir.Normalize();
	Vec3 AttackDir = m_vAttackDir * 50.f;
	AttackDir.y = 0.f;
	GetOwner()->Rigidbody()->SetVelocity(-AttackDir);
}

void CPlyAttack::Slash()
{
	bool bRight = false;
	if(m_iAttackCount == 0 || m_iAttackCount % 2 == 0 )
		bRight =  true;
	CLevelSaveLoadInScript script;
	Vec3 SpawnPos = GetOwner()->Transform()->GetWorldPos() + Vec3(0.f, 20.f, 0.f) - m_vAttackDir * 100.f;
	if (bRight)
	{
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
		CGameObject* pSlashR = script.SpawnandReturnPrefab(L"prefab//SLASH_R.prefab", (int)LAYER::PLAYERPROJECTILE, SpawnPos, 0.35f);
		pSlashR->Transform()->SetRelativeRot(XM_PI * 1.5f, m_fAttackDir, 0.f);
	}
	else
	{
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
		CGameObject* pSlashL = script.SpawnandReturnPrefab(L"prefab//SLASH_L.prefab", (int)LAYER::PLAYERPROJECTILE, SpawnPos, 0.35f);
		pSlashL->Transform()->SetRelativeRot(XM_PI * 1.5f, -m_fAttackDir, XM_PI);
	}
}
