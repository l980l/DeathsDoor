#include "pch.h"
#include "CEventMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CResMgr.h"
#include "CRenderMgr.h"


CEventMgr::CEventMgr()
    : m_LevelChanged(false)
{
}

CEventMgr::~CEventMgr()
{
}


void CEventMgr::tick()
{
    m_LevelChanged = false;

    GC_Clear();

    const size_t EventCount = m_vecEvent.size();
    for (size_t i = 0; i < EventCount; ++i)
    {
        const tEvent Event = m_vecEvent[i];

        switch (Event.Type) // wParam : GameObject, lParam : Layer Index
        {
        case EVENT_TYPE::CREATE_OBJECT:
        {
            CGameObject* pNewObject = reinterpret_cast<CGameObject*>(Event.wParam);
            if (nullptr == pNewObject)
                return;

            const int iLayerIdx = static_cast<int>(Event.lParam);
            CLevelMgr::GetInst()->GetCurLevel()->AddGameObject(pNewObject, iLayerIdx, false);

            if (CLevelMgr::GetInst()->GetCurLevel()->GetState() == LEVEL_STATE::PLAY)
                pNewObject->begin();

            m_LevelChanged = true;
        }
        break;
        case EVENT_TYPE::DELETE_OBJECT:
        {
            CGameObject* pDeleteObject = reinterpret_cast<CGameObject*>(Event.wParam);
            if (false == pDeleteObject->m_bDead)
            {
                pDeleteObject->m_bDead = true;
                m_vecGC.push_back(pDeleteObject);
            }
        }
        break;

        case EVENT_TYPE::ADD_CHILD: // wParam : ParentObject, lParam : ChildObject
        {
            CGameObject* pDestObj = reinterpret_cast<CGameObject*>(Event.wParam);
            CGameObject* pSrcObj  = reinterpret_cast<CGameObject*>(Event.lParam);

            if (nullptr == pSrcObj)
                return;

            // 부모로 지정된 오브젝트가 없으면, Child 오브젝트가 최상위 부모 오브젝트가 된다.
            if (nullptr == pDestObj)
            {
                if (pSrcObj->GetParent())
                {
                    // 기존 부모와의 연결 해제
                    pSrcObj->DisconnectFromParent();
                    // 최상위 부모 오브젝트로, 소속 레이어에 등록
                    pSrcObj->AddParentList();
                }
            }
            else
            {
                pDestObj->AddChild(pSrcObj);
            }

            m_LevelChanged = true;
        }
        break;
        case EVENT_TYPE::DELETE_RESOURCE: // wParam : RES_TYPE, lParam : Resource Adress
        {
            RES_TYPE type = static_cast<RES_TYPE>(Event.wParam);
            CRes*    pRes = reinterpret_cast<CRes*>(Event.lParam);
            if (pRes)
                CResMgr::GetInst()->DeleteRes(type, pRes->GetKey());
        }
        break;
        case EVENT_TYPE::LEVEL_CHANGE:      // wParam : Level Adress, lParam : Level Type
        case EVENT_TYPE::LEVEL_CHANGE_PLAY: // wParam : Level Adress, lParam : Level Type
        {
            const bool PlayAfterChange = EVENT_TYPE::LEVEL_CHANGE_PLAY == Event.Type;

            CRenderMgr::GetInst()->ClearCamera();
            CLevel* pLevel = reinterpret_cast<CLevel*>(Event.wParam);
            if (pLevel)
            {
                pLevel->SetLevelType(static_cast<int>(Event.lParam));
                CLevelMgr::GetInst()->ChangeLevel(pLevel);
                if (PlayAfterChange)
                    pLevel->ChangeState(LEVEL_STATE::PLAY);
                m_LevelChanged = true;
            }
        }
        break;
        }
    }

    m_vecEvent.erase(m_vecEvent.begin(), m_vecEvent.begin() + EventCount);
}


void CEventMgr::GC_Clear()
{
    for (CGameObject* GameObject : m_vecGC)
    {
        if (GameObject)
        {
            if (GameObject->GetParent())
                GameObject->DisconnectFromParent();

            delete GameObject;

            m_LevelChanged = true;
        }
    }

    m_vecGC.clear();
}
