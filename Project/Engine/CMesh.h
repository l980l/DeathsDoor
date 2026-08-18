#pragma once
#include "CRes.h"

#include "CFBXLoader.h"
#include "CStructuredBuffer.h"

struct tIndexInfo
{
    ComPtr<ID3D11Buffer> pIB;
    D3D11_BUFFER_DESC    tIBDesc;
    UINT                 iIdxCount;
    void*                pIdxSysMem;
};

class CMesh
    : public CRes
{
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC    m_tVBDesc;
    UINT                 m_VtxCount;
    void*                m_pVtxSys;

    // 하나의 버텍스버퍼에 여러개의 인덱스버퍼가 연결
    vector<tIndexInfo> m_vecIdxInfo;

public:
    Vtx*        GetVtxSysMem() const { return static_cast<Vtx*>(m_pVtxSys); }
    UINT        GetVtxCount() const { return m_VtxCount; }
    UINT        GetSubsetCount() const { return static_cast<UINT>(m_vecIdxInfo.size()); }
    tIndexInfo& GetIdxInfo(UINT _idx) { return m_vecIdxInfo[_idx]; }

    const vector<tMTBone>*     GetBones() const { return &m_vecBones; }
    UINT                       GetBoneCount() const { return static_cast<UINT>(m_vecBones.size()); }
    const vector<tMTAnimClip>* GetAnimClip() const { return &m_vecAnimClip; }
    bool                       IsAnimMesh() const { return !m_vecAnimClip.empty(); }

    CStructuredBuffer* GetBoneFrameDataBuffer() const { return m_pBoneFrameData; } // 전체 본 프레임 정보
    CStructuredBuffer* GetBoneOffsetBuffer() const { return m_pBoneOffset; }       // 각 뼈의 offset 행렬

    // Animation3D 정보
    vector<tMTAnimClip> m_vecAnimClip;
    vector<tMTBone>     m_vecBones;

    CStructuredBuffer* m_pBoneFrameData; // 전체 본 프레임 정보(크기, 이동, 회전) (프레임 개수만큼)
    CStructuredBuffer* m_pBoneOffset;    // 각 뼈의 offset 행렬(각 뼈의 위치를 되돌리는 행렬) (1행 짜리)

    void ChangeAnimClip(const vector<tMTAnimClip>* _vecAnimClip) { m_vecAnimClip = *_vecAnimClip; } // AnimClip을 변경하는 함수.

    static CMesh* CreateFromContainer(CFBXLoader& _loader);
    void          Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    virtual int Save(const wstring& _strRelativePath) override;

    void render(UINT _iSubset);
    void render_particle(UINT _iParticleCount);
    void render_instancing(UINT _iSubset);

private:
    void UpdateData(UINT _iSubset);
    void UpdateData_Inst(UINT _iSubset) const;

public:
    CMesh(bool _bEngine = false);
    virtual ~CMesh() override;
};
