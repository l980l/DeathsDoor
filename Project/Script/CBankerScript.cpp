#include "pch.h"
#include "CBankerScript.h"
#include "CPower.h"
#include "CAttackSpeed.h"
#include "CSpeed.h"
#include "CMagic.h"
#include "CStateScript.h"

CBankerScript::CBankerScript()	:
	CScript(SCRIPT_TYPE::BANKERSCRIPT)
{
}

CBankerScript::~CBankerScript()
{
}
void CBankerScript::begin()
{
	int iMtrlCount = MeshRender()->GetMtrlCount();

	for (int i = 0; i < iMtrlCount; ++i)
	{
		MeshRender()->GetDynamicMaterial(i);
	}

	// 상태 설정
	if (nullptr == m_pStateScript)
	{
		m_pStateScript = GetOwner()->GetScript<CStateScript>();
		m_pStateScript->AddState(L"Power", new CPower);
		m_pStateScript->AddState(L"AttackSpeed", new CAttackSpeed);
		m_pStateScript->AddState(L"Speed", new CSpeed);
		m_pStateScript->AddState(L"Magic", new CMagic);

		m_pStateScript->ChangeState(L"Power");
	}
}

void CBankerScript::tick()
{
}

void CBankerScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBankerScript::OnOverlap(CCollider3D* _Other)
{
	
}

void CBankerScript::EndOverlap(CCollider3D* _Other)
{
}


