#include "pch.h"
#include "CCamera.h"


#include "CDevice.h"
#include "CRenderMgr.h"
#include "CTransform.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CAnimator3D.h"
#include "CRenderComponent.h"
#include "CMaterial.h"
#include "CGraphicsShader.h"

#include "CMRT.h"
#include "CLight3D.h"

#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CInstancingBuffer.h"
#include "CMeshRender.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_Frustum(this)
	, m_fWidth(0.f)
	, m_fAspectRatio(1.f)
	, m_fScale(1.f)
	, m_fFar(50000.f)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_iLayerMask(0)
	, m_iCamIdx(-1)
{
	SetName(L"Camera");

	Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
	m_fWidth = vRenderResolution.x;
	m_fAspectRatio = vRenderResolution.x / vRenderResolution.y;
}

CCamera::CCamera(const CCamera& _Other)
	: CComponent(_Other)
	, m_Frustum(this)
	, m_fWidth(_Other.m_fWidth)
	, m_fAspectRatio(_Other.m_fAspectRatio)
	, m_fScale(_Other.m_fScale)
	, m_fFar(_Other.m_fFar)
	, m_ProjType(_Other.m_ProjType)
	, m_iLayerMask(_Other.m_iLayerMask)
	, m_iCamIdx(-1)
{
}

CCamera::~CCamera()
{	
}

void CCamera::begin()
{
	if (-1 != m_iCamIdx)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_iCamIdx); // camera begin �� �ش� ī�޶� �ε����� ���
	}
}

void CCamera::finaltick()
{
	CalcViewMat();

	CalcProjMat();	

	m_Frustum.finaltick();

	// ���콺���� ���� ���
	CalRay();
}

void CCamera::CalRay()
{
	// ���콺 ������ ���ϴ� Ray ���ϱ�
	// SwapChain Ÿ���� ViewPort ����
	CMRT* pMRT = CRenderMgr::GetInst()->GetMRT(MRT_TYPE::SWAPCHAIN);
	D3D11_VIEWPORT tVP = pMRT->GetViewPort();

	//  ���� ���콺 ��ǥ
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

	// ������ ī�޶��� ��ǥ�� �ݵ�� ������.
	m_ray.vStart = Transform()->GetWorldPos();

	// view space ������ ����
	m_ray.vDir.x = ((((vMousePos.x - tVP.TopLeftX) * 2.f / tVP.Width) - 1.f) - m_matProj._31) / m_matProj._11;
	m_ray.vDir.y = (-(((vMousePos.y - tVP.TopLeftY) * 2.f / tVP.Height) - 1.f) - m_matProj._32) / m_matProj._22;
	m_ray.vDir.z = 1.f;

	// world space ������ ����
	m_ray.vDir = XMVector3TransformNormal(m_ray.vDir, m_matViewInv);
	m_ray.vDir.Normalize();
}

void CCamera::CalcViewMat()
{
	// ==============
	// View ��� ���
	// ==============
	m_matView = XMMatrixIdentity();

	// ī�޶� ��ǥ�� �������� �̵�
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// ī�޶� �ٶ󺸴� ������ Z ��� �����ϰ� ����� ȸ�� ����� ����
	Matrix matViewRot = XMMatrixIdentity();

	Vec3 vR = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vU = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vF = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	matViewRot._11 = vR.x;	matViewRot._12 = vU.x;	matViewRot._13 = vF.x;
	matViewRot._21 = vR.y;	matViewRot._22 = vU.y;	matViewRot._23 = vF.y;
	matViewRot._31 = vR.z;	matViewRot._32 = vU.z;	matViewRot._33 = vF.z;

	m_matView = matViewTrans * matViewRot;
	m_matViewInv = XMMatrixInverse(nullptr, m_matView);
}

void CCamera::CalcProjMat()
{
	// =============
	// ���� ��� ���
	// =============
	m_matProj = XMMatrixIdentity();
	
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// ���� ����
		float fHeight = m_fWidth / m_fAspectRatio;
		m_matProj =  XMMatrixOrthographicLH(m_fWidth * (1.f / m_fScale), fHeight * (1.f / m_fScale), 1.f, m_fFar);
	}
	else
	{	
		// ���� ����
		m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, m_fFar);
	}

	// ������� �����
	m_matProjInv = XMMatrixInverse(nullptr, m_matProj);

	
}



void CCamera::SetLayerMask(int _iLayer, bool _Visible)
{
	if (_Visible)
	{
		m_iLayerMask |= 1 << _iLayer;
	}
	else
	{
		m_iLayerMask &= ~(1 << _iLayer);
	}
}

