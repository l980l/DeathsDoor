#include "pch.h"
#include "CBazzokaMelee.h"
#include "CBazookaScript.h"
#include "CSoundScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CGameCameraScript.h"
#include <Engine/CRenderMgr.h>

void CBazzokaMelee::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);
}

void CBazzokaMelee::tick()
{
	// �ִϸ��̼��� ������ Move�� �ٽ� ����.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Move");
}

void CBazzokaMelee::Exit()
{
	// Camera Shake
	CRenderMgr::GetInst()->GetMainCam()->GetOwner()->GetScript<CGameCameraScript>()->CameraShake(10.f, 800.f, 0.1f);

	// ���� �浹ü ������
	CGameObject* MonsterAtack = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\MonsterAttack.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 0.1f);

	MonsterAtack->Collider3D()->SetOffsetPos(GetOwner()->Collider3D()->GetOffsetPos());
	MonsterAtack->Collider3D()->SetOffsetScale(GetOwner()->Collider3D()->GetOffsetScale());

	// Sound
	CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\PlagueBoySlam1.ogg", 1, 0.1f);
}

CBazzokaMelee::CBazzokaMelee()
{
}

CBazzokaMelee::~CBazzokaMelee()
{
}
