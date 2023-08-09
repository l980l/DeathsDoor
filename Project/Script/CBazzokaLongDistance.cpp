#include "pch.h"
#include "CBazzokaLongDistance.h"
#include "CBazookaScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CBazookaGasGrenadeScript.h"
#include <Engine/CPhysXMgr.h>

void CBazzokaLongDistance::Enter()
{
	GetOwner()->Animator3D()->Play(1, false);

	// ����ź �߻�.
	CGameObject* pGasGrenade = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasGrenade.prefab", 6, GetOwner()->Transform()->GetWorldPos());
	CPhysXMgr::GetInst()->SetRigidPos(pGasGrenade->Rigidbody()->GetRigidbody(), GetOwner()->Transform()->GetWorldPos());

	pGasGrenade->GetScript<CBazookaGasGrenadeScript>()->SetShotDir(GetOwner()->GetScript<CBazookaScript>()->GetMonsterToPlayerDir());
}

void CBazzokaLongDistance::tick()
{
	// �ִϸ��̼��� ������ Move�� �ٽ� ����.
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
