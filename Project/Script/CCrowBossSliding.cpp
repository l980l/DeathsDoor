#include "pch.h"
#include "CCrowBossSliding.h"
#include "CCrowBossScript.h"

void CCrowBossSliding::Enter()
{
	GetOwner()->Animator3D()->Play(3, true);
}

void CCrowBossSliding::tick()
{
	vector<CGameObject*> vecChild = GetOwner()->GetChild();

	bool bChainExist = false;

	for (int i = 0; i < vecChild.size(); ++i)
	{
		// �θ� ������ �ڽ� �߿��� CrowBossChain�� �ִ��� Ȯ���Ѵ�. 
		/*if(vecChild[i]->GetScript<CrowBossChainScript>())
		{	
			// �ִٸ� �ش� ü���� ���� �����ؾ� ��. ��... ü���� �̾Ƴ� ����, �� ü�� °�� �̵��ϴ°� �´µ�? ȭ�� ������ ������ �����. 

			// bChainExist = true;
		}*/
	}

	if (!bChainExist)
	{
		ChangeState(L"RightSpin");
	}
}

void CCrowBossSliding::Exit()
{
}

CCrowBossSliding::CCrowBossSliding()
{
}

CCrowBossSliding::~CCrowBossSliding()
{
}
