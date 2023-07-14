#pragma once
#include "CComponent.h"

#include "Ptr.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CMesh.h"

class CStructuredBuffer;

class CAnimator3D :
    public CComponent
{
private:
    const vector<tMTBone>*      m_pVecBones;
    const vector<tMTAnimClip>*  m_pVecClip;

    vector<float>				m_vecClipUpdateTime;
    vector<Matrix>				m_vecFinalBoneMat; // �ؽ��Ŀ� ������ ���� �������
    int							m_iFrameCount; // 60
    double						m_dCurTime;
    int							m_iCurClip; // Ŭ�� �ε���	

    int							m_iFrameIdx; // Ŭ���� ���� ������
    int							m_iNextFrameIdx; // Ŭ���� ���� ������
    float						m_fRatio;	// ������ ���� ����

    CStructuredBuffer*          m_pBoneFinalMatBuffer;  // Ư�� �������� ���� ���
    bool						m_bFinalMatUpdate; // ������� ���� ���࿩��

public:
    virtual void finaltick() override;
    void UpdateData();

public:
    void SetBones(const vector<tMTBone>* _vecBones) { m_pVecBones = _vecBones; m_vecFinalBoneMat.resize(m_pVecBones->size()); }
    void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip);      // �ִϸ��̼� Ŭ�� ������ �����ϰ�, �ִϸ��̼� �� ��� �ð�(���� �󸶳� ����Ǿ�����)�� 0���� �ʱ�ȭ ��Ŵ.
    void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }
    void SetCurClip(int _iClipIdx) { m_iCurClip = _iClipIdx; }  // ���� Clip�� �����ϴ� �Լ�.
    int GetCurClip() { return m_iCurClip; }                     // ���� Cilp �ε����� ��ȯ�ϴ� �Լ�.
    int GetClipSize() { return m_vecClipUpdateTime.size(); }    // ��ü Clip ������ ��ȯ�ϴ� �Լ�.

    CStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    UINT GetBoneCount() { return (UINT)m_pVecBones->size(); }
    void ClearData();

    const vector<tMTAnimClip>* GetAnimClip() { return m_pVecClip; } // ���� �ִϸ��̼� Ŭ�� ���� Vecotr�� ��ȯ�ϴ� �Լ�.
    void SaveMeshAnimationClip();                                   // ���� Animator3D�� ���� �ִ� m_pVecClip�� Mesh�� �����ϰ�, Mesh->Save()�� ȣ���ؼ� Ŭ�� ������ �����ϴ� �Լ�. �ִϸ��̼� Ŭ���� Mesh���� Save �� Load�� �Ѵ�. 

private:
    void check_mesh(Ptr<CMesh> _pMesh);

public:
    virtual void SaveToLevelFile(FILE* _pFile) override;
    virtual void LoadFromLevelFile(FILE* _pFile) override;
    CLONE(CAnimator3D);

public:
    CAnimator3D();
    CAnimator3D(const CAnimator3D& _origin);
    ~CAnimator3D();
};
