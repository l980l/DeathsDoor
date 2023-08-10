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
	Vec3 CurPos = GetOwner()->Transform()->GetWorldPos();

	Vec3 vDir = GetOwner()->Transform()->GetXZDir();
	Vec3 vSpawnPos = Vec3(CurPos.x, CurPos.y + 100.f, CurPos.z) + vDir * 100.f;

	CGameObject* pGasGrenade = CLevelSaveLoadInScript::SpawnandReturnPrefab(L"prefab\\GasGrenade.prefab", (int)LAYER::MONSTERPROJECTILE, vSpawnPos);
	CPhysXMgr::GetInst()->SetRigidPos(pGasGrenade->Rigidbody()->GetRigidbody(), vSpawnPos);

	// 45도 각도로 날릴때 가장 멀리 나간다고 가정. 
	Vec3 Dir = GetOwner()->GetScript<CBazookaScript>()->GetMonsterToPlayerDir();
	float xzDir = sqrtf(Dir.x * Dir.x + Dir.z * Dir.z);
	Dir.y = (GetOwner()->GetScript<CBazookaScript>()->GetPlayerDistance() / GetOwner()->GetScript<CBazookaScript>()->GetAttackRange())* xzDir;
	Dir.Normalize();
	pGasGrenade->GetScript<CBazookaGasGrenadeScript>()->SetShotDir(Dir);
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
