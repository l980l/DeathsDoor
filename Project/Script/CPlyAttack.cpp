#include "pch.h"
#include "CPlyAttack.h"
#include "CPlayerScript.h"
#include "CPlyWpAttack.h"

#include <Engine/CDevice.h>

CPlyAttack::CPlyAttack()
	: m_iAttackCount(0)
	, m_fAfterAttack(0.f)
	, m_fAttackDelay(0.f)
	, m_fLimitTimeNextAttack(0.15f)
{
}

CPlyAttack::~CPlyAttack()
{
}

void CPlyAttack::Enter()
{
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
	CalcDir();
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
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
		else if(KEY_PRESSED(KEY::LBTN))
		{
			CalcDir();

			// ���⿡�� ����Ƚ���� �˷���.
			CPlyWpAttack* pWpAttackState = (CPlyWpAttack*)GetOwner()->GetChild()[0]->GetScript<CStateScript>()->FindState(L"Attack");
			pWpAttackState->SetAttackCount(m_iAttackCount);

			// �¿� ������ ������
			if (GetOwner()->Animator3D()->GetCurClip() == (int)PLAYERANIM_TYPE::SLASH_R)
				GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
			else
				GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);

			m_fAfterAttack = 0.f;
			m_fAttackDelay = 0.f;
		}
	}
}

void CPlyAttack::Exit()
{
	m_iAttackCount = 0;
	m_fAttackDelay = 0.f;
	m_fAfterAttack = 0.f;
}

void CPlyAttack::CalcDir()
{	
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);
	
	Vec3 AttackDir = Vec3(0.f, 0.f, 0.f);
	AttackDir = Vec3(0.f, 0.f, 0.f) - vMousePos;
	AttackDir.Normalize();
	AttackDir *= 500.f;
	AttackDir.y = 0.f;
	GetOwner()->Rigidbody()->AddVelocity(-AttackDir);
}
