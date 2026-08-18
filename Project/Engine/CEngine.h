#pragma once

class CEngine
    : public CSingleton<CEngine>
{
    HWND m_hWnd;

    // 윈도우 해상도
    Vec2 m_vResolution;

public:
    Vec2 GetWindowResolution() const { return m_vResolution; }
    HWND GetMainWnd() const { return m_hWnd; }

    int  init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
    void progress();

private:
    void tick() const;
    void render() const;

public:
    CEngine();
    virtual ~CEngine() override;
};
