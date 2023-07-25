#include "pch.h"
#include "CGameCameraScript.h"

CGameCameraScript::CGameCameraScript()
	: CScript((UINT)SCRIPT_TYPE::GAMECAMERASCRIPT)
	, m_pPlayer(nullptr)
    , m_fMoveTime(0.f)
    , m_fPrevMoveTime(0.f)
    , m_fDiffer(0.f)
    , m_fTargetScale(0.f)
    , m_fPrevScale(0.f)
{
}

CGameCameraScript::~CGameCameraScript()
{
}

void CGameCameraScript::begin()
{
	if (nullptr == m_pPlayer)
		m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	Transform()->SetRelativeRot(XM_PI / 4.f, 0.f, 0.f);
	Camera()->SetScale(0.3f);
}

void CGameCameraScript::tick()
{
	if (m_fMoveTime != 0.f)
	{
		m_fMoveTime -= DT;
		float CurScale = Camera()->GetScale();
		CurScale + (m_fDiffer * DT);
		Camera()->SetScale(CurScale);

		if (m_fMoveTime <= 0.f && m_fPrevMoveTime != 0.f)
		{
			m_fMoveTime = m_fPrevMoveTime;
			m_fPrevMoveTime = 0.f;
			m_fDiffer = m_fPrevScale - CurScale / m_fMoveTime;
		}
	}
	
	else
	{
		Vec3 CurPlayerPos = m_pPlayer->Transform()->GetWorldPos();
		CurPlayerPos.y += 1000.f;
		CurPlayerPos.z -= 1000.f;
		Transform()->SetRelativePos(CurPlayerPos);
	}
}

void CGameCameraScript::BeginOverlap(CCollider3D* _Other)
{
}

void CGameCameraScript::EndOverlap(CCollider3D* _Other)
{
}

void CGameCameraScript::SetMoveCamera(float _vTargetScale, float _fTime)
{
	m_fPrevScale = Camera()->GetScale();
	m_fDiffer = Camera()->GetScale() - _vTargetScale;
	m_fMoveTime = _fTime;
	m_fPrevMoveTime = _fTime;
	m_fDiffer /= m_fMoveTime;
}
