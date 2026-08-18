#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
    CLayer*     m_arrLayer[MAX_LAYER];
    LEVEL_STATE m_State;
    int         m_iLevel_type;

public:
    void begin() const;
    void tick() const;
    void finaltick() const;

    CLayer* FindLayerByName(const wstring& _strName) const;

    CLayer* GetLayer(int _iLayerIdx) const
    {
        assert(!(_iLayerIdx < 0));
        return m_arrLayer[_iLayerIdx];
    }

    CGameObject* FindObjectByName(const wstring& _Name) const;
    void         FindObjectByName(const wstring& _Name, vector<CGameObject*>& _Out) const;

    void AddGameObject(CGameObject* _Object, int _iLayerIdx, bool _Move) const;
    void AddGameObject(CGameObject* _Object, const wstring& _LayerName, bool _Move);

    void        ChangeState(LEVEL_STATE _State);
    LEVEL_STATE GetState() const { return m_State; }
    int         GetLevelType() const { return m_iLevel_type; }
    void        SetLevelType(int _level_type) { m_iLevel_type = _level_type; }

private:
    // 등록된 GameObject 제거
    void clear() const;

    CLONE(CLevel);
    CLevel();
    virtual ~CLevel() override;

    friend class CLevelMgr;
};
