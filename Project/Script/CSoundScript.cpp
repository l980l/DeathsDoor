#include "pch.h"
#include "CSoundScript.h"

void CSoundScript::begin()
{
	// 동적 재질 생성.
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}
	//pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BGM\\DeathsDoorPiano.mp3");
	//idx = pSound->PlayBGM(0, 0.5f);
	
}

void CSoundScript::tick()
{
	if (KEY_TAP(KEY::LEFT))
	{
		m_volume -= 0.1f;
		pSound->SetVolume(m_volume, 31);
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		m_volume += 0.1f;
		pSound->SetVolume(m_volume , 31);
	}
	if (KEY_TAP(KEY::Q))
	{
		GetOwner()->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	}
}

void CSoundScript::BeginOverlap(CCollider3D* _Other)
{
}

Ptr<CSound> CSoundScript::AddSound(wstring _filename, int _repeat, float _volume)
{
	pSound = CResMgr::GetInst()->FindRes<CSound>(_filename);
	pSound->Play(_repeat, _volume);
	return pSound;
}

CSoundScript::CSoundScript()		:
	CScript(SCRIPT_TYPE::SOUNDSCRIPT),
	m_volume(0.5f)
{
}

CSoundScript::~CSoundScript()
{
}
