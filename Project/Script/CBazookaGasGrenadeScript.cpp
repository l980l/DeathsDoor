#include "pch.h"
#include "CBazookaGasGrenadeScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CPhysXMgr.h>

void CBazookaGasGrenadeScript::begin()
{
	Vec3 Velocity = m_ShotDir;
	float fSpeed = 100.f;
	Velocity *= fSpeed;

	GetOwner()->Rigidbody()->AddForce(Velocity);

	// 가스탄 파티클 프리펩.
	m_GasBulletParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasBulletParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos());
	m_GasBulletParticle->ParticleSystem()->SetEmissive(true);
}

void CBazookaGasGrenadeScript::tick()
{
	// 날아가는 중
	if (m_iState == 0)
	{
		Vec3 CurVelocity = GetOwner()->Rigidbody()->GetVelocity();

		// 이전 프레임에는 낙하중인 경우.
		if (m_PrevVelocity.y < 0.f)
		{
			// 땅에 튕긴거임. 
			if (CurVelocity.y > 0.f)
			{
				// 퍼지는 독가스 파티클 프리펩.
				m_GasCenterParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasCenterParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos(), 4.f);
				m_GasRoundParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasRoundParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos(), 6.f);
				m_GasCenterParticle->ParticleSystem()->SetEmissive(true);
				m_GasRoundParticle->ParticleSystem()->SetEmissive(true);

				// 가스탄 삭제
				DestroyObject(m_GasBulletParticle);
				m_iState = 1;
			}
		}

		m_PrevVelocity = CurVelocity;
	}
	
	// 퍼지는 경우
	else if (m_iState == 1)
	{
		m_fGasTime += DT;

		// 퍼지는 독가스 파티클 프리펩.
		GetOwner()->Rigidbody()->ClearForce();

		// 시간이 지나서 m_GasParticle2도 사라졌으면 Destroy
		if (m_fGasTime >= 3.f)
		{
			DestroyObject(m_GasCenterParticle);
			DestroyObject(m_GasRoundParticle);

			Destroy();
		}
	}
}

void CBazookaGasGrenadeScript::BeginOverlap(CCollider3D* _Other)
{
	// Player와 부딪힌 경우 데미지.
	if (_Other->GetOwner() == CLevelMgr::GetInst()->FindObjectByName(L"Player"))
	{
		
	}
}

void CBazookaGasGrenadeScript::OnOverlap(CCollider3D* _Other)
{
}

void CBazookaGasGrenadeScript::EndOverlap(CCollider3D* _Other)
{
}

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript() :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_GasBulletParticle(nullptr)
	, m_GasCenterParticle(nullptr)
	, m_GasRoundParticle(nullptr)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript(const CBazookaGasGrenadeScript& _Other) :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_GasBulletParticle(nullptr)
	, m_GasCenterParticle(nullptr)
	, m_GasRoundParticle(nullptr)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::~CBazookaGasGrenadeScript()
{
}
