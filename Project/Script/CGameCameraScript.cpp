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
	, m_vDistance(0.f, 2000.f, 2000.f)
	, m_vOffset{}
	, m_fAccTime(0.f)
	, m_fMaxTime(0.f)
	, m_fRange(0.f)
	, m_fShakeSpeed(0.f)
	, m_fShakeDir(0.f)
	, m_bCamShake(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fMoveTime, "MoveTime");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fPrevMoveTime, "PrevMoveTime");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fDiffer, "Differ");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fTargetScale, "TargetScale");
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fPrevScale, "PrevScale");
	AddScriptParam(SCRIPT_PARAM::VEC3, &m_vDistance, "Distance");
}

CGameCameraScript::~CGameCameraScript()
{
}

void CGameCameraScript::begin()
{
	if (nullptr == m_pPlayer)
		m_pPlayer = CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player");
	Transform()->SetRelativeRot(XM_PI / 4.f, 0.f, 0.f);
	Camera()->SetScale(0.6f);
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
		CurPlayerPos.x += m_vDistance.x + m_vOffset.x;
		CurPlayerPos.y += m_vDistance.y;
		CurPlayerPos.z -= m_vDistance.z + m_vOffset.y;
		Transform()->SetRelativePos(CurPlayerPos);
	}

	ShackCamera();
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

void CGameCameraScript::CameraShake(float _fRange, float _fShackSpeed, float _fTerm)
{
	m_fAccTime = 0.f;
	m_fMaxTime = _fTerm;
	m_fRange = _fRange;
	m_fShakeSpeed = _fShackSpeed;
	m_fShakeDir = 1.f;
	m_bCamShake = true;
}

void CGameCameraScript::ShackCamera()
{
	if (!m_bCamShake)
		return;

	m_fAccTime += DT;

	if (m_fMaxTime <= m_fAccTime)
	{
		m_bCamShake = false;
		m_vOffset = Vec2(0.f, 0.f);
	}

	m_vOffset.x += DT * m_fShakeSpeed * m_fShakeDir;
	m_fShakeSpeed -= m_fShakeSpeed * m_fMaxTime * DT;
	if (m_fRange < fabsf(m_vOffset.x))
	{
		m_vOffset.x = m_fRange * m_fShakeDir;
		m_fShakeDir *= -1;
	}
}
