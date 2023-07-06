#include "pch.h"
#include "CStateScript.h"

#include "CState.h"

CStateScript::CStateScript()
	: CScript((UINT)SCRIPT_TYPE::STATESCRIPT)
	, m_mapState{}
	, m_pCurState(nullptr)
{
}

CStateScript::~CStateScript()
{
	Safe_Del_Map(m_mapState);
}

void CStateScript::begin()
{
}

void CStateScript::tick()
{
	if (nullptr == m_pCurState)
		return;

	m_pCurState->tick();
}

void CStateScript::AddState(const wstring& _strKey, CState* _pState)
{
	m_mapState.insert(make_pair(_strKey, _pState));
	_pState->m_pOwnerScript = this;
}

void CStateScript::ChangeState(const wstring& _strStateName)
{
	// ���ڷ� ���� �̸����� State�� ã�� ���� State�� ������.
	CState* pNextState = FindState(_strStateName);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}

void CStateScript::BeginOverlap(CCollider2D* _Other)
{
	m_pCurState->BeginOverlap(_Other);
}

void CStateScript::OnOverlap(CCollider2D* _Other)
{
	m_pCurState->OnOverlap(_Other);
}

void CStateScript::EndOverlap(CCollider2D* _Other)
{
	m_pCurState->EndOverlap(_Other);
}
