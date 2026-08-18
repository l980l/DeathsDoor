#pragma once

class CEntity
{
    static UINT g_iNextID;

    wstring    m_strName;
    const UINT m_iID;

public:
    void           SetName(const wstring& _strName) { m_strName = _strName; }
    const wstring& GetName() { return m_strName; }
    UINT           GetID() const { return m_iID; }

    virtual CEntity* Clone() = 0;

    CEntity();
    CEntity(const CEntity& _other);
    virtual ~CEntity();
};