void CCamera::SetLayerMaskAll(bool _Visible)
{
	if (_Visible)
		m_iLayerMask = 0xffffffff;
	else
		m_iLayerMask = 0;
}

void CCamera::SetCameraIndex(int _idx)
{
	m_iCamIdx = _idx;
	CRenderMgr::GetInst()->RegisterCamera(this, m_iCamIdx);
}

void CCamera::SortObject()
{
	// ���� ������ �з����� ����
	clear();

	// ���� ���� �����ͼ� �з�
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		// ���̾� ����ũ Ȯ��
		if (m_iLayerMask & (1 << i))
		{
			CLayer* pLayer = pCurLevel->GetLayer(i);
			const vector<CGameObject*>& vecObject = pLayer->GetObjects();

			for (size_t j = 0; j < vecObject.size(); ++j)
			{
				CRenderComponent* pRenderCom = vecObject[j]->GetRenderComponent();

				// ������ ����� ���� ������Ʈ�� ����
				if (nullptr == pRenderCom)
					continue;

				// FrustumCheck
				if (pRenderCom->IsUseFrustumCheck())
				{
					Vec3 vWorldPos = vecObject[j]->Transform()->GetWorldPos();
					if (false == m_Frustum.FrustumCheckBySphere(vWorldPos, pRenderCom->GetBounding()))
						continue;
				}

				// ���׸��� ������ŭ �ݺ�
				UINT iMtrlCount = pRenderCom->GetMtrlCount();

				for (UINT iMtrl = 0; iMtrl < iMtrlCount; ++iMtrl)
				{
					// ������ ���ų�, ������ ���̴��� ������ �ȵ� ���
					if (nullptr == pRenderCom->GetMaterial(iMtrl)
						|| nullptr == pRenderCom->GetMaterial(iMtrl)->GetShader())
					{
						continue;
					}
					
					// ���̴� �����ο� ���� �з�
					SHADER_DOMAIN eDomain = pRenderCom->GetMaterial(iMtrl)->GetShader()->GetDomain();
					Ptr<CGraphicsShader> pShader = pRenderCom->GetMaterial(iMtrl)->GetShader();

					switch (eDomain)
					{
					case SHADER_DOMAIN::DOMAIN_DEFERRED:
					case SHADER_DOMAIN::DOMAIN_OPAQUE:
					case SHADER_DOMAIN::DOMAIN_MASK:
					{
						// Shader �� POV �� ���� �ν��Ͻ� �׷��� �з��Ѵ�.
						map<ULONG64, vector<tInstObj>>* pMap = NULL;
						Ptr<CMaterial> pMtrl = pRenderCom->GetMaterial(iMtrl);

						if (pShader->GetDomain() == SHADER_DOMAIN::DOMAIN_DEFERRED)
						{
							pMap = &m_mapInstGroup_D;
						}
						else if (pShader->GetDomain() == SHADER_DOMAIN::DOMAIN_OPAQUE
							|| pShader->GetDomain() == SHADER_DOMAIN::DOMAIN_MASK)
						{
							pMap = &m_mapInstGroup_F;
						}
						else
						{
							assert(nullptr);
							continue;
						}

						uInstID uID = {};
						uID.llID = pRenderCom->GetInstID(iMtrl);

						// ID �� 0 �� ==> Mesh �� Material �� ���õ��� �ʾҴ�.
						if (0 == uID.llID)
							continue;

						map<ULONG64, vector<tInstObj>>::iterator iter = pMap->find(uID.llID);
						if (iter == pMap->end())
						{
							pMap->insert(make_pair(uID.llID, vector<tInstObj>{tInstObj{ vecObject[j], iMtrl }}));
						}
						else
						{
							iter->second.push_back(tInstObj{ vecObject[j], iMtrl });
						}
					}
						break;
					case SHADER_DOMAIN::DOMAIN_DECAL:
						m_vecDecal.push_back(vecObject[j]);
						break;					
					case SHADER_DOMAIN::DOMAIN_TRANSPARENT:
						m_vecTransparent.push_back(vecObject[j]);
						break;
					case SHADER_DOMAIN::DOMAIN_POSTPROCESS:
						m_vecPost.push_back(vecObject[j]);
						break;
					case SHADER_DOMAIN::DOMAIN_UI:
						m_vecUI.push_back(vecObject[j]);
						break;
					}
				}				
			}
		}
	}
}

