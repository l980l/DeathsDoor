#ifndef _GAUSSIANBLUR
#define _GAUSSIANBLUR

#include "value.fx"
#include "struct.fx"
#include "func.fx"

// ========================
// GaussianBlurShader
// mesh : RectMesh
// g_tex_0 : ColorTarget
// g_tex_1 : EmissiveTarget
// ========================

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_GaussianBlur(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos.xyz * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GaussianBlur(VS_OUT _in) : SV_Target1
{
    float4 vOutColor = (float4) 0.f;
    // ������ �� ����.
    float2 texelSize = 7.f / float2(g_Resolution.x, g_Resolution.y);
    
    // ����þ� ���͸� ������ �ȼ� �߽� ��ǥ
    float2 centerUV = _in.vUV;
    
    // Emissive �� ����.
    vOutColor = g_tex_1.Sample(g_sam_0, centerUV);
    
    // ����þ� ���͸� ������ �ȼ� ���� Emissive ���� �����Ͽ� ����
    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
        {
            float2 offset = float2(i, j) * texelSize;
            vOutColor += g_tex_1.Sample(g_sam_0, centerUV + offset) * GaussianFilter[i + 2][j + 2];
        }
    }
    
    return vOutColor;
}

#endif