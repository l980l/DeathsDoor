#include "pch.h"

#include "CEventMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CRenderMgr.h"
#include "ptr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CDevice.h"
#include "CRigidbody.h"





void SpawnGameObject(CGameObject* _NewObject, Vec3 _vWorldPos, int _LayerIdx)
{
	_NewObject->Transform()->SetRelativePos(_vWorldPos);

	tEvent evn = {};

	evn.Type = EVENT_TYPE::CREATE_OBJECT;
	evn.wParam = (DWORD_PTR)_NewObject;
	evn.lParam = _LayerIdx;

	CEventMgr::GetInst()->AddEvent(evn);
}

void SpawnGameObject(CGameObject* _NewObject, Vec3 _vWorldPos, const wstring& _LayerName)
{
	_NewObject->Transform()->SetRelativePos(_vWorldPos);

	tEvent evn = {};

	evn.Type = EVENT_TYPE::CREATE_OBJECT;
	evn.wParam = (DWORD_PTR)_NewObject;
	evn.lParam = CLevelMgr::GetInst()->GetCurLevel()->FindLayerByName(_LayerName)->GetLayerIndex();

	CEventMgr::GetInst()->AddEvent(evn);
}

void DestroyObject(CGameObject* _DeletObject)
{
	if (_DeletObject->IsDead())
		return;

	tEvent evn = {};

	evn.Type = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)_DeletObject;
	
	CEventMgr::GetInst()->AddEvent(evn);
}



