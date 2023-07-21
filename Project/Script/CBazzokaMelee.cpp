#include "pch.h"
#include "CBazzokaMelee.h"
#include "CBazookaScript.h"

void CBazzokaMelee::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CBazzokaMelee::tick()
{
}

void CBazzokaMelee::Exit()
{
}

CBazzokaMelee::CBazzokaMelee()
{
}

CBazzokaMelee::~CBazzokaMelee()
{
}
