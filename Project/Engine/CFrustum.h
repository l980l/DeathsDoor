#pragma once
#include "CEntity.h"

class CCamera;

enum FACE_TYPE
{
    FT_NEAR,
    FT_FAR,
    FT_LEFT,
    FT_RIGHT,
    FT_TOP,
    FT_BOT,
    FT_END,
};

class CFrustum :
    public CEntity
{
    CCamera* m_pOwner;
    Vec4     m_arrFace[FT_END];
    Vec3     m_arrProj[8];
    bool     m_bDebugShape;

public:
    void finaltick();

    bool FrustumCheckByPoint(Vec3 _vWorldPos);
    bool FrustumCheckBySphere(Vec3 _vWorldPos, float _fRadius);

    void SetDrawDebugShape(bool _bDraw) { m_bDebugShape = _bDraw; }

    CLONE(CFrustum);
    CFrustum(CCamera* _pOwner);
    virtual ~CFrustum() override;
};
