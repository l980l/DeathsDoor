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

	// ����ź ��ƼŬ ������.
	m_GasBulletParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasBulletParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos());
	m_GasBulletParticle->ParticleSystem()->SetEmissive(true);
}

void CBazookaGasGrenadeScript::tick()
{
	// ���ư��� ��
	if (m_iState == 0)
	{
		Vec3 CurVelocity = GetOwner()->Rigidbody()->GetVelocity();

		// ���� �����ӿ��� �������� ���.
		if (m_PrevVelocity.y < 0.f)
		{
			// ���� ƨ�����. 
			if (CurVelocity.y > 0.f)
			{
				// ������ ������ ��ƼŬ ������.
				m_GasCenterParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasCenterParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos(), 4.f);
				m_GasRoundParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasRoundParticle.prefab", (int)LAYER::DEFAULT, GetOwner()->Transform()->GetWorldPos(), 6.f);
				m_GasCenterParticle->ParticleSystem()->SetEmissive(true);
				m_GasRoundParticle->ParticleSystem()->SetEmissive(true);

				// ����ź ����
				DestroyObject(m_GasBulletParticle);
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

		// �ð��� ������ m_GasParticle2�� ��������� Destroy
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
