#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider2D.h"
#include "CCollider3D.h"

CCollisionMgr::CCollisionMgr()
    : m_matrix{}
{

}


CCollisionMgr::~CCollisionMgr()
{

}



void CCollisionMgr::tick()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)))
				continue;

			// iRow ���̾�� iCol ���̾�� ���� �浹�˻縦 �����Ѵ�.
			CollisionBtwLayer(pLevel->GetLayer(iRow), pLevel->GetLayer(iCol));
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(CLayer* _Left, CLayer* _Right)
{
	const vector<CGameObject*>& vecLeft = _Left->GetObjects();
	const vector<CGameObject*>& vecRight = _Right->GetObjects();

	if (_Left == _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);				
			}
		}
	}
	else
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwObject(vecLeft[i], vecRight[j]);				
			}
		}
	}
}

void CCollisionMgr::CollisionBtwObject(CGameObject* _LeftObject, CGameObject* _RightObject)
{
	if (!(_LeftObject->Collider2D() && _RightObject->Collider2D())
		&& !(_LeftObject->Collider3D() && _RightObject->Collider3D()))
		return;

	// �浹ü ID ����
	CollisionID id = {};

	if (_LeftObject->Collider2D() && _RightObject->Collider2D())
	{
		id.LeftID = _LeftObject->Collider2D()->GetID();
		id.RightID = _RightObject->Collider2D()->GetID();
	}
	else
	{
		id.LeftID = _LeftObject->Collider3D()->GetID();
		id.RightID = _RightObject->Collider3D()->GetID();
	}
	
	// ID �˻�
	map<UINT_PTR, bool>::iterator iter = m_mapColID.find(id.id);
	if (iter == m_mapColID.end())
	{
		m_mapColID.insert(make_pair(id.id, false));
		iter = m_mapColID.find(id.id);
	}

	// �� �� �ϳ��� ���� ���� ���¶��(Dead ����)
	bool bDead = false;
	if (_LeftObject->IsDead() || _RightObject->IsDead())
	{
		bDead = true;
	}

	if(_LeftObject->Collider2D() && _RightObject->Collider2D())
	{
		// �� �浹ü�� ���� �浹 ������ Ȯ��
		if (CollisionBtw2DCollider(_LeftObject->Collider2D(), _RightObject->Collider2D()))
		{
			// ������ �浹�� ���� �ְ�, ���� �ϳ� �̻��� ���� �����̶��
			if (bDead && iter->second)
			{
				_LeftObject->Collider2D()->EndOverlap(_RightObject->Collider2D());
					_RightObject->Collider2D()->EndOverlap(_LeftObject->Collider2D());
			}
			else if (iter->second)
			{
				// ��� �浹 ��
				_LeftObject->Collider2D()->OnOverlap(_RightObject->Collider2D());
				_RightObject->Collider2D()->OnOverlap(_LeftObject->Collider2D());
			}
			else
			{
				// �̹� �����ӿ� �浹
				if (!bDead) // ���� �ϳ��� Dead ���¸� �浹�� �����Ѵ�.
				{
					_LeftObject->Collider2D()->BeginOverlap(_RightObject->Collider2D());
					_RightObject->Collider2D()->BeginOverlap(_LeftObject->Collider2D());
					iter->second = true;
				}
			}
		}
		else
		{
			// �浹 ����
			if (iter->second)
			{
				_LeftObject->Collider2D()->EndOverlap(_RightObject->Collider2D());
				_RightObject->Collider2D()->EndOverlap(_LeftObject->Collider2D());
				iter->second = false;
			}
		}
	}
	else
	{
		// �� �浹ü�� ���� �浹 ������ Ȯ��
		if (CollisionBtw3DCollider(_LeftObject->Collider3D(), _RightObject->Collider3D()))
		{
			// ������ �浹�� ���� �ְ�, ���� �ϳ� �̻��� ���� �����̶��
			if (bDead && iter->second)
			{
				_LeftObject->Collider3D()->EndOverlap(_RightObject->Collider3D());
				_RightObject->Collider3D()->EndOverlap(_LeftObject->Collider3D());
			}
			else if (iter->second)
			{
				// ��� �浹 ��
				_LeftObject->Collider3D()->OnOverlap(_RightObject->Collider3D());
				_RightObject->Collider3D()->OnOverlap(_LeftObject->Collider3D());
			}
			else
			{
				// �̹� �����ӿ� �浹
				if (!bDead) // ���� �ϳ��� Dead ���¸� �浹�� �����Ѵ�.
				{
					_LeftObject->Collider3D()->BeginOverlap(_RightObject->Collider3D());
					_RightObject->Collider3D()->BeginOverlap(_LeftObject->Collider3D());
					iter->second = true;
				}
			}
		}
		else
		{
			// �浹 ����
			if (iter->second)
			{
				_LeftObject->Collider3D()->EndOverlap(_RightObject->Collider3D());
				_RightObject->Collider3D()->EndOverlap(_LeftObject->Collider3D());
				iter->second = false;
			}
		}
	}


}

