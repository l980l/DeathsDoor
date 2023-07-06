#include "pch.h"
#include "CFrustum.h"

#include "CCamera.h"

CFrustum::CFrustum(CCamera* _pOwner)
	: m_pOwner(_pOwner)
	, m_arrFace{}
	, m_bDebugShape(false)
{
	// �������� ��ǥ
	//     4 ------ 5
	//     |        |  Far
	//   / |        |
	//	/  7 ------ 6	
	// /      /
	// 0 -- 1     /
	// |    |    / Near
	// 3 -- 2
	m_arrProj[0] = Vec3(-1.f, 1.f, 0.f);
	m_arrProj[1] = Vec3(1.f, 1.f, 0.f);
	m_arrProj[2] = Vec3(1.f, -1.f, 0.f);
	m_arrProj[3] = Vec3(-1.f, -1.f, 0.f);

	m_arrProj[4] = Vec3(-1.f, 1.f, 1.f);
	m_arrProj[5] = Vec3(1.f, 1.f, 1.f);
	m_arrProj[6] = Vec3(1.f, -1.f, 1.f);
	m_arrProj[7] = Vec3(-1.f, -1.f, 1.f);
}

CFrustum::~CFrustum()
{
}

void CFrustum::finaltick()
{
	Vec3 vWorldPos[8] = {};

	// MDC �������� ��Ƴ��� �����ǥ�� ����, ������� ������� ���� ������ǥ��� ��ȯ��ų ��
	Matrix matInv = m_pOwner->GetProjMatInv() * m_pOwner->GetViewMatInv();

	for (int i = 0; i < 8; ++i)
	{
		vWorldPos[i] = XMVector3TransformCoord(m_arrProj[i], matInv);
	}

	// 3���� ���� �̿��� �ش� ���� ���� ���� �����ϴ� �������͸� ����
	m_arrFace[FT_NEAR]  = XMPlaneFromPoints(vWorldPos[0], vWorldPos[1], vWorldPos[2]);
	m_arrFace[FT_FAR]   = XMPlaneFromPoints(vWorldPos[6], vWorldPos[5], vWorldPos[4]);
	m_arrFace[FT_LEFT]  = XMPlaneFromPoints(vWorldPos[4], vWorldPos[0], vWorldPos[7]);
	m_arrFace[FT_RIGHT] = XMPlaneFromPoints(vWorldPos[1], vWorldPos[5], vWorldPos[6]);
	m_arrFace[FT_TOP]	= XMPlaneFromPoints(vWorldPos[4], vWorldPos[5], vWorldPos[1]);
	m_arrFace[FT_BOT]	= XMPlaneFromPoints(vWorldPos[2], vWorldPos[6], vWorldPos[7]); 

	// ī�޶� �þ� Debug Render
	if (m_bDebugShape)
	{
		DrawDebugFrustum(matInv, Vec4(0.f, 1.f, 0.f, 1.f));
	}
}

bool CFrustum::FrustumCheckByPoint(Vec3 _vWorldPos)
{	
	for (int i = 0; i < FT_END; ++i)
	{
		// ������ ���� �ش� ����� �������Ϳ� ����
		Vec3 vNormal = m_arrFace[i];
		vNormal.Normalize();
		float fDot = vNormal.Dot(_vWorldPos);

		// ������ ���� �������� �ش� �������� �ִܰŸ�(D) �� ��
		// a, b, c�� ���������� xyz��� �� �� 
		// ax + by + cz + d = 0 �� �ش� ��鿡 ������ �� �����Ǵ� ����� ������
		// xyz�� WorldPos�̹Ƿ� ax+ by + cz + d�� 0���� ũ�ٸ� �ش� ��麸�� �ۿ� �ִٴ� ��
		// ���� ��� �������͸� �þ߹��� �ٱ��������� �����Ƿ� false ��ȯ
		if (fDot + m_arrFace[i].w > 0)
			return false;
	}

	return true;
}

bool CFrustum::FrustumCheckBySphere(Vec3 _vWorldPos, float _fRadius)
{
	for (int i = 0; i < FT_END; ++i)
	{
		// ������ ���� �ش� ����� �������Ϳ� ����
		Vec3 vNormal = m_arrFace[i];
		vNormal.Normalize();
		float fDot = vNormal.Dot(_vWorldPos);

		// ������ ���� �������� �ش� �������� �ִܰŸ�(D) �� ��
		// ���������� �� �ٱ����� ������ ȭ�鿡 ��ġ�� �κ��� ���� ��
		if (fDot + m_arrFace[i].w > _fRadius)
			return false;
	}

	return true;
}
