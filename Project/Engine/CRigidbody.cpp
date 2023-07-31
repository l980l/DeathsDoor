#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CRigidbody::CRigidbody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_PxRigidbody(nullptr)
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::SetRigidbody(void* _pRigidbody)
{
	if (nullptr != m_PxRigidbody)
		assert(nullptr);

	m_PxRigidbody = (physx::PxRigidDynamic *)_pRigidbody;
}