void DrawDebugRect(Vec3 _vWorldPos, Vec2 _vWorldScale, Vec4 _vColor, Vec3 _vRotation, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = XMMatrixIdentity();
	info.eShape = SHAPE_TYPE::RECT;
	info.fMaxTime = _fTime;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_vWorldScale.x, _vWorldScale.y, 1.f);
	info.vWorldRotation = _vRotation;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugRect(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::RECT;
	info.fMaxTime = _fTime;	
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugCircle(Vec3 _vWorldPos, float _fRadius, Vec4 _vColor, Vec3 _vRotation, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = XMMatrixIdentity();
	info.eShape = SHAPE_TYPE::CIRCLE;
	info.fMaxTime = _fTime;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_fRadius, _fRadius, 1.f);
	info.vWorldRotation = _vRotation;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugCircle(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::CIRCLE;
	info.fMaxTime = _fTime;	
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugCube(Vec3 _vWorldPos, Vec2 _vWorldScale, Vec4 _vColor, Vec3 _vRotation, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = XMMatrixIdentity();
	info.eShape = SHAPE_TYPE::CUBE;
	info.fMaxTime = _fTime;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_vWorldScale.x, _vWorldScale.y, 1.f);
	info.vWorldRotation = _vRotation;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugCube(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::CUBE;
	info.fMaxTime = _fTime;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugSphere(Vec3 _vWorldPos, float _fRadius, Vec4 _vColor, Vec3 _vRotation, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = XMMatrixIdentity();
	info.eShape = SHAPE_TYPE::SPHERE;
	info.fMaxTime = _fTime;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_fRadius, _fRadius, _fRadius);
	info.vWorldRotation = _vRotation;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugSphere(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::SPHERE;
	info.fMaxTime = _fTime;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}


const char* ToString(RES_TYPE type)
{
	return RES_TYPE_STR[(UINT)type];
}

const wchar_t* ToWString(RES_TYPE type)
{
	return RES_TYPE_WSTR[(UINT)type];
}


const char* ToString(COMPONENT_TYPE type)
{
	return COMPONENT_TYPE_STR[(UINT)type];
}

wstring GetRelativePath(const wstring& _strBase, const wstring& _strPath)
{
	wstring strRelativePath;
	if (-1 == _strPath.find(_strBase))
	{
		return strRelativePath;
	}

	strRelativePath = _strPath.substr(_strBase.length(), _strPath.length());
	return strRelativePath;
}



Matrix GetMatrixFromFbxMatrix(FbxAMatrix& _mat)
{
	Matrix mat;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat.m[i][j] = (float)_mat.Get(i, j);
		}
	}
	return mat;
}


void SaveWString(const wstring& _str, FILE* _File)
{	
	UINT iLen = (UINT)_str.length();
	fwrite(&iLen, sizeof(UINT), 1, _File);
	fwrite(_str.c_str(), sizeof(wchar_t), _str.length(), _File);
}

void LoadWString(wstring& _str, FILE* _File)
{
	wchar_t szBuffer[256] = {};

	UINT iLen = 0;
	fread(&iLen, sizeof(UINT), 1, _File);
	fread(szBuffer, sizeof(wchar_t), iLen, _File);	

	_str = szBuffer;
}

void SaveResRef(Ptr<CRes> _Res, FILE* _File)
{
	int i = 0;
	if (nullptr == _Res)
	{
		fwrite(&i, sizeof(int), 1, _File);
	}
	else
	{
		i = 1;
		fwrite(&i, sizeof(int), 1, _File);
		SaveWString(_Res->GetKey(), _File);
		SaveWString(_Res->GetRelativePath(), _File);
	}
}

const wchar_t* ToWString(COMPONENT_TYPE type)
{
	return COMPONENT_TYPE_WSTR[(UINT)type];
}

void DrawDebugFrustum(const Matrix& _matWorld, Vec4 _vColor, float _fTime)
{
	tDebugShapeInfo info = {};

	info.matWorld = _matWorld;
	info.eShape = SHAPE_TYPE::FRUSTUM;
	info.fMaxTime = _fTime;
	info.vColor = _vColor;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

bool closeEnough(const float& a, const float& b
	, const float& epsilon = std::numeric_limits<float>::epsilon())
{
	return (epsilon > std::abs(a - b));
}

Vec3 DecomposeRotMat(const Matrix& _matRot)
{
	// _mat �� ���� �� �ٽ� ��� �����	
	Vec4 vMat[4];

	vMat[0] = Vec4(_matRot._11, _matRot._12, _matRot._13, _matRot._14);
	vMat[1] = Vec4(_matRot._21, _matRot._22, _matRot._23, _matRot._24);
	vMat[2] = Vec4(_matRot._31, _matRot._32, _matRot._33, _matRot._34);
	vMat[3] = Vec4(_matRot._41, _matRot._42, _matRot._43, _matRot._44);

	/*XMStoreFloat4(&vMat[0], _matRot._11);
	XMStoreFloat4(&vMat[1], _matRot.r[1]);
	XMStoreFloat4(&vMat[2], _matRot.r[2]);
	XMStoreFloat4(&vMat[3], _matRot.r[3]);*/

	Vec3 vNewRot;
	if (closeEnough(vMat[0].z, -1.0f)) {
		float x = 0; //gimbal lock, value of x doesn't matter
		float y = XM_PI / 2;
		float z = x + atan2f(vMat[1].x, vMat[2].x);
		vNewRot = Vec3{ x, y, z };
	}
	else if (closeEnough(vMat[0].z, 1.0f)) {
		float x = 0;
		float y = -XM_PI / 2;
		float z = -x + atan2f(-vMat[1].x, -vMat[2].x);
		vNewRot = Vec3{ x, y, z };
	}
	else { //two solutions exist
		float y1 = -asinf(vMat[0].z);
		float y2 = XM_PI - y1;

		float x1 = atan2f(vMat[1].z / cosf(y1), vMat[2].z / cosf(y1));
		float x2 = atan2f(vMat[1].z / cosf(y2), vMat[2].z / cosf(y2));

		float z1 = atan2f(vMat[0].y / cosf(y1), vMat[0].x / cosf(y1));
		float z2 = atan2f(vMat[0].y / cosf(y2), vMat[0].x / cosf(y2));

		//choose one solution to return
		//for example the "shortest" rotation
		if ((std::abs(x1) + std::abs(y1) + std::abs(z1)) <= (std::abs(x2) + std::abs(y2) + std::abs(z2)))
		{
			vNewRot = Vec3{ x1, y1, z1 };
		}
		else {
			vNewRot = Vec3{ x2, y2, z2 };
		}
	}
	return vNewRot;
}

float GetDistance(Vec3 _Vec1, Vec3 _Vec2)
{
	float a, b, c;
	a = _Vec1.x - _Vec2.x;
	b = _Vec1.y - _Vec2.y;
	c = _Vec1.z - _Vec2.z;

	return sqrt(a*a + b*b + c*c);
}

float GetDir(Vec3 _vStart, Vec3 _vTarget, bool _degree)
{
	// �Ʒ����� �������� CurPos���� TargetPos�� �ٶ󺸴� angle ��ȯ
	Vec3 CurPos = _vStart;
	Vec2 vDefault = Vec2(0.f, -1.f);
	Vec3 TargetPos = _vTarget;
	Vec2 vDir = Vec2(TargetPos.x - CurPos.x, TargetPos.z - CurPos.z);
	vDir.Normalize();
	float angle = (float)acos(vDir.Dot(vDefault));

	if (vDir.x > 0.f)
		angle = XM_2PI - angle;

	if (angle > XM_PI)
		angle = angle - XM_2PI;
	else if (angle < -XM_PI)
		angle = angle + XM_2PI;

	if(_degree)
		angle *= (180.f / XM_PI);

	return angle;
}

float GetSmoothDir(CGameObject* _pStartObject, CGameObject* _pTargetObj, float _degree)
{
	Vec3 vOwnerPos = _pStartObject->Transform()->GetWorldPos();
	Vec3 vTargetPos = _pTargetObj->Transform()->GetWorldPos();
	Vec3 vPrevDir = _pStartObject->Transform()->GetRelativeRot();
	float PrevDir = vPrevDir.y;
	float Rot = GetDir(vOwnerPos, vTargetPos);
	float Diff = Rot - PrevDir;

	if (Diff > XM_PI)
	{
		Diff = -(XM_2PI - Rot + PrevDir) * (180.f / XM_PI);
	}
	else if (Diff < -XM_PI)
	{
		Diff = (XM_2PI - PrevDir + Rot) * (180.f / XM_PI);
	}
	else
		Diff = (Rot - PrevDir) * (180.f / XM_PI);

	if (abs(Diff) > 0.1f)
	{
		bool bnegative = false;
		if (Diff < 0)
			bnegative = true;

		Diff = bnegative ? -_degree / 180.f * XM_PI : _degree / 180.f * XM_PI;
	}

	return PrevDir + Diff;
}

void AddForceCentertoMouseDir(CGameObject* _pProjectile)
{
	Vec2 vCursorPos = CKeyMgr::GetInst()->GetMousePos();
	vCursorPos -= CDevice::GetInst()->GetRenderResolution() / 2.f;
	Vec3 vMousePos = Vec3(vCursorPos.x, 0.f, -vCursorPos.y);
	float fRot = GetDir(Vec3(0.f, 0.f, 0.f), vMousePos);
	_pProjectile->Transform()->SetRelativeRot(XM_PI * 1.5f, fRot, 0.f);

	Vec3 AttackDir = Vec3(0.f, 0.f, 0.f);
	AttackDir = Vec3(0.f, 0.f, 0.f) - vMousePos;
	AttackDir.Normalize();
	AttackDir *= 500.f;
	AttackDir.y = 0.f;
	_pProjectile->Rigidbody()->SetVelocity(-AttackDir);
}

int GetSizeofFormat(DXGI_FORMAT _eFormat)
{
	int iRetByte = 0;
	switch (_eFormat)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		iRetByte = 128;
		break;

	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
		iRetByte = 96;
		break;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G32_FLOAT:
	case DXGI_FORMAT_R32G32_UINT:
	case DXGI_FORMAT_R32G32_SINT:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		iRetByte = 64;
		break;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R32_FLOAT:
	case DXGI_FORMAT_R32_UINT:
	case DXGI_FORMAT_R32_SINT:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		iRetByte = 32;
		break;
	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		iRetByte = 16;
		break;
	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
		iRetByte = 8;
		break;
		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
		iRetByte = 128;
		break;
		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_R1_UNORM:
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
		iRetByte = 64;
		break;
		// Compressed format; http://msdn2.microsoft.com/en-us/library/bb694531(VS.85).aspx
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		iRetByte = 32;
		break;
		// These are compressed, but bit-size information is unclear.
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		iRetByte = 32;
		break;
	case DXGI_FORMAT_UNKNOWN:
	default:
		return -1;
	}

	return iRetByte / 8;
}