void CCamera::SortShadowObject()
{
	m_vecDynamicShadow.clear();

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecObj = pLayer->GetObjects();

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			CRenderComponent* pRenderCom = vecObj[j]->GetRenderComponent();

			if (pRenderCom && pRenderCom->IsDynamicShadow())
			{
				m_vecDynamicShadow.push_back(vecObj[j]);
			}
		}
	}
}


void CCamera::render()
{
	// ��� ������Ʈ
	g_transform.matView = m_matView;
	g_transform.matViewInv = m_matViewInv;
	g_transform.matProj = m_matProj;

	// =====================================
	// ���̴� �����ο� ���� ���������� �׸���
	// =====================================
	// Deferred Object
	// ���� ������� ���ϴ� ������ ���� �޴� �ؽ��Ŀ� �޾ƿ�

	if (m_bWaterCamera)
	{
		CRenderMgr::GetInst()->MRT_Clear(MRT_TYPE::WATER);
		// Water MRT�� ����
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::WATER)->OMSet();
		render_deferred();
		render_water();
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::SWAPCHAIN)->OMSet();
	}

	// MainCam
	else if(CRenderMgr::GetInst()->GetMainCam() == this)
	{
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::DEFERRED)->OMSet();
		render_deferred();
		render_transparent(); // ��ƼŬ

		// Decal Render
		// decal���� position tex�� ���ڷ� �ޱ� ����
		// ������ Target���� ������ Tex�� ���ε� ��������� ��.
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::DECAL)->OMSet();
		render_decal();

		// Lighting
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::LIGHT)->OMSet();

		// LightObj ���� render 
		const vector<CLight3D*> vecLight3D = CRenderMgr::GetInst()->GetLight3D();//
		for (size_t i = 0; i < vecLight3D.size(); ++i)
		{
			vecLight3D[i]->render();
		}
		render_blur();

		// (Deferred + Light) Merge
		// ���� ����� ���� �� SwapChain ��´�� ������ �� ���
		CRenderMgr::GetInst()->GetMRT(MRT_TYPE::SWAPCHAIN)->OMSet();
		render_merge();

		// Forward Object	
		//render_opaque();
		//render_mask();
		render_forward();

		//render_transparent(); // ��ƼŬ ������ ���⼭ ��. 

		// PostProcess
		render_postprocess();

		// UI
		//render_ui();
	}

	// UI Cam
	else
	{
		render_ui();
	}
}

void CCamera::render_depthmap()
{
	// ���� ī�޶��� View, Proj ����
	g_transform.matView = m_matView;
	g_transform.matViewInv = m_matViewInv;
	g_transform.matProj = m_matProj;

	for (size_t i = 0; i < m_vecDynamicShadow.size(); ++i)
	{
		m_vecDynamicShadow[i]->GetRenderComponent()->render_depthmap();
	}
}

void CCamera::render_water()
{
	Ptr<CTexture> pWaterTex = CResMgr::GetInst()->FindRes<CTexture>(L"WaterCameraTex");
	CResMgr::GetInst()->FindRes<CMaterial>(L"WaterMtrl")->SetTexParam(TEX_0, pWaterTex);
}


void CCamera::clear()
{
	for (auto& pair : m_mapInstGroup_D)
		pair.second.clear();
	for (auto& pair : m_mapInstGroup_F)
		pair.second.clear();
		
	m_vecDecal.clear();	
	m_vecTransparent.clear();
	m_vecPost.clear();
	m_vecUI.clear();
}

