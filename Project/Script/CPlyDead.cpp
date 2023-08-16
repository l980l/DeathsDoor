#include "pch.h"
#include "CPlyDead.h"
#include "CPlayerScript.h"
#include "CLevelSaveLoadInScript.h"
#include <Engine/CEventMgr.h>
#include <Engine/CDevice.h>

CPlyDead::CPlyDead()
	: m_pDeathTex(nullptr)
	, m_fTimetoStartPoint(7.f)
{
}

CPlyDead::~CPlyDead()
{
}

void CPlyDead::Enter()
{
	GetOwner()->Animator3D()->Play((int)PLAYERANIM_TYPE::HIT_IDLE, false);
	GetOwner()->GetScript<CPlayerScript>()->SetInvincible(true);
}

void CPlyDead::tick()
{
	m_fTimetoStartPoint -= DT;
	if(GetOwner()->Animator3D()->IsFinish())
	{
		if (nullptr == m_pDeathTex)
		{
			Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
			m_pDeathTex = new CGameObject;
			m_pDeathTex->AddComponent(new CTransform);
			m_pDeathTex->AddComponent(new CMeshRender);
			m_pDeathTex->Transform()->SetRelativeScale(Vec3(vRenderResolution.x, vRenderResolution.y, 1.f));
			m_pDeathTex->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
			m_pDeathTex->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"), 0);
			m_pDeathTex->MeshRender()->GetDynamicMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->LoadTexture(L"texture\\HUD\\DeathFilter.png", L"texture\\HUD\\DeathFilter.png", 0));

			SpawnGameObject(m_pDeathTex, Vec3(0.f), (int)LAYER::UI);
		}
		if (m_fTimetoStartPoint <= 0.f)
		{
			// ��� �ؽ��� ��� �ð��� ������ ���緹���� �ٽ� ������.
			int iCurLevelType = CLevelMgr::GetInst()->GetCurLevel()->GetLevelType();
			CLevel* NewLevel = CLevelSaveLoadInScript::Stop(L"Level\\LLL.lv", LEVEL_STATE::STOP);
			NewLevel->SetName(L"LevelLoading");
			NewLevel->SetLevelType(iCurLevelType);
			tEvent evn = {};
			evn.Type = EVENT_TYPE::LEVEL_CHANGE;
			evn.wParam = (DWORD_PTR)NewLevel;
			evn.lParam = (DWORD_PTR)NewLevel->GetLevelType();
			CEventMgr::GetInst()->AddEvent(evn);

			m_pDeathTex->SetLifeSpan(0.f);
		}
	}
	// ��� �۾��� ȭ���� �����鼭 Hall Level���� �ٽ� ����
	GetOwner()->Rigidbody()->ClearForce();
}

void CPlyDead::Exit()
{
	m_pDeathTex = nullptr;
}
