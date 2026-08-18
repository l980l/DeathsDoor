#pragma once
#include "CEntity.h"

#include "CGameObject.h"

class CTransform;
class CMeshRender;

#define GET_OTHER_COMPONENT(Type) C##Type* Type() {return m_pOwner->Type();}


class CComponent :
    public CEntity
{
    CGameObject*         m_pOwner;
    const COMPONENT_TYPE m_Type;

public:
    COMPONENT_TYPE GetType() const { return m_Type; }
    CGameObject*   GetOwner() const { return m_pOwner; }

    virtual void begin()
    {
    }

    virtual void tick()
    {
    }

    virtual void finaltick() = 0;
    virtual void finaltick_module();


    virtual CComponent* Clone() override = 0;

    virtual void SaveToLevelFile(FILE* _File) = 0;
    virtual void LoadFromLevelFile(FILE* _FILE) = 0;

    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);
    GET_OTHER_COMPONENT(Camera);
    GET_OTHER_COMPONENT(Collider2D);
    GET_OTHER_COMPONENT(Collider3D);
    GET_OTHER_COMPONENT(Light2D);
    GET_OTHER_COMPONENT(Light3D);
    GET_OTHER_COMPONENT(TileMap);
    GET_OTHER_COMPONENT(SkyBox);
    GET_OTHER_COMPONENT(Decal);
    GET_OTHER_COMPONENT(Animator2D);
    GET_OTHER_COMPONENT(Animator3D);
    GET_OTHER_COMPONENT(Rigidbody);

    GET_OTHER_COMPONENT(LandScape);
    GET_OTHER_COMPONENT(ParticleSystem);

    CComponent(COMPONENT_TYPE _Type);
    CComponent(const CComponent& _Other);
    virtual ~CComponent() override;

    friend class CGameObject;
};
