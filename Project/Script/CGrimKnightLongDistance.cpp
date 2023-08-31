#include "pch.h"
#include "CGrimKnightLongDistance.h"
#include "CLevelSaveLoadInScript.h"
#include "CGrimKnightScript.h"
#include "CGhostScript.h"
#include "CStateScript.h"
#include "CSoundScript.h"
#include <Engine/CRigidbody.h>
#include <Engine/CPhysXMgr.h>

CGrimKnightLongDistance::CGrimKnightLongDistance()
{
}

CGrimKnightLongDistance::~CGrimKnightLongDistance()
{
}

void CGrimKnightLongDistance::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Trace");
		CGrimKnightScript* pScript= GetOwner()->GetScript< CGrimKnightScript>();
		pScript->SetOnCollision(false);
	}
}

void CGrimKnightLongDistance::Enter()
{
	GetOwner()->Animator3D()->Play(7, false);
	
	CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
	Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Grim\\GrimaceBullet.ogg", 1, 0.1f);

	//Ghost prefab ����
	CGameObject* pGhost = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\Ghost.prefab", (int)LAYER::MONSTERPROJECTILE, GetOwner()->Transform()->GetWorldPos(), 5.f);
	pGhost->AddComponent(new CGhostScript);
	pGhost->AddComponent(new CStateScript);
	pGhost->AddComponent(new CRigidbody);
	pGhost->MeshRender()->SetDynamicShadow(true);
	pGhost->MeshRender()->SetFrustumCheck(false);
	CPhysXMgr::GetInst()->CreateSphere(GetOwner()->Transform()->GetWorldPos(), 30.f, pGhost);
}

void CGrimKnightLongDistance::Exit()
{
}
