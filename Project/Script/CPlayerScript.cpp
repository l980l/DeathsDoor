#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CStateScript.h"
#include "PlayerStates.h"
#include "CPlayerWeaponScript.h"
#include "CLadderScript.h"
#include "CLevelSaveLoadInScript.h"
#include "CGameCameraScript.h"

#include <Engine\CRenderMgr.h>
#include <Engine/CPhysXMgr.h>

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pStateScript(nullptr)
	, m_iCurMagic(0)
	, m_bInvincible(false)
	, m_pSword(nullptr)
	, m_imoney(0)
	, m_iUpgrade{}
{
}

CPlayerScript::~CPlayerScript()
{
	if (nullptr == m_pStateScript)
		delete m_pStateScript;
}

void CPlayerScript::begin()
{
	if (nullptr == m_pSword)
	{
		m_pSword = GetOwner()->GetChild()[0]->GetScript<CPlayerWeaponScript>();
	}
	if(nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>(); 
		m_pStateScript->AddState(L"Idle", new CPlyIdle);
		m_pStateScript->AddState(L"Walk", new CPlyWalk);
		m_pStateScript->AddState(L"Run", new CPlyRun);
		m_pStateScript->AddState(L"Dodge", new CPlyDodge);
		m_pStateScript->AddState(L"Fall", new CPlyFall);
		m_pStateScript->AddState(L"Hit", new CPlyHit);
		m_pStateScript->AddState(L"Dead", new CPlyDead);
		m_pStateScript->AddState(L"Attack", new CPlyAttack);
		m_pStateScript->AddState(L"Ladder", new CPlyLadder);
		m_pStateScript->AddState(L"Arrow", new CPlyMagic_Arrow);
		m_pStateScript->AddState(L"Fire", new CPlyMagic_Fire);
		m_pStateScript->AddState(L"Bomb", new CPlyMagic_Bomb);
		m_pStateScript->AddState(L"Hook", new CPlyMagic_Hook);
		m_pStateScript->AddState(L"Hooking", new CPlyMagic_Hooking);
		m_pStateScript->ChangeState(L"Idle");
	}	
}

void CPlayerScript::tick()
{
	// ���� 1~4�� ��Ŭ������ ����ϴ� ���� ȿ�� ����
	SetMagicType();
	EditorMode();
	// Fall ���� üũ
	FallCheck();
	// Sword(Child0)�� Bow(Child1)�� Emissiveȿ�� �ο�
	int a = 1;
	GetOwner()->GetChild()[0]->MeshRender()->GetMaterial(0)->SetScalarParam(INT_0, &a);
	GetOwner()->GetChild()[1]->MeshRender()->GetMaterial(0)->SetScalarParam(INT_0, &a);
}

void CPlayerScript::BeginOverlap(CCollider3D* _Other)
{
	if (m_bEditorMode)
		return;
	// �Ʒ��� �ǰ� �������� �����̶�� return;
	if (m_bInvincible)
		return;

	if ((int)LAYER::MONSTERPROJECTILE == _Other->GetOwner()->GetLayerIndex())
	{
		ChangeState(L"Hit");
		Stat CurStat = m_pStateScript->GetStat();
		CurStat.HP -= 1;
		m_pStateScript->SetStat(CurStat);
		if (CurStat.HP <= 0)
		{
			ChangeState(L"Dead");
		}
		else
		{
			ChangeState(L"Hit");
		}

		CLevelSaveLoadInScript::SpawnPrefab(L"prefab\\HitEffect.prefab", (int)LAYER::DEFAULT, Transform()->GetWorldPos(), 0.3f);
		CAMERASHAKE(3.f, 800.f, 0.1f);
	}
}

void CPlayerScript::OnOverlap(CCollider3D* _Other)
{
	if ((int)LAYER::LADDER == _Other->GetOwner()->GetLayerIndex())
	{
		if (KEY_TAP(KEY::E))
		{	
			// ��ٸ��� �ٶ󺸰� �ִ� ����, ��ġ�� �÷��̾ ������Ŵ
			Vec3 vLadderRot = _Other->GetOwner()->Transform()->GetXZDir();
			GetOwner()->Transform()->SetRelativeRot(Vec3(XM_PI * 1.5f, vLadderRot.y, 0.f));
			Vec3 vLadderPos = _Other->GetOwner()->Transform()->GetRelativePos();
			GetOwner()->Rigidbody()->SetRigidPos(vLadderPos);

			ChangeState(L"Ladder");
			CPlyLadder* pLadderState =  (CPlyLadder*)GetOwner()->GetScript<CStateScript>()->FindState(L"Ladder");
			pLadderState->SetHeight(_Other->GetOwner()->GetScript<CLadderScript>()->GetHeight());
		}
	}
}