// �� �浹ü�� �浹 �˻� ����
bool CCollisionMgr::CollisionBtw2DCollider(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	// 0 -- 1
	// |    |
	// 3 -- 2
	Vec3 arrLocal[4] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f),
	};

	// �� �浹ü�� �� ǥ�� ���� 2���� ����
	Vec3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrLocal[1], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
	arrProj[1] = XMVector3TransformCoord(arrLocal[3], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
	
	arrProj[2] = XMVector3TransformCoord(arrLocal[1], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
	arrProj[3] = XMVector3TransformCoord(arrLocal[3], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
	
	// �� �浹ü�� �߽����� ����
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());
	

	// �и��� �׽�Ʈ
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize();

		// 4���� ǥ����͸� ������ ���������� ������Ų �Ÿ��� ���� / 2
		float fProjDist = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			fProjDist += fabsf(arrProj[j].Dot(vProj));
		}
		fProjDist /= 2.f;

		float fCenter = fabsf(vCenter.Dot(vProj));

		if (fProjDist < fCenter)
			return false;
	}


    return true;
}

bool CCollisionMgr::CollisionBtw3DCollider(CCollider3D* _pLeft, CCollider3D* _pRight)
{
	if(_pLeft->GetCollider3DType() == COLLIDER3D_TYPE::CUBE 
		|| _pRight->GetCollider3DType() == COLLIDER3D_TYPE::CUBE)
	{
		Vec3 arrLocal[8] =
		{
			Vec3(-0.5f, 0.5f, -0.5f),
			Vec3(0.5f, 0.5f, -0.5f),
			Vec3(0.5f, -0.5f, -0.5f),
			Vec3(-0.5f, -0.5f, -0.5f),
			Vec3(-0.5f, 0.5f, 0.5f),
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.5f, -0.5f, 0.5f),
			Vec3(-0.5f, -0.5f, 0.5f),
		};

		if(_pLeft->GetCollider3DType() == _pRight->GetCollider3DType())
		{			
			// �� �浹ü�� �� �� ǥ�麤�� 3���� ����
			Vec3 arrProj[6] = {};

			arrProj[0] = XMVector3TransformCoord(arrLocal[1], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
			arrProj[1] = XMVector3TransformCoord(arrLocal[3], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
			arrProj[2] = XMVector3TransformCoord(arrLocal[4], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());

			arrProj[3] = XMVector3TransformCoord(arrLocal[1], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
			arrProj[4] = XMVector3TransformCoord(arrLocal[3], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());
			arrProj[5] = XMVector3TransformCoord(arrLocal[4], _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pRight->GetColliderWorldMat());

			// �� �浹ü�� �߽����� ����
			Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());


			// �и��� �׽�Ʈ
			for (int i = 0; i < 6; ++i)
			{
				Vec3 vProj = arrProj[i];
				vProj.Normalize();

				// 4���� ǥ����͸� ������ ���������� ������Ų �Ÿ��� ���� / 2
				float fProjDist = 0.f;
				for (int j = 0; j < 6; ++j)
				{
					fProjDist += fabsf(arrProj[j].Dot(vProj));
				}
				fProjDist /= 2.f;

				float fCenter = fabsf(vCenter.Dot(vProj));

				if (fProjDist < fCenter)
					return false;
			}
		}
		else
		{
			Vec3 arrProj[3] = {};

			arrProj[0] = XMVector3TransformCoord(arrLocal[1], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
			arrProj[1] = XMVector3TransformCoord(arrLocal[3], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());
			arrProj[2] = XMVector3TransformCoord(arrLocal[4], _pLeft->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], _pLeft->GetColliderWorldMat());

			// �� �浹ü�� �߽����� ����
			Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());

			// �и��� �׽�Ʈ
			for (int i = 0; i < 3; ++i)
			{
				Vec3 vProj = arrProj[i];
				vProj.Normalize();

				// 4���� ǥ����͸� ������ ���������� ������Ų �Ÿ��� ���� / 2
				float fProjDist = 0.f;
				for (int j = 0; j < 3; ++j)
				{
					fProjDist += fabsf(arrProj[j].Dot(vProj));
				}

				float fCenter = fabsf(vCenter.Dot(vProj));

				if (fProjDist < fCenter)
					return false;
			}
		}
	}
	else
	{
		// �� �浹ü�� �߽����� ����
		Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pRight->GetColliderWorldMat()) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _pLeft->GetColliderWorldMat());
		// �� ��ü�� x�� Scale�� ������ Radius�� ���
		float fRadius = (_pLeft->GetColliderWorldMat()._11 + _pRight->GetColliderWorldMat()._11) / 2.f;

		if (vCenter.Length() > fRadius)
			return false;		
	}


	return true;
}



void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::LayerCheck(const wstring& _strLeftLayer, const wstring& _strRightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	CLayer* pLeft = pCurLevel->FindLayerByName(_strLeftLayer);
	CLayer* pRight = pCurLevel->FindLayerByName(_strRightLayer);

	LayerCheck(pLeft->GetLayerIndex(), pRight->GetLayerIndex());
}