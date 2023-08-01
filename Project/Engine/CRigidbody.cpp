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

void CRigidbody::AddForce(Vec3 _vForce)
{
    const physx::PxVec3& Force = physx::PxVec3(_vForce.x , _vForce.y, _vForce.z);
    m_PxRigidbody->addForce(Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

void CRigidbody::ClearForce()
{
    m_PxRigidbody->clearForce(physx::PxForceMode::eVELOCITY_CHANGE);
}

void CRigidbody::AddVelocity(Vec3 _vVelocity)
{
    physx::PxVec3 AddVelocity = physx::PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    m_PxRigidbody->setLinearVelocity(AddVelocity + LinearVelocity);
}

void CRigidbody::SetVelocity(Vec3 _vVelocity)
{
    const physx::PxVec3& Velocity = physx::PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z);
    m_PxRigidbody->setLinearVelocity(Velocity);
}

Vec3 CRigidbody::GetVelocity()
{
    physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    return Vec3(LinearVelocity.x, LinearVelocity.y, LinearVelocity.z);
}

void CRigidbody::SetVelocityLimit(float _fLimit) 
{ 
    m_PxRigidbody->setMaxLinearVelocity(physx::PxReal(_fLimit)); 
}

void CRigidbody::SetMass(float _fMass) 
{ 
    m_PxRigidbody->setMass(physx::PxReal(_fMass)); 
}