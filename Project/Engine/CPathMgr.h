#pragma once


class CPathMgr
    : public CSingleton<CPathMgr>
{
    SINGLE(CPathMgr);
    wchar_t m_szContentPath[256];

public:
    void init();

    const wchar_t* GetContentPath() const { return m_szContentPath; }
};
