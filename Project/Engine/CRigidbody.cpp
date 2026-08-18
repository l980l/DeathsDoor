#include "pch.h"
#include "CRigidbody.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CPhysXMgr.h"

CRigidbody::CRigidbody()
    : CComponent(COMPONENT_TYPE::RIGIDBODY)
    , m_PxRigidbody(nullptr)
    , m_PxShapeType{}
    , m_vScale{}
    , m_vSpawnPos{}
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::SetRigidbody(void* _pRigidbody)
{
    if (nullptr != m_PxRigidbody)
        assert(nullptr);
    m_PxRigidbody = static_cast<physx::PxRigidDynamic*>(_pRigidbody);
}

void CRigidbody::SetShapeType(PxGeometryType::Enum _ShapeInfo)
{
    switch (_ShapeInfo)
    {
    case PxGeometryType::Enum::eBOX:
        m_PxShapeType = SHAPE_TYPE::CUBE;
        break;
    case PxGeometryType::Enum::eCAPSULE:
        m_PxShapeType = SHAPE_TYPE::CAPSULE;
        break;
    case PxGeometryType::Enum::eSPHERE:
        m_PxShapeType = SHAPE_TYPE::SPHERE;
        break;
    }
}

void CRigidbody::SetRigidPos(Vec3 _vPos) const
{
    CPhysXMgr::GetInst()->SetRigidPos(m_PxRigidbody, _vPos);
}

PxGeometryType::Enum CRigidbody::GetShapeType() const
{
    PxGeometryType::Enum Type = PxGeometryType::Enum::eINVALID;
    switch (m_PxShapeType)
    {
    case SHAPE_TYPE::CUBE:
        Type = PxGeometryType::Enum::eBOX;
        return Type;
        break;
    case SHAPE_TYPE::CAPSULE:
        Type = PxGeometryType::Enum::eCAPSULE;
        return Type;
        break;
    case SHAPE_TYPE::SPHERE:
        Type = PxGeometryType::Enum::eSPHERE;
        return Type;
        break;
    }
}

void CRigidbody::AddForce(Vec3 _vForce) const
{
    const PxVec3& Force = PxVec3(_vForce.x, _vForce.y, _vForce.z);
    m_PxRigidbody->addForce(Force, PxForceMode::eVELOCITY_CHANGE);
}

void CRigidbody::ClearForce()
{
    m_PxRigidbody->clearForce(PxForceMode::eACCELERATION);
    SetVelocity(Vec3(0.f));
    m_PxRigidbody->setAngularVelocity(PxVec3(0.f));
}

void CRigidbody::AddVelocity(Vec3 _vVelocity) const
{
    PxVec3 AddVelocity    = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z) * 5.f;
    PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    m_PxRigidbody->setLinearVelocity(AddVelocity + LinearVelocity);
}

void CRigidbody::SetVelocity(Vec3 _vVelocity) const
{
    const PxVec3& Velocity       = PxVec3(_vVelocity.x, _vVelocity.y, _vVelocity.z) * 5.f;
    PxVec3        LinearVelocity = m_PxRigidbody->getLinearVelocity();
    PxVec3        CurVelocity    = PxVec3(Velocity.x, LinearVelocity.y, Velocity.z);
    m_PxRigidbody->setLinearVelocity(CurVelocity);
}

Vec3 CRigidbody::GetVelocity() const
{
    PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    return Vec3(LinearVelocity.x, LinearVelocity.y, LinearVelocity.z);
}

void CRigidbody::SetVelocityLimit(float _fLimit) const
{
    m_PxRigidbody->setMaxLinearVelocity(static_cast<physx::PxReal>(_fLimit));
}

void CRigidbody::SetGravity(float _fGravity) const
{
    PxVec3 LinearVelocity = m_PxRigidbody->getLinearVelocity();
    PxVec3 CurVelocity    = PxVec3(LinearVelocity.x, _fGravity, LinearVelocity.z);
    m_PxRigidbody->setLinearVelocity(CurVelocity);
}

void CRigidbody::SetMass(float _fMass) const
{
    m_PxRigidbody->setMass(static_cast<physx::PxReal>(_fMass));
}

void CRigidbody::SaveToLevelFile(FILE* _pFile)
{
    fwrite(&m_vSpawnPos, sizeof(Vec3), 1, _pFile);
    fwrite(&m_vScale, sizeof(Vec3), 1, _pFile);
    fwrite(&m_PxShapeType, sizeof(PxGeometryType::Enum), 1, _pFile);
}

void CRigidbody::LoadFromLevelFile(FILE* _pFile)
{
    fread(&m_vSpawnPos, sizeof(Vec3), 1, _pFile);
    fread(&m_vScale, sizeof(Vec3), 1, _pFile);
    fread(&m_PxShapeType, sizeof(PxGeometryType::Enum), 1, _pFile);
}
