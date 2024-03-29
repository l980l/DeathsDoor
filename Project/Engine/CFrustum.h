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
private:
    CCamera* m_pOwner;
    Vec4     m_arrFace[FT_END];
    Vec3     m_arrProj[8];
    bool     m_bDebugShape;

public:
    void finaltick();

public:
    bool FrustumCheckByPoint(Vec3 _vWorldPos);
    bool FrustumCheckBySphere(Vec3 _vWorldPos, float _fRadius);

    void SetDrawDebugShape(bool _bDraw) { m_bDebugShape = _bDraw; }    

public:
    CLONE(CFrustum);
    CFrustum(CCamera* _pOwner);
    ~CFrustum();
};

