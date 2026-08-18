#include "pch.h"
#include "CState.h"

CState::CState()
    : m_pOwnerScript(nullptr)
{
}

CState::~CState()
{
}

void CState::ChangeState(wstring _strStateName) const
{
    m_pOwnerScript->ChangeState(_strStateName);
}
