#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
public:
    virtual void finaltick() override;
    virtual int  render_update() override;

private:
    void CreatePrefabObject() const;
    void CreateEmptyObject(int layerindx) const;
    void AddComponent(COMPONENT_TYPE _type) const;
    void AddScript(const wstring& _strScriptName) const;

public:
    MenuUI();
    virtual ~MenuUI() override;
};
