#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
private:


public:
    virtual void finaltick() override;
    virtual int render_update() override;

private:
    void CreatePrefabObject();
    void CreateEmptyObject(int layerindx);
    void AddComponent(COMPONENT_TYPE _type);
    void AddScript(const wstring& _strScriptName);

public:
    MenuUI();
    ~MenuUI();
};

