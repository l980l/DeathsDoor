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
	Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();

	Vec3 vDir = GetOwner()->Transform()->GetXZDir();
	Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 100.f, CurPos.z) + vDir * 100.f;

	CGameObject* pGasGrenade = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasGrenade.prefab", (int)LAYER::MONSTERPROJECTILE, vSpawnPos);
	CPhysXMgr::GetInst()->SetRigidPos(pGasGrenade->Rigidbody()->GetRigidbody(), vSpawnPos);

	// 45�� ������ ������ ���� �ָ� �����ٰ� ����. 
	Vec3 Dir = GetOwner()->GetScript<CBazookaScript>()->GetMonsterToPlayerDir();
	float xzDir = sqrtf(Dir.x * Dir.x + Dir.z * Dir.z);
	Dir.y = (GetOwner()->GetScript<CBazookaScript>()->GetPlayerDistance() / GetOwner()->GetScript<CBazookaScript>()->GetAttackRange())* xzDir;
	Dir.Normalize();
	pGasGrenade->GetScript<CBazookaGasGrenadeScript>()->SetShotDir(Dir);
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
