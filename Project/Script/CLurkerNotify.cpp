#include "pch.h"
#include "CLurkerNotify.h"
#include "CLurkerScript.h"
#include "CSoundScript.h"

void CLurkerNotify::Enter()
{
	// AnimClip �̸��� ReadyAction��
	GetOwner()->Animator3D()->Play(1, false);

	// Player ����
	GetOwner()->GetScript<CLurkerScript>()->SetStarePlayer(true);
}

void CLurkerNotify::tick()
{
	// �̹� Notify �ൿ�� ������ �ִٸ� �ٸ� ���·�.
	if (m_bNotifyAnimEnd)
	{
		Vec3 PlayerPos = GetOwner()->GetScript<CLurkerScript>()->GetPlayerPos();
		float fDistance = GetOwner()->GetScript<CLurkerScript>()->GetPlayerDistance();

		// ���� ������ ���� ���. ������ �����ؼ� 4���� ���� �� �ϳ��� �����Ѵ�. 
		if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetAttackRange())
		{
			// �ʹ� ������ �齺��.
			if (fDistance < GetOwner()->GetScript<CLurkerScript>()->GetBackStepRange() && !m_bJustBeforeBackStep)
			{
				ChangeState(L"BackStep");
				m_bJustBeforeBackStep = true;
			}

			else
			{
				m_bJustBeforeBackStep = false;
				
				srand(time(0));
				int iRandom = rand() % 3;

				// ������ ���� ���ϰ� �ٸ� ������ �������� �ϱ�.
				if (m_iPrevPattern == iRandom)
				{
					if (m_iPrevPattern == 2)
						iRandom = 0;

					else
						++iRandom;
				}

				m_iPrevPattern = iRandom;

				if (iRandom == 0)
					ChangeState(L"Attack");
				else if (iRandom == 1)
					ChangeState(L"LeftMove");
				else if (iRandom == 2)
					ChangeState(L"RightMove");
			}
		}

		else
			ChangeState(L"Trace");
	}

	// ���� �������� ReadyAction �ִϸ��̼��� �����ٸ� m_bNotifyAnimEnd�� true�� ����.
	else
	{
		if (GetOwner()->Animator3D()->IsFinish())
			m_bNotifyAnimEnd = true;

		// Sound
		CSoundScript* soundscript = CLevelMgr::GetInst()->FindObjectByName(L"SoundUI")->GetScript<CSoundScript>();
		Ptr<CSound> pSound = soundscript->AddSound(L"Sound\\Monster\\Lurker\\LurkerDodge1.ogg", 1, 0.1f);
	}
}

void CLurkerNotify::Exit()
{
}

CLurkerNotify::CLurkerNotify() :
	m_bNotifyAnimEnd(false)
	, m_iPrevPattern(-1)
{
}

CLurkerNotify::~CLurkerNotify()
{
}
