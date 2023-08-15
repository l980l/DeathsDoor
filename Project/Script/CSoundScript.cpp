#include "pch.h"
#include "CSoundScript.h"

CSoundScript::CSoundScript() :
	CScript(SCRIPT_TYPE::SOUNDSCRIPT)
	, m_pSound(nullptr)
	, m_fVolume(0.5f)
	, m_iIdx(0)
{
}

CSoundScript::~CSoundScript()
{
	m_pSound = nullptr;
}
void CSoundScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}
	MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\VolumeUI.png", L"texture\\HUD\\VolumeUI.png", 0));
	//pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BGM\\DeathsDoorPiano.mp3");
	//idx = pSound->PlayBGM(0, 0.5f);
	
}

void CSoundScript::tick()
{
	if (KEY_TAP(KEY::LEFT))
	{
		m_fVolume -= 0.1f;
		m_pSound->SetVolume(m_fVolume, 31);
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		m_fVolume += 0.1f;
		m_pSound->SetVolume(m_fVolume, 31);
	}
	if (KEY_TAP(KEY::Q))
	{
		GetOwner()->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	}
}

void CSoundScript::BeginOverlap(CCollider3D* _Other)
{
}

Ptr<CSound> CSoundScript::AddSound(wstring _filename, int _repeat, float _volume, bool _bOverlap)
{
	m_pSound = CResMgr::GetInst()->FindRes<CSound>(_filename);
	m_pSound->Play(_repeat, _volume, -1, _bOverlap);
	return m_pSound;
}

