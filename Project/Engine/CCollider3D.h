#pragma once
#include "CComponent.h"
class CCollider3D :
    public CComponent
{
private:
    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;
    bool            m_bAbsolute;
    COLLIDER3D_TYPE m_Shape;
    Matrix          m_matCollider3D;    // Collider �� �������

    int             m_iCollisionCount;  // �浹 Ƚ��


public:
    virtual void finaltick() override;

public:
    void SetOffsetPos(Vec3 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetOffsetScale(Vec3 _vOffsetScale) { m_vOffsetScale = _vOffsetScale; }
    void SetAbsolute(bool _bSet) { m_bAbsolute = _bSet; }
    void SetCollider3DType(COLLIDER3D_TYPE _Type) { m_Shape = _Type; }

    const Vec3& GetOffsetScale() { return m_vOffsetScale; }
    const Vec3& GetOffsetPos() { return m_vOffsetPos; }
    const bool& IsAbsolute() { return m_bAbsolute; }
    const COLLIDER3D_TYPE& GetCollider3DType() { return m_Shape; }
    const Matrix& GetColliderWorldMat() { return m_matCollider3D; }
    const int& GetCollisionCount() { return m_iCollisionCount; }


public:
    void BeginOverlap(CCollider3D* _Other);
    void OnOverlap(CCollider3D* _Other);
    void EndOverlap(CCollider3D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCollider3D);
public:
    CCollider3D();
    ~CCollider3D();
};

