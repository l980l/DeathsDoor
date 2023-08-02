#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CHeightMapShader.h"
#include "CRaycastShader.h"
#include "CWeightMapShader.h"

enum class COMPUTESHADER
{
    HEIGHT,
    RAYCAST,
    WEIGHT,
};

class CLandScape :
    public CRenderComponent
{
private:
    UINT                    m_iFaceX;
    UINT                    m_iFaceZ;

    Ptr<CTexture>           m_HeightMap;    // ���� �ε����� ������ �����ؽ���

    Vec2                    m_vBrushScale;  // �귯�� ũ��(��ü ������� ũ��)
    float                   m_fVelocity;    // �귯�� �ݿ� �ӵ�
    Ptr<CTexture>           m_pBrushTex;    // �귯�� �ؽ���
    UINT                    m_iBrushIdx;

    Ptr<CRaycastShader>     m_pCSRaycast;   // ���콺 ��ŷ ���̴�
    CStructuredBuffer*      m_pCrossBuffer; // ���콺 ��ŷ ���� ������ �޴� ����

    Ptr<CHeightMapShader>   m_pCSHeightMap; // ���̸� ���̴�
    Ptr<CTexture>           m_pHeightMap;   // ���̸� �ؽ���

    Ptr<CWeightMapShader>   m_pCSWeightMap;     // ����ġ ���̴�
    CStructuredBuffer*      m_pWeightMapBuffer; // ����ġ ���� ����
    UINT                    m_iWeightWidth;     // ����ġ ������ ���μ��� ��� ��
    UINT                    m_iWeightHeight;    // ������ų ����ġ ����
    UINT                    m_iWeightIdx;       // �ؽ��� �迭 �� ����� �ؽ��� 

    LANDSCAPE_MOD           m_eMod;             // ���� ����忡�� ���°�

    Ptr<CTexture>           m_pTileArrTex;      // Ÿ�� �迭 �ؽ���

    Vec2                    m_vTessFactorDist;
    int                     m_iMaxTessFactorLevel;


  

public:
    LANDSCAPE_MOD GetCurMod() { return m_eMod; }
    void SetMod(LANDSCAPE_MOD _tMod) { m_eMod = _tMod; }
    
    void SetFace(UINT _iFaceX, UINT _iFaceZ);
    Vec2 GetFace() { return Vec2(m_iFaceX, m_iFaceZ); }

    Ptr<CTexture>& GetBrushTex() { return m_pBrushTex; }
    void SetBrushTex(Ptr<CTexture> _pBrushTex) { m_pBrushTex = _pBrushTex; }

    Vec2 GetBrushScale() { return m_vBrushScale; }
    void SetBrushScale(Vec2 _vScale) { m_vBrushScale = _vScale; }

    void SetVelocity(float _fVelocity) { m_fVelocity = _fVelocity; }
    float GetVelocity() { return m_fVelocity; }

    UINT GetBrushIdx() { return m_iBrushIdx; }
    void SetBrushIdx(UINT _iBrushIdx) { m_iBrushIdx = _iBrushIdx; }

    Ptr<CTexture>& GetHeightMap() { return m_pHeightMap; }
    void SetHeightMap(Ptr<CTexture> _HeightMap) { m_HeightMap = _HeightMap; }

    UINT GetWeightIdx() { return m_iWeightIdx; }
    void SetWeightIdx(UINT _iWeight) { m_iWeightIdx = _iWeight; }

    Ptr<CTexture>& GetTileArrTex() { return m_pTileArrTex; }

    Vec2 GetTessFactorDist() { return m_vTessFactorDist; }
    void SetTessFactorDist(Vec2 _vDist) { m_vTessFactorDist = _vDist; }

    int GetMaxTessFactorLevel() { return m_iMaxTessFactorLevel; }
    void SetMaxTessFactorLevel(int _iLevel) { m_iMaxTessFactorLevel = _iLevel; }

    virtual void begin() override;
    virtual void finaltick() override;
    virtual void render() override;
    virtual void render(UINT _iSubset) override;
    virtual void render_depthmap() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

private:
    void init();
    void CreateMesh();
    void CreateComputeShader();
    void CreateTexture();

    void Raycasting();

    void ComputeShaderSaveLoad(Ptr<CComputeShader> _pShader, COMPUTESHADER _tShader, wstring _strKey);

    CLONE(CLandScape);

public:
    CLandScape();
    ~CLandScape();
};

