#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CPhysXMgr.h"

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
    m_PxRigidbody->clearForce(physx::PxForceMode::eACCELERATION);
    SetVelocity(Vec3(0.f));
    m_PxRigidbody->setAngularVelocity(physx::PxVec3(0.f));
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
    physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    physx::PxVec3 CurVelocity = physx::PxVec3(Velocity.x, LinearVelocity.y, Velocity.z);
    m_PxRigidbody->setLinearVelocity(CurVelocity);
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

void CRigidbody::SetGravity(float _fGravity)
{
    physx::PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    physx::PxVec3 CurVelocity = physx::PxVec3(LinearVelocity.x, _fGravity, LinearVelocity.z);
    m_PxRigidbody->setLinearVelocity(CurVelocity);
}

void CRigidbody::SetMass(float _fMass) 
{ 
    m_PxRigidbody->setMass(physx::PxReal(_fMass)); 
}

void CRigidbody::SaveToLevelFile(FILE* _pFile)
{
    int a = 0;
    if (m_PxRigidbody)
        a = 1;
    fwrite(&a, sizeof(int), 1, _pFile);
    fwrite(&m_PxRigidbody, sizeof(physx::PxRigidDynamic), 1, _pFile);
}

void CRigidbody::LoadFromLevelFile(FILE* _pFile)
{
    int a = 0;
    fread(&a, sizeof(int), 1, _pFile);
    if (a)
        fread(&m_PxRigidbody, sizeof(physx::PxRigidDynamic), 1, _pFile);
}