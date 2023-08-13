#include "pch.h"
#include "CKnightDeath.h"
#include "CKnightScript.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadInScript.h"

void CKnightDeath::tick()
{
    // 애니메이션이 끝난 경우 사망 Paperburn 효과 주기.
    if (GetOwner()->Animator3D()->IsFinish())
    {
        GetOwner()->GetScript<CKnightScript>()->SetPaperBurnEffect(true);
        m_bStartPaperBurn = true;
    }

    if (m_bStartPaperBurn)
        m_fPaperBurnTime += DT;

    if (m_fPaperBurnTime > 3.f && GetOwner()->IsDead() == false)
    {
        GetOwner()->GetScript<CKnightScript>()->GetPlayer()->GetScript<CPlayerScript>()->AddMoney((UINT)600);
        CLevelSaveLoadInScript script;
        script.MoneyCount(600);
        GetOwnerScript()->Destroy();
    }
}

void CKnightDeath::Enter()
{
	GetOwner()->Animator3D()->Play(3, false);
}

void CKnightDeath::Exit()
{
}

void CKnightDeath::BeginOverlap(CCollider2D* _Other)
{
}

void CKnightDeath::OnOverlap(CCollider2D* _Other)
{
}

void CKnightDeath::EndOverlap(CCollider2D* _Other)
{
}

CKnightDeath::CKnightDeath()    :
    m_bStartPaperBurn(false),
    m_fPaperBurnTime(0.f)
{
}

CKnightDeath::~CKnightDeath()
{
}
