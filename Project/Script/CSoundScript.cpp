#include "pch.h"
#include "CSoundScript.h"

void CSoundScript::begin()
{
	pSound = CResMgr::GetInst()->FindRes<CSound>(L"Sound\\BGM\\DeathsDoorPiano.mp3");
	idx = pSound->PlayBGM(0, 0.5f);
	
}

void CSoundScript::tick()
{
	pSound->SetVolume(0.7f, idx);
}

void CSoundScript::BeginOverlap(CCollider3D* _Other)
{
}

CSoundScript::CSoundScript()		:
	CScript(SCRIPT_TYPE::SOUNDSCRIPT)
{
}

CSoundScript::~CSoundScript()
{
}
