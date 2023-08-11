#include "pch.h"
#include "CKnightDeath.h"
#include "CKnightScript.h"

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

    // ���ݱ��� �帥 �ð��� 3�� �̻��̸� Destory.
    if (m_fPaperBurnTime > 3.f)
        GetOwnerScript()->Destroy();
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
