#include "pch.h"
#include "CBazookaGasGrenadeScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CPhysXMgr.h>
#include "CSoundScript.h"

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript() :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_pGasBulletParticle(nullptr)
	, m_pGasCenterParticle(nullptr)
	, m_pGasRoundParticle(nullptr)
	, m_fBulletTime(0.f)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript(const CBazookaGasGrenadeScript& _Other) :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_pGasBulletParticle(nullptr)
	, m_pGasCenterParticle(nullptr)
	, m_pGasRoundParticle(nullptr)
	, m_fBulletTime(0.f)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::~CBazookaGasGrenadeScript()
{
	if (m_pGasBulletParticle && !m_pGasBulletParticle->IsDead())
	{
		DestroyObject(m_pGasBulletParticle);
		m_pGasBulletParticle = nullptr;
	}

	if (m_pGasCenterParticle && !m_pGasCenterParticle->IsDead())
	{
		DestroyObject(m_pGasCenterParticle);
		m_pGasCenterParticle = nullptr;
	}

	if (m_pGasRoundParticle && !m_pGasRoundParticle->IsDead())
	{
		DestroyObject(m_pGasRoundParticle);
		m_pGasRoundParticle = nullptr;
	}
}

void CBazookaGasGrenadeScript::begin()
{
	// 가스탄 파티클 프리펩.
	m_pGasBulletParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasBulletParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos());
	m_pGasBulletParticle->ParticleSystem()->SetEmissive(true);

	m_fBulletTime = 0.f;

	// Sound
	CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Bazooka\\PlagueBoyFire1.ogg", 1, 0.1f);
}

void CBazookaGasGrenadeScript::tick()
{
	m_fBulletTime += DT;
	
	// 날아가는 중
	if (m_iState == 0)
	{

		if (m_fBulletTime < 0.5f)
		{
			Vec3 Velocity = m_vShotDir;
			float fSpeed = 350.f;
			Velocity *= fSpeed;

			m_pGasBulletParticle->Transform()->SetRelativePos(GetOwner()->Transform()->GetWorldPos());
			GetOwner()->Rigidbody()->SetVelocity(Velocity);
		}

		else
		{
			GetOwner()->Rigidbody()->ClearForce();

			// 퍼지는 독가스 파티클 프리펩.
			m_pGasRoundParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasRoundParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetRelativePos());
			m_pGasRoundParticle->ParticleSystem()->SetEmissive(true);
			m_pGasCenterParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasCenterParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetRelativePos());
			m_pGasCenterParticle->ParticleSystem()->SetEmissive(true);

			// 가스탄 삭제
			DestroyObject(m_pGasBulletParticle);
			m_pGasBulletParticle = nullptr;
			m_iState = 1;

			// Sound
			CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
			Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Bazooka\\PlagueBoyExplosion1.ogg", 1, 0.1f);
		}
	}
	
	// 퍼지는 경우
	else if (m_iState == 1)
	{
		m_fGasTime += DT;

		// 퍼지는 독가스 파티클 프리펩.
		GetOwner()->Rigidbody()->ClearForce();

		if (m_fGasTime >= 1.f)
		{
			if (m_pGasCenterParticle && !m_pGasCenterParticle->IsDead())
			{
				DestroyObject(m_pGasCenterParticle);
			}

			if (m_pGasRoundParticle && !m_pGasRoundParticle->IsDead())
			{
				DestroyObject(m_pGasRoundParticle);
			}

			m_pGasCenterParticle = nullptr;
			m_pGasRoundParticle = nullptr;

			Destroy();
		}
	}

	if (m_fBulletTime >= 7.f)
	{
		Destroy();
	}
}

void CBazookaGasGrenadeScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBazookaGasGrenadeScript::OnOverlap(CCollider3D* _Other)
{
}

void CBazookaGasGrenadeScript::EndOverlap(CCollider3D* _Other)
{
}
