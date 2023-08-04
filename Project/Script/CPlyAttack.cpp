#include "pch.h"
#include "CPlyAttack.h"
#include "CPlayerScript.h"
#include "CPlyWpAttack.h"
#include "CLevelSaveLoadInScript.h"

#include <Engine/CDevice.h>

CPlyAttack::CPlyAttack()
	: m_iAttackCount(0)
	, m_fAfterAttack(0.f)
	, m_fDelay(0.f)
	, m_fTimeToIdle(0.15f)
	, m_fAttackDir(0.f)
{
	CLevelSaveLoadInScript script;
	m_pSlash[(UINT)SLASH::RIGHT] = script.SpawnandReturnPrefab(L"prefab//SLASH_R.prefab", (int)LAYER::PLAYERPROJECTILE, Vec3(0.f, 0.f, 0.f));
	m_pSlash[(UINT)SLASH::LEFT] = script.SpawnandReturnPrefab(L"prefab//SLASH_L.prefab", (int)LAYER::PLAYERPROJECTILE, Vec3(0.f, 0.f, 0.f));

	// Emissive��
	for (UINT i = (UINT)SLASH::LEFT; i < (UINT)SLASH::END; ++i)
	{
		int a = 1;
		m_pSlash[i]->MeshRender()->GetMaterial(0)->SetScalarParam(INT_0, &a);
	}
}

CPlyAttack::~CPlyAttack()
{
}

void CPlyAttack::Enter()
{
	GetOwner()->Rigidbody()->ClearForce();
	GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f));
	CalcDir();
	Slash();

	m_fDelay = GetOwnerScript()->GetStat().Attack_Speed;
	m_fRange = 40.f + 4.f * GetOwner()->GetScript<CPlayerScript>()->GetUpgrade(PLAYER_UPGRADE::Strength);

	m_vSlashPos = GetOwner()->Transform()->GetWorldPos() + Vec3(0.f, 20.f, 0.f) - m_vMouseDir * 100.f;
	m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativeRot(XM_PI * 1.6f, m_fAttackDir, 0.f);
	m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativeRot(XM_PI * 1.6f, -m_fAttackDir, XM_PI);
	m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativePos(Vec3(m_vSlashPos.x, m_vSlashPos.y - 30.f, m_vSlashPos.z));
	m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativePos(m_vSlashPos);
}

void CPlyAttack::tick()
{

	m_vSlashPos = GetOwner()->Transform()->GetWorldPos() + Vec3(0.f, 20.f, 0.f) - m_vMouseDir * 100.f;

	m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativePos(Vec3(m_vSlashPos.x, m_vSlashPos.y - 30.f, m_vSlashPos.z));
	m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativePos(m_vSlashPos);
	// ���ݸ���� �����ٸ� ���� ���ѽð� �ȿ� �����ϸ� �������� �ƴ϶�� Idle�� ��ȯ
	m_fAcctime += DT;
	if (GetOwner()->Animator3D()->IsFinish() || m_fAcctime >= m_fDelay)
	{
		if (0.f == m_fAfterAttack)
			++m_iAttackCount;
		// ���� ����� ������ ù ��° tick���� ���� ����Ƚ���� �����ϰ� ��
		// Idle������ �ð� ����
		m_fAfterAttack += DT;

		// ���� 3ȸ�� �����ų�, ���ݸ���� ������ �߰� ������ �Է����� ���� ��� Idle�� ��ȯ
		if (m_iAttackCount >= 3 || m_fAfterAttack >= m_fTimeToIdle)
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
			m_fAcctime = 0.f;
		}
	}
	else if (m_fAcctime > m_fDelay * 0.8f)
	{
		GetOwner()->Rigidbody()->SetVelocity(Vec3(0.f, 0.f, 0.f));
		m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	}

	
}

void CPlyAttack::Exit()
{
	m_iAttackCount = 0;
	m_fAcctime = 0.f;
	m_fAfterAttack = 0.f;
	GetOwner()->Rigidbody()->ClearForce();
	GetOwner()->Rigidbody()->SetGravity(0.f); 
}

void CPlyAttack::CalcDir()
{	
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	m_fAttackDir = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	GetOwner()->Transform()->SetRelativeRot(XM_PI * 1.5f, m_fAttackDir, 0.f);
	
	m_vMouseDir = Vec3(0.f, 0.f, 0.f);
	m_vMouseDir = Vec3(0.f, 0.f, 0.f) - vMousePos;
	m_vMouseDir.Normalize();
	Vec3 AttackDir = m_vMouseDir * 50.f;
	AttackDir.y = 0.f;
	GetOwner()->Rigidbody()->SetVelocity(-AttackDir);
}

void CPlyAttack::Slash()
{

	bool bRight = false;
	if(m_iAttackCount == 0 || m_iAttackCount % 2 == 0 )
		bRight =  true;
	if (bRight)
	{
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_R, false);
		m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativeScale(Vec3(m_fRange));
		m_pSlash[(UINT)SLASH::RIGHT]->Transform()->SetRelativeRot(XM_PI * 1.6f, m_fAttackDir, 0.f);
	}
	else
	{
		GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::SLASH_L, false);
		m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativeScale(Vec3(m_fRange));
		m_pSlash[(UINT)SLASH::LEFT]->Transform()->SetRelativeRot(XM_PI * 1.6f, -m_fAttackDir, XM_PI);
	}
}
