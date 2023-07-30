#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CRigidbody::CRigidbody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(3.f)
	, m_fFriction(300.f)
	, m_fFrictionScale(3.f)
	, m_fVelocityLimit(1000.f)
	, m_fGravityVLimit(1000.f)
	, m_fGravityAccel(500.f)
	, m_bGravityUse(false)
	, m_bGround(false)
	, m_bIce(false)
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::finaltick()
{
	// F = M x A
	// ���ӵ� ���ϱ�
	Vec3 vAccel = m_vForce / m_fMass;

	// ���ӵ��� �̿��ؼ� �ӵ��� ������Ŵ
	m_vVelocity += vAccel * DT;

	// �߷��� ����ϴ� ����, ���� �־�� ������ ����
	// �߷��� ���� ������ ������ �ٷ� ����
	if (m_bGravityUse && m_bGround || !m_bGravityUse)
	{
		// ���� ���ӵ�
		Vec3 vFriction = -m_vVelocity;
		if (!(vFriction.x == 0.f && vFriction.y == 0.f && vFriction.z == 0.f))
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec3(0.f, 0.f, 0.f);
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			m_vVelocity += vFriction;
		}
	}

	// �߷� ���� + ���� ���� ==> �߷�
	if (m_bGravityUse && !m_bGround)
	{
		Vec3 vGravityAccel = Vec3(0.f, -m_fGravityAccel, 0.f);
		m_vVelocity += vGravityAccel * DT;
	}


	// �ӵ� ���� ����(��, ��)
	// �߷��� ����ϴ� ���, �¿� �̵��� �߷¹���(�Ʒ�) �� �ӵ������� ���� �����Ѵ�.
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
		}

		if (m_fGravityVLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
		}

		if (m_fVelocityLimit < fabsf(m_vVelocity.z))
		{
			m_vVelocity.z = (m_vVelocity.z / fabsf(m_vVelocity.z)) * m_fVelocityLimit;
		}
	}

	// �߷��� ������� ������, ��� �������ε� �ӵ� ������ �Ǵ�.
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			// ���� �ӵ��� �Ѱ��� ���
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}

	// ������Ʈ�� ��ġ
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ŵ
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;
	vPos.z += m_vVelocity.z * DT;

	GetOwner()->Transform()->SetRelativePos(vPos);

	m_vForce = Vec3(0.f, 0.f, 0.f);
}

void CRigidbody::SetRigidbody(bool _bDynamic, void* _pRigidbody)
{
}

void CRigidbody::SetGround(bool _bGround)
{
	m_bGround = _bGround;

	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}

void CRigidbody::SetIce(bool _bIce)
{
	m_bIce = _bIce;

	// ������ ������ ���⼭ �̲��������� �ٲ��� ��
}

void CRigidbody::SaveToLevelFile(FILE* _pFile)
{
}

void CRigidbody::LoadFromLevelFile(FILE* _pFile)
{
}
