#pragma once

#include "ptr.h"
#include "CTexture.h"

class CConstBuffer;

class CDevice
    : public CSingleton<CDevice>
{
    HWND m_hWnd;

    ComPtr<ID3D11Device>        m_Device;  // GPU 메모리 할당
    ComPtr<ID3D11DeviceContext> m_Context; // GPU 제어, 렌더링, 동작 수행

    ComPtr<IDXGISwapChain> m_SwapChain;

    // 이제는 MRT에서 Clear 및 OMSet을 하므로 멤버로 RT 및 DST를 가질 필요가 없음.

    // Sampler
    ComPtr<ID3D11SamplerState> m_Sampler[2];

    // RasterizerState
    ComPtr<ID3D11RasterizerState> m_RSState[static_cast<UINT>(RS_TYPE::END)];

    // DepthStencilState
    ComPtr<ID3D11DepthStencilState> m_DSState[static_cast<UINT>(DS_TYPE::END)];

    // BlendState
    ComPtr<ID3D11BlendState> m_BSState[static_cast<UINT>(BS_TYPE::END)];


    D3D11_VIEWPORT m_ViewPort;

    // 렌더타겟 해상도
    Vec2          m_vRenderResolution;
    CConstBuffer* m_arrConstBuffer[static_cast<UINT>(CB_TYPE::END)];

public:
    int  init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
    void Present() const { m_SwapChain->Present(0, 0); }

    Vec2 GetRenderResolution() const { return m_vRenderResolution; }

private:
    int  CreateSwapChain();
    int  CreateView() const;
    int  CreateRasterizerState();
    int  CreateBlendState();
    int  CreateDepthStencilState();
    int  CreateSampler();
    void CreateConstBuffer();

public:
    ID3D11Device*        GetDevice() const { return m_Device.Get(); }
    ID3D11DeviceContext* GetDeviceContext() const { return m_Context.Get(); }
    CConstBuffer*        GetConstBuffer(CB_TYPE _Type) const { return m_arrConstBuffer[static_cast<UINT>(_Type)]; }

    ComPtr<ID3D11RasterizerState>   GetRSState(RS_TYPE _Type) { return m_RSState[static_cast<UINT>(_Type)]; }
    ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_DSState[static_cast<UINT>(_Type)]; }
    ComPtr<ID3D11BlendState>        GetBSState(BS_TYPE _Type) { return m_BSState[static_cast<UINT>(_Type)]; }


    CDevice();
    virtual ~CDevice() override;
};
