#include "pch.h"
#include "CLandScape.h"

#include "CKeyMgr.h"

#include "CResMgr.h"
#include "CTransform.h"
#include "CCamera.h"

#include "CRenderMgr.h"
#include "CStructuredBuffer.h"


CLandScape::CLandScape()
	: CRenderComponent(COMPONENT_TYPE::LANDSCAPE)
	, m_iFaceX(0)
	, m_iFaceZ(0)
	, m_HeightMap(nullptr)
	, m_vBrushScale(0.1f, 0.1f)
	, m_fVelocity(0.2f)
	, m_pBrushTex(nullptr)
	, m_iBrushIdx(0)
	, m_pCSRaycast(nullptr)
	, m_pCrossBuffer(nullptr)
	, m_pCSHeightMap(nullptr)
	, m_pHeightMap(nullptr)
	, m_pCSWeightMap(nullptr)
	, m_pWeightMapBuffer(nullptr)
	, m_iWeightWidth(0)
	, m_iWeightHeight(0)
	, m_iWeightIdx(1)
	, m_eMod(LANDSCAPE_MOD::NONE)
	, m_pTileArrTex(nullptr)
	, m_vTessFactorDist(500.f, 2000.f)
	, m_iMaxTessFactorLevel(4)
{
	SetName(L"LandScape");
	init();
	SetFrustumCheck(false);
}


CLandScape::~CLandScape()
{
	if (nullptr != m_pCrossBuffer)
		delete m_pCrossBuffer;

	if (nullptr != m_pWeightMapBuffer)
		delete m_pWeightMapBuffer;
}

void CLandScape::begin()
{
}

void CLandScape::finaltick()
{
	if (KEY_TAP(KEY::_0))
	{
		m_eMod = LANDSCAPE_MOD::NONE;
	}
	else if (KEY_TAP(KEY::_1))
	{
		m_eMod = LANDSCAPE_MOD::HEIGHT_MAP;
	}
	else if (KEY_TAP(KEY::_2))
	{
		m_eMod = LANDSCAPE_MOD::SPLAT;
	}


	if (LANDSCAPE_MOD::NONE == m_eMod)
		return;

	if (KEY_PRESSED(KEY::LCTRL) && KEY_PRESSED(KEY::LBTN))
	{
		Raycasting();

		if (LANDSCAPE_MOD::HEIGHT_MAP == m_eMod)
		{
			// ���� ��ġ������ ���� ���̸� ������.
			m_pCSHeightMap->SetInputBuffer(m_pCrossBuffer); // ��ŷ ������ HeightShader�� ����

			m_pCSHeightMap->SetBrushTex(m_pBrushTex);		// ����� �귯�� �ؽ��� ����
			m_pCSHeightMap->SetBrushIdx(m_iBrushIdx);		// �귯�� �ε��� ����
			m_pCSHeightMap->SetBrushScale(m_vBrushScale);   // �귯�� ũ��
			m_pCSHeightMap->SetVelocity(m_fVelocity);
			m_pCSHeightMap->SetHeightMap(m_pHeightMap);
			m_pCSHeightMap->Execute();
		}
		else if (LANDSCAPE_MOD::SPLAT == m_eMod)
		{
			m_pCSWeightMap->SetInputBuffer(m_pCrossBuffer);	// Raycast ��ġ
			m_pCSWeightMap->SetBrushScale(m_vBrushScale);
			m_pCSWeightMap->SetBrushArrTex(m_pBrushTex);
			m_pCSWeightMap->SetBrushIdx(m_iBrushIdx);
			m_pCSWeightMap->SetVelocity(m_fVelocity);
			m_pCSWeightMap->SetWeightMap(m_pWeightMapBuffer, m_iWeightWidth, m_iWeightHeight); // ����ġ��, ���μ���
			m_pCSWeightMap->SetWeightIdx(m_iWeightIdx);
			m_pCSWeightMap->Execute();
		}		
	}
}

void CLandScape::render()
{
	if (GetMesh() == nullptr || GetMaterial(0) == nullptr)
		return;

	Transform()->UpdateData();

	// �� ���� ����
	//GetMaterial()->GetShader()->SetRSType(RS_TYPE::WIRE_FRAME);
	GetMaterial(0)->SetScalarParam(INT_0, &m_iFaceX);
	GetMaterial(0)->SetScalarParam(INT_1, &m_iFaceZ);
	GetMaterial(0)->SetScalarParam(INT_2, &m_iMaxTessFactorLevel);


	// ���̸� ����
	Vec2 vResolution = Vec2(m_pHeightMap->Width(), m_pHeightMap->Height());
	GetMaterial(0)->SetScalarParam(VEC2_0, &vResolution);

	// ����ġ ���� �ػ� ����
	Vec2 vWeightMapResolution = Vec2((float)m_iWeightWidth, (float)m_iWeightHeight);
	GetMaterial(0)->SetScalarParam(VEC2_1, &vWeightMapResolution);

	GetMaterial(0)->SetScalarParam(VEC2_2, &m_vBrushScale);
	GetMaterial(0)->SetScalarParam(VEC2_3, &m_vTessFactorDist);
	//GetMaterial()->SetTexParam(TEX_2, m_HeightMap);

	GetMaterial(0)->SetTexParam(TEX_2, m_pHeightMap);
	
	// ����ġ ���� ����
	m_pWeightMapBuffer->UpdateData(17, PIPELINE_STAGE::PS_PIXEL);

	// Ÿ�� �迭 ���� ����
	float fTileCount = float(m_pTileArrTex->GetArraySize() / 2); // ����, �븻�� ���������Ƿ� /2 ����
	GetMaterial(0)->SetScalarParam(FLOAT_1, &fTileCount);

	// Ÿ�� �ؽ��� ����
	GetMaterial(0)->SetTexParam(TEX_ARR_0, m_pTileArrTex);
	GetMaterial(0)->UpdateData();

	GetMesh()->render(0);

	m_pWeightMapBuffer->Clear();
	m_pCrossBuffer->Clear();
}

