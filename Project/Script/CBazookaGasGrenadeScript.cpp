#include "pch.h"
#include "CBazookaGasGrenadeScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CPhysXMgr.h>

void CBazookaGasGrenadeScript::begin()
{
	// ����ź ��ƼŬ ������.
	m_GasBulletParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasBulletParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos());
	m_GasBulletParticle->ParticleSystem()->SetEmissive(true);

	GetOwner()->AddChild(m_GasBulletParticle);

	m_fBulletTime = 0.f;
}

void CBazookaGasGrenadeScript::tick()
{
	// ���ư��� ��
	if (m_iState == 0)
	{
		m_fBulletTime += DT;

		if (m_fBulletTime < 1.f)
		{
			Vec3 Velocity = m_ShotDir;
			float fSpeed = 70000.f;
			Velocity *= fSpeed * DT;

			GetOwner()->Rigidbody()->SetVelocity(Velocity);
		}

		Vec3 CurVelocity = GetOwner()->Rigidbody()->GetVelocity();

		// ���� �����ӿ��� �������� ���.
		if (m_PrevVelocity.y < 0.f)
		{
			// ���� ƨ�����. 
			if (CurVelocity.y >= 0.f)
			{
				GetOwner()->Rigidbody()->ClearForce();

				// ������ ������ ��ƼŬ ������.
				m_GasRoundParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasRoundParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetRelativePos());
				m_GasRoundParticle->ParticleSystem()->SetEmissive(true);
				m_GasCenterParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasCenterParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetRelativePos());
				m_GasCenterParticle->ParticleSystem()->SetEmissive(true);

				// ����ź ����
				DestroyObject(m_GasBulletParticle);
				m_GasBulletParticle = nullptr;
				m_iState = 1;
			}
		}

		m_PrevVelocity = CurVelocity;
	}
	
	// ������ ���
	else if (m_iState == 1)
	{
		m_fGasTime += DT;

		// ������ ������ ��ƼŬ ������.
		GetOwner()->Rigidbody()->ClearForce();

		if (m_fGasTime >= 1.f)
		{
			if (m_GasCenterParticle && !m_GasCenterParticle->IsDead())
			{
				DestroyObject(m_GasCenterParticle);
			}

			if (m_GasRoundParticle && !m_GasRoundParticle->IsDead())
			{
				DestroyObject(m_GasRoundParticle);
			}

			m_GasCenterParticle = nullptr;
			m_GasRoundParticle = nullptr;

			Destroy();
		}
	}
}

void CBazookaGasGrenadeScript::BeginOverlap(CCollider3D* _Other)
{
	// Player�� �ε��� ��� ������.
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
	, m_fBulletTime(0.f)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript(const CBazookaGasGrenadeScript& _Other) :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_GasBulletParticle(nullptr)
	, m_GasCenterParticle(nullptr)
	, m_GasRoundParticle(nullptr)
	, m_fBulletTime(0.f)
	, m_fGasTime(0.f)
{
}

CBazookaGasGrenadeScript::~CBazookaGasGrenadeScript()
{
	if (m_GasBulletParticle && !m_GasBulletParticle->IsDead())
	{
		DestroyObject(m_GasBulletParticle);
		m_GasBulletParticle = nullptr;
	}

	if (m_GasCenterParticle && !m_GasCenterParticle->IsDead())
	{
		DestroyObject(m_GasCenterParticle);
		m_GasCenterParticle = nullptr;
	}

	if (m_GasRoundParticle && !m_GasRoundParticle->IsDead())
	{
		DestroyObject(m_GasRoundParticle);
		m_GasRoundParticle = nullptr;
	}
}
