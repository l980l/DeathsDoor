#pragma once
#include "CComponent.h"

class CCollider2D :
    public CComponent
{
    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;
    bool            m_bAbsolute;
    COLLIDER2D_TYPE m_Shape;
    Matrix          m_matCollider2D; // Collider 의 월드행렬

    int m_iCollisionCount; // 충돌 횟수


public:
    virtual void finaltick() override;

    void            SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = Vec3(_vOffsetPos.x, _vOffsetPos.y, 0.f); }
    void            SetOffsetScale(Vec2 _vOffsetScale) { m_vOffsetScale = Vec3(_vOffsetScale.x, _vOffsetScale.y, 1.f); }
    void            SetAbsolute(bool _bSet) { m_bAbsolute = _bSet; }
    void            SetCollider2DType(COLLIDER2D_TYPE _Type) { m_Shape = _Type; }
    COLLIDER2D_TYPE GetCollider2DType() const { return m_Shape; }
    bool            IsAbsolute() const { return m_bAbsolute; }

    Vec3          GetOffsetScale() const { return m_vOffsetScale; }
    Vec3          GetOffsetPos() const { return m_vOffsetPos; }
    const Matrix& GetColliderWorldMat() const { return m_matCollider2D; }
    const int     GetCollisionCount() const { return m_iCollisionCount; }


    void BeginOverlap(CCollider2D* _Other);
    void OnOverlap(CCollider2D* _Other);
    void EndOverlap(CCollider2D* _Other);

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CCollider2D);
    CCollider2D();
    virtual ~CCollider2D() override;
};