void CLandScape::render_depthmap()
{
	CRenderComponent::render_depthmap();


}





void CLandScape::SetFace(UINT _iFaceX, UINT _iFaceZ)
{
	m_iFaceX = _iFaceX;
	m_iFaceZ = _iFaceZ;

	CreateMesh();
}

void CLandScape::Raycasting()
{
	// ���� ī�޶� ������
	CCamera* pMainCam = CRenderMgr::GetInst()->GetMainCam();
	if (nullptr == pMainCam)
		return;

	// ���� ���� ������ ������ ���÷� ����
	const Matrix& matWorldInv = Transform()->GetWorldInvMat();
	const tRay& ray = pMainCam->GetRay();

	tRay CamRay = {};
	CamRay.vStart = XMVector3TransformCoord(ray.vStart, matWorldInv);
	CamRay.vDir = XMVector3TransformNormal(ray.vDir, matWorldInv);
	CamRay.vDir.Normalize();

	// ������ ī�޶� Ray �� ������ ����
	tRaycastOut out = { Vec2(0.f, 0.f), 0x7fffffff, 0 };
	m_pCrossBuffer->SetData(&out, 1);

	m_pCSRaycast->SetHeightMap(m_pHeightMap);
	m_pCSRaycast->SetFaceCount(m_iFaceX, m_iFaceZ);
	m_pCSRaycast->SetCameraRay(CamRay);
	m_pCSRaycast->SetOuputBuffer(m_pCrossBuffer);

	m_pCSRaycast->Execute();
}

void CLandScape::ComputeShaderSaveLoad(Ptr<CComputeShader> _pShader, COMPUTESHADER _tShader, wstring _strKey)
{

	Ptr<CComputeShader> pRes = CResMgr::GetInst()->FindRes<CComputeShader>(_strKey);
	if (nullptr != pRes)
	{
		_pShader = pRes;
		return;
	}

	switch (_tShader)
	{
	case COMPUTESHADER::HEIGHT:
		_pShader = new CHeightMapShader(32, 32, 1);
		_pShader->CreateComputeShader(L"shader\\heightmap.fx", "CS_HeightMap");
		CResMgr::GetInst()->AddRes<CComputeShader>(_strKey, m_pCSHeightMap.Get());
		break;
	case COMPUTESHADER::RAYCAST:
		_pShader = new CRaycastShader(32, 32, 1);
		_pShader->CreateComputeShader(L"shader\\raycast.fx", "CS_Raycast");
		CResMgr::GetInst()->AddRes<CComputeShader>(_strKey, m_pCSRaycast.Get());
		break;
	case COMPUTESHADER::WEIGHT:
		_pShader = new CWeightMapShader(32, 32, 1);
		_pShader->CreateComputeShader(L"shader\\weightmap.fx", "CS_WeightMap");
		CResMgr::GetInst()->AddRes<CComputeShader>(_strKey, m_pCSWeightMap.Get());
		break;
	}
}

void CLandScape::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);

	fwrite(&m_iFaceX, sizeof(UINT), 1, _File);
	fwrite(&m_iFaceZ, sizeof(UINT), 1, _File);
	SaveResRef(m_HeightMap.Get(), _File);
	fwrite(&m_vBrushScale, sizeof(Vec2), 1, _File);
	fwrite(&m_fVelocity, sizeof(float), 1, _File);
	SaveResRef(m_pBrushTex.Get(), _File);
	fwrite(&m_iBrushIdx, sizeof(UINT), 1, _File);
	SaveResRef(m_pHeightMap.Get(), _File);
	SaveResRef(m_pTileArrTex.Get(), _File);
	fwrite(&m_vTessFactorDist, sizeof(Vec2), 1, _File);
	fwrite(&m_iMaxTessFactorLevel, sizeof(int), 1, _File);
}

void CLandScape::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);

	fread(&m_iFaceX, sizeof(UINT), 1, _File);
	fread(&m_iFaceZ, sizeof(UINT), 1, _File);
	LoadResRef(m_HeightMap, _File);
	fread(&m_vBrushScale, sizeof(Vec2), 1, _File);
	fread(&m_fVelocity, sizeof(float), 1, _File);
	LoadResRef(m_pBrushTex, _File);
	fread(&m_iBrushIdx, sizeof(UINT), 1, _File);
	LoadResRef(m_pHeightMap, _File);
	LoadResRef(m_pTileArrTex, _File);
	ComputeShaderSaveLoad(m_pCSRaycast.Get(), COMPUTESHADER::RAYCAST, L"RaycastShader");
	ComputeShaderSaveLoad(m_pCSHeightMap.Get(), COMPUTESHADER::HEIGHT, L"HeightMapShader");
	ComputeShaderSaveLoad(m_pCSWeightMap.Get(), COMPUTESHADER::WEIGHT, L"WeightMapShader");
	fread(&m_vTessFactorDist, sizeof(Vec2), 1, _File);
	fread(&m_iMaxTessFactorLevel, sizeof(int), 1, _File);

	CreateMesh();
}