void CCamera::render_deferred()
{
	for (auto& pair : m_mapSingleObj)
	{
		pair.second.clear();
	}

	// Deferred object render
	tInstancingData tInstData = {};

	for (auto& pair : m_mapInstGroup_D)
	{
		// �׷� ������Ʈ�� ���ų�, ���̴��� ���� ���
		if (pair.second.empty())
			continue;

		// instancing ���� ���� �̸��̰ų�
		// Animation2D ������Ʈ�ų�(��������Ʈ �ִϸ��̼� ������Ʈ)
		// Shader �� Instancing �� �������� �ʴ°��
		if (pair.second.size() <= 1
			|| pair.second[0].pObj->Animator2D()
			|| pair.second[0].pObj->GetRenderComponent()->GetMaterial(pair.second[0].iMtrlIdx)->GetShader()->GetVSInst() == nullptr)
		{
			// �ش� ��ü���� ���� ���������� ��ȯ
			for (UINT i = 0; i < pair.second.size(); ++i)
			{
				map<INT_PTR, vector<tInstObj>>::iterator iter
					= m_mapSingleObj.find((INT_PTR)pair.second[i].pObj);

				if (iter != m_mapSingleObj.end())
					iter->second.push_back(pair.second[i]);
				else
				{
					m_mapSingleObj.insert(make_pair((INT_PTR)pair.second[i].pObj, vector<tInstObj>{pair.second[i]}));
				}
			}
			continue;
		}

		CGameObject* pObj = pair.second[0].pObj;
		Ptr<CMesh> pMesh = pObj->GetRenderComponent()->GetMesh();
		Ptr<CMaterial> pMtrl = pObj->GetRenderComponent()->GetMaterial(pair.second[0].iMtrlIdx);

		// Instancing ���� Ŭ����
		CInstancingBuffer::GetInst()->Clear();

		int iRowIdx = 0;
		bool bHasAnim3D = false;
		for (UINT i = 0; i < pair.second.size(); ++i)
		{
			tInstData.matWorld = pair.second[i].pObj->Transform()->GetWorldMat();
			tInstData.matWV = tInstData.matWorld * m_matView;
			tInstData.matWVP = tInstData.matWV * m_matProj;

			if (pair.second[i].pObj->Animator3D())
			{
				pair.second[i].pObj->Animator3D()->UpdateData();
				tInstData.iRowIdx = iRowIdx++;
				CInstancingBuffer::GetInst()->AddInstancingBoneMat(pair.second[i].pObj->Animator3D()->GetFinalBoneMat());
				bHasAnim3D = true;
			}
			else
				tInstData.iRowIdx = -1;

			CInstancingBuffer::GetInst()->AddInstancingData(tInstData);
		}

		// �ν��Ͻ̿� �ʿ��� �����͸� ����(SysMem -> GPU Mem)
		CInstancingBuffer::GetInst()->SetData();

		if (bHasAnim3D)
		{
			pMtrl->SetAnim3D(true); // Animation Mesh �˸���
			pMtrl->SetBoneCount(pMesh->GetBoneCount());
		}

		pMtrl->UpdateData_Inst();
		pMesh->render_instancing(pair.second[0].iMtrlIdx);

		// ����
		if (bHasAnim3D)
		{
			pMtrl->SetAnim3D(false); // Animation Mesh �˸���
			pMtrl->SetBoneCount(0);
		}
	}

	// ���� ������
	for (auto& pair : m_mapSingleObj)
	{
		if (pair.second.empty())
			continue;

		pair.second[0].pObj->Transform()->UpdateData();

		for (auto& instObj : pair.second)
		{
			instObj.pObj->GetRenderComponent()->render(instObj.iMtrlIdx);
		}

		if (pair.second[0].pObj->Animator3D())
		{
			pair.second[0].pObj->Animator3D()->ClearData();
		}
	}
}

void CCamera::render_decal()
{
	for (size_t i = 0; i < m_vecDecal.size(); ++i)
	{
		m_vecDecal[i]->render();
	}
}

void CCamera::render_blur()
{
	Ptr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"GaussianBlurMtrl");

	pMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"ColorTargetTex"));
	pMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"EmissiveTargetTex"));
	pMtrl->UpdateData();

	pMesh->render(0);
}

void CCamera::render_merge()
{
	Ptr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"LightMergeMtrl");

	pMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"ColorTargetTex"));
	pMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"DiffuseTargetTex"));
	pMtrl->SetTexParam(TEX_2, CResMgr::GetInst()->FindRes<CTexture>(L"SpecularTargetTex"));
	pMtrl->SetTexParam(TEX_3, CResMgr::GetInst()->FindRes<CTexture>(L"EmissiveTargetTex"));
	pMtrl->UpdateData();

	pMesh->render(0);
}

