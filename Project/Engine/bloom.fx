#ifndef _BLOOM
#define _BLOOM

#include "value.fx"
#include "func.fx"
#include "struct.fx"
//===============
//tex_3 = ����� texture
//WRAP = clamp
//Sampler = minmap
//===============

//���� ����, ������Ʈ�� ����

#define FADETYPE     g_int_0
#define FADETIME      g_float_0

#define BLACKWHITE    g_int_1

struct VS_IN
{
    float3 vPosition : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Bloom(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition.xy = _in.vPosition;//����� �� ������
    //output.vPosition.xy = _in.vPosition * 2.f;//��ü ȭ�� = local���� NPC�������� �����ؾߵǱ⿡ 2�踦 �����ش�
    output.vPosition.zw = 1.f;
    output.vUV = _in.vUV;
    return output;
}

float4 GaussianBlurHorizontal(float2 texCoord, float pixelSize, int blurRadius)
{
    float4 blurColor = 0;
    
    for (int i = -blurRadius; i <= blurRadius; i++)
    {
        float2 offset = float2(i * pixelSize, 0);
        blurColor += g_tex_0.Sample(g_sam_0, texCoord + offset);
    }
    
    return blurColor / float(blurRadius * 2 + 1);
}

float4 GaussianBlurVertical(float2 texCoord, float pixelSize, int blurRadius)
{
    float4 blurColor = 0;
    
    for (int i = -blurRadius; i <= blurRadius; i++)
    {
        float2 offset = float2(0, i * pixelSize);
        blurColor += g_tex_0.Sample(g_sam_0, texCoord + offset);
    }
    
    return blurColor / float(blurRadius * 2 + 1);
}

static float2 PixelKernel[13] =
{
    { -6, 0 },
    { -5, 0 },
    { -4, 0 },
    { -3, 0 },
    { -2, 0 },
    { -1, 0 },
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 },
    { 4, 0 },
    { 5, 0 },
    { 6, 0 },
};

//�̸� ����� �� ���콺 ������ ����ũ ��
static float BlurWeights[13] =
{
    0.002216f, 0.008764f, 0.026995f, 0.064759f, 0.120985f, 0.176033f, 0.199471f, 0.176033f, 0.120985f, 0.064759f,
    0.026995f, 0.008764f, 0.002216f,

};

float4 PS_Bloom(VS_OUT _in) : SV_Target
{
    float4 vOriginalColor = (float4) 0.f;
    float4 vBloomColor = (float4) 0.f;
    float4 vDownSampleColor = (float4) 0.f;
    float fDOFDepth = 0.f;
    
    
    float vDOFDepth = 0.f;
    
    // ȣ��� �ȼ��� ȭ�� ��ü ���� UV
    float2 vFullUV = _in.vPosition.xy / g_Resolution;
        
    vOriginalColor = g_tex_0.Sample(g_sam_0, vFullUV);
    vDownSampleColor = float4(0.5f, 0.5f, 0.5f, 0.5f);
    //g_tex_1.Sample(g_sam_0, vFullUV);
    fDOFDepth = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //g_tex_2.Sample(g_sam_0, vFullUV);
    vBloomColor = float4(0.0f, 0.0f, 0.0f, 0.1f);
    //g_tex_3.Sample(g_sam_0, vFullUV);
    
    fDOFDepth = clamp(fDOFDepth, 0.1f, 0.8f);//DOFDEPTH�� �ּ� 0.1, �ִ� 0.8�� ����
    
    vOriginalColor = lerp(vOriginalColor, vDownSampleColor * 0.81f, fDOFDepth);//return original color + dofdepth(downsamplecolor*0.81 - original color
    
    vOriginalColor += vBloomColor;
    int blackwhite = 0;

    
    if (BLACKWHITE == 1)
    {
        float Brigtness = (vOriginalColor.x + vOriginalColor.y + vOriginalColor.z) / 3.f;
        
        if (Brigtness > 0.2f)//0.5�̻����� �ɷ�����
        {
            vOriginalColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            vOriginalColor = float4(.0f, .0f, .0f, .0f);
        }
        
    }
    //return vOriginalColor;
    return Fade_In_Out(vOriginalColor, FADETYPE, FADETIME);
    //return Fade_In_Out(vOriginalColor, 0, 5.f);
}


#endif