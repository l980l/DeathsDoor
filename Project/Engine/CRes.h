#pragma once
#include "CEntity.h"

class CRes :
    public CEntity
{
    const RES_TYPE m_Type;
    int            m_iRefCount;

    wstring m_strKey;
    wstring m_strRelativePath;

    bool m_bEngine;

protected:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

private:
    void AddRef() { ++m_iRefCount; }
    void Release();


    // 파일로부터 로딩
    virtual int Load(const wstring& _strFilePath) = 0;

public:
    // 파일로 저장
    virtual int Save(const wstring&) = 0;

    // 리소스는 Clone 을 구현하지 않는다.
    virtual CRes* Clone() override
    {
        return nullptr;
        assert(nullptr);
    }

    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }
    RES_TYPE       GetType() const { return m_Type; }
    bool           IsEngineRes() const { return m_bEngine; }

    CRes(RES_TYPE _type, bool _bEngine = false);
    CRes(const CRes& _Other);
    virtual ~CRes() override;

    friend class CResMgr;
    friend class CFBXLoader;

    template <typename T>
    friend class Ptr;
};
