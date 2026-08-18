#pragma once
#include "CComponent.h"
#include <PhysX/PxPhysics.h>
#include <PhysX/PxPhysicsAPI.h>

namespace physx
{
    class PxRigidDynamic;
}

class CRigidbody :
    public CComponent
{
    physx::PxRigidDynamic* m_PxRigidbody;
    SHAPE_TYPE             m_PxShapeType;
    Vec3                   m_vScale;
    Vec3                   m_vSpawnPos;

public:
    virtual void finaltick() override
    {
    };

    void SetRigidbody(void* _pRigidbody);
    void SetShapeType(physx::PxGeometryType::Enum _ShapeInfo);
    void SetRigidScale(Vec3 _vScale) { m_vScale = _vScale; }
    void SetSpawnPos(Vec3 _pxSpawnPos) { m_vSpawnPos = _pxSpawnPos; }
    void SetRigidPos(Vec3 _vPos) const;

    physx::PxRigidDynamic*      GetRigidbody() const { return m_PxRigidbody; }
    physx::PxGeometryType::Enum GetShapeType() const;
    Vec3                        GetRigidScale() const { return m_vScale; }
    Vec3                        SetSpawnPos() const { return m_vSpawnPos; }

    void AddForce(Vec3 _vForce) const;
    void ClearForce();

    void AddVelocity(Vec3 _vVelocity) const;
    void SetVelocity(Vec3 _vVelocity) const;
    void SetVelocityLimit(float _fLimit) const;
    void SetGravity(float _fGravity) const;
    Vec3 GetVelocity() const;
    void SetMass(float _fMass) const;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;

    CLONE(CRigidbody);

    CRigidbody();
    virtual ~CRigidbody() override;

    friend class CPhysXMgr;
};
