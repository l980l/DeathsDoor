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

	// Emissive로
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
	// 공격모션이 끝났다면 이후 제한시간 안에 공격하면 다음공격 아니라면 Idle로 전환
	m_fAcctime += DT;
	if (GetOwner()->Animator3D()->IsFinish() || m_fAcctime >= m_fDelay)
	{
		if (0.f == m_fAfterAttack)
			++m_iAttackCount;
		// 공격 모션이 끝나고 첫 번째 tick에만 현재 공격횟수가 증가하게 함
		// Idle까지의 시간 증가
		m_fAfterAttack += DT;

		// 공격 3회가 끝났거나, 공격모션이 끝나도 추가 공격을 입력하지 않은 경우 Idle로 전환
		if (m_iAttackCount >= 3 || m_fAfterAttack >= m_fTimeToIdle)
		{
			GetOwner()->GetScript<CPlayerScript>()->ChangeState(L"Idle");
		}
		else if (KEY_PRESSED(KEY::LBTN))
		{
			CalcDir();

			// 무기에도 공격횟수를 알려줌.
			CPlyWpAttack* pWpAttackState = (CPlyWpAttack*)GetOwner()->GetChild()[0]->GetScript<CStateScript>()->FindState(L"Attack");
			pWpAttackState->SetAttackCount(m_iAttackCount);

			// 좌우 번갈아 공격함
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
