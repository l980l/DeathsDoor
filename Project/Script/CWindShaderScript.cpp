#include "pch.h"
#include "CWindShaderScript.h"

void CWindShaderScript::begin()
{
    srand(time(0));
}

void CWindShaderScript::tick()
{
    float fSpawnTime = 5.f;

    m_fTime += DT;

    if (m_fTime > fSpawnTime)
    {
        m_fTime = 0.f;

        for (int i = 0; i < 4; ++i)
        {
            m_vecRandNum1[i] = rand() % 2;

        }

        for (int i = 0; i < 4; ++i)
        {
            m_vecRandNum2[i] = rand() % 2;

        }
    }

    CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl")->SetScalarParam(VEC4_0, &m_vecRandNum1);
    CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl")->SetScalarParam(VEC4_1, &m_vecRandNum2);
}

CWindShaderScript::CWindShaderScript()
	: CScript((UINT)SCRIPT_TYPE::WINDSHADERSCRIPT)
    , m_fTime(0.f)
    , m_bSpawn(false)
{
    Ptr<CTexture> NoiseTextue = CResMgr::GetInst()->Load<CTexture>(L"texture\\Deaths_Door\\noise.png", L"texture\\Deaths_Door\\noise.png");
    CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl")->SetTexParam(TEX_1, NoiseTextue.Get());
    Vec2 NoiseTextureSize(NoiseTextue->Width(), NoiseTextue->Height());
    CResMgr::GetInst()->FindRes<CMaterial>(L"WindMtrl")->SetScalarParam(VEC2_0, &NoiseTextureSize);
}

CWindShaderScript::~CWindShaderScript()
{
}