void CCamera::render_forward()
{
	for (auto& pair : m_mapSingleObj)
	{
		pair.second.clear();
	}

	// Deferred object render
	tInstancingData tInstData = {};

	for (auto& pair : m_mapInstGroup_F)
	{
		// �׷� ������Ʈ�� ���ų�, ���̴��� ���� ���
		if (pair.second.empty())
			continue;

		// instancing ���� ���� �̸��̰ų�
		// Animation2D ������Ʈ�ų�(��������Ʈ �ִϸ��̼� ������Ʈ)
		// Shader �� Instancing �� �������� �ʴ°��
		if (pair.second.size() <= 1
			|| pair.second[0].pObj->Animator2D()
			|| pair.second[0].pObj->GetRenderComponent()->GetMaterial(pair.second[0].iMtrlIdx)->GetShader()->GetVSInst() == nullptr)
		{
			// �ش� ��ü���� ���� ���������� ��ȯ
			for (UINT i = 0; i < pair.second.size(); ++i)
			{
				map<INT_PTR, vector<tInstObj>>::iterator iter
					= m_mapSingleObj.find((INT_PTR)pair.second[i].pObj);

				if (iter != m_mapSingleObj.end())
					iter->second.push_back(pair.second[i]);
				else
				{
					m_mapSingleObj.insert(make_pair((INT_PTR)pair.second[i].pObj, vector<tInstObj>{pair.second[i]}));
				}
			}
			continue;
		}

		CGameObject* pObj = pair.second[0].pObj;
		Ptr<CMesh> pMesh = pObj->GetRenderComponent()->GetMesh();
		Ptr<CMaterial> pMtrl = pObj->GetRenderComponent()->GetMaterial(pair.second[0].iMtrlIdx);

		// Instancing ���� Ŭ����
		CInstancingBuffer::GetInst()->Clear();

		int iRowIdx = 0;
		bool bHasAnim3D = false;
		for (UINT i = 0; i < pair.second.size(); ++i)
		{
			tInstData.matWorld = pair.second[i].pObj->Transform()->GetWorldMat();
			tInstData.matWV = tInstData.matWorld * m_matView;
			tInstData.matWVP = tInstData.matWV * m_matProj;

			if (pair.second[i].pObj->Animator3D())
			{
				pair.second[i].pObj->Animator3D()->UpdateData();
				tInstData.iRowIdx = iRowIdx++;
				CInstancingBuffer::GetInst()->AddInstancingBoneMat(pair.second[i].pObj->Animator3D()->GetFinalBoneMat());
				bHasAnim3D = true;
			}
			else
				tInstData.iRowIdx = -1;

			CInstancingBuffer::GetInst()->AddInstancingData(tInstData);
		}

		// �ν��Ͻ̿� �ʿ��� �����͸� ����(SysMem -> GPU Mem)
		CInstancingBuffer::GetInst()->SetData();

		if (bHasAnim3D)
		{
			pMtrl->SetAnim3D(true); // Animation Mesh �˸���
			pMtrl->SetBoneCount(pMesh->GetBoneCount());
		}

		pMtrl->UpdateData_Inst();
		pMesh->render_instancing(pair.second[0].iMtrlIdx);

		// ����
		if (bHasAnim3D)
		{
			pMtrl->SetAnim3D(false); // Animation Mesh �˸���
			pMtrl->SetBoneCount(0);
		}
	}

	// ���� ������
	for (auto& pair : m_mapSingleObj)
	{
		if (pair.second.empty())
			continue;

		pair.second[0].pObj->Transform()->UpdateData();

		for (auto& instObj : pair.second)
		{
			instObj.pObj->GetRenderComponent()->render(instObj.iMtrlIdx);
		}

		if (pair.second[0].pObj->Animator3D())
		{
			pair.second[0].pObj->Animator3D()->ClearData();
		}
	}
}

void CCamera::render_transparent()
{
	for (size_t i = 0; i < m_vecTransparent.size(); ++i)
	{
		m_vecTransparent[i]->render();
	}
}

void CCamera::render_postprocess()
{
	for (size_t i = 0; i < m_vecPost.size(); ++i)
	{
		CRenderMgr::GetInst()->CopyRenderTarget();
		m_vecPost[i]->render();
	}
}

void CCamera::render_ui()
{
	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->render();
	}
}

void CCamera::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fWidth, sizeof(float), 1, _File);
	fwrite(&m_fAspectRatio, sizeof(float), 1, _File);
	fwrite(&m_fScale, sizeof(float), 1, _File);
	fwrite(&m_fFar, sizeof(float), 1, _File);
	fwrite(&m_ProjType, sizeof(UINT), 1, _File);
	fwrite(&m_iLayerMask, sizeof(UINT), 1, _File);
	fwrite(&m_iCamIdx, sizeof(int), 1, _File);
	fwrite(&m_bWaterCamera, sizeof(bool), 1, _File);
}

void CCamera::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fWidth, sizeof(float), 1, _File);
	fread(&m_fAspectRatio, sizeof(float), 1, _File);
	fread(&m_fScale, sizeof(float), 1, _File);
	fread(&m_fFar, sizeof(float), 1, _File);
	fread(&m_ProjType, sizeof(UINT), 1, _File);
	fread(&m_iLayerMask, sizeof(UINT), 1, _File);
	fread(&m_iCamIdx, sizeof(int), 1, _File);
	fread(&m_bWaterCamera, sizeof(bool), 1, _File);
}
