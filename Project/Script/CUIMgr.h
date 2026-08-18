#pragma once
#include <Engine/CSingleton.h>

enum class HUDUI
{
    HP,
    MP,
    END,
};

class CUIMgr :
    public CSingleton<CUIMgr>
{
    SINGLE(CUIMgr);

    CGameObject* m_arrMagicUI[static_cast<UINT>(PLAYER_MAGIC::END)];
    CGameObject* m_arrHPMPUI[static_cast<UINT>(HUDUI::END)];
    CGameObject* m_pFrameUI;
    bool         m_bActive;

public:
    void UpgradePlayer(PLAYER_UPGRADE _tUpgradeType) const;
    void ActiveMagic(int _tUpgradeType);
    void SetHP(int _iCurHP);
    void SetMP(int _iCurMP, int _iCurMagic);
    void CreateUI();

    CLONE(CUIMgr);
};
