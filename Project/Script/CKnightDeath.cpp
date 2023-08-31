#include "pch.h"
#include "CKnightDeath.h"
#include "CKnightScript.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CSoundScript.h"
#include "CLevelChangeDoorScript.h"

CKnightDeath::CKnightDeath() :
    m_bStartPaperBurn(false),
    m_fPaperBurnTime(0.f)
{
}

CKnightDeath::~CKnightDeath()
{
}

void CKnightDeath::Enter()
{
    GetOwner()->Animator3D()->Play(3, false);
    CSoundScript* pSoundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
    Ptr<CSound> pSound = pSoundscript->AddSound(L"Sound\\Monster\\Knight\\KnightDeath.ogg", 1, 0.2f);
}

void CKnightDeath::tick()
{
    // �ִϸ��̼��� ���� ��� ��� Paperburn ȿ�� �ֱ�.
    if (GetOwner()->Animator3D()->IsFinish())
    {
        GetOwner()->GetScript<CKnightScript>()->SetPaperBurnEffect(true);
        m_bStartPaperBurn = true;
    }

    if (m_bStartPaperBurn)
        m_fPaperBurnTime += DT;

    if (m_fPaperBurnTime > 3.f && !GetOwner()->IsDead())
    {
        GetOwner()->GetScript<CKnightScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)600);
        CLevelSaveLoadInScript script;
        script.MoneyCount(600);
        CGameObject* pDoor = script.SpawnandReturnPrefab(L"prefab\\LevelChangeDoor.prefab",(int)LAYER::LEVELCHANGEDOOR,GetOwner()->Transform()->GetWorldPos());
        pDoor->GetScript<CLevelChangeDoorScript>()->SetLevelType((int)LEVEL_TYPE::HALL);
        GetOwnerScript()->Destroy();
    }
}

void CKnightDeath::Exit()
{
}
