#include "pch.h"
#include "CBazzokaLongDistance.h"
#include "CBazookaScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CBazookaGasGrenadeScript.h"
#include <Engine/CPhysXMgr.h>

void CBazzokaLongDistance::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);

	// 가스탄 발사.
	CGameObject* pGasGrenade = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasGrenade.prefab", 6, GetOwner()->Transform()->GetWorldPos());
	CPhysXMgr::GetInst()->SetRigidPos(pGasGrenade->Rigidbody()->GetRigidbody(), GetOwner()->Transform()->GetWorldPos());

	pGasGrenade->GetScript<CBazookaGasGrenadeScript>()->SetShotDir(GetOwner()->GetScript<CBazookaScript>()->GetMonsterToPlayerDir());
}

void CBazzokaLongDistance::tick()
{
	// 애니메이션이 끝나면 Move로 다시 변경.
	if (GetOwner()->Animator3D()->IsFinish())
		ChangeState(L"Move");
}

void CBazzokaLongDistance::Exit()
{
}

CBazzokaLongDistance::CBazzokaLongDistance()
{
}

CBazzokaLongDistance::~CBazzokaLongDistance()
{
}
