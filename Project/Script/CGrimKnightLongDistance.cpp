#include "pch.h"
#include "CGrimKnightLongDistance.h"
#include "CLevelSaveLoadInScript.h"
#include "CGrimKnightScript.h"
#include "CGhostScript.h"
#include "CStateScript.h"
#include <Engine/CRigidbody.h>
#include <Engine/CPhysXMgr.h>

void CGrimKnightLongDistance::tick()
{
	if (GetOwner()->Animator3D()->IsFinish())
	{
		ChangeState(L"Trace");
		CGrimKnightScript* gScript = GetOwner()->GetScript< CGrimKnightScript>();
		gScript->SetOnCollision(false);
	}
}

void CGrimKnightLongDistance::Enter()
{
	Stat status = GetOwnerScript()->GetStat();
	GetOwner()->Animator3D()->Play(7, false);
	
	//Ghost prefab »ý¼º
	CLevelSaveLoadInScript script;
	CGameObject* pGhost = script.SpawnandReturnPrefab(L"prefab\\Ghost.prefab", 5, GetOwner()->Transform()->GetWorldPos(), 5.f);
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

void CGrimKnightLongDistance::BeginOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::OnOverlap(CCollider2D* _Other)
{
}

void CGrimKnightLongDistance::EndOverlap(CCollider2D* _Other)
{
}

CGrimKnightLongDistance::CGrimKnightLongDistance()
{
}

CGrimKnightLongDistance::~CGrimKnightLongDistance()
{
}
