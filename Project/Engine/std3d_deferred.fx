#ifndef _DEFERRED
#define _DEFERRED

#include "value.fx"
#include "func.fx"
#include "struct.fx"

// ========================
// Std3D Deferred Shader
//
// g_tex_0 : Color Texture
// g_tex_1 : Normal Texture
// ========================
struct VS_IN
{
    float3 vPos     : POSITION;
    float2 vUV      : TEXCOORD;
   
    float3 vTangent : TANGENT;
    float3 vNormal  : NORMAL;
    float3 vBinormal : BINORMAL;

    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV       : TEXCOORD;
    
    // �ȼ� ���� �������� ���� ViewPos �� ViewNormal
    float3 vViewPos  : POSITION;
        
    float3 vViewTangent  : TANGENT;
    float3 vViewNormal   : NORMAL;
    float3 vViewBinormal : BINORMAL;
};

VS_OUT VS_Std3D_Deferred(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    if (g_iAnim)
    {
        Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices, 0);
    }

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    // �ȼ� �������� ���� View�����̽� ���� pos, Normal���� ���
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
        
    // ���忡 �ִ� ��� Obj�� ���� ��ġ�� ���� �޾ƾ� �ϹǷ� �̵����� �ݿ����� ����.
    // Obj�� ǥ����� ���͸� View Space �������� ������.
    output.vViewTangent =  normalize(mul(float4(_in.vTangent, 0.f), g_matWV));
    output.vViewNormal =   normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));
        
    return output;
}

// Rasterizer�� ���� ���� �ȼ� ȣ��

struct PS_OUT
{
    float4 vColor       : SV_Target0;
    float4 vNormal      : SV_Target1;
    float4 vPosition    : SV_Target2;
    float4 vData        : SV_Target3;
    float4 vEmissive    : SV_Target4;
};

PS_OUT PS_Std3D_Deferred(VS_OUT _in) : SV_Target
{
    // obj ���� ����(ȸ��)
    float4 vObjectColor = float4(0.6f, 0.6f, 0.6f, 1.f);
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float3 vViewNormal = _in.vViewNormal;
     
    // �ؽ��İ� ������, �ش� ������ ����Ѵ�.
    if (g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
       
    // NomalMap �� �ִٸ�
    if (g_btex_1)
    {
        float3x3 matRot =
        {
            // ���� ��� ���� ���ҽ��� OpenGL���� ���Ǵ� ���ҽ���
            // OpenGL�� DirextX�� ���̳븻�� ������ �ݴ��̹Ƿ� ���̳븻�� ��������.
            _in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal,
        };

        float3 vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        // ������ǥ ���ؿ� �ִ� ���� ��ġ�� ������ǥ�� �������� �Ű���.
        vNormal = normalize((vNormal * 2.f) - 1.f);
        vViewNormal = mul(vNormal, matRot);
    }
    
    PS_OUT output = (PS_OUT) 0.f;
    
    output.vColor =    float4(vObjectColor.xyz, 1.f);
    output.vNormal =   float4(vViewNormal.xyz, 1.f);
    output.vPosition = float4(_in.vViewPos.xyz, 1.f);
    output.vData =     float4(0.f, 0.f, 0.f, 1.f);
    output.vEmissive = float4(0.f, 0.f, 0.f, 1.f);
        
    return output;
}

#endif
