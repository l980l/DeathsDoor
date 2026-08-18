#pragma once

#include "CStructuredBuffer.h"
#include "CTexture.h"
#include "CCopyBoneShader.h"

class CInstancingBuffer
    : public CSingleton<CInstancingBuffer>
{
    ComPtr<ID3D11Buffer>    m_pInstancingBuffer;
    UINT                    m_iMaxCount;
    vector<tInstancingData> m_vecData;

    // anim3D 용도
    vector<CStructuredBuffer*> m_vecBoneMat;
    int                        m_iAnimInstCount;
    CStructuredBuffer*         m_pBoneBuffer;

    Ptr<CCopyBoneShader> m_pCopyShader;

public:
    void init();

    void Clear()
    {
        m_vecData.clear();
        m_vecBoneMat.clear();
        m_iAnimInstCount = 0;
    }

    void AddInstancingData(tInstancingData& _tData) { m_vecData.push_back(_tData); }

    UINT                 GetInstanceCount() const { return static_cast<UINT>(m_vecData.size()); }
    ComPtr<ID3D11Buffer> GetBuffer() { return m_pInstancingBuffer; }
    void                 SetData();

    void               AddInstancingBoneMat(CStructuredBuffer* _pBuffer);
    int                GetAnimInstancingCount() const { return m_iAnimInstCount; };
    CStructuredBuffer* GetBoneBuffer() const { return m_pBoneBuffer; }

private:
    void Resize(UINT _iCount);

public:
    CInstancingBuffer();
    virtual ~CInstancingBuffer() override;
};
