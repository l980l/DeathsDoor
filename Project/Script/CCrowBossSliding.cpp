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
		// 부모 옵젝의 자식 중에서 CrowBossChain이 있는지 확인한다. 
		/*if(vecChild[i]->GetScript<CrowBossChainScript>())
		{	
			// 있다면 해당 체인을 따라서 돌진해야 함. 음... 체인을 뽑아낸 다음, 그 체인 째로 이동하는게 맞는듯? 화면 밖으로 나가면 지우고. 

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
