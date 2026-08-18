#pragma once
#include "CRes.h"

class CGameObject;

class CPrefab :
    public CRes
{
    CGameObject* m_ProtoObj;

public:
    CGameObject* Instantiate() const;

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    virtual int Save(const wstring& _strRelativePath) override;

    CGameObject* GetProtoObj() const;

private:
    void         SaveProtoObj(CGameObject* _Obj, FILE* _File);
    CGameObject* LoadProtoObj(FILE* _File);

public:
    void RegisterProtoObject(CGameObject* _Proto);

    CPrefab();
    virtual ~CPrefab() override;

    friend class PrefabUI;
};
