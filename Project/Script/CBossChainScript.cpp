#include "pch.h"
#include "CBossChainScript.h"
#include "CCrowBossChainThrow.h"

CBossChainScript::CBossChainScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSCHAINSCRIPT)
{
}

CBossChainScript::~CBossChainScript()
{
}

void CBossChainScript::begin()
{
}

void CBossChainScript::tick()
{
}

void CBossChainScript::Active(bool _bActive)
{
}

void CBossChainScript::BeginOverlap(CCollider3D* _Other)
{
}

void CBossChainScript::EndOverlap(CCollider3D* _Other)
{
}

void CBossChainScript::PaveChain()
{
}

void CBossChainScript::Clear()
{
}
