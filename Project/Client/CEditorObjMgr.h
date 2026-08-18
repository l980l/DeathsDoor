#pragma once

class CGameObjectEx;

class CEditorObjMgr
    : public CSingleton<CEditorObjMgr>
{
    SINGLE(CEditorObjMgr);
    vector<CGameObjectEx*> m_vecEditorObj;

    CGameObjectEx*          m_DebugShape[static_cast<UINT>(SHAPE_TYPE::END)];
    vector<tDebugShapeInfo> m_DebugShapeInfo;

public:
    void init();
    void progress();

private:
    void tick() const;
    void render();
};