void CPlayerScript::EndOverlap(CCollider3D* _Other)
{
}

void CPlayerScript::ChangeState(wstring _strStateName)
{
	m_pStateScript->ChangeState(_strStateName);
	m_pSword->ChangeState(_strStateName);
}

void CPlayerScript::SetMagicType()
{
	if (KEY_TAP(KEY::_1))
		m_iCurMagic = (UINT)PLAYER_MAGIC::ARROW;
	else if (KEY_TAP(KEY::_2))
		m_iCurMagic = (UINT)PLAYER_MAGIC::FIRE;
	else if (KEY_TAP(KEY::_3))
		m_iCurMagic = (UINT)PLAYER_MAGIC::BOMB;
	else if (KEY_TAP(KEY::_4))
		m_iCurMagic = (UINT)PLAYER_MAGIC::HOOK;
}

void CPlayerScript::ChangeMagicState()
{
	switch (PLAYER_MAGIC(m_iCurMagic))
	{
	case PLAYER_MAGIC::ARROW:
		ChangeState(L"Arrow");
		break;
	case PLAYER_MAGIC::FIRE:
		ChangeState(L"Fire");
		break;
	case PLAYER_MAGIC::BOMB:
		ChangeState(L"Bomb");
		break;
	case PLAYER_MAGIC::HOOK:
		ChangeState(L"Hook");
		break;
	}
}

void CPlayerScript::FallCheck()
{
	if (m_pStateScript->GetCurState() != m_pStateScript->FindState(L"Dead")
		&& m_pStateScript->GetCurState() != m_pStateScript->FindState(L"Hit"))
	{
		if (abs((Transform()->GetRelativePos() - Transform()->GetPrevPos()).y) > 0.2f)
		{
			m_fFallCheckTime += DT;
			if (m_fFallCheckTime > 0.15f)
			{
				ChangeState(L"Fall");
				m_fFallCheckTime = 0.f;
			}
		}
	}
}

void CPlayerScript::EditorMode()
{
	if (KEY_TAP(KEY::Q))
	{
		Stat CurStat = m_pStateScript->GetStat();
		CurStat.Energy = CurStat.Max_Energy;
		m_pStateScript->SetStat(CurStat);
	}
	if (KEY_TAP(KEY::R))
	{
		Stat CurStat = m_pStateScript->GetStat();
		CurStat.HP = CurStat.Max_HP;
		m_pStateScript->SetStat(CurStat);
	}
	if (KEY_TAP(KEY::F))
	{
		m_bEditorMode = m_bEditorMode ? false : true;
	}

}

void CPlayerScript::Upgrade(PLAYER_UPGRADE _Type)
{
	++m_iUpgrade[(UINT)_Type];

	Stat CurStat = m_pStateScript->GetStat();
	switch (_Type)
	{
		// ���� ���ݷ� �� ���ݹ��� ����
		// 20%�� ������
	case PLAYER_UPGRADE::Strength:
		CurStat.Attack *= 1.f + (0.2f * m_iUpgrade[(UINT)PLAYER_UPGRADE::Strength]);
		break;
		// ���ݵ����� ���� �� 10% ����
	case PLAYER_UPGRADE::Dexterity:
		CurStat.Attack_Speed *= 1.f - (0.1f * m_iUpgrade[(UINT)PLAYER_UPGRADE::Dexterity]);
		break;
		// �̵��ӵ� ���� �� 10% ����
	case PLAYER_UPGRADE::Haste:
		CurStat.Speed *= 1.f + (0.1f * m_iUpgrade[(UINT)PLAYER_UPGRADE::Haste]);
		break;
		// ���� ���ݷ��� ���� �� 30%�� ����
	case PLAYER_UPGRADE::Magic:
		CurStat.Spell_Power *= 1.f + (0.3f * m_iUpgrade[(UINT)PLAYER_UPGRADE::Magic]);
		break;
	}
}

void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_iCurMagic, sizeof(UINT), 1, _File);
	fwrite(&m_imoney, sizeof(UINT), 1, _File);
	for (UINT i = 0; i < (UINT)PLAYER_UPGRADE::END; ++i)
		fwrite(&m_iUpgrade[i], sizeof(UINT), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_iCurMagic, sizeof(UINT), 1, _File);
	fread(&m_imoney, sizeof(UINT), 1, _File);
	for (UINT i = 0; i < (UINT)PLAYER_UPGRADE::END; ++i)
		fread(&m_iUpgrade[i], sizeof(UINT), 1, _File);
}