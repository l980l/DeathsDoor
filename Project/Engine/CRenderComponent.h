#pragma once
#include "CComponent.h"


#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"


struct tMtrlSet
{
    Ptr<CMaterial> pSharedMtrl;  // 공유 메테리얼
    Ptr<CMaterial> pDynamicMtrl; // 공유 메테리얼의 복사본    
    Ptr<CMaterial> pCurMtrl;     // 현재 사용 할 메테리얼
};

class CRenderComponent :
    public CComponent
{
    Ptr<CMesh>       m_pMesh;
    vector<tMtrlSet> m_vecMtrls; // 재질    

    float m_fBounding;     // FrustumCheck 용도 경계범위
    bool  m_bFrustumCheck; // 절두체 컬링 체크 유무
    bool  m_bDynamicShadow;

public:
    virtual void render() = 0;
    virtual void render(UINT _iSubset) = 0;
    virtual void render_depthmap();

    void SetMesh(Ptr<CMesh> _Mesh);
    void SetMaterial(Ptr<CMaterial> _Mtrl, UINT _idx);

    Ptr<CMesh> GetMesh() { return m_pMesh; }

    Ptr<CMaterial> GetMaterial(UINT _idx);
    Ptr<CMaterial> GetSharedMaterial(UINT _idx);
    Ptr<CMaterial> GetDynamicMaterial(UINT _idx);

    UINT GetMtrlCount() const { return static_cast<UINT>(m_vecMtrls.size()); }

    ULONG64 GetInstID(UINT _iMtrlIdx);

    void  SetFrustumCheck(bool _bUse) { m_bFrustumCheck = _bUse; }
    bool  IsUseFrustumCheck() const { return m_bFrustumCheck; }
    void  SetBounding(float _fBounding) { m_fBounding = _fBounding; }
    float GetBounding() const { return m_fBounding; }
    void  SetDynamicShadow(bool _bSet) { m_bDynamicShadow = _bSet; }
    bool  IsDynamicShadow() const { return m_bDynamicShadow; }

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


    CRenderComponent(COMPONENT_TYPE _type);
    virtual ~CRenderComponent() override;
};
