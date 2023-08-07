#include "pch.h"
#include "CBazookaGasGrenadeScript.h"
#include "CLevelSaveLoadInScript.h"

void CBazookaGasGrenadeScript::begin()
{
	/*pObject->AddComponent(new CCollider3D);
	pObject->AddComponent(new CRigidbody);
	pObject->Collider3D()->SetCollider3DType(COLLIDER3D_TYPE::SPHERE);
	pObject->Collider3D()->SetOffsetScale(Vec3(700.f, 700.f, 700.f));
	pObject->Collider3D()->SetOffsetPos(Vec3(0.f, 0.f, 333.f));*/

	Vec3 Velocity = m_ShotDir;
	float fSpeed = 50.f;
	Velocity *= fSpeed;

	GetOwner()->Rigidbody()->SetVelocity(Velocity);

	// ���ڸ��� ��ġ�� ������ ��ƼŬ ������.
	m_GasBulletParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BatAttack.prefab", 3, GetOwner()->Transform()->GetWorldPos());
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
				DestroyObject(m_GasBulletParticle);
				m_iState = 1;

				// ������ ������ ��ƼŬ ������.
				m_GasCenterParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BatAttack.prefab", 3, GetOwner()->Transform()->GetWorldPos(), 1.f);
				m_GasRoundParticle = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\BatAttack.prefab", 3, GetOwner()->Transform()->GetWorldPos(), 1.f);
			}
		}

		m_PrevVelocity = CurVelocity;
	}
	
	// ������ ���
	else if (m_iState == 1)
	{
		// ������ ������ ��ƼŬ ������.
		GetOwner()->Rigidbody()->ClearForce();

		// �ð��� ������ m_GasParticle2�� ��������� Destroy
		if (!m_GasCenterParticle&& !m_GasRoundParticle)
			Destroy();
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
{
}

CBazookaGasGrenadeScript::CBazookaGasGrenadeScript(const CBazookaGasGrenadeScript& _Other) :
	CScript((UINT)SCRIPT_TYPE::BAZOOKAGASGRENADESCRIPT)
	, m_iState(0)
	, m_GasBulletParticle(nullptr)
	, m_GasCenterParticle(nullptr)
	, m_GasRoundParticle(nullptr)
{
}

CBazookaGasGrenadeScript::~CBazookaGasGrenadeScript()
{
}
